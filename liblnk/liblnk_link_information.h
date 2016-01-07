/*
 * Link information functions
 *
 * Copyright (C) 2009-2016, Joachim Metz <joachim.metz@gmail.com>
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

#if !defined( _LIBLNK_LINK_INFORMATION_H )
#define _LIBLNK_LINK_INFORMATION_H

#include <common.h>
#include <types.h>

#include "liblnk_extern.h"
#include "liblnk_libcerror.h"

#if defined( __cplusplus )
extern "C" {
#endif

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
     uint64_t *creation_time,
     libcerror_error_t **error );

LIBLNK_EXTERN \
int liblnk_file_get_file_modification_time(
     liblnk_file_t *file,
     uint64_t *modification_time,
     libcerror_error_t **error );

LIBLNK_EXTERN \
int liblnk_file_get_file_access_time(
     liblnk_file_t *file,
     uint64_t *access_time,
     libcerror_error_t **error );

LIBLNK_EXTERN \
int liblnk_file_get_file_size(
     liblnk_file_t *file,
     uint32_t *file_size,
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
int liblnk_file_get_link_target_identifier_data(
     liblnk_file_t *file,
     uint8_t **data,
     size_t *data_size,
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

#if defined( __cplusplus )
}
#endif

#endif

