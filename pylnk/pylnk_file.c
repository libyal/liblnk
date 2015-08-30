/*
 * Python object definition of the liblnk file
 *
 * Copyright (C) 2009-2015, Joachim Metz <joachim.metz@gmail.com>
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
#include <types.h>

#if defined( HAVE_STDLIB_H ) || defined( HAVE_WINAPI )
#include <stdlib.h>
#endif

#include "pylnk_codepage.h"
#include "pylnk_datetime.h"
#include "pylnk_error.h"
#include "pylnk_file.h"
#include "pylnk_file_object_io_handle.h"
#include "pylnk_guid.h"
#include "pylnk_integer.h"
#include "pylnk_libbfio.h"
#include "pylnk_libcerror.h"
#include "pylnk_libclocale.h"
#include "pylnk_libcstring.h"
#include "pylnk_liblnk.h"
#include "pylnk_python.h"
#include "pylnk_unused.h"

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
	  "Signals the file to abort the current activity." },

	/* Functions to access the file */

	{ "open",
	  (PyCFunction) pylnk_file_open,
	  METH_VARARGS | METH_KEYWORDS,
	  "open(filename, mode='r') -> None\n"
	  "\n"
	  "Opens a file." },

	{ "open_file_object",
	  (PyCFunction) pylnk_file_open_file_object,
	  METH_VARARGS | METH_KEYWORDS,
	  "open_file_object(file_object, mode='r') -> None\n"
	  "\n"
	  "Opens a file using a file-like object." },

	{ "close",
	  (PyCFunction) pylnk_file_close,
	  METH_NOARGS,
	  "close() -> None\n"
	  "\n"
	  "Closes a file." },

	{ "get_ascii_codepage",
	  (PyCFunction) pylnk_file_get_ascii_codepage,
	  METH_NOARGS,
	  "get_ascii_codepage() -> String\n"
	  "\n"
	  "Returns the codepage used for ASCII strings in the file." },

	{ "set_ascii_codepage",
	  (PyCFunction) pylnk_file_set_ascii_codepage,
	  METH_VARARGS | METH_KEYWORDS,
	  "set_ascii_codepage(codepage) -> None\n"
	  "\n"
	  "Set the codepage used for ASCII strings in the file.\n"
	  "Expects the codepage to be a String containing a Python codec definition." },

	/* Functions to access the metadata */

	{ "get_file_creation_time",
	  (PyCFunction) pylnk_file_get_file_creation_time,
	  METH_NOARGS,
	  "get_file_creation_time() -> Datetime\n"
	  "\n"
	  "Returns the creation date and time of the linked item." },

	{ "get_file_creation_time_as_integer",
	  (PyCFunction) pylnk_file_get_file_creation_time_as_integer,
	  METH_NOARGS,
	  "get_file_creation_time_as_integer() -> Integer\n"
	  "\n"
	  "Returns the creation date and time as a 64-bit integer containing a FILETIME value." },

	{ "get_file_modification_time",
	  (PyCFunction) pylnk_file_get_file_modification_time,
	  METH_NOARGS,
	  "get_file_modification_time() -> Datetime\n"
	  "\n"
	  "Returns the modification date and time of the linked item." },

	{ "get_file_modification_time_as_integer",
	  (PyCFunction) pylnk_file_get_file_modification_time_as_integer,
	  METH_NOARGS,
	  "get_file_modification_time_as_integer() -> Integer\n"
	  "\n"
	  "Returns the modification date and time as a 64-bit integer containing a FILETIME value." },

	{ "get_file_access_time",
	  (PyCFunction) pylnk_file_get_file_access_time,
	  METH_NOARGS,
	  "get_file_access_time() -> Datetime\n"
	  "\n"
	  "Returns the access date and time of the linked item." },

	{ "get_file_access_time_as_integer",
	  (PyCFunction) pylnk_file_get_file_access_time_as_integer,
	  METH_NOARGS,
	  "get_file_access_time_as_integer() -> Integer\n"
	  "\n"
	  "Returns the access date and time as a 64-bit integer containing a FILETIME value." },

	{ "get_file_size",
	  (PyCFunction) pylnk_file_get_file_size,
	  METH_NOARGS,
	  "get_file_size() -> Integer\n"
	  "\n"
	  "Returns the size of the linked item." },

	{ "get_file_attribute_flags",
	  (PyCFunction) pylnk_file_get_file_attribute_flags,
	  METH_NOARGS,
	  "get_file_attribute_flags() -> Integer\n"
	  "\n"
	  "Returns the file attribute flags of the linked item." },

	{ "get_drive_type",
	  (PyCFunction) pylnk_file_get_drive_type,
	  METH_NOARGS,
	  "get_drive_type() -> Integer or None\n"
	  "\n"
	  "Returns the drive type." },

	{ "get_drive_serial_number",
	  (PyCFunction) pylnk_file_get_drive_serial_number,
	  METH_NOARGS,
	  "get_drive_serial_number() -> Integer or None\n"
	  "\n"
	  "Returns the drive serial number." },

	{ "get_volume_label",
	  (PyCFunction) pylnk_file_get_volume_label,
	  METH_NOARGS,
	  "get_volume_label() -> Unicode string or None\n"
	  "\n"
	  "Returns the volume label." },

	{ "get_local_path",
	  (PyCFunction) pylnk_file_get_local_path,
	  METH_NOARGS,
	  "get_local_path() -> Unicode string or None\n"
	  "\n"
	  "Returns the local path of the linked item." },

	{ "get_network_path",
	  (PyCFunction) pylnk_file_get_network_path,
	  METH_NOARGS,
	  "get_network_path() -> Unicode string or None\n"
	  "\n"
	  "Returns the network path of the linked item." },

	{ "get_description",
	  (PyCFunction) pylnk_file_get_description,
	  METH_NOARGS,
	  "get_description() -> Unicode string or None\n"
	  "\n"
	  "Returns the description of the linked item." },

	{ "get_relative_path",
	  (PyCFunction) pylnk_file_get_relative_path,
	  METH_NOARGS,
	  "get_relative_path() -> Unicode string or None\n"
	  "\n"
	  "Returns the relative path of the linked item." },

	{ "get_working_directory",
	  (PyCFunction) pylnk_file_get_working_directory,
	  METH_NOARGS,
	  "get_working_directory() -> Unicode string or None\n"
	  "\n"
	  "Returns the working directory of the linked item." },

	{ "get_command_line_arguments",
	  (PyCFunction) pylnk_file_get_command_line_arguments,
	  METH_NOARGS,
	  "get_command_line_arguments() -> Unicode string or None\n"
	  "\n"
	  "Returns the command line arguments of the linked item." },

	{ "get_icon_location",
	  (PyCFunction) pylnk_file_get_icon_location,
	  METH_NOARGS,
	  "get_icon_location() -> Unicode string or None\n"
	  "\n"
	  "Returns the icon location of the linked item." },

	{ "get_environment_variables_location",
	  (PyCFunction) pylnk_file_get_environment_variables_location,
	  METH_NOARGS,
	  "get_environment_variables_location() -> Unicode string or None\n"
	  "\n"
	  "Returns the environment variables location of the linked item." },

	{ "get_link_target_identifier_data",
	  (PyCFunction) pylnk_file_get_link_target_identifier_data,
	  METH_NOARGS,
	  "get_link_target_identifier_data() -> String or None\n"
	  "\n"
	  "Returns the link target identifier data of the linked item.\n"
	  "The string contains a shell item (identifier) list.\n" },

	{ "get_droid_volume_identifier",
	  (PyCFunction) pylnk_file_get_droid_volume_identifier,
	  METH_NOARGS,
	  "get_droid_volume_identifier() -> Unicode string or None\n"
	  "\n"
	  "Returns the droid volume identifier of the linked item." },

	{ "get_machine_identifier",
	  (PyCFunction) pylnk_file_get_machine_identifier,
	  METH_NOARGS,
	  "get_machine_identifier() -> Unicode string or None\n"
	  "\n"
	  "Returns the machine identifier of the linked item." },

	{ "get_droid_file_identifier",
	  (PyCFunction) pylnk_file_get_droid_file_identifier,
	  METH_NOARGS,
	  "get_droid_file_identifier() -> Unicode string or None\n"
	  "\n"
	  "Returns the droid file identifier of the linked item." },

	{ "get_birth_droid_volume_identifier",
	  (PyCFunction) pylnk_file_get_birth_droid_volume_identifier,
	  METH_NOARGS,
	  "get_droid_birth_volume_identifier() -> Unicode string or None\n"
	  "\n"
	  "Returns the birth droid volume identifier of the linked item." },

	{ "get_birth_droid_file_identifier",
	  (PyCFunction) pylnk_file_get_birth_droid_file_identifier,
	  METH_NOARGS,
	  "get_birth_droid_file_identifier() -> Unicode string or None\n"
	  "\n"
	  "Returns the birth droid file identifier of the linked item." },

	/* Sentinel */
	{ NULL, NULL, 0, NULL }
};

