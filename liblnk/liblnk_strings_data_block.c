/*
 * Strings data block functions
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
#include <memory.h>
#include <types.h>

#include "liblnk_data_block.h"
#include "liblnk_data_string.h"
#include "liblnk_debug.h"
#include "liblnk_definitions.h"
#include "liblnk_libcerror.h"
#include "liblnk_libcnotify.h"
#include "liblnk_libuna.h"

#include "lnk_data_blocks.h"

/* Reads a strings data block
 * Returns 1 if successful or -1 on error
 */
int liblnk_strings_data_block_read(
     liblnk_data_block_t *data_block,
     libcerror_error_t **error )
{
	liblnk_data_string_t *data_string                 = NULL;
	liblnk_internal_data_block_t *internal_data_block = NULL;
	const uint8_t *string_data                        = NULL;
	const uint8_t *unicode_string_data                = NULL;
	static char *function                             = "liblnk_data_block_strings_read";
	size_t string_size                                = 0;
	size_t unicode_string_size                        = 0;

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
	internal_data_block = (liblnk_internal_data_block_t *) data_block;

	if( internal_data_block->data == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_VALUE_MISSING,
		 "%s: invalid data block - missing data.",
		 function );

		return( -1 );
	}
	if( internal_data_block->data_size < sizeof( lnk_data_block_strings_t ) )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_VALUE_OUT_OF_BOUNDS,
		 "%s: invalid data block - data size out of bounds.",
		 function );

		return( -1 );
	}
	if( internal_data_block->value != NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_VALUE_ALREADY_SET,
		 "%s: invalid data block - value already set.",
		 function );

		return( -1 );
	}
	if( liblnk_data_string_initialize(
	     &data_string,
	     error ) != 1 )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_INITIALIZE_FAILED,
		 "%s: unable to create environment variables location.",
		 function );

		goto on_error;
	}
	string_data = ( (lnk_data_block_strings_t *) internal_data_block->data )->string;

	for( string_size = 0;
	     string_size < 260;
	     string_size++ )
	{
		if( string_data[ string_size ] == 0 )
		{
			break;
		}
	}
	if( ( string_size == 260 )
	 || ( string_data[ string_size ] != 0 ) )
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
		 string_data,
		 260,
		 LIBCNOTIFY_PRINT_DATA_FLAG_GROUP_DATA );

		if( liblnk_debug_print_string_value(
		     function,
		     "string\t\t\t\t\t",
		     string_data,
		     260,
		     internal_data_block->ascii_codepage,
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
#endif /* defined( HAVE_DEBUG_OUTPUT ) */

	unicode_string_data = ( (lnk_data_block_strings_t *) internal_data_block->data )->unicode_string;

	for( unicode_string_size = 0;
	     unicode_string_size < 520;
	     unicode_string_size += 2 )
	{
		if( ( unicode_string_data[ unicode_string_size ] == 0 )
		 && ( unicode_string_data[ unicode_string_size + 1 ] == 0 ) )
		{
			break;
		}
	}
	if( ( unicode_string_size == 520 )
	 || ( unicode_string_data[ unicode_string_size ] != 0 )
	 || ( unicode_string_data[ unicode_string_size + 1 ] != 0 ) )
	{
#if defined( HAVE_VERBOSE_OUTPUT )
		if( libcnotify_verbose != 0 )
		{
			libcnotify_printf(
			 "%s: unsupported Unicode string\n" );
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
		 "%s: Unicode string data:\n",
		 function );
		libcnotify_print_data(
		 unicode_string_data,
		 520,
		 LIBCNOTIFY_PRINT_DATA_FLAG_GROUP_DATA );

		if( liblnk_debug_print_utf16_string_value(
		     function,
		     "Unicode string\t\t\t\t",
		     unicode_string_data,
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
#endif /* defined( HAVE_DEBUG_OUTPUT ) */

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
		     unicode_string_data,
		     data_string->data_size ) == NULL )
		{
			libcerror_error_set(
			 error,
			 LIBCERROR_ERROR_DOMAIN_MEMORY,
			 LIBCERROR_MEMORY_ERROR_COPY_FAILED,
			 "%s: unable to copy Unicode string data.",
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
		     unicode_string_data,
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
		if( internal_data_block->data_size > sizeof( lnk_data_block_strings_t ) )
		{
			libcnotify_printf(
			 "%s: trailing data:\n",
			 function );
			libcnotify_print_data(
			 &( internal_data_block->data[ sizeof( lnk_data_block_strings_t ) ] ),
			 internal_data_block->data_size - sizeof( lnk_data_block_strings_t ),
			 LIBCNOTIFY_PRINT_DATA_FLAG_GROUP_DATA );
		}
	}
#endif /* defined( HAVE_DEBUG_OUTPUT ) */

	internal_data_block->value          = (intptr_t *) data_string;
	internal_data_block->free_value     = (int(*)(intptr_t **, libcerror_error_t **)) &liblnk_data_string_free;

	return( 1 );

on_error:
	if( data_string != NULL )
	{
		liblnk_data_string_free(
		 &data_string,
		 NULL );
	}
	return( -1 );
}

/* Retrieves the size of the UTF-8 string
 * The size includes the end of string character
 * Returns 1 if successful or -1 on error
 */
int liblnk_strings_data_block_get_utf8_string_size(
     liblnk_data_block_t *data_block,
     size_t *utf8_string_size,
     libcerror_error_t **error )
{
	liblnk_internal_data_block_t *internal_data_block = NULL;
	static char *function                             = "liblnk_strings_data_block_get_utf8_string_size";

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
	internal_data_block = (liblnk_internal_data_block_t *) data_block;

	if( internal_data_block->value == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_VALUE_MISSING,
		 "%s: invalid data block - missing value.",
		 function );

		return( -1 );
	}
	if( internal_data_block->data_size < 4 )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_VALUE_OUT_OF_BOUNDS,
		 "%s: invalid data block - data size value out of bounds.",
		 function );

		return( -1 );
	}
	if( ( internal_data_block->signature != LIBLNK_DATA_BLOCK_SIGNATURE_ENVIRONMENT_VARIABLES_LOCATION )
	 && ( internal_data_block->signature != LIBLNK_DATA_BLOCK_SIGNATURE_DARWIN_PROPERTIES )
	 && ( internal_data_block->signature != LIBLNK_DATA_BLOCK_SIGNATURE_ICON_LOCATION ) )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_UNSUPPORTED_VALUE,
		 "%s: invalid data block - unsupported signature.",
		 function );

		return( -1 );
	}
	if( liblnk_data_string_get_utf8_string_size(
	     (liblnk_data_string_t *) internal_data_block->value,
	     internal_data_block->ascii_codepage,
	     utf8_string_size,
	     error ) != 1 )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_GET_FAILED,
		 "%s: unable to retrieve UTF-8 string size.",
		 function );

		return( -1 );
	}
	return( 1 );
}

