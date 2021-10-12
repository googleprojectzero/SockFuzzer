/*
 * Copyright (c) 1989, 1993
 *	The Regents of the University of California.  All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions
 * are met:
 * 1. Redistributions of source code must retain the above copyright
 *    notice, this list of conditions and the following disclaimer.
 * 2. Redistributions in binary form must reproduce the above copyright
 *    notice, this list of conditions and the following disclaimer in the
 *    documentation and/or other materials provided with the distribution.
 * 3. Neither the name of the University nor the names of its contributors
 *    may be used to endorse or promote products derived from this software
 *    without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE REGENTS AND CONTRIBUTORS ``AS IS'' AND
 * ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
 * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
 * ARE DISCLAIMED.  IN NO EVENT SHALL THE REGENTS OR CONTRIBUTORS BE LIABLE
 * FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
 * DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS
 * OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION)
 * HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT
 * LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY
 * OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF
 * SUCH DAMAGE.
 */

#include <sys/cdefs.h>

#include <sys/param.h>
#include <sys/mman.h>
#include <sys/stat.h>

#include <errno.h>
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <nlist.h>

#include "local-elf.h"

#ifndef SIZE_T_MAX
#define SIZE_T_MAX 0xffffffffU
#endif

/* Note: This function is used by libkvm0, so we need to export it.
 * It is not declared in the include files though. */
int __fdnlist(int, struct nlist *);

#define	ISLAST(p)	(p->n_un.n_name == 0 || p->n_un.n_name[0] == 0)

/*
 * __elf_is_okay__ - Determine if ehdr really
 * is ELF and valid for the target platform.
 *
 * WARNING:  This is NOT an ELF ABI function and
 * as such its use should be restricted.
 */
static int
__elf_is_okay__(Elf_Ehdr *ehdr)
{
	int retval = 0;
	/*
	 * We need to check magic, class size, endianess,
	 * and version before we look at the rest of the
	 * Elf_Ehdr structure.  These few elements are
	 * represented in a machine independent fashion.
	 */
	if (IS_ELF(*ehdr) &&
	    ehdr->e_ident[EI_CLASS] == ELF_TARG_CLASS &&
	    ehdr->e_ident[EI_DATA] == ELF_TARG_DATA &&
	    ehdr->e_ident[EI_VERSION] == ELF_TARG_VER) {

		/* Now check the machine dependent header */
		if (ehdr->e_machine == ELF_TARG_MACH &&
		    ehdr->e_version == ELF_TARG_VER)
			retval = 1;
	}
	return retval;
}

/*
 * Convert an Elf_Sym into an nlist structure.  This fills in only the
 * n_value and n_type members.
 */
static void
elf_sym_to_nlist(struct nlist *nl, Elf_Sym *s, Elf_Shdr *shdr, int shnum)
{
	nl->n_value = s->st_value;

	switch (s->st_shndx) {
	case SHN_UNDEF:
	case SHN_COMMON:
		nl->n_type = N_UNDF;
		break;
	case SHN_ABS:
		nl->n_type = ELF_ST_TYPE(s->st_info) == STT_FILE ?
		    N_FN : N_ABS;
		break;
	default:
		if (s->st_shndx >= shnum)
			nl->n_type = N_UNDF;
		else {
			Elf_Shdr *sh = shdr + s->st_shndx;

			nl->n_type = sh->sh_type == SHT_PROGBITS ?
			    (sh->sh_flags & SHF_WRITE ? N_DATA : N_TEXT) :
			    (sh->sh_type == SHT_NOBITS ? N_BSS : N_UNDF);
		}
		break;
	}

	if (ELF_ST_BIND(s->st_info) == STB_GLOBAL ||
	    ELF_ST_BIND(s->st_info) == STB_WEAK)
		nl->n_type |= N_EXT;
}

