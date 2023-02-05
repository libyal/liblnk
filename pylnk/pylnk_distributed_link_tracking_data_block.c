/*
 * Python object wrapper of liblnk_data_block_t with distributed link tracker properties
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
#include "pylnk_distributed_link_tracking_data_block.h"
#include "pylnk_guid.h"
#include "pylnk_libcerror.h"
#include "pylnk_liblnk.h"
#include "pylnk_python.h"
#include "pylnk_unused.h"

PyMethodDef pylnk_distributed_link_tracking_data_block_object_methods[] = {

	{ "get_machine_identifier",
	  (PyCFunction) pylnk_distributed_link_tracking_data_block_get_machine_identifier,
	  METH_NOARGS,
	  "get_machine_identifier() -> Unicode string or None\n"
	  "\n"
	  "Retrieves the machine identifier." },

	{ "get_droid_volume_identifier",
	  (PyCFunction) pylnk_distributed_link_tracking_data_block_get_droid_volume_identifier,
	  METH_NOARGS,
	  "get_droid_volume_identifier() -> Unicode string or None\n"
	  "\n"
	  "Retrieves the droid volume identifier." },

	{ "get_droid_distributed_link_tracking_identifier",
	  (PyCFunction) pylnk_distributed_link_tracking_data_block_get_droid_file_identifier,
	  METH_NOARGS,
	  "get_droid_file_identifier() -> Unicode string or None\n"
	  "\n"
	  "Retrieves the droid file identifier." },

	{ "get_birth_droid_volume_identifier",
	  (PyCFunction) pylnk_distributed_link_tracking_data_block_get_birth_droid_volume_identifier,
	  METH_NOARGS,
	  "get_birth_droid_volume_identifier() -> Unicode string or None\n"
	  "\n"
	  "Retrieves the birth droid volume identifier." },

	{ "get_birth_droid_file_identifier",
	  (PyCFunction) pylnk_distributed_link_tracking_data_block_get_birth_droid_file_identifier,
	  METH_NOARGS,
	  "get_birth_droid_file_identifier() -> Unicode string or None\n"
	  "\n"
	  "Retrieves the birth droid file identifier." },

	/* Sentinel */
	{ NULL, NULL, 0, NULL }
};

PyGetSetDef pylnk_distributed_link_tracking_data_block_object_get_set_definitions[] = {

	{ "machine_identifier",
	  (getter) pylnk_distributed_link_tracking_data_block_get_machine_identifier,
	  (setter) 0,
	  "The machine identifier.",
	  NULL },

	{ "droid_volume_identifier",
	  (getter) pylnk_distributed_link_tracking_data_block_get_droid_volume_identifier,
	  (setter) 0,
	  "The droid volume identifier.",
	  NULL },

	{ "droid_file_identifier",
	  (getter) pylnk_distributed_link_tracking_data_block_get_droid_file_identifier,
	  (setter) 0,
	  "The droid file identifier.",
	  NULL },

	{ "birth_droid_volume_identifier",
	  (getter) pylnk_distributed_link_tracking_data_block_get_birth_droid_volume_identifier,
	  (setter) 0,
	  "The birth droid volume identifier.",
	  NULL },

	{ "birth_droid_file_identifier",
	  (getter) pylnk_distributed_link_tracking_data_block_get_birth_droid_file_identifier,
	  (setter) 0,
	  "The birth droid file identifier.",
	  NULL },

	/* Sentinel */
	{ NULL, NULL, NULL, NULL, NULL }
};