/* Retrieves the UTF-8 string
 * The size should include the end of string character
 * Returns 1 if successful or -1 on error
 */
int liblnk_strings_data_block_get_utf8_string(
     liblnk_data_block_t *data_block,
     uint8_t *utf8_string,
     size_t utf8_string_size,
     libcerror_error_t **error )
{
	liblnk_internal_data_block_t *internal_data_block = NULL;
	static char *function                             = "liblnk_strings_data_block_get_utf8_string";

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
	internal_data_block = (liblnk_internal_data_block_t *) data_block;

	if( internal_data_block->value == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_VALUE_MISSING,
		 "%s: invalid data block - missing value.",
		 function );

		return( -1 );
	}
	if( internal_data_block->data_size < 4 )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_VALUE_OUT_OF_BOUNDS,
		 "%s: invalid data block - data size value out of bounds.",
		 function );

		return( -1 );
	}
	if( ( internal_data_block->signature != LIBLNK_DATA_BLOCK_SIGNATURE_ENVIRONMENT_VARIABLES_LOCATION )
	 && ( internal_data_block->signature != LIBLNK_DATA_BLOCK_SIGNATURE_DARWIN_PROPERTIES )
	 && ( internal_data_block->signature != LIBLNK_DATA_BLOCK_SIGNATURE_ICON_LOCATION ) )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_UNSUPPORTED_VALUE,
		 "%s: invalid data block - unsupported signature.",
		 function );

		return( -1 );
	}
	if( liblnk_data_string_get_utf8_string(
	     (liblnk_data_string_t *) internal_data_block->value,
	     internal_data_block->ascii_codepage,
	     utf8_string,
	     utf8_string_size,
	     error ) != 1 )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_GET_FAILED,
		 "%s: unable to retrieve UTF-8 string.",
		 function );

		return( -1 );
	}
	return( 1 );
}

