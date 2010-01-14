/*
 * liblnk Input/Output (IO) handle
 *
 * Copyright (c) 2008-2010, Joachim Metz <forensics@hoffmannbv.nl>,
 * Hoffmann Investigations.
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

#include "liblnk_debug.h"
#include "liblnk_definitions.h"
#include "liblnk_file_information.h"
#include "liblnk_guid.h"
#include "liblnk_io_handle.h"
#include "liblnk_libbfio.h"
#include "liblnk_libfdatetime.h"
#include "liblnk_string.h"

#include "lnk_file_header.h"

const uint8_t lnk_file_class_identifier[ 16 ] = \
	{ 0x01, 0x14, 0x02, 0x00, 0x00, 0x00, 0x00, 0x00, 0xc0, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x46 };

/* Initialize an io handle
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
		 "%s: invalid io handle.",
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
			 "%s: unable to create io handle.",
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
	}
	return( 1 );
}

/* Frees an exisisting io handle
 * Returns 1 if successful or -1 on error
 */
int liblnk_io_handle_free(
     liblnk_io_handle_t **io_handle,
     liberror_error_t **error )
{
	static char *function = "liblnk_io_handle_free";
	int result            = 1;

	if( io_handle == NULL )
	{
		liberror_error_set(
		 error,
		 LIBERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid io handle.",
		 function );

		return( -1 );
	}
	if( *io_handle != NULL )
	{
		if( ( ( *io_handle )->handle_created_in_library != 0 )
		 && ( ( *io_handle )->file_io_handle != NULL )
		 && ( libbfio_handle_free(
		       &( ( *io_handle )->file_io_handle ),
		       error ) != 1 ) )
		{
			liberror_error_set(
			 error,
			 LIBERROR_ERROR_DOMAIN_RUNTIME,
			 LIBERROR_RUNTIME_ERROR_FINALIZE_FAILED,
			 "%s: unable to free file io handle.",
			 function );

			result = -1;
		}
		memory_free(
		 *io_handle );

		*io_handle = NULL;
	}
	return( result );
}

/* Opens an io handle
 * Returns 1 if successful or -1 on error
 */
