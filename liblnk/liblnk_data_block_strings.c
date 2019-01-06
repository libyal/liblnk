/*
 * Data block strings functions
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
#include <memory.h>
#include <types.h>

#include "liblnk_data_block.h"
#include "liblnk_data_block_strings.h"
#include "liblnk_data_string.h"
#include "liblnk_debug.h"
#include "liblnk_io_handle.h"
#include "liblnk_libcerror.h"
#include "liblnk_libcnotify.h"
#include "liblnk_libuna.h"

#include "lnk_data_blocks.h"

/* Reads a data block strings
 * Returns the number of bytes read if successful or -1 on error
 */
int liblnk_data_block_strings_read(
     liblnk_data_string_t *data_string,
     liblnk_data_block_t *data_block,
     liblnk_io_handle_t *io_handle,
     libcerror_error_t **error )
{
	lnk_data_block_strings_t *data_block_strings_data = NULL;
	static char *function                             = "liblnk_data_block_strings_read";
	size_t string_size                                = 0;
	size_t unicode_string_size                        = 0;

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
	if( data_block == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid data block.",
		 function );

		return( -1 );
	}
	if( data_block->data == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_VALUE_MISSING,
		 "%s: invalid data block - missing data.",
		 function );

		return( -1 );
	}
	if( data_block->data_size < sizeof( lnk_data_block_strings_t ) )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_VALUE_OUT_OF_BOUNDS,
		 "%s: invalid data block - data size too small.",
		 function );

		return( -1 );
	}
	data_block_strings_data = (lnk_data_block_strings_t *) data_block->data;

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
	for( string_size = 0;
	     string_size < 260;
	     string_size++ )
	{
		if( data_block_strings_data->string[ string_size ] == 0 )
		{
			break;
		}
	}
	if( ( string_size == 260 )
	 || ( data_block_strings_data->string[ string_size ] != 0 ) )
	{
#if defined( HAVE_VERBOSE_OUTPUT )
		if( libcnotify_verbose != 0 )
		{
			libcnotify_printf(
			 "%s: unsupported data block strings\n" );
		}
#endif
		string_size = 0;
	}
	else
	{
		string_size += 1;
	}
#if defined( HAVE_DEBUG_OUTPUT )
	if( libcnotify_verbose != 0 )
	{
		libcnotify_printf(
		 "%s: string data:\n",
		 function );
		libcnotify_print_data(
		 data_block_strings_data->string,
		 260,
		 LIBCNOTIFY_PRINT_DATA_FLAG_GROUP_DATA );

		if( liblnk_debug_print_string_value(
		     function,
		     "string\t\t\t\t\t",
		     data_block_strings_data->string,
		     260,
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
#endif
	for( unicode_string_size = 0;
	     unicode_string_size < 520;
	     unicode_string_size += 2 )
	{
		if( ( data_block_strings_data->unicode_string[ unicode_string_size ] == 0 )
		 && ( data_block_strings_data->unicode_string[ unicode_string_size + 1 ] == 0 ) )
		{
			break;
		}
	}
	if( ( unicode_string_size == 520 )
	 || ( data_block_strings_data->unicode_string[ unicode_string_size ] != 0 )
	 || ( data_block_strings_data->unicode_string[ unicode_string_size + 1 ] != 0 ) )
	{
#if defined( HAVE_VERBOSE_OUTPUT )
		if( libcnotify_verbose != 0 )
		{
			libcnotify_printf(
			 "%s: unsupported unicode string\n" );
		}
#endif
		unicode_string_size = 0;
	}
	else
	{
		unicode_string_size += 2;
	}
#if defined( HAVE_DEBUG_OUTPUT )
	if( libcnotify_verbose != 0 )
	{
		libcnotify_printf(
		 "%s: unicode string data:\n",
		 function );
		libcnotify_print_data(
		 data_block_strings_data->unicode_string,
		 520,
		 LIBCNOTIFY_PRINT_DATA_FLAG_GROUP_DATA );

		if( liblnk_debug_print_utf16_string_value(
		     function,
		     "unicode string\t\t\t\t",
		     data_block_strings_data->unicode_string,
		     520,
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
		libcnotify_printf(
		 "\n" );
	}
#endif
	if( unicode_string_size > 0 )
	{
		data_string->data_size = unicode_string_size;

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
		if( memory_copy(
		     data_string->data,
		     data_block_strings_data->unicode_string,
		     data_string->data_size ) == NULL )
		{
			libcerror_error_set(
			 error,
			 LIBCERROR_ERROR_DOMAIN_MEMORY,
			 LIBCERROR_MEMORY_ERROR_COPY_FAILED,
			 "%s: unable to copy unicode string data.",
			 function );

			goto on_error;
		}
		data_string->is_unicode = 1;
	}
	else if( string_size > 0 )
	{
		data_string->data_size = string_size;

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
		if( memory_copy(
		     data_string->data,
		     data_block_strings_data->string,
		     data_string->data_size ) == NULL )
		{
			libcerror_error_set(
			 error,
			 LIBCERROR_ERROR_DOMAIN_MEMORY,
			 LIBCERROR_MEMORY_ERROR_COPY_FAILED,
			 "%s: unable to copy string data.",
			 function );

			goto on_error;
		}
		data_string->is_unicode = 0;
	}
#if defined( HAVE_DEBUG_OUTPUT )
	if( libcnotify_verbose != 0 )
	{
		if( data_block->data_size > sizeof( lnk_data_block_strings_t ) )
		{
			libcnotify_printf(
			 "%s: trailing data:\n",
			 function );
			libcnotify_print_data(
			 &( data_block->data[ sizeof( lnk_data_block_strings_t ) ] ),
			 data_block->data_size - sizeof( lnk_data_block_strings_t ),
			 LIBCNOTIFY_PRINT_DATA_FLAG_GROUP_DATA );
		}
	}
#endif
	return( 1 );

on_error:
	if( data_string->data != NULL )
	{
		memory_free(
		 data_string->data );

		data_string->data = NULL;
	}
	data_string->data_size = 0;

	return( -1 );
}

