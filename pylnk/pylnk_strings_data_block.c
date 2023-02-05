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

#include <common.h>
#include <types.h>

#if defined( HAVE_STDLIB_H ) || defined( HAVE_WINAPI )
#include <stdlib.h>
#endif

#include "pylnk_error.h"
#include "pylnk_integer.h"
#include "pylnk_data_block.h"
#include "pylnk_strings_data_block.h"
#include "pylnk_libcerror.h"
#include "pylnk_liblnk.h"
#include "pylnk_python.h"
#include "pylnk_unused.h"

PyMethodDef pylnk_strings_data_block_object_methods[] = {

	{ "get_string",
	  (PyCFunction) pylnk_strings_data_block_get_string,
	  METH_NOARGS,
	  "get_string() -> Unicode string or None\n"
	  "\n"
	  "Retrieves the string." },

	/* Sentinel */
	{ NULL, NULL, 0, NULL }
};

PyGetSetDef pylnk_strings_data_block_object_get_set_definitions[] = {

	{ "string",
	  (getter) pylnk_strings_data_block_get_string,
	  (setter) 0,
	  "The string.",
	  NULL },

	/* Sentinel */
	{ NULL, NULL, NULL, NULL, NULL }
};

PyTypeObject pylnk_strings_data_block_type_object = {
	PyVarObject_HEAD_INIT( NULL, 0 )

	/* tp_name */
	"pylnk.strings_data_block",
	/* tp_basicsize */
	sizeof( pylnk_data_block_t ),
	/* tp_data_blocksize */
	0,
	/* tp_dealloc */
	0,
	/* tp_print */
	0,
	/* tp_getattr */
	0,
	/* tp_setattr */
	0,
	/* tp_compare */
	0,
	/* tp_repr */
	0,
	/* tp_as_number */
	0,
	/* tp_as_sequence */
	0,
	/* tp_as_mapping */
	0,
	/* tp_hash */
	0,
	/* tp_call */
	0,
	/* tp_str */
	0,
	/* tp_getattro */
	0,
	/* tp_setattro */
	0,
	/* tp_as_buffer */
	0,
	/* tp_flags */
	Py_TPFLAGS_DEFAULT,
	/* tp_doc */
	"pylnk strings_data_block object (wraps liblnk_data_block_t with strings)",
	/* tp_traverse */
	0,
	/* tp_clear */
	0,
	/* tp_richcompare */
	0,
	/* tp_weaklistoffset */
	0,
	/* tp_iter */
	0,
	/* tp_iternext */
	0,
	/* tp_methods */
	pylnk_strings_data_block_object_methods,
	/* tp_members */
	0,
	/* tp_getset */
	pylnk_strings_data_block_object_get_set_definitions,
	/* tp_base */
	&pylnk_data_block_type_object,
	/* tp_dict */
	0,
	/* tp_descr_get */
	0,
	/* tp_descr_set */
	0,
	/* tp_dictoffset */
	0,
	/* tp_init */
	0,
	/* tp_alloc */
	0,
	/* tp_new */
	0,
	/* tp_free */
	0,
	/* tp_is_gc */
	0,
	/* tp_bases */
	NULL,
	/* tp_mro */
	NULL,
	/* tp_cache */
	NULL,
	/* tp_subclasses */
	NULL,
	/* tp_weaklist */
	NULL,
	/* tp_del */
	0
};

/* Retrieves the string
 * Returns a Python object if successful or NULL on error
 */
PyObject *pylnk_strings_data_block_get_string(
           pylnk_data_block_t *pylnk_data_block,
           PyObject *arguments PYLNK_ATTRIBUTE_UNUSED )
{
	PyObject *string_object  = NULL;
	libcerror_error_t *error = NULL;
	const char *errors       = NULL;
	static char *function    = "pylnk_strings_data_block_get_string";
	char *utf8_string        = NULL;
	size_t utf8_string_size  = 0;
	int result               = 0;

	PYLNK_UNREFERENCED_PARAMETER( arguments )

	if( pylnk_data_block == NULL )
	{
		PyErr_Format(
		 PyExc_ValueError,
		 "%s: invalid data_block.",
		 function );

		return( NULL );
	}
	Py_BEGIN_ALLOW_THREADS

	result = liblnk_strings_data_block_get_utf8_string_size(
	          pylnk_data_block->data_block,
	          &utf8_string_size,
	          &error );

	Py_END_ALLOW_THREADS

	if( result == -1 )
	{
		pylnk_error_raise(
		 error,
		 PyExc_IOError,
		 "%s: unable to determine size of UTF-8 string.",
		 function );

		libcerror_error_free(
		 &error );

		goto on_error;
	}
	else if( ( result == 0 )
	      || ( utf8_string_size == 0 ) )
	{
		Py_IncRef(
		 Py_None );

		return( Py_None );
	}
	utf8_string = (char *) PyMem_Malloc(
	                        sizeof( char ) * utf8_string_size );

	if( utf8_string == NULL )
	{
		PyErr_Format(
		 PyExc_MemoryError,
		 "%s: unable to create UTF-8 string.",
		 function );

		goto on_error;
	}
	Py_BEGIN_ALLOW_THREADS

	result = liblnk_strings_data_block_get_utf8_string(
	          pylnk_data_block->data_block,
	          (uint8_t *) utf8_string,
	          utf8_string_size,
	          &error );

	Py_END_ALLOW_THREADS

	if( result != 1 )
	{
		pylnk_error_raise(
		 error,
		 PyExc_IOError,
		 "%s: unable to retrieve UTF-8 string.",
		 function );

		libcerror_error_free(
		 &error );

		goto on_error;
	}
	/* Pass the string length to PyUnicode_DecodeUTF8 otherwise it makes
	 * the end of string character is part of the string
	 */
	string_object = PyUnicode_DecodeUTF8(
	                 utf8_string,
	                 (Py_ssize_t) utf8_string_size - 1,
	                 errors );

	if( string_object == NULL )
	{
		PyErr_Format(
		 PyExc_IOError,
		 "%s: unable to convert UTF-8 string into Unicode object.",
		 function );

		goto on_error;
	}
	PyMem_Free(
	 utf8_string );

	return( string_object );

on_error:
	if( utf8_string != NULL )
	{
		PyMem_Free(
		 utf8_string );
	}
	return( NULL );
}

