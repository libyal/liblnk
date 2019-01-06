/*
 * Data block strings functions
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

#if !defined( _LIBLNK_DATA_BLOCK_STRINGS_H )
#define _LIBLNK_DATA_BLOCK_STRINGS_H

#include <common.h>
#include <types.h>

#include "liblnk_data_block.h"
#include "liblnk_data_string.h"
#include "liblnk_io_handle.h"
#include "liblnk_libcerror.h"

#if defined( __cplusplus )
extern "C" {
#endif

int liblnk_data_block_strings_read(
     liblnk_data_string_t *data_string,
     liblnk_data_block_t *data_block,
     liblnk_io_handle_t *io_handle,
     libcerror_error_t **error );

#if defined( __cplusplus )
}
#endif

#endif /* !defined( _LIBLNK_DATA_BLOCK_STRINGS_H ) */

