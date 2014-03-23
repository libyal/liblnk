if HAVE_PYTHON
AM_CFLAGS = \
	-I$(top_srcdir)/include \
	-I$(top_srcdir)/common \
	@LIBCSTRING_CPPFLAGS@ \
	@LIBCERROR_CPPFLAGS@ \
	@LIBCDATA_CPPFLAGS@ \
	@LIBCLOCALE_CPPFLAGS@ \
	@LIBUNA_CPPFLAGS@ \
	@LIBCFILE_CPPFLAGS@ \
	@LIBCPATH_CPPFLAGS@ \
	@LIBBFIO_CPPFLAGS@

pyexec_LTLIBRARIES = pylnk.la

pylnk_la_SOURCES = \
	pylnk.c pylnk.h \
	pylnk_codepage.c pylnk_codepage.h \
	pylnk_data_flags.c pylnk_data_flags.h \
	pylnk_datetime.c pylnk_datetime.h \
	pylnk_drive_types.c pylnk_drive_types.h \
	pylnk_error.c pylnk_error.h \
	pylnk_file.c pylnk_file.h \
	pylnk_file_attribute_flags.c pylnk_file_attribute_flags.h \
	pylnk_file_object_io_handle.c pylnk_file_object_io_handle.h \
	pylnk_integer.c pylnk_integer.h \
	pylnk_libbfio.h \
	pylnk_libcerror.h \
	pylnk_libclocale.h \
	pylnk_libcstring.h \
	pylnk_liblnk.h \
	pylnk_python.h \
	pylnk_unused.h

pylnk_la_LIBADD = \
	@LIBCSTRING_LIBADD@ \
	@LIBCERROR_LIBADD@ \
	../liblnk/liblnk.la \
	@LIBCDATA_LIBADD@ \
	@LIBCLOCALE_LIBADD@ \
	@LIBCFILE_LIBADD@ \
	@LIBCPATH_LIBADD@ \
	@LIBBFIO_LIBADD@

pylnk_la_CPPFLAGS = $(PYTHON_CPPFLAGS)
pylnk_la_LDFLAGS  = -module -avoid-version $(PYTHON_LDFLAGS)

endif

EXTRA_DIST = \
	setup.py \
	setup.py.in

MAINTAINERCLEANFILES = \
	Makefile.in

distclean: clean
	/bin/rm -f setup.py
	/bin/rm -f Makefile

