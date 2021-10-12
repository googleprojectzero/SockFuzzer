## Process this file with automake to produce Makefile.in

HEADERS_CPPFLAGS = \
	-I$(top_builddir) \
	-include $(top_builddir)/config.h \
	-DLIBBSD_DISABLE_DEPRECATED \
	-D__REENTRANT

AM_CPPFLAGS = \
	-isystem $(top_srcdir)/include/bsd/ \
	$(HEADERS_CPPFLAGS) \
	-DLIBBSD_OVERLAY

AM_TESTS_ENVIRONMENT = \
	export CC="$(CC)"; \
	export CPPFLAGS="$(HEADERS_CPPFLAGS)"; \
	export top_srcdir="$(top_srcdir)"; \
	$(nil)

LDADD = $(top_builddir)/src/libbsd.la

EXTRA_DIST = \
	headers-overlay.sh \
	headers-system.sh \
	$(nil)

check_SCRIPTS = \
	headers-overlay.sh \
	headers-system.sh \
	$(nil)

check_PROGRAMS = \
	overlay \
	bzero \
	closefrom \
	endian \
	humanize \
	fgetln \
	funopen \
	fparseln \
	fpurge \
	md5 \
	nlist \
	proctitle-init \
	progname \
	pwcache \
	setmode \
	strl \
	strmode \
	strnstr \
	vis \
	vis-openbsd \
	$(nil)

if HAVE_LIBTESTU01
arc4random_LDADD = $(LDADD) $(TESTU01_LIBS)

check_PROGRAMS += arc4random
endif

if BUILD_LIBBSD_CTOR
proctitle_LDFLAGS = \
	-Wl,-u,libbsd_init_func \
	$(top_builddir)/src/libbsd-ctor.a \
	$(top_builddir)/src/libbsd.la \
	$(nil)

check_PROGRAMS += proctitle
endif

fgetln_SOURCES = test-stream.c test-stream.h fgetln.c
fgetln_CFLAGS = -Wno-deprecated-declarations
fparseln_SOURCES = test-stream.c test-stream.h fparseln.c

proctitle_init_SOURCES = proctitle.c
proctitle_init_CPPFLAGS = $(AM_CPPFLAGS) -DTEST_USE_SETPROCTITLE_INIT=1

TESTS = $(check_SCRIPTS) $(check_PROGRAMS)
