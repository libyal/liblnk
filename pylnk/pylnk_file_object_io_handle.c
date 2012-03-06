/*
 * Python file object IO handle functions
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

#include "pylnk_file_object_io_handle.h"
#include "pylnk_libbfio.h"
#include "pylnk_python.h"

/* Initializes the file object IO handle
 * Returns 1 if successful or -1 on error
 */
int pylnk_file_object_io_handle_initialize(
     pylnk_file_object_io_handle_t **file_object_io_handle,
     PyObject *file_object,
     liberror_error_t **error )
{
	static char *function = "pylnk_file_object_io_handle_initialize";

	if( file_object_io_handle == NULL )
	{
		liberror_error_set(
		 error,
		 LIBERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid file object IO handle.",
		 function );

		return( -1 );
	}
	if( *file_object_io_handle != NULL )
	{
		liberror_error_set(
		 error,
		 LIBERROR_ERROR_DOMAIN_RUNTIME,
		 LIBERROR_RUNTIME_ERROR_VALUE_ALREADY_SET,
		 "%s: invalid file object IO handle value already set.",
		 function );

		return( -1 );
	}
	if( file_object == NULL )
	{
		liberror_error_set(
		 error,
		 LIBERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid file object.",
		 function );

		return( -1 );
	}
	*file_object_io_handle = memory_allocate_structure(
	                          pylnk_file_object_io_handle_t );

	if( *file_object_io_handle == NULL )
	{
		liberror_error_set(
		 error,
		 LIBERROR_ERROR_DOMAIN_MEMORY,
		 LIBERROR_MEMORY_ERROR_INSUFFICIENT,
		 "%s: unable to create file object IO handle.",
		 function );

		goto on_error;
	}
	if( memory_set(
	     *file_object_io_handle,
	     0,
	     sizeof( pylnk_file_object_io_handle_t ) ) == NULL )
	{
		liberror_error_set(
		 error,
		 LIBERROR_ERROR_DOMAIN_MEMORY,
		 LIBERROR_MEMORY_ERROR_SET_FAILED,
		 "%s: unable to clear file object IO handle.",
		 function );

		goto on_error;
	}
	( *file_object_io_handle )->file_object = file_object;

	Py_IncRef(
	 ( *file_object_io_handle )->file_object );

	return( 1 );

on_error:
	if( *file_object_io_handle != NULL )
	{
		memory_free(
		 *file_object_io_handle );

		*file_object_io_handle = NULL;
	}
	return( -1 );
}

/* Initializes the file object IO handle
 * Returns 1 if successful or -1 on error
 */
