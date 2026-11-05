/*
 * OSS-Fuzz target for liblnk file type
 *
 * Copyright (C) 2009-2026, Joachim Metz <joachim.metz@gmail.com>
 *
 * Refer to AUTHORS for acknowledgements.
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU Lesser General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU Lesser General Public License
 * along with this program.  If not, see <https://www.gnu.org/licenses/>.
 */

#include <stddef.h>
#include <stdint.h>
#include <stdlib.h>

/* Note that some of the OSS-Fuzz engines use C++
 */
extern "C" {

#include "ossfuzz_libbfio.h"
#include "ossfuzz_liblnk.h"

#if !defined( LIBLNK_HAVE_BFIO )

/* Opens a file using a Basic File IO (bfio) handle
 * Returns 1 if successful or -1 on error
 */
LIBLNK_EXTERN \
int liblnk_file_open_file_io_handle(
     liblnk_file_t *file,
     libbfio_handle_t *file_io_handle,
     int access_flags,
     liblnk_error_t **error );

/* Determines if a file contains a LNK file signature using a Basic File IO (bfio) handle
 * Returns 1 if true, 0 if not or -1 on error
 */
LIBLNK_EXTERN \
int liblnk_check_file_signature_file_io_handle(
     libbfio_handle_t *file_io_handle,
     liblnk_error_t **error );

#endif /* !defined( LIBLNK_HAVE_BFIO ) */

/* The deprecated declarations are ignored
 * so that the deprecated functions can be exercised
 */
#if defined( __clang__ )
#pragma clang diagnostic push
#pragma clang diagnostic ignored "-Wdeprecated-declarations"
#elif defined( __GNUC__ )
#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wdeprecated-declarations"
#endif

/* Used to limit the amount of memory the fuzzer will allocate
 */
#define MAXIMUM_ALLOCATION_SIZE	( 8 * 1024 * 1024 )

#define NUMBER_OF_CODEPAGES	16

/* The codepages supported by liblnk_file_set_ascii_codepage
 * The value 0 represents an unsupported codepage
 * which is used to exercise the error path
 */
static const int codepages[ NUMBER_OF_CODEPAGES ] = {
	0,
	LIBLNK_CODEPAGE_WINDOWS_874,
	LIBLNK_CODEPAGE_WINDOWS_932,
	LIBLNK_CODEPAGE_WINDOWS_936,
	LIBLNK_CODEPAGE_WINDOWS_949,
	LIBLNK_CODEPAGE_WINDOWS_950,
	LIBLNK_CODEPAGE_WINDOWS_1250,
	LIBLNK_CODEPAGE_WINDOWS_1251,
	LIBLNK_CODEPAGE_WINDOWS_1252,
	LIBLNK_CODEPAGE_WINDOWS_1253,
	LIBLNK_CODEPAGE_WINDOWS_1254,
	LIBLNK_CODEPAGE_WINDOWS_1255,
	LIBLNK_CODEPAGE_WINDOWS_1256,
	LIBLNK_CODEPAGE_WINDOWS_1257,
	LIBLNK_CODEPAGE_WINDOWS_1258,
	LIBLNK_CODEPAGE_ASCII
};

/* Function pointer type definitions
 */
typedef int (*liblnk_file_utf8_string_size_getter_t)(
               liblnk_file_t *file,
               size_t *utf8_string_size,
               liblnk_error_t **error );

typedef int (*liblnk_file_utf8_string_getter_t)(
               liblnk_file_t *file,
               uint8_t *utf8_string,
               size_t utf8_string_size,
               liblnk_error_t **error );

typedef int (*liblnk_file_utf16_string_size_getter_t)(
               liblnk_file_t *file,
               size_t *utf16_string_size,
               liblnk_error_t **error );

typedef int (*liblnk_file_utf16_string_getter_t)(
               liblnk_file_t *file,
               uint16_t *utf16_string,
               size_t utf16_string_size,
               liblnk_error_t **error );

typedef int (*liblnk_data_block_utf8_string_size_getter_t)(
               liblnk_data_block_t *data_block,
               size_t *utf8_string_size,
               liblnk_error_t **error );

typedef int (*liblnk_data_block_utf8_string_getter_t)(
               liblnk_data_block_t *data_block,
               uint8_t *utf8_string,
               size_t utf8_string_size,
               liblnk_error_t **error );

typedef int (*liblnk_data_block_utf16_string_size_getter_t)(
               liblnk_data_block_t *data_block,
               size_t *utf16_string_size,
               liblnk_error_t **error );

typedef int (*liblnk_data_block_utf16_string_getter_t)(
               liblnk_data_block_t *data_block,
               uint16_t *utf16_string,
               size_t utf16_string_size,
               liblnk_error_t **error );

typedef int (*liblnk_file_guid_getter_t)(
               liblnk_file_t *file,
               uint8_t *guid_data,
               size_t guid_data_size,
               liblnk_error_t **error );

/* Retrieves the UTF-8 encoded string from a file
 * using a pair of getter functions
 */
void fuzzer_file_fetch_utf8_string(
      liblnk_file_utf8_string_size_getter_t get_utf8_string_size,
      liblnk_file_utf8_string_getter_t get_utf8_string,
      liblnk_file_t *file )
{
	uint8_t *utf8_string    = NULL;
	size_t utf8_string_size = 0;

	if( get_utf8_string_size(
	     file,
	     &utf8_string_size,
	     NULL ) != 1 )
	{
		return;
	}
	if( ( utf8_string_size == 0 )
	 || ( utf8_string_size > MAXIMUM_ALLOCATION_SIZE ) )
	{
		return;
	}
	utf8_string = (uint8_t *) malloc( utf8_string_size );

	if( utf8_string == NULL )
	{
		return;
	}
	get_utf8_string(
	 file,
	 utf8_string,
	 utf8_string_size,
	 NULL );

	free( utf8_string );
}

/* Retrieves the UTF-16 encoded string from a file
 * using a pair of getter functions
 */
void fuzzer_file_fetch_utf16_string(
      liblnk_file_utf16_string_size_getter_t get_utf16_string_size,
      liblnk_file_utf16_string_getter_t get_utf16_string,
      liblnk_file_t *file )
{
	uint16_t *utf16_string   = NULL;
	size_t utf16_string_size = 0;

	if( get_utf16_string_size(
	     file,
	     &utf16_string_size,
	     NULL ) != 1 )
	{
		return;
	}
	if( ( utf16_string_size == 0 )
	 || ( utf16_string_size > ( MAXIMUM_ALLOCATION_SIZE / sizeof( uint16_t ) ) ) )
	{
		return;
	}
	utf16_string = (uint16_t *) malloc( utf16_string_size * sizeof( uint16_t ) );

	if( utf16_string == NULL )
	{
		return;
	}
	get_utf16_string(
	 file,
	 utf16_string,
	 utf16_string_size,
	 NULL );

	free( utf16_string );
}

/* Retrieves the UTF-8 encoded string from a data block
 * using a pair of getter functions
 */
void fuzzer_data_block_fetch_utf8_string(
      liblnk_data_block_utf8_string_size_getter_t get_utf8_string_size,
      liblnk_data_block_utf8_string_getter_t get_utf8_string,
      liblnk_data_block_t *data_block )
{
	uint8_t *utf8_string    = NULL;
	size_t utf8_string_size = 0;

	if( get_utf8_string_size(
	     data_block,
	     &utf8_string_size,
	     NULL ) != 1 )
	{
		return;
	}
	if( ( utf8_string_size == 0 )
	 || ( utf8_string_size > MAXIMUM_ALLOCATION_SIZE ) )
	{
		return;
	}
	utf8_string = (uint8_t *) malloc( utf8_string_size );

	if( utf8_string == NULL )
	{
		return;
	}
	get_utf8_string(
	 data_block,
	 utf8_string,
	 utf8_string_size,
	 NULL );

	free( utf8_string );
}

/* Retrieves the UTF-16 encoded string from a data block
 * using a pair of getter functions
 */
void fuzzer_data_block_fetch_utf16_string(
             liblnk_data_block_utf16_string_size_getter_t get_utf16_string_size,
             liblnk_data_block_utf16_string_getter_t get_utf16_string,
             liblnk_data_block_t *data_block )
{
	uint16_t *utf16_string   = NULL;
	size_t utf16_string_size = 0;

	if( get_utf16_string_size(
	     data_block,
	     &utf16_string_size,
	     NULL ) != 1 )
	{
		return;
	}
	if( ( utf16_string_size == 0 )
	 || ( utf16_string_size > ( MAXIMUM_ALLOCATION_SIZE / sizeof( uint16_t ) ) ) )
	{
		return;
	}
	utf16_string = (uint16_t *) malloc( utf16_string_size * sizeof( uint16_t ) );

	if( utf16_string == NULL )
	{
		return;
	}
	get_utf16_string(
	 data_block,
	 utf16_string,
	 utf16_string_size,
	 NULL );

	free( utf16_string );
}

/* Retrieves the GUID (identifier) from a file
 * using a getter function
 */
void fuzzer_file_fetch_guid(
             liblnk_file_guid_getter_t get_guid,
             liblnk_file_t *file )
{
	uint8_t guid_data[ 16 ] = { 0 };

	get_guid(
	 file,
	 guid_data,
	 sizeof( guid_data ),
	 NULL );
}

/* Exercises the getter functions of a data block
 */
void fuzzer_data_block_exercise_getters(
             liblnk_data_block_t *data_block )
{
	uint8_t guid_data[ 16 ] = { 0 };
	uint8_t *data           = NULL;
	size_t data_size        = 0;
	uint32_t signature      = 0;
	int result              = 0;

	if( liblnk_data_block_get_signature(
	     data_block,
	     &signature,
	     NULL ) != 1 )
	{
		return;
	}
	switch( signature )
	{
		case LIBLNK_DATA_BLOCK_SIGNATURE_ENVIRONMENT_VARIABLES_LOCATION:
		case LIBLNK_DATA_BLOCK_SIGNATURE_DARWIN_PROPERTIES:
		case LIBLNK_DATA_BLOCK_SIGNATURE_ICON_LOCATION:
			fuzzer_data_block_fetch_utf8_string(
			 liblnk_strings_data_block_get_utf8_string_size,
			 liblnk_strings_data_block_get_utf8_string,
			 data_block );

			fuzzer_data_block_fetch_utf16_string(
			 liblnk_strings_data_block_get_utf16_string_size,
			 liblnk_strings_data_block_get_utf16_string,
			 data_block );

			fuzzer_data_block_fetch_utf8_string(
			 liblnk_strings_data_block_get_utf8_path_string_size,
			 liblnk_strings_data_block_get_utf8_path_string,
			 data_block );

			fuzzer_data_block_fetch_utf16_string(
			 liblnk_strings_data_block_get_utf16_path_string_size,
			 liblnk_strings_data_block_get_utf16_path_string,
			 data_block );

			liblnk_distributed_link_tracking_data_block_get_utf8_machine_identifier_size(
			 data_block,
			 NULL,
			 NULL );

			break;

		case LIBLNK_DATA_BLOCK_SIGNATURE_DISTRIBUTED_LINK_TRACKER_PROPERTIES:
			fuzzer_data_block_fetch_utf8_string(
			 liblnk_distributed_link_tracking_data_block_get_utf8_machine_identifier_size,
			 liblnk_distributed_link_tracking_data_block_get_utf8_machine_identifier,
			 data_block );

			fuzzer_data_block_fetch_utf16_string(
			 liblnk_distributed_link_tracking_data_block_get_utf16_machine_identifier_size,
			 liblnk_distributed_link_tracking_data_block_get_utf16_machine_identifier,
			 data_block );

			liblnk_distributed_link_tracking_data_block_get_droid_volume_identifier(
			 data_block,
			 guid_data,
			 sizeof( guid_data ),
			 NULL );

			liblnk_distributed_link_tracking_data_block_get_droid_file_identifier(
			 data_block,
			 guid_data,
			 sizeof( guid_data ),
			 NULL );

			liblnk_distributed_link_tracking_data_block_get_birth_droid_volume_identifier(
			 data_block,
			 guid_data,
			 sizeof( guid_data ),
			 NULL );

			liblnk_distributed_link_tracking_data_block_get_birth_droid_file_identifier(
			 data_block,
			 guid_data,
			 sizeof( guid_data ),
			 NULL );

			liblnk_strings_data_block_get_utf8_string_size(
			 data_block,
			 NULL,
			 NULL );

			break;

		default:
			/* Retrieves the raw data of the data block
			 */
			result = liblnk_data_block_get_data_size(
			          data_block,
			          &data_size,
			          NULL );

			if( ( result == 1 )
			 && ( data_size <= MAXIMUM_ALLOCATION_SIZE ) )
			{
				data = (uint8_t *) malloc(
				                    data_size < 1 ? 1 : data_size );

				if( data != NULL )
				{
					liblnk_data_block_copy_data(
					 data_block,
					 data,
					 data_size,
					 NULL );
					free( data );
				}
			}
			liblnk_strings_data_block_get_utf8_string_size(
			 data_block,
			 NULL,
			 NULL );

			liblnk_distributed_link_tracking_data_block_get_utf8_machine_identifier_size(
			 data_block,
			 NULL,
			 NULL );

			break;
	}
}

/* Exercises the getter functions of a file
 */
void fuzzer_file_exercise_getters(
             liblnk_file_t *file )
{
	liblnk_data_block_t *data_block = NULL;
	uint8_t *data                   = NULL;
	uint16_t hot_key_value          = 0;
	uint32_t value32                = 0;
	uint64_t value64                = 0;
	size_t data_size                = 0;
	int ascii_codepage              = 0;
	int number_of_data_blocks       = 0;
	int data_block_index            = 0;
	int result                      = 0;

	liblnk_file_get_ascii_codepage(
	 file,
	 &ascii_codepage,
	 NULL );

	liblnk_file_get_data_flags(
	 file,
	 &( value32 ),
	 NULL );

	liblnk_file_get_data_size(
	 file,
	 &( value64 ),
	 NULL );

	liblnk_file_is_corrupted(
	 file,
	 NULL );

	liblnk_file_link_refers_to_file(
	 file,
	 NULL );

	liblnk_file_get_file_creation_time(
	 file,
	 &( value64 ),
	 NULL );

	liblnk_file_get_file_modification_time(
	 file,
	 &( value64 ),
	 NULL );

	liblnk_file_get_file_access_time(
	 file,
	 &( value64 ),
	 NULL );

	liblnk_file_get_file_size(
	 file,
	 &( value32 ),
	 NULL );

	liblnk_file_get_icon_index(
	 file,
	 &( value32 ),
	 NULL );

	liblnk_file_get_show_window_value(
	 file,
	 &( value32 ),
	 NULL );

	liblnk_file_get_hot_key_value(
	 file,
	 &( hot_key_value ),
	 NULL );

	liblnk_file_get_file_attribute_flags(
	 file,
	 &( value32 ),
	 NULL );

	liblnk_file_get_drive_type(
	 file,
	 &( value32 ),
	 NULL );

	liblnk_file_get_drive_serial_number(
	 file,
	 &( value32 ),
	 NULL );

	fuzzer_file_fetch_utf8_string(
	 liblnk_file_get_utf8_volume_label_size,
	 liblnk_file_get_utf8_volume_label,
	 file );

	fuzzer_file_fetch_utf16_string(
	 liblnk_file_get_utf16_volume_label_size,
	 liblnk_file_get_utf16_volume_label,
	 file );

	fuzzer_file_fetch_utf8_string(
	 liblnk_file_get_utf8_local_path_size,
	 liblnk_file_get_utf8_local_path,
	 file );

	fuzzer_file_fetch_utf16_string(
	 liblnk_file_get_utf16_local_path_size,
	 liblnk_file_get_utf16_local_path,
	 file );

	fuzzer_file_fetch_utf8_string(
	 liblnk_file_get_utf8_network_path_size,
	 liblnk_file_get_utf8_network_path,
	 file );

	fuzzer_file_fetch_utf16_string(
	 liblnk_file_get_utf16_network_path_size,
	 liblnk_file_get_utf16_network_path,
	 file );

	fuzzer_file_fetch_utf8_string(
	 liblnk_file_get_utf8_description_size,
	 liblnk_file_get_utf8_description,
	 file );

	fuzzer_file_fetch_utf16_string(
	 liblnk_file_get_utf16_description_size,
	 liblnk_file_get_utf16_description,
	 file );

	fuzzer_file_fetch_utf8_string(
	 liblnk_file_get_utf8_relative_path_size,
	 liblnk_file_get_utf8_relative_path,
	 file );

	fuzzer_file_fetch_utf16_string(
	 liblnk_file_get_utf16_relative_path_size,
	 liblnk_file_get_utf16_relative_path,
	 file );

	fuzzer_file_fetch_utf8_string(
	 liblnk_file_get_utf8_working_directory_size,
	 liblnk_file_get_utf8_working_directory,
	 file );

	fuzzer_file_fetch_utf16_string(
	 liblnk_file_get_utf16_working_directory_size,
	 liblnk_file_get_utf16_working_directory,
	 file );

	fuzzer_file_fetch_utf8_string(
	 liblnk_file_get_utf8_command_line_arguments_size,
	 liblnk_file_get_utf8_command_line_arguments,
	 file );

	fuzzer_file_fetch_utf16_string(
	 liblnk_file_get_utf16_command_line_arguments_size,
	 liblnk_file_get_utf16_command_line_arguments,
	 file );

	fuzzer_file_fetch_utf8_string(
	 liblnk_file_get_utf8_icon_location_size,
	 liblnk_file_get_utf8_icon_location,
	 file );

	fuzzer_file_fetch_utf16_string(
	 liblnk_file_get_utf16_icon_location_size,
	 liblnk_file_get_utf16_icon_location,
	 file );

	fuzzer_file_fetch_utf8_string(
	 liblnk_file_get_utf8_environment_variables_location_size,
	 liblnk_file_get_utf8_environment_variables_location,
	 file );

	fuzzer_file_fetch_utf16_string(
	 liblnk_file_get_utf16_environment_variables_location_size,
	 liblnk_file_get_utf16_environment_variables_location,
	 file );

	fuzzer_file_fetch_utf8_string(
	 liblnk_file_get_utf8_machine_identifier_size,
	 liblnk_file_get_utf8_machine_identifier,
	 file );

	fuzzer_file_fetch_utf16_string(
	 liblnk_file_get_utf16_machine_identifier_size,
	 liblnk_file_get_utf16_machine_identifier,
	 file );

	fuzzer_file_fetch_guid(
	 liblnk_file_get_droid_volume_identifier,
	 file );

	fuzzer_file_fetch_guid(
	 liblnk_file_get_droid_file_identifier,
	 file );

	fuzzer_file_fetch_guid(
	 liblnk_file_get_birth_droid_volume_identifier,
	 file );

	fuzzer_file_fetch_guid(
	 liblnk_file_get_birth_droid_file_identifier,
	 file );

	liblnk_file_has_distributed_link_tracking_data(
	 file,
	 NULL );

	/* Retrieves the link target identifier data
	 */
	data_size = 0;

	result = liblnk_file_get_link_target_identifier_data_size(
	          file,
	          &data_size,
	          NULL );

	if( ( result == 1 )
	 && ( data_size <= MAXIMUM_ALLOCATION_SIZE ) )
	{
		data = (uint8_t *) malloc(
		                    data_size < 1 ? 1 : data_size );

		if( data != NULL )
		{
			liblnk_file_copy_link_target_identifier_data(
			 file,
			 data,
			 data_size,
			 NULL );
			free( data );
		}
	}
	result = liblnk_file_get_number_of_data_blocks(
	          file,
	          &( number_of_data_blocks ),
	          NULL );

	if( ( result == 1 )
	 && ( number_of_data_blocks > 0 ) )
	{
		while( data_block_index < number_of_data_blocks )
		{
			result = liblnk_file_get_data_block_by_index(
				  file,
				  data_block_index,
				  &data_block,
				  NULL );

			if( ( result == 1 )
			 && ( data_block != NULL ) )
			{
				fuzzer_data_block_exercise_getters(
				 data_block );
				liblnk_data_block_free(
				 &data_block,
				 NULL );
			}
			data_block_index += 1;
		}
	}
}

/* Exercises the invalid output getter functions of a file
 */
void fuzzer_file_exercise_invalid_output(
             liblnk_file_t *file )
{
	liblnk_file_utf8_string_size_getter_t get_utf8_string_size = NULL;

	liblnk_file_get_ascii_codepage( file, NULL, NULL );
	liblnk_file_get_data_flags( file, NULL, NULL );
	liblnk_file_get_data_size( file, NULL, NULL );
	liblnk_file_get_file_creation_time( file, NULL, NULL );
	liblnk_file_get_file_modification_time( file, NULL, NULL );
	liblnk_file_get_file_access_time( file, NULL, NULL );
	liblnk_file_get_file_size( file, NULL, NULL );
	liblnk_file_get_icon_index( file, NULL, NULL );
	liblnk_file_get_show_window_value( file, NULL, NULL );
	liblnk_file_get_hot_key_value( file, NULL, NULL );
	liblnk_file_get_file_attribute_flags( file, NULL, NULL );
	liblnk_file_get_drive_type( file, NULL, NULL );
	liblnk_file_get_drive_serial_number( file, NULL, NULL );
	liblnk_file_get_utf8_volume_label_size( file, NULL, NULL );
	liblnk_file_get_utf16_local_path_size( file, NULL, NULL );
	liblnk_file_get_utf8_description_size( file, NULL, NULL );

	get_utf8_string_size = liblnk_file_get_utf8_environment_variables_location_size;
	get_utf8_string_size(
	 file,
	 NULL,
	 NULL );

	get_utf8_string_size = liblnk_file_get_utf8_machine_identifier_size;

	get_utf8_string_size(
	 file,
	 NULL,
	 NULL );

	liblnk_file_get_link_target_identifier_data_size( file, NULL, NULL );

	liblnk_file_get_number_of_data_blocks( file, NULL, NULL );

	liblnk_file_get_data_block_by_index( file, 0, NULL, NULL );
}

int LLVMFuzzerTestOneInput(
     const uint8_t *data,
     size_t size )
{
	libbfio_handle_t *file_io_handle = NULL;
	liblnk_file_t *file              = NULL;
	int codepage                     = 0;
	int global_codepage              = 0;
	int result                       = 0;

	/* Exercises the library support functions
	 */
	liblnk_get_version();
	liblnk_get_access_flags_read();

	liblnk_get_codepage(
	 &global_codepage,
	 NULL );
	liblnk_set_codepage(
	 1252,
	 NULL );

	/* Exercises the unsupported codepage error branch
	 */
	liblnk_set_codepage(
	 1234,
	 NULL );

	if( libbfio_memory_range_initialize(
	     &file_io_handle,
	     NULL ) != 1 )
	{
		return( 0 );
	}
	if( libbfio_memory_range_set(
	     file_io_handle,
	     (uint8_t *) data,
	     size,
	     NULL ) != 1 )
	{
		goto on_error_libbfio;
	}
	if( liblnk_file_initialize(
	     &file,
	     NULL ) != 1 )
	{
		goto on_error_libbfio;
	}
	liblnk_file_close(
	 file,
	 NULL );

	liblnk_file_signal_abort(
	 file,
	 NULL );

	liblnk_file_open_file_io_handle(
	 file,
	 NULL,
	 LIBLNK_OPEN_READ,
	 NULL );

	liblnk_file_open_file_io_handle(
	 file,
	 file_io_handle,
	 0,
	 NULL );

	liblnk_file_open_file_io_handle(
	 file,
	 file_io_handle,
	 LIBLNK_OPEN_READ_WRITE,
	 NULL );

	liblnk_check_file_signature_file_io_handle(
	 file_io_handle,
	 NULL );

	fuzzer_file_exercise_getters(
	 file );

	fuzzer_file_exercise_invalid_output(
	 file );

	if( size > 0 )
	{
		codepage = codepages[ (int) ( data[ 0 ] % NUMBER_OF_CODEPAGES ) ];
	}
	else
	{
		codepage = codepages[ 1 ];
	}
	if( liblnk_file_set_ascii_codepage(
	     file,
	     codepage,
	     NULL ) != 1 )
	{
		codepage = LIBLNK_CODEPAGE_WINDOWS_1252;
	}
	result = liblnk_file_open_file_io_handle(
	          file,
	          file_io_handle,
	          LIBLNK_OPEN_READ,
	          NULL );

	if( result == 1 )
	{
		liblnk_file_open_file_io_handle(
		 file,
		 file_io_handle,
		 LIBLNK_OPEN_READ,
		 NULL );

		fuzzer_file_exercise_getters(
		 file );

		fuzzer_file_exercise_invalid_output(
		 file );

		liblnk_file_close(
		 file,
		 NULL );
	}
	if( size > 1 )
	{
		codepage = codepages[ (int) ( data[ 1 ] % NUMBER_OF_CODEPAGES ) ];

		if( liblnk_file_set_ascii_codepage(
		     file,
		     codepage,
		     NULL ) != 1 )
		{
			codepage = LIBLNK_CODEPAGE_WINDOWS_1252;
		}
	}
	result = liblnk_file_open_file_io_handle(
	          file,
	          file_io_handle,
	          LIBLNK_OPEN_READ,
	          NULL );

	if( result == 1 )
	{
		fuzzer_file_exercise_getters(
		 file );
		fuzzer_file_exercise_invalid_output(
		 file );
	}
	liblnk_file_free(
	 &file,
	 NULL );

on_error_libbfio:
	libbfio_handle_free(
	 &file_io_handle,
	 NULL );

	return( 0 );
}

#if defined( __clang__ )
#pragma clang diagnostic pop
#elif defined( __GNUC__ )
#pragma GCC diagnostic pop
#endif

} /* extern "C" */
