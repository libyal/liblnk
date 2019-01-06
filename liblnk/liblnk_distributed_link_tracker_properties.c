/*
 * Distributed link tracker properties functions
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
#include "liblnk_distributed_link_tracker_properties.h"
#include "liblnk_libcerror.h"
#include "liblnk_libcnotify.h"
#include "liblnk_libfguid.h"
#include "liblnk_libfwsi.h"
#include "liblnk_libuna.h"

#include "lnk_data_blocks.h"

/* Creates distributed link tracker properties
 * Make sure the value distributed_link_tracker_properties is referencing, is set to NULL
 * Returns 1 if successful or -1 on error
 */
int liblnk_distributed_link_tracker_properties_initialize(
     liblnk_distributed_link_tracker_properties_t **distributed_link_tracker_properties,
     libcerror_error_t **error )
{
	static char *function = "liblnk_distributed_link_tracker_properties_initialize";

	if( distributed_link_tracker_properties == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid distributed link tracker properties.",
		 function );

		return( -1 );
	}
	if( *distributed_link_tracker_properties != NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_VALUE_ALREADY_SET,
		 "%s: invalid distributed link tracker properties value already set.",
		 function );

		return( -1 );
	}
	*distributed_link_tracker_properties = memory_allocate_structure(
	                                        liblnk_distributed_link_tracker_properties_t );

	if( *distributed_link_tracker_properties == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_MEMORY,
		 LIBCERROR_MEMORY_ERROR_INSUFFICIENT,
		 "%s: unable to create distributed link tracker properties.",
		 function );

		goto on_error;
	}
	if( memory_set(
	     *distributed_link_tracker_properties,
	     0,
	     sizeof( liblnk_distributed_link_tracker_properties_t ) ) == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_MEMORY,
		 LIBCERROR_MEMORY_ERROR_SET_FAILED,
		 "%s: unable to clear distributed link tracker properties.",
		 function );

		goto on_error;
	}
	return( 1 );

on_error:
	if( *distributed_link_tracker_properties != NULL )
	{
		memory_free(
		 *distributed_link_tracker_properties );

		*distributed_link_tracker_properties = NULL;
	}
	return( -1 );
}

/* Frees distributed link tracker properties
 * Returns 1 if successful or -1 on error
 */
int liblnk_distributed_link_tracker_properties_free(
     liblnk_distributed_link_tracker_properties_t **distributed_link_tracker_properties,
     libcerror_error_t **error )
{
	static char *function = "liblnk_distributed_link_tracker_properties_free";

	if( distributed_link_tracker_properties == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid distributed link tracker properties.",
		 function );

		return( -1 );
	}
	if( *distributed_link_tracker_properties != NULL )
	{
		memory_free(
		 *distributed_link_tracker_properties );

		*distributed_link_tracker_properties = NULL;
	}
	return( 1 );
}

/* Reads distributed link tracker properties
 * Returns the number of bytes read if successful or -1 on error
 */
int liblnk_distributed_link_tracker_properties_read(
     liblnk_distributed_link_tracker_properties_t *distributed_link_tracker_properties,
     liblnk_data_block_t *data_block,
     liblnk_io_handle_t *io_handle,
     libcerror_error_t **error )
{
	lnk_data_block_distributed_link_tracker_properties_t *distributed_link_tracker_properties_data = NULL;
	static char *function                                                                          = "liblnk_distributed_link_tracker_properties_read";
	uint32_t data_size                                                                             = 0;
	uint32_t data_version                                                                          = 0;

	if( distributed_link_tracker_properties == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid distributed link tracker properties.",
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
	if( data_block->data_size < sizeof( lnk_data_block_distributed_link_tracker_properties_t ) )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_VALUE_OUT_OF_BOUNDS,
		 "%s: invalid data block - data size too small.",
		 function );

		return( -1 );
	}
	distributed_link_tracker_properties_data = (lnk_data_block_distributed_link_tracker_properties_t *) data_block->data;

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
	byte_stream_copy_to_uint32_little_endian(
	 distributed_link_tracker_properties_data->data_size,
	 data_size );

	byte_stream_copy_to_uint32_little_endian(
	 distributed_link_tracker_properties_data->data_version,
	 data_version );

	if( data_version != 0 )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_UNSUPPORTED_VALUE,
		 "%s: unsupported data version: %" PRIu32 ".",
		 function,
		 data_version );

		return( -1 );
	}
