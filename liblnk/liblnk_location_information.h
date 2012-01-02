/*
 * Location information functions
 *
 * Copyright (c) 2009-2012, Joachim Metz <jbmetz@users.sourceforge.net>
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

#include "liblnk_io_handle.h"
#include "liblnk_libbfio.h"

#if defined( __cplusplus )
extern "C" {
#endif

enum LIBLNK_LOCATION_INFORMATION_STRING_FLAGS
{
	LIBLNK_LOCATION_INFORMATION_STRING_FLAG_VOLUME_LABEL_IS_UNICODE		= 0x01,
	LIBLNK_LOCATION_INFORMATION_STRING_FLAG_LOCAL_PATH_IS_UNICODE		= 0x02,
	LIBLNK_LOCATION_INFORMATION_STRING_FLAG_NETWORK_SHARE_NAME_IS_UNICODE	= 0x04,
	LIBLNK_LOCATION_INFORMATION_STRING_FLAG_DEVICE_NAME_IS_UNICODE		= 0x08,
	LIBLNK_LOCATION_INFORMATION_STRING_FLAG_COMMON_PATH_IS_UNICODE		= 0x10
};

typedef struct liblnk_location_information liblnk_location_information_t;

struct liblnk_location_information
{
	/* The location flags
	 */
	uint32_t flags;

	/* The string flags
	 */
	uint8_t string_flags; 

	/* The volume label
	 */
	uint8_t *volume_label;

	/* The volume label size
	 */
	size_t volume_label_size;

	/* The local path
	 */
	uint8_t *local_path;

	/* The local path size
	 */
	size_t local_path_size;

	/* The network share name
	 */
	uint8_t *network_share_name;

	/* The network share name size
	 */
	size_t network_share_name_size;

	/* The device name
	 */
	uint8_t *device_name;

	/* The device name size
	 */
	size_t device_name_size;

	/* The network provider type
	 */
	uint32_t network_provider_type;

	/* The common path
	 */
	uint8_t *common_path;

	/* The common path size
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
         liblnk_io_handle_t *io_handle,
         libbfio_handle_t *file_io_handle,
         off64_t location_information_offset,
         liberror_error_t **error );

#if defined( __cplusplus )
}
#endif

#endif