int pylnk_file_object_initialize(
     libbfio_handle_t **handle,
     PyObject *file_object,
     liberror_error_t **error )
{
	pylnk_file_object_io_handle_t *file_object_io_handle = NULL;
	static char *function                                = "pylnk_file_object_initialize";

	if( handle == NULL )
	{
		liberror_error_set(
		 error,
		 LIBERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid handle.",
		 function );

		return( -1 );
	}
	if( *handle != NULL )
	{
		liberror_error_set(
		 error,
		 LIBERROR_ERROR_DOMAIN_RUNTIME,
		 LIBERROR_RUNTIME_ERROR_VALUE_ALREADY_SET,
		 "%s: invalid handle value already set.",
		 function );

		return( -1 );
	}
	if( pylnk_file_object_io_handle_initialize(
	     &file_object_io_handle,
	     file_object,
	     error ) != 1 )
	{
		liberror_error_set(
		 error,
		 LIBERROR_ERROR_DOMAIN_RUNTIME,
		 LIBERROR_RUNTIME_ERROR_INITIALIZE_FAILED,
		 "%s: unable to create file object IO handle.",
		 function );

		goto on_error;
	}
	if( libbfio_handle_initialize(
	     handle,
	     (intptr_t *) file_object_io_handle,
	     (int (*)(intptr_t **, liberror_error_t **)) pylnk_file_object_io_handle_free,
	     (int (*)(intptr_t **, intptr_t *, liberror_error_t **)) pylnk_file_object_io_handle_clone,
	     (int (*)(intptr_t *, int, liberror_error_t **)) pylnk_file_object_io_handle_open,
	     (int (*)(intptr_t *, liberror_error_t **)) pylnk_file_object_io_handle_close,
	     (ssize_t (*)(intptr_t *, uint8_t *, size_t, liberror_error_t **)) pylnk_file_object_io_handle_read,
	     (ssize_t (*)(intptr_t *, const uint8_t *, size_t, liberror_error_t **)) pylnk_file_object_io_handle_write,
	     (off64_t (*)(intptr_t *, off64_t, int, liberror_error_t **)) pylnk_file_object_io_handle_seek_offset,
	     (int (*)(intptr_t *, liberror_error_t **)) pylnk_file_object_io_handle_exists,
	     (int (*)(intptr_t *, liberror_error_t **)) pylnk_file_object_io_handle_is_open,
	     (int (*)(intptr_t *, size64_t *, liberror_error_t **)) pylnk_file_object_io_handle_get_size,
	     LIBBFIO_FLAG_IO_HANDLE_MANAGED | LIBBFIO_FLAG_IO_HANDLE_CLONE_BY_FUNCTION,
	     error ) != 1 )
	{
		liberror_error_set(
		 error,
		 LIBERROR_ERROR_DOMAIN_RUNTIME,
		 LIBERROR_RUNTIME_ERROR_INITIALIZE_FAILED,
		 "%s: unable to create handle.",
		 function );

		goto on_error;
	}
	return( 1 );

on_error:
	if( file_object_io_handle != NULL )
	{
		pylnk_file_object_io_handle_free(
		 &file_object_io_handle,
		 NULL );
	}
	return( -1 );
}

/* Frees the file object IO handle and its attributes
 * Returns 1 if succesful or -1 on error
 */
int pylnk_file_object_io_handle_free(
     pylnk_file_object_io_handle_t **file_object_io_handle,
     liberror_error_t **error )
{
	static char *function = "pylnk_file_object_io_handle_free";

	if( file_object_io_handle == NULL )
	{
		liberror_error_set(
		 error,
		 LIBERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid file object IO handle.",
		 function );

		return( -1 );
	}
	if( *file_object_io_handle != NULL )
	{
		Py_DecRef(
		 ( *file_object_io_handle )->file_object );

		memory_free(
		 *file_object_io_handle );

		*file_object_io_handle = NULL;
	}
	return( 1 );
}

/* Clones (duplicates) the file object IO handle and its attributes
 * Returns 1 if succesful or -1 on error
 */
int pylnk_file_object_io_handle_clone(
     pylnk_file_object_io_handle_t **destination_file_object_io_handle,
     pylnk_file_object_io_handle_t *source_file_object_io_handle,
     liberror_error_t **error )
{
	static char *function = "pylnk_file_object_io_handle_clone";

	if( destination_file_object_io_handle == NULL )
	{
		liberror_error_set(
		 error,
		 LIBERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid destination file object IO handle.",
		 function );

		return( -1 );
	}
	if( *destination_file_object_io_handle != NULL )
	{
		liberror_error_set(
		 error,
		 LIBERROR_ERROR_DOMAIN_RUNTIME,
		 LIBERROR_RUNTIME_ERROR_VALUE_ALREADY_SET,
		 "%s: destination file object IO handle already set.",
		 function );

		return( -1 );
	}
	if( source_file_object_io_handle == NULL )
	{
		*destination_file_object_io_handle = NULL;

		return( 1 );
	}
	if( pylnk_file_object_io_handle_initialize(
	     destination_file_object_io_handle,
	     source_file_object_io_handle->file_object,
	     error ) != 1 )
	{
		liberror_error_set(
		 error,
		 LIBERROR_ERROR_DOMAIN_RUNTIME,
		 LIBERROR_RUNTIME_ERROR_INITIALIZE_FAILED,
		 "%s: unable to create file object IO handle.",
		 function );

		return( -1 );
	}
	if( *destination_file_object_io_handle == NULL )
	{
		liberror_error_set(
		 error,
		 LIBERROR_ERROR_DOMAIN_RUNTIME,
		 LIBERROR_RUNTIME_ERROR_VALUE_MISSING,
		 "%s: missing destination file object IO handle.",
		 function );

		return( -1 );
	}
	return( 1 );
}

