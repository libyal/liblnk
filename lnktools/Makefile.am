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
	@LIBFDATETIME_CPPFLAGS@ \
	@LIBFGUID_CPPFLAGS@ \
	@LIBFOLE_CPPFLAGS@ \
	@LIBFWPS_CPPFLAGS@ \
	@LIBFWSI_CPPFLAGS@ \
	@LIBCSYSTEM_CPPFLAGS@ \
	@LIBLNK_DLL_IMPORT@

AM_LDFLAGS = @STATIC_LDFLAGS@

bin_PROGRAMS = \
	lnkinfo

lnkinfo_SOURCES = \
	info_handle.c info_handle.h \
	lnkinfo.c \
	lnkoutput.c lnkoutput.h \
	lnktools_libbfio.h \
	lnktools_libcerror.h \
	lnktools_libclocale.h \
	lnktools_libcnotify.h \
	lnktools_libcstring.h \
	lnktools_libcsystem.h \
	lnktools_libfdatetime.h \
	lnktools_libfguid.h \
	lnktools_libfwsi.h \
	lnktools_liblnk.h \
	lnktools_libuna.h \
	shell_items.c shell_items.h

lnkinfo_LDADD = \
	@LIBCSYSTEM_LIBADD@ \
	@LIBFWSI_LIBADD@ \
	@LIBFWPS_LIBADD@ \
	@LIBFOLE_LIBADD@ \
	@LIBFGUID_LIBADD@ \
	@LIBFDATETIME_LIBADD@ \
	@LIBUNA_LIBADD@ \
	@LIBCDATA_LIBADD@ \
	../liblnk/liblnk.la \
	@LIBCNOTIFY_LIBADD@ \
	@LIBCLOCALE_LIBADD@ \
	@LIBCERROR_LIBADD@ \
	@LIBCSTRING_LIBADD@ \
	@LIBINTL@

MAINTAINERCLEANFILES = \
	Makefile.in

distclean: clean
	/bin/rm -f Makefile

splint:
	@echo "Running splint on lnkinfo ..."
	-splint -preproc -redef $(DEFS) $(DEFAULT_INCLUDES) $(INCLUDES) $(AM_CPPFLAGS) $(lnkinfo_SOURCES)

