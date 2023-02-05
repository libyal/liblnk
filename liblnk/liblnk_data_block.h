/*
 * Data block functions
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

#if !defined( _LIBLNK_DATA_BLOCK_H )
#define _LIBLNK_DATA_BLOCK_H

#include <common.h>
#include <types.h>

#include "liblnk_extern.h"
#include "liblnk_io_handle.h"
#include "liblnk_libcerror.h"
#include "liblnk_libbfio.h"
#include "liblnk_types.h"

/* The following imports are necessary as a work-around for CygWin and MinGW
 * not including exported functions in the DLL.
 */
#include "liblnk_distributed_link_tracking_data_block.h"
#include "liblnk_strings_data_block.h"

#if defined( __cplusplus )
extern "C" {
#endif

typedef struct liblnk_internal_data_block liblnk_internal_data_block_t;

struct liblnk_internal_data_block
{
	/* The size
	 */
	uint32_t size;

	/* The signature
	 */
	uint32_t signature;

	/* The data
	 */
	uint8_t *data;

	/* The data size
	 */
	uint32_t data_size;

	/* The item value
	 */
	intptr_t *value;

	/* The item free value function
	 */
	int (*free_value)(
	       intptr_t **value,
	       libcerror_error_t **error );

	/* The codepage of the extended ASCII strings
	 */
	int ascii_codepage;
};

int liblnk_data_block_initialize(
     liblnk_data_block_t **data_block,
     libcerror_error_t **error );

LIBLNK_EXTERN \
int liblnk_data_block_free(
     liblnk_data_block_t **data_block,
     libcerror_error_t **error );

int liblnk_internal_data_block_free(
     liblnk_internal_data_block_t **internal_data_block,
     libcerror_error_t **error );

int liblnk_data_block_set_data(
     liblnk_data_block_t *data_block,
     const uint8_t *data,
     size_t data_size,
     libcerror_error_t **error );

int liblnk_data_block_read_data(
     liblnk_data_block_t *data_block,
     const uint8_t *data,
     size_t data_size,
     libcerror_error_t **error );

int liblnk_data_block_read_file_io_handle(
     liblnk_data_block_t *data_block,
     liblnk_io_handle_t *io_handle,
     libbfio_handle_t *file_io_handle,
     off64_t file_offset,
     libcerror_error_t **error );

int liblnk_internal_data_block_get_size(
     liblnk_internal_data_block_t *internal_data_block,
     uint32_t *size,
     libcerror_error_t **error );

LIBLNK_EXTERN \
int liblnk_data_block_get_signature(
     liblnk_data_block_t *data_block,
     uint32_t *signature,
     libcerror_error_t **error );

LIBLNK_EXTERN \
int liblnk_data_block_get_data_size(
     liblnk_data_block_t *data_block,
     size_t *data_size,
     libcerror_error_t **error );

LIBLNK_EXTERN \
int liblnk_data_block_copy_data(
     liblnk_data_block_t *data_block,
     uint8_t *data,
     size_t data_size,
     libcerror_error_t **error );

#if defined( __cplusplus )
}
#endif

#endif /* !defined( _LIBLNK_DATA_BLOCK_H ) */

