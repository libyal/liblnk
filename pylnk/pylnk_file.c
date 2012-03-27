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

#include <common.h>
#include <memory.h>
#include <types.h>

#include <libcstring.h>
#include <liberror.h>

#if defined( HAVE_STDLIB_H ) || defined( HAVE_WINAPI )
#include <stdlib.h>
#endif

#include "pylnk.h"
#include "pylnk_codepage.h"
#include "pylnk_datetime.h"
#include "pylnk_file.h"
#include "pylnk_file_object_io_handle.h"
#include "pylnk_libbfio.h"
#include "pylnk_liblnk.h"
#include "pylnk_python.h"

#if !defined( LIBLNK_HAVE_BFIO )
LIBLNK_EXTERN \
int liblnk_file_open_file_io_handle(
     liblnk_file_t *file,
     libbfio_handle_t *file_io_handle,
     int access_flags,
     liblnk_error_t **error );
#endif

PyMethodDef pylnk_file_object_methods[] = {

	{ "signal_abort",
	  (PyCFunction) pylnk_file_signal_abort,
	  METH_NOARGS,
	  "signal_abort() -> None\n"
	  "\n"
	  "Signals the file to abort the current activity" },

	/* Functions to access the file */

	{ "open",
	  (PyCFunction) pylnk_file_open,
	  METH_VARARGS | METH_KEYWORDS,
	  "open(filename, access_flags) -> None\n"
	  "\n"
	  "Opens a file" },

	{ "open_file_object",
	  (PyCFunction) pylnk_file_open_file_object,
	  METH_VARARGS | METH_KEYWORDS,
	  "open(file_object, access_flags) -> None\n"
	  "\n"
	  "Opens a file using a file-like object" },

	{ "close",
	  (PyCFunction) pylnk_file_close,
	  METH_NOARGS,
	  "close() -> None\n"
	  "\n"
	  "Closes a file" },

	{ "get_ascii_codepage",
	  (PyCFunction) pylnk_file_get_ascii_codepage,
	  METH_NOARGS,
	  "get_ascii_codepage() -> String\n"
	  "\n"
	  "Returns the codepage used for ASCII strings in the file" },

	{ "set_ascii_codepage",
	  (PyCFunction) pylnk_file_set_ascii_codepage,
	  METH_VARARGS | METH_KEYWORDS,
	  "set_ascii_codepage(codepage) -> None\n"
	  "\n"
	  "Set the codepage used for ASCII strings in the file\n"
	  "Expects the codepage to be a String containing a Python codec definition" },

	/* Functions to access the metadata */

	{ "get_file_creation_time",
	  (PyCFunction) pylnk_file_get_file_creation_time,
	  METH_NOARGS,
	  "get_file_creation_time() -> Datetime\n"
	  "\n"
	  "Returns the creation date and time of the linked file" },

	{ "get_file_modification_time",
	  (PyCFunction) pylnk_file_get_file_modification_time,
	  METH_NOARGS,
	  "get_file_modification_time() -> Datetime\n"
	  "\n"
	  "Returns the modification date and time of the linked file" },

	{ "get_file_access_time",
	  (PyCFunction) pylnk_file_get_file_access_time,
	  METH_NOARGS,
	  "get_file_access_time() -> Datetime\n"
	  "\n"
	  "Returns the access date and time of the linked file" },

	{ "get_local_path",
	  (PyCFunction) pylnk_file_get_local_path,
	  METH_NOARGS,
	  "get_local_path() -> Unicode string or None\n"
	  "\n"
	  "Returns the local path of the linked file" },

	{ "get_network_path",
	  (PyCFunction) pylnk_file_get_network_path,
	  METH_NOARGS,
	  "get_network_path() -> Unicode string or None\n"
	  "\n"
	  "Returns the network path of the linked file" },

	{ "get_description",
	  (PyCFunction) pylnk_file_get_description,
	  METH_NOARGS,
	  "get_description() -> Unicode string or None\n"
	  "\n"
	  "Returns the description of the linked file" },

	{ "get_relative_path",
	  (PyCFunction) pylnk_file_get_relative_path,
	  METH_NOARGS,
	  "get_relative_path() -> Unicode string or None\n"
	  "\n"
	  "Returns the relative path of the linked file" },

	{ "get_working_directory",
	  (PyCFunction) pylnk_file_get_working_directory,
	  METH_NOARGS,
	  "get_working_directory() -> Unicode string or None\n"
	  "\n"
	  "Returns the working directory of the linked file" },

	{ "get_command_line_arguments",
	  (PyCFunction) pylnk_file_get_command_line_arguments,
	  METH_NOARGS,
	  "get_command_line_arguments() -> Unicode string or None\n"
	  "\n"
	  "Returns the command line arguments of the linked file" },

	{ "get_icon_location",
	  (PyCFunction) pylnk_file_get_icon_location,
	  METH_NOARGS,
	  "get_icon_location() -> Unicode string or None\n"
	  "\n"
	  "Returns the icon location of the linked file" },

	{ "get_environment_variables_location",
	  (PyCFunction) pylnk_file_get_environment_variables_location,
	  METH_NOARGS,
	  "get_environment_variables_location() -> Unicode string or None\n"
	  "\n"
	  "Returns the environment variables location of the linked file" },

	/* Sentinel */
	{ NULL, NULL, 0, NULL }
};

PyGetSetDef pylnk_file_object_get_set_definitions[] = {

	{ "ascii_codepage",
	  (getter) pylnk_file_get_ascii_codepage,
	  (setter) 0,
	  "The codepage used for ASCII strings in the file",
	  NULL },

	{ "file_creation_time",
	  (getter) pylnk_file_get_file_creation_time,
	  (setter) 0,
	  "The creation date and time of the linked file",
	  NULL },

	{ "file_modification_time",
	  (getter) pylnk_file_get_file_modification_time,
	  (setter) 0,
	  "The modification date and time of the linked file",
	  NULL },

	{ "file_access_time",
	  (getter) pylnk_file_get_file_access_time,
	  (setter) 0,
	  "The access date and time of the linked file",
	  NULL },

	{ "local_path",
	  (getter) pylnk_file_get_local_path,
	  (setter) 0,
	  "The local path of the linked file",
	  NULL },

	{ "network_path",
	  (getter) pylnk_file_get_network_path,
	  (setter) 0,
	  "The network path of the linked file",
	  NULL },

	{ "description",
	  (getter) pylnk_file_get_description,
	  (setter) 0,
	  "The descriptioni of the linked file",
	  NULL },

	{ "relative_path",
	  (getter) pylnk_file_get_relative_path,
	  (setter) 0,
	  "The relative path of the linked file",
	  NULL },

	{ "working_directory",
	  (getter) pylnk_file_get_working_directory,
	  (setter) 0,
	  "The working directory of the linked file",
	  NULL },

	{ "command_line_arguments",
	  (getter) pylnk_file_get_command_line_arguments,
	  (setter) 0,
	  "The command line arguments of the linked file",
	  NULL },

	{ "icon_location",
	  (getter) pylnk_file_get_icon_location,
	  (setter) 0,
	  "The icon location of the linked file",
	  NULL },

	{ "environment_variables",
	  (getter) pylnk_file_get_environment_variables_location,
	  (setter) 0,
	  "The environment variables location of the linked file",
	  NULL },

	/* Sentinel */
	{ NULL, NULL, NULL, NULL, NULL }
};