PyGetSetDef pylnk_file_object_get_set_definitions[] = {

	{ "ascii_codepage",
	  (getter) pylnk_file_get_ascii_codepage,
	  (setter) pylnk_file_set_ascii_codepage_setter,
	  "The codepage used for ASCII strings in the file.",
	  NULL },

	{ "file_creation_time",
	  (getter) pylnk_file_get_file_creation_time,
	  (setter) 0,
	  "The creation date and time of the linked item.",
	  NULL },

	{ "file_modification_time",
	  (getter) pylnk_file_get_file_modification_time,
	  (setter) 0,
	  "The modification date and time of the linked item.",
	  NULL },

	{ "file_access_time",
	  (getter) pylnk_file_get_file_access_time,
	  (setter) 0,
	  "The access date and time of the linked item.",
	  NULL },

	{ "file_size",
	  (getter) pylnk_file_get_file_size,
	  (setter) 0,
	  "The size of the of the linked item.",
	  NULL },

	{ "file_attribute_flags",
	  (getter) pylnk_file_get_file_attribute_flags,
	  (setter) 0,
	  "The file attribute flags of the linked item.",
	  NULL },

	{ "drive_type",
	  (getter) pylnk_file_get_drive_type,
	  (setter) 0,
	  "The drive type.",
	  NULL },

	{ "drive_serial_number",
	  (getter) pylnk_file_get_drive_serial_number,
	  (setter) 0,
	  "The drive serial number.",
	  NULL },

	{ "volume_label",
	  (getter) pylnk_file_get_volume_label,
	  (setter) 0,
	  "The volume label.",
	  NULL },

	{ "local_path",
	  (getter) pylnk_file_get_local_path,
	  (setter) 0,
	  "The local path of the linked item.",
	  NULL },

	{ "network_path",
	  (getter) pylnk_file_get_network_path,
	  (setter) 0,
	  "The network path of the linked item.",
	  NULL },

	{ "description",
	  (getter) pylnk_file_get_description,
	  (setter) 0,
	  "The description of the linked item.",
	  NULL },

	{ "relative_path",
	  (getter) pylnk_file_get_relative_path,
	  (setter) 0,
	  "The relative path of the linked item.",
	  NULL },

	{ "working_directory",
	  (getter) pylnk_file_get_working_directory,
	  (setter) 0,
	  "The working directory of the linked item.",
	  NULL },

	{ "command_line_arguments",
	  (getter) pylnk_file_get_command_line_arguments,
	  (setter) 0,
	  "The command line arguments of the linked item.",
	  NULL },

	{ "icon_location",
	  (getter) pylnk_file_get_icon_location,
	  (setter) 0,
	  "The icon location of the linked item.",
	  NULL },

	{ "environment_variables_location",
	  (getter) pylnk_file_get_environment_variables_location,
	  (setter) 0,
	  "The environment variables location of the linked item.",
	  NULL },

	{ "link_target_identifier_data",
	  (getter) pylnk_file_get_link_target_identifier_data,
	  (setter) 0,
	  "The link target identifier data of the linked item.\n"
	  "The string contains a shell item (identifier) list.",
	  NULL },

	{ "droid_volume_identifier",
	  (getter) pylnk_file_get_droid_volume_identifier,
	  (setter) 0,
	  "The droid volume identifier of the linked item.",
	  NULL },

	{ "machine_identifier",
	  (getter) pylnk_file_get_machine_identifier,
	  (setter) 0,
	  "The machine identifier of the linked item.",
	  NULL },

	{ "droid_file_identifier",
	  (getter) pylnk_file_get_droid_file_identifier,
	  (setter) 0,
	  "The droid file identifier of the linked item.",
	  NULL },

	{ "birth_droid_volume_identifier",
	  (getter) pylnk_file_get_birth_droid_volume_identifier,
	  (setter) 0,
	  "The birth droid volume identifier of the linked item.",
	  NULL },

	{ "birth_droid_file_identifier",
	  (getter) pylnk_file_get_birth_droid_file_identifier,
	  (setter) 0,
	  "The birth droid file identifier of the linked item.",
	  NULL },

	/* Sentinel */
	{ NULL, NULL, NULL, NULL, NULL }
};

