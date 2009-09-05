/*
 * liblnk Input/Output (IO) handle
 *
 * Copyright (c) 2008-2009, Joachim Metz <forensics@hoffmannbv.nl>,
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

#include "liblnk_debug.h"
#include "liblnk_definitions.h"
#include "liblnk_filetime.h"
#include "liblnk_file_information.h"
#include "liblnk_guid.h"
#include "liblnk_io_handle.h"
#include "liblnk_libbfio.h"
#include "liblnk_string.h"

#include "lnk_file_header.h"

const uint8_t lnk_file_signature[ 4 ] = { 0x4c, 0x00, 0x00, 0x00 };

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
     liblnk_file_information_t *file_information,
     liberror_error_t **error )
{
	lnk_file_header_t file_header;

	static char *function = "liblnk_io_handle_read_file_header";
	ssize_t read_count    = 0;

#if defined( HAVE_VERBOSE_OUTPUT )
	liblnk_character_t filetime_string[ LIBLNK_FILETIME_STRING_SIZE ];
	liblnk_character_t guid_string[ LIBLNK_GUID_STRING_SIZE ];

	uint32_t test         = 0;
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
	libnotify_verbose_printf(
	 "%s: file header:\n",
	 function );
	libnotify_verbose_print_data(
	 (uint8_t *) &file_header,
	 sizeof( lnk_file_header_t ) );
#endif

	if( memory_compare(
	     file_header.signature,
	     lnk_file_signature,
	     4 ) != 0 )
	{
		liberror_error_set(
		 error,
		 LIBERROR_ERROR_DOMAIN_RUNTIME,
		 LIBERROR_RUNTIME_ERROR_UNSUPPORTED_VALUE,
		 "%s: invalid file signature.",
		 function );

		return( -1 );
	}
	endian_little_convert_32bit(
	 *data_flags,
	 file_header.data_flags );
	endian_little_convert_32bit(
	 file_information->attribute_flags,
	 file_header.file_attribute_flags );

	endian_little_convert_64bit(
	 file_information->creation_time,
	 file_header.creation_time );
	endian_little_convert_64bit(
	 file_information->modification_time,
	 file_header.modification_time );
	endian_little_convert_64bit(
	 file_information->access_time,
	 file_header.access_time );

	if( liblnk_filetime_from_byte_stream(
	     &( file_information->creation_time ),
	     file_header.creation_time,
	     8,
	     LIBLNK_ENDIAN_LITTLE,
	     error ) != 1 )
	{
		liberror_error_set(
		 error,
		 LIBERROR_ERROR_DOMAIN_CONVERSION,
		 LIBERROR_CONVERSION_ERROR_GENERIC,
		 "%s: unable to create creation time.",
		 function );

		return( -1 );
	}
	if( liblnk_filetime_from_byte_stream(
	     &( file_information->modification_time ),
	     file_header.modification_time,
	     8,
	     LIBLNK_ENDIAN_LITTLE,
	     error ) != 1 )
	{
		liberror_error_set(
		 error,
		 LIBERROR_ERROR_DOMAIN_CONVERSION,
		 LIBERROR_CONVERSION_ERROR_GENERIC,
		 "%s: unable to create modification time.",
		 function );

		return( -1 );
	}
	if( liblnk_filetime_from_byte_stream(
	     &( file_information->access_time ),
	     file_header.access_time,
	     8,
	     LIBLNK_ENDIAN_LITTLE,
	     error ) != 1 )
	{
		liberror_error_set(
		 error,
		 LIBERROR_ERROR_DOMAIN_CONVERSION,
		 LIBERROR_CONVERSION_ERROR_GENERIC,
		 "%s: unable to create access time.",
		 function );

		return( -1 );
	}
	endian_little_convert_32bit(
	 file_information->size,
	 file_header.file_size );

#if defined( HAVE_VERBOSE_OUTPUT )
	endian_little_convert_32bit(
	 test,
	 file_header.signature );
	libnotify_verbose_printf(
	 "%s: signature\t\t: 0x%08" PRIx32 "\n",
	 function,
	 test );

	if( liblnk_guid_to_string(
	     (liblnk_guid_t *) file_header.class_identifier,
	     LIBLNK_ENDIAN_LITTLE,
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
	libnotify_verbose_printf(
	 "%s: class identifier\t: %s\n",
	 function,
	 guid_string );

	libnotify_verbose_printf(
	 "%s: data flags\t\t: 0x%08" PRIx32 "\n",
	 function,
	 *data_flags );
	libnotify_verbose_printf(
	 "%s: file attribute flags\t: 0x%08" PRIx32 "\n",
	 function,
	 file_information->attribute_flags );

	if( liblnk_filetime_to_string(
	     &( file_information->creation_time ),
	     filetime_string,
	     LIBLNK_FILETIME_STRING_SIZE,
	     error ) != 1 )
	{
		liberror_error_set(
		 error,
		 LIBERROR_ERROR_DOMAIN_CONVERSION,
		 LIBERROR_CONVERSION_ERROR_GENERIC,
		 "%s: unable to create filetime string.",
		 function );

		return( -1 );
	}
	libnotify_verbose_printf(
	 "%s: creation time\t: %s\n",
	 function,
	 filetime_string );

	if( liblnk_filetime_to_string(
	     &( file_information->modification_time ),
	     filetime_string,
	     LIBLNK_FILETIME_STRING_SIZE,
	     error ) != 1 )
	{
		liberror_error_set(
		 error,
		 LIBERROR_ERROR_DOMAIN_CONVERSION,
		 LIBERROR_CONVERSION_ERROR_GENERIC,
		 "%s: unable to create filetime string.",
		 function );

		return( -1 );
	}
	libnotify_verbose_printf(
	 "%s: modification time\t: %s\n",
	 function,
	 filetime_string );

	if( liblnk_filetime_to_string(
	     &( file_information->access_time ),
	     filetime_string,
	     LIBLNK_FILETIME_STRING_SIZE,
	     error ) != 1 )
	{
		liberror_error_set(
		 error,
		 LIBERROR_ERROR_DOMAIN_CONVERSION,
		 LIBERROR_CONVERSION_ERROR_GENERIC,
		 "%s: unable to create filetime string.",
		 function );

		return( -1 );
	}
	libnotify_verbose_printf(
	 "%s: access time\t\t: %s\n",
	 function,
	 filetime_string );

	libnotify_verbose_printf(
	 "%s: file size\t\t: %" PRIu32 " bytes\n",
	 function,
	 file_information->size );

	endian_little_convert_32bit(
	 test,
	 file_header.icon_index );
	libnotify_verbose_printf(
	 "%s: icon index\t\t: 0x%08" PRIx32 "\n",
	 function,
	 test );
	endian_little_convert_32bit(
	 test,
	 file_header.show_window_value );
	libnotify_verbose_printf(
	 "%s: show window value\t: 0x%08" PRIx32 "\n",
	 function,
	 test );
	endian_little_convert_32bit(
	 test,
	 file_header.hot_key_value );
	libnotify_verbose_printf(
	 "%s: hot key value\t: 0x%08" PRIx32 "\n",
	 function,
	 test );
	libnotify_verbose_printf(
	 "%s: unknown1:\n",
	 function );
	libnotify_verbose_print_data(
	 (uint8_t *) file_header.unknown1,
	 8 );

	libnotify_verbose_printf(
	 "\n" );
#endif

	return( 1 );
}

