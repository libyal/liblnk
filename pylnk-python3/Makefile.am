# Note that we cannot use: AUTOMAKE_OPTIONS = subdir-objects
# subdir-objects will compile the source files to a single version of Python.
# Since subdir-objects is being deprecated we copy the source files instead.
am__installdirs = "$(DESTDIR)$(pyexecdir3)"
pyexecdir = $(pyexecdir3)

if HAVE_PYTHON3
AM_CFLAGS = \
	-I$(top_srcdir)/include \
	-I$(top_srcdir)/common \
	@LIBCERROR_CPPFLAGS@ \
	@LIBCDATA_CPPFLAGS@ \
	@LIBCLOCALE_CPPFLAGS@ \
	@LIBCSPLIT_CPPFLAGS@ \
	@LIBUNA_CPPFLAGS@ \
	@LIBCFILE_CPPFLAGS@ \
	@LIBCPATH_CPPFLAGS@ \
	@LIBBFIO_CPPFLAGS@ \
	@LIBFGUID_CPPFLAGS@ \
	@LIBLNK_DLL_IMPORT@

am_pylnk_la_rpath = -rpath $(pyexecdir3)

BUILT_SOURCES = \
	pylnk.c pylnk.h \
	pylnk_codepage.c pylnk_codepage.h \
	pylnk_data_flags.c pylnk_data_flags.h \
	pylnk_datetime.c pylnk_datetime.h \
	pylnk_drive_types.c pylnk_drive_types.h \
	pylnk_error.c pylnk_error.h \
	pylnk_file.c pylnk_file.h \
	pylnk_file_attribute_flags.c pylnk_file_attribute_flags.h \
	pylnk_file_object_io_handle.c pylnk_file_object_io_handle.h \
	pylnk_guid.c pylnk_guid.h \
	pylnk_integer.c pylnk_integer.h \
	pylnk_libbfio.h \
	pylnk_libcerror.h \
	pylnk_libclocale.h \
	pylnk_libfguid.h \
	pylnk_liblnk.h \
	pylnk_python.h \
	pylnk_unused.h

pyexec_LTLIBRARIES = pylnk.la

nodist_pylnk_la_SOURCES = $(BUILT_SOURCES)

pylnk_la_LIBADD = \
	@LIBCERROR_LIBADD@ \
	../liblnk/liblnk.la \
	@LIBCDATA_LIBADD@ \
	@LIBCLOCALE_LIBADD@ \
	@LIBCSPLIT_LIBADD@ \
	@LIBUNA_LIBADD@ \
	@LIBCFILE_LIBADD@ \
	@LIBCPATH_LIBADD@ \
	@LIBBFIO_LIBADD@ \
	@LIBFGUID_LIBADD@

pylnk_la_CPPFLAGS = $(PYTHON3_CPPFLAGS)
pylnk_la_LDFLAGS  = -module -avoid-version $(PYTHON3_LDFLAGS)

$(BUILT_SOURCES):
	/bin/cp -f $(top_srcdir)/pylnk/$@ $@

endif

MAINTAINERCLEANFILES = \
	Makefile.in

clean-local:
	/bin/rm -f pylnk*.[ch]

distclean: clean
	/bin/rm -f Makefile

