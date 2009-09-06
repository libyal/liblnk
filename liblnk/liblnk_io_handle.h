/*
 * liblnk Input/Output (IO) handle
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

#if !defined( _LIBLNK_IO_HANDLE_H )
#define _LIBLNK_IO_HANDLE_H

#include <common.h>
#include <types.h>

#include <liberror.h>

#include "liblnk_file_information.h"
#include "liblnk_libbfio.h"

#if defined( __cplusplus )
extern "C" {
#endif

extern const uint8_t lnk_file_signature[ 4 ];

typedef struct liblnk_io_handle liblnk_io_handle_t;

struct liblnk_io_handle
{
	/* The file io handle
	 */
	libbfio_handle_t *file_io_handle;

	/* Value to indicate if the file io handle was created inside the library
	 */
	uint8_t handle_created_in_library;
};

int liblnk_io_handle_initialize(
     liblnk_io_handle_t **io_handle,
     liberror_error_t **error );

int liblnk_io_handle_free(
     liblnk_io_handle_t **io_handle,
     liberror_error_t **error );

int liblnk_io_handle_open(
     liblnk_io_handle_t *io_handle,
     libbfio_handle_t *file_io_handle,
     int flags,
     liberror_error_t **error );

int liblnk_io_handle_close(
     liblnk_io_handle_t *io_handle,
     liberror_error_t **error );

int liblnk_io_handle_read_file_header(
     liblnk_io_handle_t *io_handle,
     uint32_t *data_flags,
     uint8_t *class_identifier,
     size_t class_identifier_size,
     liblnk_file_information_t *file_information,
     liberror_error_t **error );

#if defined( __cplusplus )
}
#endif

#endif

