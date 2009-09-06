/*
 * The internal definitions
 *
 * Copyright (c) 2008-2009, Joachim Metz <forensics@hoffmannbv.nl>,
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

#if !defined( _LIBLNK_INTERNAL_DEFINITIONS_H )
#define _LIBLNK_INTERNAL_DEFINITIONS_H

#include <common.h>
#include <endian.h>

#define LIBLNK_ENDIAN_BIG		_ENDIAN_BIG
#define LIBLNK_ENDIAN_LITTLE		_ENDIAN_LITTLE

/* Define HAVE_LOCAL_LIBLNK for local use of liblnk
 */
#if !defined( HAVE_LOCAL_LIBLNK )
#include <liblnk/definitions.h>

/* The definitions in <liblnk/definitions.h> are copied here
 * for local use of liblnk
 */
#else
#define LIBLNK_VERSION			20090906

/* The liblnk version string
 */
#define LIBLNK_VERSION_STRING		"20090906"

/* The liblnk file access
 * bit 1        set to 1 for read access
 * bit 2        set to 1 for write access
 * bit 3-8      not used
 */
#define LIBLNK_FLAG_READ		0x01
/* Reserved: not supported yet */
#define LIBLNK_FLAG_WRITE		0x02

/* The liblnk file access macros
 */
#define LIBLNK_OPEN_READ		( LIBLNK_FLAG_READ )
/* Reserved: not supported yet */
#define LIBLNK_OPEN_WRITE		( LIBLNK_FLAG_WRITE )
/* Reserved: not supported yet */
#define LIBLNK_OPEN_READ_WRITE		( LIBLNK_FLAG_READ | LIBLNK_FLAG_WRITE )

/* The data flags
 */
enum LIBLNK_DATA_FLAGS
{
	LIBLNK_DATA_FLAG_CONTAINS_SHELL_ITEMS				= 0x00000001,
	LIBLNK_DATA_FLAG_CONTAINS_LOCATION_INFORMATION			= 0x00000002,
	LIBLNK_DATA_FLAG_CONTAINS_DESCRIPTION_DATA_STRING		= 0x00000004,
	LIBLNK_DATA_FLAG_CONTAINS_RELATIVE_PATH_DATA_STRING		= 0x00000008,
	LIBLNK_DATA_FLAG_CONTAINS_WORKING_DIRECTORY_DATA_STRING		= 0x00000010,
	LIBLNK_DATA_FLAG_CONTAINS_COMMAND_LINE_ARGUMENTS_DATA_STRING	= 0x00000020,
	LIBLNK_DATA_FLAG_CONTAINS_CUSTOM_ICON_FILENAME_DATA_STRING	= 0x00000040
};

#endif

/* The location flags
 */
enum LIBLNK_LOCATION_FLAGS
{
	LIBLNK_LOCATION_FLAG_HAS_VOLUME_INFORMATION			= 0x00000001,
	LIBLNK_LOCATION_FLAG_HAS_NETWORK_SHARE_INFORMATION		= 0x00000002
};

#endif

