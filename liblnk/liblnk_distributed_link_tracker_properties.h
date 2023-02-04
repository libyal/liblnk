/*
 * Distributed link tracker properties functions
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

#if !defined( _LIBLNK_DISTRIBUTED_LINK_TRACKER_PROPERTIES_H )
#define _LIBLNK_DISTRIBUTED_LINK_TRACKER_PROPERTIES_H

#include <common.h>
#include <types.h>

#include "liblnk_data_block.h"
#include "liblnk_libcerror.h"

#if defined( __cplusplus )
extern "C" {
#endif

typedef struct liblnk_distributed_link_tracker_properties liblnk_distributed_link_tracker_properties_t;

struct liblnk_distributed_link_tracker_properties
{
	/* The machine identifier string
	 */
	uint8_t machine_identifier_string[ 16 ];

	/* The droid volume identifier
	 */
	uint8_t droid_volume_identifier[ 16 ];

	/* The droid file identifier
	 */
	uint8_t droid_file_identifier[ 16 ];

	/* The birth droid volume identifier
	 */
	uint8_t birth_droid_volume_identifier[ 16 ];

	/* The birth droid file identifier
	 */
	uint8_t birth_droid_file_identifier[ 16 ];
};

int liblnk_distributed_link_tracker_properties_initialize(
     liblnk_distributed_link_tracker_properties_t **distributed_link_tracker_properties,
     libcerror_error_t **error );

int liblnk_distributed_link_tracker_properties_free(
     liblnk_distributed_link_tracker_properties_t **distributed_link_tracker_properties,
     libcerror_error_t **error );

int liblnk_distributed_link_tracker_properties_read(
     liblnk_distributed_link_tracker_properties_t *distributed_link_tracker_properties,
     liblnk_data_block_t *data_block,
     int ascii_codepage,
     libcerror_error_t **error );

int liblnk_distributed_link_tracker_properties_get_utf8_machine_identifier_size(
     liblnk_distributed_link_tracker_properties_t *distributed_link_tracker_properties,
     size_t *utf8_string_size,
     int ascii_codepage,
     libcerror_error_t **error );

int liblnk_distributed_link_tracker_properties_get_utf8_machine_identifier(
     liblnk_distributed_link_tracker_properties_t *distributed_link_tracker_properties,
     uint8_t *utf8_string,
     size_t utf8_string_size,
     int ascii_codepage,
     libcerror_error_t **error );

int liblnk_distributed_link_tracker_properties_get_utf16_machine_identifier_size(
     liblnk_distributed_link_tracker_properties_t *distributed_link_tracker_properties,
     size_t *utf16_string_size,
     int ascii_codepage,
     libcerror_error_t **error );

int liblnk_distributed_link_tracker_properties_get_utf16_machine_identifier(
     liblnk_distributed_link_tracker_properties_t *distributed_link_tracker_properties,
     uint16_t *utf16_string,
     size_t utf16_string_size,
     int ascii_codepage,
     libcerror_error_t **error );

int liblnk_distributed_link_tracker_properties_get_droid_volume_identifier(
     liblnk_distributed_link_tracker_properties_t *distributed_link_tracker_properties,
     uint8_t *guid_data,
     size_t guid_data_size,
     libcerror_error_t **error );

int liblnk_distributed_link_tracker_properties_get_droid_file_identifier(
     liblnk_distributed_link_tracker_properties_t *distributed_link_tracker_properties,
     uint8_t *guid_data,
     size_t guid_data_size,
     libcerror_error_t **error );

int liblnk_distributed_link_tracker_properties_get_birth_droid_volume_identifier(
     liblnk_distributed_link_tracker_properties_t *distributed_link_tracker_properties,
     uint8_t *guid_data,
     size_t guid_data_size,
     libcerror_error_t **error );

int liblnk_distributed_link_tracker_properties_get_birth_droid_file_identifier(
     liblnk_distributed_link_tracker_properties_t *distributed_link_tracker_properties,
     uint8_t *guid_data,
     size_t guid_data_size,
     libcerror_error_t **error );

#if defined( __cplusplus )
}
#endif

#endif /* !defined( _LIBLNK_DISTRIBUTED_LINK_TRACKER_PROPERTIES_H ) */

