/*
 * File header of the Windows Shortcut File (LNK) format
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
	/* Header size
	 * Consists of 4 bytes
	 */
	uint8_t header_size[ 4 ];

	/* Class identifier
	 * Consists of 16 bytes
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
	 */
	uint8_t creation_time[ 8 ];

	/* Last access date and time
	 * Consists of 8 bytes
	 */
	uint8_t access_time[ 8 ];

	/* Last modification date and time
	 * Consists of 8 bytes
	 */
	uint8_t modification_time[ 8 ];

	/* File size
	 * Consists of 4 bytes
	 */
	uint8_t file_size[ 4 ];

	/* Icon index
	 * Consists of 4 bytes
	 */
	uint8_t icon_index[ 4 ];

	/* Show window
	 * Consists of 4 bytes
	 */
	uint8_t show_window[ 4 ];

	/* Hot key
	 * Consists of 2 bytes
	 */
	uint8_t hot_key[ 2 ];

	/* Unknown (reserved)
	 * Consists of 2 bytes
	 */
	uint8_t unknown1[ 2 ];

	/* Unknown (reserved)
	 * Consists of 4 bytes
	 */
	uint8_t unknown2[ 4 ];

	/* Unknown (reserved)
	 * Consists of 4 bytes
	 */
	uint8_t unknown3[ 4 ];
};

#if defined( __cplusplus )
}
#endif

#endif /* !defined( _LNK_FILE_HEADER_H ) */

