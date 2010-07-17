/*
 * Input/Output (IO) handle
 *
 * Copyright (c) 2009-2010, Joachim Metz <jbmetz@users.sourceforge.net>
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

#include <libcstring.h>
#include <liberror.h>
#include <libnotify.h>

#include "liblnk_codepage.h"
#include "liblnk_debug.h"
#include "liblnk_definitions.h"
#include "liblnk_file_information.h"
#include "liblnk_io_handle.h"
#include "liblnk_libbfio.h"
#include "liblnk_libfdatetime.h"
#include "liblnk_libfguid.h"
#include "liblnk_libfwsi.h"
#include "liblnk_libuna.h"

#include "lnk_data_blocks.h"
#include "lnk_file_header.h"

const uint8_t lnk_file_class_identifier[ 16 ] = \
	{ 0x01, 0x14, 0x02, 0x00, 0x00, 0x00, 0x00, 0x00, 0xc0, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x46 };

/* Initialize an IO handle
 * Make sure the value io_handle is pointing to is set to NULL
 * Returns 1 if successful or -1 on error
 */
int liblnk_io_handle_initialize(
     liblnk_io_handle_t **io_handle,
     liberror_error_t **error )
{
	static char *function = "liblnk_io_handle_initialize";

	if( io_handle == NULL )
	{
		liberror_error_set(
		 error,
		 LIBERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid IO handle.",
		 function );

		return( -1 );
	}
	if( *io_handle == NULL )
	{
		*io_handle = (liblnk_io_handle_t *) memory_allocate(
		                                     sizeof( liblnk_io_handle_t ) );

		if( *io_handle == NULL )
		{
			liberror_error_set(
			 error,
			 LIBERROR_ERROR_DOMAIN_MEMORY,
			 LIBERROR_MEMORY_ERROR_INSUFFICIENT,
			 "%s: unable to create IO handle.",
			 function );

			return( -1 );
		}
		if( memory_set(
		     *io_handle,
		     0,
		     sizeof( liblnk_io_handle_t ) ) == NULL )
		{
			liberror_error_set(
			 error,
			 LIBERROR_ERROR_DOMAIN_MEMORY,
			 LIBERROR_MEMORY_ERROR_SET_FAILED,
			 "%s: unable to clear file.",
			 function );

			memory_free(
			 *io_handle );

			*io_handle = NULL;

			return( -1 );
		}
		( *io_handle )->ascii_codepage = LIBLNK_CODEPAGE_WINDOWS_1252;
	}
	return( 1 );
}

/* Frees an exisisting IO handle
 * Returns 1 if successful or -1 on error
 */
int liblnk_io_handle_free(
     liblnk_io_handle_t **io_handle,
     liberror_error_t **error )
{
	static char *function = "liblnk_io_handle_free";

	if( io_handle == NULL )
	{
		liberror_error_set(
		 error,
		 LIBERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid IO handle.",
		 function );

		return( -1 );
	}
	if( *io_handle != NULL )
	{
		memory_free(
		 *io_handle );

		*io_handle = NULL;
	}
	return( 1 );
}

/* Reads the file header
 * Returns the number of bytes read if successful or -1 on error
 */
