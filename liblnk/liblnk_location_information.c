/*
 * Location information functions
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
#include "liblnk_location_information.h"

#include "lnk_location_information.h"

/* Creates location information
 * Returns 1 if successful or -1 on error
 */
int liblnk_location_information_initialize(
     liblnk_location_information_t **location_information,
     liberror_error_t **error )
{
	static char *function = "liblnk_location_information_initialize";

	if( location_information == NULL )
	{
		liberror_error_set(
		 error,
		 LIBERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid location information.",
		 function );

		return( -1 );
	}
	if( *location_information == NULL )
	{
		*location_information = (liblnk_location_information_t *) memory_allocate(
		                                         sizeof( liblnk_location_information_t ) );

		if( *location_information == NULL )
		{
			liberror_error_set(
			 error,
			 LIBERROR_ERROR_DOMAIN_MEMORY,
			 LIBERROR_MEMORY_ERROR_INSUFFICIENT,
			 "%s: unable to create location information.",
			 function );

			return( -1 );
		}
		if( memory_set(
		     *location_information,
		     0,
		     sizeof( liblnk_location_information_t ) ) == NULL )
		{
			liberror_error_set(
			 error,
			 LIBERROR_ERROR_DOMAIN_MEMORY,
			 LIBERROR_MEMORY_ERROR_SET_FAILED,
			 "%s: unable to clear location information.",
			 function );

			memory_free(
			 *location_information );

			*location_information = NULL;

			return( -1 );
		}
	}
	return( 1 );
}

/* Frees location information
 * Returns 1 if successful or -1 on error
 */
int liblnk_location_information_free(
     liblnk_location_information_t **location_information,
     liberror_error_t **error )
{
	static char *function = "liblnk_location_information_free";

	if( location_information == NULL )
	{
		liberror_error_set(
		 error,
		 LIBERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid location information.",
		 function );

		return( -1 );
	}
	if( *location_information != NULL )
	{
		memory_free(
		 *location_information );

		*location_information = NULL;
	}
	return( 1 );
}

/* Reads a location information
 * Returns the amount of bytes read if successful or -1 on error
 */
