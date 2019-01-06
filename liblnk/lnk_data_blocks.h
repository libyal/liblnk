/*
 * The data blocks definition of a Windows Shortcut File (LNK)
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

#if !defined( _LNK_DATA_BLOCKS_H )
#define _LNK_DATA_BLOCKS_H

#include <common.h>
#include <types.h>

#if defined( __cplusplus )
extern "C" {
#endif

typedef struct lnk_data_block_strings lnk_data_block_strings_t;

struct lnk_data_block_strings
{
	/* The signature
	 * Consists of 4 bytes
	 * Contains: 0xa0000001 (for the environment variables properties)
	 *           0xa0000006 (for the darwin properties)
	 *           0xa0000007 (for the icon location)
	 */
	uint8_t signature[ 4 ];

	/* The string
	 * Consists of 260 bytes
	 */
	uint8_t string[ 260 ];

	/* The Unicode string
	 * Consists of 520 bytes
	 */
	uint8_t unicode_string[ 520 ];
};

typedef struct lnk_data_block_console_properties lnk_data_block_console_properties_t;

struct lnk_data_block_console_properties
{
	/* The signature
	 * Consists of 4 bytes
	 * Contains: 0xa0000002
	 */
	uint8_t signature[ 4 ];

/* TODO */
};

typedef struct lnk_data_block_distributed_link_tracker_properties lnk_data_block_distributed_link_tracker_properties_t;

struct lnk_data_block_distributed_link_tracker_properties
{
	/* The signature
	 * Consists of 4 bytes
	 * Contains: 0xa0000003
	 */
	uint8_t signature[ 4 ];

	/* The data size
	 * Consists of 4 bytes
	 */
	uint8_t data_size[ 4 ];

	/* The data version
	 * Consists of 4 bytes
	 */
	uint8_t data_version[ 4 ];

	/* The machine identifier string
	 * Consists of 16 bytes
	 */
	uint8_t machine_identifier_string[ 16 ];

	/* The droid volume identifier
	 * Consists of 16 bytes
	 * Contains a GUID
	 */
	uint8_t droid_volume_identifier[ 16 ];

	/* The droid file identifier
	 * Consists of 16 bytes
	 * Contains a GUID
	 */
	uint8_t droid_file_identifier[ 16 ];

	/* The birth droid volume identifier
	 * Consists of 16 bytes
	 * Contains a GUID
	 */
	uint8_t birth_droid_volume_identifier[ 16 ];

	/* The birth droid file identifier
	 * Consists of 16 bytes
	 * Contains a GUID
	 */
	uint8_t birth_droid_file_identifier[ 16 ];
};

typedef struct lnk_data_block_special_folder_location lnk_data_block_special_folder_location_t;

struct lnk_data_block_special_folder_location
{
	/* The signature
	 * Consists of 4 bytes
	 * Contains: 0xa0000005
	 */
	uint8_t signature[ 4 ];

	/* The folder identifier
	 * Consists of 4 bytes
	 */
	uint8_t folder_identifier[ 4 ];

	/* The first child segment offset
	 * Consists of 4 bytes
	 */
	uint8_t first_child_segment_offset[ 4 ];
};

typedef struct lnk_data_block_known_folder_location lnk_data_block_known_folder_location_t;

struct lnk_data_block_known_folder_location
{
	/* The signature
	 * Consists of 4 bytes
	 * Contains: 0xa000000b
	 */
	uint8_t signature[ 4 ];

	/* The folder identifier
	 * Consists of 16 bytes
	 * Contains a GUID
	 */
	uint8_t folder_identifier[ 16 ];

	/* The first child segment offset
	 * Consists of 4 bytes
	 */
	uint8_t first_child_segment_offset[ 4 ];
};

#if defined( __cplusplus )
}
#endif

#endif /* !defined( _LNK_DATA_BLOCKS_H ) */

