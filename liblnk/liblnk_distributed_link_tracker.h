/*
 * Distributed link tracker functions
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

#if !defined( _LIBLNK_DISTRIBUTED_LINK_TRACKER_H )
#define _LIBLNK_DISTRIBUTED_LINK_TRACKER_H

#include <common.h>
#include <types.h>

#include "liblnk_extern.h"
#include "liblnk_libcerror.h"

#if defined( __cplusplus )
extern "C" {
#endif

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
     uint8_t *guid,
     size_t size,
     libcerror_error_t **error );

LIBLNK_EXTERN \
int liblnk_file_get_droid_file_identifier(
     liblnk_file_t *file,
     uint8_t *guid,
     size_t size,
     libcerror_error_t **error );

LIBLNK_EXTERN \
int liblnk_file_get_birth_droid_volume_identifier(
     liblnk_file_t *file,
     uint8_t *guid,
     size_t size,
     libcerror_error_t **error );

LIBLNK_EXTERN \
int liblnk_file_get_birth_droid_file_identifier(
     liblnk_file_t *file,
     uint8_t *guid,
     size_t size,
     libcerror_error_t **error );

#if defined( __cplusplus )
}
#endif

#endif

