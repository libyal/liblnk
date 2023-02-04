AM_CPPFLAGS = \
	-I$(top_srcdir)/include \
	-I$(top_srcdir)/common \
	@LIBCERROR_CPPFLAGS@ \
	@LIBCTHREADS_CPPFLAGS@ \
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
	@PTHREAD_CPPFLAGS@ \
	@LIBLNK_DLL_EXPORT@

lib_LTLIBRARIES = liblnk.la

liblnk_la_SOURCES = \
	liblnk.c \
	liblnk_codepage.h \
	liblnk_data_block.c liblnk_data_block.h \
	liblnk_data_string.c liblnk_data_string.h \
	liblnk_debug.c liblnk_debug.h \
	liblnk_definitions.h \
	liblnk_distributed_link_tracker_properties.c liblnk_distributed_link_tracker_properties.h \
	liblnk_distributed_link_tracking_data_block.c liblnk_distributed_link_tracking_data_block.h \
	liblnk_error.c liblnk_error.h \
	liblnk_extern.h \
	liblnk_file.c liblnk_file.h \
	liblnk_file_header.c liblnk_file_header.h \
	liblnk_io_handle.c liblnk_io_handle.h \
	liblnk_known_folder_location.c liblnk_known_folder_location.h \
	liblnk_libbfio.h \
	liblnk_libcdata.h \
	liblnk_libcerror.h \
	liblnk_libclocale.h \
	liblnk_libcnotify.h \
	liblnk_libfdatetime.h \
	liblnk_libfguid.h \
	liblnk_libfwps.h \
	liblnk_libfwsi.h \
	liblnk_libuna.h \
	liblnk_link_target_identifier.c liblnk_link_target_identifier.h \
	liblnk_location_information.c liblnk_location_information.h \
	liblnk_notify.c liblnk_notify.h \
	liblnk_special_folder_location.c liblnk_special_folder_location.h \
	liblnk_strings_data_block.c liblnk_strings_data_block.h \
	liblnk_support.c liblnk_support.h \
	liblnk_types.h \
	liblnk_unused.h \
	lnk_data_blocks.h \
	lnk_file_header.h \
	lnk_location_information.h \
	lnk_network_share_information.h \
	lnk_volume_information.h

liblnk_la_LIBADD = \
	@LIBCERROR_LIBADD@ \
	@LIBCTHREADS_LIBADD@ \
	@LIBCDATA_LIBADD@ \
	@LIBCLOCALE_LIBADD@ \
	@LIBCNOTIFY_LIBADD@ \
	@LIBCSPLIT_LIBADD@ \
	@LIBUNA_LIBADD@ \
	@LIBCFILE_LIBADD@ \
	@LIBCPATH_LIBADD@ \
	@LIBBFIO_LIBADD@ \
	@LIBFDATETIME_LIBADD@ \
	@LIBFGUID_LIBADD@ \
	@LIBFOLE_LIBADD@ \
	@LIBFWPS_LIBADD@ \
	@LIBFWSI_LIBADD@ \
	@PTHREAD_LIBADD@

liblnk_la_LDFLAGS = -no-undefined -version-info 1:0:0

EXTRA_DIST = \
	liblnk_definitions.h.in \
	liblnk.rc \
	liblnk.rc.in

MAINTAINERCLEANFILES = \
	Makefile.in

distclean: clean
	/bin/rm -f liblnk_definitions.h
	/bin/rm -f liblnk.rc
	/bin/rm -f Makefile

splint:
	@echo "Running splint on liblnk ..."
	-splint -preproc -redef $(DEFS) $(DEFAULT_INCLUDES) $(INCLUDES) $(AM_CPPFLAGS) $(liblnk_la_SOURCES)

