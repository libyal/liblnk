/*
 * liblnk file
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

#if !defined( _LIBLNK_INTERNAL_FILE_H )
#define _LIBLNK_INTERNAL_FILE_H

#include <common.h>
#include <types.h>

#include <liberror.h>

#include "liblnk_extern.h"
#include "liblnk_io_handle.h"

#if defined( __cplusplus )
extern "C" {
#endif

typedef struct liblnk_internal_file liblnk_internal_file_t;

struct liblnk_internal_file
{
	/* The io handle
	 */
	liblnk_io_handle_t *io_handle;

	/* The codepage of the extended ASCII strings
	 */
	int ascii_codepage;

	/* Value to indicate if abort was signalled
	 */
	int abort;
};

LIBLNK_EXTERN int liblnk_file_initialize(
                   liblnk_file_t **file,
                   liberror_error_t **error );

LIBLNK_EXTERN int liblnk_file_free(
                   liblnk_file_t **file,
                   liberror_error_t **error );

LIBLNK_EXTERN int liblnk_file_signal_abort(
                   liblnk_file_t *file,
                   liberror_error_t **error );

LIBLNK_EXTERN int liblnk_file_open(
                   liblnk_file_t *file,
                   const char *filename,
                   int flags,
                   liberror_error_t **error );

#if defined( LIBLNK_WIDE_CHARACTER_TYPE )
LIBLNK_EXTERN int liblnk_file_open_wide(
                   liblnk_file_t *file,
                   const wchar_t *filename,
                   int flags,
                   liberror_error_t **error );
#endif

LIBLNK_EXTERN int liblnk_file_open_file_io_handle(
                   liblnk_file_t *file,
                   libbfio_handle_t *file_io_handle,
                   int flags,
                   liberror_error_t **error );

LIBLNK_EXTERN int liblnk_file_close(
                   liblnk_file_t *file,
                   liberror_error_t **error );

int liblnk_file_open_read(
     liblnk_internal_file_t *internal_file,
     liberror_error_t **error );

LIBLNK_EXTERN int liblnk_file_get_ascii_codepage(
                   liblnk_file_t *file,
                   int *ascii_codepage,
                   liberror_error_t **error );

LIBLNK_EXTERN int liblnk_file_set_ascii_codepage(
                   liblnk_file_t *file,
                   int ascii_codepage,
                   liberror_error_t **error );

#if defined( __cplusplus )
}
#endif

#endif

