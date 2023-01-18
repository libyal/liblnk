/*
 * File header functions
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

#if !defined( _LIBLNK_FILE_HEADER_H )
#define _LIBLNK_FILE_HEADER_H

#include <common.h>
#include <types.h>

#include "liblnk_libbfio.h"
#include "liblnk_libcerror.h"

#if defined( __cplusplus )
extern "C" {
#endif

typedef struct liblnk_file_header liblnk_file_header_t;

struct liblnk_file_header
{
	/* The class identifier
	 */
	uint8_t class_identifier[ 16 ];

	/* The data flags
	 */
	uint32_t data_flags;

	/* The file attribute flags
	 */
	uint32_t file_attribute_flags;

	/* The creation date and time
	 * Contains a 64-bit filetime value
	 */
	uint64_t creation_time;

	/* The last access date and time
	 * Contains a 64-bit filetime value
	 */
	uint64_t access_time;

	/* The last modification date and time
	 * Contains a 64-bit filetime value
	 */
	uint64_t modification_time;

	/* The file size
	 */
	uint32_t file_size;

	/* The icon index
	 */
	uint32_t icon_index;

	/* The show window
	 */
	uint32_t show_window;

	/* The hot key
	 */
	uint16_t hot_key;
};

int liblnk_file_header_initialize(
     liblnk_file_header_t **file_header,
     libcerror_error_t **error );

int liblnk_file_header_free(
     liblnk_file_header_t **file_header,
     libcerror_error_t **error );

int liblnk_file_header_read_data(
     liblnk_file_header_t *file_header,
     const uint8_t *data,
     size_t data_size,
     libcerror_error_t **error );

int liblnk_file_header_read_file_io_handle(
     liblnk_file_header_t *file_header,
     libbfio_handle_t *file_io_handle,
     off64_t file_offset,
     libcerror_error_t **error );

#if defined( __cplusplus )
}
#endif

#endif /* !defined( _LIBLNK_FILE_HEADER_H ) */

