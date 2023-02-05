/*
 * Python bindings module for liblnk (pylnk)
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
#include <narrow_string.h>
#include <types.h>

#if defined( HAVE_STDLIB_H ) || defined( HAVE_WINAPI )
#include <stdlib.h>
#endif

#include "pylnk.h"
#include "pylnk_data_block.h"
#include "pylnk_data_blocks.h"
#include "pylnk_data_flags.h"
#include "pylnk_distributed_link_tracking_data_block.h"
#include "pylnk_drive_types.h"
#include "pylnk_error.h"
#include "pylnk_file.h"
#include "pylnk_file_attribute_flags.h"
#include "pylnk_file_object_io_handle.h"
#include "pylnk_libbfio.h"
#include "pylnk_libcerror.h"
#include "pylnk_liblnk.h"
#include "pylnk_python.h"
#include "pylnk_strings_data_block.h"
#include "pylnk_unused.h"

#if !defined( LIBLNK_HAVE_BFIO )

LIBLNK_EXTERN \
int liblnk_check_file_signature_file_io_handle(
     libbfio_handle_t *file_io_handle,
     liblnk_error_t **error );

#endif /* !defined( LIBLNK_HAVE_BFIO ) */

/* The pylnk module methods
 */
PyMethodDef pylnk_module_methods[] = {
	{ "get_version",
	  (PyCFunction) pylnk_get_version,
	  METH_NOARGS,
	  "get_version() -> String\n"
	  "\n"
	  "Retrieves the version." },

	{ "check_file_signature",
	  (PyCFunction) pylnk_check_file_signature,
	  METH_VARARGS | METH_KEYWORDS,
	  "check_file_signature(filename) -> Boolean\n"
	  "\n"
	  "Checks if a file has a Windows Shortcut File (LNK) signature." },

	{ "check_file_signature_file_object",
	  (PyCFunction) pylnk_check_file_signature_file_object,
	  METH_VARARGS | METH_KEYWORDS,
	  "check_file_signature_file_object(file_object) -> Boolean\n"
	  "\n"
	  "Checks if a file has a Windows Shortcut File (LNK) signature using a file-like object." },

	{ "open",
	  (PyCFunction) pylnk_open_new_file,
	  METH_VARARGS | METH_KEYWORDS,
	  "open(filename, mode='r') -> Object\n"
	  "\n"
	  "Opens a file." },

	{ "open_file_object",
	  (PyCFunction) pylnk_open_new_file_with_file_object,
	  METH_VARARGS | METH_KEYWORDS,
	  "open_file_object(file_object, mode='r') -> Object\n"
	  "\n"
	  "Opens a file using a file-like object." },

	/* Sentinel */
	{ NULL, NULL, 0, NULL }
};

/* Retrieves the pylnk/liblnk version
 * Returns a Python object if successful or NULL on error
 */
PyObject *pylnk_get_version(
           PyObject *self PYLNK_ATTRIBUTE_UNUSED,
           PyObject *arguments PYLNK_ATTRIBUTE_UNUSED )
{
	const char *errors           = NULL;
	const char *version_string   = NULL;
	size_t version_string_length = 0;

	PYLNK_UNREFERENCED_PARAMETER( self )
	PYLNK_UNREFERENCED_PARAMETER( arguments )

	Py_BEGIN_ALLOW_THREADS

	version_string = liblnk_get_version();

	Py_END_ALLOW_THREADS

	version_string_length = narrow_string_length(
	                         version_string );

	/* Pass the string length to PyUnicode_DecodeUTF8
	 * otherwise it makes the end of string character is part
	 * of the string
	 */
	return( PyUnicode_DecodeUTF8(
	         version_string,
	         (Py_ssize_t) version_string_length,
	         errors ) );
}

/* Checks if a file has a Windows Shortcut File (LNK) signature
 * Returns a Python object if successful or NULL on error
 */
