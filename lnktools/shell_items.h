/*
 * Shell items functions
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

#if !defined( _SHELL_ITEMS_H )
#define _SHELL_ITEMS_H

#include <common.h>
#include <file_stream.h>
#include <types.h>

#include "lnktools_libfwsi.h"

#if defined( __cplusplus )
extern "C" {
#endif

void shell_items_file_attribute_flags_fprint(
      uint32_t file_attribute_flags,
      FILE *notify_stream );

int shell_items_extension_block_fprint(
     libfwsi_extension_block_t *extension_block,
     int extension_block_index,
     FILE *notify_stream,
     libcerror_error_t **error );

int shell_items_file_entry_extension_fprint(
     libfwsi_extension_block_t *extension_block,
     FILE *notify_stream,
     libcerror_error_t **error );

int shell_items_item_fprint(
     libfwsi_item_t *shell_item,
     int shell_item_index,
     FILE *notify_stream,
     libcerror_error_t **error );

int shell_items_root_folder_fprint(
     libfwsi_item_t *shell_item,
     FILE *notify_stream,
     libcerror_error_t **error );

int shell_items_volume_fprint(
     libfwsi_item_t *shell_item,
     FILE *notify_stream,
     libcerror_error_t **error );

int shell_items_file_entry_fprint(
     libfwsi_item_t *shell_item,
     FILE *notify_stream,
     libcerror_error_t **error );

int shell_items_network_location_fprint(
     libfwsi_item_t *shell_item,
     FILE *notify_stream,
     libcerror_error_t **error );

int shell_items_item_list_fprint(
     libfwsi_item_list_t *shell_item_list,
     FILE *notify_stream,
     libcerror_error_t **error );

#if defined( __cplusplus )
}
#endif

#endif /* !defined( _SHELL_ITEMS_H ) */

