/*
 * Input/Output (IO) handle
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

#include "liblnk_codepage.h"
#include "liblnk_debug.h"
#include "liblnk_definitions.h"
#include "liblnk_file_information.h"
#include "liblnk_io_handle.h"
#include "liblnk_libbfio.h"
#include "liblnk_libcerror.h"
#include "liblnk_libcnotify.h"
#include "liblnk_libcstring.h"
#include "liblnk_libfdatetime.h"
#include "liblnk_libfguid.h"
#include "liblnk_libuna.h"

#include "lnk_data_blocks.h"
#include "lnk_file_header.h"

const uint8_t lnk_file_class_identifier[ 16 ] = \
	{ 0x01, 0x14, 0x02, 0x00, 0x00, 0x00, 0x00, 0x00, 0xc0, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x46 };

/* Creates an IO handle
 * Make sure the value io_handle is referencing, is set to NULL
 * Returns 1 if successful or -1 on error
 */
int liblnk_io_handle_initialize(
     liblnk_io_handle_t **io_handle,
     libcerror_error_t **error )
{
	static char *function = "liblnk_io_handle_initialize";

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
	if( *io_handle != NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_VALUE_ALREADY_SET,
		 "%s: invalid IO handle value already set.",
		 function );

		return( -1 );
	}
	*io_handle = memory_allocate_structure(
	              liblnk_io_handle_t );

	if( *io_handle == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_MEMORY,
		 LIBCERROR_MEMORY_ERROR_INSUFFICIENT,
		 "%s: unable to create IO handle.",
		 function );

		goto on_error;
	}
	if( memory_set(
	     *io_handle,
	     0,
	     sizeof( liblnk_io_handle_t ) ) == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_MEMORY,
		 LIBCERROR_MEMORY_ERROR_SET_FAILED,
		 "%s: unable to clear file.",
		 function );

		goto on_error;
	}
	( *io_handle )->ascii_codepage = LIBLNK_CODEPAGE_WINDOWS_1252;

	return( 1 );

on_error:
	if( *io_handle != NULL )
	{
		memory_free(
		 *io_handle );

		*io_handle = NULL;
	}
	return( -1 );
}

/* Frees an IO handle
 * Returns 1 if successful or -1 on error
 */
int liblnk_io_handle_free(
     liblnk_io_handle_t **io_handle,
     libcerror_error_t **error )
{
	static char *function = "liblnk_io_handle_free";

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
	if( *io_handle != NULL )
	{
		memory_free(
		 *io_handle );

		*io_handle = NULL;
	}
	return( 1 );
}

/* Clears the IO handle
 * Returns 1 if successful or -1 on error
 */
int liblnk_io_handle_clear(
     liblnk_io_handle_t *io_handle,
     libcerror_error_t **error )
{
	static char *function = "liblnk_io_handle_clear";

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
	if( memory_set(
	     io_handle,
	     0,
	     sizeof( liblnk_io_handle_t ) ) == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_MEMORY,
		 LIBCERROR_MEMORY_ERROR_SET_FAILED,
		 "%s: unable to clear IO handle.",
		 function );

		return( -1 );
	}
	io_handle->ascii_codepage = LIBLNK_CODEPAGE_WINDOWS_1252;

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
         libcerror_error_t **error )
{
	lnk_file_header_t file_header;

	static char *function             = "liblnk_io_handle_read_file_header";
	ssize_t read_count                = 0;
	uint32_t header_size              = 0;

#if defined( HAVE_DEBUG_OUTPUT )
	libcstring_system_character_t filetime_string[ 32 ];
	libcstring_system_character_t guid_string[ 48 ];

	libfdatetime_filetime_t *filetime = NULL;
	libfguid_identifier_t *guid       = NULL;
	uint32_t value_32bit              = 0;
	uint16_t value_16bit              = 0;
	int result                        = 0;
#endif

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
	if( class_identifier == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid class identifier.",
		 function );

		return( -1 );
	}
	if( class_identifier_size < 16 )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_VALUE_TOO_SMALL,
		 "%s: class identifier too small.",
		 function );

		return( -1 );
	}
	if( class_identifier_size > (size_t) SSIZE_MAX )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_VALUE_EXCEEDS_MAXIMUM,
		 "%s: class identifier size value exceeds maximum.",
		 function );

		return( -1 );
	}
	if( file_information == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid file information.",
		 function );

		return( -1 );
	}
	if( libbfio_handle_get_size(
	     file_io_handle,
	     &( io_handle->file_size ),
	     error ) != 1 )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_GET_FAILED,
		 "%s: unable to retrieve file size.",
		 function );

		goto on_error;
	}
#if defined( HAVE_DEBUG_OUTPUT )
	if( libcnotify_verbose != 0 )
	{
		libcnotify_printf(
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
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_IO,
		 LIBCERROR_IO_ERROR_SEEK_FAILED,
		 "%s: unable to seek file header offset: 0.",
		 function );

		goto on_error;
	}
	read_count = libbfio_handle_read_buffer(
	              file_io_handle,
	              (uint8_t *) &file_header,
	              sizeof( lnk_file_header_t ),
	              error );

	if( read_count != (ssize_t) sizeof( lnk_file_header_t ) )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_IO,
		 LIBCERROR_IO_ERROR_READ_FAILED,
		 "%s: unable to read file header.",
		 function );

		goto on_error;
	}
