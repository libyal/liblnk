/*
 * Python object wrapper of liblnk_data_block_t
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

#if !defined( _PYLNK_DATA_BLOCK_H )
#define _PYLNK_DATA_BLOCK_H

#include <common.h>
#include <types.h>

#include "pylnk_liblnk.h"
#include "pylnk_python.h"

#if defined( __cplusplus )
extern "C" {
#endif

typedef struct pylnk_data_block pylnk_data_block_t;

struct pylnk_data_block
{
	/* Python object initialization
	 */
	PyObject_HEAD

	/* The liblnk data block
	 */
	liblnk_data_block_t *data_block;

	/* The parent object
	 */
	PyObject *parent_object;
};

extern PyMethodDef pylnk_data_block_object_methods[];
extern PyTypeObject pylnk_data_block_type_object;

PyObject *pylnk_data_block_new(
           liblnk_data_block_t *data_block,
           PyObject *parent_object );

int pylnk_data_block_init(
     pylnk_data_block_t *pylnk_data_block );

void pylnk_data_block_free(
      pylnk_data_block_t *pylnk_data_block );

PyObject *pylnk_data_block_get_signature(
           pylnk_data_block_t *pylnk_data_block,
           PyObject *arguments );

PyObject *pylnk_data_block_get_data(
           pylnk_data_block_t *pylnk_data_block,
           PyObject *arguments );

#if defined( __cplusplus )
}
#endif

#endif /* !defined( _PYLNK_DATA_BLOCK_H ) */

