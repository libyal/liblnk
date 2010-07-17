/*
 * Data string functions
 *
 * Copyright (c) 2009-2010, Joachim Metz <jbmetz@users.sourceforge.net>
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
#include <types.h>

#include <liberror.h>
#include <libnotify.h>

#include "liblnk_data_string.h"
#include "liblnk_definitions.h"
#include "liblnk_libbfio.h"
#include "liblnk_libuna.h"

/* Creates data string
 * Returns 1 if successful or -1 on error
 */
int liblnk_data_string_initialize(
     liblnk_data_string_t **data_string,
     liberror_error_t **error )
{
	static char *function = "liblnk_data_string_initialize";

	if( data_string == NULL )
	{
		liberror_error_set(
		 error,
		 LIBERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid data string.",
		 function );

		return( -1 );
	}
	if( *data_string == NULL )
	{
		*data_string = (liblnk_data_string_t *) memory_allocate(
		                                         sizeof( liblnk_data_string_t ) );

		if( *data_string == NULL )
		{
			liberror_error_set(
			 error,
			 LIBERROR_ERROR_DOMAIN_MEMORY,
			 LIBERROR_MEMORY_ERROR_INSUFFICIENT,
			 "%s: unable to create data string.",
			 function );

			return( -1 );
		}
		if( memory_set(
		     *data_string,
		     0,
		     sizeof( liblnk_data_string_t ) ) == NULL )
		{
			liberror_error_set(
			 error,
			 LIBERROR_ERROR_DOMAIN_MEMORY,
			 LIBERROR_MEMORY_ERROR_SET_FAILED,
			 "%s: unable to clear data string.",
			 function );

			memory_free(
			 *data_string );

			*data_string = NULL;

			return( -1 );
		}
	}
	return( 1 );
}

/* Frees data string
 * Returns 1 if successful or -1 on error
 */
