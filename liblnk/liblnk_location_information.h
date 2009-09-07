/*
 * Location information functions
 *
 * Copyright (c) 2009, Joachim Metz <forensics@hoffmannbv.nl>,
 * Hoffmann Investigations. All rights reserved.
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

#if !defined( _LIBLNK_LOCATION_INFORMATION_H )
#define _LIBLNK_LOCATION_INFORMATION_H

#include <common.h>
#include <types.h>

#include <liberror.h>

#include "liblnk_libbfio.h"
#include "liblnk_string.h"

#if defined( __cplusplus )
extern "C" {
#endif

typedef struct liblnk_location_information liblnk_location_information_t;

struct liblnk_location_information
{
	/* The location flags
	 */
	uint32_t flags;

	/* The local path string
	 */
	liblnk_character_t *local_path;

	/* The size of the local path string
	 */
	size_t local_path_size;

	/* The network share string
	 */
	liblnk_character_t *network_share;

	/* The size of the network share string
	 */
	size_t network_share_size;

	/* The path remainder string
	 */
	liblnk_character_t *path_remainder;

	/* The size of the path remainder string
	 */
	size_t path_remainder_size;
};

int liblnk_location_information_initialize(
     liblnk_location_information_t **location_information,
     liberror_error_t **error );

int liblnk_location_information_free(
     liblnk_location_information_t **location_information,
     liberror_error_t **error );

ssize_t liblnk_location_information_read(
         liblnk_location_information_t *location_information,
         libbfio_handle_t *file_io_handle,
         off64_t location_information_offset,
         int ascii_codepage,
         liberror_error_t **error );

#if defined( __cplusplus )
}
#endif

#endif

