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

#include <common.h>
#include <types.h>

#if defined( HAVE_STDLIB_H ) || defined( HAVE_WINAPI )
#include <stdlib.h>
#endif

#include "pylnk_data_block.h"
#include "pylnk_distributed_link_tracking_data_block.h"
#include "pylnk_error.h"
#include "pylnk_libcerror.h"
#include "pylnk_liblnk.h"
#include "pylnk_python.h"
#include "pylnk_strings_data_block.h"
#include "pylnk_unused.h"

PyMethodDef pylnk_data_block_object_methods[] = {

	{ "get_signature",
	  (PyCFunction) pylnk_data_block_get_signature,
	  METH_NOARGS,
	  "get_signature() -> Integer\n"
	  "\n"
	  "Retrieves the signature." },

	{ "get_data",
	  (PyCFunction) pylnk_data_block_get_data,
	  METH_NOARGS,
	  "get_data() -> Binary string\n"
	  "\n"
	  "Retrieves the data." },

	/* Sentinel */
	{ NULL, NULL, 0, NULL }
};

PyGetSetDef pylnk_data_block_object_get_set_definitions[] = {

	{ "signature",
	  (getter) pylnk_data_block_get_signature,
	  (setter) 0,
	  "The signature.",
	  NULL },

	{ "data",
	  (getter) pylnk_data_block_get_data,
	  (setter) 0,
	  "The data.",
	  NULL },

	/* Sentinel */
	{ NULL, NULL, NULL, NULL, NULL }
};