int liblnk_data_string_free(
     liblnk_data_string_t **data_string,
     liberror_error_t **error )
{
	static char *function = "liblnk_data_string_free";

	if( data_string == NULL )
	{
		liberror_error_set(
		 error,
		 LIBERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBERROR_ARGUMENT_ERROR_INVALID_VALUE,
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
         liberror_error_t **error )
{
	uint8_t data_string_size_data[ 2 ];

	static char *function                       = "liblnk_data_string_read";
	ssize_t read_count                          = 0;

#if defined( HAVE_DEBUG_OUTPUT )
	libcstring_system_character_t *value_string = NULL;
	size_t value_string_size                    = 0;
	int result                                  = 0;
#endif

	if( data_string == NULL )
	{
		liberror_error_set(
		 error,
		 LIBERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid data string.",
		 function );

		return( -1 );
	}
	if( io_handle == NULL )
	{
		liberror_error_set(
		 error,
		 LIBERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid IO handle.",
		 function );

		return( -1 );
	}
	/* Store is unicode value for internal use
	 */
	if( ( io_handle->data_flags & LIBLNK_DATA_FLAG_IS_UNICODE ) != 0 )
	{
		data_string->is_unicode = 1;
	}
	else
	{
		data_string->is_unicode = 0;
	}
#if defined( HAVE_DEBUG_OUTPUT )
	if( libnotify_verbose != 0 )
	{
		libnotify_printf(
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
		liberror_error_set(
		 error,
		 LIBERROR_ERROR_DOMAIN_IO,
		 LIBERROR_IO_ERROR_SEEK_FAILED,
		 "%s: unable to seek data string offset: %" PRIi64 ".",
		 function,
		 data_string_offset );

		return( -1 );
	}
	read_count = libbfio_handle_read(
	              file_io_handle,
	              data_string_size_data,
	              2,
	              error );

	if( read_count != (ssize_t) 2 )
	{
		liberror_error_set(
		 error,
		 LIBERROR_ERROR_DOMAIN_IO,
		 LIBERROR_IO_ERROR_READ_FAILED,
		 "%s: unable to read data string size.",
		 function );

		return( -1 );
	}
	byte_stream_copy_to_uint16_little_endian(
	 data_string_size_data,
	 data_string->data_size );
	
#if defined( HAVE_DEBUG_OUTPUT )
	if( libnotify_verbose != 0 )
	{
		libnotify_printf(
		 "%s: data string size\t: %" PRIzd "\n",
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
		liberror_error_set(
		 error,
		 LIBERROR_ERROR_DOMAIN_RUNTIME,
		 LIBERROR_RUNTIME_ERROR_VALUE_EXCEEDS_MAXIMUM,
		 "%s: data string size value exceeds maximum.",
		 function );

		return( -1 );
	}
	data_string->data = (uint8_t *) memory_allocate(
	                                 sizeof( uint8_t ) * data_string->data_size );


	if( data_string->data == NULL )
	{
		liberror_error_set(
		 error,
		 LIBERROR_ERROR_DOMAIN_MEMORY,
		 LIBERROR_MEMORY_ERROR_INSUFFICIENT,
		 "%s: unable to create data string data.",
		 function );

		return( -1 );
	}
	read_count = libbfio_handle_read(
	              file_io_handle,
	              data_string->data,
	              data_string->data_size,
	              error );

	if( read_count != (ssize_t) data_string->data_size )
	{
		liberror_error_set(
		 error,
		 LIBERROR_ERROR_DOMAIN_IO,
		 LIBERROR_IO_ERROR_READ_FAILED,
		 "%s: unable to read data string data.",
		 function );

		return( -1 );
	}
#if defined( HAVE_DEBUG_OUTPUT )
	if( libnotify_verbose != 0 )
	{
		libnotify_printf(
		 "%s: data string data:\n",
		 function );
		libnotify_print_data(
		 data_string->data,
		 data_string->data_size );
	}
#endif

#if defined( HAVE_DEBUG_OUTPUT )
	if( libnotify_verbose != 0 )
	{
		if( data_string->is_unicode != 0 )
		{
#if defined( LIBCSTRING_HAVE_WIDE_SYSTEM_CHARACTER )
			result = libuna_utf16_string_size_from_utf16_stream(
				  data_string->data,
				  data_string->data_size,
				  LIBUNA_ENDIAN_LITTLE,
				  &value_string_size,
				  error );
#else
			result = libuna_utf8_string_size_from_utf16_stream(
				  data_string->data,
				  data_string->data_size,
				  LIBUNA_ENDIAN_LITTLE,
				  &value_string_size,
				  error );
#endif
		}
		else
		{
#if defined( LIBCSTRING_HAVE_WIDE_SYSTEM_CHARACTER )
			result = libuna_utf16_string_size_from_byte_stream(
				  data_string->data,
				  data_string->data_size,
				  io_handle->ascii_codepage,
				  &value_string_size,
				  error );
#else
			result = libuna_utf8_string_size_from_byte_stream(
				  data_string->data,
				  data_string->data_size,
				  io_handle->ascii_codepage,
				  &value_string_size,
				  error );
#endif
		}
		if( result != 1 )
		{
			liberror_error_set(
			 error,
			 LIBERROR_ERROR_DOMAIN_RUNTIME,
			 LIBERROR_RUNTIME_ERROR_GET_FAILED,
			 "%s: unable to determine size of data string.",
			 function );

			return( -1 );
		}
		value_string = (libcstring_system_character_t *) memory_allocate(
								  sizeof( libcstring_system_character_t ) * value_string_size );

		if( value_string == NULL )
		{
			liberror_error_set(
			 error,
			 LIBERROR_ERROR_DOMAIN_MEMORY,
			 LIBERROR_MEMORY_ERROR_INSUFFICIENT,
			 "%s: unable to create data string.",
			 function );

			return( -1 );
		}
		if( data_string->is_unicode != 0 )
		{
#if defined( LIBCSTRING_HAVE_WIDE_SYSTEM_CHARACTER )
			result = libuna_utf16_string_copy_from_utf16_stream(
				  (libuna_utf16_character_t *) value_string,
				  value_string_size,
				  data_string->data,
				  data_string->data_size,
				  LIBUNA_ENDIAN_LITTLE,
				  error );
#else
			result = libuna_utf8_string_copy_from_utf16_stream(
				  (libuna_utf8_character_t *) value_string,
				  value_string_size,
				  data_string->data,
				  data_string->data_size,
				  LIBUNA_ENDIAN_LITTLE,
				  error );
#endif
		}
		else
		{
#if defined( LIBCSTRING_HAVE_WIDE_SYSTEM_CHARACTER )
			result = libuna_utf16_string_copy_from_byte_stream(
				  (libuna_utf16_character_t *) value_string,
				  value_string_size,
				  data_string->data,
				  data_string->data_size,
				  io_handle->ascii_codepage,
				  error );
#else
			result = libuna_utf8_string_copy_from_byte_stream(
				  (libuna_utf8_character_t *) value_string,
				  value_string_size,
				  data_string->data,
				  data_string->data_size,
				  io_handle->ascii_codepage,
				  error );
#endif
		}
		if( result != 1 )
		{
			liberror_error_set(
			 error,
			 LIBERROR_ERROR_DOMAIN_RUNTIME,
			 LIBERROR_RUNTIME_ERROR_SET_FAILED,
			 "%s: unable to set data string.",
			 function );

			memory_free(
			 value_string );

			return( -1 );
		}
		libnotify_printf(
		 "%s: data string\t: %" PRIs_LIBCSTRING_SYSTEM "\n",
		 function,
		 value_string );

		libnotify_printf(
		 "\n" );

		memory_free(
		 value_string );
	}
#endif
	return( read_count + 2 );
}