/* Opens the file object IO handle
 * Returns 1 if successful or -1 on error
 */
int pylnk_file_object_io_handle_open(
     pylnk_file_object_io_handle_t *file_object_io_handle,
     int access_flags,
     liberror_error_t **error )
{
	static char *function = "pylnk_file_object_io_handle_open";

	if( file_object_io_handle == NULL )
	{
		liberror_error_set(
		 error,
		 LIBERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid file object IO handle.",
		 function );

		return( -1 );
	}
	if( file_object_io_handle->file_object == NULL )
	{
		liberror_error_set(
		 error,
		 LIBERROR_ERROR_DOMAIN_RUNTIME,
		 LIBERROR_RUNTIME_ERROR_VALUE_MISSING,
		 "%s: invalid file object IO handle - missing file object.",
		 function );

		return( -1 );
	}
	if( ( ( access_flags & LIBBFIO_ACCESS_FLAG_READ ) != 0 )
	 && ( ( access_flags & LIBBFIO_ACCESS_FLAG_WRITE ) != 0 ) )
	{
		liberror_error_set(
		 error,
		 LIBERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBERROR_ARGUMENT_ERROR_UNSUPPORTED_VALUE,
		 "%s: unsupported access flags.",
		 function );

		return( -1 );
	}
	if( ( access_flags & LIBBFIO_ACCESS_FLAG_WRITE ) != 0 )
	{
		liberror_error_set(
		 error,
		 LIBERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBERROR_ARGUMENT_ERROR_UNSUPPORTED_VALUE,
		 "%s: write access currently not supported.",
		 function );

		return( -1 );
	}
	/* No need to do anything here, because the file object is already open
	 */
	file_object_io_handle->access_flags = access_flags;

	return( 1 );
}

/* Closes the file object IO handle
 * Returns 0 if successful or -1 on error
 */
int pylnk_file_object_io_handle_close(
     pylnk_file_object_io_handle_t *file_object_io_handle,
     liberror_error_t **error )
{
	static char *function = "pylnk_file_object_io_handle_close";

	if( file_object_io_handle == NULL )
	{
		liberror_error_set(
		 error,
		 LIBERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid file object IO handle.",
		 function );

		return( -1 );
	}
	if( file_object_io_handle->file_object == NULL )
	{
		liberror_error_set(
		 error,
		 LIBERROR_ERROR_DOMAIN_RUNTIME,
		 LIBERROR_RUNTIME_ERROR_VALUE_MISSING,
		 "%s: invalid file object IO handle - missing file object.",
		 function );

		return( -1 );
	}
	/* Do not close the file object, have Python deal with it
	 */
	file_object_io_handle->access_flags = 0;

	return( 0 );
}

/* Reads a buffer from the file object IO handle
 * Returns the number of bytes read if successful, or -1 on error
 */
