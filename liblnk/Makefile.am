AM_CPPFLAGS = \
	-I$(top_srcdir)/include \
	-I$(top_srcdir)/common \
	-I$(top_srcdir)/libcstring \
	-I$(top_srcdir)/liberror \
	-I$(top_srcdir)/libnotify \
	@LIBUNA_CPPFLAGS@ \
	@LIBBFIO_CPPFLAGS@ \
	@LIBFDATETIME_CPPFLAGS@ \
	@LIBFGUID_CPPFLAGS@ \
	@LIBFWSI_CPPFLAGS@ \
	@MEMWATCH_CPPFLAGS@

lib_LTLIBRARIES = liblnk.la

liblnk_la_SOURCES = \
	liblnk.c \
	liblnk_codepage.h \
	liblnk_data_block.c liblnk_data_block.h \
	liblnk_data_block_strings.c liblnk_data_block_strings.h \
	liblnk_data_string.c liblnk_data_string.h \
	liblnk_debug.c liblnk_debug.h \
	liblnk_definitions.h \
	liblnk_distributed_link_tracker.c liblnk_distributed_link_tracker.h \
	liblnk_distributed_link_tracker_properties.c liblnk_distributed_link_tracker_properties.h \
	liblnk_error.c liblnk_error.h \
	liblnk_extern.h \
	liblnk_file.c liblnk_file.h \
	liblnk_file_information.c liblnk_file_information.h \
	liblnk_io_handle.c liblnk_io_handle.h \
	liblnk_known_folder_location.c liblnk_known_folder_location.h \
	liblnk_libbfio.h \
	liblnk_libfdatetime.h \
	liblnk_libfguid.h \
	liblnk_libfwsi.h \
	liblnk_libuna.h \
	liblnk_link_information.c liblnk_link_information.h \
	liblnk_location_information.c liblnk_location_information.h \
	liblnk_notify.c liblnk_notify.h \
	liblnk_shell_item_identifiers_list.c liblnk_shell_item_identifiers_list.h \
	liblnk_special_folder_location.c liblnk_special_folder_location.h \
	liblnk_support.c liblnk_support.h \
	liblnk_types.h \
	liblnk_unused.h \
	lnk_data_blocks.h \
	lnk_file_header.h \
	lnk_location_information.h

liblnk_la_LIBADD = \
	../libcstring/libcstring.la \
	../liberror/liberror.la \
	../libnotify/libnotify.la \
	@LIBUNA_LIBADD@ \
	@LIBBFIO_LIBADD@ \
	@LIBFDATETIME_LIBADD@ \
	@LIBFGUID_LIBADD@ \
	@LIBFWSI_LIBADD@

liblnk_la_LDFLAGS = -no-undefined -version-info 1:0:0

EXTRA_DIST = \
	liblnk_definitions.h.in

MAINTAINERCLEANFILES = \
	Makefile.in

distclean: clean
	/bin/rm -f Makefile

splint:
	@echo "Running splint on liblnk ..." 
	-splint -preproc -redef $(DEFS) $(DEFAULT_INCLUDES) $(INCLUDES) $(AM_CPPFLAGS) $(liblnk_la_SOURCES) 