/* TODO check if data size matches data block size */
	if( data_size < 88 )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_UNSUPPORTED_VALUE,
		 "%s: unsupported data size: %" PRIu32 ".",
		 function,
		 data_size );

		return( -1 );
	}
	if( memory_copy(
	     distributed_link_tracker_properties->machine_identifier_string,
	     distributed_link_tracker_properties_data->machine_identifier_string,
	     16 ) == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_MEMORY,
		 LIBCERROR_MEMORY_ERROR_COPY_FAILED,
		 "%s: unable to copy machine identifier string.",
		 function );

		return( -1 );
	}
	if( memory_copy(
	     distributed_link_tracker_properties->droid_volume_identifier,
	     distributed_link_tracker_properties_data->droid_volume_identifier,
	     16 ) == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_MEMORY,
		 LIBCERROR_MEMORY_ERROR_COPY_FAILED,
		 "%s: unable to copy droid volume identifier.",
		 function );

		return( -1 );
	}
	if( memory_copy(
	     distributed_link_tracker_properties->droid_file_identifier,
	     distributed_link_tracker_properties_data->droid_file_identifier,
	     16 ) == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_MEMORY,
		 LIBCERROR_MEMORY_ERROR_COPY_FAILED,
		 "%s: unable to copy droid file identifier.",
		 function );

		return( -1 );
	}
	if( memory_copy(
	     distributed_link_tracker_properties->birth_droid_volume_identifier,
	     distributed_link_tracker_properties_data->birth_droid_volume_identifier,
	     16 ) == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_MEMORY,
		 LIBCERROR_MEMORY_ERROR_COPY_FAILED,
		 "%s: unable to copy birth droid volume identifier.",
		 function );

		return( -1 );
	}
	if( memory_copy(
	     distributed_link_tracker_properties->birth_droid_file_identifier,
	     distributed_link_tracker_properties_data->birth_droid_file_identifier,
	     16 ) == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_MEMORY,
		 LIBCERROR_MEMORY_ERROR_COPY_FAILED,
		 "%s: unable to copy birth droid file identifier.",
		 function );

		return( -1 );
	}
#if defined( HAVE_DEBUG_OUTPUT )
	if( libcnotify_verbose != 0 )
	{
		libcnotify_printf(
		 "%s: data size\t\t\t: %" PRIu32 "\n",
		 function,
		 data_size );

		libcnotify_printf(
		 "%s: data version\t\t\t: %" PRIu32 "\n",
		 function,
		 data_version );

		libcnotify_printf(
		 "%s: machine identifier string data:\n",
		 function );
		libcnotify_print_data(
		 distributed_link_tracker_properties_data->machine_identifier_string,
		 16,
		 0 );

		if( liblnk_debug_print_string_value(
		     function,
		     "machine identifier string\t",
		     distributed_link_tracker_properties_data->machine_identifier_string,
		     16,
		     io_handle->ascii_codepage,
		     error ) != 1 )
		{
			libcerror_error_set(
			 error,
			 LIBCERROR_ERROR_DOMAIN_RUNTIME,
			 LIBCERROR_RUNTIME_ERROR_PRINT_FAILED,
			 "%s: unable to print string value.",
			 function );

			return( -1 );
		}
		if( liblnk_debug_print_guid_value(
		     function,
		     "droid volume identifier\t",
		     distributed_link_tracker_properties->droid_volume_identifier,
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
		if( liblnk_debug_print_guid_value(
		     function,
		     "droid file identifier\t\t",
		     distributed_link_tracker_properties->droid_file_identifier,
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
		if( liblnk_debug_print_guid_value(
		     function,
		     "birth droid volume identifier\t",
		     distributed_link_tracker_properties->birth_droid_volume_identifier,
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
		if( liblnk_debug_print_guid_value(
		     function,
		     "birth droid file identifier\t",
		     distributed_link_tracker_properties->birth_droid_file_identifier,
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
		 "\n" );
	}
#endif
#if defined( HAVE_DEBUG_OUTPUT )
	if( libcnotify_verbose != 0 )
	{
		if( data_block->data_size > sizeof( lnk_data_block_distributed_link_tracker_properties_t ) )
		{
			libcnotify_printf(
			 "%s: trailing data:\n",
			 function );
			libcnotify_print_data(
			 &( data_block->data[ sizeof( lnk_data_block_distributed_link_tracker_properties_t ) ] ),
			 data_block->data_size - sizeof( lnk_data_block_distributed_link_tracker_properties_t ),
			 0 );
		}
	}
#endif
	return( 1 );
}