ssize_t pylnk_file_object_io_handle_read(
         pylnk_file_object_io_handle_t *file_object_io_handle,
         uint8_t *buffer,
         size_t size,
         liberror_error_t **error )
{
	PyObject *argument_size       = NULL;
	PyObject *exception_string    = NULL;
	PyObject *exception_traceback = NULL;
	PyObject *exception_type      = NULL;
	PyObject *exception_value     = NULL;
	PyObject *method_name         = NULL;
	PyObject *method_result       = NULL;
	char *error_string            = NULL;
	char *safe_buffer             = NULL;
	static char *function         = "pylnk_file_object_io_handle_read";
	PyGILState_STATE gil_state    = 0;
	Py_ssize_t safe_read_count    = 0;
	ssize_t read_count            = 0;
	int result                    = 0;

	if( file_object_io_handle == NULL )
	{
		liberror_error_set(
		 error,
		 LIBERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid file object IO handle.",
		 function );

		return( -1 );
	}
	if( file_object_io_handle->file_object == NULL )
	{
		liberror_error_set(
		 error,
		 LIBERROR_ERROR_DOMAIN_RUNTIME,
		 LIBERROR_RUNTIME_ERROR_VALUE_MISSING,
		 "%s: invalid file object IO handle - missing file object.",
		 function );

		return( -1 );
	}
	if( buffer == NULL )
	{
		liberror_error_set(
		 error,
		 LIBERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid buffer.",
		 function );

		return( -1 );
	}
	if( size > (size_t) SSIZE_MAX )
	{
		liberror_error_set(
		 error,
		 LIBERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBERROR_ARGUMENT_ERROR_VALUE_EXCEEDS_MAXIMUM,
		 "%s: invalid size value exceeds maximum.",
		 function );

		return( -1 );
	}
	if( size > 0 )
	{
		gil_state = PyGILState_Ensure();

		method_name = PyString_FromString(
			       "read" );

		argument_size = PyLong_FromSize_t(
				 size );

		PyErr_Clear();

		method_result = PyObject_CallMethodObjArgs(
				 file_object_io_handle->file_object,
				 method_name,
				 argument_size,
				 NULL );

		if( PyErr_Occurred() )
		{
			PyErr_Fetch(
			 &exception_type,
			 &exception_value,
			 &exception_traceback );

			exception_string = PyObject_Repr(
					    exception_value );

			error_string = PyString_AsString(
					exception_string );

			if( error_string != NULL )
			{
				liberror_error_set(
				 error,
				 LIBERROR_ERROR_DOMAIN_IO,
				 LIBERROR_IO_ERROR_READ_FAILED,
				 "%s: unable to read from file object with error: %s.",
				 function,
				 error_string );
			}
			else
			{
				liberror_error_set(
				 error,
				 LIBERROR_ERROR_DOMAIN_IO,
				 LIBERROR_IO_ERROR_READ_FAILED,
				 "%s: unable to read from file object.",
				 function );
			}
			Py_DecRef(
			 exception_string );

			goto on_error;
		}
		result = PyString_AsStringAndSize(
			  method_result,
			  &safe_buffer,
			  &safe_read_count );

		if( result == -1 )
		{
			PyErr_Fetch(
			 &exception_type,
			 &exception_value,
			 &exception_traceback );

			exception_string = PyObject_Repr(
					    exception_value );

			error_string = PyString_AsString(
					exception_string );

			if( error_string != NULL )
			{
				liberror_error_set(
				 error,
				 LIBERROR_ERROR_DOMAIN_IO,
				 LIBERROR_IO_ERROR_READ_FAILED,
				 "%s: unable to read from file object with error: %s.",
				 function,
				 error_string );
			}
			else
			{
				liberror_error_set(
				 error,
				 LIBERROR_ERROR_DOMAIN_IO,
				 LIBERROR_IO_ERROR_READ_FAILED,
				 "%s: unable to read from file object.",
				 function );
			}
			Py_DecRef(
			 exception_string );

			goto on_error;
		}
		if( safe_read_count > (Py_ssize_t) SSIZE_MAX )
		{
			liberror_error_set(
			 error,
			 LIBERROR_ERROR_DOMAIN_RUNTIME,
			 LIBERROR_RUNTIME_ERROR_VALUE_EXCEEDS_MAXIMUM,
			 "%s: invalid read count value exceeds maximum.",
			 function );

			goto on_error;
		}
		read_count = (ssize_t) safe_read_count;

		if( memory_copy(
		     buffer,
		     safe_buffer,
		     read_count ) == NULL )
		{
			liberror_error_set(
			 error,
			 LIBERROR_ERROR_DOMAIN_MEMORY,
			 LIBERROR_MEMORY_ERROR_COPY_FAILED,
			 "%s: unable to data to buffer.",
			 function );

			goto on_error;
		}
		Py_DecRef(
		 method_result );

		Py_DecRef(
		 argument_size );

		Py_DecRef(
		 method_name );

		PyGILState_Release(
		 gil_state );
	}
	return( read_count );

on_error:
	if( method_result != NULL )
	{
		Py_DecRef(
		 method_result );
	}
	if( argument_size != NULL )
	{
		Py_DecRef(
		 argument_size );
	}
	if( method_name != NULL )
	{
		Py_DecRef(
		 method_name );
	}
	PyGILState_Release(
	 gil_state );

	return( -1 );
}

