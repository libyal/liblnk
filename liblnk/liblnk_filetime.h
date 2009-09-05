/*
 * Filetime functions
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

#if !defined( _LIBLNK_FILETIME_H )
#define _LIBLNK_FILETIME_H

#include <common.h>
#include <types.h>

#include <liberror.h>

#if defined( __cplusplus )
extern "C" {
#endif

#define LIBLNK_FILETIME_ZERO		{ 0, 0 }
#define LIBLNK_FILETIME_STRING_SIZE	26

typedef struct liblnk_filetime liblnk_filetime_t;

/* Contains a 64-bit value representing the number of 100-nanosecond intervals since January 1, 1601 (UTC)
 */
struct liblnk_filetime
{
	/* The lower filetime part
	 */
	uint32_t lower;

	/* The upper filetime part
	 */
	uint32_t upper;
};

int liblnk_filetime_from_byte_stream(
     liblnk_filetime_t *filetime,
     uint8_t *byte_stream,
     size_t byte_stream_size,
     uint8_t byte_order,
     liberror_error_t **error );

int liblnk_filetime_to_string(
     liblnk_filetime_t *filetime,
     uint8_t *string,
     size_t string_size,
     liberror_error_t **error );

#if defined( __cplusplus )
}
#endif

#endif

