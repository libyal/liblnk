/*
 * Python object definition of the sequence and iterator object of data blocks
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

#if !defined( _PYLNK_DATA_BLOCKS_H )
#define _PYLNK_DATA_BLOCKS_H

#include <common.h>
#include <types.h>

#include "pylnk_liblnk.h"
#include "pylnk_python.h"

#if defined( __cplusplus )
extern "C" {
#endif

typedef struct pylnk_data_blocks pylnk_data_blocks_t;

struct pylnk_data_blocks
{
	/* Python object initialization
	 */
	PyObject_HEAD

	/* The parent object
	 */
	PyObject *parent_object;

	/* The get item by index callback function
	 */
	PyObject* (*get_item_by_index)(
	             PyObject *parent_object,
	             int index );

	/* The current index
	 */
	int current_index;

	/* The number of items
	 */
	int number_of_items;
};

extern PyTypeObject pylnk_data_blocks_type_object;

PyObject *pylnk_data_blocks_new(
           PyObject *parent_object,
           PyObject* (*get_item_by_index)(
                        PyObject *parent_object,
                        int index ),
           int number_of_items );

int pylnk_data_blocks_init(
     pylnk_data_blocks_t *sequence_object );

void pylnk_data_blocks_free(
      pylnk_data_blocks_t *sequence_object );

Py_ssize_t pylnk_data_blocks_len(
            pylnk_data_blocks_t *sequence_object );

PyObject *pylnk_data_blocks_getitem(
           pylnk_data_blocks_t *sequence_object,
           Py_ssize_t item_index );

PyObject *pylnk_data_blocks_iter(
           pylnk_data_blocks_t *sequence_object );

PyObject *pylnk_data_blocks_iternext(
           pylnk_data_blocks_t *sequence_object );

#if defined( __cplusplus )
}
#endif

#endif /* !defined( _PYLNK_DATA_BLOCKS_H ) */

