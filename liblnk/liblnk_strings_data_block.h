/*
 * Strings data block functions
 *
 * Copyright (C) 2009-2023, Joachim Metz <joachim.metz@gmail.com>
 *
 * Refer to AUTHORS for acknowledgements.
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU Lesser General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU Lesser General Public License
 * along with this program.  If not, see <https://www.gnu.org/licenses/>.
 */

#if !defined( _LIBLNK_STRINGS_DATA_BLOCK_H )
#define _LIBLNK_STRINGS_DATA_BLOCK_H

#include <common.h>
#include <types.h>

#include "liblnk_extern.h"
#include "liblnk_libcerror.h"
#include "liblnk_types.h"

#if defined( __cplusplus )
extern "C" {
#endif

int liblnk_strings_data_block_read(
     liblnk_data_block_t *data_block,
     libcerror_error_t **error );

LIBLNK_EXTERN \
int liblnk_strings_data_block_get_utf8_string_size(
     liblnk_data_block_t *data_block,
     size_t *utf8_string_size,
     libcerror_error_t **error );

LIBLNK_EXTERN \
int liblnk_strings_data_block_get_utf8_string(
     liblnk_data_block_t *data_block,
     uint8_t *utf8_string,
     size_t utf8_string_size,
     libcerror_error_t **error );

LIBLNK_EXTERN \
int liblnk_strings_data_block_get_utf16_string_size(
     liblnk_data_block_t *data_block,
     size_t *utf16_string_size,
     libcerror_error_t **error );

LIBLNK_EXTERN \
int liblnk_strings_data_block_get_utf16_string(
     liblnk_data_block_t *data_block,
     uint16_t *utf16_string,
     size_t utf16_string_size,
     libcerror_error_t **error );

#if defined( __cplusplus )
}
#endif

#endif /* !defined( _LIBLNK_STRINGS_DATA_BLOCK_H ) */

