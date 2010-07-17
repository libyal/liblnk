/*
 * Data string functions
 *
 * Copyright (c) 2009-2010, Joachim Metz <jbmetz@users.sourceforge.net>
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

#if !defined( _LIBLNK_DATA_STRING_H )
#define _LIBLNK_DATA_STRING_H

#include <common.h>
#include <types.h>

#include <liberror.h>

#include "liblnk_io_handle.h"
#include "liblnk_libbfio.h"

#if defined( __cplusplus )
extern "C" {
#endif

typedef struct liblnk_data_string liblnk_data_string_t;

struct liblnk_data_string
{
	/* Value to indicate if the string data is in Unicode (UTF-16 little-endian)
	 */
	uint8_t is_unicode;

	/* The data
	 */
	uint8_t *data;

	/* The data size
	 */
	size_t data_size;
};

int liblnk_data_string_initialize(
     liblnk_data_string_t **data_string,
     liberror_error_t **error );

int liblnk_data_string_free(
     liblnk_data_string_t **data_string,
     liberror_error_t **error );

ssize_t liblnk_data_string_read(
         liblnk_data_string_t *data_string,
         liblnk_io_handle_t *io_handle,
         libbfio_handle_t *file_io_handle,
         off64_t data_string_offset,
         liberror_error_t **error );

#if defined( __cplusplus )
}
#endif

#endif

