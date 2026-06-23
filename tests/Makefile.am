AUTOMAKE_OPTIONS = subdir-objects

AM_CPPFLAGS = \
	-I../include -I$(top_srcdir)/include \
	-I../common -I$(top_srcdir)/common \
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

BUILT_SOURCES = package.m4

check_AUTOTESTS = \
	test_library \
	test_manpages \
	test_tools

if HAVE_PYTHON_TESTS
check_AUTOTESTS += test_python_module
endif

check_SCRIPTS = \
	pylnk_test_file.py \
	pylnk_test_support.py

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
	lnk_test_tools_path_string \
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
	../lnktools/path_string.c ../lnktools/path_string.h \
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
	@LIBFOLE_LIBADD@ \
	@LIBFGUID_LIBADD@ \
	@LIBFDATETIME_LIBADD@ \
	@LIBUNA_LIBADD@ \
	@LIBCNOTIFY_LIBADD@ \
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
	@LIBCERROR_LIBADD@ \
	@LIBINTL@

lnk_test_tools_path_string_SOURCES = \
	../lnktools/path_string.c ../lnktools/path_string.h \
	lnk_test_libcerror.h \
	lnk_test_libcpath.h \
	lnk_test_macros.h \
	lnk_test_tools_path_string.c \
	lnk_test_unused.h

lnk_test_tools_path_string_LDADD = \
	@LIBUNA_LIBADD@ \
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

AUTOM4TE = autom4te
AUTOTEST = $(AUTOM4TE) --language=autotest

SUFFIXES = .at

.at:
	$(AM_V_GEN)rm -f $@ $@.tmp; \
	$(AUTOTEST) -I '$(srcdir)' -o $@.tmp $< && \
	mv $@.tmp $@

atconfig: $(top_builddir)/config.status
	cd $(top_builddir) && $(SHELL) ./config.status tests/$@

check-build: $(check_PROGRAMS)

check-local: $(check_AUTOTESTS)
	@fail=0; \
	for test_suite in $(check_AUTOTESTS); do \
		$(AM_TESTS_ENVIRONMENT) $(SHELL) "./$$test_suite" $(TESTSUITEFLAGS) || fail=1; \
		echo ""; \
	done; \
	exit $$fail

clean-local:
	for test_suite in $(check_AUTOTESTS); do \
		test ! -f "$$test_suite" || $(SHELL) "./$$test_suite" --clean; \
	done

package.m4: $(top_srcdir)/configure.ac
	$(AM_V_GEN):; \
	{ \
	  echo 'm4_define([AT_PACKAGE_NAME], [$(PACKAGE_NAME)])' ; \
	  echo 'm4_define([AT_PACKAGE_TARNAME], [$(PACKAGE_TARNAME)])' ; \
	  echo 'm4_define([AT_PACKAGE_VERSION], [$(PACKAGE_VERSION)])' ; \
	  echo 'm4_define([AT_PACKAGE_STRING], [$(PACKAGE_STRING)])' ; \
	  echo 'm4_define([AT_PACKAGE_BUGREPORT], [$(PACKAGE_BUGREPORT)])' ; \
	} > $@

test_inputs_liblnk.at: generate_test_inputs.sh
	$(SHELL) $(srcdir)/generate_test_inputs.sh $(PACKAGE_NAME) liblnk

test_inputs_pylnk.at: generate_test_inputs.sh
	$(SHELL) $(srcdir)/generate_test_inputs.sh $(PACKAGE_NAME) pylnk

test_inputs_lnkinfo.at: generate_test_inputs.sh
	$(SHELL) $(srcdir)/generate_test_inputs.sh $(PACKAGE_NAME) lnkinfo

test_library: \
	package.m4 \
	test_inputs_liblnk.at \
	test_library.at \
	test_macros.at

test_manpages: \
	package.m4 \
	test_manpages.at

test_python_module: \
	package.m4 \
	test_inputs_pylnk.at \
	test_macros.at \
	test_python_module.at

test_tools: \
	package.m4 \
	test_inputs_lnkinfo.at \
	test_macros.at \
	test_tools.at

EXTRA_DIST = \
	$(check_AUTOTESTS:=.at) \
	$(check_SCRIPTS) \
	generate_test_inputs.sh \
	package.m4 \
	test_macros.at

CLEANFILES = \
	$(check_AUTOTESTS) \
	*.exe \
	*.tmp \
	notify_stream.log \
	test_inputs_*.at

DISTCLEANFILES = \
	*.log \
	atconfig \
	Makefile \
	Makefile.in

