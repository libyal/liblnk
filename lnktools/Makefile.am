AM_CPPFLAGS = \
	-I$(top_srcdir)/include \
	-I$(top_srcdir)/common \
	@LIBCSTRING_CPPFLAGS@ \
	@LIBCERROR_CPPFLAGS@ \
	@LIBUNA_CPPFLAGS@ \
	@LIBCFILE_CPPFLAGS@ \
	@LIBCPATH_CPPFLAGS@ \
	@LIBBFIO_CPPFLAGS@ \
	@LIBFDATETIME_CPPFLAGS@ \
	@LIBFGUID_CPPFLAGS@ \
	@LIBFWSI_CPPFLAGS@ \
	@LIBCSYSTEM_CPPFLAGS@ \
	@MEMWATCH_CPPFLAGS@ \
	@LIBLNK_DLL_IMPORT@

AM_LDFLAGS = @STATIC_LDFLAGS@

bin_PROGRAMS = \
	lnkinfo

lnkinfo_SOURCES = \
	info_handle.c info_handle.h \
	lnkinfo.c \
	lnkinput.c lnkinput.h \
	lnkoutput.c lnkoutput.h \
	lnktools_libcerror.h \
	lnktools_libcstring.h \
	lnktools_libfdatetime.h \
	lnktools_libfguid.h \
	lnktools_libfwsi.h \
	lnktools_liblnk.h

lnkinfo_LDADD  = \
	@LIBCERROR_LIBADD@ \
	../liblnk/liblnk.la \
	@LIBFDATETIME_LIBADD@ \
	@LIBFGUID_LIBADD@ \
	@LIBFWSI_LIBADD@ \
	@LIBCSYSTEM_LIBADD@ \
	@LIBINTL@ \
	@MEMWATCH_LIBADD@

MAINTAINERCLEANFILES = \
	Makefile.in

distclean: clean
	/bin/rm -f Makefile

splint:
	@echo "Running splint on lnkinfo ..." 
	-splint -preproc -redef $(DEFS) $(DEFAULT_INCLUDES) $(INCLUDES) $(AM_CPPFLAGS) $(lnkinfo_SOURCES) 

