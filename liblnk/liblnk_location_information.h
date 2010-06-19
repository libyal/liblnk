/*
 * Location information functions
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

	/* The volume label string
	 */
	liblnk_character_t *volume_label;

	/* The size of the volume label string
	 */
	size_t volume_label_size;

	/* The local path string
	 */
	liblnk_character_t *local_path;

	/* The size of the local path string
	 */
	size_t local_path_size;

	/* The network share name string
	 */
	liblnk_character_t *network_share_name;

	/* The size of the network share name string
	 */
	size_t network_share_name_size;

	/* The device name string
	 */
	liblnk_character_t *device_name;

	/* The size of the device name string
	 */
	size_t device_name_size;

	/* The network provider type
	 */
	uint32_t network_provider_type;

	/* The common path string
	 */
	liblnk_character_t *common_path;

	/* The size of the common path string
	 */
	size_t common_path_size;
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

