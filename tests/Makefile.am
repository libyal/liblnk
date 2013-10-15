AM_CPPFLAGS = \
	-I$(top_srcdir)/include \
	-I$(top_srcdir)/common \
	@LIBCSTRING_CPPFLAGS@ \
	@LIBCERROR_CPPFLAGS@ \
	@LIBCDATA_CPPFLAGS@ \
	@LIBCLOCALE_CPPFLAGS@ \
	@LIBCNOTIFY_CPPFLAGS@ \
	@LIBCSPLIT_CPPFLAGS@ \
	@LIBUNA_CPPFLAGS@ \
	@LIBCFILE_CPPFLAGS@ \
	@LIBCPATH_CPPFLAGS@ \
	@LIBBFIO_CPPFLAGS@ \
	@LIBLNK_DLL_IMPORT@

if HAVE_PYTHON
TESTS_PYLNK  = \
	test_pylnk_set_ascii_codepage.sh \
	test_pylnk_open_close.sh
endif

TESTS = \
	test_set_ascii_codepage.sh \
	test_open_close.sh \
	test_lnkinfo.sh \
	$(TESTS_PYLNK)

check_SCRIPTS = \
	pylnk_test_open_close.py \
	pylnk_test_set_ascii_codepage.py \
	test_open_close.sh \
	test_pylnk_open_close.sh \
	test_pylnk_set_ascii_codepage.sh \
	test_lnkinfo.sh \
	test_runner.sh \
	test_set_ascii_codepage.sh

EXTRA_DIST = \
	$(check_SCRIPTS)

check_PROGRAMS =  \
	lnk_test_open_close \
	lnk_test_set_ascii_codepage

lnk_test_open_close_SOURCES = \
	lnk_test_libcerror.h \
	lnk_test_liblnk.h \
	lnk_test_libcstring.h \
	lnk_test_open_close.c

lnk_test_open_close_LDADD = \
	../liblnk/liblnk.la \
	@LIBBFIO_LIBADD@ \
	@LIBCPATH_LIBADD@ \
	@LIBCFILE_LIBADD@ \
	@LIBUNA_LIBADD@ \
	@LIBCSPLIT_LIBADD@ \
	@LIBCNOTIFY_LIBADD@ \
	@LIBCLOCALE_LIBADD@ \
	@LIBCDATA_LIBADD@ \
	@LIBCERROR_LIBADD@ \
	@LIBCSTRING_LIBADD@

lnk_test_set_ascii_codepage_SOURCES = \
	lnk_test_libcerror.h \
	lnk_test_libclocale.h \
	lnk_test_liblnk.h \
	lnk_test_libcstring.h \
	lnk_test_set_ascii_codepage.c

lnk_test_set_ascii_codepage_LDADD = \
	../liblnk/liblnk.la \
	@LIBCLOCALE_LIBADD@ \
	@LIBCERROR_LIBADD@ \
	@LIBCSTRING_LIBADD@

MAINTAINERCLEANFILES = \
	Makefile.in

distclean: clean
	/bin/rm -f Makefile

