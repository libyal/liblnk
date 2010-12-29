AM_CPPFLAGS = \
	-I$(top_srcdir)/include \
	-I$(top_srcdir)/common \
	-I$(top_srcdir)/libcstring \
	-I$(top_srcdir)/liberror \
	-I$(top_srcdir)/libsystem \
	@LIBUNA_CPPFLAGS@ \
	@LIBBFIO_CPPFLAGS@ \
	@LIBFDATETIME_CPPFLAGS@ \
	@LIBFGUID_CPPFLAGS@ \
	@LIBFWSI_CPPFLAGS@ \
	@MEMWATCH_CPPFLAGS@ \
	@LIBLNK_DLL_IMPORT@

AM_LDFLAGS = @STATIC_LDFLAGS@

bin_PROGRAMS = \
	lnkinfo

lnkinfo_SOURCES = \
	lnkinfo.c \
	lnkinput.c lnkinput.h \
	lnkoutput.c lnkoutput.h

lnkinfo_LDADD  = \
	../liberror/liberror.la \
	../liblnk/liblnk.la \
	../libsystem/libsystem.la \
	@LIBFDATETIME_LIBADD@ \
	@MEMWATCH_LIBADD@

MAINTAINERCLEANFILES = \
	Makefile.in

distclean: clean
	/bin/rm -f Makefile

splint:
	@echo "Running splint on lnkinfo ..." 
	-splint -preproc -redef $(DEFS) $(DEFAULT_INCLUDES) $(INCLUDES) $(AM_CPPFLAGS) $(lnkinfo_SOURCES) 

