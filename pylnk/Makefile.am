if HAVE_PYTHON
AM_CFLAGS = \
	-I$(top_srcdir)/include \
	-I$(top_srcdir)/common \
	-I$(top_srcdir)/libcstring \
	-I$(top_srcdir)/liberror \
	@LIBBFIO_CPPFLAGS@ \
	@MEMWATCH_CPPFLAGS@

pyexec_LTLIBRARIES = pylnk.la

pylnk_la_SOURCES = \
	pylnk.c pylnk.h \
	pylnk_datetime.c pylnk_datetime.h \
	pylnk_libbfio.h \
	pylnk_liblnk.h \
	pylnk_file.c pylnk_file.h \
	pylnk_file_object_io_handle.c pylnk_file_object_io_handle.h \
	pylnk_python.h

pylnk_la_LIBADD = \
	../libcstring/libcstring.la \
	../liberror/liberror.la \
	../liblnk/liblnk.la \
	@LIBBFIO_LIBADD@

pylnk_la_CPPFLAGS = $(PYTHON_CPPFLAGS)
pylnk_la_LDFLAGS  = -module -avoid-version $(PYTHON_LDFLAGS)

endif

MAINTAINERCLEANFILES = \
	Makefile.in

distclean: clean
	/bin/rm -f Makefile