/* Retrieves the size of the UTF-16 string
 * The size includes the end of string character
 * Returns 1 if successful or -1 on error
 */
int liblnk_strings_data_block_get_utf16_string_size(
     liblnk_data_block_t *data_block,
     size_t *utf16_string_size,
     libcerror_error_t **error )
{
	liblnk_internal_data_block_t *internal_data_block = NULL;
	static char *function                             = "liblnk_strings_data_block_get_utf16_string_size";

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
	internal_data_block = (liblnk_internal_data_block_t *) data_block;

	if( internal_data_block->value == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_VALUE_MISSING,
		 "%s: invalid data block - missing value.",
		 function );

		return( -1 );
	}
	if( internal_data_block->data_size < 4 )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_VALUE_OUT_OF_BOUNDS,
		 "%s: invalid data block - data size value out of bounds.",
		 function );

		return( -1 );
	}
	if( ( internal_data_block->signature != LIBLNK_DATA_BLOCK_SIGNATURE_ENVIRONMENT_VARIABLES_LOCATION )
	 && ( internal_data_block->signature != LIBLNK_DATA_BLOCK_SIGNATURE_DARWIN_PROPERTIES )
	 && ( internal_data_block->signature != LIBLNK_DATA_BLOCK_SIGNATURE_ICON_LOCATION ) )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_UNSUPPORTED_VALUE,
		 "%s: invalid data block - unsupported signature.",
		 function );

		return( -1 );
	}
	if( liblnk_data_string_get_utf16_string_size(
	     (liblnk_data_string_t *) internal_data_block->value,
	     internal_data_block->ascii_codepage,
	     utf16_string_size,
	     error ) != 1 )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_GET_FAILED,
		 "%s: unable to retrieve UTF-16 string size.",
		 function );

		return( -1 );
	}
	return( 1 );
}

/* Retrieves the UTF-16 string
 * The size should include the end of string character
 * Returns 1 if successful or -1 on error
 */
int liblnk_strings_data_block_get_utf16_string(
     liblnk_data_block_t *data_block,
     uint16_t *utf16_string,
     size_t utf16_string_size,
     libcerror_error_t **error )
{
	liblnk_internal_data_block_t *internal_data_block = NULL;
	static char *function                             = "liblnk_strings_data_block_get_utf16_string";

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
	internal_data_block = (liblnk_internal_data_block_t *) data_block;

	if( internal_data_block->value == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_VALUE_MISSING,
		 "%s: invalid data block - missing value.",
		 function );

		return( -1 );
	}
	if( internal_data_block->data_size < 4 )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_VALUE_OUT_OF_BOUNDS,
		 "%s: invalid data block - data size value out of bounds.",
		 function );

		return( -1 );
	}
	if( ( internal_data_block->signature != LIBLNK_DATA_BLOCK_SIGNATURE_ENVIRONMENT_VARIABLES_LOCATION )
	 && ( internal_data_block->signature != LIBLNK_DATA_BLOCK_SIGNATURE_DARWIN_PROPERTIES )
	 && ( internal_data_block->signature != LIBLNK_DATA_BLOCK_SIGNATURE_ICON_LOCATION ) )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_UNSUPPORTED_VALUE,
		 "%s: invalid data block - unsupported signature.",
		 function );

		return( -1 );
	}
	if( liblnk_data_string_get_utf16_string(
	     (liblnk_data_string_t *) internal_data_block->value,
	     internal_data_block->ascii_codepage,
	     utf16_string,
	     utf16_string_size,
	     error ) != 1 )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_GET_FAILED,
		 "%s: unable to retrieve UTF-16 string.",
		 function );

		return( -1 );
	}
	return( 1 );
}

