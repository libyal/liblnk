/*
 * Shell itemi identifier functions
 *
 * Copyright (c) 2009, Joachim Metz <forensics@hoffmannbv.nl>,
 * Hoffmann Investigations. All rights reserved.
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
#include <endian.h>
#include <memory.h>
#include <types.h>

#include <liberror.h>
#include <libnotify.h>

#include "liblnk_definitions.h"
#include "liblnk_libbfio.h"
#include "liblnk_shell_item_identifiers.h"

/* Creates shell item identifiers
 * Returns 1 if successful or -1 on error
 */
int liblnk_shell_item_identifiers_initialize(
     liblnk_shell_item_identifiers_t **shell_item_identifiers,
     liberror_error_t **error )
{
	static char *function = "liblnk_shell_item_identifiers_initialize";

	if( shell_item_identifiers == NULL )
	{
		liberror_error_set(
		 error,
		 LIBERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid shell item identifiers.",
		 function );

		return( -1 );
	}
	if( *shell_item_identifiers == NULL )
	{
		*shell_item_identifiers = (liblnk_shell_item_identifiers_t *) memory_allocate(
		                                                               sizeof( liblnk_shell_item_identifiers_t ) );

		if( *shell_item_identifiers == NULL )
		{
			liberror_error_set(
			 error,
			 LIBERROR_ERROR_DOMAIN_MEMORY,
			 LIBERROR_MEMORY_ERROR_INSUFFICIENT,
			 "%s: unable to create shell item identifiers.",
			 function );

			return( -1 );
		}
		if( memory_set(
		     *shell_item_identifiers,
		     0,
		     sizeof( liblnk_shell_item_identifiers_t ) ) == NULL )
		{
			liberror_error_set(
			 error,
			 LIBERROR_ERROR_DOMAIN_MEMORY,
			 LIBERROR_MEMORY_ERROR_SET_FAILED,
			 "%s: unable to clear shell item identifiers.",
			 function );

			memory_free(
			 *shell_item_identifiers );

			*shell_item_identifiers = NULL;

			return( -1 );
		}
	}
	return( 1 );
}

/* Frees shell item identifiers
 * Returns 1 if successful or -1 on error
 */
int liblnk_shell_item_identifiers_free(
     liblnk_shell_item_identifiers_t **shell_item_identifiers,
     liberror_error_t **error )
{
	static char *function = "liblnk_shell_item_identifiers_free";

	if( shell_item_identifiers == NULL )
	{
		liberror_error_set(
		 error,
		 LIBERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid shell item identifiers.",
		 function );

		return( -1 );
	}
	if( *shell_item_identifiers != NULL )
	{
		memory_free(
		 *shell_item_identifiers );

		*shell_item_identifiers = NULL;
	}
	return( 1 );
}

/* Reads a shell item identifiers
 * Returns the amount of bytes read if successful or -1 on error
 */
