/*
 * Link information functions
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
#include <memory.h>
#include <types.h>

#include "liblnk_definitions.h"
#include "liblnk_file.h"
#include "liblnk_libcerror.h"
#include "liblnk_libcnotify.h"
#include "liblnk_libuna.h"

/* Determines if the file contains distributed link tracking data
 * Returns 1 if the file contains such data, 0 if not or -1 on error
 */
int liblnk_file_has_distributed_link_tracking_data(
     liblnk_file_t *file,
     libcerror_error_t **error )
{
	liblnk_internal_file_t *internal_file = NULL;
	static char *function                 = "liblnk_file_has_distributed_link_tracking_data";

	if( file == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid file.",
		 function );

		return( -1 );
	}
	internal_file = (liblnk_internal_file_t *) file;

	if( internal_file->io_handle == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_VALUE_MISSING,
		 "%s: invalid file - missing IO handle.",
		 function );

		return( -1 );
	}
	if( internal_file->distributed_link_tracker_properties == NULL )
	{
		return( 0 );
	}
	return( 1 );
}

/* Retrieves the size of the UTF-8 encoded machine identifier
 * The size includes the end of string character
 * Returns 1 if successful or -1 on error
 */
int liblnk_file_get_utf8_machine_identifier_size(
     liblnk_file_t *file,
     size_t *utf8_string_size,
     libcerror_error_t **error )
{
	liblnk_internal_file_t *internal_file = NULL;
	static char *function                 = "liblnk_file_get_utf8_machine_identifier_size";

	if( file == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid file.",
		 function );

		return( -1 );
	}
	internal_file = (liblnk_internal_file_t *) file;

	if( internal_file->io_handle == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_VALUE_MISSING,
		 "%s: invalid file - missing IO handle.",
		 function );

		return( -1 );
	}
	if( internal_file->distributed_link_tracker_properties == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_VALUE_MISSING,
		 "%s: invalid file - missing distributed link tracker properties.",
		 function );

		return( -1 );
	}
	if( libuna_utf8_string_size_from_byte_stream(
	     internal_file->distributed_link_tracker_properties->machine_identifier_string,
	     16,
	     internal_file->io_handle->ascii_codepage,
	     utf8_string_size,
	     error ) != 1 )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_GET_FAILED,
		 "%s: unable to retrieve UTF-8 machine identifier string size.",
		 function );

		return( -1 );
	}
	return( 1 );
}

/* Retrieves the UTF-8 encoded machine identifier
 * The size should include the end of string character
 * Returns 1 if successful or -1 on error
 */
int liblnk_file_get_utf8_machine_identifier(
     liblnk_file_t *file,
     uint8_t *utf8_string,
     size_t utf8_string_size,
     libcerror_error_t **error )
{
	liblnk_internal_file_t *internal_file = NULL;
	static char *function                 = "liblnk_file_get_utf8_machine_identifier";

	if( file == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid file.",
		 function );

		return( -1 );
	}
	internal_file = (liblnk_internal_file_t *) file;

	if( internal_file->io_handle == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_VALUE_MISSING,
		 "%s: invalid file - missing IO handle.",
		 function );

		return( -1 );
	}
	if( internal_file->distributed_link_tracker_properties == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_VALUE_MISSING,
		 "%s: invalid file - missing distributed link tracker properties.",
		 function );

		return( -1 );
	}
	if( libuna_utf8_string_copy_from_byte_stream(
	     utf8_string,
	     utf8_string_size,
	     internal_file->distributed_link_tracker_properties->machine_identifier_string,
	     16,
	     internal_file->io_handle->ascii_codepage,
	     error ) != 1 )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_SET_FAILED,
		 "%s: unable to set UTF-8 data string.",
		 function );

		return( -1 );
	}
	return( 1 );
}

/* Retrieves the size of the UTF-16 encoded machine identifier
 * The size includes the end of string character
 * Returns 1 if successful or -1 on error
 */
