/*
 * Shell item identifiers list functions
 *
 * Copyright (c) 2009-2011, Joachim Metz <jbmetz@users.sourceforge.net>
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

#if !defined( _LIBLNK_SHELL_ITEM_IDENTIFIERS_LIST_H )
#define _LIBLNK_SHELL_ITEM_IDENTIFIERS_LIST_H

#include <common.h>
#include <types.h>

#include <liberror.h>

#include "liblnk_libbfio.h"

#if defined( __cplusplus )
extern "C" {
#endif

typedef struct liblnk_shell_item_identifiers_list liblnk_shell_item_identifiers_list_t;

struct liblnk_shell_item_identifiers_list
{
	/* Dummy value
	 */
	int dummy;
};

int liblnk_shell_item_identifiers_list_initialize(
     liblnk_shell_item_identifiers_list_t **shell_item_identifiers_list,
     liberror_error_t **error );

int liblnk_shell_item_identifiers_list_free(
     liblnk_shell_item_identifiers_list_t **shell_item_identifiers_list,
     liberror_error_t **error );

ssize_t liblnk_shell_item_identifiers_list_read(
         liblnk_shell_item_identifiers_list_t *shell_item_identifiers_list,
         libbfio_handle_t *file_io_handle,
         off64_t shell_item_identifiers_list_offset,
         liberror_error_t **error );

#if defined( __cplusplus )
}
#endif

#endif

