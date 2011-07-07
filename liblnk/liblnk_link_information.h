/*
 * Link information functions
 *
 * Copyright (c) 2009-2011, Joachim Metz <jbmetz@users.sourceforge.net>
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

#include <liberror.h>

#include "liblnk_extern.h"

#if defined( __cplusplus )
extern "C" {
#endif

LIBLNK_EXTERN \
int liblnk_file_get_data_flags(
     liblnk_file_t *file,
     uint32_t *data_flags,
     liberror_error_t **error );

LIBLNK_EXTERN \
int liblnk_file_link_refers_to_file(
     liblnk_file_t *file,
     liberror_error_t **error );

LIBLNK_EXTERN \
int liblnk_file_get_file_attribute_flags(
     liblnk_file_t *file,
     uint32_t *file_attribute_flags,
     liberror_error_t **error );

LIBLNK_EXTERN \
int liblnk_file_get_file_creation_time(
     liblnk_file_t *file,
     uint64_t *creation_time,
     liberror_error_t **error );

LIBLNK_EXTERN \
int liblnk_file_get_file_modification_time(
     liblnk_file_t *file,
     uint64_t *modification_time,
     liberror_error_t **error );

LIBLNK_EXTERN \
int liblnk_file_get_file_access_time(
     liblnk_file_t *file,
     uint64_t *access_time,
     liberror_error_t **error );

LIBLNK_EXTERN \
int liblnk_file_get_file_size(
     liblnk_file_t *file,
     uint32_t *file_size,
     liberror_error_t **error );

/* TODO add raw string functions ? */

LIBLNK_EXTERN \
int liblnk_file_get_utf8_local_path_size(
     liblnk_file_t *file,
     size_t *utf8_string_size,
     liberror_error_t **error );

LIBLNK_EXTERN \
int liblnk_file_get_utf8_local_path(
     liblnk_file_t *file,
     uint8_t *utf8_string,
     size_t utf8_string_size,
     liberror_error_t **error );

LIBLNK_EXTERN \
int liblnk_file_get_utf16_local_path_size(
     liblnk_file_t *file,
     size_t *utf16_string_size,
     liberror_error_t **error );

LIBLNK_EXTERN \
int liblnk_file_get_utf16_local_path(
     liblnk_file_t *file,
     uint16_t *utf16_string,
     size_t utf16_string_size,
     liberror_error_t **error );

LIBLNK_EXTERN \
int liblnk_file_get_utf8_network_path_size(
     liblnk_file_t *file,
     size_t *utf8_string_size,
     liberror_error_t **error );

LIBLNK_EXTERN \
int liblnk_file_get_utf8_network_path(
     liblnk_file_t *file,
     uint8_t *utf8_string,
     size_t utf8_string_size,
     liberror_error_t **error );

LIBLNK_EXTERN \
int liblnk_file_get_utf16_network_path_size(
     liblnk_file_t *file,
     size_t *utf16_string_size,
     liberror_error_t **error );

LIBLNK_EXTERN \
int liblnk_file_get_utf16_network_path(
     liblnk_file_t *file,
     uint16_t *utf16_string,
     size_t utf16_string_size,
     liberror_error_t **error );

LIBLNK_EXTERN \
int liblnk_file_get_utf8_description_size(
     liblnk_file_t *file,
     size_t *utf8_string_size,
     liberror_error_t **error );

LIBLNK_EXTERN \
int liblnk_file_get_utf8_description(
     liblnk_file_t *file,
     uint8_t *utf8_string,
     size_t utf8_string_size,
     liberror_error_t **error );

LIBLNK_EXTERN \
int liblnk_file_get_utf16_description_size(
     liblnk_file_t *file,
     size_t *utf16_string_size,
     liberror_error_t **error );

LIBLNK_EXTERN \
int liblnk_file_get_utf16_description(
     liblnk_file_t *file,
     uint16_t *utf16_string,
     size_t utf16_string_size,
     liberror_error_t **error );

LIBLNK_EXTERN \
int liblnk_file_get_utf8_relative_path_size(
     liblnk_file_t *file,
     size_t *utf8_string_size,
     liberror_error_t **error );

LIBLNK_EXTERN \
int liblnk_file_get_utf8_relative_path(
     liblnk_file_t *file,
     uint8_t *utf8_string,
     size_t utf8_string_size,
     liberror_error_t **error );

LIBLNK_EXTERN \
int liblnk_file_get_utf16_relative_path_size(
     liblnk_file_t *file,
     size_t *utf16_string_size,
     liberror_error_t **error );

LIBLNK_EXTERN \
int liblnk_file_get_utf16_relative_path(
     liblnk_file_t *file,
     uint16_t *utf16_string,
     size_t utf16_string_size,
     liberror_error_t **error );

LIBLNK_EXTERN \
int liblnk_file_get_utf8_working_directory_size(
     liblnk_file_t *file,
     size_t *utf8_string_size,
     liberror_error_t **error );

LIBLNK_EXTERN \
int liblnk_file_get_utf8_working_directory(
     liblnk_file_t *file,
     uint8_t *utf8_string,
     size_t utf8_string_size,
     liberror_error_t **error );

LIBLNK_EXTERN \
int liblnk_file_get_utf16_working_directory_size(
     liblnk_file_t *file,
     size_t *utf16_string_size,
     liberror_error_t **error );

LIBLNK_EXTERN \
int liblnk_file_get_utf16_working_directory(
     liblnk_file_t *file,
     uint16_t *utf16_string,
     size_t utf16_string_size,
     liberror_error_t **error );

LIBLNK_EXTERN \
int liblnk_file_get_utf8_command_line_arguments_size(
     liblnk_file_t *file,
     size_t *utf8_string_size,
     liberror_error_t **error );

LIBLNK_EXTERN \
int liblnk_file_get_utf8_command_line_arguments(
     liblnk_file_t *file,
     uint8_t *utf8_string,
     size_t utf8_string_size,
     liberror_error_t **error );

LIBLNK_EXTERN \
int liblnk_file_get_utf16_command_line_arguments_size(
     liblnk_file_t *file,
     size_t *utf16_string_size,
     liberror_error_t **error );

LIBLNK_EXTERN \
int liblnk_file_get_utf16_command_line_arguments(
     liblnk_file_t *file,
     uint16_t *utf16_string,
     size_t utf16_string_size,
     liberror_error_t **error );

LIBLNK_EXTERN \
int liblnk_file_get_utf8_icon_location_size(
     liblnk_file_t *file,
     size_t *utf8_string_size,
     liberror_error_t **error );

LIBLNK_EXTERN \
int liblnk_file_get_utf8_icon_location(
     liblnk_file_t *file,
     uint8_t *utf8_string,
     size_t utf8_string_size,
     liberror_error_t **error );

LIBLNK_EXTERN \
int liblnk_file_get_utf16_icon_location_size(
     liblnk_file_t *file,
     size_t *utf16_string_size,
     liberror_error_t **error );

LIBLNK_EXTERN \
int liblnk_file_get_utf16_icon_location(
     liblnk_file_t *file,
     uint16_t *utf16_string,
     size_t utf16_string_size,
     liberror_error_t **error );

#if defined( __cplusplus )
}
#endif

#endif

