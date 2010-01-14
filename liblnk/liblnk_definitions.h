/*
 * The internal definitions
 *
 * Copyright (c) 2008-2010, Joachim Metz <forensics@hoffmannbv.nl>,
 * Hoffmann Investigations.
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
#include <byte_stream.h>

#define LIBLNK_ENDIAN_BIG						_BYTE_STREAM_ENDIAN_BIG
#define LIBLNK_ENDIAN_LITTLE						_BYTE_STREAM_ENDIAN_LITTLE

/* Define HAVE_LOCAL_LIBLNK for local use of liblnk
 */
#if !defined( HAVE_LOCAL_LIBLNK )
#include <liblnk/definitions.h>

/* The definitions in <liblnk/definitions.h> are copied here
 * for local use of liblnk
 */
#else
#define LIBLNK_VERSION							20090913

/* The liblnk version string
 */
#define LIBLNK_VERSION_STRING						"20090913"

/* The liblnk file access
 * bit 1        set to 1 for read access
 * bit 2        set to 1 for write access
 * bit 3-8      not used
 */
#define LIBLNK_FLAG_READ						0x01
/* Reserved: not supported yet */
#define LIBLNK_FLAG_WRITE						0x02

/* The liblnk file access macros
 */
#define LIBLNK_OPEN_READ						( LIBLNK_FLAG_READ )
/* Reserved: not supported yet */
#define LIBLNK_OPEN_WRITE						( LIBLNK_FLAG_WRITE )
/* Reserved: not supported yet */
#define LIBLNK_OPEN_READ_WRITE						( LIBLNK_FLAG_READ | LIBLNK_FLAG_WRITE )

/* The data flags
 */
enum LIBLNK_DATA_FLAGS
{
	LIBLNK_DATA_FLAG_HAS_LINK_TARGET_IDENTIFIER			= 0x00000001,
	LIBLNK_DATA_FLAG_HAS_LOCATION_INFORMATION			= 0x00000002,
	LIBLNK_DATA_FLAG_HAS_DESCRIPTION_STRING				= 0x00000004,
	LIBLNK_DATA_FLAG_HAS_RELATIVE_PATH_STRING			= 0x00000008,
	LIBLNK_DATA_FLAG_HAS_WORKING_DIRECTORY_STRING			= 0x00000010,
	LIBLNK_DATA_FLAG_HAS_COMMAND_LINE_ARGUMENTS_STRING		= 0x00000020,
	LIBLNK_DATA_FLAG_HAS_ICON_LOCATION_STRING			= 0x00000040,
	LIBLNK_DATA_FLAG_IS_UNICODE					= 0x00000080,
	LIBLNK_DATA_FLAG_FORCE_NO_LOCATION_INFORMATION			= 0x00000100,
	LIBLNK_DATA_FLAG_HAS_ENVIRONMENT_VARIABLES_LOCATION_BLOCK	= 0x00000200,
	LIBLNK_DATA_FLAG_RUN_IN_SEPARATE_PROCESS			= 0x00000400,

	LIBLNK_DATA_FLAG_HAS_DARWIN_IDENTIFIER				= 0x00001000,
	LIBLNK_DATA_FLAG_RUN_AS_USER					= 0x00002000,
	LIBLNK_DATA_FLAG_HAS_ICON_LOCATION_BLOCK			= 0x00004000,
	LIBLNK_DATA_FLAG_NO_PIDL_ALIAS					= 0x00008000,

	LIBLNK_DATA_FLAG_RUN_WITH_SHIM_LAYER				= 0x00020000,
	LIBLNK_DATA_FLAG_NO_DISTRIBUTED_LINK_TRACKING_DATA_BLOCK	= 0x00040000,
	LIBLNK_DATA_FLAG_HAS_METADATA_PROPERTY_STORE_DATA_BLOCK		= 0x00080000,
};

/* The file attribute flags
 */
enum LIBLNK_FILE_ATTRIBUTE_FLAGS
{
	LIBLNK_FILE_ATTRIBUTE_FLAG_READ_ONLY				= 0x00000001,
	LIBLNK_FILE_ATTRIBUTE_FLAG_HIDDEN				= 0x00000002,
	LIBLNK_FILE_ATTRIBUTE_FLAG_SYSTEM				= 0x00000004,

	LIBLNK_FILE_ATTRIBUTE_FLAG_DIRECTORY				= 0x00000010,
	LIBLNK_FILE_ATTRIBUTE_FLAG_ARCHIVE				= 0x00000020,
	LIBLNK_FILE_ATTRIBUTE_FLAG_DEVICE				= 0x00000040,
	LIBLNK_FILE_ATTRIBUTE_FLAG_NORMAL				= 0x00000080,
	LIBLNK_FILE_ATTRIBUTE_FLAG_TEMPORARY				= 0x00000100,
	LIBLNK_FILE_ATTRIBUTE_FLAG_SPARSE_FILE				= 0x00000200,
	LIBLNK_FILE_ATTRIBUTE_FLAG_REPARSE_POINT			= 0x00000400,
	LIBLNK_FILE_ATTRIBUTE_FLAG_COMPRESSED				= 0x00000800,
	LIBLNK_FILE_ATTRIBUTE_FLAG_OFFLINE				= 0x00001000,
	LIBLNK_FILE_ATTRIBUTE_FLAG_NOT_CONTENT_INDEXED			= 0x00002000,
	LIBLNK_FILE_ATTRIBUTE_FLAG_ENCRYPTED				= 0x00004000,

	LIBLNK_FILE_ATTRIBUTE_FLAG_VIRTUAL				= 0x00010000
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

