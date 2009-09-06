AM_CPPFLAGS = -I$(top_srcdir)/include -I$(top_srcdir)/common -I$(top_srcdir)/liberror -I$(top_srcdir)/libsystem @LIBUNA_CPPFLAGS@ @LIBBFIO_CPPFLAGS@ @LIBFDATETIME_CPPFLAGS@ @MEMWATCH_CPPFLAGS@ @LIBLNK_DLL_IMPORT@
AM_LDFLAGS  = @STATIC_LDFLAGS@

bin_PROGRAMS = lnkinfo

lnkinfo_SOURCES = \
	filetime.c filetime.h \
	guid.c guid.h \
	lnkinfo.c \
	lnkinput.c lnkinput.h \
	lnkoutput.c lnkoutput.h

lnkinfo_LDADD   = ../liberror/liberror.la ../liblnk/liblnk.la ../libsystem/libsystem.la @MEMWATCH_LIBADD@

distclean: clean
	/bin/rm -f Makefile

splint:
	@echo "Running splint on lnkinfo ..." 
	-splint -preproc -redef $(DEFS) $(DEFAULT_INCLUDES) $(INCLUDES) $(AM_CPPFLAGS) $(lnkinfo_SOURCES) 

