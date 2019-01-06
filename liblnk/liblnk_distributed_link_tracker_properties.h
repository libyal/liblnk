/*
 * Distributed link tracker properties functions
 *
 * Copyright (C) 2009-2019, Joachim Metz <joachim.metz@gmail.com>
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

#if !defined( _LIBLNK_DISTRIBUTED_LINK_TRACKER_PROPERTIES_H )
#define _LIBLNK_DISTRIBUTED_LINK_TRACKER_PROPERTIES_H

#include <common.h>
#include <types.h>

#include "liblnk_data_block.h"
#include "liblnk_io_handle.h"
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
     liblnk_io_handle_t *io_handle,
     libcerror_error_t **error );

#if defined( __cplusplus )
}
#endif

#endif /* !defined( _LIBLNK_DISTRIBUTED_LINK_TRACKER_PROPERTIES_H ) */