ssize_t liblnk_io_handle_read_file_header(
         liblnk_io_handle_t *io_handle,
         libbfio_handle_t *file_io_handle,
         uint8_t *class_identifier,
         size_t class_identifier_size,
         liblnk_file_information_t *file_information,
         liberror_error_t **error )
{
	lnk_file_header_t file_header;

	static char *function             = "liblnk_io_handle_read_file_header";
	ssize_t read_count                = 0;
	uint32_t header_size              = 0;

#if defined( HAVE_VERBOSE_OUTPUT )
	libcstring_system_character_t filetime_string[ 24 ];
	libcstring_system_character_t guid_string[ LIBFGUID_IDENTIFIER_STRING_SIZE ];

	libfdatetime_filetime_t *filetime = NULL;
	libfguid_identifier_t *guid       = NULL;
	uint32_t value_32bit              = 0;
	uint16_t value_16bit              = 0;
	int result                        = 0;
#endif

	if( io_handle == NULL )
	{
		liberror_error_set(
		 error,
		 LIBERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid IO handle.",
		 function );

		return( -1 );
	}
	if( class_identifier == NULL )
	{
		liberror_error_set(
		 error,
		 LIBERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid class identifier.",
		 function );

		return( -1 );
	}
	if( class_identifier_size < 16 )
	{
		liberror_error_set(
		 error,
		 LIBERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBERROR_ARGUMENT_ERROR_VALUE_TOO_SMALL,
		 "%s: class identifier too small.",
		 function );

		return( -1 );
	}
	if( class_identifier_size > (size_t) SSIZE_MAX )
	{
		liberror_error_set(
		 error,
		 LIBERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBERROR_ARGUMENT_ERROR_VALUE_EXCEEDS_MAXIMUM,
		 "%s: class identifier size value exceeds maximum.",
		 function );

		return( -1 );
	}
	if( file_information == NULL )
	{
		liberror_error_set(
		 error,
		 LIBERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid file information.",
		 function );

		return( -1 );
	}
	if( libbfio_handle_get_size(
	     file_io_handle,
	     &( io_handle->file_size ),
	     error ) != 1 )
	{
		liberror_error_set(
		 error,
		 LIBERROR_ERROR_DOMAIN_RUNTIME,
		 LIBERROR_RUNTIME_ERROR_GET_FAILED,
		 "%s: unable to retrieve file size.",
		 function );

		return( -1 );
	}
#if defined( HAVE_DEBUG_OUTPUT )
	if( libnotify_verbose != 0 )
	{
		libnotify_printf(
		 "%s: reading file header at offset: 0 (0x00000000)\n",
		 function );
	}
#endif
	if( libbfio_handle_seek_offset(
	     file_io_handle,
	     0,
	     SEEK_SET,
	     error ) == -1 )
	{
		liberror_error_set(
		 error,
		 LIBERROR_ERROR_DOMAIN_IO,
		 LIBERROR_IO_ERROR_SEEK_FAILED,
		 "%s: unable to seek file header offset: 0.",
		 function );

		return( -1 );
	}
	read_count = libbfio_handle_read(
	              file_io_handle,
	              (uint8_t *) &file_header,
	              sizeof( lnk_file_header_t ),
	              error );

	if( read_count != (ssize_t) sizeof( lnk_file_header_t ) )
	{
		liberror_error_set(
		 error,
		 LIBERROR_ERROR_DOMAIN_IO,
		 LIBERROR_IO_ERROR_READ_FAILED,
		 "%s: unable to read file header.",
		 function );

		return( -1 );
	}
#if defined( HAVE_DEBUG_OUTPUT )
	if( libnotify_verbose != 0 )
	{
		libnotify_printf(
		 "%s: file header:\n",
		 function );
		libnotify_print_data(
		 (uint8_t *) &file_header,
		 sizeof( lnk_file_header_t ) );
	}
#endif

	byte_stream_copy_to_uint32_little_endian(
	 file_header.header_size,
	 header_size );

	if( header_size != 0x4c )
	{
		liberror_error_set(
		 error,
		 LIBERROR_ERROR_DOMAIN_RUNTIME,
		 LIBERROR_RUNTIME_ERROR_UNSUPPORTED_VALUE,
		 "%s: unsupported header size: %" PRIu32 ".",
		 function,
		 header_size );

		return( -1 );
	}
	if( memory_compare(
	     file_header.class_identifier,
	     lnk_file_class_identifier,
	     16 ) != 0 )
	{
		liberror_error_set(
		 error,
		 LIBERROR_ERROR_DOMAIN_RUNTIME,
		 LIBERROR_RUNTIME_ERROR_UNSUPPORTED_VALUE,
		 "%s: unsupported file class identifier.",
		 function );

		return( -1 );
	}
	/* TODO is a libfguid version of the class identifier needed ? */
	if( memory_copy(
	     class_identifier,
	     file_header.class_identifier,
	     16 ) == NULL )
	{
		liberror_error_set(
		 error,
		 LIBERROR_ERROR_DOMAIN_MEMORY,
		 LIBERROR_MEMORY_ERROR_SET_FAILED,
		 "%s: unable to copy class identifier.",
		 function );

		return( -1 );
	}
	byte_stream_copy_to_uint32_little_endian(
	 file_header.data_flags,
	 io_handle->data_flags );
	byte_stream_copy_to_uint32_little_endian(
	 file_header.file_attribute_flags,
	 file_information->attribute_flags );

	byte_stream_copy_to_uint64_little_endian(
	 file_header.creation_time,
	 file_information->creation_time )
	byte_stream_copy_to_uint64_little_endian(
	 file_header.access_time,
	 file_information->access_time );
	byte_stream_copy_to_uint64_little_endian(
	 file_header.modification_time,
	 file_information->modification_time );

	byte_stream_copy_to_uint32_little_endian(
	 file_header.file_size,
	 file_information->size );

#if defined( HAVE_VERBOSE_OUTPUT )
	if( libnotify_verbose != 0 )
	{
		libnotify_printf(
		 "%s: header size\t\t\t: %" PRIu32 "\n",
		 function,
		 header_size );

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

			return( -1 );
		}
		if( libfguid_identifier_copy_from_byte_stream(
		     guid,
		     file_header.class_identifier,
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

			libfguid_identifier_free(
			 &guid,
			 NULL );

			return( -1 );
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

			libfguid_identifier_free(
			 &guid,
			 NULL );

			return( -1 );
		}
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

			return( -1 );
		}
		libnotify_printf(
		 "%s: class identifier\t\t: %" PRIs_LIBCSTRING_SYSTEM "\n",
		 function,
		 guid_string );

		libnotify_printf(
		 "%s: data flags\t\t\t: 0x%08" PRIx32 "\n",
		 function,
		 io_handle->data_flags );
		liblnk_debug_print_data_flags(
		 io_handle->data_flags );
		libnotify_printf(
		 "\n" );

		libnotify_printf(
		 "%s: file attribute flags\t\t: 0x%08" PRIx32 "\n",
		 function,
		 file_information->attribute_flags );
		liblnk_debug_print_file_attribute_flags(
		 file_information->attribute_flags );
		libnotify_printf(
		 "\n" );

		if( libfdatetime_filetime_initialize(
		     &filetime,
		     error ) != 1 )
		{
			liberror_error_set(
			 error,
			 LIBERROR_ERROR_DOMAIN_RUNTIME,
			 LIBERROR_RUNTIME_ERROR_INITIALIZE_FAILED,
			 "%s: unable to create filetime.",
			 function );

			return( -1 );
		}
		if( libfdatetime_filetime_copy_from_byte_stream(
		     filetime,
		     file_header.creation_time,
		     8,
		     LIBFDATETIME_ENDIAN_LITTLE,
		     error ) != 1 )
		{
			liberror_error_set(
			 error,
			 LIBERROR_ERROR_DOMAIN_RUNTIME,
			 LIBERROR_RUNTIME_ERROR_COPY_FAILED,
			 "%s: unable to copy byte stream to filetime.",
			 function );

			libfdatetime_filetime_free(
			 &filetime,
			 NULL );

			return( -1 );
		}
#if defined( LIBCSTRING_HAVE_WIDE_SYSTEM_CHARACTER )
		result = libfdatetime_filetime_copy_to_utf16_string(
			  filetime,
			  (uint16_t *) filetime_string,
			  24,
			  LIBFDATETIME_STRING_FORMAT_FLAG_DATE_TIME,
			  LIBFDATETIME_DATE_TIME_FORMAT_CTIME,
			  error );
#else
		result = libfdatetime_filetime_copy_to_utf8_string(
			  filetime,
			  (uint8_t *) filetime_string,
			  24,
			  LIBFDATETIME_STRING_FORMAT_FLAG_DATE_TIME,
			  LIBFDATETIME_DATE_TIME_FORMAT_CTIME,
			  error );
#endif
		if( result != 1 )
		{
			liberror_error_set(
			 error,
			 LIBERROR_ERROR_DOMAIN_RUNTIME,
			 LIBERROR_RUNTIME_ERROR_COPY_FAILED,
			 "%s: unable to copy filetime to string.",
			 function );

			libfdatetime_filetime_free(
			 &filetime,
			 NULL );

			return( -1 );
		}
		libnotify_printf(
		 "%s: creation time\t\t: %" PRIs_LIBCSTRING_SYSTEM " UTC\n",
		 function,
		 filetime_string );

		if( libfdatetime_filetime_copy_from_byte_stream(
		     filetime,
		     file_header.access_time,
		     8,
		     LIBFDATETIME_ENDIAN_LITTLE,
		     error ) != 1 )
		{
			liberror_error_set(
			 error,
			 LIBERROR_ERROR_DOMAIN_RUNTIME,
			 LIBERROR_RUNTIME_ERROR_COPY_FAILED,
			 "%s: unable to copy byte stream to filetime.",
			 function );

			libfdatetime_filetime_free(
			 &filetime,
			 NULL );

			return( -1 );
		}
#if defined( LIBCSTRING_HAVE_WIDE_SYSTEM_CHARACTER )
		result = libfdatetime_filetime_copy_to_utf16_string(
			  filetime,
			  (uint16_t *) filetime_string,
			  24,
			  LIBFDATETIME_STRING_FORMAT_FLAG_DATE_TIME,
			  LIBFDATETIME_DATE_TIME_FORMAT_CTIME,
			  error );
#else
		result = libfdatetime_filetime_copy_to_utf8_string(
			  filetime,
			  (uint8_t *) filetime_string,
			  24,
			  LIBFDATETIME_STRING_FORMAT_FLAG_DATE_TIME,
			  LIBFDATETIME_DATE_TIME_FORMAT_CTIME,
			  error );
#endif
		if( result != 1 )
		{
			liberror_error_set(
			 error,
			 LIBERROR_ERROR_DOMAIN_RUNTIME,
			 LIBERROR_RUNTIME_ERROR_COPY_FAILED,
			 "%s: unable to copy filetime to string.",
			 function );

			libfdatetime_filetime_free(
			 &filetime,
			 NULL );

			return( -1 );
		}
		libnotify_printf(
		 "%s: access time\t\t\t: %" PRIs_LIBCSTRING_SYSTEM " UTC\n",
		 function,
		 filetime_string );

		if( libfdatetime_filetime_copy_from_byte_stream(
		     filetime,
		     file_header.modification_time,
		     8,
		     LIBFDATETIME_ENDIAN_LITTLE,
		     error ) != 1 )
		{
			liberror_error_set(
			 error,
			 LIBERROR_ERROR_DOMAIN_RUNTIME,
			 LIBERROR_RUNTIME_ERROR_COPY_FAILED,
			 "%s: unable to copy byte stream to filetime.",
			 function );

			libfdatetime_filetime_free(
			 &filetime,
			 NULL );

			return( -1 );
		}
#if defined( LIBCSTRING_HAVE_WIDE_SYSTEM_CHARACTER )
		result = libfdatetime_filetime_copy_to_utf16_string(
			  filetime,
			  (uint16_t *) filetime_string,
			  24,
			  LIBFDATETIME_STRING_FORMAT_FLAG_DATE_TIME,
			  LIBFDATETIME_DATE_TIME_FORMAT_CTIME,
			  error );
#else
		result = libfdatetime_filetime_copy_to_utf8_string(
			  filetime,
			  (uint8_t *) filetime_string,
			  24,
			  LIBFDATETIME_STRING_FORMAT_FLAG_DATE_TIME,
			  LIBFDATETIME_DATE_TIME_FORMAT_CTIME,
			  error );
#endif
		if( result != 1 )
		{
			liberror_error_set(
			 error,
			 LIBERROR_ERROR_DOMAIN_RUNTIME,
			 LIBERROR_RUNTIME_ERROR_COPY_FAILED,
			 "%s: unable to copy filetime to string.",
			 function );

			libfdatetime_filetime_free(
			 &filetime,
			 NULL );

			return( -1 );
		}
		libnotify_printf(
		 "%s: modification time\t\t: %" PRIs_LIBCSTRING_SYSTEM " UTC\n",
		 function,
		 filetime_string );

		if( libfdatetime_filetime_free(
		     &filetime,
		     error ) != 1 )
		{
			liberror_error_set(
			 error,
			 LIBERROR_ERROR_DOMAIN_RUNTIME,
			 LIBERROR_RUNTIME_ERROR_FINALIZE_FAILED,
			 "%s: unable to free filetime.",
			 function );

			return( -1 );
		}
		libnotify_printf(
		 "%s: file size\t\t\t: %" PRIu32 " bytes\n",
		 function,
		 file_information->size );

		byte_stream_copy_to_uint32_little_endian(
		 file_header.icon_index,
		 value_32bit );
		libnotify_printf(
		 "%s: icon index\t\t\t: 0x%08" PRIx32 "\n",
		 function,
		 value_32bit );

		byte_stream_copy_to_uint32_little_endian(
		 file_header.show_window_value,
		 value_32bit );
		libnotify_printf(
		 "%s: show window value\t\t: 0x%08" PRIx32 "\n",
		 function,
		 value_32bit );

		byte_stream_copy_to_uint16_little_endian(
		 file_header.hot_key_value,
		 value_16bit );
		libnotify_printf(
		 "%s: hot key value\t\t: 0x%04" PRIx16 "\n",
		 function,
		 value_16bit );

		libnotify_printf(
		 "%s: reserved:\n",
		 function );
		libnotify_print_data(
		 (uint8_t *) file_header.reserved,
		 10 );

		libnotify_printf(
		 "\n" );
	}
