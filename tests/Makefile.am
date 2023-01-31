AUTOMAKE_OPTIONS = subdir-objects

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
	@LIBLNK_DLL_IMPORT@

if HAVE_PYTHON_TESTS
TESTS_PYLNK = \
	test_python_module.sh
endif

TESTS = \
	test_library.sh \
	test_tools.sh \
	test_lnkinfo.sh \
	$(TESTS_PYLNK)

check_SCRIPTS = \
	pylnk_test_file.py \
	pylnk_test_support.py \
	test_library.sh \
	test_lnkinfo.sh \
	test_manpage.sh \
	test_python_module.sh \
	test_runner.sh \
	test_tools.sh

EXTRA_DIST = \
	$(check_SCRIPTS)

check_PROGRAMS = \
	lnk_test_data_block \
	lnk_test_data_string \
	lnk_test_distributed_link_tracker_properties \
	lnk_test_error \
	lnk_test_file \
	lnk_test_file_header \
	lnk_test_io_handle \
	lnk_test_known_folder_location \
	lnk_test_link_target_identifier \
	lnk_test_location_information \
	lnk_test_notify \
	lnk_test_special_folder_location \
	lnk_test_support \
	lnk_test_tools_info_handle \
	lnk_test_tools_output \
	lnk_test_tools_signal

lnk_test_data_block_SOURCES = \
	lnk_test_data_block.c \
	lnk_test_functions.c lnk_test_functions.h \
	lnk_test_libbfio.h \
	lnk_test_libcerror.h \
	lnk_test_liblnk.h \
	lnk_test_macros.h \
	lnk_test_memory.c lnk_test_memory.h \
	lnk_test_unused.h

lnk_test_data_block_LDADD = \
	@LIBBFIO_LIBADD@ \
	@LIBCPATH_LIBADD@ \
	@LIBCFILE_LIBADD@ \
	@LIBUNA_LIBADD@ \
	@LIBCSPLIT_LIBADD@ \
	@LIBCNOTIFY_LIBADD@ \
	@LIBCLOCALE_LIBADD@ \
	@LIBCDATA_LIBADD@ \
	../liblnk/liblnk.la \
	@LIBCERROR_LIBADD@

lnk_test_data_string_SOURCES = \
	lnk_test_data_string.c \
	lnk_test_functions.c lnk_test_functions.h \
	lnk_test_libbfio.h \
	lnk_test_libcerror.h \
	lnk_test_liblnk.h \
	lnk_test_macros.h \
	lnk_test_memory.c lnk_test_memory.h \
	lnk_test_unused.h

lnk_test_data_string_LDADD = \
	@LIBBFIO_LIBADD@ \
	@LIBCPATH_LIBADD@ \
	@LIBCFILE_LIBADD@ \
	@LIBUNA_LIBADD@ \
	@LIBCSPLIT_LIBADD@ \
	@LIBCNOTIFY_LIBADD@ \
	@LIBCLOCALE_LIBADD@ \
	@LIBCDATA_LIBADD@ \
	../liblnk/liblnk.la \
	@LIBCERROR_LIBADD@

lnk_test_distributed_link_tracker_properties_SOURCES = \
	lnk_test_distributed_link_tracker_properties.c \
	lnk_test_libcerror.h \
	lnk_test_liblnk.h \
	lnk_test_macros.h \
	lnk_test_memory.c lnk_test_memory.h \
	lnk_test_unused.h

lnk_test_distributed_link_tracker_properties_LDADD = \
	../liblnk/liblnk.la \
	@LIBCERROR_LIBADD@

lnk_test_error_SOURCES = \
	lnk_test_error.c \
	lnk_test_liblnk.h \
	lnk_test_macros.h \
	lnk_test_unused.h

lnk_test_error_LDADD = \
	../liblnk/liblnk.la

lnk_test_file_SOURCES = \
	lnk_test_file.c \
	lnk_test_functions.c lnk_test_functions.h \
	lnk_test_getopt.c lnk_test_getopt.h \
	lnk_test_libbfio.h \
	lnk_test_libcerror.h \
	lnk_test_libclocale.h \
	lnk_test_libcnotify.h \
	lnk_test_liblnk.h \
	lnk_test_libuna.h \
	lnk_test_macros.h \
	lnk_test_memory.c lnk_test_memory.h

lnk_test_file_LDADD = \
	@LIBBFIO_LIBADD@ \
	@LIBCPATH_LIBADD@ \
	@LIBCFILE_LIBADD@ \
	@LIBUNA_LIBADD@ \
	@LIBCSPLIT_LIBADD@ \
	@LIBCNOTIFY_LIBADD@ \
	@LIBCLOCALE_LIBADD@ \
	@LIBCDATA_LIBADD@ \
	../liblnk/liblnk.la \
	@LIBCTHREADS_LIBADD@ \
	@LIBCERROR_LIBADD@ \
	@PTHREAD_LIBADD@

lnk_test_file_header_SOURCES = \
	lnk_test_file_header.c \
	lnk_test_functions.c lnk_test_functions.h \
	lnk_test_libbfio.h \
	lnk_test_libcerror.h \
	lnk_test_liblnk.h \
	lnk_test_macros.h \
	lnk_test_memory.c lnk_test_memory.h \
	lnk_test_unused.h

lnk_test_file_header_LDADD = \
	@LIBBFIO_LIBADD@ \
	@LIBCPATH_LIBADD@ \
	@LIBCFILE_LIBADD@ \
	@LIBUNA_LIBADD@ \
	@LIBCSPLIT_LIBADD@ \
	@LIBCNOTIFY_LIBADD@ \
	@LIBCLOCALE_LIBADD@ \
	@LIBCDATA_LIBADD@ \
	../liblnk/liblnk.la \
	@LIBCERROR_LIBADD@

