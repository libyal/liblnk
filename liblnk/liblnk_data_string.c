/*
 * Data string functions
 *
 * Copyright (C) 2009-2019, Joachim Metz <joachim.metz@gmail.com>
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
#include <byte_stream.h>
#include <memory.h>
#include <narrow_string.h>
#include <system_string.h>
#include <types.h>
#include <wide_string.h>

#include "liblnk_data_string.h"
#include "liblnk_debug.h"
#include "liblnk_definitions.h"
#include "liblnk_libbfio.h"
#include "liblnk_libcerror.h"
#include "liblnk_libcnotify.h"
#include "liblnk_libuna.h"

/* Creates a data string
 * Make sure the value data_string is referencing, is set to NULL
 * Returns 1 if successful or -1 on error
 */
int liblnk_data_string_initialize(
     liblnk_data_string_t **data_string,
     libcerror_error_t **error )
{
	static char *function = "liblnk_data_string_initialize";

	if( data_string == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid data string.",
		 function );

		return( -1 );
	}
	if( *data_string != NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_VALUE_ALREADY_SET,
		 "%s: invalid data string value already set.",
		 function );

		return( -1 );
	}
	*data_string = memory_allocate_structure(
	                liblnk_data_string_t );

	if( *data_string == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_MEMORY,
		 LIBCERROR_MEMORY_ERROR_INSUFFICIENT,
		 "%s: unable to create data string.",
		 function );

		goto on_error;
	}
	if( memory_set(
	     *data_string,
	     0,
	     sizeof( liblnk_data_string_t ) ) == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_MEMORY,
		 LIBCERROR_MEMORY_ERROR_SET_FAILED,
		 "%s: unable to clear data string.",
		 function );

		goto on_error;
	}
	return( 1 );

on_error:
	if( *data_string != NULL )
	{
		memory_free(
		 *data_string );

		*data_string = NULL;
	}
	return( -1 );
}

/* Frees a data string
 * Returns 1 if successful or -1 on error
 */
int liblnk_data_string_free(
     liblnk_data_string_t **data_string,
     libcerror_error_t **error )
{
	static char *function = "liblnk_data_string_free";

	if( data_string == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid data string.",
		 function );

		return( -1 );
	}
	if( *data_string != NULL )
	{
		if( ( *data_string )->data != NULL )
		{
			memory_free(
			 ( *data_string )->data );
		}
		memory_free(
		 *data_string );

		*data_string = NULL;
	}
	return( 1 );
}

/* Reads a data string
 * Returns the number of bytes read if successful or -1 on error
 */
ssize_t liblnk_data_string_read(
         liblnk_data_string_t *data_string,
         liblnk_io_handle_t *io_handle,
         libbfio_handle_t *file_io_handle,
         off64_t data_string_offset,
         libcerror_error_t **error )
{
	uint8_t data_string_size_data[ 2 ];

	static char *function = "liblnk_data_string_read";
	ssize_t read_count    = 0;

	if( data_string == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid data string.",
		 function );

		return( -1 );
	}
	if( data_string->data != NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_VALUE_ALREADY_SET,
		 "%s: invalid data string - data already set.",
		 function );

		return( -1 );
	}
	if( io_handle == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid IO handle.",
		 function );

		return( -1 );
	}
	/* Store is unicode value for internal use
	 */
	data_string->is_unicode = io_handle->is_unicode;

#if defined( HAVE_DEBUG_OUTPUT )
	if( libcnotify_verbose != 0 )
	{
		libcnotify_printf(
		 "%s: reading data string at offset: %" PRIi64 " (0x%08" PRIx64 ")\n",
		 function,
		 data_string_offset,
		 data_string_offset );
	}
#endif
	if( libbfio_handle_seek_offset(
	     file_io_handle,
	     data_string_offset,
	     SEEK_SET,
	     error ) == -1 )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_IO,
		 LIBCERROR_IO_ERROR_SEEK_FAILED,
		 "%s: unable to seek data string offset: %" PRIi64 ".",
		 function,
		 data_string_offset );

		goto on_error;
	}
	read_count = libbfio_handle_read_buffer(
	              file_io_handle,
	              data_string_size_data,
	              2,
	              error );

	if( read_count != (ssize_t) 2 )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_IO,
		 LIBCERROR_IO_ERROR_READ_FAILED,
		 "%s: unable to read data string size.",
		 function );

		goto on_error;
	}
	byte_stream_copy_to_uint16_little_endian(
	 data_string_size_data,
	 data_string->data_size );
	
#if defined( HAVE_DEBUG_OUTPUT )
	if( libcnotify_verbose != 0 )
	{
		libcnotify_printf(
		 "%s: data string size\t\t\t\t: %" PRIzd "\n",
		 function,
		 data_string->data_size );
	}