#endif
	/* TODO compare file sizes */

	return( read_count );
}

/* Reads the (extra) data blocks
 * Returns the number of bytes read if successful or -1 on error
 */
ssize_t liblnk_io_handle_read_data_blocks(
         liblnk_io_handle_t *io_handle,
         libbfio_handle_t *file_io_handle,
         off64_t data_blocks_offset,
         liberror_error_t **error )
{
	uint8_t data_block_size_data[ 4 ];

	uint8_t *data_block_data                    = NULL;
	static char *function                       = "liblnk_io_handle_read_data_blocks";
	ssize_t read_count                          = 0;
	ssize_t total_read_count                    = 0;
	uint32_t data_block_size                    = 0;
	uint32_t data_block_signature               = 0;

#if defined( HAVE_DEBUG_OUTPUT )
	libcstring_system_character_t guid_string[ LIBFGUID_IDENTIFIER_STRING_SIZE ];

	libcstring_system_character_t *value_string = NULL;
	libfguid_identifier_t *guid                 = NULL;
	size_t value_string_size                    = 0;
	uint32_t value_32bit                        = 0;
	int result                                  = 0;
#endif

	if( io_handle == NULL )
	{
		liberror_error_set(
		 error,
		 LIBERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid IO handle.",
		 function );

		return( -1 );
	}
#if defined( HAVE_DEBUG_OUTPUT )
	if( libnotify_verbose != 0 )
	{
		libnotify_printf(
		 "%s: reading data blocks at offset: %" PRIi64 " (0x%08" PRIx64 ")\n",
		 function,
		 data_blocks_offset,
		 data_blocks_offset );
	}
#endif
	if( libbfio_handle_seek_offset(
	     file_io_handle,
	     data_blocks_offset,
	     SEEK_SET,
	     error ) == -1 )
	{
		liberror_error_set(
		 error,
		 LIBERROR_ERROR_DOMAIN_IO,
		 LIBERROR_IO_ERROR_SEEK_FAILED,
		 "%s: unable to seek data blocks offset: %" PRIi64 ".",
		 function,
		 data_blocks_offset );

		return( -1 );
	}
	while( data_blocks_offset < (off64_t) io_handle->file_size )
	{
		read_count = libbfio_handle_read(
			      file_io_handle,
			      data_block_size_data,
			      4,
			      error );

		if( read_count != (ssize_t) 4 )
		{
			liberror_error_set(
			 error,
			 LIBERROR_ERROR_DOMAIN_IO,
			 LIBERROR_IO_ERROR_READ_FAILED,
			 "%s: unable to read data block size.",
			 function );

			return( -1 );
		}
		data_blocks_offset += read_count;
		total_read_count   += read_count;

		byte_stream_copy_to_uint32_little_endian(
		 data_block_size_data,
		 data_block_size );

#if defined( HAVE_DEBUG_OUTPUT )
		if( libnotify_verbose != 0 )
		{
			libnotify_printf(
			 "%s: data block size\t\t\t\t\t\t: %" PRIu32 "\n",
			 function,
			 data_block_size );
		}
#endif
		if( data_block_size == 0 )
		{
			break;
		}
		if( data_block_size < 4 )
		{
			liberror_error_set(
			 error,
			 LIBERROR_ERROR_DOMAIN_RUNTIME,
			 LIBERROR_RUNTIME_ERROR_VALUE_OUT_OF_BOUNDS,
			 "%s: data block size too small.",
			 function );

			return( -1 );
		}
		data_block_size -= 4;

		if( ( data_blocks_offset + data_block_size ) > (off64_t) io_handle->file_size )
		{
			liberror_error_set(
			 error,
			 LIBERROR_ERROR_DOMAIN_RUNTIME,
			 LIBERROR_RUNTIME_ERROR_VALUE_OUT_OF_BOUNDS,
			 "%s: data block size exceeds file size.",
			 function );

			return( -1 );
		}
		data_block_data = (uint8_t *) memory_allocate(
					       sizeof( uint8_t ) * data_block_size );

		if( data_block_data == NULL )
		{
			liberror_error_set(
			 error,
			 LIBERROR_ERROR_DOMAIN_MEMORY,
			 LIBERROR_MEMORY_ERROR_INSUFFICIENT,
			 "%s: unable to create data block data.",
			 function );

			return( -1 );
		}
		read_count = libbfio_handle_read(
			      file_io_handle,
			      data_block_data,
			      data_block_size,
			      error );

		if( read_count != (ssize_t) data_block_size )
		{
			liberror_error_set(
			 error,
			 LIBERROR_ERROR_DOMAIN_IO,
			 LIBERROR_IO_ERROR_READ_FAILED,
			 "%s: unable to read data block data.",
			 function );

			memory_free(
			 data_block_data );

			return( -1 );
		}
		data_blocks_offset += read_count;
		total_read_count   += read_count;

#if defined( HAVE_DEBUG_OUTPUT )
		if( libnotify_verbose != 0 )
		{
			libnotify_printf(
			 "%s: data block data:\n",
			 function );
			libnotify_print_data(
			 data_block_data,
			 data_block_size );
		}
#endif
		byte_stream_copy_to_uint32_little_endian(
		 data_block_data,
		 data_block_signature );

#if defined( HAVE_DEBUG_OUTPUT )
		if( libnotify_verbose != 0 )
		{
			libnotify_printf(
			 "%s: data block signature\t\t\t\t\t\t: 0x%08" PRIx32 "\n",
			 function,
			 data_block_signature );
		}
#endif
#ifdef TODO
	if( ( io_handle->data_flags & LIBLNK_DATA_FLAG_HAS_METADATA_PROPERTY_STORE_DATA_BLOCK ) != 0 )
	{
	}
#endif
		switch( data_block_signature )
		{
			case LIBLNK_DATA_BLOCK_SIGNATURE_ENVIRONMENT_VARIABLES_LOCATION:
/* TODO add data block size check */
				if( ( io_handle->data_flags & LIBLNK_DATA_FLAG_HAS_ENVIRONMENT_VARIABLES_LOCATION_BLOCK ) != 0 )
				{
/* TODO notify that flag was not set */
				}
#if defined( HAVE_VERBOSE_OUTPUT )
				if( libnotify_verbose != 0 )
				{
					libnotify_printf(
					 "%s: environment variables location data:\n",
					 function );
					libnotify_print_data(
					 ( (lnk_data_block_environment_variables_location_t *) data_block_data )->environment_variables_location,
					 260 );

#if defined( LIBCSTRING_HAVE_WIDE_SYSTEM_CHARACTER )
					result = libuna_utf16_string_size_from_byte_stream(
						  ( (lnk_data_block_environment_variables_location_t *) data_block_data )->environment_variables_location,
						  260,
						  io_handle->ascii_codepage,
						  &value_string_size,
						  error );
#else
					result = libuna_utf8_string_size_from_byte_stream(
						  ( (lnk_data_block_environment_variables_location_t *) data_block_data )->environment_variables_location,
						  260,
						  io_handle->ascii_codepage,
						  &value_string_size,
						  error );
#endif
					if( result != 1 )
					{
						liberror_error_set(
						 error,
						 LIBERROR_ERROR_DOMAIN_RUNTIME,
						 LIBERROR_RUNTIME_ERROR_GET_FAILED,
						 "%s: unable to determine size of environment variables location string.",
						 function );

						return( -1 );
					}
					value_string = (libcstring_system_character_t *) memory_allocate(
					                                                  sizeof( libcstring_system_character_t ) * value_string_size );

					if( value_string == NULL )
					{
						liberror_error_set(
						 error,
						 LIBERROR_ERROR_DOMAIN_MEMORY,
						 LIBERROR_MEMORY_ERROR_INSUFFICIENT,
						 "%s: unable to create environment variables location string.",
						 function );

						return( -1 );
					}
#if defined( LIBCSTRING_HAVE_WIDE_SYSTEM_CHARACTER )
					result = libuna_utf16_string_copy_from_byte_stream(
						  (libuna_utf16_character_t *) value_string,
						  value_string_size,
						  ( (lnk_data_block_environment_variables_location_t *) data_block_data )->environment_variables_location,
						  260,
						  io_handle->ascii_codepage,
						  error );
#else
					result = libuna_utf8_string_copy_from_byte_stream(
						  (libuna_utf8_character_t *) value_string,
						  value_string_size,
						  ( (lnk_data_block_environment_variables_location_t *) data_block_data )->environment_variables_location,
						  260,
						  io_handle->ascii_codepage,
						  error );
#endif
					if( result != 1 )
					{
						liberror_error_set(
						 error,
						 LIBERROR_ERROR_DOMAIN_RUNTIME,
						 LIBERROR_RUNTIME_ERROR_SET_FAILED,
						 "%s: unable to set environment variables location string.",
						 function );

						memory_free(
						 value_string );

						return( -1 );
					}
					libnotify_printf(
					 "%s: environment variables location\t\t\t\t: %" PRIs_LIBCSTRING_SYSTEM "\n",
					 function,
					 value_string );

					memory_free(
					 value_string );

/* TODO print as string */
					libnotify_printf(
					 "%s: unicode environment variables location data:\n",
					 function );
					libnotify_print_data(
					 ( (lnk_data_block_environment_variables_location_t *) data_block_data )->unicode_environment_variables_location,
					 520 );

#if defined( LIBCSTRING_HAVE_WIDE_SYSTEM_CHARACTER )
					result = libuna_utf16_string_size_from_utf16_stream(
						  ( (lnk_data_block_environment_variables_location_t *) data_block_data )->unicode_environment_variables_location,
						  520,
						  LIBUNA_ENDIAN_LITTLE,
						  &value_string_size,
						  error );
#else
					result = libuna_utf8_string_size_from_utf16_stream(
						  ( (lnk_data_block_environment_variables_location_t *) data_block_data )->unicode_environment_variables_location,
						  520,
						  LIBUNA_ENDIAN_LITTLE,
						  &value_string_size,
						  error );
#endif
					if( result != 1 )
					{
						liberror_error_set(
						 error,
						 LIBERROR_ERROR_DOMAIN_RUNTIME,
						 LIBERROR_RUNTIME_ERROR_GET_FAILED,
						 "%s: unable to determine size of unicode environment variables location string.",
						 function );

						return( -1 );
					}
					value_string = (libcstring_system_character_t *) memory_allocate(
					                                                  sizeof( libcstring_system_character_t ) * value_string_size );

					if( value_string == NULL )
					{
						liberror_error_set(
						 error,
						 LIBERROR_ERROR_DOMAIN_MEMORY,
						 LIBERROR_MEMORY_ERROR_INSUFFICIENT,
						 "%s: unable to create unicode environment variables location string.",
						 function );

						return( -1 );
					}
#if defined( LIBCSTRING_HAVE_WIDE_SYSTEM_CHARACTER )
					result = libuna_utf16_string_copy_from_utf16_stream(
						  (libuna_utf16_character_t *) value_string,
						  value_string_size,
						  ( (lnk_data_block_environment_variables_location_t *) data_block_data )->unicode_environment_variables_location,
						  520,
						  LIBUNA_ENDIAN_LITTLE,
						  error );
#else
					result = libuna_utf8_string_copy_from_utf16_stream(
						  (libuna_utf8_character_t *) value_string,
						  value_string_size,
						  ( (lnk_data_block_environment_variables_location_t *) data_block_data )->unicode_environment_variables_location,
						  520,
						  LIBUNA_ENDIAN_LITTLE,
						  error );
#endif
					if( result != 1 )
					{
						liberror_error_set(
						 error,
						 LIBERROR_ERROR_DOMAIN_RUNTIME,
						 LIBERROR_RUNTIME_ERROR_SET_FAILED,
						 "%s: unable to set unicode environment variables location string.",
						 function );

						memory_free(
						 value_string );

						return( -1 );
					}
					libnotify_printf(
					 "%s: unicode environment variables location\t\t\t: %" PRIs_LIBCSTRING_SYSTEM "\n",
					 function,
					 value_string );

					memory_free(
					 value_string );

					libnotify_printf(
					 "\n" );
				}
#endif
				break;

			case LIBLNK_DATA_BLOCK_SIGNATURE_DISTRIBUTED_LINK_TRACKER_PROPERTIES:
/* TODO add data block size check */
/* TODO add size and version check */
#if defined( HAVE_VERBOSE_OUTPUT )
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

						return( -1 );
					}
					byte_stream_copy_to_uint32_little_endian(
					 ( (lnk_data_block_distributed_link_tracker_properties_t *) data_block_data )->data_size,
					 value_32bit );

					libnotify_printf(
					 "%s: distributed link tracker data size\t\t\t\t: %" PRIu32 "\n",
					 function,
					 value_32bit );

					byte_stream_copy_to_uint32_little_endian(
					 ( (lnk_data_block_distributed_link_tracker_properties_t *) data_block_data )->data_version,
					 value_32bit );

					libnotify_printf(
					 "%s: distributed link tracker data version\t\t\t: %" PRIu32 "\n",
					 function,
					 value_32bit );

					libnotify_printf(
					 "%s: distributed link tracker machine identifier string data:\n",
					 function );
					libnotify_print_data(
					 ( (lnk_data_block_distributed_link_tracker_properties_t *) data_block_data )->machine_identifier_string,
					 16 );

#if defined( LIBCSTRING_HAVE_WIDE_SYSTEM_CHARACTER )
					result = libuna_utf16_string_size_from_byte_stream(
						  ( (lnk_data_block_distributed_link_tracker_properties_t *) data_block_data )->machine_identifier_string,
						  16,
						  io_handle->ascii_codepage,
						  &value_string_size,
						  error );
#else
					result = libuna_utf8_string_size_from_byte_stream(
						  ( (lnk_data_block_distributed_link_tracker_properties_t *) data_block_data )->machine_identifier_string,
						  16,
						  io_handle->ascii_codepage,
						  &value_string_size,
						  error );
#endif
					if( result != 1 )
					{
						liberror_error_set(
						 error,
						 LIBERROR_ERROR_DOMAIN_RUNTIME,
						 LIBERROR_RUNTIME_ERROR_GET_FAILED,
						 "%s: unable to determine size of machine identifier string.",
						 function );

						return( -1 );
					}
					value_string = (libcstring_system_character_t *) memory_allocate(
					                                                  sizeof( libcstring_system_character_t ) * value_string_size );

					if( value_string == NULL )
					{
						liberror_error_set(
						 error,
						 LIBERROR_ERROR_DOMAIN_MEMORY,
						 LIBERROR_MEMORY_ERROR_INSUFFICIENT,
						 "%s: unable to create machine identifier string.",
						 function );

						return( -1 );
					}
#if defined( LIBCSTRING_HAVE_WIDE_SYSTEM_CHARACTER )
					result = libuna_utf16_string_copy_from_byte_stream(
						  (libuna_utf16_character_t *) value_string,
						  value_string_size,
						  ( (lnk_data_block_distributed_link_tracker_properties_t *) data_block_data )->machine_identifier_string,
						  16,
						  io_handle->ascii_codepage,
						  error );
#else
					result = libuna_utf8_string_copy_from_byte_stream(
						  (libuna_utf8_character_t *) value_string,
						  value_string_size,
						  ( (lnk_data_block_distributed_link_tracker_properties_t *) data_block_data )->machine_identifier_string,
						  16,
						  io_handle->ascii_codepage,
						  error );
#endif
					if( result != 1 )
					{
						liberror_error_set(
						 error,
						 LIBERROR_ERROR_DOMAIN_RUNTIME,
						 LIBERROR_RUNTIME_ERROR_SET_FAILED,
						 "%s: unable to set machine identifier string.",
						 function );

						memory_free(
						 value_string );

						return( -1 );
					}
					libnotify_printf(
					 "%s: distributed link tracker machine identifier string\t\t: %" PRIs_LIBCSTRING_SYSTEM "\n",
					 function,
					 value_string );

					memory_free(
					 value_string );

					if( libfguid_identifier_copy_from_byte_stream(
					     guid,
					     ( (lnk_data_block_distributed_link_tracker_properties_t *) data_block_data )->droid_volume_identifier,
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

						libfguid_identifier_free(
						 &guid,
						 NULL );

						return( -1 );
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

						libfguid_identifier_free(
						 &guid,
						 NULL );

						return( -1 );
					}
					libnotify_printf(
					 "%s: distributed link tracker droid volume identifier\t\t: %" PRIs_LIBCSTRING_SYSTEM "\n",
					 function,
					 guid_string );

					if( libfguid_identifier_copy_from_byte_stream(
					     guid,
					     ( (lnk_data_block_distributed_link_tracker_properties_t *) data_block_data )->droid_file_identifier,
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

						libfguid_identifier_free(
						 &guid,
						 NULL );

						return( -1 );
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

						libfguid_identifier_free(
						 &guid,
						 NULL );

						return( -1 );
					}
					libnotify_printf(
					 "%s: distributed link tracker droid file identifier\t\t: %" PRIs_LIBCSTRING_SYSTEM "\n",
					 function,
					 guid_string );

					if( libfguid_identifier_copy_from_byte_stream(
					     guid,
					     ( (lnk_data_block_distributed_link_tracker_properties_t *) data_block_data )->birth_droid_volume_identifier,
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

						libfguid_identifier_free(
						 &guid,
						 NULL );

						return( -1 );
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

						libfguid_identifier_free(
						 &guid,
						 NULL );

						return( -1 );
					}
					libnotify_printf(
					 "%s: distributed link tracker birth droid volume identifier\t: %" PRIs_LIBCSTRING_SYSTEM "\n",
					 function,
					 guid_string );

					if( libfguid_identifier_copy_from_byte_stream(
					     guid,
					     ( (lnk_data_block_distributed_link_tracker_properties_t *) data_block_data )->birth_droid_file_identifier,
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

						libfguid_identifier_free(
						 &guid,
						 NULL );

						return( -1 );
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

						libfguid_identifier_free(
						 &guid,
						 NULL );

						return( -1 );
					}
					libnotify_printf(
					 "%s: distributed link tracker birth droid file identifier\t\t: %" PRIs_LIBCSTRING_SYSTEM "\n",
					 function,
					 guid_string );

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

						return( -1 );
					}
				}
#endif
				break;

			case LIBLNK_DATA_BLOCK_SIGNATURE_SPECIAL_FOLDER_LOCATION:
/* TODO add data block size check */
#if defined( HAVE_VERBOSE_OUTPUT )
				if( libnotify_verbose != 0 )
				{
					byte_stream_copy_to_uint32_little_endian(
					 ( (lnk_data_block_special_folder_location_t *) data_block_data )->special_folder_identifier,
					 value_32bit );

					libnotify_printf(
					 "%s: special folder identifier\t\t\t\t\t: %" PRIu32 "\n",
					 function,
					 value_32bit );

					byte_stream_copy_to_uint32_little_endian(
					 ( (lnk_data_block_special_folder_location_t *) data_block_data )->first_child_segment_offset,
					 value_32bit );

					libnotify_printf(
					 "%s: first child segment offset\t\t\t\t\t: %" PRIu32 "\n",
					 function,
					 value_32bit );

					libnotify_printf(
					 "\n" );
				}
#endif
				break;

			case LIBLNK_DATA_BLOCK_SIGNATURE_DARWIN_PROPERTIES:
/* TODO add data block size check */
				if( ( io_handle->data_flags & LIBLNK_DATA_FLAG_HAS_DARWIN_IDENTIFIER ) != 0 )
				{
/* TODO notify that flag was not set */
				}
#if defined( HAVE_VERBOSE_OUTPUT )
				if( libnotify_verbose != 0 )
				{
					libnotify_printf(
					 "%s: darwin properties data:\n",
					 function );
					libnotify_print_data(
					 ( (lnk_data_block_darwin_properties_t *) data_block_data )->darwin_applicaton_identifier,
					 260 );

#if defined( LIBCSTRING_HAVE_WIDE_SYSTEM_CHARACTER )
					result = libuna_utf16_string_size_from_byte_stream(
						  ( (lnk_data_block_darwin_properties_t *) data_block_data )->darwin_applicaton_identifier,
						  260,
						  io_handle->ascii_codepage,
						  &value_string_size,
						  error );
#else
					result = libuna_utf8_string_size_from_byte_stream(
						  ( (lnk_data_block_darwin_properties_t *) data_block_data )->darwin_applicaton_identifier,
						  260,
						  io_handle->ascii_codepage,
						  &value_string_size,
						  error );
#endif
					if( result != 1 )
					{
						liberror_error_set(
						 error,
						 LIBERROR_ERROR_DOMAIN_RUNTIME,
						 LIBERROR_RUNTIME_ERROR_GET_FAILED,
						 "%s: unable to determine size of darwin application identifier string.",
						 function );

						return( -1 );
					}
					value_string = (libcstring_system_character_t *) memory_allocate(
					                                                  sizeof( libcstring_system_character_t ) * value_string_size );

					if( value_string == NULL )
					{
						liberror_error_set(
						 error,
						 LIBERROR_ERROR_DOMAIN_MEMORY,
						 LIBERROR_MEMORY_ERROR_INSUFFICIENT,
						 "%s: unable to create darwin application identifier string.",
						 function );

						return( -1 );
					}
#if defined( LIBCSTRING_HAVE_WIDE_SYSTEM_CHARACTER )
					result = libuna_utf16_string_copy_from_byte_stream(
						  (libuna_utf16_character_t *) value_string,
						  value_string_size,
						  ( (lnk_data_block_darwin_properties_t *) data_block_data )->darwin_applicaton_identifier,
						  260,
						  io_handle->ascii_codepage,
						  error );
#else
					result = libuna_utf8_string_copy_from_byte_stream(
						  (libuna_utf8_character_t *) value_string,
						  value_string_size,
						  ( (lnk_data_block_darwin_properties_t *) data_block_data )->darwin_applicaton_identifier,
						  260,
						  io_handle->ascii_codepage,
						  error );
#endif
					if( result != 1 )
					{
						liberror_error_set(
						 error,
						 LIBERROR_ERROR_DOMAIN_RUNTIME,
						 LIBERROR_RUNTIME_ERROR_SET_FAILED,
						 "%s: unable to set darwin application identifier string.",
						 function );

						memory_free(
						 value_string );

						return( -1 );
					}
					libnotify_printf(
					 "%s: darwin application identifier\t\t\t\t\t: %" PRIs_LIBCSTRING_SYSTEM "\n",
					 function,
					 value_string );

					memory_free(
					 value_string );

/* TODO print as string */
					libnotify_printf(
					 "%s: unicode darwin application identifier data:\n",
					 function );
					libnotify_print_data(
					 ( (lnk_data_block_darwin_properties_t *) data_block_data )->unicode_darwin_applicaton_identifier,
					 520 );

#if defined( LIBCSTRING_HAVE_WIDE_SYSTEM_CHARACTER )
					result = libuna_utf16_string_size_from_utf16_stream(
						  ( (lnk_data_block_darwin_properties_t *) data_block_data )->unicode_darwin_applicaton_identifier,
						  520,
						  LIBUNA_ENDIAN_LITTLE,
						  &value_string_size,
						  error );
#else
					result = libuna_utf8_string_size_from_utf16_stream(
						  ( (lnk_data_block_darwin_properties_t *) data_block_data )->unicode_darwin_applicaton_identifier,
						  520,
						  LIBUNA_ENDIAN_LITTLE,
						  &value_string_size,
						  error );
#endif
					if( result != 1 )
					{
						liberror_error_set(
						 error,
						 LIBERROR_ERROR_DOMAIN_RUNTIME,
						 LIBERROR_RUNTIME_ERROR_GET_FAILED,
						 "%s: unable to determine size of unicode darwin application identifier string.",
						 function );

						return( -1 );
					}
					value_string = (libcstring_system_character_t *) memory_allocate(
					                                                  sizeof( libcstring_system_character_t ) * value_string_size );

					if( value_string == NULL )
					{
						liberror_error_set(
						 error,
						 LIBERROR_ERROR_DOMAIN_MEMORY,
						 LIBERROR_MEMORY_ERROR_INSUFFICIENT,
						 "%s: unable to create unicode darwin application identifier string.",
						 function );

						return( -1 );
					}
#if defined( LIBCSTRING_HAVE_WIDE_SYSTEM_CHARACTER )
					result = libuna_utf16_string_copy_from_utf16_stream(
						  (libuna_utf16_character_t *) value_string,
						  value_string_size,
						  ( (lnk_data_block_darwin_properties_t *) data_block_data )->unicode_darwin_applicaton_identifier,
						  520,
						  LIBUNA_ENDIAN_LITTLE,
						  error );
#else
					result = libuna_utf8_string_copy_from_utf16_stream(
						  (libuna_utf8_character_t *) value_string,
						  value_string_size,
						  ( (lnk_data_block_darwin_properties_t *) data_block_data )->unicode_darwin_applicaton_identifier,
						  520,
						  LIBUNA_ENDIAN_LITTLE,
						  error );
#endif
					if( result != 1 )
					{
						liberror_error_set(
						 error,
						 LIBERROR_ERROR_DOMAIN_RUNTIME,
						 LIBERROR_RUNTIME_ERROR_SET_FAILED,
						 "%s: unable to set unicode darwin application identifier string.",
						 function );

						memory_free(
						 value_string );

						return( -1 );
					}
					libnotify_printf(
					 "%s: unicode darwin application identifier\t\t\t\t: %" PRIs_LIBCSTRING_SYSTEM "\n",
					 function,
					 value_string );

					memory_free(
					 value_string );

					libnotify_printf(
					 "\n" );
				}
#endif
				break;

			case LIBLNK_DATA_BLOCK_SIGNATURE_ICON_LOCATION:
/* TODO add data block size check */
				if( ( io_handle->data_flags & LIBLNK_DATA_FLAG_HAS_ICON_LOCATION_BLOCK ) != 0 )
				{
/* TODO notify that flag was not set */
				}
#if defined( HAVE_VERBOSE_OUTPUT )
				if( libnotify_verbose != 0 )
				{
					libnotify_printf(
					 "%s: icon location data:\n",
					 function );
					libnotify_print_data(
					 ( (lnk_data_block_icon_location_t *) data_block_data )->icon_location,
					 260 );

#if defined( LIBCSTRING_HAVE_WIDE_SYSTEM_CHARACTER )
					result = libuna_utf16_string_size_from_byte_stream(
						  ( (lnk_data_block_icon_location_t *) data_block_data )->icon_location,
						  260,
						  io_handle->ascii_codepage,
						  &value_string_size,
						  error );
#else
					result = libuna_utf8_string_size_from_byte_stream(
						  ( (lnk_data_block_icon_location_t *) data_block_data )->icon_location,
						  260,
						  io_handle->ascii_codepage,
						  &value_string_size,
						  error );
#endif
					if( result != 1 )
					{
						liberror_error_set(
						 error,
						 LIBERROR_ERROR_DOMAIN_RUNTIME,
						 LIBERROR_RUNTIME_ERROR_GET_FAILED,
						 "%s: unable to determine size of icon location string.",
						 function );

						return( -1 );
					}
					value_string = (libcstring_system_character_t *) memory_allocate(
					                                                  sizeof( libcstring_system_character_t ) * value_string_size );

					if( value_string == NULL )
					{
						liberror_error_set(
						 error,
						 LIBERROR_ERROR_DOMAIN_MEMORY,
						 LIBERROR_MEMORY_ERROR_INSUFFICIENT,
						 "%s: unable to create icon location string.",
						 function );

						return( -1 );
					}
#if defined( LIBCSTRING_HAVE_WIDE_SYSTEM_CHARACTER )
					result = libuna_utf16_string_copy_from_byte_stream(
						  (libuna_utf16_character_t *) value_string,
						  value_string_size,
						  ( (lnk_data_block_icon_location_t *) data_block_data )->icon_location,
						  260,
						  io_handle->ascii_codepage,
						  error );
#else
					result = libuna_utf8_string_copy_from_byte_stream(
						  (libuna_utf8_character_t *) value_string,
						  value_string_size,
						  ( (lnk_data_block_icon_location_t *) data_block_data )->icon_location,
						  260,
						  io_handle->ascii_codepage,
						  error );
#endif
					if( result != 1 )
					{
						liberror_error_set(
						 error,
						 LIBERROR_ERROR_DOMAIN_RUNTIME,
						 LIBERROR_RUNTIME_ERROR_SET_FAILED,
						 "%s: unable to set icon location string.",
						 function );

						memory_free(
						 value_string );

						return( -1 );
					}
					libnotify_printf(
					 "%s: icon location\t\t\t\t\t\t: %" PRIs_LIBCSTRING_SYSTEM "\n",
					 function,
					 value_string );

					memory_free(
					 value_string );

/* TODO print as string */
					libnotify_printf(
					 "%s: unicode icon location data:\n",
					 function );
					libnotify_print_data(
					 ( (lnk_data_block_icon_location_t *) data_block_data )->unicode_icon_location,
					 520 );

#if defined( LIBCSTRING_HAVE_WIDE_SYSTEM_CHARACTER )
					result = libuna_utf16_string_size_from_utf16_stream(
						  ( (lnk_data_block_icon_location_t *) data_block_data )->unicode_icon_location,
						  520,
						  LIBUNA_ENDIAN_LITTLE,
						  &value_string_size,
						  error );
#else
					result = libuna_utf8_string_size_from_utf16_stream(
						  ( (lnk_data_block_icon_location_t *) data_block_data )->unicode_icon_location,
						  520,
						  LIBUNA_ENDIAN_LITTLE,
						  &value_string_size,
						  error );
#endif
					if( result != 1 )
					{
						liberror_error_set(
						 error,
						 LIBERROR_ERROR_DOMAIN_RUNTIME,
						 LIBERROR_RUNTIME_ERROR_GET_FAILED,
						 "%s: unable to determine size of unicode icon location string.",
						 function );

						return( -1 );
					}
					value_string = (libcstring_system_character_t *) memory_allocate(
					                                                  sizeof( libcstring_system_character_t ) * value_string_size );

					if( value_string == NULL )
					{
						liberror_error_set(
						 error,
						 LIBERROR_ERROR_DOMAIN_MEMORY,
						 LIBERROR_MEMORY_ERROR_INSUFFICIENT,
						 "%s: unable to create unicode icon location string.",
						 function );

						return( -1 );
					}
#if defined( LIBCSTRING_HAVE_WIDE_SYSTEM_CHARACTER )
					result = libuna_utf16_string_copy_from_utf16_stream(
						  (libuna_utf16_character_t *) value_string,
						  value_string_size,
						  ( (lnk_data_block_icon_location_t *) data_block_data )->unicode_icon_location,
						  520,
						  LIBUNA_ENDIAN_LITTLE,
						  error );
#else
					result = libuna_utf8_string_copy_from_utf16_stream(
						  (libuna_utf8_character_t *) value_string,
						  value_string_size,
						  ( (lnk_data_block_icon_location_t *) data_block_data )->unicode_icon_location,
						  520,
						  LIBUNA_ENDIAN_LITTLE,
						  error );
#endif
					if( result != 1 )
					{
						liberror_error_set(
						 error,
						 LIBERROR_ERROR_DOMAIN_RUNTIME,
						 LIBERROR_RUNTIME_ERROR_SET_FAILED,
						 "%s: unable to set unicode icon location string.",
						 function );

						memory_free(
						 value_string );

						return( -1 );
					}
					libnotify_printf(
					 "%s: unicode icon location\t\t\t\t\t: %" PRIs_LIBCSTRING_SYSTEM "\n",
					 function,
					 value_string );

					memory_free(
					 value_string );

					libnotify_printf(
					 "\n" );
				}
#endif
				break;

			case LIBLNK_DATA_BLOCK_SIGNATURE_KNOWN_FOLDER_LOCATION:
/* TODO add data block size check */
#if defined( HAVE_VERBOSE_OUTPUT )
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

						return( -1 );
					}
					if( libfguid_identifier_copy_from_byte_stream(
					     guid,
					     ( (lnk_data_block_known_folder_location_t *) data_block_data )->known_folder_identifier,
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

						libfguid_identifier_free(
						 &guid,
						 NULL );

						return( -1 );
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

						libfguid_identifier_free(
						 &guid,
						 NULL );

						return( -1 );
					}
					libnotify_printf(
					 "%s: known folder identifier\t\t\t\t\t: %" PRIs_LIBCSTRING_SYSTEM "\n",
					 function,
					 guid_string );

					libnotify_printf(
					 "%s: known folder name\t\t\t\t\t\t: %s\n",
					 function,
					 libfwsi_folder_identifier_get_name(
					  ( (lnk_data_block_known_folder_location_t *) data_block_data )->known_folder_identifier ) );

					byte_stream_copy_to_uint32_little_endian(
					 ( (lnk_data_block_known_folder_location_t *) data_block_data )->first_child_segment_offset,
					 value_32bit );

					libnotify_printf(
					 "%s: first child segment offset\t\t\t\t\t: %" PRIu32 "\n",
					 function,
					 value_32bit );

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

						return( -1 );
					}
				}
#endif
				break;

			default:
#if defined( HAVE_VERBOSE_OUTPUT )
				if( libnotify_verbose != 0 )
				{
					libnotify_printf(
					 "%s: unsupported extra data block.\n\n",
					 function );
				}
#endif
				break;
		}
		memory_free(
		 data_block_data );
	}
	return( total_read_count );
}