/* Writes a buffer to the file object IO handle
 * Returns the number of bytes written if successful, or -1 on error
 */
ssize_t pylnk_file_object_io_handle_write(
         pylnk_file_object_io_handle_t *file_object_io_handle,
         const uint8_t *buffer,
         size_t size,
         liberror_error_t **error )
{
	PyObject *argument_string     = NULL;
	PyObject *exception_string    = NULL;
	PyObject *exception_traceback = NULL;
	PyObject *exception_type      = NULL;
	PyObject *exception_value     = NULL;
	PyObject *method_name         = NULL;
	PyObject *method_result       = NULL;
	char *error_string            = NULL;
	static char *function         = "pylnk_file_object_io_handle_write";
	PyGILState_STATE gil_state    = 0;
	ssize_t write_count           = 0;

	if( file_object_io_handle == NULL )
	{
		liberror_error_set(
		 error,
		 LIBERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid file object IO handle.",
		 function );

		return( -1 );
	}
	if( file_object_io_handle->file_object == NULL )
	{
		liberror_error_set(
		 error,
		 LIBERROR_ERROR_DOMAIN_RUNTIME,
		 LIBERROR_RUNTIME_ERROR_VALUE_MISSING,
		 "%s: invalid file object IO handle - missing file object.",
		 function );

		return( -1 );
	}
	if( buffer == NULL )
	{
		liberror_error_set(
		 error,
		 LIBERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid buffer.",
		 function );

		return( -1 );
	}
	if( size > (size_t) SSIZE_MAX )
	{
		liberror_error_set(
		 error,
		 LIBERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBERROR_ARGUMENT_ERROR_VALUE_EXCEEDS_MAXIMUM,
		 "%s: invalid size value exceeds maximum.",
		 function );

		return( -1 );
	}
	if( size > 0 )
	{
		gil_state = PyGILState_Ensure();

		method_name = PyString_FromString(
			       "write" );

/* TODO set up argument_string */

		write_count = (ssize_t) size;

		PyErr_Clear();

		method_result = PyObject_CallMethodObjArgs(
				 file_object_io_handle->file_object,
				 method_name,
				 argument_string,
				 NULL );

		if( PyErr_Occurred() )
		{
			PyErr_Fetch(
			 &exception_type,
			 &exception_value,
			 &exception_traceback );

			exception_string = PyObject_Repr(
					    exception_value );

			error_string = PyString_AsString(
					exception_string );

			if( error_string != NULL )
			{
				liberror_error_set(
				 error,
				 LIBERROR_ERROR_DOMAIN_IO,
				 LIBERROR_IO_ERROR_WRITE_FAILED,
				 "%s: unable to write from file object with error: %s.",
				 function,
				 error_string );
			}
			else
			{
				liberror_error_set(
				 error,
				 LIBERROR_ERROR_DOMAIN_IO,
				 LIBERROR_IO_ERROR_WRITE_FAILED,
				 "%s: unable to write from file object.",
				 function );
			}
			Py_DecRef(
			 exception_string );

			goto on_error;
		}
		Py_DecRef(
		 method_result );

		Py_DecRef(
		 argument_string );

		Py_DecRef(
		 method_name );

		PyGILState_Release(
		 gil_state );
	}
	return( write_count );

on_error:
	if( method_result != NULL )
	{
		Py_DecRef(
		 method_result );
	}
	if( argument_string != NULL )
	{
		Py_DecRef(
		 argument_string );
	}
	if( method_name != NULL )
	{
		Py_DecRef(
		 method_name );
	}
	PyGILState_Release(
	 gil_state );

	return( -1 );
}

