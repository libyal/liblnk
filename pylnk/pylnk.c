/*
 * Python bindings module for liblnk (pylnk)
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
#include <types.h>

#if defined( HAVE_STDLIB_H ) || defined( HAVE_WINAPI )
#include <stdlib.h>
#endif

#include "pylnk.h"
#include "pylnk_file.h"
#include "pylnk_libcerror.h"
#include "pylnk_libcstring.h"
#include "pylnk_liblnk.h"
#include "pylnk_python.h"

/* The pylnk module methods
 */
PyMethodDef pylnk_module_methods[] = {
	{ "get_version",
	  (PyCFunction) pylnk_get_version,
	  METH_NOARGS,
	  "Retrieves the version" },

	{ "get_access_flags_read",
	  (PyCFunction) pylnk_get_access_flags_read,
	  METH_NOARGS,
	  "Retrieves the read access flags" },

	{ "check_file_signature",
	  (PyCFunction) pylnk_check_file_signature,
	  METH_VARARGS | METH_KEYWORDS,
	  "Checks if a file has a Windows Shortcut File (LNK) signature" },

	{ "open",
	  (PyCFunction) pylnk_file_new_open,
	  METH_VARARGS | METH_KEYWORDS,
	  "Creates a new file and opens it" },

	/* Sentinel */
	{ NULL, NULL, 0, NULL }
};

/* Retrieves the pylnk/liblnk version
 * Returns a Python object if successful or NULL on error
 */
PyObject *pylnk_get_version(
           PyObject *self )
{
	const char *errors           = NULL;
	const char *version_string   = NULL;
	size_t version_string_length = 0;

	version_string = liblnk_get_version();

	version_string_length = libcstring_narrow_string_length(
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

/* Retrieves the pylnk/liblnk read access flags
 * Returns a Python object if successful or NULL on error
 */
PyObject *pylnk_get_access_flags_read(
           PyObject *self )
{
	return( PyInt_FromLong(
	         (long) liblnk_get_access_flags_read() ) );
}

/* Checks if the file has a Windows NT Registy File signature
 * Returns a Python object if successful or NULL on error
 */
PyObject *pylnk_check_file_signature(
           PyObject *self,
           PyObject *arguments,
           PyObject *keywords )
{
	char error_string[ PYLNK_ERROR_STRING_SIZE ];

	libcerror_error_t *error     = NULL;
	static char *function       = "pylnk_check_file_signature";
	static char *keyword_list[] = { "filename", NULL };
	const char *filename        = NULL;
	int result                  = 0;

	if( PyArg_ParseTupleAndKeywords(
	     arguments,
	     keywords,
	     "|s",
	     keyword_list,
	     &filename ) == 0 )
	{
		return( NULL );
	}
	result = liblnk_check_file_signature(
	          filename,
	          &error );

	if( result == -1 )
	{
		if( libcerror_error_backtrace_sprint(
		     error,
		     error_string,
		     PYLNK_ERROR_STRING_SIZE ) == -1 )
                {
			PyErr_Format(
			 PyExc_IOError,
			 "%s: unable to check file signature.",
			 function );
		}
		else
		{
			PyErr_Format(
			 PyExc_IOError,
			 "%s: unable to check file signature.\n%s",
			 function,
			 error_string );
		}
		libcerror_error_free(
		 &error );

		return( NULL );
	}
	if( result != 0 )
	{
		return( Py_True );
	}
	return( Py_False );
}

/* Declarations for DLL import/export
 */
#ifndef PyMODINIT_FUNC
#define PyMODINIT_FUNC void
#endif

/* Initializes the pylnk module
 */
PyMODINIT_FUNC initpylnk(
                void ) 
{
	PyObject *module               = NULL;
	PyTypeObject *file_type_object = NULL;
	PyGILState_STATE gil_state     = 0;

	PyEval_InitThreads();

	gil_state = PyGILState_Ensure();

	/* Create the module
	 */
	module = Py_InitModule3(
	          "pylnk",
	           pylnk_module_methods,
	           "Python liblnk module (pylnk)." );

	/* Setup the file type object
	 */
	pylnk_file_type_object.tp_new = PyType_GenericNew;

	if( PyType_Ready(
	     &pylnk_file_type_object ) < 0 )
	{
		return;
	}
	Py_IncRef(
	 (PyObject *) &pylnk_file_type_object );

	file_type_object = &pylnk_file_type_object;

	PyModule_AddObject(
	 module,
	"file",
	(PyObject *) file_type_object );

	PyGILState_Release(
	 gil_state );
}

