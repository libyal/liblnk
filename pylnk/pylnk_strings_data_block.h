/*
 * Python object wrapper of liblnk_data_block_t with strings
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

#if !defined( _PYLNK_STRINGS_DATA_BLOCK_H )
#define _PYLNK_STRINGS_DATA_BLOCK_H

#include <common.h>
#include <types.h>

#include "pylnk_data_block.h"
#include "pylnk_liblnk.h"
#include "pylnk_python.h"

#if defined( __cplusplus )
extern "C" {
#endif

extern PyMethodDef pylnk_strings_data_block_object_methods[];
extern PyTypeObject pylnk_strings_data_block_type_object;

PyObject *pylnk_strings_data_block_get_string(
           pylnk_data_block_t *pylnk_data_block,
           PyObject *arguments );

#if defined( __cplusplus )
}
#endif

#endif /* !defined( _PYLNK_STRINGS_DATA_BLOCK_H ) */

