/*
 * Location information functions
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

#include "liblnk_debug.h"
#include "liblnk_definitions.h"
#include "liblnk_libbfio.h"
#include "liblnk_libcerror.h"
#include "liblnk_libcnotify.h"
#include "liblnk_libfwsi.h"
#include "liblnk_libuna.h"
#include "liblnk_location_information.h"

#include "lnk_location_information.h"
#include "lnk_network_share_information.h"
#include "lnk_volume_information.h"

/* Creates location information
 * Make sure the value location_information is referencing, is set to NULL
 * Returns 1 if successful or -1 on error
 */
int liblnk_location_information_initialize(
     liblnk_location_information_t **location_information,
     libcerror_error_t **error )
{
	static char *function = "liblnk_location_information_initialize";

	if( location_information == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid location information.",
		 function );

		return( -1 );
	}
	if( *location_information != NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_VALUE_ALREADY_SET,
		 "%s: invalid location information value already set.",
		 function );

		return( -1 );
	}
	*location_information = memory_allocate_structure(
				 liblnk_location_information_t );

	if( *location_information == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_MEMORY,
		 LIBCERROR_MEMORY_ERROR_INSUFFICIENT,
		 "%s: unable to create location information.",
		 function );

		goto on_error;
	}
	if( memory_set(
	     *location_information,
	     0,
	     sizeof( liblnk_location_information_t ) ) == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_MEMORY,
		 LIBCERROR_MEMORY_ERROR_SET_FAILED,
		 "%s: unable to clear location information.",
		 function );

		goto on_error;
	}
	return( 1 );

on_error:
	if( *location_information != NULL )
	{
		memory_free(
		 *location_information );

		*location_information = NULL;
	}
	return( -1 );
}

/* Frees location information
 * Returns 1 if successful or -1 on error
 */
int liblnk_location_information_free(
     liblnk_location_information_t **location_information,
     libcerror_error_t **error )
{
	static char *function = "liblnk_location_information_free";

	if( location_information == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid location information.",
		 function );

		return( -1 );
	}
	if( *location_information != NULL )
	{
		if( ( *location_information )->volume_label != NULL )
		{
			memory_free(
			 ( *location_information )->volume_label );
		}
		if( ( *location_information )->local_path != NULL )
		{
			memory_free(
			 ( *location_information )->local_path );
		}
		if( ( *location_information )->network_share_name != NULL )
		{
			memory_free(
			 ( *location_information )->network_share_name );
		}
		if( ( *location_information )->device_name != NULL )
		{
			memory_free(
			 ( *location_information )->device_name );
		}
		if( ( *location_information )->common_path != NULL )
		{
			memory_free(
			 ( *location_information )->common_path );
		}
		memory_free(
		 *location_information );

		*location_information = NULL;
	}
	return( 1 );
}

/* Reads a location information
 * Returns the number of bytes read if successful or -1 on error
 */
int liblnk_location_information_read_data(
     liblnk_location_information_t *location_information,
     liblnk_io_handle_t *io_handle,
     const uint8_t *data,
     size_t data_size,
     libcerror_error_t **error )
{
	const uint8_t *location_information_value_data = NULL;
	const uint8_t *string_data                     = NULL;
	const uint8_t *unicode_string_data             = NULL;
	static char *function                          = "liblnk_location_information_read_data";
	ssize_t read_count                             = 0;
	uint32_t common_path_offset                    = 0;
	uint32_t device_name_offset                    = 0;
	uint32_t local_path_offset                     = 0;
	uint32_t location_information_header_size      = 0;
	uint32_t location_information_value_size       = 0;
	uint32_t network_share_information_offset      = 0;
	uint32_t network_share_name_offset             = 0;
	uint32_t unicode_common_path_offset            = 0;
	uint32_t unicode_device_name_offset            = 0;
	uint32_t unicode_local_path_offset             = 0;
	uint32_t unicode_network_share_name_offset     = 0;
	uint32_t unicode_value_size                    = 0;
	uint32_t unicode_volume_label_offset           = 0;
	uint32_t value_size                            = 0;
	uint32_t volume_information_offset             = 0;
	uint32_t volume_label_data_size                = 0;
	uint32_t volume_label_offset                   = 0;

#if defined( HAVE_DEBUG_OUTPUT )
	uint32_t value_32bit                           = 0;
#endif

	if( location_information == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid location information.",
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
	if( data_size < sizeof( lnk_location_information_t ) )
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
#if defined( HAVE_DEBUG_OUTPUT )
	if( libcnotify_verbose != 0 )
	{
		libcnotify_printf(
		 "%s: location information data:\n",
		 function );
		libcnotify_print_data(
		 data,
		 data_size,
		 LIBCNOTIFY_PRINT_DATA_FLAG_GROUP_DATA );
	}
#endif
	byte_stream_copy_to_uint32_little_endian(
	 ( (lnk_location_information_t *) data )->header_size,
	 location_information_header_size );

	if( location_information_header_size == 0 )
	{
		io_handle->flags |= LIBLNK_IO_HANDLE_FLAG_IS_CORRUPTED;

		return( read_count + 4 );
	}
	byte_stream_copy_to_uint32_little_endian(
	 ( (lnk_location_information_t *) data )->location_flags,
	 location_information->flags );

	byte_stream_copy_to_uint32_little_endian(
	 ( (lnk_location_information_t *) data )->volume_information_offset,
	 volume_information_offset );

	byte_stream_copy_to_uint32_little_endian(
	 ( (lnk_location_information_t *) data )->local_path_offset,
	 local_path_offset );

	byte_stream_copy_to_uint32_little_endian(
	 ( (lnk_location_information_t *) data )->network_share_information_offset,
	 network_share_information_offset );

	byte_stream_copy_to_uint32_little_endian(
	 ( (lnk_location_information_t *) data )->common_path_offset,
	 common_path_offset );

#if defined( HAVE_DEBUG_OUTPUT )
	if( libcnotify_verbose != 0 )
	{
		libcnotify_printf(
		 "%s: location information header size\t\t\t\t: %" PRIu32 "\n",
		 function,
		 location_information_header_size );

		libcnotify_printf(
		 "%s: location information flags\t\t\t\t: 0x%08" PRIx32 "\n",
		 function,
		 location_information->flags );

		libcnotify_printf(
		 "%s: location information volume information offset\t\t: 0x%08" PRIx32 "\n",
		 function,
		 volume_information_offset );

		libcnotify_printf(
		 "%s: location information local path offset\t\t\t: 0x%08" PRIx32 "\n",
		 function,
		 local_path_offset );

		libcnotify_printf(
		 "%s: location information network share information offset\t: 0x%08" PRIx32 "\n",
		 function,
		 network_share_information_offset );

		libcnotify_printf(
		 "%s: location information common path offset\t\t\t: 0x%08" PRIx32 "\n",
		 function,
		 common_path_offset );
	}
#endif
	if( ( location_information_header_size != 28 )
	 && ( location_information_header_size != 32 )
	 && ( location_information_header_size != 36 ) )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_UNSUPPORTED_VALUE,
		 "%s: unsupported location information header size: %" PRIu32 ".",
		 function,
		 location_information_header_size );

		goto on_error;
	}
	if( location_information_header_size > 28 )
	{
		byte_stream_copy_to_uint32_little_endian(
		 ( (lnk_location_information_t *) data )->unicode_local_path_offset,
		 unicode_local_path_offset );

#if defined( HAVE_DEBUG_OUTPUT )
		if( libcnotify_verbose != 0 )
		{
			libcnotify_printf(
			 "%s: location information unicode local path offset\t\t: %" PRIu32 "\n",
			 function,
			 unicode_local_path_offset );
		}
#endif
	}
	if( location_information_header_size > 32 )
	{
		byte_stream_copy_to_uint32_little_endian(
		 ( (lnk_location_information_t *) data )->unicode_common_path_offset,
		 unicode_common_path_offset );

#if defined( HAVE_DEBUG_OUTPUT )
		if( libcnotify_verbose != 0 )
		{
			libcnotify_printf(
			 "%s: location information unicode common path offset\t\t: %" PRIu32 "\n",
			 function,
			 unicode_common_path_offset );
		}
#endif
	}
