AM_CPPFLAGS = \
	-I$(top_srcdir)/include \
	-I$(top_srcdir)/common \
	@LIBCSTRING_CPPFLAGS@ \
	@LIBCERROR_CPPFLAGS@

TESTS = \
	test_open_close.sh

check_SCRIPTS = \
	test_open_close.sh

EXTRA_DIST = \
	$(check_SCRIPTS)

check_PROGRAMS =  \
	lnk_test_open_close

lnk_test_open_close_SOURCES = \
	lnk_test_libcerror.h \
	lnk_test_liblnk.h \
	lnk_test_libcstring.h \
	lnk_test_open_close.c

lnk_test_open_close_LDADD = \
	../liblnk/liblnk.la
	@LIBCERROR_LIBADD@ \
	@LIBCSTRING_LIBADD@

MAINTAINERCLEANFILES = \
	Makefile.in

distclean: clean
	/bin/rm -f Makefile