ssize_t liblnk_location_information_read(
         liblnk_location_information_t *location_information,
         libbfio_handle_t *file_io_handle,
         off64_t location_information_offset,
         liberror_error_t **error )
{
	uint8_t location_information_size_data[ 4 ];

	uint8_t *location_information_data        = NULL;
	uint8_t *location_information_value_data  = NULL;
	static char *function                     = "liblnk_location_information_read";
	size_t location_information_size          = 0;
	ssize_t read_count                        = 0;
	uint32_t local_path_offset                = 0;
	uint32_t path_remainder_offset            = 0;
	uint32_t network_share_information_offset = 0;
	uint32_t network_share_name_offset        = 0;
	uint32_t volume_information_offset        = 0;
	uint32_t volume_label_offset              = 0;
	uint32_t value_size                       = 0;

#if defined( HAVE_DEBUG_OUTPUT )
	uint32_t test                             = 0;
#endif

	if( location_information == NULL )
	{
		liberror_error_set(
		 error,
		 LIBERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid location information.",
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
	 "%s: reading location information at offset: %" PRIu64 " (0x%08" PRIx64 ")\n",
	 function,
	 location_information_offset,
	 location_information_offset );
#endif

	if( libbfio_handle_seek_offset(
	     file_io_handle,
	     location_information_offset,
	     SEEK_SET,
	     error ) == -1 )
	{
		liberror_error_set(
		 error,
		 LIBERROR_ERROR_DOMAIN_IO,
		 LIBERROR_IO_ERROR_SEEK_FAILED,
		 "%s: unable to seek location information offset: %" PRIu64 ".",
		 function,
		 location_information_offset );

		return( -1 );
	}
	read_count = libbfio_handle_read(
	              file_io_handle,
	              location_information_size_data,
	              4,
	              error );

	if( read_count != (ssize_t) 4 )
	{
		liberror_error_set(
		 error,
		 LIBERROR_ERROR_DOMAIN_IO,
		 LIBERROR_IO_ERROR_READ_FAILED,
		 "%s: unable to read location information size.",
		 function );

		return( -1 );
	}
	endian_little_convert_32bit(
	 location_information_size,
	 location_information_size_data );
	
#if defined( HAVE_DEBUG_OUTPUT )
	libnotify_verbose_printf(
	 "%s: location information size\t: %" PRIzd "\n",
	 function,
	 location_information_size );
#endif

	if( location_information_size <= 4 )
	{
#if defined( HAVE_VERBOSE_OUTPUT )
		libnotify_verbose_printf(
		 "%s: empty location information.\n",
		 function );
#endif

		return( read_count );
	}
	if( location_information_size > (size_t) SSIZE_MAX )
	{
		liberror_error_set(
		 error,
		 LIBERROR_ERROR_DOMAIN_RUNTIME,
		 LIBERROR_RUNTIME_ERROR_VALUE_EXCEEDS_MAXIMUM,
		 "%s: location information size value exceeds maximum.",
		 function );

		return( -1 );
	}
	location_information_size -= 4;

	location_information_data = (uint8_t *) memory_allocate(
	                                         sizeof( uint8_t ) * location_information_size );


	if( location_information_data == NULL )
	{
		liberror_error_set(
		 error,
		 LIBERROR_ERROR_DOMAIN_MEMORY,
		 LIBERROR_MEMORY_ERROR_INSUFFICIENT,
		 "%s: unable to create location information data.",
		 function );

		return( -1 );
	}
	read_count = libbfio_handle_read(
	              file_io_handle,
	              location_information_data,
	              location_information_size,
	              error );

	if( read_count != (ssize_t) location_information_size )
	{
		liberror_error_set(
		 error,
		 LIBERROR_ERROR_DOMAIN_IO,
		 LIBERROR_IO_ERROR_READ_FAILED,
		 "%s: unable to read location information data.",
		 function );

		memory_free(
		 location_information_data );

		return( -1 );
	}
#if defined( HAVE_DEBUG_OUTPUT )
	libnotify_verbose_printf(
	 "%s: location information data:\n",
	 function );
	libnotify_verbose_print_data(
	 location_information_data,
	 location_information_size );
#endif

#if defined( HAVE_VERBOSE_OUTPUT )
	endian_little_convert_32bit(
	 value_size,
	 ( (lnk_location_information_t *) location_information_data )->data_offset );
#endif
	endian_little_convert_32bit(
	 location_information->flags,
	 ( (lnk_location_information_t *) location_information_data )->location_flags );
	endian_little_convert_32bit(
	 volume_information_offset,
	 ( (lnk_location_information_t *) location_information_data )->volume_information_offset );
	endian_little_convert_32bit(
	 local_path_offset,
	 ( (lnk_location_information_t *) location_information_data )->local_path_offset );
	endian_little_convert_32bit(
	 network_share_information_offset,
	 ( (lnk_location_information_t *) location_information_data )->network_share_information_offset );
	endian_little_convert_32bit(
	 path_remainder_offset,
	 ( (lnk_location_information_t *) location_information_data )->path_remainder_offset );

#if defined( HAVE_VERBOSE_OUTPUT )
	libnotify_verbose_printf(
	 "%s: location information data offset\t\t\t: %" PRIu32 "\n",
	 function,
	 value_size );
	libnotify_verbose_printf(
	 "%s: location information flags\t\t\t\t: 0x%08" PRIx32 "\n",
	 function,
	 location_information->flags );
	libnotify_verbose_printf(
	 "%s: location information volume information offset\t: %" PRIu32 "\n",
	 function,
	 volume_information_offset );
	libnotify_verbose_printf(
	 "%s: location information local path offset\t\t: %" PRIu32 "\n",
	 function,
	 local_path_offset );
	libnotify_verbose_printf(
	 "%s: location information network share information offset\t: %" PRIu32 "\n",
	 function,
	 network_share_information_offset );
	libnotify_verbose_printf(
	 "%s: location information path remainder offset\t\t: %" PRIu32 "\n",
	 function,
	 path_remainder_offset );
	libnotify_verbose_printf(
	 "\n" );
#endif

	if( volume_information_offset > 0 )
	{
		if( volume_information_offset <= 4 )
		{
			liberror_error_set(
			 error,
			 LIBERROR_ERROR_DOMAIN_RUNTIME,
			 LIBERROR_RUNTIME_ERROR_VALUE_OUT_OF_RANGE,
			 "%s: volume information offset exceeds location information data.",
			 function );

			memory_free(
			 location_information_data );

			return( -1 );
		}
		volume_information_offset -= 4;

		if( volume_information_offset > location_information_size )
		{
			liberror_error_set(
			 error,
			 LIBERROR_ERROR_DOMAIN_RUNTIME,
			 LIBERROR_RUNTIME_ERROR_VALUE_OUT_OF_RANGE,
			 "%s: volume information offset exceeds location information data.",
			 function );

			memory_free(
			 location_information_data );

			return( -1 );
		}
		location_information_value_data = &( location_information_data[ volume_information_offset ] );

		endian_little_convert_32bit(
		 value_size,
		 ( (lnk_volume_information_t *) location_information_value_data )->size );

#if defined( HAVE_DEBUG_OUTPUT )
		libnotify_verbose_printf(
		 "%s: volume information data:\n",
		 function );
		libnotify_verbose_print_data(
		 location_information_value_data,
		 value_size );
#endif

		endian_little_convert_32bit(
		 volume_label_offset,
		 ( (lnk_volume_information_t *) location_information_value_data )->volume_label_offset );

#if defined( HAVE_VERBOSE_OUTPUT )
		libnotify_verbose_printf(
		 "%s: volume information size\t\t\t\t: %" PRIu32 "\n",
		 function,
		 value_size );

		endian_little_convert_32bit(
		 test,
		 ( (lnk_volume_information_t *) location_information_value_data )->volume_type );

		libnotify_verbose_printf(
		 "%s: volume information volume type\t\t\t: 0x%08" PRIx32 "\n",
		 function,
		 test );

		endian_little_convert_32bit(
		 test,
		 ( (lnk_volume_information_t *) location_information_value_data )->volume_serial_number );

		libnotify_verbose_printf(
		 "%s: volume information serial number\t\t\t: 0x%08" PRIx32 "\n",
		 function,
		 test );

		libnotify_verbose_printf(
		 "%s: volume information volume label offset\t\t: %" PRIu32 "\n",
		 function,
		 volume_label_offset );
#endif
		if( volume_label_offset > value_size )
		{
			liberror_error_set(
			 error,
			 LIBERROR_ERROR_DOMAIN_RUNTIME,
			 LIBERROR_RUNTIME_ERROR_VALUE_OUT_OF_RANGE,
			 "%s: volume label offset exceeds volume information data.",
			 function );

			memory_free(
			 location_information_data );

			return( -1 );
		}
		location_information_value_data = &( location_information_value_data[ volume_label_offset ] );

		value_size = 0;

		while( location_information_value_data[ value_size ] != 0 )
		{
			value_size++;
		}
		value_size++;

#if defined( HAVE_DEBUG_OUTPUT )
		libnotify_verbose_printf(
		 "%s: volume information volume label size\t\t\t: %" PRIu32 "\n",
		 function,
		 value_size );
		libnotify_verbose_printf(
		 "%s: volume information volume label data:\n",
		 function );
		libnotify_verbose_print_data(
		 location_information_value_data,
		 value_size );
#endif
	}
	if( local_path_offset > 0 )
	{
		if( local_path_offset <= 4 )
		{
			liberror_error_set(
			 error,
			 LIBERROR_ERROR_DOMAIN_RUNTIME,
			 LIBERROR_RUNTIME_ERROR_VALUE_OUT_OF_RANGE,
			 "%s: local path information offset exceeds location information data.",
			 function );

			memory_free(
			 location_information_data );

			return( -1 );
		}
		local_path_offset -= 4;

		if( local_path_offset > location_information_size )
		{
			liberror_error_set(
			 error,
			 LIBERROR_ERROR_DOMAIN_RUNTIME,
			 LIBERROR_RUNTIME_ERROR_VALUE_OUT_OF_RANGE,
			 "%s: local path offset exceeds location information data.",
			 function );

			memory_free(
			 location_information_data );

			return( -1 );
		}
		location_information_value_data = &( location_information_data[ local_path_offset ] );

		value_size = 0;

		while( location_information_value_data[ value_size ] != 0 )
		{
			value_size++;
		}
		value_size++;

#if defined( HAVE_DEBUG_OUTPUT )
		libnotify_verbose_printf(
		 "%s: local path size\t: %" PRIu32 "\n",
		 function,
		 value_size );
		libnotify_verbose_printf(
		 "%s: local path data:\n",
		 function );
		libnotify_verbose_print_data(
		 location_information_value_data,
		 value_size );
#endif
	}
	if( network_share_information_offset > 0 )
	{
		if( network_share_information_offset <= 4 )
		{
			liberror_error_set(
			 error,
			 LIBERROR_ERROR_DOMAIN_RUNTIME,
			 LIBERROR_RUNTIME_ERROR_VALUE_OUT_OF_RANGE,
			 "%s: network share information offset exceeds location information data.",
			 function );

			memory_free(
			 location_information_data );

			return( -1 );
		}
		network_share_information_offset -= 4;

		if( network_share_information_offset > location_information_size )
		{
			liberror_error_set(
			 error,
			 LIBERROR_ERROR_DOMAIN_RUNTIME,
			 LIBERROR_RUNTIME_ERROR_VALUE_OUT_OF_RANGE,
			 "%s: network share information offset exceeds location information data.",
			 function );

			memory_free(
			 location_information_data );

			return( -1 );
		}
		location_information_value_data = &( location_information_data[ network_share_information_offset ] );

		endian_little_convert_32bit(
		 value_size,
		 ( (lnk_network_share_information_t *) location_information_value_data )->size );

#if defined( HAVE_DEBUG_OUTPUT )
		libnotify_verbose_printf(
		 "%s: network share information data:\n",
		 function );
		libnotify_verbose_print_data(
		 location_information_value_data,
		 value_size );
#endif

		endian_little_convert_32bit(
		 network_share_name_offset,
		 ( (lnk_network_share_information_t *) location_information_value_data )->network_share_name_offset );

#if defined( HAVE_VERBOSE_OUTPUT )
		libnotify_verbose_printf(
		 "%s: network share information size\t\t\t: %" PRIu32 "\n",
		 function,
		 value_size );

		endian_little_convert_32bit(
		 test,
		 ( (lnk_network_share_information_t *) location_information_value_data )->network_share_type );

		libnotify_verbose_printf(
		 "%s: network share information network share type\t\t: 0x%08" PRIx32 "\n",
		 function,
		 test );

		libnotify_verbose_printf(
		 "%s: network share information network share name offset\t: %" PRIu32 "\n",
		 function,
		 network_share_name_offset );

		libnotify_verbose_printf(
		 "%s: network share information network share unknown:\n",
		 function );
		libnotify_verbose_print_data(
		 ( (lnk_network_share_information_t *) location_information_value_data )->unknown,
		 8 );
#endif
		if( network_share_name_offset > value_size )
		{
			liberror_error_set(
			 error,
			 LIBERROR_ERROR_DOMAIN_RUNTIME,
			 LIBERROR_RUNTIME_ERROR_VALUE_OUT_OF_RANGE,
			 "%s: network share name offset exceeds network share information data.",
			 function );

			memory_free(
			 location_information_data );

			return( -1 );
		}
		location_information_value_data = &( location_information_value_data[ network_share_name_offset ] );

		value_size = 0;

		while( location_information_value_data[ value_size ] != 0 )
		{
			value_size++;
		}
		value_size++;

#if defined( HAVE_DEBUG_OUTPUT )
		libnotify_verbose_printf(
		 "%s: network share information network share name size\t: %" PRIu32 "\n",
		 function,
		 value_size );
		libnotify_verbose_printf(
		 "%s: network share information network share name data:\n",
		 function );
		libnotify_verbose_print_data(
		 location_information_value_data,
		 value_size );
#endif
	}
	if( path_remainder_offset > 0 )
	{
		if( path_remainder_offset <= 4 )
		{
			liberror_error_set(
			 error,
			 LIBERROR_ERROR_DOMAIN_RUNTIME,
			 LIBERROR_RUNTIME_ERROR_VALUE_OUT_OF_RANGE,
			 "%s: path remainder information offset exceeds location information data.",
			 function );

			memory_free(
			 location_information_data );

			return( -1 );
		}
		path_remainder_offset -= 4;

		if( path_remainder_offset > location_information_size )
		{
			liberror_error_set(
			 error,
			 LIBERROR_ERROR_DOMAIN_RUNTIME,
			 LIBERROR_RUNTIME_ERROR_VALUE_OUT_OF_RANGE,
			 "%s: path remainder offset exceeds location information data.",
			 function );

			memory_free(
			 location_information_data );

			return( -1 );
		}
		location_information_value_data = &( location_information_data[ path_remainder_offset ] );

		value_size = 0;

		while( location_information_value_data[ value_size ] != 0 )
		{
			value_size++;
		}
		value_size++;

#if defined( HAVE_DEBUG_OUTPUT )
		libnotify_verbose_printf(
		 "%s: path remainder size\t: %" PRIu32 "\n",
		 function,
		 value_size );
		libnotify_verbose_printf(
		 "%s: path remainder data:\n",
		 function );
		libnotify_verbose_print_data(
		 location_information_value_data,
		 value_size );
#endif
	}

	memory_free(
	 location_information_data );

#if defined( HAVE_VERBOSE_OUTPUT )
	libnotify_verbose_printf(
	 "\n" );
#endif

	return( read_count + 4 );
}