PyObject *pylnk_check_file_signature(
           PyObject *self PYLNK_ATTRIBUTE_UNUSED,
           PyObject *arguments,
           PyObject *keywords )
{
	PyObject *string_object     = NULL;
	libcerror_error_t *error    = NULL;
	const char *filename_narrow = NULL;
	static char *function       = "pylnk_check_file_signature";
	static char *keyword_list[] = { "filename", NULL };
	int result                  = 0;

#if defined( HAVE_WIDE_SYSTEM_CHARACTER )
	const wchar_t *filename_wide = NULL;
#else
	PyObject *utf8_string_object = NULL;
#endif

	PYLNK_UNREFERENCED_PARAMETER( self )

	/* Note that PyArg_ParseTupleAndKeywords with "s" will force Unicode strings to be converted to narrow character string.
	 * On Windows the narrow character strings contains an extended ASCII string with a codepage. Hence we get a conversion
	 * exception. This will also fail if the default encoding is not set correctly. We cannot use "u" here either since that
	 * does not allow us to pass non Unicode string objects and Python (at least 2.7) does not seems to automatically upcast them.
	 */
	if( PyArg_ParseTupleAndKeywords(
	     arguments,
	     keywords,
	     "O|",
	     keyword_list,
	     &string_object ) == 0 )
	{
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
		 "%s: unable to determine if string object is of type Unicode.",
		 function );

		return( NULL );
	}
	else if( result != 0 )
	{
		PyErr_Clear();

#if defined( HAVE_WIDE_SYSTEM_CHARACTER )
		filename_wide = (wchar_t *) PyUnicode_AsUnicode(
		                             string_object );
		Py_BEGIN_ALLOW_THREADS

		result = liblnk_check_file_signature_wide(
		          filename_wide,
		          &error );

		Py_END_ALLOW_THREADS
#else
		utf8_string_object = PyUnicode_AsUTF8String(
		                      string_object );

		if( utf8_string_object == NULL )
		{
			pylnk_error_fetch_and_raise(
			 PyExc_RuntimeError,
			 "%s: unable to convert Unicode string to UTF-8.",
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

		result = liblnk_check_file_signature(
		          filename_narrow,
		          &error );

		Py_END_ALLOW_THREADS

		Py_DecRef(
		 utf8_string_object );

#endif /* defined( HAVE_WIDE_SYSTEM_CHARACTER ) */

		if( result == -1 )
		{
			pylnk_error_raise(
			 error,
			 PyExc_IOError,
			 "%s: unable to check file signature.",
			 function );

			libcerror_error_free(
			 &error );

			return( NULL );
		}
		if( result != 0 )
		{
			Py_IncRef(
			 (PyObject *) Py_True );

			return( Py_True );
		}
		Py_IncRef(
		 (PyObject *) Py_False );

		return( Py_False );
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

		result = liblnk_check_file_signature(
		          filename_narrow,
		          &error );

		Py_END_ALLOW_THREADS

		if( result == -1 )
		{
			pylnk_error_raise(
			 error,
			 PyExc_IOError,
			 "%s: unable to check file signature.",
			 function );

			libcerror_error_free(
			 &error );

			return( NULL );
		}
		if( result != 0 )
		{
			Py_IncRef(
			 (PyObject *) Py_True );

			return( Py_True );
		}
		Py_IncRef(
		 (PyObject *) Py_False );

		return( Py_False );
	}
	PyErr_Format(
	 PyExc_TypeError,
	 "%s: unsupported string object type.",
	 function );

	return( NULL );
}

/* Checks if a file has a Windows Shortcut File (LNK) signature using a file-like object
 * Returns a Python object if successful or NULL on error
 */
PyObject *pylnk_check_file_signature_file_object(
           PyObject *self PYLNK_ATTRIBUTE_UNUSED,
           PyObject *arguments,
           PyObject *keywords )
{
	PyObject *file_object            = NULL;
	libbfio_handle_t *file_io_handle = NULL;
	libcerror_error_t *error         = NULL;
	static char *function            = "pylnk_check_file_signature_file_object";
	static char *keyword_list[]      = { "file_object", NULL };
	int result                       = 0;

	PYLNK_UNREFERENCED_PARAMETER( self )

	if( PyArg_ParseTupleAndKeywords(
	     arguments,
	     keywords,
	     "O|",
	     keyword_list,
	     &file_object ) == 0 )
	{
		return( NULL );
	}
	if( pylnk_file_object_initialize(
	     &file_io_handle,
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

	result = liblnk_check_file_signature_file_io_handle(
	          file_io_handle,
	          &error );

	Py_END_ALLOW_THREADS

	if( result == -1 )
	{
		pylnk_error_raise(
		 error,
		 PyExc_IOError,
		 "%s: unable to check file signature.",
		 function );

		libcerror_error_free(
		 &error );

		goto on_error;
	}
	if( libbfio_handle_free(
	     &file_io_handle,
	     &error ) != 1 )
	{
		pylnk_error_raise(
		 error,
		 PyExc_MemoryError,
		 "%s: unable to free file IO handle.",
		 function );

		libcerror_error_free(
		 &error );

		goto on_error;
	}
	if( result != 0 )
	{
		Py_IncRef(
		 (PyObject *) Py_True );

		return( Py_True );
	}
	Py_IncRef(
	 (PyObject *) Py_False );

	return( Py_False );

on_error:
	if( file_io_handle != NULL )
	{
		libbfio_handle_free(
		 &file_io_handle,
		 NULL );
	}
	return( NULL );
}

/* Creates a new file object and opens it
 * Returns a Python object if successful or NULL on error
 */
PyObject *pylnk_open_new_file(
           PyObject *self PYLNK_ATTRIBUTE_UNUSED,
           PyObject *arguments,
           PyObject *keywords )
{
	pylnk_file_t *pylnk_file = NULL;
	static char *function    = "pylnk_open_new_file";

	PYLNK_UNREFERENCED_PARAMETER( self )

	/* PyObject_New does not invoke tp_init
	 */
	pylnk_file = PyObject_New(
	              struct pylnk_file,
	              &pylnk_file_type_object );

	if( pylnk_file == NULL )
	{
		PyErr_Format(
		 PyExc_MemoryError,
		 "%s: unable to create file.",
		 function );

		goto on_error;
	}
	if( pylnk_file_init(
	     pylnk_file ) != 0 )
	{
		goto on_error;
	}
	if( pylnk_file_open(
	     pylnk_file,
	     arguments,
	     keywords ) == NULL )
	{
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

/* Creates a new file object and opens it using a file-like object
 * Returns a Python object if successful or NULL on error
 */
PyObject *pylnk_open_new_file_with_file_object(
           PyObject *self PYLNK_ATTRIBUTE_UNUSED,
           PyObject *arguments,
           PyObject *keywords )
{
	pylnk_file_t *pylnk_file = NULL;
	static char *function    = "pylnk_open_new_file_with_file_object";

	PYLNK_UNREFERENCED_PARAMETER( self )

	/* PyObject_New does not invoke tp_init
	 */
	pylnk_file = PyObject_New(
	              struct pylnk_file,
	              &pylnk_file_type_object );

	if( pylnk_file == NULL )
	{
		PyErr_Format(
		 PyExc_MemoryError,
		 "%s: unable to create file.",
		 function );

		goto on_error;
	}
	if( pylnk_file_init(
	     pylnk_file ) != 0 )
	{
		goto on_error;
	}
	if( pylnk_file_open_file_object(
	     pylnk_file,
	     arguments,
	     keywords ) == NULL )
	{
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

#if PY_MAJOR_VERSION >= 3

/* The pylnk module definition
 */
PyModuleDef pylnk_module_definition = {
	PyModuleDef_HEAD_INIT,

	/* m_name */
	"pylnk",
	/* m_doc */
	"Python liblnk module (pylnk).",
	/* m_size */
	-1,
	/* m_methods */
	pylnk_module_methods,
	/* m_reload */
	NULL,
	/* m_traverse */
	NULL,
	/* m_clear */
	NULL,
	/* m_free */
	NULL,
};

#endif /* PY_MAJOR_VERSION >= 3 */

/* Initializes the pylnk module
 */
#if PY_MAJOR_VERSION >= 3
PyMODINIT_FUNC PyInit_pylnk(
                void )
#else
PyMODINIT_FUNC initpylnk(
                void )
#endif
{
	PyObject *module           = NULL;
	PyGILState_STATE gil_state = 0;

#if defined( HAVE_DEBUG_OUTPUT )
	liblnk_notify_set_stream(
	 stderr,
	 NULL );
	liblnk_notify_set_verbose(
	 1 );
#endif

	/* Create the module
	 * This function must be called before grabbing the GIL
	 * otherwise the module will segfault on a version mismatch
	 */
#if PY_MAJOR_VERSION >= 3
	module = PyModule_Create(
	          &pylnk_module_definition );
#else
	module = Py_InitModule3(
	          "pylnk",
	          pylnk_module_methods,
	          "Python liblnk module (pylnk)." );
#endif
	if( module == NULL )
	{
#if PY_MAJOR_VERSION >= 3
		return( NULL );
#else
		return;
#endif
	}
#if PY_VERSION_HEX < 0x03070000
	PyEval_InitThreads();
#endif
	gil_state = PyGILState_Ensure();

	/* Setup the data_block type object
	 */
	pylnk_data_block_type_object.tp_new = PyType_GenericNew;

	if( PyType_Ready(
	     &pylnk_data_block_type_object ) < 0 )
	{
		goto on_error;
	}
	Py_IncRef(
	 (PyObject *) &pylnk_data_block_type_object );

	PyModule_AddObject(
	 module,
	 "data_block",
	 (PyObject *) &pylnk_data_block_type_object );

	/* Setup the data_blocks type object
	 */
	pylnk_data_blocks_type_object.tp_new = PyType_GenericNew;

	if( PyType_Ready(
	     &pylnk_data_blocks_type_object ) < 0 )
	{
		goto on_error;
	}
	Py_IncRef(
	 (PyObject *) &pylnk_data_blocks_type_object );

	PyModule_AddObject(
	 module,
	 "data_blocks",
	 (PyObject *) &pylnk_data_blocks_type_object );

	/* Setup the data_flags type object
	 */
	pylnk_data_flags_type_object.tp_new = PyType_GenericNew;

	if( pylnk_data_flags_init_type(
	     &pylnk_data_flags_type_object ) != 1 )
	{
		goto on_error;
	}
	if( PyType_Ready(
	     &pylnk_data_flags_type_object ) < 0 )
	{
		goto on_error;
	}
	Py_IncRef(
	 (PyObject *) &pylnk_data_flags_type_object );

	PyModule_AddObject(
	 module,
	 "data_flags",
	 (PyObject *) &pylnk_data_flags_type_object );

	/* Setup the distributed_link_tracking_data_block type object
	 */
	pylnk_distributed_link_tracking_data_block_type_object.tp_new = PyType_GenericNew;

	if( PyType_Ready(
	     &pylnk_distributed_link_tracking_data_block_type_object ) < 0 )
	{
		goto on_error;
	}
	Py_IncRef(
	 (PyObject *) &pylnk_distributed_link_tracking_data_block_type_object );

	PyModule_AddObject(
	 module,
	 "distributed_link_tracking_data_block",
	 (PyObject *) &pylnk_distributed_link_tracking_data_block_type_object );

	/* Setup the drive_types type object
	 */
	pylnk_drive_types_type_object.tp_new = PyType_GenericNew;

	if( pylnk_drive_types_init_type(
	     &pylnk_drive_types_type_object ) != 1 )
	{
		goto on_error;
	}
	if( PyType_Ready(
	     &pylnk_drive_types_type_object ) < 0 )
	{
		goto on_error;
	}
	Py_IncRef(
	 (PyObject *) &pylnk_drive_types_type_object );

	PyModule_AddObject(
	 module,
	 "drive_types",
	 (PyObject *) &pylnk_drive_types_type_object );

	/* Setup the file type object
	 */
	pylnk_file_type_object.tp_new = PyType_GenericNew;

	if( PyType_Ready(
	     &pylnk_file_type_object ) < 0 )
	{
		goto on_error;
	}
	Py_IncRef(
	 (PyObject *) &pylnk_file_type_object );

	PyModule_AddObject(
	 module,
	 "file",
	 (PyObject *) &pylnk_file_type_object );

	/* Setup the file_attribute_flags type object
	 */
	pylnk_file_attribute_flags_type_object.tp_new = PyType_GenericNew;

	if( pylnk_file_attribute_flags_init_type(
	     &pylnk_file_attribute_flags_type_object ) != 1 )
	{
		goto on_error;
	}
	if( PyType_Ready(
	     &pylnk_file_attribute_flags_type_object ) < 0 )
	{
		goto on_error;
	}
	Py_IncRef(
	 (PyObject *) &pylnk_file_attribute_flags_type_object );

	PyModule_AddObject(
	 module,
	 "file_attribute_flags",
	 (PyObject *) &pylnk_file_attribute_flags_type_object );

	/* Setup the strings_data_block type object
	 */
	pylnk_strings_data_block_type_object.tp_new = PyType_GenericNew;

	if( PyType_Ready(
	     &pylnk_strings_data_block_type_object ) < 0 )
	{
		goto on_error;
	}
	Py_IncRef(
	 (PyObject *) &pylnk_strings_data_block_type_object );

	PyModule_AddObject(
	 module,
	 "strings_data_block",
	 (PyObject *) &pylnk_strings_data_block_type_object );

	PyGILState_Release(
	 gil_state );

#if PY_MAJOR_VERSION >= 3
	return( module );
#else
	return;
#endif

on_error:
	PyGILState_Release(
	 gil_state );

#if PY_MAJOR_VERSION >= 3
	return( NULL );
#else
	return;
#endif
}