#if defined( HAVE_DEBUG_OUTPUT )
	if( libcnotify_verbose != 0 )
	{
		libcnotify_printf(
		 "\n" );
	}
#endif
	/* Volume information path
	 */
	if( ( ( location_information->flags & 0x00000001UL ) != 0 )
	 && ( volume_information_offset > 0 ) )
	{
		if( volume_information_offset < location_information_header_size )
		{
			libcerror_error_set(
			 error,
			 LIBCERROR_ERROR_DOMAIN_RUNTIME,
			 LIBCERROR_RUNTIME_ERROR_VALUE_OUT_OF_BOUNDS,
			 "%s: volume information offset smaller than location information header size.",
			 function );

			goto on_error;
		}
		volume_information_offset -= 4;

		if( data_size < 4 )
		{
			libcerror_error_set(
			 error,
			 LIBCERROR_ERROR_DOMAIN_RUNTIME,
			 LIBCERROR_RUNTIME_ERROR_VALUE_OUT_OF_BOUNDS,
			 "%s: location information size value out of bounds.",
			 function );

			goto on_error;
		}
		if( volume_information_offset > ( data_size - 4 ) )
		{
			libcerror_error_set(
			 error,
			 LIBCERROR_ERROR_DOMAIN_RUNTIME,
			 LIBCERROR_RUNTIME_ERROR_VALUE_OUT_OF_BOUNDS,
			 "%s: volume information offset exceeds location information size.",
			 function );

			goto on_error;
		}
		location_information_value_data = &( data[ volume_information_offset ] );

		byte_stream_copy_to_uint32_little_endian(
		 ( (lnk_volume_information_t *) location_information_value_data )->size,
		 location_information_value_size );

		if( location_information_value_size > ( data_size - volume_information_offset ) )
		{
			libcerror_error_set(
			 error,
			 LIBCERROR_ERROR_DOMAIN_RUNTIME,
			 LIBCERROR_RUNTIME_ERROR_VALUE_OUT_OF_BOUNDS,
			 "%s: volume information data size value out of bounds.",
			 function );

			goto on_error;
		}
#if defined( HAVE_DEBUG_OUTPUT )
		if( libcnotify_verbose != 0 )
		{
			libcnotify_printf(
			 "%s: volume information data:\n",
			 function );
			libcnotify_print_data(
			 location_information_value_data,
			 location_information_value_size,
			 LIBCNOTIFY_PRINT_DATA_FLAG_GROUP_DATA );
		}
#endif
		if( location_information_value_size < 16 )
		{
			libcerror_error_set(
			 error,
			 LIBCERROR_ERROR_DOMAIN_RUNTIME,
			 LIBCERROR_RUNTIME_ERROR_VALUE_OUT_OF_BOUNDS,
			 "%s: location information value size value out of bounds.",
			 function );

			goto on_error;
		}
		byte_stream_copy_to_uint32_little_endian(
		 ( (lnk_volume_information_t *) location_information_value_data )->drive_type,
		 location_information->drive_type );

		byte_stream_copy_to_uint32_little_endian(
		 ( (lnk_volume_information_t *) location_information_value_data )->drive_serial_number,
		 location_information->drive_serial_number );

		byte_stream_copy_to_uint32_little_endian(
		 ( (lnk_volume_information_t *) location_information_value_data )->volume_label_offset,
		 volume_label_offset );

#if defined( HAVE_DEBUG_OUTPUT )
		if( libcnotify_verbose != 0 )
		{
			libcnotify_printf(
			 "%s: volume information size\t\t\t\t\t: %" PRIu32 "\n",
			 function,
			 location_information_value_size );

			libcnotify_printf(
			 "%s: volume information drive type\t\t\t\t: 0x%08" PRIx32 " (%s)\n",
			 function,
			 location_information->drive_type,
			 liblnk_debug_print_drive_type(
			  location_information->drive_type ) );

			libcnotify_printf(
			 "%s: volume information drive serial number\t\t\t: 0x%08" PRIx32 "\n",
			 function,
			 location_information->drive_serial_number );

			libcnotify_printf(
			 "%s: volume information volume label offset\t\t\t: %" PRIu32 "\n",
			 function,
			 volume_label_offset );
		}
#endif
		if( volume_label_offset > 16 )
		{
			if( location_information_value_size < 20 )
			{
				libcerror_error_set(
				 error,
				 LIBCERROR_ERROR_DOMAIN_RUNTIME,
				 LIBCERROR_RUNTIME_ERROR_VALUE_OUT_OF_BOUNDS,
				 "%s: location information value size value out of bounds.",
				 function );

				goto on_error;
			}
			byte_stream_copy_to_uint32_little_endian(
			 ( (lnk_volume_information_t *) location_information_value_data )->unicode_volume_label_offset,
			 unicode_volume_label_offset );

#if defined( HAVE_DEBUG_OUTPUT )
			if( libcnotify_verbose != 0 )
			{
				libcnotify_printf(
				 "%s: unicode volume information volume label offset\t\t: %" PRIu32 "\n",
				 function,
				 unicode_volume_label_offset );
			}
#endif
		}
		if( volume_label_offset > 0 )
		{
			if( volume_label_offset > location_information_value_size )
			{
				libcerror_error_set(
				 error,
				 LIBCERROR_ERROR_DOMAIN_RUNTIME,
				 LIBCERROR_RUNTIME_ERROR_VALUE_OUT_OF_BOUNDS,
				 "%s: volume label offset exceeds volume information data.",
				 function );

				goto on_error;
			}
			volume_label_data_size = location_information_value_size - volume_label_offset;

			string_data = &( location_information_value_data[ volume_label_offset ] );

			for( value_size = 0;
			     value_size < volume_label_data_size;
			     value_size++ )
			{
				if( string_data[ value_size ] == 0 )
				{
					value_size++;
					break;
				}
			}
#if defined( HAVE_DEBUG_OUTPUT )
			if( libcnotify_verbose != 0 )
			{
				libcnotify_printf(
				 "%s: volume information volume label size\t\t\t: %" PRIu32 "\n",
				 function,
				 value_size );

				libcnotify_printf(
				 "%s: volume information volume label data:\n",
				 function );
				libcnotify_print_data(
				 string_data,
				 value_size,
				 LIBCNOTIFY_PRINT_DATA_FLAG_GROUP_DATA );
			}
#endif
		}
		if( unicode_volume_label_offset > 0 )
		{
			if( unicode_volume_label_offset > location_information_value_size )
			{
				libcerror_error_set(
				 error,
				 LIBCERROR_ERROR_DOMAIN_RUNTIME,
				 LIBCERROR_RUNTIME_ERROR_VALUE_OUT_OF_BOUNDS,
				 "%s: unicode volume label offset exceeds volume information data.",
				 function );

				goto on_error;
			}
			volume_label_data_size = location_information_value_size - unicode_volume_label_offset;

			unicode_string_data = &( location_information_value_data[ unicode_volume_label_offset ] );

			for( unicode_value_size = 0;
			     ( unicode_value_size + 1 ) < volume_label_data_size;
			     unicode_value_size += 2 )
			{
				if( ( unicode_string_data[ unicode_value_size ] == 0 )
				 && ( unicode_string_data[ unicode_value_size + 1 ] == 0 ) )
				{
					unicode_value_size += 2;
					break;
				}
			}
#if defined( HAVE_DEBUG_OUTPUT )
			if( libcnotify_verbose != 0 )
			{
				libcnotify_printf(
				 "%s: unicode volume information volume label size\t\t: %" PRIu32 "\n",
				 function,
				 unicode_value_size );

				libcnotify_printf(
				 "%s: unicode volume information volume label data:\n",
				 function );
				libcnotify_print_data(
				 unicode_string_data,
				 unicode_value_size,
				 LIBCNOTIFY_PRINT_DATA_FLAG_GROUP_DATA );
			}
#endif
			location_information->volume_label = (uint8_t *) memory_allocate(
			                                                  sizeof( uint8_t ) * unicode_value_size );

			if( location_information->volume_label == NULL )
			{
				libcerror_error_set(
				 error,
				 LIBCERROR_ERROR_DOMAIN_MEMORY,
				 LIBCERROR_MEMORY_ERROR_INSUFFICIENT,
				 "%s: unable to create volume label.",
				 function );

				goto on_error;
			}
			if( memory_copy(
			     location_information->volume_label,
			     unicode_string_data,
			     unicode_value_size ) == NULL )
			{
				libcerror_error_set(
				 error,
				 LIBCERROR_ERROR_DOMAIN_MEMORY,
				 LIBCERROR_MEMORY_ERROR_COPY_FAILED,
				 "%s: unable to copy volume label.",
				 function );

				goto on_error;
			}
			location_information->volume_label_size = unicode_value_size;
			location_information->string_flags     |= LIBLNK_LOCATION_INFORMATION_STRING_FLAG_VOLUME_LABEL_IS_UNICODE;
		}
		else if( volume_label_offset > 0 )
		{
			location_information->volume_label = (uint8_t *) memory_allocate(
			                                                  sizeof( uint8_t ) * value_size );

			if( location_information->volume_label == NULL )
			{
				libcerror_error_set(
				 error,
				 LIBCERROR_ERROR_DOMAIN_MEMORY,
				 LIBCERROR_MEMORY_ERROR_INSUFFICIENT,
				 "%s: unable to create volume label.",
				 function );

				goto on_error;
			}
			if( memory_copy(
			     location_information->volume_label,
			     string_data,
			     value_size ) == NULL )
			{
				libcerror_error_set(
				 error,
				 LIBCERROR_ERROR_DOMAIN_MEMORY,
				 LIBCERROR_MEMORY_ERROR_COPY_FAILED,
				 "%s: unable to copy volume label.",
				 function );

				goto on_error;
			}
			location_information->volume_label_size = value_size;
		}
#if defined( HAVE_DEBUG_OUTPUT )
		if( libcnotify_verbose != 0 )
		{
			if( ( location_information->string_flags & LIBLNK_LOCATION_INFORMATION_STRING_FLAG_VOLUME_LABEL_IS_UNICODE ) != 0 )
			{
				if( liblnk_debug_print_utf16_string_value(
				     function,
				     "volume information volume label\t\t\t\t",
				     location_information->volume_label,
				     location_information->volume_label_size,
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
			}
			else
			{
				if( liblnk_debug_print_string_value(
				     function,
				     "volume information volume label\t\t\t\t",
				     location_information->volume_label,
				     location_information->volume_label_size,
				     io_handle->ascii_codepage,
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
		}
#endif
	}
	/* Local path
	 */
	if( ( location_information->flags & 0x00000001UL ) != 0 )
	{
		if( local_path_offset > 0 )
		{
			if( local_path_offset < location_information_header_size )
			{
				libcerror_error_set(
				 error,
				 LIBCERROR_ERROR_DOMAIN_RUNTIME,
				 LIBCERROR_RUNTIME_ERROR_VALUE_OUT_OF_BOUNDS,
				 "%s: local path information offset smaller than location information header size",
				 function );

				goto on_error;
			}
			local_path_offset -= 4;

			if( local_path_offset > data_size )
			{
				libcerror_error_set(
				 error,
				 LIBCERROR_ERROR_DOMAIN_RUNTIME,
				 LIBCERROR_RUNTIME_ERROR_VALUE_OUT_OF_BOUNDS,
				 "%s: local path offset exceeds location information data.",
				 function );

				goto on_error;
			}
			string_data = &( data[ local_path_offset ] );

			for( value_size = 0;
			     value_size < ( data_size - local_path_offset );
			     value_size++ )
			{
				if( string_data[ value_size ] == 0 )
				{
					value_size++;
					break;
				}
			}
#if defined( HAVE_DEBUG_OUTPUT )
			if( libcnotify_verbose != 0 )
			{
				libcnotify_printf(
				 "%s: local path data size\t\t\t\t\t: %" PRIu32 "\n",
				 function,
				 value_size );

				libcnotify_printf(
				 "%s: local path data:\n",
				 function );
				libcnotify_print_data(
				 string_data,
				 value_size,
				 LIBCNOTIFY_PRINT_DATA_FLAG_GROUP_DATA );
			}
#endif
		}
		if( unicode_local_path_offset > 0 )
		{
			if( unicode_local_path_offset < location_information_header_size )
			{
				libcerror_error_set(
				 error,
				 LIBCERROR_ERROR_DOMAIN_RUNTIME,
				 LIBCERROR_RUNTIME_ERROR_VALUE_OUT_OF_BOUNDS,
				 "%s: unicode local path information offset smaller than location information header size",
				 function );

				goto on_error;
			}
			unicode_local_path_offset -= 4;

			if( unicode_local_path_offset > data_size )
			{
				libcerror_error_set(
				 error,
				 LIBCERROR_ERROR_DOMAIN_RUNTIME,
				 LIBCERROR_RUNTIME_ERROR_VALUE_OUT_OF_BOUNDS,
				 "%s: unicode local path offset exceeds location information data.",
				 function );

				goto on_error;
			}
			unicode_string_data = &( data[ unicode_local_path_offset ] );

			for( unicode_value_size = 0;
			     ( unicode_value_size + 1 ) < ( data_size - unicode_local_path_offset );
			     unicode_value_size += 2 )
			{
				if( ( unicode_string_data[ unicode_value_size ] == 0 )
				 && ( unicode_string_data[ unicode_value_size + 1 ] == 0 ) )
				{
					unicode_value_size += 2;
					break;
				}
			}
#if defined( HAVE_DEBUG_OUTPUT )
			if( libcnotify_verbose != 0 )
			{
				libcnotify_printf(
				 "%s: unicode local path data size\t\t\t\t: %" PRIu32 "\n",
				 function,
				 value_size );

				libcnotify_printf(
				 "%s: unicode local path data:\n",
				 function );
				libcnotify_print_data(
				 unicode_string_data,
				 unicode_value_size,
				 LIBCNOTIFY_PRINT_DATA_FLAG_GROUP_DATA );
			}
#endif
			location_information->local_path = (uint8_t *) memory_allocate(
			                                                sizeof( uint8_t ) * unicode_value_size );

			if( location_information->local_path == NULL )
			{
				libcerror_error_set(
				 error,
				 LIBCERROR_ERROR_DOMAIN_MEMORY,
				 LIBCERROR_MEMORY_ERROR_INSUFFICIENT,
				 "%s: unable to create local path.",
				 function );

				goto on_error;
			}
			if( memory_copy(
			     location_information->local_path,
			     unicode_string_data,
			     unicode_value_size ) == NULL )
			{
				libcerror_error_set(
				 error,
				 LIBCERROR_ERROR_DOMAIN_MEMORY,
				 LIBCERROR_MEMORY_ERROR_COPY_FAILED,
				 "%s: unable to copy local path.",
				 function );

				goto on_error;
			}
			location_information->local_path_size = unicode_value_size;
			location_information->string_flags   |= LIBLNK_LOCATION_INFORMATION_STRING_FLAG_LOCAL_PATH_IS_UNICODE;
		}
		else if( local_path_offset > 0 )
		{
			location_information->local_path = (uint8_t *) memory_allocate(
			                                                sizeof( uint8_t ) * value_size );

			if( location_information->local_path == NULL )
			{
				libcerror_error_set(
				 error,
				 LIBCERROR_ERROR_DOMAIN_MEMORY,
				 LIBCERROR_MEMORY_ERROR_INSUFFICIENT,
				 "%s: unable to create local path.",
				 function );

				goto on_error;
			}
			if( memory_copy(
			     location_information->local_path,
			     string_data,
			     value_size ) == NULL )
			{
				libcerror_error_set(
				 error,
				 LIBCERROR_ERROR_DOMAIN_MEMORY,
				 LIBCERROR_MEMORY_ERROR_COPY_FAILED,
				 "%s: unable to copy local path.",
				 function );

				goto on_error;
			}
			location_information->local_path_size = value_size;
		}
#if defined( HAVE_DEBUG_OUTPUT )
		if( libcnotify_verbose != 0 )
		{
			if( ( local_path_offset > 0 )
			 || ( unicode_local_path_offset > 0 ) )
			{
				if( ( location_information->string_flags & LIBLNK_LOCATION_INFORMATION_STRING_FLAG_LOCAL_PATH_IS_UNICODE ) != 0 )
				{
					if( liblnk_debug_print_utf16_string_value(
					     function,
					     "local path\t\t\t\t\t\t",
					     location_information->local_path,
					     location_information->local_path_size,
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
				}
				else
				{
					if( liblnk_debug_print_string_value(
					     function,
					     "local path\t\t\t\t\t\t",
					     location_information->local_path,
					     location_information->local_path_size,
					     io_handle->ascii_codepage,
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
			}
		}
#endif
	}
	/* Network share information
	 */
	if( ( ( location_information->flags & 0x00000002UL ) != 0 )
	 && ( network_share_information_offset > 0 ) )
	{
		if( network_share_information_offset < location_information_header_size )
		{
			libcerror_error_set(
			 error,
			 LIBCERROR_ERROR_DOMAIN_RUNTIME,
			 LIBCERROR_RUNTIME_ERROR_VALUE_OUT_OF_BOUNDS,
			 "%s: network share information offset smaller than location information header size.",
			 function );

			goto on_error;
		}
		network_share_information_offset -= 4;

		if( data_size < 4 )
		{
			libcerror_error_set(
			 error,
			 LIBCERROR_ERROR_DOMAIN_RUNTIME,
			 LIBCERROR_RUNTIME_ERROR_VALUE_OUT_OF_BOUNDS,
			 "%s: location information size value out of bounds.",
			 function );

			goto on_error;
		}
		if( network_share_information_offset > ( data_size - 4 ) )
		{
			libcerror_error_set(
			 error,
			 LIBCERROR_ERROR_DOMAIN_RUNTIME,
			 LIBCERROR_RUNTIME_ERROR_VALUE_OUT_OF_BOUNDS,
			 "%s: network share information offset exceeds location information size.",
			 function );

			goto on_error;
		}
		location_information_value_data = &( data[ network_share_information_offset ] );

		byte_stream_copy_to_uint32_little_endian(
		 ( (lnk_network_share_information_t *) location_information_value_data )->size,
		 location_information_value_size );

		if( location_information_value_size > ( data_size - network_share_information_offset ) )
		{
			libcerror_error_set(
			 error,
			 LIBCERROR_ERROR_DOMAIN_RUNTIME,
			 LIBCERROR_RUNTIME_ERROR_VALUE_OUT_OF_BOUNDS,
			 "%s: network share information data size value out of bounds.",
			 function );

			goto on_error;
		}
#if defined( HAVE_DEBUG_OUTPUT )
		if( libcnotify_verbose != 0 )
		{
			libcnotify_printf(
			 "%s: network share information data:\n",
			 function );
			libcnotify_print_data(
			 location_information_value_data,
			 location_information_value_size,
			 LIBCNOTIFY_PRINT_DATA_FLAG_GROUP_DATA );
		}
#endif
		if( location_information_value_size < 16 )
		{
			libcerror_error_set(
			 error,
			 LIBCERROR_ERROR_DOMAIN_RUNTIME,
			 LIBCERROR_RUNTIME_ERROR_VALUE_OUT_OF_BOUNDS,
			 "%s: location information value size value out of bounds.",
			 function );

			goto on_error;
		}
		byte_stream_copy_to_uint32_little_endian(
		 ( (lnk_network_share_information_t *) location_information_value_data )->network_share_name_offset,
		 network_share_name_offset );

		byte_stream_copy_to_uint32_little_endian(
		 ( (lnk_network_share_information_t *) location_information_value_data )->device_name_offset,
		 device_name_offset );

		byte_stream_copy_to_uint32_little_endian(
		 ( (lnk_network_share_information_t *) location_information_value_data )->network_provider_type,
		 location_information->network_provider_type );

#if defined( HAVE_DEBUG_OUTPUT )
		if( libcnotify_verbose != 0 )
		{
			libcnotify_printf(
			 "%s: network share information size\t\t\t\t: %" PRIu32 "\n",
			 function,
			 location_information_value_size );

			byte_stream_copy_to_uint32_little_endian(
			 ( (lnk_network_share_information_t *) location_information_value_data )->network_share_type,
			 value_32bit );
			libcnotify_printf(
			 "%s: network share information network share type\t\t: 0x%08" PRIx32 "\n",
			 function,
			 value_32bit );

			libcnotify_printf(
			 "%s: network share information network share name offset\t: %" PRIu32 "\n",
			 function,
			 network_share_name_offset );

			libcnotify_printf(
			 "%s: network share information device name offset\t\t: %" PRIu32 "\n",
			 function,
			 device_name_offset );

			libcnotify_printf(
			 "%s: network share information network provider type\t\t: 0x%08" PRIx32 " (%s)\n",
			 function,
			 location_information->network_provider_type,
			 liblnk_debug_print_network_provider_type(
			  location_information->network_provider_type ) );
		}
#endif
		if( network_share_name_offset > 20 )
		{
			if( location_information_value_size < 28 )
			{
				libcerror_error_set(
				 error,
				 LIBCERROR_ERROR_DOMAIN_RUNTIME,
				 LIBCERROR_RUNTIME_ERROR_VALUE_OUT_OF_BOUNDS,
				 "%s: location information value size value out of bounds.",
				 function );

				goto on_error;
			}
			byte_stream_copy_to_uint32_little_endian(
			 ( (lnk_network_share_information_t *) location_information_value_data )->unicode_network_share_name_offset,
			 unicode_network_share_name_offset );

			byte_stream_copy_to_uint32_little_endian(
			 ( (lnk_network_share_information_t *) location_information_value_data )->unicode_device_name_offset,
			 unicode_device_name_offset );

#if defined( HAVE_DEBUG_OUTPUT )
			if( libcnotify_verbose != 0 )
			{
				libcnotify_printf(
				 "%s: network share information unicode network share name offset\t: %" PRIu32 "\n",
				 function,
				 unicode_network_share_name_offset );

				libcnotify_printf(
				 "%s: network share information unicode device name offset\t: %" PRIu32 "\n",
				 function,
				 unicode_device_name_offset );
			}
#endif
		}
		if( network_share_name_offset > 0 )
		{
			if( network_share_name_offset > location_information_value_size )
			{
				libcerror_error_set(
				 error,
				 LIBCERROR_ERROR_DOMAIN_RUNTIME,
				 LIBCERROR_RUNTIME_ERROR_VALUE_OUT_OF_BOUNDS,
				 "%s: network share name offset exceeds network share information data.",
				 function );

				goto on_error;
			}
			string_data = &( location_information_value_data[ network_share_name_offset ] );

			for( value_size = 0;
			     value_size < ( location_information_value_size - network_share_name_offset );
			     value_size++ )
			{
				if( string_data[ value_size ] == 0 )
				{
					value_size++;
					break;
				}
			}
#if defined( HAVE_DEBUG_OUTPUT )
			if( libcnotify_verbose != 0 )
			{
				libcnotify_printf(
				 "%s: network share information network share name size\t: %" PRIu32 "\n",
				 function,
				 value_size );

				libcnotify_printf(
				 "%s: network share information network share name data:\n",
				 function );
				libcnotify_print_data(
				 string_data,
				 value_size,
				 LIBCNOTIFY_PRINT_DATA_FLAG_GROUP_DATA );
			}
#endif
		}
		if( unicode_network_share_name_offset > 0 )
		{
			if( unicode_network_share_name_offset > location_information_value_size )
			{
				libcerror_error_set(
				 error,
				 LIBCERROR_ERROR_DOMAIN_RUNTIME,
				 LIBCERROR_RUNTIME_ERROR_VALUE_OUT_OF_BOUNDS,
				 "%s: unicode network share name offset exceeds volume information data.",
				 function );

				goto on_error;
			}
			unicode_string_data = &( location_information_value_data[ unicode_network_share_name_offset ] );

			for( unicode_value_size = 0;
			     ( unicode_value_size + 1 ) < ( location_information_value_size - unicode_network_share_name_offset );
			     unicode_value_size += 2 )
			{
				if( ( unicode_string_data[ unicode_value_size ] == 0 )
				 && ( unicode_string_data[ unicode_value_size + 1 ] == 0 ) )
				{
					unicode_value_size += 2;
					break;
				}
			}
#if defined( HAVE_DEBUG_OUTPUT )
			if( libcnotify_verbose != 0 )
			{
				libcnotify_printf(
				 "%s: unicode volume information network share name size\t\t: %" PRIu32 "\n",
				 function,
				 unicode_value_size );

				libcnotify_printf(
				 "%s: unicode volume information network share name data:\n",
				 function );
				libcnotify_print_data(
				 unicode_string_data,
				 unicode_value_size,
				 LIBCNOTIFY_PRINT_DATA_FLAG_GROUP_DATA );
			}
#endif
			location_information->network_share_name = (uint8_t *) memory_allocate(
			                                                        sizeof( uint8_t ) * unicode_value_size );

			if( location_information->network_share_name == NULL )
			{
				libcerror_error_set(
				 error,
				 LIBCERROR_ERROR_DOMAIN_MEMORY,
				 LIBCERROR_MEMORY_ERROR_INSUFFICIENT,
				 "%s: unable to create network share name.",
				 function );

				goto on_error;
			}
			if( memory_copy(
			     location_information->network_share_name,
			     unicode_string_data,
			     unicode_value_size ) == NULL )
			{
				libcerror_error_set(
				 error,
				 LIBCERROR_ERROR_DOMAIN_MEMORY,
				 LIBCERROR_MEMORY_ERROR_COPY_FAILED,
				 "%s: unable to copy network share name.",
				 function );

				goto on_error;
			}
			location_information->network_share_name_size = unicode_value_size;
			location_information->string_flags           |= LIBLNK_LOCATION_INFORMATION_STRING_FLAG_NETWORK_SHARE_NAME_IS_UNICODE;
		}
		else if( network_share_name_offset > 0 )
		{
			location_information->network_share_name = (uint8_t *) memory_allocate(
										sizeof( uint8_t ) * value_size );

			if( location_information->network_share_name == NULL )
			{
				libcerror_error_set(
				 error,
				 LIBCERROR_ERROR_DOMAIN_MEMORY,
				 LIBCERROR_MEMORY_ERROR_INSUFFICIENT,
				 "%s: unable to create network share name.",
				 function );

				goto on_error;
			}
			if( memory_copy(
			     location_information->network_share_name,
			     string_data,
			     value_size ) == NULL )
			{
				libcerror_error_set(
				 error,
				 LIBCERROR_ERROR_DOMAIN_MEMORY,
				 LIBCERROR_MEMORY_ERROR_COPY_FAILED,
				 "%s: unable to copy network share name.",
				 function );

				goto on_error;
			}
			location_information->network_share_name_size = value_size;
		}
#if defined( HAVE_DEBUG_OUTPUT )
		if( libcnotify_verbose != 0 )
		{
			if( location_information->network_share_name != NULL )
			{
				if( ( location_information->string_flags & LIBLNK_LOCATION_INFORMATION_STRING_FLAG_NETWORK_SHARE_NAME_IS_UNICODE ) != 0 )
				{
					if( liblnk_debug_print_utf16_string_value(
					     function,
					     "volume information network share name\t\t\t",
					     location_information->network_share_name,
					     location_information->network_share_name_size,
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
				}
				else
				{
					if( liblnk_debug_print_string_value(
					     function,
					     "volume information network share name\t\t\t",
					     location_information->network_share_name,
					     location_information->network_share_name_size,
					     io_handle->ascii_codepage,
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
			}
		}
#endif
		if( device_name_offset > 0 )
		{
			if( device_name_offset > location_information_value_size )
			{
				libcerror_error_set(
				 error,
				 LIBCERROR_ERROR_DOMAIN_RUNTIME,
				 LIBCERROR_RUNTIME_ERROR_VALUE_OUT_OF_BOUNDS,
				 "%s: device name offset exceeds network share information data.",
				 function );

				goto on_error;
			}
			string_data = &( location_information_value_data[ device_name_offset ] );

			for( value_size = 0;
			     value_size < ( location_information_value_size - device_name_offset );
			     value_size++ )
			{
				if( string_data[ value_size ] == 0 )
				{
					value_size++;
					break;
				}
			}
#if defined( HAVE_DEBUG_OUTPUT )
			if( libcnotify_verbose != 0 )
			{
				libcnotify_printf(
				 "%s: network share information device name size\t\t: %" PRIu32 "\n",
				 function,
				 value_size );

				libcnotify_printf(
				 "%s: network share information device name data:\n",
				 function );
				libcnotify_print_data(
				 string_data,
				 value_size,
				 LIBCNOTIFY_PRINT_DATA_FLAG_GROUP_DATA );
			}
#endif
		}
		if( unicode_device_name_offset > 0 )
		{
			if( unicode_device_name_offset > location_information_value_size )
			{
				libcerror_error_set(
				 error,
				 LIBCERROR_ERROR_DOMAIN_RUNTIME,
				 LIBCERROR_RUNTIME_ERROR_VALUE_OUT_OF_BOUNDS,
				 "%s: unicode device name offset exceeds volume information data.",
				 function );

				goto on_error;
			}
			unicode_string_data = &( location_information_value_data[ unicode_device_name_offset ] );

			for( unicode_value_size = 0;
			     ( unicode_value_size + 1 ) < ( location_information_value_size - unicode_device_name_offset );
			     unicode_value_size += 2 )
			{
				if( ( unicode_string_data[ unicode_value_size ] == 0 )
				 && ( unicode_string_data[ unicode_value_size + 1 ] == 0 ) )
				{
					unicode_value_size += 2;
					break;
				}
			}
#if defined( HAVE_DEBUG_OUTPUT )
			if( libcnotify_verbose != 0 )
			{
				libcnotify_printf(
				 "%s: unicode volume information device name size\t\t: %" PRIu32 "\n",
				 function,
				 unicode_value_size );

				libcnotify_printf(
				 "%s: unicode volume information device name data:\n",
				 function );
				libcnotify_print_data(
				 unicode_string_data,
				 unicode_value_size,
				 LIBCNOTIFY_PRINT_DATA_FLAG_GROUP_DATA );
			}
#endif
			location_information->device_name = (uint8_t *) memory_allocate(
			                                                 sizeof( uint8_t ) * unicode_value_size );

			if( location_information->device_name == NULL )
			{
				libcerror_error_set(
				 error,
				 LIBCERROR_ERROR_DOMAIN_MEMORY,
				 LIBCERROR_MEMORY_ERROR_INSUFFICIENT,
				 "%s: unable to create device name.",
				 function );

				goto on_error;
			}
			if( memory_copy(
			     location_information->device_name,
			     unicode_string_data,
			     unicode_value_size ) == NULL )
			{
				libcerror_error_set(
				 error,
				 LIBCERROR_ERROR_DOMAIN_MEMORY,
				 LIBCERROR_MEMORY_ERROR_COPY_FAILED,
				 "%s: unable to copy device name.",
				 function );

				goto on_error;
			}
			location_information->device_name_size = unicode_value_size;
			location_information->string_flags    |= LIBLNK_LOCATION_INFORMATION_STRING_FLAG_DEVICE_NAME_IS_UNICODE;
		}
		else if( device_name_offset > 0 )
		{
			location_information->device_name = (uint8_t *) memory_allocate(
			                                                 sizeof( uint8_t ) * value_size );

			if( location_information->device_name == NULL )
			{
				libcerror_error_set(
				 error,
				 LIBCERROR_ERROR_DOMAIN_MEMORY,
				 LIBCERROR_MEMORY_ERROR_INSUFFICIENT,
				 "%s: unable to create device name.",
				 function );

				goto on_error;
			}
			if( memory_copy(
			     location_information->device_name,
			     string_data,
			     value_size ) == NULL )
			{
				libcerror_error_set(
				 error,
				 LIBCERROR_ERROR_DOMAIN_MEMORY,
				 LIBCERROR_MEMORY_ERROR_COPY_FAILED,
				 "%s: unable to copy device name.",
				 function );

				goto on_error;
			}
			location_information->device_name_size = value_size;
		}
#if defined( HAVE_DEBUG_OUTPUT )
		if( libcnotify_verbose != 0 )
		{
			if( location_information->device_name != NULL )
			{
				if( ( location_information->string_flags & LIBLNK_LOCATION_INFORMATION_STRING_FLAG_DEVICE_NAME_IS_UNICODE ) != 0 )
				{
					if( liblnk_debug_print_utf16_string_value(
					     function,
					     "volume information device name\t\t\t",
					     location_information->device_name,
					     location_information->device_name_size,
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
				}
				else
				{
					if( liblnk_debug_print_string_value(
					     function,
					     "volume information device name\t\t\t",
					     location_information->device_name,
					     location_information->device_name_size,
					     io_handle->ascii_codepage,
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
			}
		}
#endif /* defined( HAVE_DEBUG_OUTPUT ) */
	}
	/* Common path
	 */
	if( common_path_offset > 0 )
	{
		if( common_path_offset < location_information_header_size )
		{
			libcerror_error_set(
			 error,
			 LIBCERROR_ERROR_DOMAIN_RUNTIME,
			 LIBCERROR_RUNTIME_ERROR_VALUE_OUT_OF_BOUNDS,
			 "%s: common path offset smaller than location information header size.",
			 function );

			goto on_error;
		}
		common_path_offset -= 4;

		if( common_path_offset > data_size )
		{
			libcerror_error_set(
			 error,
			 LIBCERROR_ERROR_DOMAIN_RUNTIME,
			 LIBCERROR_RUNTIME_ERROR_VALUE_OUT_OF_BOUNDS,
			 "%s: common path offset exceeds location information data.",
			 function );

			goto on_error;
		}
		string_data = &( data[ common_path_offset ] );

		for( value_size = 0;
		     value_size < ( data_size - common_path_offset );
		     value_size++ )
		{
			if( string_data[ value_size ] == 0 )
			{
				value_size++;
				break;
			}
		}
#if defined( HAVE_DEBUG_OUTPUT )
		if( libcnotify_verbose != 0 )
		{
			libcnotify_printf(
			 "%s: common path data size\t\t\t\t\t: %" PRIu32 "\n",
			 function,
			 value_size );

			libcnotify_printf(
			 "%s: common path data:\n",
			 function );
			libcnotify_print_data(
			 string_data,
			 value_size,
			 LIBCNOTIFY_PRINT_DATA_FLAG_GROUP_DATA );
		}
#endif
	}
	if( unicode_common_path_offset > 0 )
	{
		if( unicode_common_path_offset < location_information_header_size )
		{
			libcerror_error_set(
			 error,
			 LIBCERROR_ERROR_DOMAIN_RUNTIME,
			 LIBCERROR_RUNTIME_ERROR_VALUE_OUT_OF_BOUNDS,
			 "%s: unicode common path information offset smaller than location information header size",
			 function );

			goto on_error;
		}
		unicode_common_path_offset -= 4;

		if( unicode_common_path_offset > data_size )
		{
			libcerror_error_set(
			 error,
			 LIBCERROR_ERROR_DOMAIN_RUNTIME,
			 LIBCERROR_RUNTIME_ERROR_VALUE_OUT_OF_BOUNDS,
			 "%s: unicode common path offset exceeds location information data.",
			 function );

			goto on_error;
		}
		unicode_string_data = &( data[ unicode_common_path_offset ] );

		for( unicode_value_size = 0;
		     ( unicode_value_size + 1 ) < ( data_size - unicode_common_path_offset );
		     unicode_value_size += 2 )
		{
			if( ( unicode_string_data[ unicode_value_size ] == 0 )
			 && ( unicode_string_data[ unicode_value_size + 1 ] == 0 ) )
			{
				unicode_value_size += 2;
				break;
			}
		}
#if defined( HAVE_DEBUG_OUTPUT )
		if( libcnotify_verbose != 0 )
		{
			libcnotify_printf(
			 "%s: unicode common path data size\t\t\t\t: %" PRIu32 "\n",
			 function,
			 value_size );

			libcnotify_printf(
			 "%s: unicode common path data:\n",
			 function );
			libcnotify_print_data(
			 unicode_string_data,
			 unicode_value_size,
			 LIBCNOTIFY_PRINT_DATA_FLAG_GROUP_DATA );
		}
#endif
		location_information->common_path = (uint8_t *) memory_allocate(
		                                                 sizeof( uint8_t ) * unicode_value_size );

		if( location_information->common_path == NULL )
		{
			libcerror_error_set(
			 error,
			 LIBCERROR_ERROR_DOMAIN_MEMORY,
			 LIBCERROR_MEMORY_ERROR_INSUFFICIENT,
			 "%s: unable to create common path.",
			 function );

			goto on_error;
		}
		if( memory_copy(
		     location_information->common_path,
		     unicode_string_data,
		     unicode_value_size ) == NULL )
		{
			libcerror_error_set(
			 error,
			 LIBCERROR_ERROR_DOMAIN_MEMORY,
			 LIBCERROR_MEMORY_ERROR_COPY_FAILED,
			 "%s: unable to copy common path.",
			 function );

			goto on_error;
		}
		location_information->common_path_size = unicode_value_size;
		location_information->string_flags    |= LIBLNK_LOCATION_INFORMATION_STRING_FLAG_COMMON_PATH_IS_UNICODE;
	}
	else if( common_path_offset > 0 )
	{
		location_information->common_path = (uint8_t *) memory_allocate(
		                                                 sizeof( uint8_t ) * value_size );

		if( location_information->common_path == NULL )
		{
			libcerror_error_set(
			 error,
			 LIBCERROR_ERROR_DOMAIN_MEMORY,
			 LIBCERROR_MEMORY_ERROR_INSUFFICIENT,
			 "%s: unable to create common path.",
			 function );

			goto on_error;
		}
		if( memory_copy(
		     location_information->common_path,
		     string_data,
		     value_size ) == NULL )
		{
			libcerror_error_set(
			 error,
			 LIBCERROR_ERROR_DOMAIN_MEMORY,
			 LIBCERROR_MEMORY_ERROR_COPY_FAILED,
			 "%s: unable to copy common path.",
			 function );

			goto on_error;
		}
		location_information->common_path_size = value_size;
	}
#if defined( HAVE_DEBUG_OUTPUT )
	if( libcnotify_verbose != 0 )
	{
		if( ( common_path_offset > 0 )
		 || ( unicode_common_path_offset > 0 ) )
		{
			if( ( location_information->string_flags & LIBLNK_LOCATION_INFORMATION_STRING_FLAG_COMMON_PATH_IS_UNICODE ) != 0 )
			{
				if( liblnk_debug_print_utf16_string_value(
				     function,
				     "common path\t\t\t\t\t\t",
				     location_information->common_path,
				     location_information->common_path_size,
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
			}
			else
			{
				if( liblnk_debug_print_string_value(
				     function,
				     "common path\t\t\t\t\t\t",
				     location_information->device_name,
				     location_information->device_name_size,
				     io_handle->ascii_codepage,
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
		}
	}
#endif /* defined( HAVE_VERBOSE_OUTPUT ) */
	return( 1 );

on_error:
	if( location_information->common_path != NULL )
	{
		memory_free(
		 location_information->common_path );

		location_information->common_path = NULL;
	}
	if( location_information->device_name != NULL )
	{
		memory_free(
		 location_information->device_name );

		location_information->device_name = NULL;
	}
	if( location_information->network_share_name != NULL )
	{
		memory_free(
		 location_information->network_share_name );

		location_information->network_share_name = NULL;
	}
	if( location_information->local_path != NULL )
	{
		memory_free(
		 location_information->local_path );

		location_information->local_path = NULL;
	}
	if( location_information->volume_label != NULL )
	{
		memory_free(
		 location_information->volume_label );

		location_information->volume_label = NULL;
	}
	return( -1 );
}

/* Reads a location information
 * Returns the number of bytes read if successful or -1 on error
 */
ssize_t liblnk_location_information_read(
         liblnk_location_information_t *location_information,
         liblnk_io_handle_t *io_handle,
         libbfio_handle_t *file_io_handle,
         off64_t location_information_offset,
         libcerror_error_t **error )
{
	uint8_t location_information_size_data[ 4 ];

	uint8_t *location_information_data = NULL;
	static char *function              = "liblnk_location_information_read";
	size_t location_information_size   = 0;
	ssize_t read_count                 = 0;

	if( location_information == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid location information.",
		 function );

		return( -1 );
	}
#if defined( HAVE_DEBUG_OUTPUT )
	if( libcnotify_verbose != 0 )
	{
		libcnotify_printf(
		 "%s: reading location information at offset: %" PRIi64 " (0x%08" PRIx64 ")\n",
		 function,
		 location_information_offset,
		 location_information_offset );
	}
#endif
	if( libbfio_handle_seek_offset(
	     file_io_handle,
	     location_information_offset,
	     SEEK_SET,
	     error ) == -1 )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_IO,
		 LIBCERROR_IO_ERROR_SEEK_FAILED,
		 "%s: unable to seek location information offset: %" PRIi64 ".",
		 function,
		 location_information_offset );

		goto on_error;
	}
	read_count = libbfio_handle_read_buffer(
	              file_io_handle,
	              location_information_size_data,
	              4,
	              error );

	if( read_count != (ssize_t) 4 )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_IO,
		 LIBCERROR_IO_ERROR_READ_FAILED,
		 "%s: unable to read location information size.",
		 function );

		goto on_error;
	}
	byte_stream_copy_to_uint32_little_endian(
	 location_information_size_data,
	 location_information_size );
	
#if defined( HAVE_DEBUG_OUTPUT )
	if( libcnotify_verbose != 0 )
	{
		libcnotify_printf(
		 "%s: location information size\t\t\t\t\t: %" PRIzd "\n",
		 function,
		 location_information_size );
	}
#endif
	if( location_information_size <= 4 )
	{
#if defined( HAVE_VERBOSE_OUTPUT )
		if( libcnotify_verbose != 0 )
		{
			libcnotify_printf(
			 "%s: empty location information.\n",
			 function );
		}
#endif
		return( read_count );
	}
	if( location_information_size > (size_t) SSIZE_MAX )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_VALUE_EXCEEDS_MAXIMUM,
		 "%s: location information size value exceeds maximum.",
		 function );

		goto on_error;
	}
	location_information_size -= 4;

	location_information_data = (uint8_t *) memory_allocate(
	                                         sizeof( uint8_t ) * location_information_size );

	if( location_information_data == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_MEMORY,
		 LIBCERROR_MEMORY_ERROR_INSUFFICIENT,
		 "%s: unable to create location information data.",
		 function );

		goto on_error;
	}
	read_count = libbfio_handle_read_buffer(
	              file_io_handle,
	              location_information_data,
	              location_information_size,
	              error );

	if( read_count != (ssize_t) location_information_size )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_IO,
		 LIBCERROR_IO_ERROR_READ_FAILED,
		 "%s: unable to read location information data.",
		 function );

		goto on_error;
	}
	if( liblnk_location_information_read_data(
	     location_information,
	     io_handle,
	     location_information_data,
	     location_information_size,
	     error ) != 1 )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_IO,
		 LIBCERROR_IO_ERROR_READ_FAILED,
		 "%s: unable to read location information.",
		 function );

		goto on_error;
	}
	memory_free(
	 location_information_data );

	location_information_data = NULL;

#if defined( HAVE_DEBUG_OUTPUT )
	if( libcnotify_verbose != 0 )
	{
		libcnotify_printf(
		 "\n" );
	}
#endif
	return( read_count + 4 );

on_error:
	if( location_information_data != NULL )
	{
		memory_free(
		 location_information_data );
	}
	return( -1 );
}

