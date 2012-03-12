/*
 * Link target identifier functions
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
#include <byte_stream.h>
#include <memory.h>
#include <types.h>

#include <liberror.h>
#include <libnotify.h>

#include "liblnk_definitions.h"
#include "liblnk_libbfio.h"
#include "liblnk_libfwsi.h"
#include "liblnk_link_target_identifier.h"

/* Creates link target identifier
 * Returns 1 if successful or -1 on error
 */
int liblnk_link_target_identifier_initialize(
     liblnk_link_target_identifier_t **link_target_identifier,
     liberror_error_t **error )
{
	static char *function = "liblnk_link_target_identifier_initialize";

	if( link_target_identifier == NULL )
	{
		liberror_error_set(
		 error,
		 LIBERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid link target identifier.",
		 function );

		return( -1 );
	}
	if( *link_target_identifier != NULL )
	{
		liberror_error_set(
		 error,
		 LIBERROR_ERROR_DOMAIN_RUNTIME,
		 LIBERROR_RUNTIME_ERROR_VALUE_ALREADY_SET,
		 "%s: invalid link target identifier value already set.",
		 function );

		return( -1 );
	}
	*link_target_identifier = memory_allocate_structure(
	                           liblnk_link_target_identifier_t );

	if( *link_target_identifier == NULL )
	{
		liberror_error_set(
		 error,
		 LIBERROR_ERROR_DOMAIN_MEMORY,
		 LIBERROR_MEMORY_ERROR_INSUFFICIENT,
		 "%s: unable to create link target identifier.",
		 function );

		goto on_error;
	}
	if( memory_set(
	     *link_target_identifier,
	     0,
	     sizeof( liblnk_link_target_identifier_t ) ) == NULL )
	{
		liberror_error_set(
		 error,
		 LIBERROR_ERROR_DOMAIN_MEMORY,
		 LIBERROR_MEMORY_ERROR_SET_FAILED,
		 "%s: unable to clear link target identifier.",
		 function );

		goto on_error;
	}
	return( 1 );

on_error:
	if( *link_target_identifier != NULL )
	{
		memory_free(
		 *link_target_identifier );

		*link_target_identifier = NULL;
	}
	return( -1 );
}

/* Frees link target identifier
 * Returns 1 if successful or -1 on error
 */
int liblnk_link_target_identifier_free(
     liblnk_link_target_identifier_t **link_target_identifier,
     liberror_error_t **error )
{
	static char *function = "liblnk_link_target_identifier_free";

	if( link_target_identifier == NULL )
	{
		liberror_error_set(
		 error,
		 LIBERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid link target identifier.",
		 function );

		return( -1 );
	}
	if( *link_target_identifier != NULL )
	{
		if( ( *link_target_identifier )->data != NULL )
		{
			memory_free(
			 ( *link_target_identifier )->data );
		}
		memory_free(
		 *link_target_identifier );

		*link_target_identifier = NULL;
	}
	return( 1 );
}

/* Reads a link target identifier
 * Returns the number of bytes read if successful or -1 on error
 */
