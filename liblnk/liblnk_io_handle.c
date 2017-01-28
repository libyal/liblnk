/*
 * Input/Output (IO) handle
 *
 * Copyright (C) 2009-2017, Joachim Metz <joachim.metz@gmail.com>
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
#include "liblnk_libfdatetime.h"
#include "liblnk_libfguid.h"
#include "liblnk_libfwsi.h"
#include "liblnk_libuna.h"

#include "lnk_data_blocks.h"
#include "lnk_file_header.h"

const uint8_t lnk_file_class_identifier[ 16 ] = {
	0x01, 0x14, 0x02, 0x00, 0x00, 0x00, 0x00, 0x00, 0xc0, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x46 };

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
	if(liblnk_get_codepage(&((*io_handle)->ascii_codepage), &error) != 1)
	{
		goto on_error;
	}

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

	static char *function = "liblnk_io_handle_read_file_header";
	ssize_t read_count    = 0;
	uint32_t header_size  = 0;

#if defined( HAVE_DEBUG_OUTPUT )
	uint32_t value_32bit  = 0;
	uint16_t value_16bit  = 0;
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

		return( -1 );
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

		return( -1 );
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

		return( -1 );
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

		return( -1 );
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

		return( -1 );
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

	byte_stream_copy_to_uint32_little_endian(
	 file_header.icon_index,
	 file_information->icon_index );

	byte_stream_copy_to_uint32_little_endian(
	 file_header.show_window_value,
	 file_information->show_window_value );

	byte_stream_copy_to_uint16_little_endian(
	 file_header.hot_key_value,
	 file_information->hot_key_value );

#if defined( HAVE_DEBUG_OUTPUT )
	if( libcnotify_verbose != 0 )
	{
		libcnotify_printf(
		 "%s: header size\t\t\t\t: %" PRIu32 "\n",
		 function,
		 header_size );

		if( libfwsi_debug_print_guid_value(
		     function,
		     "class identifier\t\t\t",
		     file_header.class_identifier,
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

		if( liblnk_debug_print_filetime_value(
		     function,
		     "creation time\t\t\t",
		     file_header.creation_time,
		     8,
		     LIBFDATETIME_ENDIAN_LITTLE,
		     LIBFDATETIME_STRING_FORMAT_TYPE_CTIME | LIBFDATETIME_STRING_FORMAT_FLAG_DATE_TIME_NANO_SECONDS,
		     error ) != 1 )
		{
			libcerror_error_set(
			 error,
			 LIBCERROR_ERROR_DOMAIN_RUNTIME,
			 LIBCERROR_RUNTIME_ERROR_PRINT_FAILED,
			 "%s: unable to print filetime value.",
			 function );

			return( -1 );
		}
		if( liblnk_debug_print_filetime_value(
		     function,
		     "access time\t\t\t\t",
		     file_header.access_time,
		     8,
		     LIBFDATETIME_ENDIAN_LITTLE,
		     LIBFDATETIME_STRING_FORMAT_TYPE_CTIME | LIBFDATETIME_STRING_FORMAT_FLAG_DATE_TIME_NANO_SECONDS,
		     error ) != 1 )
		{
			libcerror_error_set(
			 error,
			 LIBCERROR_ERROR_DOMAIN_RUNTIME,
			 LIBCERROR_RUNTIME_ERROR_PRINT_FAILED,
			 "%s: unable to print filetime value.",
			 function );

			return( -1 );
		}
		if( liblnk_debug_print_filetime_value(
		     function,
		     "modification time\t\t\t",
		     file_header.modification_time,
		     8,
		     LIBFDATETIME_ENDIAN_LITTLE,
		     LIBFDATETIME_STRING_FORMAT_TYPE_CTIME | LIBFDATETIME_STRING_FORMAT_FLAG_DATE_TIME_NANO_SECONDS,
		     error ) != 1 )
		{
			libcerror_error_set(
			 error,
			 LIBCERROR_ERROR_DOMAIN_RUNTIME,
			 LIBCERROR_RUNTIME_ERROR_PRINT_FAILED,
			 "%s: unable to print filetime value.",
			 function );

			return( -1 );
		}
		libcnotify_printf(
		 "%s: file size\t\t\t\t: %" PRIu32 " bytes\n",
		 function,
		 file_information->size );

		libcnotify_printf(
		 "%s: icon index\t\t\t\t: 0x%08" PRIx32 "\n",
		 function,
		 file_information->icon_index );

		libcnotify_printf(
		 "%s: show window value\t\t\t: 0x%08" PRIx32 "\n",
		 function,
		 file_information->show_window_value );

		libcnotify_printf(
		 "%s: hot key value\t\t\t: 0x%04" PRIx16 "\n",
		 function,
		 file_information->hot_key_value );

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
}
