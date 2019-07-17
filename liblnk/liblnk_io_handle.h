/*
 * Input/Output (IO) handle
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

#if !defined( _LIBLNK_IO_HANDLE_H )
#define _LIBLNK_IO_HANDLE_H

#include <common.h>
#include <types.h>

#include "liblnk_libcerror.h"

#if defined( __cplusplus )
extern "C" {
#endif

extern const uint8_t lnk_file_class_identifier[ 16 ];

typedef struct liblnk_io_handle liblnk_io_handle_t;

struct liblnk_io_handle
{
	/* The file size
	 */
	size64_t file_size;

	/* Value to indicate if the string data is in Unicode (UTF-16 little-endian)
	 */
	uint8_t is_unicode;

	/* Flags
	 */
	uint8_t flags;

	/* The codepage of the extended ASCII strings
	 */
	int ascii_codepage;

	/* Value to indicate if abort was signalled
	 */
	int abort;
};

int liblnk_io_handle_initialize(
     liblnk_io_handle_t **io_handle,
     libcerror_error_t **error );

int liblnk_io_handle_free(
     liblnk_io_handle_t **io_handle,
     libcerror_error_t **error );

int liblnk_io_handle_clear(
     liblnk_io_handle_t *io_handle,
     libcerror_error_t **error );

#if defined( __cplusplus )
}
#endif

#endif /* !defined( _LIBLNK_IO_HANDLE_H ) */

