/*
 * Copyright © 2013 Guillem Jover <guillem@hadrons.org>
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions
 * are met:
 * 1. Redistributions of source code must retain the above copyright
 *    notice, this list of conditions and the following disclaimer.
 * 2. Redistributions in binary form must reproduce the above copyright
 *    notice, this list of conditions and the following disclaimer in the
 *    documentation and/or other materials provided with the distribution.
 * 3. The name of the author may not be used to endorse or promote products
 *    derived from this software without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED ``AS IS'' AND ANY EXPRESS OR IMPLIED WARRANTIES,
 * INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY
 * AND FITNESS FOR A PARTICULAR PURPOSE ARE DISCLAIMED.  IN NO EVENT SHALL
 * THE AUTHOR BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL,
 * EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO,
 * PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS;
 * OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY,
 * WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR
 * OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF
 * ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 */

#include <unistd.h>

/*
 * The automatic initialization cannot be part of the main shared library,
 * because there is no thread-safe way to change the environ global
 * variable. This is not a problem if the initializaion happens just at
 * program load time, but becomes one if the shared library is directly or
 * indirectly dlopen()ed during the execution of the program, which could
 * have either kept references to the old environ or could change it in
 * some other thread. This has been observed for example on systems using
 * Samba NSS modules.
 *
 * To avoid any other possible fallout, the constructor is split into a
 * new static library that needs to be linked explicitly into programs
 * using setproctitle(). As an additional safety measure the pkg-config
 * linker flags will mark the program as not allowing to be dlopen()ed
 * so that we make sure to avoid the problem described above.
 */

/*
 * Force setproctitle_init() function into the .init_array section instead of
 * expecting either the compiler to place constructors there or the linker to
 * move them from .ctors to .init_array.
 */
void (*libbsd_init_func)(int argc, char *argv[], char *envp[])
	__attribute__((__section__(".init_array"))) = setproctitle_init;
