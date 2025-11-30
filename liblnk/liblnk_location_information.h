/*
 * Location information functions
 *
 * Copyright (C) 2009-2025, Joachim Metz <joachim.metz@gmail.com>
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

#if !defined( _LIBLNK_LOCATION_INFORMATION_H )
#define _LIBLNK_LOCATION_INFORMATION_H

#include <common.h>
#include <types.h>

#include "liblnk_io_handle.h"
#include "liblnk_libbfio.h"
#include "liblnk_libcerror.h"

#if defined( __cplusplus )
extern "C" {
#endif

typedef struct liblnk_location_information liblnk_location_information_t;

struct liblnk_location_information
{
	/* The location flags
	 */
	uint32_t flags;

	/* The drive type
	 */
	uint32_t drive_type;

	/* The drive serial number
	 */
	uint32_t drive_serial_number;

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
     libcerror_error_t **error );

int liblnk_location_information_free(
     liblnk_location_information_t **location_information,
     libcerror_error_t **error );

int liblnk_location_information_read_data(
     liblnk_location_information_t *location_information,
     liblnk_io_handle_t *io_handle,
     const uint8_t *data,
     size_t data_size,
     libcerror_error_t **error );

ssize_t liblnk_location_information_read(
         liblnk_location_information_t *location_information,
         liblnk_io_handle_t *io_handle,
         libbfio_handle_t *file_io_handle,
         off64_t location_information_offset,
         libcerror_error_t **error );

int liblnk_location_information_get_utf8_volume_label_size(
     liblnk_location_information_t *location_information,
     int ascii_codepage,
     size_t *utf8_string_size,
     libcerror_error_t **error );

int liblnk_location_information_get_utf8_volume_label(
     liblnk_location_information_t *location_information,
     int ascii_codepage,
     uint8_t *utf8_string,
     size_t utf8_string_size,
     libcerror_error_t **error );

int liblnk_location_information_get_utf16_volume_label_size(
     liblnk_location_information_t *location_information,
     int ascii_codepage,
     size_t *utf16_string_size,
     libcerror_error_t **error );

int liblnk_location_information_get_utf16_volume_label(
     liblnk_location_information_t *location_information,
     int ascii_codepage,
     uint16_t *utf16_string,
     size_t utf16_string_size,
     libcerror_error_t **error );

int liblnk_location_information_get_utf8_local_path_size(
     liblnk_location_information_t *location_information,
     int ascii_codepage,
     size_t *utf8_string_size,
     libcerror_error_t **error );

int liblnk_location_information_get_utf8_local_path(
     liblnk_location_information_t *location_information,
     int ascii_codepage,
     uint8_t *utf8_string,
     size_t utf8_string_size,
     libcerror_error_t **error );

int liblnk_location_information_get_utf16_local_path_size(
     liblnk_location_information_t *location_information,
     int ascii_codepage,
     size_t *utf16_string_size,
     libcerror_error_t **error );

int liblnk_location_information_get_utf16_local_path(
     liblnk_location_information_t *location_information,
     int ascii_codepage,
     uint16_t *utf16_string,
     size_t utf16_string_size,
     libcerror_error_t **error );

int liblnk_location_information_get_utf8_network_path_size(
     liblnk_location_information_t *location_information,
     int ascii_codepage,
     size_t *utf8_string_size,
     libcerror_error_t **error );

int liblnk_location_information_get_utf8_network_path(
     liblnk_location_information_t *location_information,
     int ascii_codepage,
     uint8_t *utf8_string,
     size_t utf8_string_size,
     libcerror_error_t **error );

int liblnk_location_information_get_utf16_network_path_size(
     liblnk_location_information_t *location_information,
     int ascii_codepage,
     size_t *utf16_string_size,
     libcerror_error_t **error );

int liblnk_location_information_get_utf16_network_path(
     liblnk_location_information_t *location_information,
     int ascii_codepage,
     uint16_t *utf16_string,
     size_t utf16_string_size,
     libcerror_error_t **error );

#if defined( __cplusplus )
}
#endif

#endif /* !defined( _LIBLNK_LOCATION_INFORMATION_H ) */