/* Seeks a certain offset within the file object IO handle
 * Returns the offset if the seek is successful or -1 on error
 */
off64_t pylnk_file_object_io_handle_seek_offset(
         pylnk_file_object_io_handle_t *file_object_io_handle,
         off64_t offset,
         int whence,
         liberror_error_t **error )
{
	PyObject *argument_offset     = NULL;
	PyObject *argument_whence     = NULL;
	PyObject *exception_string    = NULL;
	PyObject *exception_traceback = NULL;
	PyObject *exception_type      = NULL;
	PyObject *exception_value     = NULL;
	PyObject *method_name         = NULL;
	PyObject *method_result       = NULL;
	char *error_string            = NULL;
	static char *function         = "pylnk_file_object_io_handle_seek_offset";
	PyGILState_STATE gil_state    = 0;

	if( file_object_io_handle == NULL )
	{
		liberror_error_set(
		 error,
		 LIBERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid file object IO handle.",
		 function );

		return( -1 );
	}
	if( file_object_io_handle->file_object == NULL )
	{
		liberror_error_set(
		 error,
		 LIBERROR_ERROR_DOMAIN_RUNTIME,
		 LIBERROR_RUNTIME_ERROR_VALUE_MISSING,
		 "%s: invalid file object IO handle - missing file object.",
		 function );

		return( -1 );
	}
	if( offset > (off64_t) INT64_MAX )
	{
		liberror_error_set(
		 error,
		 LIBERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBERROR_ARGUMENT_ERROR_VALUE_EXCEEDS_MAXIMUM,
		 "%s: invalid offset value exceeds maximum.",
		 function );

		return( -1 );
	}
	if( ( whence != SEEK_CUR )
	 && ( whence != SEEK_END )
	 && ( whence != SEEK_SET ) )
	{
		liberror_error_set(
		 error,
		 LIBERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBERROR_ARGUMENT_ERROR_UNSUPPORTED_VALUE,
		 "%s: unsupported whence.",
		 function );

		return( -1 );
	}
	gil_state = PyGILState_Ensure();

	method_name = PyString_FromString(
	               "seek" );

	argument_offset = PyLong_FromLongLong(
	                   (PY_LONG_LONG) offset );

	argument_whence = PyInt_FromLong(
	                   (long) whence );

	PyErr_Clear();

	method_result = PyObject_CallMethodObjArgs(
	                 file_object_io_handle->file_object,
	                 method_name,
	                 argument_offset,
	                 argument_whence,
	                 NULL );

	if( PyErr_Occurred() )
	{
		PyErr_Fetch(
		 &exception_type,
		 &exception_value,
		 &exception_traceback );

		exception_string = PyObject_Repr(
		                    exception_value );

		error_string = PyString_AsString(
		                exception_string );

		if( error_string != NULL )
		{
			liberror_error_set(
			 error,
			 LIBERROR_ERROR_DOMAIN_IO,
			 LIBERROR_IO_ERROR_SEEK_FAILED,
			 "%s: unable to seek in file object with error: %s.",
			 function,
			 error_string );
		}
		else
		{
			liberror_error_set(
			 error,
			 LIBERROR_ERROR_DOMAIN_IO,
			 LIBERROR_IO_ERROR_SEEK_FAILED,
			 "%s: unable to seek in file object.",
			 function );
		}
		Py_DecRef(
		 exception_string );

		goto on_error;
	}
	Py_DecRef(
	 method_result );

	Py_DecRef(
	 argument_whence );

	Py_DecRef(
	 argument_offset );

	Py_DecRef(
	 method_name );

	PyGILState_Release(
	 gil_state );

/* TODO make sure the offset is returned correctly */

	return( offset );

on_error:
	if( method_result != NULL )
	{
		Py_DecRef(
		 method_result );
	}
	if( argument_whence != NULL )
	{
		Py_DecRef(
		 argument_whence );
	}
	if( argument_offset != NULL )
	{
		Py_DecRef(
		 argument_offset );
	}
	if( method_name != NULL )
	{
		Py_DecRef(
		 method_name );
	}
	PyGILState_Release(
	 gil_state );

	return( -1 );
}

