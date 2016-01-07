/*
 * The file header definition of a Windows Shortcut File (LNK)
 *
 * Copyright (C) 2009-2016, Joachim Metz <joachim.metz@gmail.com>
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

#if !defined( _LNK_FILE_HEADER_H )
#define _LNK_FILE_HEADER_H

#include <common.h>
#include <types.h>

#if defined( __cplusplus )
extern "C" {
#endif

typedef struct lnk_file_header lnk_file_header_t;

struct lnk_file_header
{
	/* The header size
	 * Consists of 4 bytes
	 */
	uint8_t header_size[ 4 ];

	/* Class identifier
	 * Consists of 16 bytes
	 * Contains the little-endian GUID: {00021401-0000-0000-00c0-000000000046}
	 */
	uint8_t class_identifier[ 16 ];

	/* Data flags
	 * Consists of 4 bytes
	 */
	uint8_t data_flags[ 4 ];

	/* File attribute flags
	 * Consists of 4 bytes
	 */
	uint8_t file_attribute_flags[ 4 ];

	/* Creation date and time
	 * Consists of 8 bytes
	 * Contains a filetime
	 */
	uint8_t creation_time[ 8 ];

	/* Last access date and time
	 * Consists of 8 bytes
	 * Contains a filetime
	 */
	uint8_t access_time[ 8 ];

	/* Last modification date and time
	 * Consists of 8 bytes
	 * Contains a filetime
	 */
	uint8_t modification_time[ 8 ];

	/* The size of the file
	 * Consists of 4 bytes
	 */
	uint8_t file_size[ 4 ];

	/* The icon index value
	 * Consists of 4 bytes
	 */
	uint8_t icon_index[ 4 ];

	/* The ShowWindow value
	 * Consists of 4 bytes
	 */
	uint8_t show_window_value[ 4 ];

	/* The hot key value
	 * Consists of 2 bytes
	 */
	uint8_t hot_key_value[ 2 ];

	/* Reserved
	 * Consists of 10 bytes
	 * a 2 byte value
	 * a 4 byte value
	 * a 4 byte value
	 */
	uint8_t reserved[ 10 ];
};

#if defined( __cplusplus )
}
#endif

#endif