PyTypeObject pylnk_file_type_object = {
	PyVarObject_HEAD_INIT( NULL, 0 )

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
           void )
{
	pylnk_file_t *pylnk_file = NULL;
	static char *function    = "pylnk_file_new";

	pylnk_file = PyObject_New(
	              struct pylnk_file,
	              &pylnk_file_type_object );

	if( pylnk_file == NULL )
	{
		PyErr_Format(
		 PyExc_MemoryError,
		 "%s: unable to initialize file.",
		 function );

		goto on_error;
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
           PyObject *self PYLNK_ATTRIBUTE_UNUSED,
           PyObject *arguments,
           PyObject *keywords )
{
	PyObject *pylnk_file = NULL;

	PYLNK_UNREFERENCED_PARAMETER( self )

	pylnk_file = pylnk_file_new();

	pylnk_file_open(
	 (pylnk_file_t *) pylnk_file,
	 arguments,
	 keywords );

	return( pylnk_file );
}

/* Creates a new file object and opens it
 * Returns a Python object if successful or NULL on error
 */
PyObject *pylnk_file_new_open_file_object(
           PyObject *self PYLNK_ATTRIBUTE_UNUSED,
           PyObject *arguments,
           PyObject *keywords )
{
	PyObject *pylnk_file = NULL;

	PYLNK_UNREFERENCED_PARAMETER( self )

	pylnk_file = pylnk_file_new();

	pylnk_file_open_file_object(
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
	static char *function    = "pylnk_file_init";
	libcerror_error_t *error = NULL;

	if( pylnk_file == NULL )
	{
		PyErr_Format(
		 PyExc_ValueError,
		 "%s: invalid file.",
		 function );

		return( -1 );
	}
	pylnk_file->file           = NULL;
	pylnk_file->file_io_handle = NULL;

	if( liblnk_file_initialize(
	     &( pylnk_file->file ),
	     &error ) != 1 )
	{
		pylnk_error_raise(
		 error,
		 PyExc_MemoryError,
		 "%s: unable to initialize file.",
		 function );

		libcerror_error_free(
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
	libcerror_error_t *error    = NULL;
	struct _typeobject *ob_type = NULL;
	static char *function       = "pylnk_file_free";
	int result                  = 0;

	if( pylnk_file == NULL )
	{
		PyErr_Format(
		 PyExc_ValueError,
		 "%s: invalid file.",
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
	ob_type = Py_TYPE(
	           pylnk_file );

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
	Py_BEGIN_ALLOW_THREADS

	result = liblnk_file_free(
	          &( pylnk_file->file ),
	          &error );

	Py_END_ALLOW_THREADS

	if( result != 1 )
	{
		pylnk_error_raise(
		 error,
		 PyExc_MemoryError,
		 "%s: unable to free liblnk file.",
		 function );

		libcerror_error_free(
		 &error );
	}
	ob_type->tp_free(
	 (PyObject*) pylnk_file );
}

/* Signals the file to abort the current activity
 * Returns a Python object if successful or NULL on error
 */
PyObject *pylnk_file_signal_abort(
           pylnk_file_t *pylnk_file,
           PyObject *arguments PYLNK_ATTRIBUTE_UNUSED )
{
	libcerror_error_t *error = NULL;
	static char *function    = "pylnk_file_signal_abort";
	int result               = 0;

	PYLNK_UNREFERENCED_PARAMETER( arguments )

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
		pylnk_error_raise(
		 error,
		 PyExc_IOError,
		 "%s: unable to signal abort.",
		 function );

		libcerror_error_free(
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
	PyObject *string_object      = NULL;
	libcerror_error_t *error     = NULL;
	static char *function        = "pylnk_file_open";
	static char *keyword_list[]  = { "filename", "mode", NULL };
	const char *filename_narrow  = NULL;
	char *mode                   = NULL;
	int result                   = 0;

#if defined( LIBCSTRING_HAVE_WIDE_SYSTEM_CHARACTER )
	const wchar_t *filename_wide = NULL;
#else
	PyObject *utf8_string_object = NULL;
#endif

	if( pylnk_file == NULL )
	{
		PyErr_Format(
		 PyExc_ValueError,
		 "%s: invalid file.",
		 function );

		return( NULL );
	}
	/* Note that PyArg_ParseTupleAndKeywords with "s" will force Unicode strings to be converted to narrow character string.
	 * On Windows the narrow character strings contains an extended ASCII string with a codepage. Hence we get a conversion
	 * exception. This will also fail if the default encoding is not set correctly. We cannot use "u" here either since that
	 * does not allow us to pass non Unicode string objects and Python (at least 2.7) does not seems to automatically upcast them.
	 */
	if( PyArg_ParseTupleAndKeywords(
	     arguments,
	     keywords,
	     "O|s",
	     keyword_list,
	     &string_object,
	     &mode ) == 0 )
	{
		return( NULL );
	}
	if( ( mode != NULL )
	 && ( mode[ 0 ] != 'r' ) )
	{
		PyErr_Format(
		 PyExc_ValueError,
		 "%s: unsupported mode: %s.",
		 function,
		 mode );

		return( NULL );
	}
	PyErr_Clear();

	result = PyObject_IsInstance(
	          string_object,
	          (PyObject *) &PyUnicode_Type );

	if( result == -1 )
	{
		pylnk_error_fetch_and_raise(
	         PyExc_RuntimeError,
		 "%s: unable to determine if string object is of type unicode.",
		 function );

		return( NULL );
	}
	else if( result != 0 )
	{
		PyErr_Clear();

#if defined( LIBCSTRING_HAVE_WIDE_SYSTEM_CHARACTER )
		filename_wide = (wchar_t *) PyUnicode_AsUnicode(
		                             string_object );
		Py_BEGIN_ALLOW_THREADS

		result = liblnk_file_open_wide(
		          pylnk_file->file,
	                  filename_wide,
		          LIBLNK_OPEN_READ,
		          &error );

		Py_END_ALLOW_THREADS
#else
		utf8_string_object = PyUnicode_AsUTF8String(
		                      string_object );

		if( utf8_string_object == NULL )
		{
			pylnk_error_fetch_and_raise(
			 PyExc_RuntimeError,
			 "%s: unable to convert unicode string to UTF-8.",
			 function );

			return( NULL );
		}
#if PY_MAJOR_VERSION >= 3
		filename_narrow = PyBytes_AsString(
				   utf8_string_object );
#else
		filename_narrow = PyString_AsString(
				   utf8_string_object );
#endif
		Py_BEGIN_ALLOW_THREADS

		result = liblnk_file_open(
		          pylnk_file->file,
	                  filename_narrow,
		          LIBLNK_OPEN_READ,
		          &error );

		Py_END_ALLOW_THREADS

		Py_DecRef(
		 utf8_string_object );
#endif
		if( result != 1 )
		{
			pylnk_error_raise(
			 error,
			 PyExc_IOError,
			 "%s: unable to open file.",
			 function );

			libcerror_error_free(
			 &error );

			return( NULL );
		}
		Py_IncRef(
		 Py_None );

		return( Py_None );
	}
	PyErr_Clear();

#if PY_MAJOR_VERSION >= 3
	result = PyObject_IsInstance(
		  string_object,
		  (PyObject *) &PyBytes_Type );
#else
	result = PyObject_IsInstance(
		  string_object,
		  (PyObject *) &PyString_Type );
#endif
	if( result == -1 )
	{
		pylnk_error_fetch_and_raise(
	         PyExc_RuntimeError,
		 "%s: unable to determine if string object is of type string.",
		 function );

		return( NULL );
	}
	else if( result != 0 )
	{
		PyErr_Clear();

#if PY_MAJOR_VERSION >= 3
		filename_narrow = PyBytes_AsString(
				   string_object );
#else
		filename_narrow = PyString_AsString(
				   string_object );
#endif
		Py_BEGIN_ALLOW_THREADS

		result = liblnk_file_open(
		          pylnk_file->file,
	                  filename_narrow,
		          LIBLNK_OPEN_READ,
		          &error );

		Py_END_ALLOW_THREADS

		if( result != 1 )
		{
			pylnk_error_raise(
			 error,
			 PyExc_IOError,
			 "%s: unable to open file.",
			 function );

			libcerror_error_free(
			 &error );

			return( NULL );
		}
		Py_IncRef(
		 Py_None );

		return( Py_None );
	}
	PyErr_Format(
	 PyExc_TypeError,
	 "%s: unsupported string object type.",
	 function );

	return( NULL );
}

/* Opens a file using a file-like object
 * Returns a Python object if successful or NULL on error
 */
PyObject *pylnk_file_open_file_object(
           pylnk_file_t *pylnk_file,
           PyObject *arguments,
           PyObject *keywords )
{
	PyObject *file_object       = NULL;
	libcerror_error_t *error    = NULL;
	char *mode                  = NULL;
	static char *keyword_list[] = { "file_object", "mode", NULL };
	static char *function       = "pylnk_file_open_file_object";
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
	     "O|s",
	     keyword_list,
	     &file_object,
	     &mode ) == 0 )
	{
		return( NULL );
	}
	if( ( mode != NULL )
	 && ( mode[ 0 ] != 'r' ) )
	{
		PyErr_Format(
		 PyExc_ValueError,
		 "%s: unsupported mode: %s.",
		 function,
		 mode );

		return( NULL );
	}
	if( pylnk_file_object_initialize(
	     &( pylnk_file->file_io_handle ),
	     file_object,
	     &error ) != 1 )
	{
		pylnk_error_raise(
		 error,
		 PyExc_MemoryError,
		 "%s: unable to initialize file IO handle.",
		 function );

		libcerror_error_free(
		 &error );

		goto on_error;
	}
	Py_BEGIN_ALLOW_THREADS

	result = liblnk_file_open_file_io_handle(
	          pylnk_file->file,
	          pylnk_file->file_io_handle,
	          LIBLNK_OPEN_READ,
	          &error );

	Py_END_ALLOW_THREADS

	if( result != 1 )
	{
		pylnk_error_raise(
		 error,
		 PyExc_IOError,
		 "%s: unable to open file.",
		 function );

		libcerror_error_free(
		 &error );

		goto on_error;
	}
	Py_IncRef(
	 Py_None );

	return( Py_None );

on_error:
	if( pylnk_file->file_io_handle != NULL )
	{
		libbfio_handle_free(
		 &( pylnk_file->file_io_handle ),
		 NULL );
	}
	return( NULL );
}

/* Closes a file
 * Returns a Python object if successful or NULL on error
 */
PyObject *pylnk_file_close(
           pylnk_file_t *pylnk_file,
           PyObject *arguments PYLNK_ATTRIBUTE_UNUSED )
{
	libcerror_error_t *error = NULL;
	static char *function    = "pylnk_file_close";
	int result               = 0;

	PYLNK_UNREFERENCED_PARAMETER( arguments )

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
		pylnk_error_raise(
		 error,
		 PyExc_IOError,
		 "%s: unable to close file.",
		 function );

		libcerror_error_free(
		 &error );

		return( NULL );
	}
	if( pylnk_file->file_io_handle != NULL )
	{
		Py_BEGIN_ALLOW_THREADS

		result = libbfio_handle_free(
		          &( pylnk_file->file_io_handle ),
		          &error );

		Py_END_ALLOW_THREADS

		if( result != 1 )
		{
			pylnk_error_raise(
			 error,
			 PyExc_IOError,
			 "%s: unable to free libbfio file IO handle.",
			 function );

			libcerror_error_free(
			 &error );

			return( NULL );
		}
	}
	Py_IncRef(
	 Py_None );

	return( Py_None );
}

/* Retrieves the codepage used for ASCII strings in the file
 * Returns a Python object if successful or NULL on error
 */
PyObject *pylnk_file_get_ascii_codepage(
           pylnk_file_t *pylnk_file,
           PyObject *arguments PYLNK_ATTRIBUTE_UNUSED )
{
	libcerror_error_t *error    = NULL;
	PyObject *string_object     = NULL;
	const char *codepage_string = NULL;
	static char *function       = "pylnk_file_get_ascii_codepage";
	int ascii_codepage          = 0;
	int result                  = 0;

	PYLNK_UNREFERENCED_PARAMETER( arguments )

	if( pylnk_file == NULL )
	{
		PyErr_Format(
		 PyExc_ValueError,
		 "%s: invalid file.",
		 function );

		return( NULL );
	}
	Py_BEGIN_ALLOW_THREADS

	result = liblnk_file_get_ascii_codepage(
	          pylnk_file->file,
	          &ascii_codepage,
	          &error );

	Py_END_ALLOW_THREADS

	if( result != 1 )
	{
		pylnk_error_raise(
		 error,
		 PyExc_IOError,
		 "%s: unable to retrieve ASCII codepage.",
		 function );

		libcerror_error_free(
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
#if PY_MAJOR_VERSION >= 3
	string_object = PyBytes_FromString(
	                 codepage_string );
#else
	string_object = PyString_FromString(
	                 codepage_string );
#endif
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
 * Returns 1 if successful or -1 on error
 */
int pylnk_file_set_ascii_codepage_from_string(
     pylnk_file_t *pylnk_file,
     const char *codepage_string )
{
	libcerror_error_t *error      = NULL;
	static char *function         = "pylnk_file_set_ascii_codepage_from_string";
	size_t codepage_string_length = 0;
	uint32_t feature_flags        = 0;
	int ascii_codepage            = 0;
	int result                    = 0;

	if( pylnk_file == NULL )
	{
		PyErr_Format(
		 PyExc_ValueError,
		 "%s: invalid file.",
		 function );

		return( -1 );
	}
	if( codepage_string == NULL )
	{
		PyErr_Format(
		 PyExc_ValueError,
		 "%s: invalid codepage string.",
		 function );

		return( -1 );
	}
	codepage_string_length = libcstring_narrow_string_length(
	                          codepage_string );

	feature_flags = LIBCLOCALE_CODEPAGE_FEATURE_FLAG_HAVE_WINDOWS;

	if( libclocale_codepage_copy_from_string(
	     &ascii_codepage,
	     codepage_string,
	     codepage_string_length,
	     feature_flags,
	     &error ) != 1 )
	{
		pylnk_error_raise(
		 error,
		 PyExc_RuntimeError,
		 "%s: unable to determine ASCII codepage.",
		 function );

		libcerror_error_free(
		 &error );

		return( -1 );
	}
	Py_BEGIN_ALLOW_THREADS

	result = liblnk_file_set_ascii_codepage(
	          pylnk_file->file,
	          ascii_codepage,
	          &error );

	Py_END_ALLOW_THREADS

	if( result != 1 )
	{
		pylnk_error_raise(
		 error,
		 PyExc_IOError,
		 "%s: unable to set ASCII codepage.",
		 function );

		libcerror_error_free(
		 &error );

		return( -1 );
	}
	return( 1 );
}

/* Sets the codepage used for ASCII strings in the file
 * Returns a Python object if successful or NULL on error
 */
PyObject *pylnk_file_set_ascii_codepage(
           pylnk_file_t *pylnk_file,
           PyObject *arguments,
           PyObject *keywords )
{
	static char *keyword_list[] = { "codepage", NULL };
	char *codepage_string       = NULL;
	int result                  = 0;

	if( PyArg_ParseTupleAndKeywords(
	     arguments,
	     keywords,
	     "s",
	     keyword_list,
	     &codepage_string ) == 0 )
	{
		return( NULL );
	}
	result = pylnk_file_set_ascii_codepage_from_string(
	          pylnk_file,
	          codepage_string );

	if( result != 1 )
	{
		return( NULL );
	}
	Py_IncRef(
	 Py_None );

	return( Py_None );
}

/* Sets the codepage used for ASCII strings in the file
 * Returns a Python object if successful or NULL on error
 */
int pylnk_file_set_ascii_codepage_setter(
     pylnk_file_t *pylnk_file,
     PyObject *string_object,
     void *closure PYLNK_ATTRIBUTE_UNUSED )
{
	PyObject *utf8_string_object = NULL;
	static char *function        = "pylnk_file_set_ascii_codepage_setter";
	char *codepage_string        = NULL;
	int result                   = 0;

	PYLNK_UNREFERENCED_PARAMETER( closure )

	PyErr_Clear();

	result = PyObject_IsInstance(
	          string_object,
	          (PyObject *) &PyUnicode_Type );

	if( result == -1 )
	{
		pylnk_error_fetch_and_raise(
	         PyExc_RuntimeError,
		 "%s: unable to determine if string object is of type unicode.",
		 function );

		return( -1 );
	}
	else if( result != 0 )
	{
		/* The codepage string should only contain ASCII characters.
		 */
		utf8_string_object = PyUnicode_AsUTF8String(
		                      string_object );

		if( utf8_string_object == NULL )
		{
			pylnk_error_fetch_and_raise(
			 PyExc_RuntimeError,
			 "%s: unable to convert unicode string to UTF-8.",
			 function );

			return( -1 );
		}
#if PY_MAJOR_VERSION >= 3
		codepage_string = PyBytes_AsString(
				   utf8_string_object );
#else
		codepage_string = PyString_AsString(
				   utf8_string_object );
#endif
		if( codepage_string == NULL )
		{
			return( -1 );
		}
		result = pylnk_file_set_ascii_codepage_from_string(
		          pylnk_file,
		          codepage_string );

		if( result != 1 )
		{
			return( -1 );
		}
		return( 0 );
	}
	PyErr_Clear();

#if PY_MAJOR_VERSION >= 3
	result = PyObject_IsInstance(
		  string_object,
		  (PyObject *) &PyBytes_Type );
#else
	result = PyObject_IsInstance(
		  string_object,
		  (PyObject *) &PyString_Type );
#endif
	if( result == -1 )
	{
		pylnk_error_fetch_and_raise(
	         PyExc_RuntimeError,
		 "%s: unable to determine if string object is of type string.",
		 function );

		return( -1 );
	}
	else if( result != 0 )
	{
#if PY_MAJOR_VERSION >= 3
		codepage_string = PyBytes_AsString(
		                   string_object );
#else
		codepage_string = PyString_AsString(
		                   string_object );
#endif
		if( codepage_string == NULL )
		{
			return( -1 );
		}
		result = pylnk_file_set_ascii_codepage_from_string(
			  pylnk_file,
			  codepage_string );

		if( result != 1 )
		{
			return( -1 );
		}
		return( 0 );
	}
	PyErr_Format(
	 PyExc_TypeError,
	 "%s: unsupported string object type.",
	 function );

	return( -1 );
}

/* Retrieves the creation date and time of the linked item
 * Returns a Python object if successful or NULL on error
 */
PyObject *pylnk_file_get_file_creation_time(
           pylnk_file_t *pylnk_file,
           PyObject *arguments PYLNK_ATTRIBUTE_UNUSED )
{
	libcerror_error_t *error   = NULL;
	PyObject *date_time_object = NULL;
	static char *function      = "pylnk_file_get_file_creation_time";
	uint64_t filetime          = 0;
	int result                 = 0;

	PYLNK_UNREFERENCED_PARAMETER( arguments )

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
		pylnk_error_raise(
		 error,
		 PyExc_IOError,
		 "%s: unable to retrieve file creation time.",
		 function );

		libcerror_error_free(
		 &error );

		return( NULL );
	}
	date_time_object = pylnk_datetime_new_from_filetime(
	                    filetime );

	return( date_time_object );
}

/* Retrieves the creation date and time as an integer
 * Returns a Python object if successful or NULL on error
 */
PyObject *pylnk_file_get_file_creation_time_as_integer(
           pylnk_file_t *pylnk_file,
           PyObject *arguments PYLNK_ATTRIBUTE_UNUSED )
{
	libcerror_error_t *error = NULL;
	PyObject *integer_object = NULL;
	static char *function    = "pylnk_file_get_file_creation_time_as_integer";
	uint64_t filetime        = 0;
	int result               = 0;

	PYLNK_UNREFERENCED_PARAMETER( arguments )

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
		pylnk_error_raise(
		 error,
		 PyExc_IOError,
		 "%s: unable to retrieve creation time.",
		 function );

		libcerror_error_free(
		 &error );

		return( NULL );
	}
	integer_object = pylnk_integer_unsigned_new_from_64bit(
	                  (uint64_t) filetime );

	return( integer_object );
}

/* Retrieves the modification date and time of the linked item
 * Returns a Python object if successful or NULL on error
 */
PyObject *pylnk_file_get_file_modification_time(
           pylnk_file_t *pylnk_file,
           PyObject *arguments PYLNK_ATTRIBUTE_UNUSED )
{
	libcerror_error_t *error   = NULL;
	PyObject *date_time_object = NULL;
	static char *function      = "pylnk_file_get_file_modification_time";
	uint64_t filetime          = 0;
	int result                 = 0;

	PYLNK_UNREFERENCED_PARAMETER( arguments )

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
		pylnk_error_raise(
		 error,
		 PyExc_IOError,
		 "%s: unable to retrieve file modification time.",
		 function );

		libcerror_error_free(
		 &error );

		return( NULL );
	}
	date_time_object = pylnk_datetime_new_from_filetime(
	                    filetime );

	return( date_time_object );
}

/* Retrieves the modification date and time as an integer
 * Returns a Python object if successful or NULL on error
 */
PyObject *pylnk_file_get_file_modification_time_as_integer(
           pylnk_file_t *pylnk_file,
           PyObject *arguments PYLNK_ATTRIBUTE_UNUSED )
{
	libcerror_error_t *error = NULL;
	PyObject *integer_object = NULL;
	static char *function    = "pylnk_file_get_file_modification_time_as_integer";
	uint64_t filetime        = 0;
	int result               = 0;

	PYLNK_UNREFERENCED_PARAMETER( arguments )

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
		pylnk_error_raise(
		 error,
		 PyExc_IOError,
		 "%s: unable to retrieve modification time.",
		 function );

		libcerror_error_free(
		 &error );

		return( NULL );
	}
	integer_object = pylnk_integer_unsigned_new_from_64bit(
	                  (uint64_t) filetime );

	return( integer_object );
}

/* Retrieves the access date and time of the linked item
 * Returns a Python object if successful or NULL on error
 */
PyObject *pylnk_file_get_file_access_time(
           pylnk_file_t *pylnk_file,
           PyObject *arguments PYLNK_ATTRIBUTE_UNUSED )
{
	libcerror_error_t *error   = NULL;
	PyObject *date_time_object = NULL;
	static char *function      = "pylnk_file_get_file_access_time";
	uint64_t filetime          = 0;
	int result                 = 0;

	PYLNK_UNREFERENCED_PARAMETER( arguments )

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
		pylnk_error_raise(
		 error,
		 PyExc_IOError,
		 "%s: unable to retrieve file access time.",
		 function );

		libcerror_error_free(
		 &error );

		return( NULL );
	}
	date_time_object = pylnk_datetime_new_from_filetime(
	                    filetime );

	return( date_time_object );
}

/* Retrieves the access date and time as an integer
 * Returns a Python object if successful or NULL on error
 */
PyObject *pylnk_file_get_file_access_time_as_integer(
           pylnk_file_t *pylnk_file,
           PyObject *arguments PYLNK_ATTRIBUTE_UNUSED )
{
	libcerror_error_t *error = NULL;
	PyObject *integer_object = NULL;
	static char *function    = "pylnk_file_get_file_access_time_as_integer";
	uint64_t filetime        = 0;
	int result               = 0;

	PYLNK_UNREFERENCED_PARAMETER( arguments )

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
		pylnk_error_raise(
		 error,
		 PyExc_IOError,
		 "%s: unable to retrieve access time.",
		 function );

		libcerror_error_free(
		 &error );

		return( NULL );
	}
	integer_object = pylnk_integer_unsigned_new_from_64bit(
	                  (uint64_t) filetime );

	return( integer_object );
}

/* Retrieves the file size
 * Returns a Python object if successful or NULL on error
 */
PyObject *pylnk_file_get_file_size(
           pylnk_file_t *pylnk_file,
           PyObject *arguments PYLNK_ATTRIBUTE_UNUSED )
{
	libcerror_error_t *error = NULL;
	PyObject *integer_object = NULL;
	static char *function    = "pylnk_file_get_file_size";
	uint32_t file_size       = 0;
	int result               = 0;

	PYLNK_UNREFERENCED_PARAMETER( arguments )

	if( pylnk_file == NULL )
	{
		PyErr_Format(
		 PyExc_TypeError,
		 "%s: invalid file.",
		 function );

		return( NULL );
	}
	Py_BEGIN_ALLOW_THREADS

	result = liblnk_file_get_file_size(
	          pylnk_file->file,
	          &file_size,
	          &error );

	Py_END_ALLOW_THREADS

	if( result != 1 )
	{
		pylnk_error_raise(
		 error,
		 PyExc_IOError,
		 "%s: unable to retrieve file size.",
		 function );

		libcerror_error_free(
		 &error );

		return( NULL );
	}
	integer_object = pylnk_integer_unsigned_new_from_64bit(
	                  (uint64_t) file_size );

	return( integer_object );
}

/* Retrieves the file attribute flags
 * Returns a Python object if successful or NULL on error
 */
PyObject *pylnk_file_get_file_attribute_flags(
           pylnk_file_t *pylnk_file,
           PyObject *arguments PYLNK_ATTRIBUTE_UNUSED )
{
	libcerror_error_t *error      = NULL;
	PyObject *integer_object      = NULL;
	static char *function         = "pylnk_file_get_file_attribute_flags";
	uint32_t file_attribute_flags = 0;
	int result                    = 0;

	PYLNK_UNREFERENCED_PARAMETER( arguments )

	if( pylnk_file == NULL )
	{
		PyErr_Format(
		 PyExc_TypeError,
		 "%s: invalid file.",
		 function );

		return( NULL );
	}
	Py_BEGIN_ALLOW_THREADS

	result = liblnk_file_get_file_attribute_flags(
	          pylnk_file->file,
	          &file_attribute_flags,
	          &error );

	Py_END_ALLOW_THREADS

	if( result != 1 )
	{
		pylnk_error_raise(
		 error,
		 PyExc_IOError,
		 "%s: unable to retrieve file attribute flags.",
		 function );

		libcerror_error_free(
		 &error );

		return( NULL );
	}
	integer_object = pylnk_integer_unsigned_new_from_64bit(
	                  (uint64_t) file_attribute_flags );

	return( integer_object );
}

/* Retrieves the drive type
 * Returns a Python object if successful or NULL on error
 */
PyObject *pylnk_file_get_drive_type(
           pylnk_file_t *pylnk_file,
           PyObject *arguments PYLNK_ATTRIBUTE_UNUSED )
{
	libcerror_error_t *error = NULL;
	PyObject *integer_object = NULL;
	static char *function    = "pylnk_file_get_drive_type";
	uint32_t drive_type      = 0;
	int result               = 0;

	PYLNK_UNREFERENCED_PARAMETER( arguments )

	if( pylnk_file == NULL )
	{
		PyErr_Format(
		 PyExc_TypeError,
		 "%s: invalid file.",
		 function );

		return( NULL );
	}
	Py_BEGIN_ALLOW_THREADS

	result = liblnk_file_get_drive_type(
	          pylnk_file->file,
	          &drive_type,
	          &error );

	Py_END_ALLOW_THREADS

	if( result == -1 )
	{
		pylnk_error_raise(
		 error,
		 PyExc_IOError,
		 "%s: unable to retrieve drive type.",
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
	integer_object = pylnk_integer_unsigned_new_from_64bit(
	                  (uint64_t) drive_type );

	return( integer_object );
}

/* Retrieves the drive serial number
 * Returns a Python object if successful or NULL on error
 */
PyObject *pylnk_file_get_drive_serial_number(
           pylnk_file_t *pylnk_file,
           PyObject *arguments PYLNK_ATTRIBUTE_UNUSED )
{
	libcerror_error_t *error     = NULL;
	PyObject *integer_object     = NULL;
	static char *function        = "pylnk_file_get_drive_serial_number";
	uint32_t drive_serial_number = 0;
	int result                   = 0;

	PYLNK_UNREFERENCED_PARAMETER( arguments )

	if( pylnk_file == NULL )
	{
		PyErr_Format(
		 PyExc_TypeError,
		 "%s: invalid file.",
		 function );

		return( NULL );
	}
	Py_BEGIN_ALLOW_THREADS

	result = liblnk_file_get_drive_serial_number(
	          pylnk_file->file,
	          &drive_serial_number,
	          &error );

	Py_END_ALLOW_THREADS

	if( result == -1 )
	{
		pylnk_error_raise(
		 error,
		 PyExc_IOError,
		 "%s: unable to retrieve drive serial number.",
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
	integer_object = pylnk_integer_unsigned_new_from_64bit(
	                  (uint64_t) drive_serial_number );

	return( integer_object );
}

/* Retrieves the volume label of the linked item
 * Returns a Python object if successful or NULL on error
 */
PyObject *pylnk_file_get_volume_label(
           pylnk_file_t *pylnk_file,
           PyObject *arguments PYLNK_ATTRIBUTE_UNUSED )
{
	libcerror_error_t *error = NULL;
	PyObject *string_object  = NULL;
	static char *function    = "pylnk_file_get_volume_label";
	const char *errors       = NULL;
	char *volume_label       = NULL;
	size_t volume_label_size = 0;
	int result               = 0;

	PYLNK_UNREFERENCED_PARAMETER( arguments )

	if( pylnk_file == NULL )
	{
		PyErr_Format(
		 PyExc_ValueError,
		 "%s: invalid file.",
		 function );

		return( NULL );
	}
	Py_BEGIN_ALLOW_THREADS

	result = liblnk_file_get_utf8_volume_label_size(
	          pylnk_file->file,
	          &volume_label_size,
	          &error );

	Py_END_ALLOW_THREADS

	if( result == -1 )
	{
		pylnk_error_raise(
		 error,
		 PyExc_IOError,
		 "%s: unable to retrieve UTF-8 volume label size.",
		 function );

		libcerror_error_free(
		 &error );

		goto on_error;
	}
	/* Check if the volume label is present
	 */
	else if( ( result == 0 )
	      || ( volume_label_size == 0 ) )
	{
		Py_IncRef(
		 Py_None );

		return( Py_None );
	}
	volume_label = (char *) PyMem_Malloc(
	                         sizeof( char ) * volume_label_size );

	if( volume_label == NULL )
	{
		PyErr_Format(
		 PyExc_MemoryError,
		 "%s: unable to create UTF-8 volume label.",
		 function );

		goto on_error;
	}
	Py_BEGIN_ALLOW_THREADS

	result = liblnk_file_get_utf8_volume_label(
	          pylnk_file->file,
	          (uint8_t *) volume_label,
	          volume_label_size,
	          &error );

	Py_END_ALLOW_THREADS

	if( result == -1 )
	{
		pylnk_error_raise(
		 error,
		 PyExc_IOError,
		 "%s: unable to retrieve UTF-8 volume label.",
		 function );

		libcerror_error_free(
		 &error );

		goto on_error;
	}
	/* Check if the volume label is present
	 */
	else if( result == 0 )
	{
		PyMem_Free(
		 volume_label );

		Py_IncRef(
		 Py_None );

		return( Py_None );
	}
	/* Pass the string length to PyUnicode_DecodeUTF8
	 * otherwise it makes the end of string character is part
	 * of the string
	 */
	string_object = PyUnicode_DecodeUTF8(
	                 volume_label,
	                 (Py_ssize_t) volume_label_size - 1,
	                 errors );

	if( string_object == NULL )
	{
		PyErr_Format(
		 PyExc_IOError,
		 "%s: unable to convert UTF-8 volume label into Unicode.",
		 function );

		goto on_error;
	}
	PyMem_Free(
	 volume_label );

	return( string_object );

on_error:
	if( volume_label != NULL )
	{
		PyMem_Free(
		 volume_label );
	}
	return( NULL );
}

/* Retrieves the local path of the linked item
 * Returns a Python object if successful or NULL on error
 */
PyObject *pylnk_file_get_local_path(
           pylnk_file_t *pylnk_file,
           PyObject *arguments PYLNK_ATTRIBUTE_UNUSED )
{
	libcerror_error_t *error = NULL;
	PyObject *string_object  = NULL;
	static char *function    = "pylnk_file_get_local_path";
	const char *errors       = NULL;
	char *local_path         = NULL;
	size_t local_path_size   = 0;
	int result               = 0;

	PYLNK_UNREFERENCED_PARAMETER( arguments )

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
		pylnk_error_raise(
		 error,
		 PyExc_IOError,
		 "%s: unable to retrieve UTF-8 local path size.",
		 function );

		libcerror_error_free(
		 &error );

		goto on_error;
	}
	/* Check if the local path is present
	 */
	else if( ( result == 0 )
	      || ( local_path_size == 0 ) )
	{
		Py_IncRef(
		 Py_None );

		return( Py_None );
	}
	local_path = (char *) PyMem_Malloc(
	                       sizeof( char ) * local_path_size );

	if( local_path == NULL )
	{
		PyErr_Format(
		 PyExc_MemoryError,
		 "%s: unable to create UTF-8 local path.",
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
		pylnk_error_raise(
		 error,
		 PyExc_IOError,
		 "%s: unable to retrieve UTF-8 local path.",
		 function );

		libcerror_error_free(
		 &error );

		goto on_error;
	}
	/* Check if the local path is present
	 */
	else if( result == 0 )
	{
		PyMem_Free(
		 local_path );

		Py_IncRef(
		 Py_None );

		return( Py_None );
	}
	/* Pass the string length to PyUnicode_DecodeUTF8
	 * otherwise it makes the end of string character is part
	 * of the string
	 */
	string_object = PyUnicode_DecodeUTF8(
	                 local_path,
	                 (Py_ssize_t) local_path_size - 1,
	                 errors );

	if( string_object == NULL )
	{
		PyErr_Format(
		 PyExc_IOError,
		 "%s: unable to convert UTF-8 local path into Unicode.",
		 function );

		goto on_error;
	}
	PyMem_Free(
	 local_path );

	return( string_object );

on_error:
	if( local_path != NULL )
	{
		PyMem_Free(
		 local_path );
	}
	return( NULL );
}

/* Retrieves the network path of the linked item
 * Returns a Python object if successful or NULL on error
 */
PyObject *pylnk_file_get_network_path(
           pylnk_file_t *pylnk_file,
           PyObject *arguments PYLNK_ATTRIBUTE_UNUSED )
{
	libcerror_error_t *error = NULL;
	PyObject *string_object  = NULL;
	static char *function    = "pylnk_file_get_network_path";
	const char *errors       = NULL;
	char *network_path       = NULL;
	size_t network_path_size = 0;
	int result               = 0;

	PYLNK_UNREFERENCED_PARAMETER( arguments )

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
		pylnk_error_raise(
		 error,
		 PyExc_IOError,
		 "%s: unable to retrieve UTF-8 network path size.",
		 function );

		libcerror_error_free(
		 &error );

		goto on_error;
	}
	/* Check if the network path is present
	 */
	else if( ( result == 0 )
	      || ( network_path_size == 0 ) )
	{
		Py_IncRef(
		 Py_None );

		return( Py_None );
	}
	network_path = (char *) PyMem_Malloc(
	                         sizeof( char ) * network_path_size );

	if( network_path == NULL )
	{
		PyErr_Format(
		 PyExc_MemoryError,
		 "%s: unable to create UTF-8 network path.",
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
		pylnk_error_raise(
		 error,
		 PyExc_IOError,
		 "%s: unable to retrieve UTF-8 network path.",
		 function );

		libcerror_error_free(
		 &error );

		goto on_error;
	}
	/* Check if the network path is present
	 */
	else if( result == 0 )
	{
		PyMem_Free(
		 network_path );

		Py_IncRef(
		 Py_None );

		return( Py_None );
	}
	/* Pass the string length to PyUnicode_DecodeUTF8
	 * otherwise it makes the end of string character is part
	 * of the string
	 */
	string_object = PyUnicode_DecodeUTF8(
	                 network_path,
	                 (Py_ssize_t) network_path_size - 1,
	                 errors );

	if( string_object == NULL )
	{
		PyErr_Format(
		 PyExc_IOError,
		 "%s: unable to convert UTF-8 network path into Unicode.",
		 function );

		goto on_error;
	}
	PyMem_Free(
	 network_path );

	return( string_object );

on_error:
	if( network_path != NULL )
	{
		PyMem_Free(
		 network_path );
	}
	return( NULL );
}

/* Retrieves the description of the linked item
 * Returns a Python object if successful or NULL on error
 */
PyObject *pylnk_file_get_description(
           pylnk_file_t *pylnk_file,
           PyObject *arguments PYLNK_ATTRIBUTE_UNUSED )
{
	libcerror_error_t *error = NULL;
	PyObject *string_object  = NULL;
	static char *function    = "pylnk_file_get_description";
	const char *errors       = NULL;
	char *description        = NULL;
	size_t description_size  = 0;
	int result               = 0;

	PYLNK_UNREFERENCED_PARAMETER( arguments )

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
		pylnk_error_raise(
		 error,
		 PyExc_IOError,
		 "%s: unable to retrieve UTF-8 description size.",
		 function );

		libcerror_error_free(
		 &error );

		goto on_error;
	}
	/* Check if the description is present
	 */
	else if( ( result == 0 )
	      || ( description_size == 0 ) )
	{
		Py_IncRef(
		 Py_None );

		return( Py_None );
	}
	description = (char *) PyMem_Malloc(
	                        sizeof( char ) * description_size );

	if( description == NULL )
	{
		PyErr_Format(
		 PyExc_MemoryError,
		 "%s: unable to create UTF-8 description.",
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
		pylnk_error_raise(
		 error,
		 PyExc_IOError,
		 "%s: unable to retrieve UTF-8 description.",
		 function );

		libcerror_error_free(
		 &error );

		goto on_error;
	}
	/* Check if the description is present
	 */
	else if( result == 0 )
	{
		PyMem_Free(
		 description );

		Py_IncRef(
		 Py_None );

		return( Py_None );
	}
	/* Pass the string length to PyUnicode_DecodeUTF8
	 * otherwise it makes the end of string character is part
	 * of the string
	 */
	string_object = PyUnicode_DecodeUTF8(
	                 description,
	                 (Py_ssize_t) description_size - 1,
	                 errors );

	if( string_object == NULL )
	{
		PyErr_Format(
		 PyExc_IOError,
		 "%s: unable to convert UTF-8 description into Unicode.",
		 function );

		goto on_error;
	}
	PyMem_Free(
	 description );

	return( string_object );

on_error:
	if( description != NULL )
	{
		PyMem_Free(
		 description );
	}
	return( NULL );
}

/* Retrieves the relative path of the linked item
 * Returns a Python object if successful or NULL on error
 */
PyObject *pylnk_file_get_relative_path(
           pylnk_file_t *pylnk_file,
           PyObject *arguments PYLNK_ATTRIBUTE_UNUSED )
{
	libcerror_error_t *error  = NULL;
	PyObject *string_object   = NULL;
	static char *function     = "pylnk_file_get_relative_path";
	const char *errors        = NULL;
	char *relative_path       = NULL;
	size_t relative_path_size = 0;
	int result                = 0;

	PYLNK_UNREFERENCED_PARAMETER( arguments )

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
		pylnk_error_raise(
		 error,
		 PyExc_IOError,
		 "%s: unable to retrieve UTF-8 relative path size.",
		 function );

		libcerror_error_free(
		 &error );

		goto on_error;
	}
	/* Check if the relative path is present
	 */
	else if( ( result == 0 )
	      || ( relative_path_size == 0 ) )
	{
		Py_IncRef(
		 Py_None );

		return( Py_None );
	}
	relative_path = (char *) PyMem_Malloc(
	                          sizeof( char ) * relative_path_size );

	if( relative_path == NULL )
	{
		PyErr_Format(
		 PyExc_MemoryError,
		 "%s: unable to create UTF-8 relative path.",
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
		pylnk_error_raise(
		 error,
		 PyExc_IOError,
		 "%s: unable to retrieve UTF-8 relative path.",
		 function );

		libcerror_error_free(
		 &error );

		goto on_error;
	}
	/* Check if the relative path is present
	 */
	else if( result == 0 )
	{
		PyMem_Free(
		 relative_path );

		Py_IncRef(
		 Py_None );

		return( Py_None );
	}
	/* Pass the string length to PyUnicode_DecodeUTF8
	 * otherwise it makes the end of string character is part
	 * of the string
	 */
	string_object = PyUnicode_DecodeUTF8(
	                 relative_path,
	                 (Py_ssize_t) relative_path_size - 1,
	                 errors );

	if( string_object == NULL )
	{
		PyErr_Format(
		 PyExc_IOError,
		 "%s: unable to convert UTF-8 relative path into Unicode.",
		 function );

		goto on_error;
	}
	PyMem_Free(
	 relative_path );

	return( string_object );

on_error:
	if( relative_path != NULL )
	{
		PyMem_Free(
		 relative_path );
	}
	return( NULL );
}

/* Retrieves the working directory of the linked item
 * Returns a Python object if successful or NULL on error
 */
PyObject *pylnk_file_get_working_directory(
           pylnk_file_t *pylnk_file,
           PyObject *arguments PYLNK_ATTRIBUTE_UNUSED )
{
	libcerror_error_t *error      = NULL;
	PyObject *string_object       = NULL;
	static char *function         = "pylnk_file_get_working_directory";
	const char *errors            = NULL;
	char *working_directory       = NULL;
	size_t working_directory_size = 0;
	int result                    = 0;

	PYLNK_UNREFERENCED_PARAMETER( arguments )

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
		pylnk_error_raise(
		 error,
		 PyExc_IOError,
		 "%s: unable to retrieve UTF-8 working directory size.",
		 function );

		libcerror_error_free(
		 &error );

		goto on_error;
	}
	/* Check if the working directory is present
	 */
	else if( ( result == 0 )
	      || ( working_directory_size == 0 ) )
	{
		Py_IncRef(
		 Py_None );

		return( Py_None );
	}
	working_directory = (char *) PyMem_Malloc(
	                              sizeof( char ) * working_directory_size );

	if( working_directory == NULL )
	{
		PyErr_Format(
		 PyExc_MemoryError,
		 "%s: unable to create UTF-8 working directory.",
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
		pylnk_error_raise(
		 error,
		 PyExc_IOError,
		 "%s: unable to retrieve UTF-8 working directory.",
		 function );

		libcerror_error_free(
		 &error );

		goto on_error;
	}
	/* Check if the working directory is present
	 */
	else if( result == 0 )
	{
		PyMem_Free(
		 working_directory );

		Py_IncRef(
		 Py_None );

		return( Py_None );
	}
	/* Pass the string length to PyUnicode_DecodeUTF8
	 * otherwise it makes the end of string character is part
	 * of the string
	 */
	string_object = PyUnicode_DecodeUTF8(
	                 working_directory,
	                 (Py_ssize_t) working_directory_size - 1,
	                 errors );

	if( string_object == NULL )
	{
		PyErr_Format(
		 PyExc_IOError,
		 "%s: unable to convert UTF-8 working directory into Unicode.",
		 function );

		goto on_error;
	}
	PyMem_Free(
	 working_directory );

	return( string_object );

on_error:
	if( working_directory != NULL )
	{
		PyMem_Free(
		 working_directory );
	}
	return( NULL );
}

/* Retrieves the command line arguments of the linked item
 * Returns a Python object if successful or NULL on error
 */
PyObject *pylnk_file_get_command_line_arguments(
           pylnk_file_t *pylnk_file,
           PyObject *arguments PYLNK_ATTRIBUTE_UNUSED )
{
	libcerror_error_t *error           = NULL;
	PyObject *string_object            = NULL;
	static char *function              = "pylnk_file_get_command_line_arguments";
	const char *errors                 = NULL;
	char *command_line_arguments       = NULL;
	size_t command_line_arguments_size = 0;
	int result                         = 0;

	PYLNK_UNREFERENCED_PARAMETER( arguments )

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
		pylnk_error_raise(
		 error,
		 PyExc_IOError,
		 "%s: unable to retrieve UTF-8 command line arguments size.",
		 function );

		libcerror_error_free(
		 &error );

		goto on_error;
	}
	/* Check if the command line arguments is present
	 */
	else if( ( result == 0 )
	      || ( command_line_arguments_size == 0 ) )
	{
		Py_IncRef(
		 Py_None );

		return( Py_None );
	}
	command_line_arguments = (char *) PyMem_Malloc(
	                                   sizeof( char ) * command_line_arguments_size );

	if( command_line_arguments == NULL )
	{
		PyErr_Format(
		 PyExc_MemoryError,
		 "%s: unable to create UTF-8 command line arguments.",
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
		pylnk_error_raise(
		 error,
		 PyExc_IOError,
		 "%s: unable to retrieve UTF-8 command line arguments.",
		 function );

		libcerror_error_free(
		 &error );

		goto on_error;
	}
	/* Check if the command line arguments is present
	 */
	else if( result == 0 )
	{
		PyMem_Free(
		 command_line_arguments );

		Py_IncRef(
		 Py_None );

		return( Py_None );
	}
	/* Pass the string length to PyUnicode_DecodeUTF8
	 * otherwise it makes the end of string character is part
	 * of the string
	 */
	string_object = PyUnicode_DecodeUTF8(
	                 command_line_arguments,
	                 (Py_ssize_t) command_line_arguments_size - 1,
	                 errors );

	if( string_object == NULL )
	{
		PyErr_Format(
		 PyExc_IOError,
		 "%s: unable to convert UTF-8 command line arguments into Unicode.",
		 function );

		goto on_error;
	}
	PyMem_Free(
	 command_line_arguments );

	return( string_object );

on_error:
	if( command_line_arguments != NULL )
	{
		PyMem_Free(
		 command_line_arguments );
	}
	return( NULL );
}

/* Retrieves the icon location of the linked item
 * Returns a Python object if successful or NULL on error
 */
PyObject *pylnk_file_get_icon_location(
           pylnk_file_t *pylnk_file,
           PyObject *arguments PYLNK_ATTRIBUTE_UNUSED )
{
	libcerror_error_t *error  = NULL;
	PyObject *string_object   = NULL;
	static char *function     = "pylnk_file_get_icon_location";
	const char *errors        = NULL;
	char *icon_location       = NULL;
	size_t icon_location_size = 0;
	int result                = 0;

	PYLNK_UNREFERENCED_PARAMETER( arguments )

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
		pylnk_error_raise(
		 error,
		 PyExc_IOError,
		 "%s: unable to retrieve UTF-8 icon location size.",
		 function );

		libcerror_error_free(
		 &error );

		goto on_error;
	}
	/* Check if the icon location is present
	 */
	else if( ( result == 0 )
	      || ( icon_location_size == 0 ) )
	{
		Py_IncRef(
		 Py_None );

		return( Py_None );
	}
	icon_location = (char *) PyMem_Malloc(
	                          sizeof( char ) * icon_location_size );

	if( icon_location == NULL )
	{
		PyErr_Format(
		 PyExc_MemoryError,
		 "%s: unable to create UTF-8 icon location.",
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
		pylnk_error_raise(
		 error,
		 PyExc_IOError,
		 "%s: unable to retrieve UTF-8 icon location.",
		 function );

		libcerror_error_free(
		 &error );

		goto on_error;
	}
	/* Check if the icon location is present
	 */
	else if( result == 0 )
	{
		PyMem_Free(
		 icon_location );

		Py_IncRef(
		 Py_None );

		return( Py_None );
	}
	/* Pass the string length to PyUnicode_DecodeUTF8
	 * otherwise it makes the end of string character is part
	 * of the string
	 */
	string_object = PyUnicode_DecodeUTF8(
	                 icon_location,
	                 (Py_ssize_t) icon_location_size - 1,
	                 errors );

	if( string_object == NULL )
	{
		PyErr_Format(
		 PyExc_IOError,
		 "%s: unable to convert UTF-8 icon location into Unicode.",
		 function );

		goto on_error;
	}
	PyMem_Free(
	 icon_location );

	return( string_object );

on_error:
	if( icon_location != NULL )
	{
		PyMem_Free(
		 icon_location );
	}
	return( NULL );
}

/* Retrieves the environment variables location of the linked item
 * Returns a Python object if successful or NULL on error
 */
PyObject *pylnk_file_get_environment_variables_location(
           pylnk_file_t *pylnk_file,
           PyObject *arguments PYLNK_ATTRIBUTE_UNUSED )
{
	libcerror_error_t *error                   = NULL;
	PyObject *string_object                    = NULL;
	static char *function                      = "pylnk_file_get_environment_variables_location";
	const char *errors                         = NULL;
	char *environment_variables_location       = NULL;
	size_t environment_variables_location_size = 0;
	int result                                 = 0;

	PYLNK_UNREFERENCED_PARAMETER( arguments )

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
		pylnk_error_raise(
		 error,
		 PyExc_IOError,
		 "%s: unable to retrieve UTF-8 environment variables location size.",
		 function );

		libcerror_error_free(
		 &error );

		goto on_error;
	}
	/* Check if the environment variables location is present
	 */
	else if( ( result == 0 )
	      || ( environment_variables_location_size == 0 ) )
	{
		Py_IncRef(
		 Py_None );

		return( Py_None );
	}
	environment_variables_location = (char *) PyMem_Malloc(
	                                           sizeof( char ) * environment_variables_location_size );

	if( environment_variables_location == NULL )
	{
		PyErr_Format(
		 PyExc_MemoryError,
		 "%s: unable to create UTF-8 environment variables location.",
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
		pylnk_error_raise(
		 error,
		 PyExc_IOError,
		 "%s: unable to retrieve UTF-8 environment variables location.",
		 function );

		libcerror_error_free(
		 &error );

		goto on_error;
	}
	/* Check if the environment variables location is present
	 */
	else if( result == 0 )
	{
		PyMem_Free(
		 environment_variables_location );

		Py_IncRef(
		 Py_None );

		return( Py_None );
	}
	/* Pass the string length to PyUnicode_DecodeUTF8
	 * otherwise it makes the end of string character is part
	 * of the string
	 */
	string_object = PyUnicode_DecodeUTF8(
	                 environment_variables_location,
	                 (Py_ssize_t) environment_variables_location_size - 1,
	                 errors );

	if( string_object == NULL )
	{
		PyErr_Format(
		 PyExc_IOError,
		 "%s: unable to convert UTF-8 environment variables location into Unicode.",
		 function );

		goto on_error;
	}
	PyMem_Free(
	 environment_variables_location );

	return( string_object );

on_error:
	if( environment_variables_location != NULL )
	{
		PyMem_Free(
		 environment_variables_location );
	}
	return( NULL );
}

/* Retrieves the link target identifier data of the linked item
 * Returns a Python object if successful or NULL on error
 */
PyObject *pylnk_file_get_link_target_identifier_data(
           pylnk_file_t *pylnk_file,
           PyObject *arguments PYLNK_ATTRIBUTE_UNUSED )
{
	libcerror_error_t *error                = NULL;
	PyObject *string_object                 = NULL;
	static char *function                   = "pylnk_file_get_link_target_identifier_data";
	char *link_target_identifier_data       = NULL;
	size_t link_target_identifier_data_size = 0;
	int result                              = 0;

	PYLNK_UNREFERENCED_PARAMETER( arguments )

	if( pylnk_file == NULL )
	{
		PyErr_Format(
		 PyExc_ValueError,
		 "%s: invalid file.",
		 function );

		return( NULL );
	}
	Py_BEGIN_ALLOW_THREADS

	result = liblnk_file_get_link_target_identifier_data_size(
	          pylnk_file->file,
	          &link_target_identifier_data_size,
	          &error );

	Py_END_ALLOW_THREADS

	if( result == -1 )
	{
		pylnk_error_raise(
		 error,
		 PyExc_IOError,
		 "%s: unable to retrieve link target identifier data size.",
		 function );

		libcerror_error_free(
		 &error );

		goto on_error;
	}
	/* Check if the link target identifier data is present
	 */
	else if( ( result == 0 )
	      || ( link_target_identifier_data_size == 0 ) )
	{
		Py_IncRef(
		 Py_None );

		return( Py_None );
	}
	link_target_identifier_data = (char *) PyMem_Malloc(
	                                        sizeof( char ) * link_target_identifier_data_size );

	if( link_target_identifier_data == NULL )
	{
		PyErr_Format(
		 PyExc_MemoryError,
		 "%s: unable to create link target identifier data.",
		 function );

		goto on_error;
	}
	Py_BEGIN_ALLOW_THREADS

	result = liblnk_file_copy_link_target_identifier_data(
	          pylnk_file->file,
	          (uint8_t *) link_target_identifier_data,
	          link_target_identifier_data_size,
	          &error );

	Py_END_ALLOW_THREADS

	if( result == -1 )
	{
		pylnk_error_raise(
		 error,
		 PyExc_IOError,
		 "%s: unable to copy link target identifier data.",
		 function );

		libcerror_error_free(
		 &error );

		goto on_error;
	}
	/* Check if the link target identifier data is present
	 */
	else if( result == 0 )
	{
		PyMem_Free(
		 link_target_identifier_data );

		Py_IncRef(
		 Py_None );

		return( Py_None );
	}
	/* This is a byte string so include the full size
	 */
#if PY_MAJOR_VERSION >= 3
	string_object = PyBytes_FromStringAndSize(
	                 link_target_identifier_data,
	                 (Py_ssize_t) link_target_identifier_data_size );
#else
	string_object = PyString_FromStringAndSize(
	                 link_target_identifier_data,
	                 (Py_ssize_t) link_target_identifier_data_size );
#endif
	if( string_object == NULL )
	{
		PyErr_Format(
		 PyExc_IOError,
		 "%s: unable to convert link target identifier into string.",
		 function );

		goto on_error;
	}
	PyMem_Free(
	 link_target_identifier_data );

	return( string_object );

on_error:
	if( link_target_identifier_data != NULL )
	{
		PyMem_Free(
		 link_target_identifier_data );
	}
	return( NULL );
}

/* Retrieves the machine identifier of the linked item
 * Returns a Python object if successful or NULL on error
 */
PyObject *pylnk_file_get_machine_identifier(
           pylnk_file_t *pylnk_file,
           PyObject *arguments PYLNK_ATTRIBUTE_UNUSED )
{
	libcerror_error_t *error       = NULL;
	PyObject *string_object        = NULL;
	static char *function          = "pylnk_file_get_machine_identifier";
	const char *errors             = NULL;
	char *machine_identifier       = NULL;
	size_t machine_identifier_size = 0;
	int result                     = 0;

	PYLNK_UNREFERENCED_PARAMETER( arguments )

	if( pylnk_file == NULL )
	{
		PyErr_Format(
		 PyExc_ValueError,
		 "%s: invalid file.",
		 function );

		return( NULL );
	}
	Py_BEGIN_ALLOW_THREADS

	result = liblnk_file_has_distributed_link_tracking_data(
	          pylnk_file->file,
	          &error );

	Py_END_ALLOW_THREADS

	if( result == -1 )
	{
		pylnk_error_raise(
		 error,
		 PyExc_IOError,
		 "%s: unable to determine if file has distributed link tracking data.",
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
	Py_BEGIN_ALLOW_THREADS

	result = liblnk_file_get_utf8_machine_identifier_size(
	          pylnk_file->file,
	          &machine_identifier_size,
	          &error );

	Py_END_ALLOW_THREADS

	if( result != 1 )
	{
		pylnk_error_raise(
		 error,
		 PyExc_IOError,
		 "%s: unable to retrieve UTF-8 mschine identifier size.",
		 function );

		libcerror_error_free(
		 &error );

		goto on_error;
	}
	/* Check if the machine identifier is present
	 */
	else if( machine_identifier_size == 0 )
	{
		Py_IncRef(
		 Py_None );

		return( Py_None );
	}
	machine_identifier = (char *) PyMem_Malloc(
	                               sizeof( char ) * machine_identifier_size );

	if( machine_identifier == NULL )
	{
		PyErr_Format(
		 PyExc_MemoryError,
		 "%s: unable to create UTF-8 machine identifier.",
		 function );

		goto on_error;
	}
	Py_BEGIN_ALLOW_THREADS

	result = liblnk_file_get_utf8_machine_identifier(
	          pylnk_file->file,
	          (uint8_t *) machine_identifier,
	          machine_identifier_size,
	          &error );

	Py_END_ALLOW_THREADS

	if( result == -1 )
	{
		pylnk_error_raise(
		 error,
		 PyExc_IOError,
		 "%s: unable to retrieve UTF-8 machine identifier.",
		 function );

		libcerror_error_free(
		 &error );

		goto on_error;
	}
	/* Check if the machine identifier is present
	 */
	else if( result == 0 )
	{
		PyMem_Free(
		 machine_identifier );

		Py_IncRef(
		 Py_None );

		return( Py_None );
	}
	/* Pass the string length to PyUnicode_DecodeUTF8
	 * otherwise it makes the end of string character is part
	 * of the string
	 */
	string_object = PyUnicode_DecodeUTF8(
	                 machine_identifier,
	                 (Py_ssize_t) machine_identifier_size - 1,
	                 errors );

	if( string_object == NULL )
	{
		PyErr_Format(
		 PyExc_IOError,
		 "%s: unable to convert UTF-8 machine identifier into Unicode.",
		 function );

		goto on_error;
	}
	PyMem_Free(
	 machine_identifier );

	return( string_object );

on_error:
	if( machine_identifier != NULL )
	{
		PyMem_Free(
		 machine_identifier );
	}
	return( NULL );
}

/* Retrieves the droid volume identifier of the linked item
 * Returns a Python object if successful or NULL on error
 */
PyObject *pylnk_file_get_droid_volume_identifier(
           pylnk_file_t *pylnk_file,
           PyObject *arguments PYLNK_ATTRIBUTE_UNUSED )
{
	uint8_t guid_data[ 16 ];

	libcerror_error_t *error = NULL;
	PyObject *string_object  = NULL;
	static char *function    = "pylnk_file_get_droid_volume_identifier";
	int result               = 0;

	PYLNK_UNREFERENCED_PARAMETER( arguments )

	if( pylnk_file == NULL )
	{
		PyErr_Format(
		 PyExc_TypeError,
		 "%s: invalid file.",
		 function );

		return( NULL );
	}
	Py_BEGIN_ALLOW_THREADS

	result = liblnk_file_has_distributed_link_tracking_data(
	          pylnk_file->file,
	          &error );

	Py_END_ALLOW_THREADS

	if( result == -1 )
	{
		pylnk_error_raise(
		 error,
		 PyExc_IOError,
		 "%s: unable to determine if file has distributed link tracking data.",
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
	Py_BEGIN_ALLOW_THREADS

	result = liblnk_file_get_droid_volume_identifier(
	          pylnk_file->file,
	          guid_data,
	          16,
	          &error );

	Py_END_ALLOW_THREADS

	if( result != 1 )
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
	string_object = pylnk_string_new_from_guid(
			 guid_data,
			 16 );

	return( string_object );
}

/* Retrieves the droid file identifier of the linked item
 * Returns a Python object if successful or NULL on error
 */
PyObject *pylnk_file_get_droid_file_identifier(
           pylnk_file_t *pylnk_file,
           PyObject *arguments PYLNK_ATTRIBUTE_UNUSED )
{
	uint8_t guid_data[ 16 ];

	libcerror_error_t *error = NULL;
	PyObject *string_object  = NULL;
	static char *function    = "pylnk_file_get_droid_file_identifier";
	int result               = 0;

	PYLNK_UNREFERENCED_PARAMETER( arguments )

	if( pylnk_file == NULL )
	{
		PyErr_Format(
		 PyExc_TypeError,
		 "%s: invalid file.",
		 function );

		return( NULL );
	}
	Py_BEGIN_ALLOW_THREADS

	result = liblnk_file_has_distributed_link_tracking_data(
	          pylnk_file->file,
	          &error );

	Py_END_ALLOW_THREADS

	if( result == -1 )
	{
		pylnk_error_raise(
		 error,
		 PyExc_IOError,
		 "%s: unable to determine if file has distributed link tracking data.",
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
	Py_BEGIN_ALLOW_THREADS

	result = liblnk_file_get_droid_file_identifier(
	          pylnk_file->file,
	          guid_data,
	          16,
	          &error );

	Py_END_ALLOW_THREADS

	if( result != 1 )
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
	string_object = pylnk_string_new_from_guid(
			 guid_data,
			 16 );

	return( string_object );
}

/* Retrieves the birth droid volume identifier of the linked item
 * Returns a Python object if successful or NULL on error
 */
PyObject *pylnk_file_get_birth_droid_volume_identifier(
           pylnk_file_t *pylnk_file,
           PyObject *arguments PYLNK_ATTRIBUTE_UNUSED )
{
	uint8_t guid_data[ 16 ];

	libcerror_error_t *error = NULL;
	PyObject *string_object  = NULL;
	static char *function    = "pylnk_file_get_birth_droid_volume_identifier";
	int result               = 0;

	PYLNK_UNREFERENCED_PARAMETER( arguments )

	if( pylnk_file == NULL )
	{
		PyErr_Format(
		 PyExc_TypeError,
		 "%s: invalid file.",
		 function );

		return( NULL );
	}
	Py_BEGIN_ALLOW_THREADS

	result = liblnk_file_has_distributed_link_tracking_data(
	          pylnk_file->file,
	          &error );

	Py_END_ALLOW_THREADS

	if( result == -1 )
	{
		pylnk_error_raise(
		 error,
		 PyExc_IOError,
		 "%s: unable to determine if file has distributed link tracking data.",
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
	Py_BEGIN_ALLOW_THREADS

	result = liblnk_file_get_birth_droid_volume_identifier(
	          pylnk_file->file,
	          guid_data,
	          16,
	          &error );

	Py_END_ALLOW_THREADS

	if( result != 1 )
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
	string_object = pylnk_string_new_from_guid(
			 guid_data,
			 16 );

	return( string_object );
}

/* Retrieves the birth droid file identifier of the linked item
 * Returns a Python object if successful or NULL on error
 */
PyObject *pylnk_file_get_birth_droid_file_identifier(
           pylnk_file_t *pylnk_file,
           PyObject *arguments PYLNK_ATTRIBUTE_UNUSED )
{
	uint8_t guid_data[ 16 ];

	libcerror_error_t *error = NULL;
	PyObject *string_object  = NULL;
	static char *function    = "pylnk_file_get_birth_droid_file_identifier";
	int result               = 0;

	PYLNK_UNREFERENCED_PARAMETER( arguments )

	if( pylnk_file == NULL )
	{
		PyErr_Format(
		 PyExc_TypeError,
		 "%s: invalid file.",
		 function );

		return( NULL );
	}
	Py_BEGIN_ALLOW_THREADS

	result = liblnk_file_has_distributed_link_tracking_data(
	          pylnk_file->file,
	          &error );

	Py_END_ALLOW_THREADS

	if( result == -1 )
	{
		pylnk_error_raise(
		 error,
		 PyExc_IOError,
		 "%s: unable to determine if file has distributed link tracking data.",
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
	Py_BEGIN_ALLOW_THREADS

	result = liblnk_file_get_birth_droid_file_identifier(
	          pylnk_file->file,
	          guid_data,
	          16,
	          &error );

	Py_END_ALLOW_THREADS

	if( result != 1 )
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
	string_object = pylnk_string_new_from_guid(
			 guid_data,
			 16 );

	return( string_object );
}

