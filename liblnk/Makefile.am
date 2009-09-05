AM_CPPFLAGS = -I$(top_srcdir)/include -I$(top_srcdir)/common -I$(top_srcdir)/liberror -I$(top_srcdir)/libnotify @LIBUNA_CPPFLAGS@ @LIBBFIO_CPPFLAGS@ @MEMWATCH_CPPFLAGS@

lib_LTLIBRARIES = liblnk.la

liblnk_la_SOURCES = \
	liblnk.c \
	liblnk_debug.c liblnk_debug.h \
	liblnk_definitions.h \
	liblnk_error.c liblnk_error.h \
	liblnk_extern.h \
	liblnk_file.c liblnk_file.h \
	liblnk_filetime.c liblnk_filetime.h \
	liblnk_guid.c liblnk_guid.h \
	liblnk_io_handle.c liblnk_io_handle.h \
	liblnk_libbfio.h \
	liblnk_libuna.h \
	liblnk_notify.c liblnk_notify.h \
	liblnk_string.h \
	liblnk_support.c liblnk_support.h \
	lnk_file_header.h

liblnk_la_LIBADD  = ../liberror/liberror.la ../libnotify/libnotify.la @LIBUNA_LIBADD@ @LIBBFIO_LIBADD@
liblnk_la_LDFLAGS = -no-undefined -version-info 1:0:0

EXTRA_DIST = \
	liblnk_definitions.h.in

distclean: clean
	/bin/rm -f Makefile

splint:
	@echo "Running splint on liblnk ..." 
	-splint -preproc -redef $(DEFS) $(DEFAULT_INCLUDES) $(INCLUDES) $(AM_CPPFLAGS) $(liblnk_la_SOURCES) 