#if defined( HAVE_DEBUG_OUTPUT )
	if( libcnotify_verbose != 0 )
	{
		libcnotify_printf(
		 "%s: file header:\n",
		 function );
		libcnotify_print_data(
		 (uint8_t *) &file_header,
		 sizeof( lnk_file_header_t ),
		 0 );
	}
#endif
	byte_stream_copy_to_uint32_little_endian(
	 file_header.header_size,
	 header_size );

	if( header_size != 0x4c )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_UNSUPPORTED_VALUE,
		 "%s: unsupported header size: %" PRIu32 ".",
		 function,
		 header_size );

		goto on_error;
	}
	if( memory_compare(
	     file_header.class_identifier,
	     lnk_file_class_identifier,
	     16 ) != 0 )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_UNSUPPORTED_VALUE,
		 "%s: unsupported file class identifier.",
		 function );

		goto on_error;
	}
	/* TODO is a libfguid version of the class identifier needed ? */
	if( memory_copy(
	     class_identifier,
	     file_header.class_identifier,
	     16 ) == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_MEMORY,
		 LIBCERROR_MEMORY_ERROR_SET_FAILED,
		 "%s: unable to copy class identifier.",
		 function );

		goto on_error;
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

#if defined( HAVE_DEBUG_OUTPUT )
	if( libcnotify_verbose != 0 )
	{
		libcnotify_printf(
		 "%s: header size\t\t\t\t: %" PRIu32 "\n",
		 function,
		 header_size );

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
		     file_header.class_identifier,
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
		libcnotify_printf(
		 "%s: class identifier\t\t\t: %" PRIs_LIBCSTRING_SYSTEM "\n",
		 function,
		 guid_string );

		libcnotify_printf(
		 "%s: data flags\t\t\t\t: 0x%08" PRIx32 "\n",
		 function,
		 io_handle->data_flags );
		liblnk_debug_print_data_flags(
		 io_handle->data_flags );
		libcnotify_printf(
		 "\n" );

		libcnotify_printf(
		 "%s: file attribute flags\t\t\t: 0x%08" PRIx32 "\n",
		 function,
		 file_information->attribute_flags );
		liblnk_debug_print_file_attribute_flags(
		 file_information->attribute_flags );
		libcnotify_printf(
		 "\n" );

		if( libfdatetime_filetime_initialize(
		     &filetime,
		     error ) != 1 )
		{
			libcerror_error_set(
			 error,
			 LIBCERROR_ERROR_DOMAIN_RUNTIME,
			 LIBCERROR_RUNTIME_ERROR_INITIALIZE_FAILED,
			 "%s: unable to create filetime.",
			 function );

			goto on_error;
		}
		if( libfdatetime_filetime_copy_from_byte_stream(
		     filetime,
		     file_header.creation_time,
		     8,
		     LIBFDATETIME_ENDIAN_LITTLE,
		     error ) != 1 )
		{
			libcerror_error_set(
			 error,
			 LIBCERROR_ERROR_DOMAIN_RUNTIME,
			 LIBCERROR_RUNTIME_ERROR_COPY_FAILED,
			 "%s: unable to copy byte stream to filetime.",
			 function );

			goto on_error;
		}
#if defined( LIBCSTRING_HAVE_WIDE_SYSTEM_CHARACTER )
		result = libfdatetime_filetime_copy_to_utf16_string(
			  filetime,
			  (uint16_t *) filetime_string,
			  32,
			  LIBFDATETIME_STRING_FORMAT_TYPE_CTIME | LIBFDATETIME_STRING_FORMAT_FLAG_DATE_TIME_NANO_SECONDS,
			  error );
#else
		result = libfdatetime_filetime_copy_to_utf8_string(
			  filetime,
			  (uint8_t *) filetime_string,
			  32,
			  LIBFDATETIME_STRING_FORMAT_TYPE_CTIME | LIBFDATETIME_STRING_FORMAT_FLAG_DATE_TIME_NANO_SECONDS,
			  error );
#endif
		if( result != 1 )
		{
			libcerror_error_set(
			 error,
			 LIBCERROR_ERROR_DOMAIN_RUNTIME,
			 LIBCERROR_RUNTIME_ERROR_COPY_FAILED,
			 "%s: unable to copy filetime to string.",
			 function );

			goto on_error;
		}
		libcnotify_printf(
		 "%s: creation time\t\t\t: %" PRIs_LIBCSTRING_SYSTEM " UTC\n",
		 function,
		 filetime_string );

		if( libfdatetime_filetime_copy_from_byte_stream(
		     filetime,
		     file_header.access_time,
		     8,
		     LIBFDATETIME_ENDIAN_LITTLE,
		     error ) != 1 )
		{
			libcerror_error_set(
			 error,
			 LIBCERROR_ERROR_DOMAIN_RUNTIME,
			 LIBCERROR_RUNTIME_ERROR_COPY_FAILED,
			 "%s: unable to copy byte stream to filetime.",
			 function );

			goto on_error;
		}
#if defined( LIBCSTRING_HAVE_WIDE_SYSTEM_CHARACTER )
		result = libfdatetime_filetime_copy_to_utf16_string(
			  filetime,
			  (uint16_t *) filetime_string,
			  32,
			  LIBFDATETIME_STRING_FORMAT_TYPE_CTIME | LIBFDATETIME_STRING_FORMAT_FLAG_DATE_TIME_NANO_SECONDS,
			  error );
#else
		result = libfdatetime_filetime_copy_to_utf8_string(
			  filetime,
			  (uint8_t *) filetime_string,
			  32,
			  LIBFDATETIME_STRING_FORMAT_TYPE_CTIME | LIBFDATETIME_STRING_FORMAT_FLAG_DATE_TIME_NANO_SECONDS,
			  error );
#endif
		if( result != 1 )
		{
			libcerror_error_set(
			 error,
			 LIBCERROR_ERROR_DOMAIN_RUNTIME,
			 LIBCERROR_RUNTIME_ERROR_COPY_FAILED,
			 "%s: unable to copy filetime to string.",
			 function );

			goto on_error;
		}
		libcnotify_printf(
		 "%s: access time\t\t\t\t: %" PRIs_LIBCSTRING_SYSTEM " UTC\n",
		 function,
		 filetime_string );

		if( libfdatetime_filetime_copy_from_byte_stream(
		     filetime,
		     file_header.modification_time,
		     8,
		     LIBFDATETIME_ENDIAN_LITTLE,
		     error ) != 1 )
		{
			libcerror_error_set(
			 error,
			 LIBCERROR_ERROR_DOMAIN_RUNTIME,
			 LIBCERROR_RUNTIME_ERROR_COPY_FAILED,
			 "%s: unable to copy byte stream to filetime.",
			 function );

			goto on_error;
		}
#if defined( LIBCSTRING_HAVE_WIDE_SYSTEM_CHARACTER )
		result = libfdatetime_filetime_copy_to_utf16_string(
			  filetime,
			  (uint16_t *) filetime_string,
			  32,
			  LIBFDATETIME_STRING_FORMAT_TYPE_CTIME | LIBFDATETIME_STRING_FORMAT_FLAG_DATE_TIME_NANO_SECONDS,
			  error );
#else
		result = libfdatetime_filetime_copy_to_utf8_string(
			  filetime,
			  (uint8_t *) filetime_string,
			  32,
			  LIBFDATETIME_STRING_FORMAT_TYPE_CTIME | LIBFDATETIME_STRING_FORMAT_FLAG_DATE_TIME_NANO_SECONDS,
			  error );
#endif
		if( result != 1 )
		{
			libcerror_error_set(
			 error,
			 LIBCERROR_ERROR_DOMAIN_RUNTIME,
			 LIBCERROR_RUNTIME_ERROR_COPY_FAILED,
			 "%s: unable to copy filetime to string.",
			 function );

			goto on_error;
		}
		libcnotify_printf(
		 "%s: modification time\t\t\t: %" PRIs_LIBCSTRING_SYSTEM " UTC\n",
		 function,
		 filetime_string );

		if( libfdatetime_filetime_free(
		     &filetime,
		     error ) != 1 )
		{
			libcerror_error_set(
			 error,
			 LIBCERROR_ERROR_DOMAIN_RUNTIME,
			 LIBCERROR_RUNTIME_ERROR_FINALIZE_FAILED,
			 "%s: unable to free filetime.",
			 function );

			goto on_error;
		}
		libcnotify_printf(
		 "%s: file size\t\t\t\t: %" PRIu32 " bytes\n",
		 function,
		 file_information->size );

		byte_stream_copy_to_uint32_little_endian(
		 file_header.icon_index,
		 value_32bit );
		libcnotify_printf(
		 "%s: icon index\t\t\t\t: 0x%08" PRIx32 "\n",
		 function,
		 value_32bit );

		byte_stream_copy_to_uint32_little_endian(
		 file_header.show_window_value,
		 value_32bit );
		libcnotify_printf(
		 "%s: show window value\t\t\t: 0x%08" PRIx32 "\n",
		 function,
		 value_32bit );

		byte_stream_copy_to_uint16_little_endian(
		 file_header.hot_key_value,
		 value_16bit );
		libcnotify_printf(
		 "%s: hot key value\t\t\t: 0x%04" PRIx16 "\n",
		 function,
		 value_16bit );

		libcnotify_printf(
		 "%s: reserved:\n",
		 function );
		libcnotify_print_data(
		 (uint8_t *) file_header.reserved,
		 10,
		 0 );

		libcnotify_printf(
		 "\n" );
	}
#endif
	/* TODO compare file sizes */

	return( read_count );

on_error:
#if defined( HAVE_DEBUG_OUTPUT )
	if( filetime != NULL )
	{
		libfdatetime_filetime_free(
		 &filetime,
		 NULL );
	}
	if( guid != NULL )
	{
		libfguid_identifier_free(
		 &guid,
		 NULL );
	}
#endif
	return( -1 );
}

