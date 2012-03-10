/*
 * Codepage functions
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

#if !defined( _PYLNK_CODEPAGE_H )
#define _PYLNK_CODEPAGE_H

#include <common.h>
#include <types.h>

#include <libcstring.h>
#include <liberror.h>

#include "pylnk_liblnk.h"

#if defined( __cplusplus )
extern "C" {
#endif

/* The codepage feature flag definitions
 */
enum PYLNK_CODEPAGE_FEATURE_FLAGS
{
	PYLNK_CODEPAGE_FEATURE_FLAG_HAVE_ISO_8859_CODEPAGES	= 0x00000001UL,
	PYLNK_CODEPAGE_FEATURE_FLAG_HAVE_KOI8_CODEPAGES		= 0x00000002UL,
	PYLNK_CODEPAGE_FEATURE_FLAG_HAVE_WINDOWS_CODEPAGES	= 0x00000004UL,
};

/* The codepage set definitions
 */
enum PYLNK_CODEPAGE_SETS
{
	PYLNK_CODEPAGE_SET_UNDEFINED				= 0,
	PYLNK_CODEPAGE_SET_GENERIC				= 1,
	PYLNK_CODEPAGE_SET_ISO_8859				= (int) 'i',
	PYLNK_CODEPAGE_SET_KOI8					= (int) 'k',
	PYLNK_CODEPAGE_SET_WINDOWS				= (int) 'w'
};

/* The codepage definitions
 */
enum PYLNK_CODEPAGES
{
	PYLNK_CODEPAGE_UNDEFINED				= 0,

	PYLNK_CODEPAGE_ASCII					= LIBLNK_CODEPAGE_ASCII,

	PYLNK_CODEPAGE_ISO_8859_1				= LIBLNK_CODEPAGE_ISO_8859_1,
	PYLNK_CODEPAGE_ISO_8859_2				= LIBLNK_CODEPAGE_ISO_8859_2,
	PYLNK_CODEPAGE_ISO_8859_3				= LIBLNK_CODEPAGE_ISO_8859_3,
	PYLNK_CODEPAGE_ISO_8859_4				= LIBLNK_CODEPAGE_ISO_8859_4,
	PYLNK_CODEPAGE_ISO_8859_5				= LIBLNK_CODEPAGE_ISO_8859_5,
	PYLNK_CODEPAGE_ISO_8859_6				= LIBLNK_CODEPAGE_ISO_8859_6,
	PYLNK_CODEPAGE_ISO_8859_7				= LIBLNK_CODEPAGE_ISO_8859_7,
	PYLNK_CODEPAGE_ISO_8859_8				= LIBLNK_CODEPAGE_ISO_8859_8,
	PYLNK_CODEPAGE_ISO_8859_9				= LIBLNK_CODEPAGE_ISO_8859_9,
	PYLNK_CODEPAGE_ISO_8859_10				= LIBLNK_CODEPAGE_ISO_8859_10,
	PYLNK_CODEPAGE_ISO_8859_11				= LIBLNK_CODEPAGE_ISO_8859_11,
	PYLNK_CODEPAGE_ISO_8859_13				= LIBLNK_CODEPAGE_ISO_8859_13,
	PYLNK_CODEPAGE_ISO_8859_14				= LIBLNK_CODEPAGE_ISO_8859_14,
	PYLNK_CODEPAGE_ISO_8859_15				= LIBLNK_CODEPAGE_ISO_8859_15,
	PYLNK_CODEPAGE_ISO_8859_16				= LIBLNK_CODEPAGE_ISO_8859_16,

	PYLNK_CODEPAGE_KOI8_R					= LIBLNK_CODEPAGE_KOI8_R,
	PYLNK_CODEPAGE_KOI8_U					= LIBLNK_CODEPAGE_KOI8_U,

	PYLNK_CODEPAGE_WINDOWS_874				= LIBLNK_CODEPAGE_WINDOWS_874,
	PYLNK_CODEPAGE_WINDOWS_932				= LIBLNK_CODEPAGE_WINDOWS_932,
	PYLNK_CODEPAGE_WINDOWS_936				= LIBLNK_CODEPAGE_WINDOWS_936,
	PYLNK_CODEPAGE_WINDOWS_949				= LIBLNK_CODEPAGE_WINDOWS_949,
	PYLNK_CODEPAGE_WINDOWS_950				= LIBLNK_CODEPAGE_WINDOWS_950,
	PYLNK_CODEPAGE_WINDOWS_1250				= LIBLNK_CODEPAGE_WINDOWS_1250,
	PYLNK_CODEPAGE_WINDOWS_1251				= LIBLNK_CODEPAGE_WINDOWS_1251,
	PYLNK_CODEPAGE_WINDOWS_1252				= LIBLNK_CODEPAGE_WINDOWS_1252,
	PYLNK_CODEPAGE_WINDOWS_1253				= LIBLNK_CODEPAGE_WINDOWS_1253,
	PYLNK_CODEPAGE_WINDOWS_1254				= LIBLNK_CODEPAGE_WINDOWS_1254,
	PYLNK_CODEPAGE_WINDOWS_1255				= LIBLNK_CODEPAGE_WINDOWS_1255,
	PYLNK_CODEPAGE_WINDOWS_1256				= LIBLNK_CODEPAGE_WINDOWS_1256,
	PYLNK_CODEPAGE_WINDOWS_1257				= LIBLNK_CODEPAGE_WINDOWS_1257,
	PYLNK_CODEPAGE_WINDOWS_1258				= LIBLNK_CODEPAGE_WINDOWS_1258
};

int pylnk_codepage_from_string(
     int *codepage,
     const char *string,
     size_t string_length,
     uint32_t feature_flags,
     liberror_error_t **error );

const char *pylnk_codepage_to_string(
             int codepage );

/* TODO add list function */

#if defined( __cplusplus )
}
#endif

#endif