int liblnk_io_handle_open(
     liblnk_io_handle_t *io_handle,
     libbfio_handle_t *file_io_handle,
     int flags,
     liberror_error_t **error )
{
        static char *function = "liblnk_io_handle_open";

        if( io_handle == NULL )
        {
                liberror_error_set(
                 error,
                 LIBERROR_ERROR_DOMAIN_ARGUMENTS,
                 LIBERROR_ARGUMENT_ERROR_INVALID_VALUE,
                 "%s: invalid io handle.",
                 function );

                return( -1 );
        }
	if( io_handle->file_io_handle != NULL )
	{
		liberror_error_set(
		 error,
		 LIBERROR_ERROR_DOMAIN_RUNTIME,
		 LIBERROR_RUNTIME_ERROR_VALUE_ALREADY_SET,
		 "%s: invalid io handle - file io handle already set.",
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
	io_handle->file_io_handle = file_io_handle;

	if( libbfio_handle_open(
	     io_handle->file_io_handle,
	     flags,
	     error ) != 1 )
	{
                liberror_error_set(
                 error,
                 LIBERROR_ERROR_DOMAIN_IO,
                 LIBERROR_IO_ERROR_OPEN_FAILED,
                 "%s: unable to open file io handle.",
                 function );

                return( -1 );
	}
	return( 1 );
}

/* Closes an io handle
 * Returns 0 if successful or -1 on error
 */
int liblnk_io_handle_close(
     liblnk_io_handle_t *io_handle,
     liberror_error_t **error )
{
        static char *function = "liblnk_io_handle_close";

        if( io_handle == NULL )
        {
                liberror_error_set(
                 error,
                 LIBERROR_ERROR_DOMAIN_ARGUMENTS,
                 LIBERROR_ARGUMENT_ERROR_INVALID_VALUE,
                 "%s: invalid io handle.",
                 function );

                return( -1 );
        }
#if defined( HAVE_DEBUG_OUTPUT )
	if( liblnk_debug_print_read_offsets(
	     io_handle->file_io_handle,
	     error ) != 1 )
	{
		liberror_error_set(
		 error,
                 LIBERROR_ERROR_DOMAIN_RUNTIME,
                 LIBERROR_RUNTIME_ERROR_PRINT_FAILED,
		 "%s: unable to print the read offsets.",
		 function );
	}
#endif
	if( libbfio_handle_close(
	     io_handle->file_io_handle,
	     error ) != 0 )
	{
                liberror_error_set(
                 error,
                 LIBERROR_ERROR_DOMAIN_IO,
                 LIBERROR_IO_ERROR_CLOSE_FAILED,
                 "%s: unable to close file io handle.",
                 function );

                return( -1 );
	}
	return( 0 );
}

/* Reads the file header
 * Returns 1 if successful or -1 on error
 */
int liblnk_io_handle_read_file_header(
     liblnk_io_handle_t *io_handle,
     uint32_t *data_flags,
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
	liblnk_character_t date_time_string[ 24 ];
	liblnk_character_t guid_string[ LIBLNK_GUID_STRING_SIZE ];

	libfdatetime_filetime_t *filetime = NULL;
	uint32_t value_32bit              = 0;
	uint16_t value_16bit              = 0;
#endif

	if( io_handle == NULL )
	{
		liberror_error_set(
		 error,
		 LIBERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid io handle.",
		 function );

		return( -1 );
	}
	if( io_handle->file_io_handle == NULL )
	{
		liberror_error_set(
		 error,
		 LIBERROR_ERROR_DOMAIN_RUNTIME,
		 LIBERROR_RUNTIME_ERROR_VALUE_MISSING,
		 "%s: invalid io handle - missing file io handle.",
		 function );

		return( -1 );
	}
	if( data_flags == NULL )
	{
		liberror_error_set(
		 error,
		 LIBERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid data flags.",
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
#if defined( HAVE_DEBUG_OUTPUT )
	if( libnotify_verbose != 0 )
	{
		libnotify_printf(
		 "%s: reading file header at offset: 0 (0x00000000)\n",
		 function );
	}
#endif

	if( libbfio_handle_seek_offset(
	     io_handle->file_io_handle,
	     0,
	     SEEK_SET,
	     error ) == -1 )
	{
		liberror_error_set(
		 error,
		 LIBERROR_ERROR_DOMAIN_IO,
		 LIBERROR_IO_ERROR_SEEK_FAILED,
		 "%s: unable to seek file header offset: %" PRIu64 ".",
		 function,
		 0 );

		return( -1 );
	}
	read_count = libbfio_handle_read(
	              io_handle->file_io_handle,
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
	if( memory_copy(
	     class_identifier,
	     (liblnk_guid_t *) file_header.class_identifier,
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
	 *data_flags );
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
		 "%s: header size\t\t: %" PRIu32 "\n",
		 function,
		 header_size );

		if( liblnk_guid_to_string(
		     (liblnk_guid_t *) file_header.class_identifier,
		     LIBFDATETIME_ENDIAN_LITTLE,
		     guid_string,
		     LIBLNK_GUID_STRING_SIZE,
		     error ) != 1 )
		{
			liberror_error_set(
			 error,
			 LIBERROR_ERROR_DOMAIN_CONVERSION,
			 LIBERROR_CONVERSION_ERROR_GENERIC,
			 "%s: unable to create guid string.",
			 function );

			return( -1 );
		}
		libnotify_printf(
		 "%s: class identifier\t: %s\n",
		 function,
		 guid_string );

		if( liblnk_debug_print_data_flags(
		     *data_flags,
		     error ) != 1 )
		{
			liberror_error_set(
			 error,
			 LIBERROR_ERROR_DOMAIN_RUNTIME,
			 LIBERROR_RUNTIME_ERROR_PRINT_FAILED,
			 "%s: unable to print data flags.",
			 function );

			return( -1 );
		}
		if( liblnk_debug_print_file_attribute_flags(
		     file_information->attribute_flags,
		     error ) != 1 )
		{
			liberror_error_set(
			 error,
			 LIBERROR_ERROR_DOMAIN_RUNTIME,
			 LIBERROR_RUNTIME_ERROR_PRINT_FAILED,
			 "%s: unable to print file attribute flags.",
			 function );

			return( -1 );
		}
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
			 LIBERROR_ERROR_DOMAIN_CONVERSION,
			 LIBERROR_CONVERSION_ERROR_GENERIC,
			 "%s: unable to create creation time.",
			 function );

			libfdatetime_filetime_free(
			 &filetime,
			 NULL );

			return( -1 );
		}
		if( libfdatetime_filetime_copy_to_utf8_string(
		     filetime,
		     date_time_string,
		     24,
		     LIBFDATETIME_STRING_FORMAT_FLAG_DATE_TIME,
		     LIBFDATETIME_DATE_TIME_FORMAT_CTIME,
		     error ) != 1 )
		{
			liberror_error_set(
			 error,
			 LIBERROR_ERROR_DOMAIN_CONVERSION,
			 LIBERROR_CONVERSION_ERROR_GENERIC,
			 "%s: unable to create filetime string.",
			 function );

			libfdatetime_filetime_free(
			 &filetime,
			 NULL );

			return( -1 );
		}
		libnotify_printf(
		 "%s: creation time\t: %s\n",
		 function,
		 (char *) date_time_string );

		if( libfdatetime_filetime_copy_from_byte_stream(
		     filetime,
		     file_header.access_time,
		     8,
		     LIBFDATETIME_ENDIAN_LITTLE,
		     error ) != 1 )
		{
			liberror_error_set(
			 error,
			 LIBERROR_ERROR_DOMAIN_CONVERSION,
			 LIBERROR_CONVERSION_ERROR_GENERIC,
			 "%s: unable to create access time.",
			 function );

			libfdatetime_filetime_free(
			 &filetime,
			 NULL );

			return( -1 );
		}
		if( libfdatetime_filetime_copy_to_utf8_string(
		     filetime,
		     date_time_string,
		     24,
		     LIBFDATETIME_STRING_FORMAT_FLAG_DATE_TIME,
		     LIBFDATETIME_DATE_TIME_FORMAT_CTIME,
		     error ) != 1 )
		{
			liberror_error_set(
			 error,
			 LIBERROR_ERROR_DOMAIN_CONVERSION,
			 LIBERROR_CONVERSION_ERROR_GENERIC,
			 "%s: unable to create filetime string.",
			 function );

			libfdatetime_filetime_free(
			 &filetime,
			 NULL );

			return( -1 );
		}
		libnotify_printf(
		 "%s: access time\t\t: %s\n",
		 function,
		 (char *) date_time_string );

		if( libfdatetime_filetime_copy_from_byte_stream(
		     filetime,
		     file_header.modification_time,
		     8,
		     LIBFDATETIME_ENDIAN_LITTLE,
		     error ) != 1 )
		{
			liberror_error_set(
			 error,
			 LIBERROR_ERROR_DOMAIN_CONVERSION,
			 LIBERROR_CONVERSION_ERROR_GENERIC,
			 "%s: unable to create modification time.",
			 function );

			libfdatetime_filetime_free(
			 &filetime,
			 NULL );

			return( -1 );
		}
		if( libfdatetime_filetime_copy_to_utf8_string(
		     filetime,
		     date_time_string,
		     24,
		     LIBFDATETIME_STRING_FORMAT_FLAG_DATE_TIME,
		     LIBFDATETIME_DATE_TIME_FORMAT_CTIME,
		     error ) != 1 )
		{
			liberror_error_set(
			 error,
			 LIBERROR_ERROR_DOMAIN_CONVERSION,
			 LIBERROR_CONVERSION_ERROR_GENERIC,
			 "%s: unable to create filetime string.",
			 function );

			libfdatetime_filetime_free(
			 &filetime,
			 NULL );

			return( -1 );
		}
		libnotify_printf(
		 "%s: modification time\t: %s\n",
		 function,
		 (char *) date_time_string );

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
		 "%s: file size\t\t: %" PRIu32 " bytes\n",
		 function,
		 file_information->size );

		byte_stream_copy_to_uint32_little_endian(
		 file_header.icon_index,
		 value_32bit );
		libnotify_printf(
		 "%s: icon index\t\t: 0x%08" PRIx32 "\n",
		 function,
		 value_32bit );

		byte_stream_copy_to_uint32_little_endian(
		 file_header.show_window_value,
		 value_32bit );
		libnotify_printf(
		 "%s: show window value\t: 0x%08" PRIx32 "\n",
		 function,
		 value_32bit );

		byte_stream_copy_to_uint16_little_endian(
		 file_header.hot_key_value,
		 value_16bit );
		libnotify_printf(
		 "%s: hot key value\t: 0x%04" PRIx16 "\n",
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

	return( 1 );
}