PyTypeObject pylnk_file_type_object = {
	PyObject_HEAD_INIT( NULL )

	/* ob_size */
	0,
	/* tp_name */
	"pylnk.file",
	/* tp_basicsize */
	sizeof( pylnk_file_t ),
	/* tp_itemsize */
	0,
	/* tp_dealloc */
	(destructor) pylnk_file_free,
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
	"pylnk file object (wraps liblnk_file_t)",
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
	pylnk_file_object_methods,
	/* tp_members */
	0,
	/* tp_getset */
	pylnk_file_object_get_set_definitions,
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
	(initproc) pylnk_file_init,
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

/* Creates a new file object
 * Returns a Python object if successful or NULL on error
 */
PyObject *pylnk_file_new(
           PyObject *self )
{
	pylnk_file_t *pylnk_file = NULL;
	static char *function      = "pylnk_file_new";

	pylnk_file = PyObject_New(
	              struct pylnk_file,
	              &pylnk_file_type_object );

	if( pylnk_file == NULL )
	{
		PyErr_Format(
		 PyExc_MemoryError,
		 "%s: unable to initialize file.",
		 function );

		return( NULL );
	}
	if( pylnk_file_init(
	     pylnk_file ) != 0 )
	{
		PyErr_Format(
		 PyExc_MemoryError,
		 "%s: unable to initialize file.",
		 function );

		goto on_error;
	}
	return( (PyObject *) pylnk_file );

on_error:
	if( pylnk_file != NULL )
	{
		Py_DecRef(
		 (PyObject *) pylnk_file );
	}
	return( NULL );
}

/* Creates a new file object and opens it
 * Returns a Python object if successful or NULL on error
 */
PyObject *pylnk_file_new_open(
           PyObject *self,
           PyObject *arguments,
           PyObject *keywords )
{
	PyObject *pylnk_file = NULL;

	pylnk_file = pylnk_file_new(
	              self );

	pylnk_file_open(
	 (pylnk_file_t *) pylnk_file,
	 arguments,
	 keywords );

	return( pylnk_file );
}

/* Intializes a file object
 * Returns 0 if successful or -1 on error
 */
int pylnk_file_init(
     pylnk_file_t *pylnk_file )
{
	char error_string[ PYLNK_ERROR_STRING_SIZE ];

	static char *function   = "pylnk_file_init";
	liberror_error_t *error = NULL;

	if( pylnk_file == NULL )
	{
		PyErr_Format(
		 PyExc_ValueError,
		 "%s: invalid file.",
		 function );

		return( -1 );
	}
	/* Make sure liblnk file is set to NULL
	 */
	pylnk_file->file = NULL;

	if( liblnk_file_initialize(
	     &( pylnk_file->file ),
	     &error ) != 1 )
	{
		if( liberror_error_backtrace_sprint(
		     error,
		     error_string,
		     PYLNK_ERROR_STRING_SIZE ) == -1 )
                {
			PyErr_Format(
			 PyExc_MemoryError,
			 "%s: unable to initialize file.",
			 function );
		}
		else
		{
			PyErr_Format(
			 PyExc_MemoryError,
			 "%s: unable to initialize file.\n%s",
			 function,
			 error_string );
		}
		liberror_error_free(
		 &error );

		return( -1 );
	}
	return( 0 );
}

/* Frees a file object
 */
void pylnk_file_free(
      pylnk_file_t *pylnk_file )
{
	char error_string[ PYLNK_ERROR_STRING_SIZE ];

	liberror_error_t *error = NULL;
	static char *function   = "pylnk_file_free";

	if( pylnk_file == NULL )
	{
		PyErr_Format(
		 PyExc_ValueError,
		 "%s: invalid file.",
		 function );

		return;
	}
	if( pylnk_file->ob_type == NULL )
	{
		PyErr_Format(
		 PyExc_ValueError,
		 "%s: invalid file - missing ob_type.",
		 function );

		return;
	}
	if( pylnk_file->ob_type->tp_free == NULL )
	{
		PyErr_Format(
		 PyExc_ValueError,
		 "%s: invalid file - invalid ob_type - missing tp_free.",
		 function );

		return;
	}
	if( pylnk_file->file == NULL )
	{
		PyErr_Format(
		 PyExc_ValueError,
		 "%s: invalid file - missing liblnk file.",
		 function );

		return;
	}
	if( liblnk_file_free(
	     &( pylnk_file->file ),
	     &error ) != 1 )
	{
		if( liberror_error_backtrace_sprint(
		     error,
		     error_string,
		     PYLNK_ERROR_STRING_SIZE ) == -1 )
                {
			PyErr_Format(
			 PyExc_MemoryError,
			 "%s: unable to free liblnk file.",
			 function );
		}
		else
		{
			PyErr_Format(
			 PyExc_MemoryError,
			 "%s: unable to free liblnk file.\n%s",
			 function,
			 error_string );
		}
		liberror_error_free(
		 &error );
	}
	pylnk_file->ob_type->tp_free(
	 (PyObject*) pylnk_file );
}

/* Signals the file to abort the current activity
 * Returns a Python object if successful or NULL on error
 */
PyObject *pylnk_file_signal_abort(
           pylnk_file_t *pylnk_file )
{
	char error_string[ PYLNK_ERROR_STRING_SIZE ];

	liberror_error_t *error = NULL;
	static char *function   = "pylnk_file_signal_abort";
	int result              = 0;

	if( pylnk_file == NULL )
	{
		PyErr_Format(
		 PyExc_ValueError,
		 "%s: invalid file.",
		 function );

		return( NULL );
	}
	Py_BEGIN_ALLOW_THREADS

	result = liblnk_file_signal_abort(
	          pylnk_file->file,
	          &error );

	Py_END_ALLOW_THREADS

	if( result != 1 )
	{
		if( liberror_error_backtrace_sprint(
		     error,
		     error_string,
		     PYLNK_ERROR_STRING_SIZE ) == -1 )
                {
			PyErr_Format(
			 PyExc_IOError,
			 "%s: unable to signal abort.",
			 function );
		}
		else
		{
			PyErr_Format(
			 PyExc_IOError,
			 "%s: unable to signal abort.\n%s",
			 function,
			 error_string );
		}
		liberror_error_free(
		 &error );

		return( NULL );
	}
	Py_IncRef(
	 Py_None );

	return( Py_None );
}

/* Opens a file
 * Returns a Python object if successful or NULL on error
 */
PyObject *pylnk_file_open(
           pylnk_file_t *pylnk_file,
           PyObject *arguments,
           PyObject *keywords )
{
	char error_string[ PYLNK_ERROR_STRING_SIZE ];

	liberror_error_t *error     = NULL;
	char *filename              = NULL;
	static char *keyword_list[] = { "filename", "access_flags", NULL };
	static char *function       = "pylnk_file_open";
	int access_flags            = 0;
	int result                  = 0;

	if( pylnk_file == NULL )
	{
		PyErr_Format(
		 PyExc_ValueError,
		 "%s: invalid file.",
		 function );

		return( NULL );
	}
	if( PyArg_ParseTupleAndKeywords(
	     arguments,
	     keywords,
	     "s|i",
	     keyword_list,
	     &filename,
	     &access_flags ) == 0 )
        {
                return( NULL );
        }
	/* Default to read-only if no access flags were provided
	 */
	if( access_flags == 0 )
	{
		access_flags = liblnk_get_access_flags_read();
	}
	Py_BEGIN_ALLOW_THREADS

	result = liblnk_file_open(
	          pylnk_file->file,
                  filename,
                  access_flags,
	          &error );

	Py_END_ALLOW_THREADS

	if( result != 1 )
	{
		if( liberror_error_backtrace_sprint(
		     error,
		     error_string,
		     PYLNK_ERROR_STRING_SIZE ) == -1 )
                {
			PyErr_Format(
			 PyExc_IOError,
			 "%s: unable to open file.",
			 function );
		}
		else
		{
			PyErr_Format(
			 PyExc_IOError,
			 "%s: unable to open file.\n%s",
			 function,
			 error_string );
		}
		liberror_error_free(
		 &error );

		return( NULL );
	}
	Py_IncRef(
	 Py_None );

	return( Py_None );
}

/* Opens a file using a file-like object
 * Returns a Python object if successful or NULL on error
 */
PyObject *pylnk_file_open_file_object(
           pylnk_file_t *pylnk_file,
           PyObject *arguments,
           PyObject *keywords )
{
	char error_string[ PYLNK_ERROR_STRING_SIZE ];

	PyObject *file_object            = NULL;
	libbfio_handle_t *file_io_handle = NULL;
	liberror_error_t *error          = NULL;
	static char *keyword_list[]      = { "file_object", "access_flags", NULL };
	static char *function            = "pylnk_file_open_file_object";
	int access_flags                 = 0;
	int result                       = 0;

	if( pylnk_file == NULL )
	{
		PyErr_Format(
		 PyExc_ValueError,
		 "%s: invalid file.",
		 function );

		return( NULL );
	}
	if( PyArg_ParseTupleAndKeywords(
	     arguments,
	     keywords,
	     "O|i",
	     keyword_list,
	     &file_object,
	     &access_flags ) == 0 )
        {
                return( NULL );
        }
	/* Default to read-only if no access flags were provided
	 */
	if( access_flags == 0 )
	{
		access_flags = liblnk_get_access_flags_read();
	}
	if( pylnk_file_object_initialize(
	     &file_io_handle,
	     file_object,
	     &error ) != 1 )
	{
		if( liberror_error_backtrace_sprint(
		     error,
		     error_string,
		     PYLNK_ERROR_STRING_SIZE ) == -1 )
                {
			PyErr_Format(
			 PyExc_MemoryError,
			 "%s: unable to initialize file IO handle.",
			 function );
		}
		else
		{
			PyErr_Format(
			 PyExc_MemoryError,
			 "%s: unable to initialize file IO handle.\n%s",
			 function,
			 error_string );
		}
		liberror_error_free(
		 &error );

		goto on_error;
	}
	Py_BEGIN_ALLOW_THREADS

	result = liblnk_file_open_file_io_handle(
	          pylnk_file->file,
                  file_io_handle,
                  access_flags,
	          &error );

	Py_END_ALLOW_THREADS

	if( result != 1 )
	{
		if( liberror_error_backtrace_sprint(
		     error,
		     error_string,
		     PYLNK_ERROR_STRING_SIZE ) == -1 )
                {
			PyErr_Format(
			 PyExc_IOError,
			 "%s: unable to open file.",
			 function );
		}
		else
		{
			PyErr_Format(
			 PyExc_IOError,
			 "%s: unable to open file.\n%s",
			 function,
			 error_string );
		}
		liberror_error_free(
		 &error );

		goto on_error;
	}
	Py_IncRef(
	 Py_None );

	return( Py_None );

on_error:
	if( file_io_handle != NULL )
	{
		libbfio_handle_free(
		 &file_io_handle,
		 NULL );
	}
	return( NULL );
}

/* Closes a file
 * Returns a Python object if successful or NULL on error
 */
PyObject *pylnk_file_close(
           pylnk_file_t *pylnk_file )
{
	char error_string[ PYLNK_ERROR_STRING_SIZE ];

	liberror_error_t *error = NULL;
	static char *function   = "pylnk_file_close";
	int result              = 0;

	if( pylnk_file == NULL )
	{
		PyErr_Format(
		 PyExc_ValueError,
		 "%s: invalid file.",
		 function );

		return( NULL );
	}
	Py_BEGIN_ALLOW_THREADS

	result = liblnk_file_close(
	          pylnk_file->file,
	          &error );

	Py_END_ALLOW_THREADS

	if( result != 0 )
	{
		if( liberror_error_backtrace_sprint(
		     error,
		     error_string,
		     PYLNK_ERROR_STRING_SIZE ) == -1 )
                {
			PyErr_Format(
			 PyExc_IOError,
			 "%s: unable to close file.",
			 function );
		}
		else
		{
			PyErr_Format(
			 PyExc_IOError,
			 "%s: unable to close file.\n%s",
			 function,
			 error_string );
		}
		liberror_error_free(
		 &error );

		return( NULL );
	}
	Py_IncRef(
	 Py_None );

	return( Py_None );
}

/* Retrieves the codepage used for ASCII strings in the file
 * Returns a Python object holding the offset if successful or NULL on error
 */
PyObject *pylnk_file_get_ascii_codepage(
           pylnk_file_t *pylnk_file )
{
	char error_string[ PYLNK_ERROR_STRING_SIZE ];

	liberror_error_t *error     = NULL;
	PyObject *string_object     = NULL;
	const char *codepage_string = NULL;
	static char *function       = "pylnk_file_get_ascii_codepage";
	int ascii_codepage          = 0;

	if( pylnk_file == NULL )
	{
		PyErr_Format(
		 PyExc_ValueError,
		 "%s: invalid file.",
		 function );

		return( NULL );
	}
	if( liblnk_file_get_ascii_codepage(
	     pylnk_file->file,
	     &ascii_codepage,
	     &error ) != 1 )
	{
		if( liberror_error_backtrace_sprint(
		     error,
		     error_string,
		     PYLNK_ERROR_STRING_SIZE ) == -1 )
		{
			PyErr_Format(
			 PyExc_IOError,
			 "%s: unable to retrieve ASCII codepage.",
			 function );
		}
		else
		{
			PyErr_Format(
			 PyExc_IOError,
			 "%s: unable to retrieve ASCII codepage.\n%s",
			 function,
			 error_string );
		}
		liberror_error_free(
		 &error );

		return( NULL );
	}
	codepage_string = pylnk_codepage_to_string(
	                   ascii_codepage );

	if( codepage_string == NULL )
	{
		PyErr_Format(
		 PyExc_ValueError,
		 "%s: unsupported ASCII codepage: %d.",
		 function,
		 ascii_codepage );

		return( NULL );
	}
	string_object = PyString_FromString(
	                 codepage_string );

	if( string_object == NULL )
	{
		PyErr_Format(
		 PyExc_IOError,
		 "%s: unable to convert codepage string into string object.",
		 function );

		return( NULL );
	}
	return( string_object );
}

/* Sets the codepage used for ASCII strings in the file
 * Returns a Python object holding the offset if successful or NULL on error
 */
PyObject *pylnk_file_set_ascii_codepage(
           pylnk_file_t *pylnk_file,
           PyObject *arguments,
           PyObject *keywords )
{
	char error_string[ PYLNK_ERROR_STRING_SIZE ];

	liberror_error_t *error       = NULL;
	char *codepage_string         = NULL;
	static char *keyword_list[]   = { "codepage", NULL };
	static char *function         = "pylnk_file_set_ascii_codepage";
	size_t codepage_string_length = 0;
	uint32_t feature_flags        = 0;
	int ascii_codepage            = 0;

	if( pylnk_file == NULL )
	{
		PyErr_Format(
		 PyExc_ValueError,
		 "%s: invalid file.",
		 function );

		return( NULL );
	}
	if( PyArg_ParseTupleAndKeywords(
	     arguments,
	     keywords,
	     "s",
	     keyword_list,
	     &codepage_string ) == 0 )
        {
                return( NULL );
        }
	if( codepage_string == NULL )
	{
		PyErr_Format(
		 PyExc_ValueError,
		 "%s: invalid codepage string.",
		 function );

		return( NULL );
	}
	codepage_string_length = libcstring_narrow_string_length(
	                          codepage_string );

	feature_flags = PYLNK_CODEPAGE_FEATURE_FLAG_HAVE_KOI8_CODEPAGES
	              | PYLNK_CODEPAGE_FEATURE_FLAG_HAVE_WINDOWS_CODEPAGES;

	if( pylnk_codepage_from_string(
	     &ascii_codepage,
	     codepage_string,
	     codepage_string_length,
	     feature_flags,
	     &error ) != 1 )
	{
		if( liberror_error_backtrace_sprint(
		     error,
		     error_string,
		     PYLNK_ERROR_STRING_SIZE ) == -1 )
		{
			PyErr_Format(
			 PyExc_RuntimeError,
			 "%s: unable to determine ASCII codepage.",
			 function );
		}
		else
		{
			PyErr_Format(
			 PyExc_RuntimeError,
			 "%s: unable to determine ASCII codepage.\n%s",
			 function,
			 error_string );
		}
		liberror_error_free(
		 &error );

		return( NULL );
	}
	if( liblnk_file_set_ascii_codepage(
	     pylnk_file->file,
	     ascii_codepage,
	     &error ) != 1 )
	{
		if( liberror_error_backtrace_sprint(
		     error,
		     error_string,
		     PYLNK_ERROR_STRING_SIZE ) == -1 )
		{
			PyErr_Format(
			 PyExc_IOError,
			 "%s: unable to set ASCII codepage.",
			 function );
		}
		else
		{
			PyErr_Format(
			 PyExc_IOError,
			 "%s: unable to set ASCII codepage.\n%s",
			 function,
			 error_string );
		}
		liberror_error_free(
		 &error );

		return( NULL );
	}
	Py_IncRef(
	 Py_None );

	return( Py_None );
}

/* Retrieves the creation date and time of the linked file
 * Returns a Python object holding the offset if successful or NULL on error
 */
PyObject *pylnk_file_get_file_creation_time(
           pylnk_file_t *pylnk_file )
{
	char error_string[ PYLNK_ERROR_STRING_SIZE ];

	liberror_error_t *error    = NULL;
	PyObject *date_time_object = NULL;
	static char *function      = "pylnk_file_get_file_creation_time";
	uint64_t filetime          = 0;
	int result                 = 0;

	if( pylnk_file == NULL )
	{
		PyErr_Format(
		 PyExc_ValueError,
		 "%s: invalid file.",
		 function );

		return( NULL );
	}
	Py_BEGIN_ALLOW_THREADS

	result = liblnk_file_get_file_creation_time(
	          pylnk_file->file,
	          &filetime,
	          &error );

	Py_END_ALLOW_THREADS

	if( result != 1 )
	{
		if( liberror_error_backtrace_sprint(
		     error,
		     error_string,
		     PYLNK_ERROR_STRING_SIZE ) == -1 )
		{
			PyErr_Format(
			 PyExc_IOError,
			 "%s: unable to retrieve file creation time.",
			 function );
		}
		else
		{
			PyErr_Format(
			 PyExc_IOError,
			 "%s: unable to retrieve file creation time.\n%s",
			 function,
			 error_string );
		}
		liberror_error_free(
		 &error );

		return( NULL );
	}
	date_time_object = pylnk_datetime_new_from_filetime(
	                    filetime );

	return( date_time_object );
}

/* Retrieves the modification date and time of the linked file
 * Returns a Python object holding the offset if successful or NULL on error
 */
PyObject *pylnk_file_get_file_modification_time(
           pylnk_file_t *pylnk_file )
{
	char error_string[ PYLNK_ERROR_STRING_SIZE ];

	liberror_error_t *error    = NULL;
	PyObject *date_time_object = NULL;
	static char *function      = "pylnk_file_get_file_modification_time";
	uint64_t filetime          = 0;
	int result                 = 0;

	if( pylnk_file == NULL )
	{
		PyErr_Format(
		 PyExc_ValueError,
		 "%s: invalid file.",
		 function );

		return( NULL );
	}
	Py_BEGIN_ALLOW_THREADS

	result = liblnk_file_get_file_modification_time(
	          pylnk_file->file,
	          &filetime,
	          &error );

	Py_END_ALLOW_THREADS

	if( result != 1 )
	{
		if( liberror_error_backtrace_sprint(
		     error,
		     error_string,
		     PYLNK_ERROR_STRING_SIZE ) == -1 )
		{
			PyErr_Format(
			 PyExc_IOError,
			 "%s: unable to retrieve file modification time.",
			 function );
		}
		else
		{
			PyErr_Format(
			 PyExc_IOError,
			 "%s: unable to retrieve file modification time.\n%s",
			 function,
			 error_string );
		}
		liberror_error_free(
		 &error );

		return( NULL );
	}
	date_time_object = pylnk_datetime_new_from_filetime(
	                    filetime );

	return( date_time_object );
}

/* Retrieves the access date and time of the linked file
 * Returns a Python object holding the offset if successful or NULL on error
 */
PyObject *pylnk_file_get_file_access_time(
           pylnk_file_t *pylnk_file )
{
	char error_string[ PYLNK_ERROR_STRING_SIZE ];

	liberror_error_t *error    = NULL;
	PyObject *date_time_object = NULL;
	static char *function      = "pylnk_file_get_file_access_time";
	uint64_t filetime          = 0;
	int result                 = 0;

	if( pylnk_file == NULL )
	{
		PyErr_Format(
		 PyExc_ValueError,
		 "%s: invalid file.",
		 function );

		return( NULL );
	}
	Py_BEGIN_ALLOW_THREADS

	result = liblnk_file_get_file_access_time(
	          pylnk_file->file,
	          &filetime,
	          &error );

	Py_END_ALLOW_THREADS

	if( result != 1 )
	{
		if( liberror_error_backtrace_sprint(
		     error,
		     error_string,
		     PYLNK_ERROR_STRING_SIZE ) == -1 )
		{
			PyErr_Format(
			 PyExc_IOError,
			 "%s: unable to retrieve file access time.",
			 function );
		}
		else
		{
			PyErr_Format(
			 PyExc_IOError,
			 "%s: unable to retrieve file access time.\n%s",
			 function,
			 error_string );
		}
		liberror_error_free(
		 &error );

		return( NULL );
	}
	date_time_object = pylnk_datetime_new_from_filetime(
	                    filetime );

	return( date_time_object );
}

/* Retrieves the local path of the linked file
 * Returns a Python object holding the offset if successful or NULL on error
 */
PyObject *pylnk_file_get_local_path(
           pylnk_file_t *pylnk_file )
{
	char error_string[ PYLNK_ERROR_STRING_SIZE ];

	liberror_error_t *error = NULL;
	PyObject *string_object = NULL;
	static char *function   = "pylnk_file_get_local_path";
	const char *errors      = NULL;
	char *local_path        = NULL;
	size_t local_path_size  = 0;
	int result              = 0;

	if( pylnk_file == NULL )
	{
		PyErr_Format(
		 PyExc_ValueError,
		 "%s: invalid file.",
		 function );

		return( NULL );
	}
	Py_BEGIN_ALLOW_THREADS

	result = liblnk_file_get_utf8_local_path_size(
	          pylnk_file->file,
	          &local_path_size,
	          &error );

	Py_END_ALLOW_THREADS

	if( result == -1 )
	{
		if( liberror_error_backtrace_sprint(
		     error,
		     error_string,
		     PYLNK_ERROR_STRING_SIZE ) == -1 )
		{
			PyErr_Format(
			 PyExc_IOError,
			 "%s: unable to retrieve UTF-8 local path size.",
			 function );
		}
		else
		{
			PyErr_Format(
			 PyExc_IOError,
			 "%s: unable to retrieve UTF-8 local path size.\n%s",
			 function,
			 error_string );
		}
		liberror_error_free(
		 &error );

		goto on_error;
	}
	/* Check if the local path is present
	 */
	else if( ( result == 0 )
	      || ( local_path_size == 0 ) )
	{
		return( Py_None );
	}
	local_path = (char *) memory_allocate(
	                       sizeof( char ) * local_path_size );

	if( local_path == NULL )
	{
		PyErr_Format(
		 PyExc_MemoryError,
		 "%s: unable to create local path.",
		 function );

		goto on_error;
	}
	Py_BEGIN_ALLOW_THREADS

	result = liblnk_file_get_utf8_local_path(
	          pylnk_file->file,
	          (uint8_t *) local_path,
	          local_path_size,
	          &error );

	Py_END_ALLOW_THREADS

	if( result == -1 )
	{
		if( liberror_error_backtrace_sprint(
		     error,
		     error_string,
		     PYLNK_ERROR_STRING_SIZE ) == -1 )
		{
			PyErr_Format(
			 PyExc_IOError,
			 "%s: unable to retrieve UTF-8 local path.",
			 function );
		}
		else
		{
			PyErr_Format(
			 PyExc_IOError,
			 "%s: unable to retrieve UTF-8 local path.\n%s",
			 function,
			 error_string );
		}
		liberror_error_free(
		 &error );

		goto on_error;
	}
	/* Check if the local path is present
	 */
	else if( result == 0 )
	{
		memory_free(
		 local_path );

		return( Py_None );
	}
	string_object = PyUnicode_DecodeUTF8(
	                 local_path,
	                 (Py_ssize_t) local_path_size,
	                 errors );

	if( string_object == NULL )
	{
		PyErr_Format(
		 PyExc_IOError,
		 "%s: unable to convert UTF-8 local path into Unicode.",
		 function );

		goto on_error;
	}
	memory_free(
	 local_path );

	return( string_object );

on_error:
	if( local_path != NULL )
	{
		memory_free(
		 local_path );
	}
	return( NULL );
}

/* Retrieves the network path of the linked file
 * Returns a Python object holding the offset if successful or NULL on error
 */
PyObject *pylnk_file_get_network_path(
           pylnk_file_t *pylnk_file )
{
	char error_string[ PYLNK_ERROR_STRING_SIZE ];

	liberror_error_t *error  = NULL;
	PyObject *string_object  = NULL;
	static char *function    = "pylnk_file_get_network_path";
	const char *errors       = NULL;
	char *network_path       = NULL;
	size_t network_path_size = 0;
	int result               = 0;

	if( pylnk_file == NULL )
	{
		PyErr_Format(
		 PyExc_ValueError,
		 "%s: invalid file.",
		 function );

		return( NULL );
	}
	Py_BEGIN_ALLOW_THREADS

	result = liblnk_file_get_utf8_network_path_size(
	          pylnk_file->file,
	          &network_path_size,
	          &error );

	Py_END_ALLOW_THREADS

	if( result == -1 )
	{
		if( liberror_error_backtrace_sprint(
		     error,
		     error_string,
		     PYLNK_ERROR_STRING_SIZE ) == -1 )
		{
			PyErr_Format(
			 PyExc_IOError,
			 "%s: unable to retrieve UTF-8 network path size.",
			 function );
		}
		else
		{
			PyErr_Format(
			 PyExc_IOError,
			 "%s: unable to retrieve UTF-8 network path size.\n%s",
			 function,
			 error_string );
		}
		liberror_error_free(
		 &error );

		goto on_error;
	}
	/* Check if the network path is present
	 */
	else if( ( result == 0 )
	      || ( network_path_size == 0 ) )
	{
		return( Py_None );
	}
	network_path = (char *) memory_allocate(
	                         sizeof( char ) * network_path_size );

	if( network_path == NULL )
	{
		PyErr_Format(
		 PyExc_MemoryError,
		 "%s: unable to create network path.",
		 function );

		goto on_error;
	}
	Py_BEGIN_ALLOW_THREADS

	result = liblnk_file_get_utf8_network_path(
	          pylnk_file->file,
	          (uint8_t *) network_path,
	          network_path_size,
	          &error );

	Py_END_ALLOW_THREADS

	if( result == -1 )
	{
		if( liberror_error_backtrace_sprint(
		     error,
		     error_string,
		     PYLNK_ERROR_STRING_SIZE ) == -1 )
		{
			PyErr_Format(
			 PyExc_IOError,
			 "%s: unable to retrieve UTF-8 network path.",
			 function );
		}
		else
		{
			PyErr_Format(
			 PyExc_IOError,
			 "%s: unable to retrieve UTF-8 network path.\n%s",
			 function,
			 error_string );
		}
		liberror_error_free(
		 &error );

		goto on_error;
	}
	/* Check if the network path is present
	 */
	else if( result == 0 )
	{
		memory_free(
		 network_path );

		return( Py_None );
	}
	string_object = PyUnicode_DecodeUTF8(
	                 network_path,
	                 (Py_ssize_t) network_path_size,
	                 errors );

	if( string_object == NULL )
	{
		PyErr_Format(
		 PyExc_IOError,
		 "%s: unable to convert UTF-8 network path into Unicode.",
		 function );

		goto on_error;
	}
	memory_free(
	 network_path );

	return( string_object );

on_error:
	if( network_path != NULL )
	{
		memory_free(
		 network_path );
	}
	return( NULL );
}

/* Retrieves the description of the linked file
 * Returns a Python object holding the offset if successful or NULL on error
 */
PyObject *pylnk_file_get_description(
           pylnk_file_t *pylnk_file )
{
	char error_string[ PYLNK_ERROR_STRING_SIZE ];

	liberror_error_t *error  = NULL;
	PyObject *string_object  = NULL;
	static char *function    = "pylnk_file_get_description";
	const char *errors       = NULL;
	char *description        = NULL;
	size_t description_size  = 0;
	int result               = 0;

	if( pylnk_file == NULL )
	{
		PyErr_Format(
		 PyExc_ValueError,
		 "%s: invalid file.",
		 function );

		return( NULL );
	}
	Py_BEGIN_ALLOW_THREADS

	result = liblnk_file_get_utf8_description_size(
	          pylnk_file->file,
	          &description_size,
	          &error );

	Py_END_ALLOW_THREADS

	if( result == -1 )
	{
		if( liberror_error_backtrace_sprint(
		     error,
		     error_string,
		     PYLNK_ERROR_STRING_SIZE ) == -1 )
		{
			PyErr_Format(
			 PyExc_IOError,
			 "%s: unable to retrieve UTF-8 description size.",
			 function );
		}
		else
		{
			PyErr_Format(
			 PyExc_IOError,
			 "%s: unable to retrieve UTF-8 description size.\n%s",
			 function,
			 error_string );
		}
		liberror_error_free(
		 &error );

		goto on_error;
	}
	/* Check if the description is present
	 */
	else if( ( result == 0 )
	      || ( description_size == 0 ) )
	{
		return( Py_None );
	}
	description = (char *) memory_allocate(
	                        sizeof( char ) * description_size );

	if( description == NULL )
	{
		PyErr_Format(
		 PyExc_MemoryError,
		 "%s: unable to create description.",
		 function );

		goto on_error;
	}
	Py_BEGIN_ALLOW_THREADS

	result = liblnk_file_get_utf8_description(
	          pylnk_file->file,
	          (uint8_t *) description,
	          description_size,
	          &error );

	Py_END_ALLOW_THREADS

	if( result == -1 )
	{
		if( liberror_error_backtrace_sprint(
		     error,
		     error_string,
		     PYLNK_ERROR_STRING_SIZE ) == -1 )
		{
			PyErr_Format(
			 PyExc_IOError,
			 "%s: unable to retrieve UTF-8 description.",
			 function );
		}
		else
		{
			PyErr_Format(
			 PyExc_IOError,
			 "%s: unable to retrieve UTF-8 description.\n%s",
			 function,
			 error_string );
		}
		liberror_error_free(
		 &error );

		goto on_error;
	}
	/* Check if the description is present
	 */
	else if( result == 0 )
	{
		memory_free(
		 description );

		return( Py_None );
	}
	string_object = PyUnicode_DecodeUTF8(
	                 description,
	                 (Py_ssize_t) description_size,
	                 errors );

	if( string_object == NULL )
	{
		PyErr_Format(
		 PyExc_IOError,
		 "%s: unable to convert UTF-8 description into Unicode.",
		 function );

		goto on_error;
	}
	memory_free(
	 description );

	return( string_object );

on_error:
	if( description != NULL )
	{
		memory_free(
		 description );
	}
	return( NULL );
}

/* Retrieves the relative path of the linked file
 * Returns a Python object holding the offset if successful or NULL on error
 */
PyObject *pylnk_file_get_relative_path(
           pylnk_file_t *pylnk_file )
{
	char error_string[ PYLNK_ERROR_STRING_SIZE ];

	liberror_error_t *error   = NULL;
	PyObject *string_object   = NULL;
	static char *function     = "pylnk_file_get_relative_path";
	const char *errors        = NULL;
	char *relative_path       = NULL;
	size_t relative_path_size = 0;
	int result                = 0;

	if( pylnk_file == NULL )
	{
		PyErr_Format(
		 PyExc_ValueError,
		 "%s: invalid file.",
		 function );

		return( NULL );
	}
	Py_BEGIN_ALLOW_THREADS

	result = liblnk_file_get_utf8_relative_path_size(
	          pylnk_file->file,
	          &relative_path_size,
	          &error );

	Py_END_ALLOW_THREADS

	if( result == -1 )
	{
		if( liberror_error_backtrace_sprint(
		     error,
		     error_string,
		     PYLNK_ERROR_STRING_SIZE ) == -1 )
		{
			PyErr_Format(
			 PyExc_IOError,
			 "%s: unable to retrieve UTF-8 relative path size.",
			 function );
		}
		else
		{
			PyErr_Format(
			 PyExc_IOError,
			 "%s: unable to retrieve UTF-8 relative path size.\n%s",
			 function,
			 error_string );
		}
		liberror_error_free(
		 &error );

		goto on_error;
	}
	/* Check if the relative path is present
	 */
	else if( ( result == 0 )
	      || ( relative_path_size == 0 ) )
	{
		return( Py_None );
	}
	relative_path = (char *) memory_allocate(
	                          sizeof( char ) * relative_path_size );

	if( relative_path == NULL )
	{
		PyErr_Format(
		 PyExc_MemoryError,
		 "%s: unable to create relative path.",
		 function );

		goto on_error;
	}
	Py_BEGIN_ALLOW_THREADS

	result = liblnk_file_get_utf8_relative_path(
	          pylnk_file->file,
	          (uint8_t *) relative_path,
	          relative_path_size,
	          &error );

	Py_END_ALLOW_THREADS

	if( result == -1 )
	{
		if( liberror_error_backtrace_sprint(
		     error,
		     error_string,
		     PYLNK_ERROR_STRING_SIZE ) == -1 )
		{
			PyErr_Format(
			 PyExc_IOError,
			 "%s: unable to retrieve UTF-8 relative path.",
			 function );
		}
		else
		{
			PyErr_Format(
			 PyExc_IOError,
			 "%s: unable to retrieve UTF-8 relative path.\n%s",
			 function,
			 error_string );
		}
		liberror_error_free(
		 &error );

		goto on_error;
	}
	/* Check if the relative path is present
	 */
	else if( result == 0 )
	{
		memory_free(
		 relative_path );

		return( Py_None );
	}
	string_object = PyUnicode_DecodeUTF8(
	                 relative_path,
	                 (Py_ssize_t) relative_path_size,
	                 errors );

	if( string_object == NULL )
	{
		PyErr_Format(
		 PyExc_IOError,
		 "%s: unable to convert UTF-8 relative path into Unicode.",
		 function );

		goto on_error;
	}
	memory_free(
	 relative_path );

	return( string_object );

on_error:
	if( relative_path != NULL )
	{
		memory_free(
		 relative_path );
	}
	return( NULL );
}

/* Retrieves the working directory of the linked file
 * Returns a Python object holding the offset if successful or NULL on error
 */
PyObject *pylnk_file_get_working_directory(
           pylnk_file_t *pylnk_file )
{
	char error_string[ PYLNK_ERROR_STRING_SIZE ];

	liberror_error_t *error       = NULL;
	PyObject *string_object       = NULL;
	static char *function         = "pylnk_file_get_working_directory";
	const char *errors            = NULL;
	char *working_directory       = NULL;
	size_t working_directory_size = 0;
	int result                    = 0;

	if( pylnk_file == NULL )
	{
		PyErr_Format(
		 PyExc_ValueError,
		 "%s: invalid file.",
		 function );

		return( NULL );
	}
	Py_BEGIN_ALLOW_THREADS

	result = liblnk_file_get_utf8_working_directory_size(
	          pylnk_file->file,
	          &working_directory_size,
	          &error );

	Py_END_ALLOW_THREADS

	if( result == -1 )
	{
		if( liberror_error_backtrace_sprint(
		     error,
		     error_string,
		     PYLNK_ERROR_STRING_SIZE ) == -1 )
		{
			PyErr_Format(
			 PyExc_IOError,
			 "%s: unable to retrieve UTF-8 working directory size.",
			 function );
		}
		else
		{
			PyErr_Format(
			 PyExc_IOError,
			 "%s: unable to retrieve UTF-8 working directory size.\n%s",
			 function,
			 error_string );
		}
		liberror_error_free(
		 &error );

		goto on_error;
	}
	/* Check if the working directory is present
	 */
	else if( ( result == 0 )
	      || ( working_directory_size == 0 ) )
	{
		return( Py_None );
	}
	working_directory = (char *) memory_allocate(
	                              sizeof( char ) * working_directory_size );

	if( working_directory == NULL )
	{
		PyErr_Format(
		 PyExc_MemoryError,
		 "%s: unable to create working directory.",
		 function );

		goto on_error;
	}
	Py_BEGIN_ALLOW_THREADS

	result = liblnk_file_get_utf8_working_directory(
	          pylnk_file->file,
	          (uint8_t *) working_directory,
	          working_directory_size,
	          &error );

	Py_END_ALLOW_THREADS

	if( result == -1 )
	{
		if( liberror_error_backtrace_sprint(
		     error,
		     error_string,
		     PYLNK_ERROR_STRING_SIZE ) == -1 )
		{
			PyErr_Format(
			 PyExc_IOError,
			 "%s: unable to retrieve UTF-8 working directory.",
			 function );
		}
		else
		{
			PyErr_Format(
			 PyExc_IOError,
			 "%s: unable to retrieve UTF-8 working directory.\n%s",
			 function,
			 error_string );
		}
		liberror_error_free(
		 &error );

		goto on_error;
	}
	/* Check if the working directory is present
	 */
	else if( result == 0 )
	{
		memory_free(
		 working_directory );

		return( Py_None );
	}
	string_object = PyUnicode_DecodeUTF8(
	                 working_directory,
	                 (Py_ssize_t) working_directory_size,
	                 errors );

	if( string_object == NULL )
	{
		PyErr_Format(
		 PyExc_IOError,
		 "%s: unable to convert UTF-8 working directory into Unicode.",
		 function );

		goto on_error;
	}
	memory_free(
	 working_directory );

	return( string_object );

on_error:
	if( working_directory != NULL )
	{
		memory_free(
		 working_directory );
	}
	return( NULL );
}

/* Retrieves the command line arguments of the linked file
 * Returns a Python object holding the offset if successful or NULL on error
 */
PyObject *pylnk_file_get_command_line_arguments(
           pylnk_file_t *pylnk_file )
{
	char error_string[ PYLNK_ERROR_STRING_SIZE ];

	liberror_error_t *error            = NULL;
	PyObject *string_object            = NULL;
	static char *function              = "pylnk_file_get_command_line_arguments";
	const char *errors                 = NULL;
	char *command_line_arguments       = NULL;
	size_t command_line_arguments_size = 0;
	int result                         = 0;

	if( pylnk_file == NULL )
	{
		PyErr_Format(
		 PyExc_ValueError,
		 "%s: invalid file.",
		 function );

		return( NULL );
	}
	Py_BEGIN_ALLOW_THREADS

	result = liblnk_file_get_utf8_command_line_arguments_size(
	          pylnk_file->file,
	          &command_line_arguments_size,
	          &error );

	Py_END_ALLOW_THREADS

	if( result == -1 )
	{
		if( liberror_error_backtrace_sprint(
		     error,
		     error_string,
		     PYLNK_ERROR_STRING_SIZE ) == -1 )
		{
			PyErr_Format(
			 PyExc_IOError,
			 "%s: unable to retrieve UTF-8 command line arguments size.",
			 function );
		}
		else
		{
			PyErr_Format(
			 PyExc_IOError,
			 "%s: unable to retrieve UTF-8 command line arguments size.\n%s",
			 function,
			 error_string );
		}
		liberror_error_free(
		 &error );

		goto on_error;
	}
	/* Check if the command line arguments is present
	 */
	else if( ( result == 0 )
	      || ( command_line_arguments_size == 0 ) )
	{
		return( Py_None );
	}
	command_line_arguments = (char *) memory_allocate(
	                                   sizeof( char ) * command_line_arguments_size );

	if( command_line_arguments == NULL )
	{
		PyErr_Format(
		 PyExc_MemoryError,
		 "%s: unable to create command line arguments.",
		 function );

		goto on_error;
	}
	Py_BEGIN_ALLOW_THREADS

	result = liblnk_file_get_utf8_command_line_arguments(
	          pylnk_file->file,
	          (uint8_t *) command_line_arguments,
	          command_line_arguments_size,
	          &error );

	Py_END_ALLOW_THREADS

	if( result == -1 )
	{
		if( liberror_error_backtrace_sprint(
		     error,
		     error_string,
		     PYLNK_ERROR_STRING_SIZE ) == -1 )
		{
			PyErr_Format(
			 PyExc_IOError,
			 "%s: unable to retrieve UTF-8 command line arguments.",
			 function );
		}
		else
		{
			PyErr_Format(
			 PyExc_IOError,
			 "%s: unable to retrieve UTF-8 command line arguments.\n%s",
			 function,
			 error_string );
		}
		liberror_error_free(
		 &error );

		goto on_error;
	}
	/* Check if the command line arguments is present
	 */
	else if( result == 0 )
	{
		memory_free(
		 command_line_arguments );

		return( Py_None );
	}
	string_object = PyUnicode_DecodeUTF8(
	                 command_line_arguments,
	                 (Py_ssize_t) command_line_arguments_size,
	                 errors );

	if( string_object == NULL )
	{
		PyErr_Format(
		 PyExc_IOError,
		 "%s: unable to convert UTF-8 command line arguments into Unicode.",
		 function );

		goto on_error;
	}
	memory_free(
	 command_line_arguments );

	return( string_object );

on_error:
	if( command_line_arguments != NULL )
	{
		memory_free(
		 command_line_arguments );
	}
	return( NULL );
}

/* Retrieves the icon location of the linked file
 * Returns a Python object holding the offset if successful or NULL on error
 */
PyObject *pylnk_file_get_icon_location(
           pylnk_file_t *pylnk_file )
{
	char error_string[ PYLNK_ERROR_STRING_SIZE ];

	liberror_error_t *error   = NULL;
	PyObject *string_object   = NULL;
	static char *function     = "pylnk_file_get_icon_location";
	const char *errors        = NULL;
	char *icon_location       = NULL;
	size_t icon_location_size = 0;
	int result                = 0;

	if( pylnk_file == NULL )
	{
		PyErr_Format(
		 PyExc_ValueError,
		 "%s: invalid file.",
		 function );

		return( NULL );
	}
	Py_BEGIN_ALLOW_THREADS

	result = liblnk_file_get_utf8_icon_location_size(
	          pylnk_file->file,
	          &icon_location_size,
	          &error );

	Py_END_ALLOW_THREADS

	if( result == -1 )
	{
		if( liberror_error_backtrace_sprint(
		     error,
		     error_string,
		     PYLNK_ERROR_STRING_SIZE ) == -1 )
		{
			PyErr_Format(
			 PyExc_IOError,
			 "%s: unable to retrieve UTF-8 icon location size.",
			 function );
		}
		else
		{
			PyErr_Format(
			 PyExc_IOError,
			 "%s: unable to retrieve UTF-8 icon location size.\n%s",
			 function,
			 error_string );
		}
		liberror_error_free(
		 &error );

		goto on_error;
	}
	/* Check if the icon location is present
	 */
	else if( ( result == 0 )
	      || ( icon_location_size == 0 ) )
	{
		return( Py_None );
	}
	icon_location = (char *) memory_allocate(
	                          sizeof( char ) * icon_location_size );

	if( icon_location == NULL )
	{
		PyErr_Format(
		 PyExc_MemoryError,
		 "%s: unable to create icon location.",
		 function );

		goto on_error;
	}
	Py_BEGIN_ALLOW_THREADS

	result = liblnk_file_get_utf8_icon_location(
	          pylnk_file->file,
	          (uint8_t *) icon_location,
	          icon_location_size,
	          &error );

	Py_END_ALLOW_THREADS

	if( result == -1 )
	{
		if( liberror_error_backtrace_sprint(
		     error,
		     error_string,
		     PYLNK_ERROR_STRING_SIZE ) == -1 )
		{
			PyErr_Format(
			 PyExc_IOError,
			 "%s: unable to retrieve UTF-8 icon location.",
			 function );
		}
		else
		{
			PyErr_Format(
			 PyExc_IOError,
			 "%s: unable to retrieve UTF-8 icon location.\n%s",
			 function,
			 error_string );
		}
		liberror_error_free(
		 &error );

		goto on_error;
	}
	/* Check if the icon location is present
	 */
	else if( result == 0 )
	{
		memory_free(
		 icon_location );

		return( Py_None );
	}
	string_object = PyUnicode_DecodeUTF8(
	                 icon_location,
	                 (Py_ssize_t) icon_location_size,
	                 errors );

	if( string_object == NULL )
	{
		PyErr_Format(
		 PyExc_IOError,
		 "%s: unable to convert UTF-8 icon location into Unicode.",
		 function );

		goto on_error;
	}
	memory_free(
	 icon_location );

	return( string_object );

on_error:
	if( icon_location != NULL )
	{
		memory_free(
		 icon_location );
	}
	return( NULL );
}

/* Retrieves the environment variables location of the linked file
 * Returns a Python object holding the offset if successful or NULL on error
 */
PyObject *pylnk_file_get_environment_variables_location(
           pylnk_file_t *pylnk_file )
{
	char error_string[ PYLNK_ERROR_STRING_SIZE ];

	liberror_error_t *error                    = NULL;
	PyObject *string_object                    = NULL;
	static char *function                      = "pylnk_file_get_environment_variables_location";
	const char *errors                         = NULL;
	char *environment_variables_location       = NULL;
	size_t environment_variables_location_size = 0;
	int result                                 = 0;

	if( pylnk_file == NULL )
	{
		PyErr_Format(
		 PyExc_ValueError,
		 "%s: invalid file.",
		 function );

		return( NULL );
	}
	Py_BEGIN_ALLOW_THREADS

	result = liblnk_file_get_utf8_environment_variables_location_size(
	          pylnk_file->file,
	          &environment_variables_location_size,
	          &error );

	Py_END_ALLOW_THREADS

	if( result == -1 )
	{
		if( liberror_error_backtrace_sprint(
		     error,
		     error_string,
		     PYLNK_ERROR_STRING_SIZE ) == -1 )
		{
			PyErr_Format(
			 PyExc_IOError,
			 "%s: unable to retrieve UTF-8 environment variables location size.",
			 function );
		}
		else
		{
			PyErr_Format(
			 PyExc_IOError,
			 "%s: unable to retrieve UTF-8 environment variables location size.\n%s",
			 function,
			 error_string );
		}
		liberror_error_free(
		 &error );

		goto on_error;
	}
	/* Check if the environment variables location is present
	 */
	else if( ( result == 0 )
	      || ( environment_variables_location_size == 0 ) )
	{
		return( Py_None );
	}
	environment_variables_location = (char *) memory_allocate(
	                                           sizeof( char ) * environment_variables_location_size );

	if( environment_variables_location == NULL )
	{
		PyErr_Format(
		 PyExc_MemoryError,
		 "%s: unable to create environment variables location.",
		 function );

		goto on_error;
	}
	Py_BEGIN_ALLOW_THREADS

	result = liblnk_file_get_utf8_environment_variables_location(
	          pylnk_file->file,
	          (uint8_t *) environment_variables_location,
	          environment_variables_location_size,
	          &error );

	Py_END_ALLOW_THREADS

	if( result == -1 )
	{
		if( liberror_error_backtrace_sprint(
		     error,
		     error_string,
		     PYLNK_ERROR_STRING_SIZE ) == -1 )
		{
			PyErr_Format(
			 PyExc_IOError,
			 "%s: unable to retrieve UTF-8 environment variables location.",
			 function );
		}
		else
		{
			PyErr_Format(
			 PyExc_IOError,
			 "%s: unable to retrieve UTF-8 environment variables location.\n%s",
			 function,
			 error_string );
		}
		liberror_error_free(
		 &error );

		goto on_error;
	}
	/* Check if the environment variables location is present
	 */
	else if( result == 0 )
	{
		memory_free(
		 environment_variables_location );

		return( Py_None );
	}
	string_object = PyUnicode_DecodeUTF8(
	                 environment_variables_location,
	                 (Py_ssize_t) environment_variables_location_size,
	                 errors );

	if( string_object == NULL )
	{
		PyErr_Format(
		 PyExc_IOError,
		 "%s: unable to convert UTF-8 environment variables location into Unicode.",
		 function );

		goto on_error;
	}
	memory_free(
	 environment_variables_location );

	return( string_object );

on_error:
	if( environment_variables_location != NULL )
	{
		memory_free(
		 environment_variables_location );
	}
	return( NULL );
}

