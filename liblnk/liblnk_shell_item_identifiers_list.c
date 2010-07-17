/*
 * Shell item identifiers list functions
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

#include "liblnk_definitions.h"
#include "liblnk_libbfio.h"
#include "liblnk_libfwsi.h"
#include "liblnk_shell_item_identifiers_list.h"

/* Creates shell item identifiers
 * Returns 1 if successful or -1 on error
 */
int liblnk_shell_item_identifiers_list_initialize(
     liblnk_shell_item_identifiers_list_t **shell_item_identifiers_list,
     liberror_error_t **error )
{
	static char *function = "liblnk_shell_item_identifiers_list_initialize";

	if( shell_item_identifiers_list == NULL )
	{
		liberror_error_set(
		 error,
		 LIBERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid shell item identifiers list.",
		 function );

		return( -1 );
	}
	if( *shell_item_identifiers_list == NULL )
	{
		*shell_item_identifiers_list = (liblnk_shell_item_identifiers_list_t *) memory_allocate(
		                                                                         sizeof( liblnk_shell_item_identifiers_list_t ) );

		if( *shell_item_identifiers_list == NULL )
		{
			liberror_error_set(
			 error,
			 LIBERROR_ERROR_DOMAIN_MEMORY,
			 LIBERROR_MEMORY_ERROR_INSUFFICIENT,
			 "%s: unable to create shell item identifiers list.",
			 function );

			return( -1 );
		}
		if( memory_set(
		     *shell_item_identifiers_list,
		     0,
		     sizeof( liblnk_shell_item_identifiers_list_t ) ) == NULL )
		{
			liberror_error_set(
			 error,
			 LIBERROR_ERROR_DOMAIN_MEMORY,
			 LIBERROR_MEMORY_ERROR_SET_FAILED,
			 "%s: unable to clear shell item identifiers list.",
			 function );

			memory_free(
			 *shell_item_identifiers_list );

			*shell_item_identifiers_list = NULL;

			return( -1 );
		}
	}
	return( 1 );
}

/* Frees shell item identifiers
 * Returns 1 if successful or -1 on error
 */
int liblnk_shell_item_identifiers_list_free(
     liblnk_shell_item_identifiers_list_t **shell_item_identifiers_list,
     liberror_error_t **error )
{
	static char *function = "liblnk_shell_item_identifiers_list_free";

	if( shell_item_identifiers_list == NULL )
	{
		liberror_error_set(
		 error,
		 LIBERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid shell item identifiers list.",
		 function );

		return( -1 );
	}
	if( *shell_item_identifiers_list != NULL )
	{
		memory_free(
		 *shell_item_identifiers_list );

		*shell_item_identifiers_list = NULL;
	}
	return( 1 );
}

/* Reads a shell item identifiers
 * Returns the number of bytes read if successful or -1 on error
 */
