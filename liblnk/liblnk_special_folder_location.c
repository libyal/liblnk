/*
 * Special folder location functions
 *
 * Copyright (C) 2009-2016, Joachim Metz <joachim.metz@gmail.com>
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
#include "liblnk_libcerror.h"
#include "liblnk_libcnotify.h"
#include "liblnk_special_folder_location.h"

#include "lnk_data_blocks.h"

/* Creates a special folder location
 * Make sure the value special_folder_location is referencing, is set to NULL
 * Returns 1 if successful or -1 on error
 */
int liblnk_special_folder_location_initialize(
     liblnk_special_folder_location_t **special_folder_location,
     libcerror_error_t **error )
{
	static char *function = "liblnk_special_folder_location_initialize";

	if( special_folder_location == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid special folder location.",
		 function );

		return( -1 );
	}
	if( *special_folder_location != NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_VALUE_ALREADY_SET,
		 "%s: invalid special folder location value already set.",
		 function );

		return( -1 );
	}
	*special_folder_location = memory_allocate_structure(
	                            liblnk_special_folder_location_t );

	if( *special_folder_location == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_MEMORY,
		 LIBCERROR_MEMORY_ERROR_INSUFFICIENT,
		 "%s: unable to create special folder location.",
		 function );

		goto on_error;
	}
	if( memory_set(
	     *special_folder_location,
	     0,
	     sizeof( liblnk_special_folder_location_t ) ) == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_MEMORY,
		 LIBCERROR_MEMORY_ERROR_SET_FAILED,
		 "%s: unable to clear special folder location.",
		 function );

		goto on_error;
	}
	return( 1 );

on_error:
	if( *special_folder_location != NULL )
	{
		memory_free(
		 *special_folder_location );

		*special_folder_location = NULL;
	}
	return( -1 );
}

/* Frees a special folder location
 * Returns 1 if successful or -1 on error
 */
int liblnk_special_folder_location_free(
     liblnk_special_folder_location_t **special_folder_location,
     libcerror_error_t **error )
{
	static char *function = "liblnk_special_folder_location_free";

	if( special_folder_location == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid special folder location.",
		 function );

		return( -1 );
	}
	if( *special_folder_location != NULL )
	{
		memory_free(
		 *special_folder_location );

		*special_folder_location = NULL;
	}
	return( 1 );
}

/* Reads the special folder location
 * Returns the number of bytes read if successful or -1 on error
 */
int liblnk_special_folder_location_read(
     liblnk_special_folder_location_t *special_folder_location,
     liblnk_data_block_t *data_block,
     libcerror_error_t **error )
{
	lnk_data_block_special_folder_location_t *special_folder_location_data = NULL;
	static char *function                                                  = "liblnk_special_folder_location_read";

	if( special_folder_location == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid special folder location.",
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
	if( data_block->data_size < sizeof( lnk_data_block_special_folder_location_t ) )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_VALUE_OUT_OF_BOUNDS,
		 "%s: invalid data block - data size too small.",
		 function );

		return( -1 );
	}
	special_folder_location_data = (lnk_data_block_special_folder_location_t *) data_block->data;

	byte_stream_copy_to_uint32_little_endian(
	 special_folder_location_data->folder_identifier,
	 special_folder_location->folder_identifier );

	byte_stream_copy_to_uint32_little_endian(
	 special_folder_location_data->first_child_segment_offset,
	 special_folder_location->first_child_segment_offset );

#if defined( HAVE_DEBUG_OUTPUT )
	if( libcnotify_verbose != 0 )
	{
		libcnotify_printf(
		 "%s: folder identifier\t\t\t: %" PRIu32 "\n",
		 function,
		 special_folder_location->folder_identifier );

		libcnotify_printf(
		 "%s: first child segment offset\t\t: %" PRIu32 "\n",
		 function,
		 special_folder_location->first_child_segment_offset );

		libcnotify_printf(
		 "\n" );
	}
#endif
#if defined( HAVE_DEBUG_OUTPUT )
	if( libcnotify_verbose != 0 )
	{
		if( data_block->data_size > sizeof( lnk_data_block_special_folder_location_t ) )
		{
			libcnotify_printf(
			 "%s: trailing data:\n",
			 function );
			libcnotify_print_data(
			 &( data_block->data[ sizeof( lnk_data_block_special_folder_location_t ) ] ),
			 data_block->data_size - sizeof( lnk_data_block_special_folder_location_t ),
			 0 );
		}
	}
#endif
	return( 1 );
}

