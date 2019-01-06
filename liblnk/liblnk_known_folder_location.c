/*
 * Known folder location functions
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

#include "liblnk_data_block.h"
#include "liblnk_debug.h"
#include "liblnk_known_folder_location.h"
#include "liblnk_libcerror.h"
#include "liblnk_libcnotify.h"
#include "liblnk_libfguid.h"
#include "liblnk_libfwsi.h"

#include "lnk_data_blocks.h"

/* Creates a known folder location
 * Make sure the value known_folder_location is referencing, is set to NULL
 * Returns 1 if successful or -1 on error
 */
int liblnk_known_folder_location_initialize(
     liblnk_known_folder_location_t **known_folder_location,
     libcerror_error_t **error )
{
	static char *function = "liblnk_known_folder_location_initialize";

	if( known_folder_location == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid known folder location.",
		 function );

		return( -1 );
	}
	if( *known_folder_location != NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_VALUE_ALREADY_SET,
		 "%s: invalid known folder location value already set.",
		 function );

		return( -1 );
	}
	*known_folder_location = memory_allocate_structure(
	                          liblnk_known_folder_location_t );

	if( *known_folder_location == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_MEMORY,
		 LIBCERROR_MEMORY_ERROR_INSUFFICIENT,
		 "%s: unable to create known folder location.",
		 function );

		goto on_error;
	}
	if( memory_set(
	     *known_folder_location,
	     0,
	     sizeof( liblnk_known_folder_location_t ) ) == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_MEMORY,
		 LIBCERROR_MEMORY_ERROR_SET_FAILED,
		 "%s: unable to clear known folder location.",
		 function );

		goto on_error;
	}
	return( 1 );

on_error:
	if( *known_folder_location != NULL )
	{
		memory_free(
		 *known_folder_location );

		*known_folder_location = NULL;
	}
	return( -1 );
}

/* Frees q known folder location
 * Returns 1 if successful or -1 on error
 */
int liblnk_known_folder_location_free(
     liblnk_known_folder_location_t **known_folder_location,
     libcerror_error_t **error )
{
	static char *function = "liblnk_known_folder_location_free";

	if( known_folder_location == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid known folder location.",
		 function );

		return( -1 );
	}
	if( *known_folder_location != NULL )
	{
		memory_free(
		 *known_folder_location );

		*known_folder_location = NULL;
	}
	return( 1 );
}

/* Reads the known folder location data block
 * Returns 1 if successful or -1 on error
 */
int liblnk_known_folder_location_read_data_block(
     liblnk_known_folder_location_t *known_folder_location,
     const liblnk_data_block_t *data_block,
     libcerror_error_t **error )
{
	static char *function = "liblnk_known_folder_location_read_data_block";

	if( known_folder_location == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid known folder location.",
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
	if( liblnk_known_folder_location_read_data(
	     known_folder_location,
	     data_block->data,
	     data_block->data_size,
	     error ) != 1 )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_IO,
		 LIBCERROR_IO_ERROR_READ_FAILED,
		 "%s: unable to read known folder location.",
		 function );

		return( -1 );
	}
	return( 1 );
}

/* Reads the known folder location
 * Returns 1 if successful or -1 on error
 */
int liblnk_known_folder_location_read_data(
     liblnk_known_folder_location_t *known_folder_location,
     const uint8_t *data,
     size_t data_size,
     libcerror_error_t **error )
{
	static char *function = "liblnk_known_folder_location_read_data";

	if( known_folder_location == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid known folder location.",
		 function );

		return( -1 );
	}
	if( data == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid data.",
		 function );

		return( -1 );
	}
	if( data_size < sizeof( lnk_data_block_known_folder_location_t ) )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_VALUE_TOO_SMALL,
		 "%s: invalid data size value too small.",
		 function );

		return( -1 );
	}
	if( data_size > (size_t) SSIZE_MAX )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_VALUE_EXCEEDS_MAXIMUM,
		 "%s: invalid data size value exceeds maximum.",
		 function );

		return( -1 );
	}
	if( memory_copy(
	     known_folder_location->folder_identifier,
	     ( (lnk_data_block_known_folder_location_t *) data )->folder_identifier,
	     16 ) == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_MEMORY,
		 LIBCERROR_MEMORY_ERROR_COPY_FAILED,
		 "%s: unable to copy folder identifier.",
		 function );

		return( -1 );
	}
	byte_stream_copy_to_uint32_little_endian(
	 ( (lnk_data_block_known_folder_location_t *) data )->first_child_segment_offset,
	 known_folder_location->first_child_segment_offset );

#if defined( HAVE_DEBUG_OUTPUT )
	if( libcnotify_verbose != 0 )
	{
		if( liblnk_debug_print_guid_value(
		     function,
		     "known folder identifier\t\t\t",
		     known_folder_location->folder_identifier,
		     16,
		     LIBFGUID_ENDIAN_LITTLE,
		     LIBFGUID_STRING_FORMAT_FLAG_USE_LOWER_CASE,
		     error ) != 1 )
		{
			libcerror_error_set(
			 error,
			 LIBCERROR_ERROR_DOMAIN_RUNTIME,
			 LIBCERROR_RUNTIME_ERROR_PRINT_FAILED,
			 "%s: unable to print GUID value.",
			 function );

			return( -1 );
		}
		libcnotify_printf(
		 "%s: known folder name\t\t\t: %s\n",
		 function,
		 libfwsi_known_folder_identifier_get_name(
		  known_folder_location->folder_identifier ) );

		libcnotify_printf(
		 "%s: first child segment offset\t\t: %" PRIu32 "\n",
		 function,
		 known_folder_location->first_child_segment_offset );

		libcnotify_printf(
		 "\n" );
	}
#endif
#if defined( HAVE_DEBUG_OUTPUT )
	if( libcnotify_verbose != 0 )
	{
		if( data_size > sizeof( lnk_data_block_known_folder_location_t ) )
		{
			libcnotify_printf(
			 "%s: trailing data:\n",
			 function );
			libcnotify_print_data(
			 &( data[ sizeof( lnk_data_block_known_folder_location_t ) ] ),
			 data_size - sizeof( lnk_data_block_known_folder_location_t ),
			 0 );
		}
	}
#endif
	return( 1 );
}