#endif

	/* The size contains the number of characters
	 * a Unicode (UTF-16) string requires 2 bytes per character
	 */
	if( data_string->is_unicode != 0 )
	{
		data_string->data_size *= 2;
	}
	if( data_string->data_size > (size_t) SSIZE_MAX )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_VALUE_EXCEEDS_MAXIMUM,
		 "%s: data string size value exceeds maximum.",
		 function );

		goto on_error;
	}
	data_string->data = (uint8_t *) memory_allocate(
	                                 sizeof( uint8_t ) * data_string->data_size );


	if( data_string->data == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_MEMORY,
		 LIBCERROR_MEMORY_ERROR_INSUFFICIENT,
		 "%s: unable to create data string data.",
		 function );

		goto on_error;
	}
	read_count = libbfio_handle_read_buffer(
	              file_io_handle,
	              data_string->data,
	              data_string->data_size,
	              error );

	if( read_count != (ssize_t) data_string->data_size )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_IO,
		 LIBCERROR_IO_ERROR_READ_FAILED,
		 "%s: unable to read data string data.",
		 function );

		goto on_error;
	}
#if defined( HAVE_DEBUG_OUTPUT )
	if( libcnotify_verbose != 0 )
	{
		libcnotify_printf(
		 "%s: data string data:\n",
		 function );
		libcnotify_print_data(
		 data_string->data,
		 data_string->data_size,
		 0 );
	}
#endif
#if defined( HAVE_DEBUG_OUTPUT )
	if( libcnotify_verbose != 0 )
	{
		if( data_string->is_unicode != 0 )
		{
			if( liblnk_debug_print_utf16_string_value(
			     function,
			     "data string\t\t\t\t\t",
			     data_string->data,
			     data_string->data_size,
			     LIBUNA_ENDIAN_LITTLE,
			     error ) != 1 )
			{
				libcerror_error_set(
				 error,
				 LIBCERROR_ERROR_DOMAIN_RUNTIME,
				 LIBCERROR_RUNTIME_ERROR_PRINT_FAILED,
				 "%s: unable to print UTF-16 string value.",
				 function );

				goto on_error;
			}
		}
		else
		{
			if( liblnk_debug_print_string_value(
			     function,
			     "data string\t\t\t\t\t",
			     data_string->data,
			     data_string->data_size,
			     io_handle->ascii_codepage,
			     error ) != 1 )
			{
				libcerror_error_set(
				 error,
				 LIBCERROR_ERROR_DOMAIN_RUNTIME,
				 LIBCERROR_RUNTIME_ERROR_PRINT_FAILED,
				 "%s: unable to print string value.",
				 function );

				goto on_error;
			}
		}
		libcnotify_printf(
		 "\n" );
	}
#endif
	return( read_count + 2 );

on_error:
	if( data_string->data != NULL )
	{
		memory_free(
		 data_string->data );

		data_string->data = NULL;
	}
	return( -1 );
}

/* Retrieves the size of the UTF-8 encoded data string
 * The size includes the end of string character
 * Returns 1 if successful, 0 if value is not available or -1 on error
 */
int liblnk_data_string_get_utf8_string_size(
     liblnk_data_string_t *data_string,
     int ascii_codepage,
     size_t *utf8_string_size,
     libcerror_error_t **error )
{
	static char *function = "liblnk_data_string_get_utf8_string_size";
	int result            = 0;

	if( data_string == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid data string.",
		 function );

		return( -1 );
	}
	if( data_string->data == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_VALUE_MISSING,
		 "%s: invalid data string - missing data.",
		 function );

		return( -1 );
	}
	if( utf8_string_size == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid UTF-8 string size.",
		 function );

		return( -1 );
	}
	if( data_string->is_unicode != 0 )
	{
		result = libuna_utf8_string_size_from_utf16_stream(
			  data_string->data,
			  data_string->data_size,
			  LIBUNA_ENDIAN_LITTLE,
			  utf8_string_size,
			  error );
	}
	else
	{
		result = libuna_utf8_string_size_from_byte_stream(
			  data_string->data,
			  data_string->data_size,
			  ascii_codepage,
			  utf8_string_size,
			  error );
	}
	if( result != 1 )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_GET_FAILED,
		 "%s: unable to retrieve UTF-8 data string size.",
		 function );

		return( -1 );
	}
	return( 1 );
}

/* Retrieves the UTF-8 encoded data string
 * The size should include the end of string character
 * Returns 1 if successful, 0 if value is not available or -1 on error
 */
