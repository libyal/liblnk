/*
 * Link target identifier functions
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

#if !defined( _LIBLNK_LINK_TARGET_IDENTIFIER_H )
#define _LIBLNK_LINK_TARGET_IDENTIFIER_H

#include <common.h>
#include <types.h>

#include "liblnk_io_handle.h"
#include "liblnk_libbfio.h"
#include "liblnk_libcerror.h"

#if defined( __cplusplus )
extern "C" {
#endif

typedef struct liblnk_link_target_identifier liblnk_link_target_identifier_t;

struct liblnk_link_target_identifier
{
	/* The data
	 */
	uint8_t *data;

	/* The data size
	 */
	size_t data_size;
};

int liblnk_link_target_identifier_initialize(
     liblnk_link_target_identifier_t **link_target_identifier,
     libcerror_error_t **error );

int liblnk_link_target_identifier_free(
     liblnk_link_target_identifier_t **link_target_identifier,
     libcerror_error_t **error );

ssize_t liblnk_link_target_identifier_read(
         liblnk_link_target_identifier_t *link_target_identifier,
         liblnk_io_handle_t *io_handle,
         libbfio_handle_t *file_io_handle,
         off64_t link_target_identifier_offset,
         libcerror_error_t **error );

#if defined( __cplusplus )
}
#endif

#endif /* !defined( _LIBLNK_LINK_TARGET_IDENTIFIER_H ) */

