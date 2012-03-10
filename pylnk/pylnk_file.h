/*
 * Python object definition of the liblnk file
 *
 * Copyright (c) 2009-2012, Joachim Metz <jbmetz@users.sourceforge.net>
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

#if !defined( _PYLNK_FILE_H )
#define _PYLNK_FILE_H

#include <common.h>
#include <types.h>

#include <liberror.h>

#include "pylnk_liblnk.h"
#include "pylnk_python.h"

#if defined( __cplusplus )
extern "C" {
#endif

typedef struct pylnk_file pylnk_file_t;

struct pylnk_file
{
	/* Python object initialization
	 */
	PyObject_HEAD

	/* The liblnk file
	 */
	liblnk_file_t *file;
};

extern PyMethodDef pylnk_file_object_methods[];
extern PyTypeObject pylnk_file_type_object;

PyObject *pylnk_file_new(
           PyObject *self );

PyObject *pylnk_file_new_open(
           PyObject *self,
           PyObject *arguments,
           PyObject *keywords );

int pylnk_file_init(
     pylnk_file_t *pylnk_file );

void pylnk_file_free(
      pylnk_file_t *pylnk_file );

PyObject *pylnk_file_signal_abort(
           pylnk_file_t *pylnk_file );

PyObject *pylnk_file_get_attibute(
           pylnk_file_t *pylnk_file,
           const char *attribute_name,
           size_t attribute_name_length );

PyObject *pylnk_file_get_attibute_by_string(
           pylnk_file_t *pylnk_file,
           const char *attribute_name );

PyObject *pylnk_file_get_attibute_by_object(
           pylnk_file_t *pylnk_file,
           PyObject *attribute_name );

PyObject *pylnk_file_open(
           pylnk_file_t *pylnk_file,
           PyObject *arguments,
           PyObject *keywords );

PyObject *pylnk_file_open_file_object(
           pylnk_file_t *pylnk_file,
           PyObject *arguments,
           PyObject *keywords );

PyObject *pylnk_file_close(
           pylnk_file_t *pylnk_file );

PyObject *pylnk_file_get_ascii_codepage(
           pylnk_file_t *pylnk_file );

PyObject *pylnk_file_set_ascii_codepage(
           pylnk_file_t *pylnk_file,
           PyObject *arguments,
           PyObject *keywords );

PyObject *pylnk_file_get_file_creation_time(
           pylnk_file_t *pylnk_file );

PyObject *pylnk_file_get_file_modification_time(
           pylnk_file_t *pylnk_file );

PyObject *pylnk_file_get_file_access_time(
           pylnk_file_t *pylnk_file );

PyObject *pylnk_file_get_local_path(
           pylnk_file_t *pylnk_file );

PyObject *pylnk_file_get_network_path(
           pylnk_file_t *pylnk_file );

PyObject *pylnk_file_get_description(
           pylnk_file_t *pylnk_file );

PyObject *pylnk_file_get_relative_path(
           pylnk_file_t *pylnk_file );

PyObject *pylnk_file_get_working_directory(
           pylnk_file_t *pylnk_file );

PyObject *pylnk_file_get_command_line_arguments(
           pylnk_file_t *pylnk_file );

PyObject *pylnk_file_get_icon_location(
           pylnk_file_t *pylnk_file );

PyObject *pylnk_file_get_environment_variables_location(
           pylnk_file_t *pylnk_file );

#if defined( __cplusplus )
}
#endif

#endif