int liblnk_file_get_utf16_machine_identifier_size(
     liblnk_file_t *file,
     size_t *utf16_string_size,
     libcerror_error_t **error )
{
	liblnk_internal_file_t *internal_file = NULL;
	static char *function                 = "liblnk_file_get_utf16_machine_identifier_size";

	if( file == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid file.",
		 function );

		return( -1 );
	}
	internal_file = (liblnk_internal_file_t *) file;

	if( internal_file->io_handle == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_VALUE_MISSING,
		 "%s: invalid file - missing IO handle.",
		 function );

		return( -1 );
	}
	if( internal_file->distributed_link_tracker_properties == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_VALUE_MISSING,
		 "%s: invalid file - missing distributed link tracker properties.",
		 function );

		return( -1 );
	}
	if( libuna_utf16_string_size_from_byte_stream(
	     internal_file->distributed_link_tracker_properties->machine_identifier_string,
	     16,
	     internal_file->io_handle->ascii_codepage,
	     utf16_string_size,
	     error ) != 1 )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_GET_FAILED,
		 "%s: unable to retrieve UTF-16 machine identifier string size.",
		 function );

		return( -1 );
	}
	return( 1 );
}

/* Retrieves the UTF-16 encoded machine identifier
 * The size should include the end of string character
 * Returns 1 if successful or -1 on error
 */
int liblnk_file_get_utf16_machine_identifier(
     liblnk_file_t *file,
     uint16_t *utf16_string,
     size_t utf16_string_size,
     libcerror_error_t **error )
{
	liblnk_internal_file_t *internal_file = NULL;
	static char *function                 = "liblnk_file_get_utf16_machine_identifier";

	if( file == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid file.",
		 function );

		return( -1 );
	}
	internal_file = (liblnk_internal_file_t *) file;

	if( internal_file->io_handle == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_VALUE_MISSING,
		 "%s: invalid file - missing IO handle.",
		 function );

		return( -1 );
	}
	if( internal_file->distributed_link_tracker_properties == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_VALUE_MISSING,
		 "%s: invalid file - missing distributed link tracker properties.",
		 function );

		return( -1 );
	}
	if( libuna_utf16_string_copy_from_byte_stream(
	     utf16_string,
	     utf16_string_size,
	     internal_file->distributed_link_tracker_properties->machine_identifier_string,
	     16,
	     internal_file->io_handle->ascii_codepage,
	     error ) != 1 )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_SET_FAILED,
		 "%s: unable to set UTF-16 data string.",
		 function );

		return( -1 );
	}
	return( 1 );
}

/* Retrieves the droid volume identifier
 * Returns 1 if successful or -1 on error
 */