ssize_t liblnk_shell_item_identifiers_read(
         liblnk_shell_item_identifiers_t *shell_item_identifiers,
         libbfio_handle_t *file_io_handle,
         off64_t shell_item_identifiers_offset,
         liberror_error_t **error )
{
	uint8_t shell_item_identifiers_size_data[ 2 ];

	uint8_t *shell_item_identifier_data  = NULL;
	uint8_t *shell_item_identifiers_data = NULL;
	static char *function                = "liblnk_shell_item_identifiers_read";
	size_t shell_item_identifiers_size   = 0;
	ssize_t read_count                   = 0;
	uint16_t shell_item_identifier_size  = 0;
	int shell_item_identifier_index      = 0;

	if( shell_item_identifiers == NULL )
	{
		liberror_error_set(
		 error,
		 LIBERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid shell item identifiers.",
		 function );

		return( -1 );
	}
	if( file_io_handle == NULL )
	{
		liberror_error_set(
		 error,
		 LIBERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid file io handle.",
		 function );

		return( -1 );
	}
#if defined( HAVE_DEBUG_OUTPUT )
	libnotify_verbose_printf(
	 "%s: reading shell item identifiers at offset: %" PRIu64 " (0x%08" PRIx64 ")\n",
	 function,
	 shell_item_identifiers_offset,
	 shell_item_identifiers_offset );
#endif

	if( libbfio_handle_seek_offset(
	     file_io_handle,
	     shell_item_identifiers_offset,
	     SEEK_SET,
	     error ) == -1 )
	{
		liberror_error_set(
		 error,
		 LIBERROR_ERROR_DOMAIN_IO,
		 LIBERROR_IO_ERROR_SEEK_FAILED,
		 "%s: unable to seek shell item identifiers offset: %" PRIu64 ".",
		 function,
		 shell_item_identifiers_offset );

		return( -1 );
	}
	read_count = libbfio_handle_read(
	              file_io_handle,
	              shell_item_identifiers_size_data,
	              2,
	              error );

	if( read_count != (ssize_t) 2 )
	{
		liberror_error_set(
		 error,
		 LIBERROR_ERROR_DOMAIN_IO,
		 LIBERROR_IO_ERROR_READ_FAILED,
		 "%s: unable to read shell item identifiers size.",
		 function );

		return( -1 );
	}
	endian_little_convert_16bit(
	 shell_item_identifiers_size,
	 shell_item_identifiers_size_data );
	
#if defined( HAVE_DEBUG_OUTPUT )
	libnotify_verbose_printf(
	 "%s: shell item identifiers size\t: %" PRIzd "\n",
	 function,
	 shell_item_identifiers_size );
#endif

	if( shell_item_identifiers_size > (size_t) SSIZE_MAX )
	{
		liberror_error_set(
		 error,
		 LIBERROR_ERROR_DOMAIN_RUNTIME,
		 LIBERROR_RUNTIME_ERROR_VALUE_EXCEEDS_MAXIMUM,
		 "%s: shell item identifiers size value exceeds maximum.",
		 function );

		return( -1 );
	}
	shell_item_identifiers_data = (uint8_t *) memory_allocate(
	                                sizeof( uint8_t ) * shell_item_identifiers_size );


	if( shell_item_identifiers_data == NULL )
	{
		liberror_error_set(
		 error,
		 LIBERROR_ERROR_DOMAIN_MEMORY,
		 LIBERROR_MEMORY_ERROR_INSUFFICIENT,
		 "%s: unable to create shell item identifiers data.",
		 function );

		return( -1 );
	}
	read_count = libbfio_handle_read(
	              file_io_handle,
	              shell_item_identifiers_data,
	              shell_item_identifiers_size,
	              error );

	if( read_count != (ssize_t) shell_item_identifiers_size )
	{
		liberror_error_set(
		 error,
		 LIBERROR_ERROR_DOMAIN_IO,
		 LIBERROR_IO_ERROR_READ_FAILED,
		 "%s: unable to read shell item identifiers data.",
		 function );

		memory_free(
		 shell_item_identifiers_data );

		return( -1 );
	}
#if defined( HAVE_DEBUG_OUTPUT )
	libnotify_verbose_printf(
	 "%s: shell item identifiers data:\n",
	 function );
	libnotify_verbose_print_data(
	 shell_item_identifiers_data,
	 shell_item_identifiers_size );
#endif

	shell_item_identifier_data = shell_item_identifiers_data;

	do
	{
		endian_little_convert_16bit(
		 shell_item_identifier_size,
		 shell_item_identifier_data );

		shell_item_identifier_data += 2;

#if defined( HAVE_DEBUG_OUTPUT )
		libnotify_verbose_printf(
		 "%s: shell item identifier: %d size\t: %" PRIu16 "\n",
		 function,
		 shell_item_identifier_index,
		 shell_item_identifier_size );
#endif

		if( shell_item_identifier_size > 0 )
		{
			shell_item_identifier_size -= 2;

#if defined( HAVE_DEBUG_OUTPUT )
			libnotify_verbose_printf(
			 "%s: shell item identifier: %d data:\n",
			 function,
			 shell_item_identifier_index );
			libnotify_verbose_print_data(
			 shell_item_identifier_data,
			 shell_item_identifier_size );
#endif
			shell_item_identifier_data += shell_item_identifier_size;

			shell_item_identifier_index++;
		}
	}
	while( shell_item_identifier_size != 0 );

	memory_free(
	 shell_item_identifiers_data );

	return( read_count + 2 );
}

