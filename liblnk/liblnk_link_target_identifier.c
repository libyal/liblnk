/*
 * Link target identifier functions
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
#include <types.h>

#include "liblnk_definitions.h"
#include "liblnk_io_handle.h"
#include "liblnk_libbfio.h"
#include "liblnk_libcerror.h"
#include "liblnk_libcnotify.h"
#include "liblnk_libfwsi.h"
#include "liblnk_link_target_identifier.h"

/* Creates a link target identifier
 * Make sure the value link_target_identifier is referencing, is set to NULL
 * Returns 1 if successful or -1 on error
 */
int liblnk_link_target_identifier_initialize(
     liblnk_link_target_identifier_t **link_target_identifier,
     libcerror_error_t **error )
{
	static char *function = "liblnk_link_target_identifier_initialize";

	if( link_target_identifier == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid link target identifier.",
		 function );

		return( -1 );
	}
	if( *link_target_identifier != NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_VALUE_ALREADY_SET,
		 "%s: invalid link target identifier value already set.",
		 function );

		return( -1 );
	}
	*link_target_identifier = memory_allocate_structure(
	                           liblnk_link_target_identifier_t );

	if( *link_target_identifier == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_MEMORY,
		 LIBCERROR_MEMORY_ERROR_INSUFFICIENT,
		 "%s: unable to create link target identifier.",
		 function );

		goto on_error;
	}
	if( memory_set(
	     *link_target_identifier,
	     0,
	     sizeof( liblnk_link_target_identifier_t ) ) == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_MEMORY,
		 LIBCERROR_MEMORY_ERROR_SET_FAILED,
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

/* Frees a link target identifier
 * Returns 1 if successful or -1 on error
 */
int liblnk_link_target_identifier_free(
     liblnk_link_target_identifier_t **link_target_identifier,
     libcerror_error_t **error )
{
	static char *function = "liblnk_link_target_identifier_free";

	if( link_target_identifier == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
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
         liblnk_io_handle_t *io_handle,
         libbfio_handle_t *file_io_handle,
         off64_t file_offset,
         libcerror_error_t **error )
{
	uint8_t size_data[ 2 ];

	static char *function                = "liblnk_link_target_identifier_read";
	ssize_t read_count                   = 0;

#if defined( HAVE_DEBUG_OUTPUT )
	libfwsi_item_list_t *shell_item_list = NULL;
	size_t shell_item_list_data_size     = 0;
#endif

	if( link_target_identifier == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid link target identifier.",
		 function );

		return( -1 );
	}
	if( link_target_identifier->data != NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_VALUE_ALREADY_SET,
		 "%s: invalid link target identifier - data value already set.",
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
#if defined( HAVE_DEBUG_OUTPUT )
	if( libcnotify_verbose != 0 )
	{
		libcnotify_printf(
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
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_IO,
		 LIBCERROR_IO_ERROR_SEEK_FAILED,
		 "%s: unable to seek link target identifier offset: %" PRIi64 ".",
		 function,
		 file_offset );

		goto on_error;
	}
	read_count = libbfio_handle_read_buffer(
	              file_io_handle,
	              size_data,
	              2,
	              error );

	if( read_count != (ssize_t) 2 )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_IO,
		 LIBCERROR_IO_ERROR_READ_FAILED,
		 "%s: unable to read link target identifier size.",
		 function );

		goto on_error;
	}
	byte_stream_copy_to_uint16_little_endian(
	 size_data,
	 link_target_identifier->data_size )
	
	link_target_identifier->data = (uint8_t *) memory_allocate(
	                                            sizeof( uint8_t ) * link_target_identifier->data_size );


	if( link_target_identifier->data == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_MEMORY,
		 LIBCERROR_MEMORY_ERROR_INSUFFICIENT,
		 "%s: unable to create link target identifier data.",
		 function );

		goto on_error;
	}
	read_count = libbfio_handle_read_buffer(
	              file_io_handle,
	              link_target_identifier->data,
	              link_target_identifier->data_size,
	              error );

	if( read_count != (ssize_t) link_target_identifier->data_size )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_IO,
		 LIBCERROR_IO_ERROR_READ_FAILED,
		 "%s: unable to read link target identifier data.",
		 function );

		goto on_error;
	}
#if defined( HAVE_DEBUG_OUTPUT )
	if( libcnotify_verbose != 0 )
	{
		if( libfwsi_item_list_initialize(
		     &shell_item_list,
		     error ) != 1 )
		{
			libcerror_error_set(
			 error,
			 LIBCERROR_ERROR_DOMAIN_RUNTIME,
			 LIBCERROR_RUNTIME_ERROR_INITIALIZE_FAILED,
			 "%s: unable to create shell item list.",
			 function );

			goto on_error;
		}
		if( libfwsi_item_list_copy_from_byte_stream(
		     shell_item_list,
		     link_target_identifier->data,
		     link_target_identifier->data_size,
		     io_handle->ascii_codepage,
		     error ) != 1 )
		{
			libcerror_error_set(
			 error,
			 LIBCERROR_ERROR_DOMAIN_RUNTIME,
			 LIBCERROR_RUNTIME_ERROR_COPY_FAILED,
			 "%s: unable to copy byte stream to shell item list.",
			 function );

			goto on_error;
		}
		if( libfwsi_item_list_get_data_size(
		     shell_item_list,
		     &shell_item_list_data_size,
		     error ) != 1 )
		{
			libcerror_error_set(
			 error,
			 LIBCERROR_ERROR_DOMAIN_RUNTIME,
			 LIBCERROR_RUNTIME_ERROR_GET_FAILED,
			 "%s: unable to retrieve shell item list data size.",
			 function );

			goto on_error;
		}
		if( libfwsi_item_list_free(
		     &shell_item_list,
		     error ) != 1 )
		{
			libcerror_error_set(
			 error,
			 LIBCERROR_ERROR_DOMAIN_RUNTIME,
			 LIBCERROR_RUNTIME_ERROR_FINALIZE_FAILED,
			 "%s: unable to free shell item list.",
			 function );

			goto on_error;
		}
	}
#endif
#if defined( HAVE_DEBUG_OUTPUT )
	if( libcnotify_verbose != 0 )
	{
		if( shell_item_list_data_size < link_target_identifier->data_size )
		{
			libcnotify_printf(
			 "%s: trailing data:\n",
			 function );
			libcnotify_print_data(
			 &( link_target_identifier->data[ shell_item_list_data_size ] ),
			 link_target_identifier->data_size - shell_item_list_data_size,
			 LIBCNOTIFY_PRINT_DATA_FLAG_GROUP_DATA );
		}
	}
#endif
	return( (ssize_t) ( link_target_identifier->data_size + 2 ) );

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

