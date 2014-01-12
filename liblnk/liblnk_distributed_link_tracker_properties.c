/*
 * Distributed link tracker properties functions
 *
 * Copyright (c) 2009-2014, Joachim Metz <joachim.metz@gmail.com>
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
#include "liblnk_distributed_link_tracker_properties.h"
#include "liblnk_libcerror.h"
#include "liblnk_libcnotify.h"
#include "liblnk_libfguid.h"
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

#if defined( HAVE_DEBUG_OUTPUT )
	libcstring_system_character_t guid_string[ 48 ];

	libcstring_system_character_t *value_string                                                    = NULL;
	libfguid_identifier_t *guid                                                                    = NULL;
	size_t value_string_size                                                                       = 0;
	int result                                                                                     = 0;
#endif

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

		goto on_error;
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

		goto on_error;
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

		goto on_error;
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

		goto on_error;
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

		goto on_error;
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

		goto on_error;
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

		goto on_error;
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

#if defined( LIBCSTRING_HAVE_WIDE_SYSTEM_CHARACTER )
		result = libuna_utf16_string_size_from_byte_stream(
			  distributed_link_tracker_properties_data->machine_identifier_string,
			  16,
			  io_handle->ascii_codepage,
			  &value_string_size,
			  error );
#else
		result = libuna_utf8_string_size_from_byte_stream(
			  distributed_link_tracker_properties_data->machine_identifier_string,
			  16,
			  io_handle->ascii_codepage,
			  &value_string_size,
			  error );
#endif
		if( result != 1 )
		{
			libcerror_error_set(
			 error,
			 LIBCERROR_ERROR_DOMAIN_RUNTIME,
			 LIBCERROR_RUNTIME_ERROR_GET_FAILED,
			 "%s: unable to determine size of machine identifier string.",
			 function );

			goto on_error;
		}
		if( ( value_string_size > (size_t) SSIZE_MAX )
		 || ( ( sizeof( libcstring_system_character_t ) * value_string_size )  > (size_t) SSIZE_MAX ) )
		{
			libcerror_error_set(
			 error,
			 LIBCERROR_ERROR_DOMAIN_RUNTIME,
			 LIBCERROR_RUNTIME_ERROR_VALUE_EXCEEDS_MAXIMUM,
			 "%s: invalid machine identifier string size value exceeds maximum.",
			 function );

			goto on_error;
		}
		value_string = libcstring_system_string_allocate(
				value_string_size );

		if( value_string == NULL )
		{
			libcerror_error_set(
			 error,
			 LIBCERROR_ERROR_DOMAIN_MEMORY,
			 LIBCERROR_MEMORY_ERROR_INSUFFICIENT,
			 "%s: unable to create machine identifier string.",
			 function );

			goto on_error;
		}
#if defined( LIBCSTRING_HAVE_WIDE_SYSTEM_CHARACTER )
		result = libuna_utf16_string_copy_from_byte_stream(
			  (libuna_utf16_character_t *) value_string,
			  value_string_size,
			  distributed_link_tracker_properties_data->machine_identifier_string,
			  16,
			  io_handle->ascii_codepage,
			  error );
#else
		result = libuna_utf8_string_copy_from_byte_stream(
			  (libuna_utf8_character_t *) value_string,
			  value_string_size,
			  distributed_link_tracker_properties_data->machine_identifier_string,
			  16,
			  io_handle->ascii_codepage,
			  error );
#endif
		if( result != 1 )
		{
			libcerror_error_set(
			 error,
			 LIBCERROR_ERROR_DOMAIN_RUNTIME,
			 LIBCERROR_RUNTIME_ERROR_SET_FAILED,
			 "%s: unable to set machine identifier string.",
			 function );

			goto on_error;
		}
		libcnotify_printf(
		 "%s: machine identifier string\t: %" PRIs_LIBCSTRING_SYSTEM "\n",
		 function,
		 value_string );

		memory_free(
		 value_string );

		value_string = NULL;

		if( libfguid_identifier_initialize(
		     &guid,
		     error ) != 1 )
		{
			libcerror_error_set(
			 error,
			 LIBCERROR_ERROR_DOMAIN_RUNTIME,
			 LIBCERROR_RUNTIME_ERROR_INITIALIZE_FAILED,
			 "%s: unable to create GUID.",
			 function );

			goto on_error;
		}
		if( libfguid_identifier_copy_from_byte_stream(
		     guid,
		     distributed_link_tracker_properties->droid_volume_identifier,
		     16,
		     LIBFGUID_ENDIAN_LITTLE,
		     error ) != 1 )
		{
			libcerror_error_set(
			 error,
			 LIBCERROR_ERROR_DOMAIN_RUNTIME,
			 LIBCERROR_RUNTIME_ERROR_COPY_FAILED,
			 "%s: unable to copy byte stream to GUID.",
			 function );

			goto on_error;
		}
#if defined( LIBCSTRING_HAVE_WIDE_SYSTEM_CHARACTER )
		result = libfguid_identifier_copy_to_utf16_string(
			  guid,
			  (uint16_t *) guid_string,
			  48,
			  LIBFGUID_STRING_FORMAT_FLAG_USE_LOWER_CASE,
			  error );
#else
		result = libfguid_identifier_copy_to_utf8_string(
			  guid,
			  (uint8_t *) guid_string,
			  48,
			  LIBFGUID_STRING_FORMAT_FLAG_USE_LOWER_CASE,
			  error );
#endif
		if( result != 1 )
		{
			libcerror_error_set(
			 error,
			 LIBCERROR_ERROR_DOMAIN_RUNTIME,
			 LIBCERROR_RUNTIME_ERROR_COPY_FAILED,
			 "%s: unable to copy GUID to string.",
			 function );

			goto on_error;
		}
		libcnotify_printf(
		 "%s: droid volume identifier\t: %" PRIs_LIBCSTRING_SYSTEM "\n",
		 function,
		 guid_string );

		if( libfguid_identifier_copy_from_byte_stream(
		     guid,
		     distributed_link_tracker_properties->droid_file_identifier,
		     16,
		     LIBFGUID_ENDIAN_LITTLE,
		     error ) != 1 )
		{
			libcerror_error_set(
			 error,
			 LIBCERROR_ERROR_DOMAIN_RUNTIME,
			 LIBCERROR_RUNTIME_ERROR_COPY_FAILED,
			 "%s: unable to copy byte stream to GUID.",
			 function );

			goto on_error;
		}
#if defined( LIBCSTRING_HAVE_WIDE_SYSTEM_CHARACTER )
		result = libfguid_identifier_copy_to_utf16_string(
			  guid,
			  (uint16_t *) guid_string,
			  48,
			  LIBFGUID_STRING_FORMAT_FLAG_USE_LOWER_CASE,
			  error );
#else
		result = libfguid_identifier_copy_to_utf8_string(
			  guid,
			  (uint8_t *) guid_string,
			  48,
			  LIBFGUID_STRING_FORMAT_FLAG_USE_LOWER_CASE,
			  error );
#endif
		if( result != 1 )
		{
			libcerror_error_set(
			 error,
			 LIBCERROR_ERROR_DOMAIN_RUNTIME,
			 LIBCERROR_RUNTIME_ERROR_COPY_FAILED,
			 "%s: unable to copy GUID to string.",
			 function );

			goto on_error;
		}
		libcnotify_printf(
		 "%s: droid file identifier\t\t: %" PRIs_LIBCSTRING_SYSTEM "\n",
		 function,
		 guid_string );

		if( libfguid_identifier_copy_from_byte_stream(
		     guid,
		     distributed_link_tracker_properties->birth_droid_volume_identifier,
		     16,
		     LIBFGUID_ENDIAN_LITTLE,
		     error ) != 1 )
		{
			libcerror_error_set(
			 error,
			 LIBCERROR_ERROR_DOMAIN_RUNTIME,
			 LIBCERROR_RUNTIME_ERROR_COPY_FAILED,
			 "%s: unable to copy byte stream to GUID.",
			 function );

			goto on_error;
		}
#if defined( LIBCSTRING_HAVE_WIDE_SYSTEM_CHARACTER )
		result = libfguid_identifier_copy_to_utf16_string(
			  guid,
			  (uint16_t *) guid_string,
			  48,
			  LIBFGUID_STRING_FORMAT_FLAG_USE_LOWER_CASE,
			  error );
#else
		result = libfguid_identifier_copy_to_utf8_string(
			  guid,
			  (uint8_t *) guid_string,
			  48,
			  LIBFGUID_STRING_FORMAT_FLAG_USE_LOWER_CASE,
			  error );
#endif
		if( result != 1 )
		{
			libcerror_error_set(
			 error,
			 LIBCERROR_ERROR_DOMAIN_RUNTIME,
			 LIBCERROR_RUNTIME_ERROR_COPY_FAILED,
			 "%s: unable to copy GUID to string.",
			 function );

			goto on_error;
		}
		libcnotify_printf(
		 "%s: birth droid volume identifier\t: %" PRIs_LIBCSTRING_SYSTEM "\n",
		 function,
		 guid_string );

		if( libfguid_identifier_copy_from_byte_stream(
		     guid,
		     distributed_link_tracker_properties->birth_droid_file_identifier,
		     16,
		     LIBFGUID_ENDIAN_LITTLE,
		     error ) != 1 )
		{
			libcerror_error_set(
			 error,
			 LIBCERROR_ERROR_DOMAIN_RUNTIME,
			 LIBCERROR_RUNTIME_ERROR_COPY_FAILED,
			 "%s: unable to copy byte stream to GUID.",
			 function );

			goto on_error;
		}
#if defined( LIBCSTRING_HAVE_WIDE_SYSTEM_CHARACTER )
		result = libfguid_identifier_copy_to_utf16_string(
			  guid,
			  (uint16_t *) guid_string,
			  48,
			  LIBFGUID_STRING_FORMAT_FLAG_USE_LOWER_CASE,
			  error );
#else
		result = libfguid_identifier_copy_to_utf8_string(
			  guid,
			  (uint8_t *) guid_string,
			  48,
			  LIBFGUID_STRING_FORMAT_FLAG_USE_LOWER_CASE,
			  error );
#endif
		if( result != 1 )
		{
			libcerror_error_set(
			 error,
			 LIBCERROR_ERROR_DOMAIN_RUNTIME,
			 LIBCERROR_RUNTIME_ERROR_COPY_FAILED,
			 "%s: unable to copy GUID to string.",
			 function );

			goto on_error;
		}
		libcnotify_printf(
		 "%s: birth droid file identifier\t: %" PRIs_LIBCSTRING_SYSTEM "\n",
		 function,
		 guid_string );

		libcnotify_printf(
		 "\n" );

		if( libfguid_identifier_free(
		     &guid,
		     error ) != 1 )
		{
			libcerror_error_set(
			 error,
			 LIBCERROR_ERROR_DOMAIN_RUNTIME,
			 LIBCERROR_RUNTIME_ERROR_FINALIZE_FAILED,
			 "%s: unable to free GUID.",
			 function );

			goto on_error;
		}
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

on_error:
#if defined( HAVE_DEBUG_OUTPUT )
	if( guid != NULL )
	{
		libfguid_identifier_free(
		 &guid,
		 NULL );
	}
	if( value_string != NULL )
	{
		memory_free(
		 value_string );
	}
#endif
	return( -1 );
}