PyTypeObject pylnk_data_block_type_object = {
	PyVarObject_HEAD_INIT( NULL, 0 )

	/* tp_name */
	"pylnk.data_block",
	/* tp_basicsize */
	sizeof( pylnk_data_block_t ),
	/* tp_itemsize */
	0,
	/* tp_dealloc */
	(destructor) pylnk_data_block_free,
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
	"pylnk data block object (wraps liblnk_data_block_t)",
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
	pylnk_data_block_object_methods,
	/* tp_members */
	0,
	/* tp_getset */
	pylnk_data_block_object_get_set_definitions,
	/* tp_base */
	0,
	/* tp_dict */
	0,
	/* tp_descr_get */
	0,
	/* tp_descr_set */
	0,
	/* tp_dictoffset */
	0,
	/* tp_init */
	(initproc) pylnk_data_block_init,
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

/* Retrieves the data block type object
 * Returns a Python type object if successful or NULL on error
 */
PyTypeObject *pylnk_data_block_get_type_object(
               liblnk_data_block_t *data_block )
{
	libcerror_error_t *error = NULL;
	static char *function    = "pylnk_data_block_get_type_object";
	uint32_t signature       = 0;
	int result               = 0;

	if( data_block == NULL )
	{
		PyErr_Format(
		 PyExc_TypeError,
		 "%s: invalid data block.",
		 function );

		return( NULL );
	}
	Py_BEGIN_ALLOW_THREADS

	result = liblnk_data_block_get_signature(
	          data_block,
	          &signature,
	          &error );

	Py_END_ALLOW_THREADS

	if( result != 1 )
	{
		pylnk_error_raise(
		 error,
		 PyExc_IOError,
		 "%s: unable to retrieve signature.",
		 function );

		libcerror_error_free(
		 &error );

		return( NULL );
	}
	switch( signature )
	{
		case LIBLNK_DATA_BLOCK_SIGNATURE_ENVIRONMENT_VARIABLES_LOCATION:
		case LIBLNK_DATA_BLOCK_SIGNATURE_DARWIN_PROPERTIES:
		case LIBLNK_DATA_BLOCK_SIGNATURE_ICON_LOCATION:
			return( &pylnk_strings_data_block_type_object );

		case LIBLNK_DATA_BLOCK_SIGNATURE_DISTRIBUTED_LINK_TRACKER_PROPERTIES:
			return( &pylnk_distributed_link_tracking_data_block_type_object );

		default:
			break;
	}
	return( &pylnk_data_block_type_object );
}

/* Creates a new data block object
 * Returns a Python object if successful or NULL on error
 */
PyObject *pylnk_data_block_new(
           PyTypeObject *type_object,
           liblnk_data_block_t *data_block,
           PyObject *parent_object )
{
	pylnk_data_block_t *pylnk_data_block = NULL;
	static char *function                = "pylnk_data_block_new";

	if( data_block == NULL )
	{
		PyErr_Format(
		 PyExc_ValueError,
		 "%s: invalid data block.",
		 function );

		return( NULL );
	}
	/* PyObject_New does not invoke tp_init
	 */
	pylnk_data_block = PyObject_New(
	                    struct pylnk_data_block,
	                    type_object );

	if( pylnk_data_block == NULL )
	{
		PyErr_Format(
		 PyExc_MemoryError,
		 "%s: unable to initialize data block.",
		 function );

		goto on_error;
	}
	pylnk_data_block->data_block    = data_block;
	pylnk_data_block->parent_object = parent_object;

	if( pylnk_data_block->parent_object != NULL )
	{
		Py_IncRef(
		 pylnk_data_block->parent_object );
	}
	return( (PyObject *) pylnk_data_block );

on_error:
	if( pylnk_data_block != NULL )
	{
		Py_DecRef(
		 (PyObject *) pylnk_data_block );
	}
	return( NULL );
}

/* Initializes a data block object
 * Returns 0 if successful or -1 on error
 */
int pylnk_data_block_init(
     pylnk_data_block_t *pylnk_data_block )
{
	static char *function = "pylnk_data_block_init";

	if( pylnk_data_block == NULL )
	{
		PyErr_Format(
		 PyExc_ValueError,
		 "%s: invalid data block.",
		 function );

		return( -1 );
	}
	/* Make sure liblnk data block is set to NULL
	 */
	pylnk_data_block->data_block = NULL;

	PyErr_Format(
	 PyExc_NotImplementedError,
	 "%s: initialize of data block not supported.",
	 function );

	return( -1 );
}

/* Frees a data block object
 */
void pylnk_data_block_free(
      pylnk_data_block_t *pylnk_data_block )
{
	struct _typeobject *ob_type = NULL;
	libcerror_error_t *error    = NULL;
	static char *function       = "pylnk_data_block_free";
	int result                  = 0;

	if( pylnk_data_block == NULL )
	{
		PyErr_Format(
		 PyExc_ValueError,
		 "%s: invalid data block.",
		 function );

		return;
	}
	ob_type = Py_TYPE(
	           pylnk_data_block );

	if( ob_type == NULL )
	{
		PyErr_Format(
		 PyExc_ValueError,
		 "%s: missing ob_type.",
		 function );

		return;
	}
	if( ob_type->tp_free == NULL )
	{
		PyErr_Format(
		 PyExc_ValueError,
		 "%s: invalid ob_type - missing tp_free.",
		 function );

		return;
	}
	if( pylnk_data_block->data_block != NULL )
	{
		Py_BEGIN_ALLOW_THREADS

		result = liblnk_data_block_free(
		          &( pylnk_data_block->data_block ),
		          &error );

		Py_END_ALLOW_THREADS

		if( result != 1 )
		{
			pylnk_error_raise(
			 error,
			 PyExc_MemoryError,
			 "%s: unable to free liblnk data block.",
			 function );

			libcerror_error_free(
			 &error );
		}
	}
	if( pylnk_data_block->parent_object != NULL )
	{
		Py_DecRef(
		 pylnk_data_block->parent_object );
	}
	ob_type->tp_free(
	 (PyObject*) pylnk_data_block );
}

/* Retrieves the 
 * Returns a Python object if successful or NULL on error
 */
PyObject *pylnk_data_block_get_signature(
           pylnk_data_block_t *pylnk_data_block,
           PyObject *arguments PYLNK_ATTRIBUTE_UNUSED )
{
	PyObject *integer_object = NULL;
	libcerror_error_t *error = NULL;
	static char *function    = "pylnk_data_block_get_signature";
	uint32_t value_32bit     = 0;
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

	result = liblnk_data_block_get_signature(
	          pylnk_data_block->data_block,
	          &value_32bit,
	          &error );

	Py_END_ALLOW_THREADS

	if( result != 1 )
	{
		pylnk_error_raise(
		 error,
		 PyExc_IOError,
		 "%s: unable to retrieve .",
		 function );

		libcerror_error_free(
		 &error );

		return( NULL );
	}
	integer_object = PyLong_FromUnsignedLong(
	                  (unsigned long) value_32bit );

	return( integer_object );
}

/* Retrieves the 
 * Returns a Python object if successful or NULL on error
 */
PyObject *pylnk_data_block_get_data(
           pylnk_data_block_t *pylnk_data_block,
           PyObject *arguments PYLNK_ATTRIBUTE_UNUSED )
{
	PyObject *bytes_object   = NULL;
	libcerror_error_t *error = NULL;
	char *data               = NULL;
	static char *function    = "pylnk_data_block_get_data";
	size_t data_size         = 0;
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

	result = liblnk_data_block_get_data_size(
	          pylnk_data_block->data_block,
	          &data_size,
	          &error );

	Py_END_ALLOW_THREADS

	if( result == -1 )
	{
		pylnk_error_raise(
		 error,
		 PyExc_IOError,
		 "%s: unable to retrieve  size.",
		 function );

		libcerror_error_free(
		 &error );

		goto on_error;
	}
	else if( ( result == 0 )
	      || ( data_size == 0 ) )
	{
		Py_IncRef(
		 Py_None );

		return( Py_None );
	}
	data = (char *) PyMem_Malloc(
	                 sizeof( char ) * data_size );

	if( data == NULL )
	{
		PyErr_Format(
		 PyExc_MemoryError,
		 "%s: unable to create data.",
		 function );

		goto on_error;
	}
	Py_BEGIN_ALLOW_THREADS

	result = liblnk_data_block_copy_data(
	          pylnk_data_block->data_block,
	          (uint8_t *) data,
	          data_size,
	          &error );

	Py_END_ALLOW_THREADS

	if( result != 1 )
	{
		pylnk_error_raise(
		 error,
		 PyExc_IOError,
		 "%s: unable to copy .",
		 function );

		libcerror_error_free(
		 &error );

		goto on_error;
	}
	/* This is a binary string so include the full size
	 */
#if PY_MAJOR_VERSION >= 3
	bytes_object = PyBytes_FromStringAndSize(
	                data,
	                (Py_ssize_t) data_size );
#else
	bytes_object = PyString_FromStringAndSize(
	                data,
	                (Py_ssize_t) data_size );
#endif
	if( bytes_object == NULL )
	{
		PyErr_Format(
		 PyExc_IOError,
		 "%s: unable to convert data into Bytes object.",
		 function );

		goto on_error;
	}
	PyMem_Free(
	 data );

	return( bytes_object );

on_error:
	if( data != NULL )
	{
		PyMem_Free(
		 data );
	}
	return( NULL );
}

