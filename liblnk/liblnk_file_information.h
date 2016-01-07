/*
 * File information functions
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

#if !defined( _LIBLNK_FILE_INFORMATION_H )
#define _LIBLNK_FILE_INFORMATION_H

#include <common.h>
#include <types.h>

#include "liblnk_libcerror.h"

#if defined( __cplusplus )
extern "C" {
#endif

typedef struct liblnk_file_information liblnk_file_information_t;

struct liblnk_file_information
{
	/* The size
	 */
	uint32_t size;

	/* The attribute flags
	 */
	uint32_t attribute_flags;

	/* The creation date and time
	 * Contains a 64-bit filetime value
	 */
	uint64_t creation_time;

	/* The last modificatoin date and time
	 * Contains a 64-bit filetime value
	 */
	uint64_t modification_time;

	/* The last access date and time
	 * Contains a 64-bit filetime value
	 */
	uint64_t access_time;
};

int liblnk_file_information_initialize(
     liblnk_file_information_t **file_information,
     libcerror_error_t **error );

int liblnk_file_information_free(
     liblnk_file_information_t **file_information,
     libcerror_error_t **error );

#if defined( __cplusplus )
}
#endif

#endif

