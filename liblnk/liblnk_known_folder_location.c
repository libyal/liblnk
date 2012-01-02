/*
 * Known folder location functions
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

#include "liblnk_data_block.h"
#include "liblnk_known_folder_location.h"
#include "liblnk_libfguid.h"
#include "liblnk_libfwsi.h"

#include "lnk_data_blocks.h"

/* Creates known folder location
 * Returns 1 if successful or -1 on error
 */
int liblnk_known_folder_location_initialize(
     liblnk_known_folder_location_t **known_folder_location,
     liberror_error_t **error )
{
	static char *function = "liblnk_known_folder_location_initialize";

	if( known_folder_location == NULL )
	{
		liberror_error_set(
		 error,
		 LIBERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid known folder location.",
		 function );

		return( -1 );
	}
	if( *known_folder_location != NULL )
	{
		liberror_error_set(
		 error,
		 LIBERROR_ERROR_DOMAIN_RUNTIME,
		 LIBERROR_RUNTIME_ERROR_VALUE_ALREADY_SET,
		 "%s: invalid known folder location value already set.",
		 function );

		return( -1 );
	}
	*known_folder_location = memory_allocate_structure(
	                          liblnk_known_folder_location_t );

	if( *known_folder_location == NULL )
	{
		liberror_error_set(
		 error,
		 LIBERROR_ERROR_DOMAIN_MEMORY,
		 LIBERROR_MEMORY_ERROR_INSUFFICIENT,
		 "%s: unable to create known folder location.",
		 function );

		goto on_error;
	}
	if( memory_set(
	     *known_folder_location,
	     0,
	     sizeof( liblnk_known_folder_location_t ) ) == NULL )
	{
		liberror_error_set(
		 error,
		 LIBERROR_ERROR_DOMAIN_MEMORY,
		 LIBERROR_MEMORY_ERROR_SET_FAILED,
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

/* Frees known folder location
 * Returns 1 if successful or -1 on error
 */
int liblnk_known_folder_location_free(
     liblnk_known_folder_location_t **known_folder_location,
     liberror_error_t **error )
{
	static char *function = "liblnk_known_folder_location_free";

	if( known_folder_location == NULL )
	{
		liberror_error_set(
		 error,
		 LIBERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBERROR_ARGUMENT_ERROR_INVALID_VALUE,
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

/* Reads the known folder location
 * Returns the number of bytes read if successful or -1 on error
 */
int liblnk_known_folder_location_read(
     liblnk_known_folder_location_t *known_folder_location,
     liblnk_data_block_t *data_block,
     liberror_error_t **error )
{
	lnk_data_block_known_folder_location_t *known_folder_location_data = NULL;
	static char *function                                              = "liblnk_data_block_strings_read";

#if defined( HAVE_DEBUG_OUTPUT )
	libcstring_system_character_t guid_string[ LIBFGUID_IDENTIFIER_STRING_SIZE ];

	libfguid_identifier_t *guid                                        = NULL;
	int result                                                         = 0;
#endif

	if( known_folder_location == NULL )
	{
		liberror_error_set(
		 error,
		 LIBERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid known folder location.",
		 function );

		return( -1 );
	}
	if( data_block == NULL )
	{
		liberror_error_set(
		 error,
		 LIBERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid data block.",
		 function );

		return( -1 );
	}
	if( data_block->data == NULL )
	{
		liberror_error_set(
		 error,
		 LIBERROR_ERROR_DOMAIN_RUNTIME,
		 LIBERROR_RUNTIME_ERROR_VALUE_MISSING,
		 "%s: invalid data block - missing data.",
		 function );

		return( -1 );
	}
	if( data_block->data_size < sizeof( lnk_data_block_known_folder_location_t ) )
	{
		liberror_error_set(
		 error,
		 LIBERROR_ERROR_DOMAIN_RUNTIME,
		 LIBERROR_RUNTIME_ERROR_VALUE_OUT_OF_BOUNDS,
		 "%s: invalid data block - data size too small.",
		 function );

		return( -1 );
	}
	known_folder_location_data = (lnk_data_block_known_folder_location_t *) data_block->data;

	if( memory_copy(
	     known_folder_location->folder_identifier,
	     known_folder_location_data->folder_identifier,
	     16 ) == NULL )
	{
		liberror_error_set(
		 error,
		 LIBERROR_ERROR_DOMAIN_MEMORY,
		 LIBERROR_MEMORY_ERROR_COPY_FAILED,
		 "%s: unable to copy folder identifier.",
		 function );

		goto on_error;
	}
	byte_stream_copy_to_uint32_little_endian(
	 known_folder_location_data->first_child_segment_offset,
	 known_folder_location->first_child_segment_offset );

#if defined( HAVE_DEBUG_OUTPUT )
	if( libnotify_verbose != 0 )
	{
		if( libfguid_identifier_initialize(
		     &guid,
		     error ) != 1 )
		{
			liberror_error_set(
			 error,
			 LIBERROR_ERROR_DOMAIN_RUNTIME,
			 LIBERROR_RUNTIME_ERROR_INITIALIZE_FAILED,
			 "%s: unable to create GUID.",
			 function );

			goto on_error;
		}
		if( libfguid_identifier_copy_from_byte_stream(
		     guid,
		     known_folder_location->folder_identifier,
		     16,
		     LIBFGUID_ENDIAN_LITTLE,
		     error ) != 1 )
		{
			liberror_error_set(
			 error,
			 LIBERROR_ERROR_DOMAIN_RUNTIME,
			 LIBERROR_RUNTIME_ERROR_COPY_FAILED,
			 "%s: unable to copy byte stream to GUID.",
			 function );

			goto on_error;
		}
#if defined( LIBCSTRING_HAVE_WIDE_SYSTEM_CHARACTER )
		result = libfguid_identifier_copy_to_utf16_string(
			  guid,
			  (uint16_t *) guid_string,
			  LIBFGUID_IDENTIFIER_STRING_SIZE,
			  error );
#else
		result = libfguid_identifier_copy_to_utf8_string(
			  guid,
			  (uint8_t *) guid_string,
			  LIBFGUID_IDENTIFIER_STRING_SIZE,
			  error );
#endif
		if( result != 1 )
		{
			liberror_error_set(
			 error,
			 LIBERROR_ERROR_DOMAIN_RUNTIME,
			 LIBERROR_RUNTIME_ERROR_COPY_FAILED,
			 "%s: unable to copy GUID to string.",
			 function );

			goto on_error;
		}
		libnotify_printf(
		 "%s: folder identifier\t\t\t: %" PRIs_LIBCSTRING_SYSTEM "\n",
		 function,
		 guid_string );

		libnotify_printf(
		 "%s: folder name\t\t\t\t: %s\n",
		 function,
		 libfwsi_folder_identifier_get_name(
		  known_folder_location->folder_identifier ) );

		libnotify_printf(
		 "%s: first child segment offset\t\t: %" PRIu32 "\n",
		 function,
		 known_folder_location->first_child_segment_offset );

		libnotify_printf(
		 "\n" );

		if( libfguid_identifier_free(
		     &guid,
		     error ) != 1 )
		{
			liberror_error_set(
			 error,
			 LIBERROR_ERROR_DOMAIN_RUNTIME,
			 LIBERROR_RUNTIME_ERROR_FINALIZE_FAILED,
			 "%s: unable to free GUID.",
			 function );

			goto on_error;
		}
	}
#endif
#if defined( HAVE_DEBUG_OUTPUT )
	if( libnotify_verbose != 0 )
	{
		if( data_block->data_size > sizeof( lnk_data_block_known_folder_location_t ) )
		{
			libnotify_printf(
			 "%s: trailing data:\n",
			 function );
			libnotify_print_data(
			 &( data_block->data[ sizeof( lnk_data_block_known_folder_location_t ) ] ),
			 data_block->data_size - sizeof( lnk_data_block_known_folder_location_t ) );
		}
	}
#endif
	return( 1 );

on_error:
#if defined( HAVE_DEBUG_OUTPUT )
	if( guid != NULL )
	{
		libfguid_identifier_free(
		 &guid,
		 NULL );
	}
#endif
	return( -1 );
}