PyTypeObject pylnk_distributed_link_tracking_data_block_type_object = {
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
	"pylnk strings_data_block object (wraps liblnk_data_block_t with distributed link tracker properties)",
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
	pylnk_distributed_link_tracking_data_block_object_methods,
	/* tp_members */
	0,
	/* tp_getset */
	pylnk_distributed_link_tracking_data_block_object_get_set_definitions,
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

/* Retrieves the machine identifier
 * Returns a Python object if successful or NULL on error
 */
PyObject *pylnk_distributed_link_tracking_data_block_get_machine_identifier(
           pylnk_data_block_t *pylnk_data_block,
           PyObject *arguments PYLNK_ATTRIBUTE_UNUSED )
{
	PyObject *string_object  = NULL;
	libcerror_error_t *error = NULL;
	const char *errors       = NULL;
	static char *function    = "pylnk_distributed_link_tracking_data_block_get_machine_identifier";
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

	result = liblnk_distributed_link_tracking_data_block_get_utf8_machine_identifier_size(
	          pylnk_data_block->data_block,
	          &utf8_string_size,
	          &error );

	Py_END_ALLOW_THREADS

	if( result == -1 )
	{
		pylnk_error_raise(
		 error,
		 PyExc_IOError,
		 "%s: unable to determine size of machine identifier as UTF-8 string.",
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

	result = liblnk_distributed_link_tracking_data_block_get_utf8_machine_identifier(
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
		 "%s: unable to retrieve machine identifier as UTF-8 string.",
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

/* Retrieves the droid volume identifier
 * Returns a Python object if successful or NULL on error
 */
PyObject *pylnk_distributed_link_tracking_data_block_get_droid_volume_identifier(
           pylnk_data_block_t *pylnk_data_block,
           PyObject *arguments PYLNK_ATTRIBUTE_UNUSED )
{
	uint8_t guid_data[ 16 ];

	PyObject *string_object  = NULL;
	libcerror_error_t *error = NULL;
	static char *function    = "pylnk_distributed_link_tracking_data_block_get_droid_volume_identifier";
	int result               = 0;

	PYLNK_UNREFERENCED_PARAMETER( arguments )

	if( pylnk_data_block == NULL )
	{
		PyErr_Format(
		 PyExc_ValueError,
		 "%s: invalid data block.",
		 function );

		return( NULL );
	}
	Py_BEGIN_ALLOW_THREADS

	result = liblnk_distributed_link_tracking_data_block_get_droid_volume_identifier(
	          pylnk_data_block->data_block,
	          guid_data,
	          16,
	          &error );

	Py_END_ALLOW_THREADS

	if( result == -1 )
	{
		pylnk_error_raise(
		 error,
		 PyExc_IOError,
		 "%s: unable to retrieve droid volume identifier.",
		 function );

		libcerror_error_free(
		 &error );

		return( NULL );
	}
	else if( result == 0 )
	{
		Py_IncRef(
		 Py_None );

		return( Py_None );
	}
	string_object = pylnk_string_new_from_guid(
	                 guid_data,
	                 16 );

	if( string_object == NULL )
	{
		PyErr_Format(
		 PyExc_IOError,
		 "%s: unable to convert GUID into Unicode object.",
		 function );

		return( NULL );
	}
	return( string_object );
}

/* Retrieves the droid file identifier
 * Returns a Python object if successful or NULL on error
 */
PyObject *pylnk_distributed_link_tracking_data_block_get_droid_file_identifier(
           pylnk_data_block_t *pylnk_data_block,
           PyObject *arguments PYLNK_ATTRIBUTE_UNUSED )
{
	uint8_t guid_data[ 16 ];

	PyObject *string_object  = NULL;
	libcerror_error_t *error = NULL;
	static char *function    = "pylnk_distributed_link_tracking_data_block_get_droid_file_identifier";
	int result               = 0;

	PYLNK_UNREFERENCED_PARAMETER( arguments )

	if( pylnk_data_block == NULL )
	{
		PyErr_Format(
		 PyExc_ValueError,
		 "%s: invalid data block.",
		 function );

		return( NULL );
	}
	Py_BEGIN_ALLOW_THREADS

	result = liblnk_distributed_link_tracking_data_block_get_droid_file_identifier(
	          pylnk_data_block->data_block,
	          guid_data,
	          16,
	          &error );

	Py_END_ALLOW_THREADS

	if( result == -1 )
	{
		pylnk_error_raise(
		 error,
		 PyExc_IOError,
		 "%s: unable to retrieve droid file identifier.",
		 function );

		libcerror_error_free(
		 &error );

		return( NULL );
	}
	else if( result == 0 )
	{
		Py_IncRef(
		 Py_None );

		return( Py_None );
	}
	string_object = pylnk_string_new_from_guid(
	                 guid_data,
	                 16 );

	if( string_object == NULL )
	{
		PyErr_Format(
		 PyExc_IOError,
		 "%s: unable to convert GUID into Unicode object.",
		 function );

		return( NULL );
	}
	return( string_object );
}

/* Retrieves the birth droid volume identifier
 * Returns a Python object if successful or NULL on error
 */
PyObject *pylnk_distributed_link_tracking_data_block_get_birth_droid_volume_identifier(
           pylnk_data_block_t *pylnk_data_block,
           PyObject *arguments PYLNK_ATTRIBUTE_UNUSED )
{
	uint8_t guid_data[ 16 ];

	PyObject *string_object  = NULL;
	libcerror_error_t *error = NULL;
	static char *function    = "pylnk_distributed_link_tracking_data_block_get_birth_droid_volume_identifier";
	int result               = 0;

	PYLNK_UNREFERENCED_PARAMETER( arguments )

	if( pylnk_data_block == NULL )
	{
		PyErr_Format(
		 PyExc_ValueError,
		 "%s: invalid data block.",
		 function );

		return( NULL );
	}
	Py_BEGIN_ALLOW_THREADS

	result = liblnk_distributed_link_tracking_data_block_get_birth_droid_volume_identifier(
	          pylnk_data_block->data_block,
	          guid_data,
	          16,
	          &error );

	Py_END_ALLOW_THREADS

	if( result == -1 )
	{
		pylnk_error_raise(
		 error,
		 PyExc_IOError,
		 "%s: unable to retrieve birth droid volume identifier.",
		 function );

		libcerror_error_free(
		 &error );

		return( NULL );
	}
	else if( result == 0 )
	{
		Py_IncRef(
		 Py_None );

		return( Py_None );
	}
	string_object = pylnk_string_new_from_guid(
	                 guid_data,
	                 16 );

	if( string_object == NULL )
	{
		PyErr_Format(
		 PyExc_IOError,
		 "%s: unable to convert GUID into Unicode object.",
		 function );

		return( NULL );
	}
	return( string_object );
}

/* Retrieves the birth droid file identifier
 * Returns a Python object if successful or NULL on error
 */
PyObject *pylnk_distributed_link_tracking_data_block_get_birth_droid_file_identifier(
           pylnk_data_block_t *pylnk_data_block,
           PyObject *arguments PYLNK_ATTRIBUTE_UNUSED )
{
	uint8_t guid_data[ 16 ];

	PyObject *string_object  = NULL;
	libcerror_error_t *error = NULL;
	static char *function    = "pylnk_distributed_link_tracking_data_block_get_birth_droid_file_identifier";
	int result               = 0;

	PYLNK_UNREFERENCED_PARAMETER( arguments )

	if( pylnk_data_block == NULL )
	{
		PyErr_Format(
		 PyExc_ValueError,
		 "%s: invalid data block.",
		 function );

		return( NULL );
	}
	Py_BEGIN_ALLOW_THREADS

	result = liblnk_distributed_link_tracking_data_block_get_birth_droid_file_identifier(
	          pylnk_data_block->data_block,
	          guid_data,
	          16,
	          &error );

	Py_END_ALLOW_THREADS

	if( result == -1 )
	{
		pylnk_error_raise(
		 error,
		 PyExc_IOError,
		 "%s: unable to retrieve birth droid file identifier.",
		 function );

		libcerror_error_free(
		 &error );

		return( NULL );
	}
	else if( result == 0 )
	{
		Py_IncRef(
		 Py_None );

		return( Py_None );
	}
	string_object = pylnk_string_new_from_guid(
	                 guid_data,
	                 16 );

	if( string_object == NULL )
	{
		PyErr_Format(
		 PyExc_IOError,
		 "%s: unable to convert GUID into Unicode object.",
		 function );

		return( NULL );
	}
	return( string_object );
}