int liblnk_file_get_droid_volume_identifier(
     liblnk_file_t *file,
     uint8_t *guid,
     size_t size,
     libcerror_error_t **error )
{
	liblnk_internal_file_t *internal_file = NULL;
	static char *function                 = "liblnk_file_get_droid_volume_identifier";

	if( file == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid file.",
		 function );

		return( -1 );
	}
	internal_file = (liblnk_internal_file_t *) file;

	if( internal_file->distributed_link_tracker_properties == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_VALUE_MISSING,
		 "%s: invalid file - missing distributed link tracker properties.",
		 function );

		return( -1 );
	}
	if( guid == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid GUID.",
		 function );

		return( -1 );
	}
	if( size > (size_t) SSIZE_MAX )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_VALUE_EXCEEDS_MAXIMUM,
		 "%s: size value exceeds maximum.",
		 function );

		return( -1 );
	}
	if( size < 16 )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_VALUE_TOO_SMALL,
		 "%s: GUID value too small.",
		 function );

		return( -1 );
	}
	if( memory_copy(
	     guid,
	     internal_file->distributed_link_tracker_properties->droid_volume_identifier,
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
	return( 1 );
}

/* Retrieves the droid file identifier
 * Returns 1 if successful or -1 on error
 */
int liblnk_file_get_droid_file_identifier(
     liblnk_file_t *file,
     uint8_t *guid,
     size_t size,
     libcerror_error_t **error )
{
	liblnk_internal_file_t *internal_file = NULL;
	static char *function                 = "liblnk_file_get_droid_file_identifier";

	if( file == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid file.",
		 function );

		return( -1 );
	}
	internal_file = (liblnk_internal_file_t *) file;

	if( internal_file->distributed_link_tracker_properties == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_VALUE_MISSING,
		 "%s: invalid file - missing distributed link tracker properties.",
		 function );

		return( -1 );
	}
	if( guid == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid GUID.",
		 function );

		return( -1 );
	}
	if( size > (size_t) SSIZE_MAX )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_VALUE_EXCEEDS_MAXIMUM,
		 "%s: size value exceeds maximum.",
		 function );

		return( -1 );
	}
	if( size < 16 )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_VALUE_TOO_SMALL,
		 "%s: GUID value too small.",
		 function );

		return( -1 );
	}
	if( memory_copy(
	     guid,
	     internal_file->distributed_link_tracker_properties->droid_file_identifier,
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
	return( 1 );
}

/* Retrieves the birth droid volume identifier
 * Returns 1 if successful or -1 on error
 */
int liblnk_file_get_birth_droid_volume_identifier(
     liblnk_file_t *file,
     uint8_t *guid,
     size_t size,
     libcerror_error_t **error )
{
	liblnk_internal_file_t *internal_file = NULL;
	static char *function                 = "liblnk_file_get_birth_droid_volume_identifier";

	if( file == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid file.",
		 function );

		return( -1 );
	}
	internal_file = (liblnk_internal_file_t *) file;

	if( internal_file->distributed_link_tracker_properties == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_VALUE_MISSING,
		 "%s: invalid file - missing distributed link tracker properties.",
		 function );

		return( -1 );
	}
	if( guid == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid GUID.",
		 function );

		return( -1 );
	}
	if( size > (size_t) SSIZE_MAX )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_VALUE_EXCEEDS_MAXIMUM,
		 "%s: size value exceeds maximum.",
		 function );

		return( -1 );
	}
	if( size < 16 )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_VALUE_TOO_SMALL,
		 "%s: GUID value too small.",
		 function );

		return( -1 );
	}
	if( memory_copy(
	     guid,
	     internal_file->distributed_link_tracker_properties->birth_droid_volume_identifier,
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
	return( 1 );
}

/* Retrieves the birth droid file identifier
 * Returns 1 if successful or -1 on error
 */
int liblnk_file_get_birth_droid_file_identifier(
     liblnk_file_t *file,
     uint8_t *guid,
     size_t size,
     libcerror_error_t **error )
{
	liblnk_internal_file_t *internal_file = NULL;
	static char *function                 = "liblnk_file_get_birth_droid_file_identifier";

	if( file == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid file.",
		 function );

		return( -1 );
	}
	internal_file = (liblnk_internal_file_t *) file;

	if( internal_file->distributed_link_tracker_properties == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_VALUE_MISSING,
		 "%s: invalid file - missing distributed link tracker properties.",
		 function );

		return( -1 );
	}
	if( guid == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid GUID.",
		 function );

		return( -1 );
	}
	if( size > (size_t) SSIZE_MAX )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_VALUE_EXCEEDS_MAXIMUM,
		 "%s: size value exceeds maximum.",
		 function );

		return( -1 );
	}
	if( size < 16 )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_VALUE_TOO_SMALL,
		 "%s: GUID value too small.",
		 function );

		return( -1 );
	}
	if( memory_copy(
	     guid,
	     internal_file->distributed_link_tracker_properties->birth_droid_file_identifier,
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
	return( 1 );
}


