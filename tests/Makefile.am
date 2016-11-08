AM_CPPFLAGS = \
	-I$(top_srcdir)/include \
	-I$(top_srcdir)/common \
	@LIBCERROR_CPPFLAGS@ \
	@LIBCDATA_CPPFLAGS@ \
	@LIBCLOCALE_CPPFLAGS@ \
	@LIBCNOTIFY_CPPFLAGS@ \
	@LIBCSPLIT_CPPFLAGS@ \
	@LIBUNA_CPPFLAGS@ \
	@LIBCFILE_CPPFLAGS@ \
	@LIBCPATH_CPPFLAGS@ \
	@LIBBFIO_CPPFLAGS@ \
	@LIBCSYSTEM_CPPFLAGS@ \
	@PTHREAD_CPPFLAGS@ \
	@LIBLNK_DLL_IMPORT@

if HAVE_PYTHON_TESTS
TESTS_PYLNK = \
	test_python_functions.sh \
	test_pylnk_set_ascii_codepage.sh
endif

TESTS = \
	test_api_functions.sh \
	test_api_types.sh \
	test_lnkinfo.sh \
	$(TESTS_PYLNK)

check_SCRIPTS = \
	pylnk_test_get_version.py \
	pylnk_test_open_close.py \
	pylnk_test_set_ascii_codepage.py \
	test_api_functions.sh \
	test_api_types.sh \
	test_lnkinfo.sh \
	test_python_functions.sh \
	test_pylnk_set_ascii_codepage.sh \
	test_runner.sh

EXTRA_DIST = \
	$(check_SCRIPTS)

check_PROGRAMS = \
	lnk_test_error \
	lnk_test_file \
	lnk_test_open_close \
	lnk_test_support

lnk_test_error_SOURCES = \
	lnk_test_error.c \
	lnk_test_liblnk.h \
	lnk_test_macros.h \
	lnk_test_unused.h

lnk_test_error_LDADD = \
	../liblnk/liblnk.la

lnk_test_file_SOURCES = \
	lnk_test_file.c \
	lnk_test_libcerror.h \
	lnk_test_libclocale.h \
	lnk_test_libcsystem.h \
	lnk_test_liblnk.h \
	lnk_test_libuna.h \
	lnk_test_memory.c lnk_test_memory.h \
	lnk_test_unused.h

lnk_test_file_LDADD = \
	@LIBCSYSTEM_LIBADD@ \
	@LIBUNA_LIBADD@ \
	@LIBCNOTIFY_LIBADD@ \
	@LIBCLOCALE_LIBADD@ \
	@LIBCDATA_LIBADD@ \
	../liblnk/liblnk.la \
	@LIBCERROR_LIBADD@

lnk_test_open_close_SOURCES = \
	lnk_test_libcerror.h \
	lnk_test_libcsystem.h \
	lnk_test_liblnk.h \
	lnk_test_open_close.c

lnk_test_open_close_LDADD = \
	@LIBCSYSTEM_LIBADD@ \
	../liblnk/liblnk.la \
	@LIBCTHREADS_LIBADD@ \
	@LIBCERROR_LIBADD@
	@PTHREAD_LIBADD@

lnk_test_support_SOURCES = \
	lnk_test_libcerror.h \
	lnk_test_libclocale.h \
	lnk_test_libcsystem.h \
	lnk_test_liblnk.h \
	lnk_test_libuna.h \
	lnk_test_macros.h \
	lnk_test_support.c \
	lnk_test_unused.h

lnk_test_support_LDADD = \
	@LIBCSYSTEM_LIBADD@ \
	@LIBUNA_LIBADD@ \
	@LIBCNOTIFY_LIBADD@ \
	@LIBCLOCALE_LIBADD@ \
	@LIBCDATA_LIBADD@ \
	../liblnk/liblnk.la \
	@LIBCERROR_LIBADD@

MAINTAINERCLEANFILES = \
	Makefile.in

distclean: clean
	/bin/rm -f Makefile