ssize_t liblnk_shell_item_identifiers_list_read(
         liblnk_shell_item_identifiers_list_t *shell_item_identifiers_list,
         libbfio_handle_t *file_io_handle,
         off64_t shell_item_identifiers_list_offset,
         liberror_error_t **error )
{
	uint8_t shell_item_identifiers_list_size_data[ 2 ];

	libfwsi_item_t *shell_item                = NULL;
	uint8_t *shell_item_identifier_data       = NULL;
	uint8_t *shell_item_identifiers_list_data = NULL;
	static char *function                     = "liblnk_shell_item_identifiers_list_read";
	size_t shell_item_identifiers_list_size   = 0;
	ssize_t read_count                        = 0;
	uint16_t shell_item_identifier_size       = 0;
	int shell_item_identifier_index           = 0;

	if( shell_item_identifiers_list == NULL )
	{
		liberror_error_set(
		 error,
		 LIBERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid shell item identifiers list.",
		 function );

		return( -1 );
	}
	if( file_io_handle == NULL )
	{
		liberror_error_set(
		 error,
		 LIBERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid file IO handle.",
		 function );

		return( -1 );
	}
#if defined( HAVE_DEBUG_OUTPUT )
	if( libnotify_verbose != 0 )
	{
		libnotify_printf(
		 "%s: reading shell item identifiers list at offset: %" PRIi64 " (0x%08" PRIx64 ")\n",
		 function,
		 shell_item_identifiers_list_offset,
		 shell_item_identifiers_list_offset );
	}
#endif

	if( libbfio_handle_seek_offset(
	     file_io_handle,
	     shell_item_identifiers_list_offset,
	     SEEK_SET,
	     error ) == -1 )
	{
		liberror_error_set(
		 error,
		 LIBERROR_ERROR_DOMAIN_IO,
		 LIBERROR_IO_ERROR_SEEK_FAILED,
		 "%s: unable to seek shell item identifiers list offset: %" PRIi64 ".",
		 function,
		 shell_item_identifiers_list_offset );

		return( -1 );
	}
	read_count = libbfio_handle_read(
	              file_io_handle,
	              shell_item_identifiers_list_size_data,
	              2,
	              error );

	if( read_count != (ssize_t) 2 )
	{
		liberror_error_set(
		 error,
		 LIBERROR_ERROR_DOMAIN_IO,
		 LIBERROR_IO_ERROR_READ_FAILED,
		 "%s: unable to read shell item identifiers list size.",
		 function );

		return( -1 );
	}
	byte_stream_copy_to_uint16_little_endian(
	 shell_item_identifiers_list_size_data,
	 shell_item_identifiers_list_size )
	
#if defined( HAVE_DEBUG_OUTPUT )
	if( libnotify_verbose != 0 )
	{
		libnotify_printf(
		 "%s: shell item identifiers list size\t: %" PRIzd "\n",
		 function,
		 shell_item_identifiers_list_size );
	}
#endif

	if( shell_item_identifiers_list_size > (size_t) SSIZE_MAX )
	{
		liberror_error_set(
		 error,
		 LIBERROR_ERROR_DOMAIN_RUNTIME,
		 LIBERROR_RUNTIME_ERROR_VALUE_EXCEEDS_MAXIMUM,
		 "%s: shell item identifiers list size value exceeds maximum.",
		 function );

		return( -1 );
	}
	shell_item_identifiers_list_data = (uint8_t *) memory_allocate(
	                                                sizeof( uint8_t ) * shell_item_identifiers_list_size );


	if( shell_item_identifiers_list_data == NULL )
	{
		liberror_error_set(
		 error,
		 LIBERROR_ERROR_DOMAIN_MEMORY,
		 LIBERROR_MEMORY_ERROR_INSUFFICIENT,
		 "%s: unable to create shell item identifiers list data.",
		 function );

		return( -1 );
	}
	read_count = libbfio_handle_read(
	              file_io_handle,
	              shell_item_identifiers_list_data,
	              shell_item_identifiers_list_size,
	              error );

	if( read_count != (ssize_t) shell_item_identifiers_list_size )
	{
		liberror_error_set(
		 error,
		 LIBERROR_ERROR_DOMAIN_IO,
		 LIBERROR_IO_ERROR_READ_FAILED,
		 "%s: unable to read shell item identifiers list data.",
		 function );

		memory_free(
		 shell_item_identifiers_list_data );

		return( -1 );
	}
#if defined( HAVE_DEBUG_OUTPUT )
	if( libnotify_verbose != 0 )
	{
		libnotify_printf(
		 "%s: shell item identifiers list data:\n",
		 function );
		libnotify_print_data(
		 shell_item_identifiers_list_data,
		 shell_item_identifiers_list_size );
	}
#endif

	shell_item_identifier_data = shell_item_identifiers_list_data;

	if( libfwsi_item_initialize(
	     &shell_item,
	     error ) != 1 )
	{
		liberror_error_set(
		 error,
		 LIBERROR_ERROR_DOMAIN_RUNTIME,
		 LIBERROR_RUNTIME_ERROR_INITIALIZE_FAILED,
		 "%s: unable to create shell item.",
		 function );

		memory_free(
		 shell_item_identifiers_list_data );

		return( -1 );
	}
	do
	{
#if defined( HAVE_DEBUG_OUTPUT )
		if( libnotify_verbose != 0 )
		{
			libnotify_printf(
			 "%s: shell item identifier: %d\n",
			 function,
			 shell_item_identifier_index );
		}
#endif
		if( libfwsi_item_copy_from_byte_stream(
		     shell_item,
		     shell_item_identifier_data,
		     shell_item_identifiers_list_size,
		     error ) != 1 )
		{
			liberror_error_set(
			 error,
			 LIBERROR_ERROR_DOMAIN_RUNTIME,
			 LIBERROR_RUNTIME_ERROR_COPY_FAILED,
			 "%s: unable to copy byte stream to shell item.",
			 function );

			libfwsi_item_free(
			 &shell_item,
			 NULL );
			memory_free(
			 shell_item_identifiers_list_data );

			return( -1 );
		}
		/* TODO replace by function to obtain size from shell item */
		byte_stream_copy_to_uint16_little_endian(
		 shell_item_identifier_data,
		 shell_item_identifier_size );

		shell_item_identifier_data       += shell_item_identifier_size;
		shell_item_identifiers_list_size -= shell_item_identifier_size;

		shell_item_identifier_index++;
	}
	while( shell_item_identifier_size != 0 );

	if( libfwsi_item_free(
	     &shell_item,
	     error ) != 1 )
	{
		liberror_error_set(
		 error,
		 LIBERROR_ERROR_DOMAIN_RUNTIME,
		 LIBERROR_RUNTIME_ERROR_FINALIZE_FAILED,
		 "%s: unable to free shell item.",
		 function );

		memory_free(
		 shell_item_identifiers_list_data );

		return( -1 );
	}
	memory_free(
	 shell_item_identifiers_list_data );

	return( read_count + 2 );
}