int liblnk_data_string_get_utf8_string(
     liblnk_data_string_t *data_string,
     int ascii_codepage,
     uint8_t *utf8_string,
     size_t utf8_string_size,
     libcerror_error_t **error )
{
	static char *function = "liblnk_data_string_get_utf8_string";
	int result            = 0;

	if( data_string == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid data string.",
		 function );

		return( -1 );
	}
	if( data_string->data == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_VALUE_MISSING,
		 "%s: invalid data string - missing data.",
		 function );

		return( -1 );
	}
	if( utf8_string == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid UTF-8 string.",
		 function );

		return( -1 );
	}
	if( utf8_string_size > (size_t) SSIZE_MAX )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_VALUE_EXCEEDS_MAXIMUM,
		 "%s: invalid UTF-8 string size value exceeds maximum.",
		 function );

		return( -1 );
	}
	if( data_string->is_unicode != 0 )
	{
		result = libuna_utf8_string_copy_from_utf16_stream(
			  utf8_string,
			  utf8_string_size,
			  data_string->data,
			  data_string->data_size,
			  LIBUNA_ENDIAN_LITTLE,
			  error );
	}
	else
	{
		result = libuna_utf8_string_copy_from_byte_stream(
			  utf8_string,
			  utf8_string_size,
			  data_string->data,
			  data_string->data_size,
			  ascii_codepage,
			  error );
	}
	if( result != 1 )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_SET_FAILED,
		 "%s: unable to set UTF-8 data string.",
		 function );

		return( -1 );
	}
	return( 1 );
}

/* Retrieves the size of the UTF-16 encoded data string
 * The size includes the end of string character
 * Returns 1 if successful, 0 if value is not available or -1 on error
 */
int liblnk_data_string_get_utf16_string_size(
     liblnk_data_string_t *data_string,
     int ascii_codepage,
     size_t *utf16_string_size,
     libcerror_error_t **error )
{
	static char *function = "liblnk_data_string_get_utf16_string_size";
	int result            = 0;

	if( data_string == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid data string.",
		 function );

		return( -1 );
	}
	if( data_string->data == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_VALUE_MISSING,
		 "%s: invalid data string - missing data.",
		 function );

		return( -1 );
	}
	if( utf16_string_size == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid UTF-16 string size.",
		 function );

		return( -1 );
	}
	if( data_string->is_unicode != 0 )
	{
		result = libuna_utf16_string_size_from_utf16_stream(
			  data_string->data,
			  data_string->data_size,
			  LIBUNA_ENDIAN_LITTLE,
			  utf16_string_size,
			  error );
	}
	else
	{
		result = libuna_utf16_string_size_from_byte_stream(
			  data_string->data,
			  data_string->data_size,
			  ascii_codepage,
			  utf16_string_size,
			  error );
	}
	if( result != 1 )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_GET_FAILED,
		 "%s: unable to retrieve UTF-16 data string size.",
		 function );

		return( -1 );
	}
	return( 1 );
}

/* Retrieves the UTF-16 encoded data string
 * The size should include the end of string character
 * Returns 1 if successful, 0 if value is not available or -1 on error
 */
int liblnk_data_string_get_utf16_string(
     liblnk_data_string_t *data_string,
     int ascii_codepage,
     uint16_t *utf16_string,
     size_t utf16_string_size,
     libcerror_error_t **error )
{
	static char *function = "liblnk_data_string_get_utf16_string";
	int result            = 0;

	if( data_string == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid data string.",
		 function );

		return( -1 );
	}
	if( data_string->data == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_VALUE_MISSING,
		 "%s: invalid data string - missing data.",
		 function );

		return( -1 );
	}
	if( utf16_string == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid UTF-16 string.",
		 function );

		return( -1 );
	}
	if( utf16_string_size > (size_t) SSIZE_MAX )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_VALUE_EXCEEDS_MAXIMUM,
		 "%s: invalid UTF-16 string size value exceeds maximum.",
		 function );

		return( -1 );
	}
	if( data_string->is_unicode != 0 )
	{
		result = libuna_utf16_string_copy_from_utf16_stream(
			  utf16_string,
			  utf16_string_size,
			  data_string->data,
			  data_string->data_size,
			  LIBUNA_ENDIAN_LITTLE,
			  error );
	}
	else
	{
		result = libuna_utf16_string_copy_from_byte_stream(
			  utf16_string,
			  utf16_string_size,
			  data_string->data,
			  data_string->data_size,
			  ascii_codepage,
			  error );
	}
	if( result != 1 )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_SET_FAILED,
		 "%s: unable to set UTF-16 data string.",
		 function );

		return( -1 );
	}
	return( 1 );
}