int
__fdnlist(int fd, struct nlist *list)
{
	struct nlist *p;
	Elf_Off symoff = 0, symstroff = 0;
	Elf_Word symsize = 0, symstrsize = 0;
	Elf_Sword cc, i;
	int nent = -1;
	int errsave;
	Elf_Sym sbuf[1024];
	Elf_Sym *s;
	Elf_Ehdr ehdr;
	char *strtab = NULL;
	Elf_Shdr *shdr = NULL;
	Elf_Word shdr_size;
	struct stat st;

	/* Make sure obj is OK */
	if (lseek(fd, (off_t)0, SEEK_SET) == -1 ||
	    read(fd, &ehdr, sizeof(Elf_Ehdr)) != sizeof(Elf_Ehdr) ||
	    !__elf_is_okay__(&ehdr) ||
	    fstat(fd, &st) < 0)
		return (-1);

	if (ehdr.e_shnum == 0 ||
	    ehdr.e_shentsize != sizeof(Elf_Shdr)) {
		errno = ERANGE;
		return (-1);
	}

	/* calculate section header table size */
	shdr_size = ehdr.e_shentsize * ehdr.e_shnum;

	/* Make sure it's not too big to mmap */
	if (shdr_size > SIZE_T_MAX || shdr_size > st.st_size) {
		errno = EFBIG;
		return (-1);
	}

	shdr = malloc((size_t)shdr_size);
	if (shdr == NULL)
		return (-1);

	/* Load section header table. */
	if (pread(fd, shdr, (size_t)shdr_size, (off_t)ehdr.e_shoff) != (ssize_t)shdr_size)
		goto done;

	/*
	 * Find the symbol table entry and it's corresponding
	 * string table entry.	Version 1.1 of the ABI states
	 * that there is only one symbol table but that this
	 * could change in the future.
	 */
	for (i = 0; i < ehdr.e_shnum; i++) {
		if (shdr[i].sh_type == SHT_SYMTAB) {
			if (shdr[i].sh_link >= ehdr.e_shnum)
				goto done;

			symoff = shdr[i].sh_offset;
			symsize = shdr[i].sh_size;
			symstroff = shdr[shdr[i].sh_link].sh_offset;
			symstrsize = shdr[shdr[i].sh_link].sh_size;
			break;
		}
	}

	/* Check for files too large to mmap. */
	if (symstrsize > SIZE_T_MAX || symstrsize > st.st_size) {
		errno = EFBIG;
		goto done;
	}
	/*
	 * Load string table into our address space.  This gives us
	 * an easy way to randomly access all the strings, without
	 * making the memory allocation permanent as with malloc/free
	 * (i.e., munmap will return it to the system).
	 */
	strtab = malloc((size_t)symstrsize);
	if (strtab == NULL)
		goto done;

	if (pread(fd, strtab, (size_t)symstrsize, (off_t)symstroff) != (ssize_t)symstrsize)
		goto done;

	/*
	 * clean out any left-over information for all valid entries.
	 * Type and value defined to be 0 if not found; historical
	 * versions cleared other and desc as well.  Also figure out
	 * the largest string length so don't read any more of the
	 * string table than we have to.
	 *
	 * XXX clearing anything other than n_type and n_value violates
	 * the semantics given in the man page.
	 */
	nent = 0;
	for (p = list; !ISLAST(p); ++p) {
		p->n_type = 0;
		p->n_other = 0;
		p->n_desc = 0;
		p->n_value = 0;
		++nent;
	}

	/* Don't process any further if object is stripped. */
	if (symoff == 0)
		goto done;
		
	if (lseek(fd, (off_t) symoff, SEEK_SET) == -1) {
		nent = -1;
		goto done;
	}

	while (symsize > 0 && nent > 0) {
		cc = MIN(symsize, sizeof(sbuf));
		if (read(fd, sbuf, cc) != cc)
			break;
		symsize -= cc;
		for (s = sbuf; cc > 0 && nent > 0; ++s, cc -= sizeof(*s)) {
			char *name;
			Elf_Word size;

			name = strtab + s->st_name;
			if (name[0] == '\0')
				continue;
			size = symstrsize - s->st_name;

			for (p = list; !ISLAST(p); p++) {
				if ((p->n_un.n_name[0] == '_' &&
				     strncmp(name, p->n_un.n_name+1, size) == 0) ||
				    strncmp(name, p->n_un.n_name, size) == 0) {
					elf_sym_to_nlist(p, s, shdr,
					    ehdr.e_shnum);
					if (--nent <= 0)
						break;
				}
			}
		}
	}
  done:
	errsave = errno;
	free(strtab);
	free(shdr);
	errno = errsave;
	return (nent);
}

int
nlist(const char *name, struct nlist *list)
{
	int fd, n;

	if (list == NULL) {
		errno = EINVAL;
		return (-1);
	}
	fd = open(name, O_RDONLY, 0);
	if (fd < 0)
		return (-1);
	n = __fdnlist(fd, list);
	(void)close(fd);
	return (n);
}
