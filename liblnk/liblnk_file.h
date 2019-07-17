/*
 * File functions
 *
 * Copyright (C) 2009-2019, Joachim Metz <joachim.metz@gmail.com>
 *
 * Refer to AUTHORS for acknowledgements.
 *
 * This software is free software: you can redistribute it and/or modify
 * it under the terms of the GNU Lesser General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * This software is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU Lesser General Public License
 * along with this software.  If not, see <http://www.gnu.org/licenses/>.
 */

#if !defined( _LIBLNK_FILE_H )
#define _LIBLNK_FILE_H

#include <common.h>
#include <types.h>

#include "liblnk_data_string.h"
#include "liblnk_distributed_link_tracker_properties.h"
#include "liblnk_extern.h"
#include "liblnk_file_header.h"
#include "liblnk_io_handle.h"
#include "liblnk_known_folder_location.h"
#include "liblnk_libbfio.h"
#include "liblnk_libcerror.h"
#include "liblnk_link_target_identifier.h"
#include "liblnk_location_information.h"
#include "liblnk_special_folder_location.h"
#include "liblnk_types.h"

#if defined( __cplusplus )
extern "C" {
#endif

typedef struct liblnk_internal_file liblnk_internal_file_t;

struct liblnk_internal_file
{
	/* The IO handle
	 */
	liblnk_io_handle_t *io_handle;

	/* The file IO handle
	 */
	libbfio_handle_t *file_io_handle;

	/* Value to indicate if the file IO handle was created inside the library
	 */
	uint8_t file_io_handle_created_in_library;

	/* Value to indicate if the file IO handle was opened inside the library
	 */
	uint8_t file_io_handle_opened_in_library;

	/* The file information
	 */
	liblnk_file_header_t *file_information;

	/* The link target identifier
	 * Consists of a shell item (identifiers) list
	 */
	liblnk_link_target_identifier_t *link_target_identifier;

	/* The location information
	 */
	liblnk_location_information_t *location_information;

	/* The description
	 */
	liblnk_data_string_t *description;

	/* The relative path
	 */
	liblnk_data_string_t *relative_path;

	/* The working directory
	 */
	liblnk_data_string_t *working_directory;

	/* The command line arguments
	 */
	liblnk_data_string_t *command_line_arguments;

	/* The icon location
	 */
	liblnk_data_string_t *icon_location;

	/* The environment variables location
	 */
	liblnk_data_string_t *environment_variables_location;

	/* The darwin application identifier
	 */
	liblnk_data_string_t *darwin_application_identifier;

	/* The special folder location
	 */
	liblnk_special_folder_location_t *special_folder_location;

	/* The known folder location
	 */
	liblnk_known_folder_location_t *known_folder_location;

	/* The distributed link tracker properties
	 */
	liblnk_distributed_link_tracker_properties_t *distributed_link_tracker_properties;
};

LIBLNK_EXTERN \
int liblnk_file_initialize(
     liblnk_file_t **file,
     libcerror_error_t **error );

LIBLNK_EXTERN \
int liblnk_file_free(
     liblnk_file_t **file,
     libcerror_error_t **error );

LIBLNK_EXTERN \
int liblnk_file_signal_abort(
     liblnk_file_t *file,
     libcerror_error_t **error );

LIBLNK_EXTERN \
int liblnk_file_open(
     liblnk_file_t *file,
     const char *filename,
     int access_flags,
     libcerror_error_t **error );

#if defined( HAVE_WIDE_CHARACTER_TYPE )

LIBLNK_EXTERN \
int liblnk_file_open_wide(
     liblnk_file_t *file,
     const wchar_t *filename,
     int access_flags,
     libcerror_error_t **error );

#endif /* defined( HAVE_WIDE_CHARACTER_TYPE ) */

LIBLNK_EXTERN \
int liblnk_file_open_file_io_handle(
     liblnk_file_t *file,
     libbfio_handle_t *file_io_handle,
     int access_flags,
     libcerror_error_t **error );

LIBLNK_EXTERN \
int liblnk_file_close(
     liblnk_file_t *file,
     libcerror_error_t **error );

int liblnk_file_open_read(
     liblnk_internal_file_t *internal_file,
     libbfio_handle_t *file_io_handle,
     libcerror_error_t **error );

LIBLNK_EXTERN \
int liblnk_file_get_ascii_codepage(
     liblnk_file_t *file,
     int *ascii_codepage,
     libcerror_error_t **error );

LIBLNK_EXTERN \
int liblnk_file_set_ascii_codepage(
     liblnk_file_t *file,
     int ascii_codepage,
     libcerror_error_t **error );

/* -------------------------------------------------------------------------
 * Link information functions
 * ------------------------------------------------------------------------- */

LIBLNK_EXTERN \
int liblnk_file_get_data_flags(
     liblnk_file_t *file,
     uint32_t *data_flags,
     libcerror_error_t **error );

LIBLNK_EXTERN \
int liblnk_file_link_refers_to_file(
     liblnk_file_t *file,
     libcerror_error_t **error );

LIBLNK_EXTERN \
int liblnk_file_get_file_creation_time(
     liblnk_file_t *file,
     uint64_t *filetime,
     libcerror_error_t **error );

LIBLNK_EXTERN \
int liblnk_file_get_file_modification_time(
     liblnk_file_t *file,
     uint64_t *filetime,
     libcerror_error_t **error );

LIBLNK_EXTERN \
int liblnk_file_get_file_access_time(
     liblnk_file_t *file,
     uint64_t *filetime,
     libcerror_error_t **error );

LIBLNK_EXTERN \
int liblnk_file_get_file_size(
     liblnk_file_t *file,
     uint32_t *file_size,
     libcerror_error_t **error );

LIBLNK_EXTERN \
int liblnk_file_get_icon_index(
     liblnk_file_t *file,
     uint32_t *icon_index,
     libcerror_error_t **error );

LIBLNK_EXTERN \
int liblnk_file_get_show_window_value(
     liblnk_file_t *file,
     uint32_t *show_window_value,
     libcerror_error_t **error );

LIBLNK_EXTERN \
int liblnk_file_get_hot_key_value(
     liblnk_file_t *file,
     uint16_t *hot_key_value,
     libcerror_error_t **error );

LIBLNK_EXTERN \
int liblnk_file_get_file_attribute_flags(
     liblnk_file_t *file,
     uint32_t *file_attribute_flags,
     libcerror_error_t **error );

LIBLNK_EXTERN \
int liblnk_file_get_drive_type(
     liblnk_file_t *file,
     uint32_t *drive_type,
     libcerror_error_t **error );

LIBLNK_EXTERN \
int liblnk_file_get_drive_serial_number(
     liblnk_file_t *file,
     uint32_t *drive_serial_number,
     libcerror_error_t **error );

/* TODO add raw string functions ? */

LIBLNK_EXTERN \
int liblnk_file_get_utf8_volume_label_size(
     liblnk_file_t *file,
     size_t *utf8_string_size,
     libcerror_error_t **error );

LIBLNK_EXTERN \
int liblnk_file_get_utf8_volume_label(
     liblnk_file_t *file,
     uint8_t *utf8_string,
     size_t utf8_string_size,
     libcerror_error_t **error );

LIBLNK_EXTERN \
int liblnk_file_get_utf16_volume_label_size(
     liblnk_file_t *file,
     size_t *utf16_string_size,
     libcerror_error_t **error );

LIBLNK_EXTERN \
int liblnk_file_get_utf16_volume_label(
     liblnk_file_t *file,
     uint16_t *utf16_string,
     size_t utf16_string_size,
     libcerror_error_t **error );

LIBLNK_EXTERN \
int liblnk_file_get_utf8_local_path_size(
     liblnk_file_t *file,
     size_t *utf8_string_size,
     libcerror_error_t **error );

LIBLNK_EXTERN \
int liblnk_file_get_utf8_local_path(
     liblnk_file_t *file,
     uint8_t *utf8_string,
     size_t utf8_string_size,
     libcerror_error_t **error );

LIBLNK_EXTERN \
int liblnk_file_get_utf16_local_path_size(
     liblnk_file_t *file,
     size_t *utf16_string_size,
     libcerror_error_t **error );

LIBLNK_EXTERN \
int liblnk_file_get_utf16_local_path(
     liblnk_file_t *file,
     uint16_t *utf16_string,
     size_t utf16_string_size,
     libcerror_error_t **error );

LIBLNK_EXTERN \
int liblnk_file_get_utf8_network_path_size(
     liblnk_file_t *file,
     size_t *utf8_string_size,
     libcerror_error_t **error );

LIBLNK_EXTERN \
int liblnk_file_get_utf8_network_path(
     liblnk_file_t *file,
     uint8_t *utf8_string,
     size_t utf8_string_size,
     libcerror_error_t **error );

LIBLNK_EXTERN \
int liblnk_file_get_utf16_network_path_size(
     liblnk_file_t *file,
     size_t *utf16_string_size,
     libcerror_error_t **error );

LIBLNK_EXTERN \
int liblnk_file_get_utf16_network_path(
     liblnk_file_t *file,
     uint16_t *utf16_string,
     size_t utf16_string_size,
     libcerror_error_t **error );

LIBLNK_EXTERN \
int liblnk_file_get_utf8_description_size(
     liblnk_file_t *file,
     size_t *utf8_string_size,
     libcerror_error_t **error );

LIBLNK_EXTERN \
int liblnk_file_get_utf8_description(
     liblnk_file_t *file,
     uint8_t *utf8_string,
     size_t utf8_string_size,
     libcerror_error_t **error );

LIBLNK_EXTERN \
int liblnk_file_get_utf16_description_size(
     liblnk_file_t *file,
     size_t *utf16_string_size,
     libcerror_error_t **error );

LIBLNK_EXTERN \
int liblnk_file_get_utf16_description(
     liblnk_file_t *file,
     uint16_t *utf16_string,
     size_t utf16_string_size,
     libcerror_error_t **error );

LIBLNK_EXTERN \
int liblnk_file_get_utf8_relative_path_size(
     liblnk_file_t *file,
     size_t *utf8_string_size,
     libcerror_error_t **error );

LIBLNK_EXTERN \
int liblnk_file_get_utf8_relative_path(
     liblnk_file_t *file,
     uint8_t *utf8_string,
     size_t utf8_string_size,
     libcerror_error_t **error );

LIBLNK_EXTERN \
int liblnk_file_get_utf16_relative_path_size(
     liblnk_file_t *file,
     size_t *utf16_string_size,
     libcerror_error_t **error );

LIBLNK_EXTERN \
int liblnk_file_get_utf16_relative_path(
     liblnk_file_t *file,
     uint16_t *utf16_string,
     size_t utf16_string_size,
     libcerror_error_t **error );

LIBLNK_EXTERN \
int liblnk_file_get_utf8_working_directory_size(
     liblnk_file_t *file,
     size_t *utf8_string_size,
     libcerror_error_t **error );

LIBLNK_EXTERN \
int liblnk_file_get_utf8_working_directory(
     liblnk_file_t *file,
     uint8_t *utf8_string,
     size_t utf8_string_size,
     libcerror_error_t **error );

LIBLNK_EXTERN \
int liblnk_file_get_utf16_working_directory_size(
     liblnk_file_t *file,
     size_t *utf16_string_size,
     libcerror_error_t **error );

LIBLNK_EXTERN \
int liblnk_file_get_utf16_working_directory(
     liblnk_file_t *file,
     uint16_t *utf16_string,
     size_t utf16_string_size,
     libcerror_error_t **error );

LIBLNK_EXTERN \
int liblnk_file_get_utf8_command_line_arguments_size(
     liblnk_file_t *file,
     size_t *utf8_string_size,
     libcerror_error_t **error );

LIBLNK_EXTERN \
int liblnk_file_get_utf8_command_line_arguments(
     liblnk_file_t *file,
     uint8_t *utf8_string,
     size_t utf8_string_size,
     libcerror_error_t **error );

LIBLNK_EXTERN \
int liblnk_file_get_utf16_command_line_arguments_size(
     liblnk_file_t *file,
     size_t *utf16_string_size,
     libcerror_error_t **error );

LIBLNK_EXTERN \
int liblnk_file_get_utf16_command_line_arguments(
     liblnk_file_t *file,
     uint16_t *utf16_string,
     size_t utf16_string_size,
     libcerror_error_t **error );

LIBLNK_EXTERN \
int liblnk_file_get_utf8_icon_location_size(
     liblnk_file_t *file,
     size_t *utf8_string_size,
     libcerror_error_t **error );

LIBLNK_EXTERN \
int liblnk_file_get_utf8_icon_location(
     liblnk_file_t *file,
     uint8_t *utf8_string,
     size_t utf8_string_size,
     libcerror_error_t **error );

LIBLNK_EXTERN \
int liblnk_file_get_utf16_icon_location_size(
     liblnk_file_t *file,
     size_t *utf16_string_size,
     libcerror_error_t **error );

LIBLNK_EXTERN \
int liblnk_file_get_utf16_icon_location(
     liblnk_file_t *file,
     uint16_t *utf16_string,
     size_t utf16_string_size,
     libcerror_error_t **error );

LIBLNK_EXTERN \
int liblnk_file_get_utf8_environment_variables_location_size(
     liblnk_file_t *file,
     size_t *utf8_string_size,
     libcerror_error_t **error );

LIBLNK_EXTERN \
int liblnk_file_get_utf8_environment_variables_location(
     liblnk_file_t *file,
     uint8_t *utf8_string,
     size_t utf8_string_size,
     libcerror_error_t **error );

LIBLNK_EXTERN \
int liblnk_file_get_utf16_environment_variables_location_size(
     liblnk_file_t *file,
     size_t *utf16_string_size,
     libcerror_error_t **error );

LIBLNK_EXTERN \
int liblnk_file_get_utf16_environment_variables_location(
     liblnk_file_t *file,
     uint16_t *utf16_string,
     size_t utf16_string_size,
     libcerror_error_t **error );

LIBLNK_EXTERN \
int liblnk_file_get_link_target_identifier_data_size(
     liblnk_file_t *file,
     size_t *data_size,
     libcerror_error_t **error );

LIBLNK_EXTERN \
int liblnk_file_copy_link_target_identifier_data(
     liblnk_file_t *file,
     uint8_t *data,
     size_t data_size,
     libcerror_error_t **error );

/* -------------------------------------------------------------------------
 * Distributed link tracking data functions
 * ------------------------------------------------------------------------- */

LIBLNK_EXTERN \
int liblnk_file_has_distributed_link_tracking_data(
     liblnk_file_t *file,
     libcerror_error_t **error );

LIBLNK_EXTERN \
int liblnk_file_get_utf8_machine_identifier_size(
     liblnk_file_t *file,
     size_t *utf8_string_size,
     libcerror_error_t **error );

LIBLNK_EXTERN \
int liblnk_file_get_utf8_machine_identifier(
     liblnk_file_t *file,
     uint8_t *utf8_string,
     size_t utf8_string_size,
     libcerror_error_t **error );

LIBLNK_EXTERN \
int liblnk_file_get_utf16_machine_identifier_size(
     liblnk_file_t *file,
     size_t *utf16_string_size,
     libcerror_error_t **error );

LIBLNK_EXTERN \
int liblnk_file_get_utf16_machine_identifier(
     liblnk_file_t *file,
     uint16_t *utf16_string,
     size_t utf16_string_size,
     libcerror_error_t **error );

LIBLNK_EXTERN \
int liblnk_file_get_droid_volume_identifier(
     liblnk_file_t *file,
     uint8_t *guid_data,
     size_t guid_data_size,
     libcerror_error_t **error );

LIBLNK_EXTERN \
int liblnk_file_get_droid_file_identifier(
     liblnk_file_t *file,
     uint8_t *guid_data,
     size_t guid_data_size,
     libcerror_error_t **error );

LIBLNK_EXTERN \
int liblnk_file_get_birth_droid_volume_identifier(
     liblnk_file_t *file,
     uint8_t *guid_data,
     size_t guid_data_size,
     libcerror_error_t **error );

LIBLNK_EXTERN \
int liblnk_file_get_birth_droid_file_identifier(
     liblnk_file_t *file,
     uint8_t *guid_data,
     size_t guid_data_size,
     libcerror_error_t **error );

#if defined( __cplusplus )
}
#endif

#endif /* !defined( _LIBLNK_FILE_H ) */