/* Function to determine if a file exists
 * Returns 1 if file exists, 0 if not or -1 on error
 */
int pylnk_file_object_io_handle_exists(
     pylnk_file_object_io_handle_t *file_object_io_handle,
     liberror_error_t **error )
{
	static char *function = "pylnk_file_object_io_handle_exists";

	if( file_object_io_handle == NULL )
	{
		liberror_error_set(
		 error,
		 LIBERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid file object IO handle.",
		 function );

		return( -1 );
	}
	if( file_object_io_handle->file_object == NULL )
	{
		return( 0 );
	}
	return( 1 );
}

/* Check if the file is open
 * Returns 1 if open, 0 if not or -1 on error
 */
int pylnk_file_object_io_handle_is_open(
     pylnk_file_object_io_handle_t *file_object_io_handle,
     liberror_error_t **error )
{
	static char *function = "pylnk_file_object_io_handle_is_open";

	if( file_object_io_handle == NULL )
	{
		liberror_error_set(
		 error,
		 LIBERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid file object IO handle.",
		 function );

		return( -1 );
	}
	if( file_object_io_handle->file_object == NULL )
	{
		liberror_error_set(
		 error,
		 LIBERROR_ERROR_DOMAIN_RUNTIME,
		 LIBERROR_RUNTIME_ERROR_VALUE_MISSING,
		 "%s: invalid file object IO handle - missing file object.",
		 function );

		return( -1 );
	}
	/* As far as BFIO is concerned the file object is always open
	 */
	return( 1 );
}

/* Retrieves the file size
 * Returns 1 if successful or -1 on error
 */
int pylnk_file_object_io_handle_get_size(
     pylnk_file_object_io_handle_t *file_object_io_handle,
     size64_t *size,
     liberror_error_t **error )
{
	PyObject *exception_string    = NULL;
	PyObject *exception_traceback = NULL;
	PyObject *exception_type      = NULL;
	PyObject *exception_value     = NULL;
	PyObject *method_name         = NULL;
	PyObject *method_result       = NULL;
	char *error_string            = NULL;
	static char *function         = "pylnk_file_object_io_handle_get_size";
	PyGILState_STATE gil_state    = 0;
	int result                    = 0;

	if( file_object_io_handle == NULL )
	{
		liberror_error_set(
		 error,
		 LIBERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid file object IO handle.",
		 function );

		return( -1 );
	}
	if( file_object_io_handle->file_object == NULL )
	{
		liberror_error_set(
		 error,
		 LIBERROR_ERROR_DOMAIN_RUNTIME,
		 LIBERROR_RUNTIME_ERROR_VALUE_MISSING,
		 "%s: invalid file object IO handle - missing file object.",
		 function );

		return( -1 );
	}
	gil_state = PyGILState_Ensure();

	method_name = PyString_FromString(
	               "get_size" );

	PyErr_Clear();

	/* Determine if the file object has the get_size method
	 */
	result = PyObject_HasAttr(
	          file_object_io_handle->file_object,
	          method_name );

	Py_DecRef(
	 method_name );

	if( result != 0 )
	{
/* TODO try calling get_size */
	}
	else
	{
/* TODO try tell the current offset, seek to the end, tell the offset and seek back to the current offset */
	}
	PyGILState_Release(
	 gil_state );

	return( 1 );
}