lnk_test_io_handle_SOURCES = \
	lnk_test_io_handle.c \
	lnk_test_libcerror.h \
	lnk_test_liblnk.h \
	lnk_test_macros.h \
	lnk_test_memory.c lnk_test_memory.h \
	lnk_test_unused.h

lnk_test_io_handle_LDADD = \
	../liblnk/liblnk.la \
	@LIBCERROR_LIBADD@

lnk_test_known_folder_location_SOURCES = \
	lnk_test_known_folder_location.c \
	lnk_test_libcerror.h \
	lnk_test_liblnk.h \
	lnk_test_macros.h \
	lnk_test_memory.c lnk_test_memory.h \
	lnk_test_unused.h

lnk_test_known_folder_location_LDADD = \
	../liblnk/liblnk.la \
	@LIBCERROR_LIBADD@

lnk_test_link_target_identifier_SOURCES = \
	lnk_test_libcerror.h \
	lnk_test_liblnk.h \
	lnk_test_link_target_identifier.c \
	lnk_test_macros.h \
	lnk_test_memory.c lnk_test_memory.h \
	lnk_test_unused.h

lnk_test_link_target_identifier_LDADD = \
	../liblnk/liblnk.la \
	@LIBCERROR_LIBADD@

lnk_test_location_information_SOURCES = \
	lnk_test_libcerror.h \
	lnk_test_liblnk.h \
	lnk_test_location_information.c \
	lnk_test_macros.h \
	lnk_test_memory.c lnk_test_memory.h \
	lnk_test_unused.h

lnk_test_location_information_LDADD = \
	../liblnk/liblnk.la \
	@LIBCERROR_LIBADD@

lnk_test_notify_SOURCES = \
	lnk_test_libcerror.h \
	lnk_test_liblnk.h \
	lnk_test_macros.h \
	lnk_test_notify.c \
	lnk_test_unused.h

lnk_test_notify_LDADD = \
	../liblnk/liblnk.la \
	@LIBCERROR_LIBADD@

lnk_test_special_folder_location_SOURCES = \
	lnk_test_libcerror.h \
	lnk_test_liblnk.h \
	lnk_test_macros.h \
	lnk_test_memory.c lnk_test_memory.h \
	lnk_test_special_folder_location.c \
	lnk_test_unused.h

lnk_test_special_folder_location_LDADD = \
	../liblnk/liblnk.la \
	@LIBCERROR_LIBADD@

lnk_test_support_SOURCES = \
	lnk_test_functions.c lnk_test_functions.h \
	lnk_test_getopt.c lnk_test_getopt.h \
	lnk_test_libbfio.h \
	lnk_test_libcerror.h \
	lnk_test_libclocale.h \
	lnk_test_libcnotify.h \
	lnk_test_liblnk.h \
	lnk_test_libuna.h \
	lnk_test_macros.h \
	lnk_test_memory.c lnk_test_memory.h \
	lnk_test_support.c \
	lnk_test_unused.h

lnk_test_support_LDADD = \
	@LIBBFIO_LIBADD@ \
	@LIBCPATH_LIBADD@ \
	@LIBCFILE_LIBADD@ \
	@LIBUNA_LIBADD@ \
	@LIBCSPLIT_LIBADD@ \
	@LIBCNOTIFY_LIBADD@ \
	@LIBCLOCALE_LIBADD@ \
	@LIBCDATA_LIBADD@ \
	../liblnk/liblnk.la \
	@LIBCERROR_LIBADD@

lnk_test_tools_info_handle_SOURCES = \
	../lnktools/info_handle.c ../lnktools/info_handle.h \
	../lnktools/property_store.c ../lnktools/property_store.h \
	../lnktools/shell_items.c ../lnktools/shell_items.h \
	lnk_test_libcerror.h \
	lnk_test_macros.h \
	lnk_test_memory.c lnk_test_memory.h \
	lnk_test_tools_info_handle.c \
	lnk_test_unused.h

lnk_test_tools_info_handle_LDADD = \
	@LIBFWSI_LIBADD@ \
	@LIBFWPS_LIBADD@ \
	@LIBFGUID_LIBADD@ \
	@LIBFDATETIME_LIBADD@ \
	@LIBUNA_LIBADD@ \
	@LIBCLOCALE_LIBADD@ \
	@LIBCDATA_LIBADD@ \
	../liblnk/liblnk.la \
	@LIBCERROR_LIBADD@

lnk_test_tools_output_SOURCES = \
	../lnktools/lnktools_output.c ../lnktools/lnktools_output.h \
	lnk_test_libcerror.h \
	lnk_test_macros.h \
	lnk_test_tools_output.c \
	lnk_test_unused.h

lnk_test_tools_output_LDADD = \
	../liblnk/liblnk.la \
	@LIBCERROR_LIBADD@

lnk_test_tools_signal_SOURCES = \
	../lnktools/lnktools_signal.c ../lnktools/lnktools_signal.h \
	lnk_test_libcerror.h \
	lnk_test_macros.h \
	lnk_test_tools_signal.c \
	lnk_test_unused.h

lnk_test_tools_signal_LDADD = \
	../liblnk/liblnk.la \
	@LIBCERROR_LIBADD@

MAINTAINERCLEANFILES = \
	Makefile.in

distclean: clean
	/bin/rm -f Makefile