ssize_t liblnk_link_target_identifier_read(
         liblnk_link_target_identifier_t *link_target_identifier,
         libbfio_handle_t *file_io_handle,
         off64_t file_offset,
         liberror_error_t **error )
{
	uint8_t size_data[ 2 ];

	libfwsi_item_list_t *shell_item_list = NULL;
	static char *function                = "liblnk_link_target_identifier_read";
	ssize_t read_count                   = 0;

	if( link_target_identifier == NULL )
	{
		liberror_error_set(
		 error,
		 LIBERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid link target identifier.",
		 function );

		return( -1 );
	}
	if( link_target_identifier->data != NULL )
	{
		liberror_error_set(
		 error,
		 LIBERROR_ERROR_DOMAIN_RUNTIME,
		 LIBERROR_RUNTIME_ERROR_VALUE_ALREADY_SET,
		 "%s: invalid link target identifier - data value already set.",
		 function );

		return( -1 );
	}
#if defined( HAVE_DEBUG_OUTPUT )
	if( libnotify_verbose != 0 )
	{
		libnotify_printf(
		 "%s: reading link target identifier at offset: %" PRIi64 " (0x%08" PRIx64 ")\n",
		 function,
		 file_offset,
		 file_offset );
	}
#endif
	if( libbfio_handle_seek_offset(
	     file_io_handle,
	     file_offset,
	     SEEK_SET,
	     error ) == -1 )
	{
		liberror_error_set(
		 error,
		 LIBERROR_ERROR_DOMAIN_IO,
		 LIBERROR_IO_ERROR_SEEK_FAILED,
		 "%s: unable to seek link target identifier offset: %" PRIi64 ".",
		 function,
		 file_offset );

		goto on_error;
	}
	read_count = libbfio_handle_read(
	              file_io_handle,
	              size_data,
	              2,
	              error );

	if( read_count != (ssize_t) 2 )
	{
		liberror_error_set(
		 error,
		 LIBERROR_ERROR_DOMAIN_IO,
		 LIBERROR_IO_ERROR_READ_FAILED,
		 "%s: unable to read link target identifier size.",
		 function );

		goto on_error;
	}
	byte_stream_copy_to_uint16_little_endian(
	 size_data,
	 link_target_identifier->data_size )
	
	link_target_identifier->data = (uint8_t *) memory_allocate(
	                                            sizeof( uint8_t ) * ( link_target_identifier->data_size + 2 ) );


	if( link_target_identifier->data == NULL )
	{
		liberror_error_set(
		 error,
		 LIBERROR_ERROR_DOMAIN_MEMORY,
		 LIBERROR_MEMORY_ERROR_INSUFFICIENT,
		 "%s: unable to create link target identifier data.",
		 function );

		goto on_error;
	}
	link_target_identifier->data[ 0 ] = size_data[ 0 ];
	link_target_identifier->data[ 1 ] = size_data[ 1 ];

	read_count = libbfio_handle_read(
	              file_io_handle,
	              &( link_target_identifier->data[ 2 ] ),
	              link_target_identifier->data_size,
	              error );

	if( read_count != (ssize_t) link_target_identifier->data_size )
	{
		liberror_error_set(
		 error,
		 LIBERROR_ERROR_DOMAIN_IO,
		 LIBERROR_IO_ERROR_READ_FAILED,
		 "%s: unable to read link target identifier data.",
		 function );

		goto on_error;
	}
	link_target_identifier->data_size += 2;

#if defined( HAVE_DEBUG_OUTPUT )
	if( libnotify_verbose != 0 )
	{
		if( libfwsi_item_list_initialize(
		     &shell_item_list,
		     error ) != 1 )
		{
			liberror_error_set(
			 error,
			 LIBERROR_ERROR_DOMAIN_RUNTIME,
			 LIBERROR_RUNTIME_ERROR_INITIALIZE_FAILED,
			 "%s: unable to create shell item list.",
			 function );

			goto on_error;
		}
		if( libfwsi_item_list_copy_from_byte_stream(
		     shell_item_list,
		     link_target_identifier->data,
		     link_target_identifier->data_size,
		     error ) != 1 )
		{
			liberror_error_set(
			 error,
			 LIBERROR_ERROR_DOMAIN_RUNTIME,
			 LIBERROR_RUNTIME_ERROR_COPY_FAILED,
			 "%s: unable to copy byte stream to shell item list.",
			 function );

			goto on_error;
		}
		if( libfwsi_item_list_free(
		     &shell_item_list,
		     error ) != 1 )
		{
			liberror_error_set(
			 error,
			 LIBERROR_ERROR_DOMAIN_RUNTIME,
			 LIBERROR_RUNTIME_ERROR_FINALIZE_FAILED,
			 "%s: unable to free shell item list.",
			 function );

			goto on_error;
		}
	}
#endif
	return( (ssize_t) link_target_identifier->data_size );

on_error:
#if defined( HAVE_DEBUG_OUTPUT )
	if( shell_item_list != NULL )
	{
		libfwsi_item_list_free(
		 &shell_item_list,
		 NULL );
	}
#endif
	if( link_target_identifier->data != NULL )
	{
		memory_free(
		 link_target_identifier->data );

		link_target_identifier->data = NULL;
	}
	link_target_identifier->data_size = 0;

	return( -1 );
}

