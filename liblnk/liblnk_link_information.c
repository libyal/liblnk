/*
 * Link information functions
 *
 * Copyright (C) 2009-2015, Joachim Metz <joachim.metz@gmail.com>
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
#include "liblnk_file_information.h"
#include "liblnk_libcerror.h"
#include "liblnk_libuna.h"
#include "liblnk_link_information.h"
#include "liblnk_link_target_identifier.h"
#include "liblnk_location_information.h"

/* Retrieves the data flags
 * The data flags contain information about the available link information
 * Returns 1 if successful or -1 on error
 */
int liblnk_file_get_data_flags(
     liblnk_file_t *file,
     uint32_t *data_flags,
     libcerror_error_t **error )
{
	liblnk_internal_file_t *internal_file = NULL;
	static char *function                 = "liblnk_file_get_data_flags";

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
	if( data_flags == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid data flags.",
		 function );

		return( -1 );
	}
	*data_flags = internal_file->io_handle->data_flags;

	return( 1 );
}

/* Determines if the link refers to a file
 * Returns 1 if the link refers to a file, 0 if not or -1 on error
 */
int liblnk_file_link_refers_to_file(
     liblnk_file_t *file,
     libcerror_error_t **error )
{
	liblnk_internal_file_t *internal_file = NULL;
	static char *function                 = "liblnk_file_link_refers_to_file";

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
	if( ( internal_file->io_handle->data_flags & LIBLNK_DATA_FLAG_HAS_LOCATION_INFORMATION ) == 0 )
	{
		return( 0 );
	}
	return( 1 );
}

/* Retrieves the 64-bit filetime value containing the linked file's creation date and time
 * The creation time is only set when the link refers to a file
 * Returns 1 if successful or -1 on error
 */
int liblnk_file_get_file_creation_time(
     liblnk_file_t *file,
     uint64_t *creation_time,
     libcerror_error_t **error )
{
	liblnk_internal_file_t *internal_file = NULL;
	static char *function                 = "liblnk_file_get_file_creation_time";

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

	if( internal_file->file_information == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_VALUE_MISSING,
		 "%s: invalid file - missing file information.",
		 function );

		return( -1 );
	}
	if( creation_time == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid creation time.",
		 function );

		return( -1 );
	}
	*creation_time = internal_file->file_information->creation_time;

	return( 1 );
}

/* Retrieves the 64-bit filetime value containing the linked file's last modification date and time
 * The modification time is only set when the link refers to a file
 * Returns 1 if successful or -1 on error
 */
int liblnk_file_get_file_modification_time(
     liblnk_file_t *file,
     uint64_t *modification_time,
     libcerror_error_t **error )
{
	liblnk_internal_file_t *internal_file = NULL;
	static char *function                 = "liblnk_file_get_file_modification_time";

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

	if( internal_file->file_information == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_VALUE_MISSING,
		 "%s: invalid file - missing file information.",
		 function );

		return( -1 );
	}
	if( modification_time == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid modification time.",
		 function );

		return( -1 );
	}
	*modification_time = internal_file->file_information->modification_time;

	return( 1 );
}

/* Retrieves the 64-bit filetime value containing the linked file's last access date and time
 * The access time is only set when the link refers to a file
 * Returns 1 if successful or -1 on error
 */
int liblnk_file_get_file_access_time(
     liblnk_file_t *file,
     uint64_t *access_time,
     libcerror_error_t **error )
{
	liblnk_internal_file_t *internal_file = NULL;
	static char *function                 = "liblnk_file_get_file_access_time";

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

	if( internal_file->file_information == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_VALUE_MISSING,
		 "%s: invalid file - missing file information.",
		 function );

		return( -1 );
	}
	if( access_time == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid access time.",
		 function );

		return( -1 );
	}
	*access_time = internal_file->file_information->access_time;

	return( 1 );
}

/* Retrieves the linked file's size
 * The file size is only set if the link refers to a file
 * Returns 1 if successful or -1 on error
 */
int liblnk_file_get_file_size(
     liblnk_file_t *file,
     uint32_t *file_size,
     libcerror_error_t **error )
{
	liblnk_internal_file_t *internal_file = NULL;
	static char *function                 = "liblnk_file_get_file_size";

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

	if( internal_file->file_information == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_VALUE_MISSING,
		 "%s: invalid file - missing file information.",
		 function );

		return( -1 );
	}
	if( file_size == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid file size.",
		 function );

		return( -1 );
	}
	*file_size = internal_file->file_information->size;

	return( 1 );
}

/* Retrieves the linked file's attribute flags
 * The file attribute flags are only set if the link refers to a file
 * Returns 1 if successful or -1 on error
 */
int liblnk_file_get_file_attribute_flags(
     liblnk_file_t *file,
     uint32_t *file_attribute_flags,
     libcerror_error_t **error )
{
	liblnk_internal_file_t *internal_file = NULL;
	static char *function                 = "liblnk_file_get_file_attribute_flags";

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

	if( internal_file->file_information == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_VALUE_MISSING,
		 "%s: invalid file - missing file information.",
		 function );

		return( -1 );
	}
	if( file_attribute_flags == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid file attribute flags.",
		 function );

		return( -1 );
	}
	*file_attribute_flags = internal_file->file_information->attribute_flags;

	return( 1 );
}

/* Retrieves the drive type
 * The drive type is only set if the link refers to a file on a local volume
 * Returns 1 if successful, 0 if value is not available or -1 on error
 */
int liblnk_file_get_drive_type(
     liblnk_file_t *file,
     uint32_t *drive_type,
     libcerror_error_t **error )
{
	liblnk_internal_file_t *internal_file = NULL;
	static char *function                 = "liblnk_file_get_drive_type";

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
	if( drive_type == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid drive type.",
		 function );

		return( -1 );
	}
	if( internal_file->location_information == NULL )
	{
		return( 0 );
	}
	*drive_type = internal_file->location_information->drive_type;

	return( 1 );
}

/* Retrieves the drive serial number
 * The drive serial number is only set if the link refers to a file on a local volume
 * Returns 1 if successful, 0 if value is not available or -1 on error
 */
int liblnk_file_get_drive_serial_number(
     liblnk_file_t *file,
     uint32_t *drive_serial_number,
     libcerror_error_t **error )
{
	liblnk_internal_file_t *internal_file = NULL;
	static char *function                 = "liblnk_file_get_drive_serial_number";

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
	if( drive_serial_number == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid drive serial number.",
		 function );

		return( -1 );
	}
	if( internal_file->location_information == NULL )
	{
		return( 0 );
	}
	*drive_serial_number = internal_file->location_information->drive_serial_number;

	return( 1 );
}

/* TODO add raw string functions */

/* Retrieves the size of the UTF-8 encoded volume label
 * The size includes the end of string character
 * The volume label is only set if the link refers to a file on a local volume
 * Returns 1 if successful, 0 if value is not available or -1 on error
 */
int liblnk_file_get_utf8_volume_label_size(
     liblnk_file_t *file,
     size_t *utf8_string_size,
     libcerror_error_t **error )
{
	liblnk_internal_file_t *internal_file = NULL;
	static char *function                 = "liblnk_file_get_utf8_volume_label_size";
	int result                            = 0;

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
	if( utf8_string_size == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid UTF-8 string size.",
		 function );

		return( -1 );
	}
	if( internal_file->location_information == NULL )
	{
		return( 0 );
	}
	if( ( internal_file->location_information->flags & LIBLNK_LOCATION_FLAG_HAS_VOLUME_INFORMATION ) == 0 )
	{
		return( 0 );
	}
	if( ( internal_file->location_information->string_flags & LIBLNK_LOCATION_INFORMATION_STRING_FLAG_VOLUME_LABEL_IS_UNICODE ) != 0 )
	{
		result = libuna_utf8_string_size_from_utf16_stream(
			  internal_file->location_information->volume_label,
			  internal_file->location_information->volume_label_size,
			  LIBUNA_ENDIAN_LITTLE,
			  utf8_string_size,
			  error );
	}
	else
	{
		result = libuna_utf8_string_size_from_byte_stream(
			  internal_file->location_information->volume_label,
			  internal_file->location_information->volume_label_size,
			  internal_file->io_handle->ascii_codepage,
			  utf8_string_size,
			  error );
	}
	if( result != 1 )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_GET_FAILED,
		 "%s: unable to retrieve UTF-8 volume label string size.",
		 function );

		return( -1 );
	}
	return( 1 );
}

/* Retrieves the UTF-8 encoded volume label
 * The size should include the end of string character
 * The volume label is only set if the link refers to a file on a local volume
 * Returns 1 if successful, 0 if value is not available or -1 on error
 */
int liblnk_file_get_utf8_volume_label(
     liblnk_file_t *file,
     uint8_t *utf8_string,
     size_t utf8_string_size,
     libcerror_error_t **error )
{
	liblnk_internal_file_t *internal_file = NULL;
	static char *function                 = "liblnk_file_get_utf8_volume_label";
	size_t string_index                   = 0;
	int result                            = 0;

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
	if( utf8_string == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid UTF-8 string.",
		 function );

		return( -1 );
	}
	if( utf8_string_size > (size_t) SSIZE_MAX )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_VALUE_EXCEEDS_MAXIMUM,
		 "%s: invalid UTF-8 string size value exceeds maximum.",
		 function );

		return( -1 );
	}
	if( internal_file->location_information == NULL )
	{
		return( 0 );
	}
	if( ( internal_file->location_information->flags & LIBLNK_LOCATION_FLAG_HAS_VOLUME_INFORMATION ) == 0 )
	{
		return( 0 );
	}
	if( ( internal_file->location_information->string_flags & LIBLNK_LOCATION_INFORMATION_STRING_FLAG_LOCAL_PATH_IS_UNICODE ) != 0 )
	{
		result = libuna_utf8_string_with_index_copy_from_utf16_stream(
			  utf8_string,
			  utf8_string_size,
			  &string_index,
			  internal_file->location_information->volume_label,
			  internal_file->location_information->volume_label_size,
			  LIBUNA_ENDIAN_LITTLE,
			  error );
	}
	else
	{
		result = libuna_utf8_string_with_index_copy_from_byte_stream(
			  utf8_string,
			  utf8_string_size,
			  &string_index,
			  internal_file->location_information->volume_label,
			  internal_file->location_information->volume_label_size,
			  internal_file->io_handle->ascii_codepage,
			  error );
	}
	if( result != 1 )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_SET_FAILED,
		 "%s: unable to set UTF-8 volume label string.",
		 function );

		return( -1 );
	}
	return( 1 );
}

/* Retrieves the size of the UTF-16 encoded volume label
 * The size includes the end of string character
 * The volume label is only set if the link refers to a file on a local volume
 * Returns 1 if successful, 0 if value is not available or -1 on error
 */
int liblnk_file_get_utf16_volume_label_size(
     liblnk_file_t *file,
     size_t *utf16_string_size,
     libcerror_error_t **error )
{
	liblnk_internal_file_t *internal_file = NULL;
	static char *function                 = "liblnk_file_get_utf16_volume_label_size";
	int result                            = 0;

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
	if( utf16_string_size == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid UTF-16 string size.",
		 function );

		return( -1 );
	}
	if( internal_file->location_information == NULL )
	{
		return( 0 );
	}
	if( ( internal_file->location_information->flags & LIBLNK_LOCATION_FLAG_HAS_VOLUME_INFORMATION ) == 0 )
	{
		return( 0 );
	}
	if( ( internal_file->location_information->string_flags & LIBLNK_LOCATION_INFORMATION_STRING_FLAG_VOLUME_LABEL_IS_UNICODE ) != 0 )
	{
		result = libuna_utf16_string_size_from_utf16_stream(
			  internal_file->location_information->volume_label,
			  internal_file->location_information->volume_label_size,
			  LIBUNA_ENDIAN_LITTLE,
			  utf16_string_size,
			  error );
	}
	else
	{
		result = libuna_utf16_string_size_from_byte_stream(
			  internal_file->location_information->volume_label,
			  internal_file->location_information->volume_label_size,
			  internal_file->io_handle->ascii_codepage,
			  utf16_string_size,
			  error );
	}
	if( result != 1 )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_GET_FAILED,
		 "%s: unable to retrieve UTF-16 volume label string size.",
		 function );

		return( -1 );
	}
	return( 1 );
}

/* Retrieves the UTF-16 encoded volume label
 * The size should include the end of string character
 * The volume label is only set if the link refers to a file on a local volume
 * Returns 1 if successful, 0 if value is not available or -1 on error
 */
int liblnk_file_get_utf16_volume_label(
     liblnk_file_t *file,
     uint16_t *utf16_string,
     size_t utf16_string_size,
     libcerror_error_t **error )
{
	liblnk_internal_file_t *internal_file = NULL;
	static char *function                 = "liblnk_file_get_utf16_volume_label";
	size_t string_index                   = 0;
	int result                            = 0;

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
	if( utf16_string == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid UTF-16 string.",
		 function );

		return( -1 );
	}
	if( utf16_string_size > (size_t) SSIZE_MAX )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_VALUE_EXCEEDS_MAXIMUM,
		 "%s: invalid UTF-16 string size value exceeds maximum.",
		 function );

		return( -1 );
	}
	if( internal_file->location_information == NULL )
	{
		return( 0 );
	}
	if( ( internal_file->location_information->flags & LIBLNK_LOCATION_FLAG_HAS_VOLUME_INFORMATION ) == 0 )
	{
		return( 0 );
	}
	if( ( internal_file->location_information->string_flags & LIBLNK_LOCATION_INFORMATION_STRING_FLAG_LOCAL_PATH_IS_UNICODE ) != 0 )
	{
		result = libuna_utf16_string_with_index_copy_from_utf16_stream(
			  utf16_string,
			  utf16_string_size,
			  &string_index,
			  internal_file->location_information->volume_label,
			  internal_file->location_information->volume_label_size,
			  LIBUNA_ENDIAN_LITTLE,
			  error );
	}
	else
	{
		result = libuna_utf16_string_with_index_copy_from_byte_stream(
			  utf16_string,
			  utf16_string_size,
			  &string_index,
			  internal_file->location_information->volume_label,
			  internal_file->location_information->volume_label_size,
			  internal_file->io_handle->ascii_codepage,
			  error );
	}
	if( result != 1 )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_SET_FAILED,
		 "%s: unable to set UTF-16 volume label string.",
		 function );

		return( -1 );
	}
	return( 1 );
}

/* Retrieves the size of the UTF-8 encoded local path
 * The size includes the end of string character
 * The local path is only set if the link refers to a file on a local volume
 * Returns 1 if successful, 0 if value is not available or -1 on error
 */
int liblnk_file_get_utf8_local_path_size(
     liblnk_file_t *file,
     size_t *utf8_string_size,
     libcerror_error_t **error )
{
	liblnk_internal_file_t *internal_file = NULL;
	static char *function                 = "liblnk_file_get_utf8_local_path_size";
	size_t utf8_common_path_size          = 0;
	size_t utf8_local_path_size           = 0;
	int result                            = 0;

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
	if( utf8_string_size == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid UTF-8 string size.",
		 function );

		return( -1 );
	}
	if( internal_file->location_information == NULL )
	{
		return( 0 );
	}
	if( ( internal_file->location_information->flags & LIBLNK_LOCATION_FLAG_HAS_VOLUME_INFORMATION ) == 0 )
	{
		return( 0 );
	}
	if( ( internal_file->location_information->string_flags & LIBLNK_LOCATION_INFORMATION_STRING_FLAG_LOCAL_PATH_IS_UNICODE ) != 0 )
	{
		result = libuna_utf8_string_size_from_utf16_stream(
			  internal_file->location_information->local_path,
			  internal_file->location_information->local_path_size,
			  LIBUNA_ENDIAN_LITTLE,
			  &utf8_local_path_size,
			  error );
	}
	else
	{
		result = libuna_utf8_string_size_from_byte_stream(
			  internal_file->location_information->local_path,
			  internal_file->location_information->local_path_size,
			  internal_file->io_handle->ascii_codepage,
			  &utf8_local_path_size,
			  error );
	}
	if( result != 1 )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_GET_FAILED,
		 "%s: unable to retrieve UTF-8 local path string size.",
		 function );

		return( -1 );
	}
	result = 0;

	if( ( internal_file->location_information->string_flags & LIBLNK_LOCATION_INFORMATION_STRING_FLAG_LOCAL_PATH_IS_UNICODE ) != 0 )
	{
		if( internal_file->location_information->local_path_size >= 4 )
		{
			if( ( ( internal_file->location_information->local_path )[ internal_file->location_information->local_path_size - 4 ] != (uint8_t) '\\' )
			 || ( ( internal_file->location_information->local_path )[ internal_file->location_information->local_path_size - 3 ] != 0 ) )
			{
				if( ( internal_file->location_information->string_flags & LIBLNK_LOCATION_INFORMATION_STRING_FLAG_COMMON_PATH_IS_UNICODE ) != 0 )
				{
					if( internal_file->location_information->common_path_size > 2 )
					{
						result = 1;
					}
				}
				else
				{
					if( internal_file->location_information->common_path_size > 1 )
					{
						result = 1;
					}
				}
			}
		}
	}
	else
	{
		if( internal_file->location_information->local_path_size >= 2 )
		{
			if( ( internal_file->location_information->local_path )[ internal_file->location_information->local_path_size - 2 ] != (uint8_t) '\\' )
			{
				if( ( internal_file->location_information->string_flags & LIBLNK_LOCATION_INFORMATION_STRING_FLAG_COMMON_PATH_IS_UNICODE ) != 0 )
				{
					if( internal_file->location_information->common_path_size > 2 )
					{
						result = 1;
					}
				}
				else
				{
					if( internal_file->location_information->common_path_size > 1 )
					{
						result = 1;
					}
				}
			}
		}
	}
	if( result != 0 )
	{
		utf8_local_path_size += 1;
	}
	if( ( internal_file->location_information->string_flags & LIBLNK_LOCATION_INFORMATION_STRING_FLAG_COMMON_PATH_IS_UNICODE ) != 0 )
	{
		result = libuna_utf8_string_size_from_utf16_stream(
			  internal_file->location_information->common_path,
			  internal_file->location_information->common_path_size,
			  LIBUNA_ENDIAN_LITTLE,
			  &utf8_common_path_size,
			  error );
	}
	else
	{
		result = libuna_utf8_string_size_from_byte_stream(
			  internal_file->location_information->common_path,
			  internal_file->location_information->common_path_size,
			  internal_file->io_handle->ascii_codepage,
			  &utf8_common_path_size,
			  error );
	}
	if( result != 1 )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_GET_FAILED,
		 "%s: unable to retrieve UTF-8 common path string size.",
		 function );

		return( -1 );
	}
	*utf8_string_size = utf8_local_path_size + utf8_common_path_size - 1;

	return( 1 );
}

/* Retrieves the UTF-8 encoded local path
 * The size should include the end of string character
 * The local path is only set if the link refers to a file on a local volume
 * Returns 1 if successful, 0 if value is not available or -1 on error
 */
int liblnk_file_get_utf8_local_path(
     liblnk_file_t *file,
     uint8_t *utf8_string,
     size_t utf8_string_size,
     libcerror_error_t **error )
{
	liblnk_internal_file_t *internal_file = NULL;
	static char *function                 = "liblnk_file_get_utf8_local_path";
	size_t string_index                   = 0;
	int result                            = 0;

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
	if( utf8_string == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid UTF-8 string.",
		 function );

		return( -1 );
	}
	if( utf8_string_size > (size_t) SSIZE_MAX )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_VALUE_EXCEEDS_MAXIMUM,
		 "%s: invalid UTF-8 string size value exceeds maximum.",
		 function );

		return( -1 );
	}
	if( internal_file->location_information == NULL )
	{
		return( 0 );
	}
	if( ( internal_file->location_information->flags & LIBLNK_LOCATION_FLAG_HAS_VOLUME_INFORMATION ) == 0 )
	{
		return( 0 );
	}
	if( ( internal_file->location_information->string_flags & LIBLNK_LOCATION_INFORMATION_STRING_FLAG_LOCAL_PATH_IS_UNICODE ) != 0 )
	{
		result = libuna_utf8_string_with_index_copy_from_utf16_stream(
			  utf8_string,
			  utf8_string_size,
			  &string_index,
			  internal_file->location_information->local_path,
			  internal_file->location_information->local_path_size,
			  LIBUNA_ENDIAN_LITTLE,
			  error );
	}
	else
	{
		result = libuna_utf8_string_with_index_copy_from_byte_stream(
			  utf8_string,
			  utf8_string_size,
			  &string_index,
			  internal_file->location_information->local_path,
			  internal_file->location_information->local_path_size,
			  internal_file->io_handle->ascii_codepage,
			  error );
	}
	if( result != 1 )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_SET_FAILED,
		 "%s: unable to set UTF-8 local path string.",
		 function );

		return( -1 );
	}
	string_index--;

	result = 0;

	if( ( internal_file->location_information->string_flags & LIBLNK_LOCATION_INFORMATION_STRING_FLAG_LOCAL_PATH_IS_UNICODE ) != 0 )
	{
		if( internal_file->location_information->local_path_size >= 4 )
		{
			if( ( ( internal_file->location_information->local_path )[ internal_file->location_information->local_path_size - 4 ] != (uint8_t) '\\' )
			 || ( ( internal_file->location_information->local_path )[ internal_file->location_information->local_path_size - 3 ] != 0 ) )
			{
				if( ( internal_file->location_information->string_flags & LIBLNK_LOCATION_INFORMATION_STRING_FLAG_COMMON_PATH_IS_UNICODE ) != 0 )
				{
					if( internal_file->location_information->common_path_size > 2 )
					{
						result = 1;
					}
				}
				else
				{
					if( internal_file->location_information->common_path_size > 1 )
					{
						result = 1;
					}
				}
			}
		}
	}
	else
	{
		if( internal_file->location_information->local_path_size >= 2 )
		{
			if( ( internal_file->location_information->local_path )[ internal_file->location_information->local_path_size - 2 ] != (uint8_t) '\\' )
			{
				if( ( internal_file->location_information->string_flags & LIBLNK_LOCATION_INFORMATION_STRING_FLAG_COMMON_PATH_IS_UNICODE ) != 0 )
				{
					if( internal_file->location_information->common_path_size > 2 )
					{
						result = 1;
					}
				}
				else
				{
					if( internal_file->location_information->common_path_size > 1 )
					{
						result = 1;
					}
				}
			}
		}
	}
	if( result != 0 )
	{
		if( ( string_index + 1 ) > utf8_string_size )
		{
			libcerror_error_set(
			 error,
			 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
			 LIBCERROR_ARGUMENT_ERROR_VALUE_TOO_SMALL,
			 "%s: UTF-8 string value too small.",
			 function );

			return( -1 );
		}
		utf8_string[ string_index++ ] = (uint8_t) '\\';
	}
	if( ( internal_file->location_information->string_flags & LIBLNK_LOCATION_INFORMATION_STRING_FLAG_COMMON_PATH_IS_UNICODE ) != 0 )
	{
		result = libuna_utf8_string_with_index_copy_from_utf16_stream(
			  utf8_string,
			  utf8_string_size,
			  &string_index,
			  internal_file->location_information->common_path,
			  internal_file->location_information->common_path_size,
			  LIBUNA_ENDIAN_LITTLE,
			  error );
	}
	else
	{
		result = libuna_utf8_string_with_index_copy_from_byte_stream(
			  utf8_string,
			  utf8_string_size,
			  &string_index,
			  internal_file->location_information->common_path,
			  internal_file->location_information->common_path_size,
			  internal_file->io_handle->ascii_codepage,
			  error );
	}
	if( result != 1 )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_SET_FAILED,
		 "%s: unable to set UTF-8 common path string.",
		 function );

		return( -1 );
	}
	return( 1 );
}

/* Retrieves the size of the UTF-16 encoded local path
 * The size includes the end of string character
 * The local path is only set if the link refers to a file on a local volume
 * Returns 1 if successful, 0 if value is not available or -1 on error
 */
int liblnk_file_get_utf16_local_path_size(
     liblnk_file_t *file,
     size_t *utf16_string_size,
     libcerror_error_t **error )
{
	liblnk_internal_file_t *internal_file = NULL;
	static char *function                 = "liblnk_file_get_utf16_local_path_size";
	size_t utf16_common_path_size         = 0;
	size_t utf16_local_path_size          = 0;
	int result                            = 0;

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
	if( utf16_string_size == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid UTF-16 string size.",
		 function );

		return( -1 );
	}
	if( internal_file->location_information == NULL )
	{
		return( 0 );
	}
	if( ( internal_file->location_information->flags & LIBLNK_LOCATION_FLAG_HAS_VOLUME_INFORMATION ) == 0 )
	{
		return( 0 );
	}
	if( ( internal_file->location_information->string_flags & LIBLNK_LOCATION_INFORMATION_STRING_FLAG_LOCAL_PATH_IS_UNICODE ) != 0 )
	{
		result = libuna_utf16_string_size_from_utf16_stream(
			  internal_file->location_information->local_path,
			  internal_file->location_information->local_path_size,
			  LIBUNA_ENDIAN_LITTLE,
			  &utf16_local_path_size,
			  error );
	}
	else
	{
		result = libuna_utf16_string_size_from_byte_stream(
			  internal_file->location_information->local_path,
			  internal_file->location_information->local_path_size,
			  internal_file->io_handle->ascii_codepage,
			  &utf16_local_path_size,
			  error );
	}
	if( result != 1 )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_GET_FAILED,
		 "%s: unable to retrieve UTF-16 local path string size.",
		 function );

		return( -1 );
	}
	result = 0;

	if( ( internal_file->location_information->string_flags & LIBLNK_LOCATION_INFORMATION_STRING_FLAG_LOCAL_PATH_IS_UNICODE ) != 0 )
	{
		if( internal_file->location_information->local_path_size >= 4 )
		{
			if( ( ( internal_file->location_information->local_path )[ internal_file->location_information->local_path_size - 4 ] != (uint8_t) '\\' )
			 || ( ( internal_file->location_information->local_path )[ internal_file->location_information->local_path_size - 3 ] != 0 ) )
			{
				if( ( internal_file->location_information->string_flags & LIBLNK_LOCATION_INFORMATION_STRING_FLAG_COMMON_PATH_IS_UNICODE ) != 0 )
				{
					if( internal_file->location_information->common_path_size > 2 )
					{
						result = 1;
					}
				}
				else
				{
					if( internal_file->location_information->common_path_size > 1 )
					{
						result = 1;
					}
				}
			}
		}
	}
	else
	{
		if( internal_file->location_information->local_path_size >= 2 )
		{
			if( ( internal_file->location_information->local_path )[ internal_file->location_information->local_path_size - 2 ] != (uint8_t) '\\' )
			{
				if( ( internal_file->location_information->string_flags & LIBLNK_LOCATION_INFORMATION_STRING_FLAG_COMMON_PATH_IS_UNICODE ) != 0 )
				{
					if( internal_file->location_information->common_path_size > 2 )
					{
						result = 1;
					}
				}
				else
				{
					if( internal_file->location_information->common_path_size > 1 )
					{
						result = 1;
					}
				}
			}
		}
	}
	if( result != 0 )
	{
		utf16_local_path_size += 1;
	}
	if( ( internal_file->location_information->string_flags & LIBLNK_LOCATION_INFORMATION_STRING_FLAG_COMMON_PATH_IS_UNICODE ) != 0 )
	{
		result = libuna_utf16_string_size_from_utf16_stream(
			  internal_file->location_information->common_path,
			  internal_file->location_information->common_path_size,
			  LIBUNA_ENDIAN_LITTLE,
			  &utf16_common_path_size,
			  error );
	}
	else
	{
		result = libuna_utf16_string_size_from_byte_stream(
			  internal_file->location_information->common_path,
			  internal_file->location_information->common_path_size,
			  internal_file->io_handle->ascii_codepage,
			  &utf16_common_path_size,
			  error );
	}
	if( result != 1 )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_GET_FAILED,
		 "%s: unable to retrieve UTF-16 common path string size.",
		 function );

		return( -1 );
	}
	*utf16_string_size = utf16_local_path_size + utf16_common_path_size - 1;

	return( 1 );
}

/* Retrieves the UTF-16 encoded local path
 * The size should include the end of string character
 * The local path is only set if the link refers to a file on a local volume
 * Returns 1 if successful, 0 if value is not available or -1 on error
 */
int liblnk_file_get_utf16_local_path(
     liblnk_file_t *file,
     uint16_t *utf16_string,
     size_t utf16_string_size,
     libcerror_error_t **error )
{
	liblnk_internal_file_t *internal_file = NULL;
	static char *function                 = "liblnk_file_get_utf16_local_path";
	size_t string_index                   = 0;
	int result                            = 0;

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
	if( utf16_string == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid UTF-16 string.",
		 function );

		return( -1 );
	}
	if( utf16_string_size > (size_t) SSIZE_MAX )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_VALUE_EXCEEDS_MAXIMUM,
		 "%s: invalid UTF-16 string size value exceeds maximum.",
		 function );

		return( -1 );
	}
	if( internal_file->location_information == NULL )
	{
		return( 0 );
	}
	if( ( internal_file->location_information->flags & LIBLNK_LOCATION_FLAG_HAS_VOLUME_INFORMATION ) == 0 )
	{
		return( 0 );
	}
	if( ( internal_file->location_information->string_flags & LIBLNK_LOCATION_INFORMATION_STRING_FLAG_LOCAL_PATH_IS_UNICODE ) != 0 )
	{
		result = libuna_utf16_string_with_index_copy_from_utf16_stream(
			  utf16_string,
			  utf16_string_size,
			  &string_index,
			  internal_file->location_information->local_path,
			  internal_file->location_information->local_path_size,
			  LIBUNA_ENDIAN_LITTLE,
			  error );
	}
	else
	{
		result = libuna_utf16_string_with_index_copy_from_byte_stream(
			  utf16_string,
			  utf16_string_size,
			  &string_index,
			  internal_file->location_information->local_path,
			  internal_file->location_information->local_path_size,
			  internal_file->io_handle->ascii_codepage,
			  error );
	}
	if( result != 1 )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_SET_FAILED,
		 "%s: unable to set UTF-16 local path string.",
		 function );

		return( -1 );
	}
	string_index--;

	result = 0;

	if( ( internal_file->location_information->string_flags & LIBLNK_LOCATION_INFORMATION_STRING_FLAG_LOCAL_PATH_IS_UNICODE ) != 0 )
	{
		if( internal_file->location_information->local_path_size >= 4 )
		{
			if( ( ( internal_file->location_information->local_path )[ internal_file->location_information->local_path_size - 4 ] != (uint8_t) '\\' )
			 || ( ( internal_file->location_information->local_path )[ internal_file->location_information->local_path_size - 3 ] != 0 ) )
			{
				if( ( internal_file->location_information->string_flags & LIBLNK_LOCATION_INFORMATION_STRING_FLAG_COMMON_PATH_IS_UNICODE ) != 0 )
				{
					if( internal_file->location_information->common_path_size > 2 )
					{
						result = 1;
					}
				}
				else
				{
					if( internal_file->location_information->common_path_size > 1 )
					{
						result = 1;
					}
				}
			}
		}
	}
	else
	{
		if( internal_file->location_information->local_path_size >= 2 )
		{
			if( ( internal_file->location_information->local_path )[ internal_file->location_information->local_path_size - 2 ] != (uint16_t) '\\' )
			{
				if( ( internal_file->location_information->string_flags & LIBLNK_LOCATION_INFORMATION_STRING_FLAG_COMMON_PATH_IS_UNICODE ) != 0 )
				{
					if( internal_file->location_information->common_path_size > 2 )
					{
						result = 1;
					}
				}
				else
				{
					if( internal_file->location_information->common_path_size > 1 )
					{
						result = 1;
					}
				}
			}
		}
	}
	if( result != 0 )
	{
		if( ( string_index + 1 ) > utf16_string_size )
		{
			libcerror_error_set(
			 error,
			 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
			 LIBCERROR_ARGUMENT_ERROR_VALUE_TOO_SMALL,
			 "%s: UTF-16 string value too small.",
			 function );

			return( -1 );
		}
		utf16_string[ string_index++ ] = (uint16_t) '\\';
	}
	if( ( internal_file->location_information->string_flags & LIBLNK_LOCATION_INFORMATION_STRING_FLAG_COMMON_PATH_IS_UNICODE ) != 0 )
	{
		result = libuna_utf16_string_with_index_copy_from_utf16_stream(
			  utf16_string,
			  utf16_string_size,
			  &string_index,
			  internal_file->location_information->common_path,
			  internal_file->location_information->common_path_size,
			  LIBUNA_ENDIAN_LITTLE,
			  error );
	}
	else
	{
		result = libuna_utf16_string_with_index_copy_from_byte_stream(
			  utf16_string,
			  utf16_string_size,
			  &string_index,
			  internal_file->location_information->common_path,
			  internal_file->location_information->common_path_size,
			  internal_file->io_handle->ascii_codepage,
			  error );
	}
	if( result != 1 )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_SET_FAILED,
		 "%s: unable to set UTF-16 common path string.",
		 function );

		return( -1 );
	}
	return( 1 );
}

/* Retrieves the size of the UTF-8 encoded network path
 * The size includes the end of string character
 * The network path is only set if the link refers to a file on a network share
 * Returns 1 if successful, 0 if value is not available or -1 on error
 */
int liblnk_file_get_utf8_network_path_size(
     liblnk_file_t *file,
     size_t *utf8_string_size,
     libcerror_error_t **error )
{
	liblnk_internal_file_t *internal_file = NULL;
	static char *function                 = "liblnk_file_get_utf8_network_path_size";
	size_t utf8_common_path_size          = 0;
	size_t utf8_network_share_name_size   = 0;
	int result                            = 0;

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
	if( utf8_string_size == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid UTF-8 string size.",
		 function );

		return( -1 );
	}
	if( internal_file->location_information == NULL )
	{
		return( 0 );
	}
	if( ( internal_file->location_information->flags & LIBLNK_LOCATION_FLAG_HAS_NETWORK_SHARE_INFORMATION ) == 0 )
	{
		return( 0 );
	}
	if( ( internal_file->location_information->string_flags & LIBLNK_LOCATION_INFORMATION_STRING_FLAG_NETWORK_SHARE_NAME_IS_UNICODE ) != 0 )
	{
		result = libuna_utf8_string_size_from_utf16_stream(
			  internal_file->location_information->network_share_name,
			  internal_file->location_information->network_share_name_size,
			  LIBUNA_ENDIAN_LITTLE,
			  &utf8_network_share_name_size,
			  error );
	}
	else
	{
		result = libuna_utf8_string_size_from_byte_stream(
			  internal_file->location_information->network_share_name,
			  internal_file->location_information->network_share_name_size,
			  internal_file->io_handle->ascii_codepage,
			  &utf8_network_share_name_size,
			  error );
	}
	if( result != 1 )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_GET_FAILED,
		 "%s: unable to retrieve UTF-8 network share name string size.",
		 function );

		return( -1 );
	}
	result = 0;

	if( ( internal_file->location_information->string_flags & LIBLNK_LOCATION_INFORMATION_STRING_FLAG_NETWORK_SHARE_NAME_IS_UNICODE ) != 0 )
	{
		if( internal_file->location_information->network_share_name_size >= 4 )
		{
			if( ( ( internal_file->location_information->network_share_name )[ internal_file->location_information->network_share_name_size - 4 ] != (uint8_t) '\\' )
			 || ( ( internal_file->location_information->network_share_name )[ internal_file->location_information->network_share_name_size - 3 ] != 0 ) )
			{
				if( ( internal_file->location_information->string_flags & LIBLNK_LOCATION_INFORMATION_STRING_FLAG_COMMON_PATH_IS_UNICODE ) != 0 )
				{
					if( internal_file->location_information->common_path_size > 2 )
					{
						result = 1;
					}
				}
				else
				{
					if( internal_file->location_information->common_path_size > 1 )
					{
						result = 1;
					}
				}
			}
		}
	}
	else
	{
		if( internal_file->location_information->network_share_name_size >= 2 )
		{
			if( ( internal_file->location_information->network_share_name )[ internal_file->location_information->network_share_name_size - 2 ] != (uint8_t) '\\' )
			{
				if( ( internal_file->location_information->string_flags & LIBLNK_LOCATION_INFORMATION_STRING_FLAG_COMMON_PATH_IS_UNICODE ) != 0 )
				{
					if( internal_file->location_information->common_path_size > 2 )
					{
						result = 1;
					}
				}
				else
				{
					if( internal_file->location_information->common_path_size > 1 )
					{
						result = 1;
					}
				}
			}
		}
	}
	if( result != 0 )
	{
		utf8_network_share_name_size += 1;
	}
	if( ( internal_file->location_information->string_flags & LIBLNK_LOCATION_INFORMATION_STRING_FLAG_COMMON_PATH_IS_UNICODE ) != 0 )
	{
		result = libuna_utf8_string_size_from_utf16_stream(
			  internal_file->location_information->common_path,
			  internal_file->location_information->common_path_size,
			  LIBUNA_ENDIAN_LITTLE,
			  &utf8_common_path_size,
			  error );
	}
	else
	{
		result = libuna_utf8_string_size_from_byte_stream(
			  internal_file->location_information->common_path,
			  internal_file->location_information->common_path_size,
			  internal_file->io_handle->ascii_codepage,
			  &utf8_common_path_size,
			  error );
	}
	if( result != 1 )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_GET_FAILED,
		 "%s: unable to retrieve UTF-8 common path string size.",
		 function );

		return( -1 );
	}
	*utf8_string_size = utf8_network_share_name_size + utf8_common_path_size - 1;

	return( 1 );
}

/* Retrieves the UTF-8 encoded network path
 * The size should include the end of string character
 * The network path is only set if the link refers to a file on a network share
 * Returns 1 if successful, 0 if value is not available or -1 on error
 */
int liblnk_file_get_utf8_network_path(
     liblnk_file_t *file,
     uint8_t *utf8_string,
     size_t utf8_string_size,
     libcerror_error_t **error )
{
	liblnk_internal_file_t *internal_file = NULL;
	static char *function                 = "liblnk_file_get_utf8_network_path";
	size_t string_index                   = 0;
	int result                            = 0;

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
	if( utf8_string == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid UTF-8 string.",
		 function );

		return( -1 );
	}
	if( utf8_string_size > (size_t) SSIZE_MAX )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_VALUE_EXCEEDS_MAXIMUM,
		 "%s: invalid UTF-8 string size value exceeds maximum.",
		 function );

		return( -1 );
	}
	if( internal_file->location_information == NULL )
	{
		return( 0 );
	}
	if( ( internal_file->location_information->flags & LIBLNK_LOCATION_FLAG_HAS_NETWORK_SHARE_INFORMATION ) == 0 )
	{
		return( 0 );
	}
	if( ( internal_file->location_information->string_flags & LIBLNK_LOCATION_INFORMATION_STRING_FLAG_NETWORK_SHARE_NAME_IS_UNICODE ) != 0 )
	{
		result = libuna_utf8_string_with_index_copy_from_utf16_stream(
			  utf8_string,
			  utf8_string_size,
			  &string_index,
			  internal_file->location_information->network_share_name,
			  internal_file->location_information->network_share_name_size,
			  LIBUNA_ENDIAN_LITTLE,
			  error );
	}
	else
	{
		result = libuna_utf8_string_with_index_copy_from_byte_stream(
			  utf8_string,
			  utf8_string_size,
			  &string_index,
			  internal_file->location_information->network_share_name,
			  internal_file->location_information->network_share_name_size,
			  internal_file->io_handle->ascii_codepage,
			  error );
	}
	if( result != 1 )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_SET_FAILED,
		 "%s: unable to set UTF-8 network share name string.",
		 function );

		return( -1 );
	}
	string_index--;

	result = 0;

	if( ( internal_file->location_information->string_flags & LIBLNK_LOCATION_INFORMATION_STRING_FLAG_NETWORK_SHARE_NAME_IS_UNICODE ) != 0 )
	{
		if( internal_file->location_information->network_share_name_size >= 4 )
		{
			if( ( ( internal_file->location_information->network_share_name )[ internal_file->location_information->network_share_name_size - 4 ] != (uint8_t) '\\' )
			 || ( ( internal_file->location_information->network_share_name )[ internal_file->location_information->network_share_name_size - 3 ] != 0 ) )
			{
				if( ( internal_file->location_information->string_flags & LIBLNK_LOCATION_INFORMATION_STRING_FLAG_COMMON_PATH_IS_UNICODE ) != 0 )
				{
					if( internal_file->location_information->common_path_size > 2 )
					{
						result = 1;
					}
				}
				else
				{
					if( internal_file->location_information->common_path_size > 1 )
					{
						result = 1;
					}
				}
			}
		}
	}
	else
	{
		if( internal_file->location_information->network_share_name_size >= 2 )
		{
			if( ( internal_file->location_information->network_share_name )[ internal_file->location_information->network_share_name_size - 2 ] != (uint8_t) '\\' )
			{
				if( ( internal_file->location_information->string_flags & LIBLNK_LOCATION_INFORMATION_STRING_FLAG_COMMON_PATH_IS_UNICODE ) != 0 )
				{
					if( internal_file->location_information->common_path_size > 2 )
					{
						result = 1;
					}
				}
				else
				{
					if( internal_file->location_information->common_path_size > 1 )
					{
						result = 1;
					}
				}
			}
		}
	}
	if( result != 0 )
	{
		if( ( string_index + 1 ) > utf8_string_size )
		{
			libcerror_error_set(
			 error,
			 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
			 LIBCERROR_ARGUMENT_ERROR_VALUE_TOO_SMALL,
			 "%s: UTF-8 string value too small.",
			 function );

			return( -1 );
		}
		utf8_string[ string_index++ ] = (uint8_t) '\\';
	}
	if( ( internal_file->location_information->string_flags & LIBLNK_LOCATION_INFORMATION_STRING_FLAG_COMMON_PATH_IS_UNICODE ) != 0 )
	{
		result = libuna_utf8_string_with_index_copy_from_utf16_stream(
			  utf8_string,
			  utf8_string_size,
		          &string_index,
			  internal_file->location_information->common_path,
			  internal_file->location_information->common_path_size,
			  LIBUNA_ENDIAN_LITTLE,
			  error );
	}
	else
	{
		result = libuna_utf8_string_with_index_copy_from_byte_stream(
			  utf8_string,
			  utf8_string_size,
		          &string_index,
			  internal_file->location_information->common_path,
			  internal_file->location_information->common_path_size,
			  internal_file->io_handle->ascii_codepage,
			  error );
	}
	if( result != 1 )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_SET_FAILED,
		 "%s: unable to set UTF-8 common path string.",
		 function );

		return( -1 );
	}
	return( 1 );
}

/* Retrieves the size of the UTF-16 encoded network path
 * The size includes the end of string character
 * The network path is only set if the link refers to a file on a network share
 * Returns 1 if successful, 0 if value is not available or -1 on error
 */
int liblnk_file_get_utf16_network_path_size(
     liblnk_file_t *file,
     size_t *utf16_string_size,
     libcerror_error_t **error )
{
	liblnk_internal_file_t *internal_file = NULL;
	static char *function                 = "liblnk_file_get_utf16_network_path_size";
	size_t utf16_common_path_size         = 0;
	size_t utf16_network_share_name_size  = 0;
	int result                            = 0;

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
	if( utf16_string_size == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid UTF-16 string size.",
		 function );

		return( -1 );
	}
	if( internal_file->location_information == NULL )
	{
		return( 0 );
	}
	if( ( internal_file->location_information->flags & LIBLNK_LOCATION_FLAG_HAS_NETWORK_SHARE_INFORMATION ) == 0 )
	{
		return( 0 );
	}
	if( ( internal_file->location_information->string_flags & LIBLNK_LOCATION_INFORMATION_STRING_FLAG_NETWORK_SHARE_NAME_IS_UNICODE ) != 0 )
	{
		result = libuna_utf16_string_size_from_utf16_stream(
			  internal_file->location_information->network_share_name,
			  internal_file->location_information->network_share_name_size,
			  LIBUNA_ENDIAN_LITTLE,
			  &utf16_network_share_name_size,
			  error );
	}
	else
	{
		result = libuna_utf16_string_size_from_byte_stream(
			  internal_file->location_information->network_share_name,
			  internal_file->location_information->network_share_name_size,
			  internal_file->io_handle->ascii_codepage,
			  &utf16_network_share_name_size,
			  error );
	}
	if( result != 1 )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_GET_FAILED,
		 "%s: unable to retrieve UTF-16 network share name string size.",
		 function );

		return( -1 );
	}
	result = 0;

	if( ( internal_file->location_information->string_flags & LIBLNK_LOCATION_INFORMATION_STRING_FLAG_NETWORK_SHARE_NAME_IS_UNICODE ) != 0 )
	{
		if( internal_file->location_information->network_share_name_size >= 4 )
		{
			if( ( ( internal_file->location_information->network_share_name )[ internal_file->location_information->network_share_name_size - 4 ] != (uint8_t) '\\' )
			 || ( ( internal_file->location_information->network_share_name )[ internal_file->location_information->network_share_name_size - 3 ] != 0 ) )
			{
				if( ( internal_file->location_information->string_flags & LIBLNK_LOCATION_INFORMATION_STRING_FLAG_COMMON_PATH_IS_UNICODE ) != 0 )
				{
					if( internal_file->location_information->common_path_size > 2 )
					{
						result = 1;
					}
				}
				else
				{
					if( internal_file->location_information->common_path_size > 1 )
					{
						result = 1;
					}
				}
			}
		}
	}
	else
	{
		if( internal_file->location_information->network_share_name_size >= 2 )
		{
			if( ( internal_file->location_information->network_share_name )[ internal_file->location_information->network_share_name_size - 2 ] != (uint8_t) '\\' )
			{
				if( ( internal_file->location_information->string_flags & LIBLNK_LOCATION_INFORMATION_STRING_FLAG_COMMON_PATH_IS_UNICODE ) != 0 )
				{
					if( internal_file->location_information->common_path_size > 2 )
					{
						result = 1;
					}
				}
				else
				{
					if( internal_file->location_information->common_path_size > 1 )
					{
						result = 1;
					}
				}
			}
		}
	}
	if( result != 0 )
	{
		utf16_network_share_name_size += 1;
	}
	if( ( internal_file->location_information->string_flags & LIBLNK_LOCATION_INFORMATION_STRING_FLAG_COMMON_PATH_IS_UNICODE ) != 0 )
	{
		result = libuna_utf16_string_size_from_utf16_stream(
			  internal_file->location_information->common_path,
			  internal_file->location_information->common_path_size,
			  LIBUNA_ENDIAN_LITTLE,
			  &utf16_common_path_size,
			  error );
	}
	else
	{
		result = libuna_utf16_string_size_from_byte_stream(
			  internal_file->location_information->common_path,
			  internal_file->location_information->common_path_size,
			  internal_file->io_handle->ascii_codepage,
			  &utf16_common_path_size,
			  error );
	}
	if( result != 1 )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_GET_FAILED,
		 "%s: unable to retrieve UTF-16 common path string size.",
		 function );

		return( -1 );
	}
	*utf16_string_size = utf16_network_share_name_size + utf16_common_path_size - 1;

	return( 1 );
}

/* Retrieves the UTF-16 encoded network path
 * The size should include the end of string character
 * The network path is only set if the link refers to a file on a network share
 * Returns 1 if successful, 0 if value is not available or -1 on error
 */
int liblnk_file_get_utf16_network_path(
     liblnk_file_t *file,
     uint16_t *utf16_string,
     size_t utf16_string_size,
     libcerror_error_t **error )
{
	liblnk_internal_file_t *internal_file = NULL;
	static char *function                 = "liblnk_file_get_utf16_network_path";
	size_t string_index                   = 0;
	int result                            = 0;

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
	if( utf16_string == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid UTF-16 string.",
		 function );

		return( -1 );
	}
	if( utf16_string_size > (size_t) SSIZE_MAX )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_VALUE_EXCEEDS_MAXIMUM,
		 "%s: invalid UTF-16 string size value exceeds maximum.",
		 function );

		return( -1 );
	}
	if( internal_file->location_information == NULL )
	{
		return( 0 );
	}
	if( ( internal_file->location_information->flags & LIBLNK_LOCATION_FLAG_HAS_NETWORK_SHARE_INFORMATION ) == 0 )
	{
		return( 0 );
	}
	if( ( internal_file->location_information->string_flags & LIBLNK_LOCATION_INFORMATION_STRING_FLAG_NETWORK_SHARE_NAME_IS_UNICODE ) != 0 )
	{
		result = libuna_utf16_string_with_index_copy_from_utf16_stream(
			  utf16_string,
			  utf16_string_size,
			  &string_index,
			  internal_file->location_information->network_share_name,
			  internal_file->location_information->network_share_name_size,
			  LIBUNA_ENDIAN_LITTLE,
			  error );
	}
	else
	{
		result = libuna_utf16_string_with_index_copy_from_byte_stream(
			  utf16_string,
			  utf16_string_size,
			  &string_index,
			  internal_file->location_information->network_share_name,
			  internal_file->location_information->network_share_name_size,
			  internal_file->io_handle->ascii_codepage,
			  error );
	}
	if( result != 1 )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_SET_FAILED,
		 "%s: unable to set UTF-16 network share name string.",
		 function );

		return( -1 );
	}
	string_index--;

	result = 0;

	if( ( internal_file->location_information->string_flags & LIBLNK_LOCATION_INFORMATION_STRING_FLAG_NETWORK_SHARE_NAME_IS_UNICODE ) != 0 )
	{
		if( internal_file->location_information->network_share_name_size >= 4 )
		{
			if( ( ( internal_file->location_information->network_share_name )[ internal_file->location_information->network_share_name_size - 4 ] != (uint8_t) '\\' )
			 || ( ( internal_file->location_information->network_share_name )[ internal_file->location_information->network_share_name_size - 3 ] != 0 ) )
			{
				if( ( internal_file->location_information->string_flags & LIBLNK_LOCATION_INFORMATION_STRING_FLAG_COMMON_PATH_IS_UNICODE ) != 0 )
				{
					if( internal_file->location_information->common_path_size > 2 )
					{
						result = 1;
					}
				}
				else
				{
					if( internal_file->location_information->common_path_size > 1 )
					{
						result = 1;
					}
				}
			}
		}
	}
	else
	{
		if( internal_file->location_information->network_share_name_size >= 2 )
		{
			if( ( internal_file->location_information->network_share_name )[ internal_file->location_information->network_share_name_size - 2 ] != (uint8_t) '\\' )
			{
				if( ( internal_file->location_information->string_flags & LIBLNK_LOCATION_INFORMATION_STRING_FLAG_COMMON_PATH_IS_UNICODE ) != 0 )
				{
					if( internal_file->location_information->common_path_size > 2 )
					{
						result = 1;
					}
				}
				else
				{
					if( internal_file->location_information->common_path_size > 1 )
					{
						result = 1;
					}
				}
			}
		}
	}
	if( result != 0 )
	{
		if( ( string_index + 1 ) > utf16_string_size )
		{
			libcerror_error_set(
			 error,
			 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
			 LIBCERROR_ARGUMENT_ERROR_VALUE_TOO_SMALL,
			 "%s: UTF-16 string value too small.",
			 function );

			return( -1 );
		}
		utf16_string[ string_index++ ] = (uint16_t) '\\';
	}
	if( ( internal_file->location_information->string_flags & LIBLNK_LOCATION_INFORMATION_STRING_FLAG_COMMON_PATH_IS_UNICODE ) != 0 )
	{
		result = libuna_utf16_string_with_index_copy_from_utf16_stream(
			  utf16_string,
			  utf16_string_size,
			  &string_index,
			  internal_file->location_information->common_path,
			  internal_file->location_information->common_path_size,
			  LIBUNA_ENDIAN_LITTLE,
			  error );
	}
	else
	{
		result = libuna_utf16_string_with_index_copy_from_byte_stream(
			  utf16_string,
			  utf16_string_size,
			  &string_index,
			  internal_file->location_information->common_path,
			  internal_file->location_information->common_path_size,
			  internal_file->io_handle->ascii_codepage,
			  error );
	}
	if( result != 1 )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_SET_FAILED,
		 "%s: unable to set UTF-16 common path string.",
		 function );

		return( -1 );
	}
	return( 1 );
}

/* Retrieves the size of the UTF-8 encoded description
 * The size includes the end of string character
 * Returns 1 if successful, 0 if value is not available or -1 on error
 */
int liblnk_file_get_utf8_description_size(
     liblnk_file_t *file,
     size_t *utf8_string_size,
     libcerror_error_t **error )
{
	liblnk_internal_file_t *internal_file = NULL;
	static char *function                 = "liblnk_file_get_utf8_description_size";

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
	if( internal_file->description == NULL )
	{
		return( 0 );
	}
	if( liblnk_data_string_get_utf8_string_size(
	     internal_file->description,
	     internal_file->io_handle->ascii_codepage,
	     utf8_string_size,
	     error ) != 1 )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_GET_FAILED,
		 "%s: unable to retrieve UTF-8 data string size.",
		 function );

		return( -1 );
	}
	return( 1 );
}

/* Retrieves the UTF-8 encoded description
 * The size should include the end of string character
 * Returns 1 if successful, 0 if value is not available or -1 on error
 */
int liblnk_file_get_utf8_description(
     liblnk_file_t *file,
     uint8_t *utf8_string,
     size_t utf8_string_size,
     libcerror_error_t **error )
{
	liblnk_internal_file_t *internal_file = NULL;
	static char *function                 = "liblnk_file_get_utf8_description";

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
	if( internal_file->description == NULL )
	{
		return( 0 );
	}
	if( liblnk_data_string_get_utf8_string(
	     internal_file->description,
	     internal_file->io_handle->ascii_codepage,
	     utf8_string,
	     utf8_string_size,
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

/* Retrieves the size of the UTF-16 encoded description
 * The size includes the end of string character
 * Returns 1 if successful, 0 if value is not available or -1 on error
 */
int liblnk_file_get_utf16_description_size(
     liblnk_file_t *file,
     size_t *utf16_string_size,
     libcerror_error_t **error )
{
	liblnk_internal_file_t *internal_file = NULL;
	static char *function                 = "liblnk_file_get_utf16_description_size";

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
	if( internal_file->description == NULL )
	{
		return( 0 );
	}
	if( liblnk_data_string_get_utf16_string_size(
	     internal_file->description,
	     internal_file->io_handle->ascii_codepage,
	     utf16_string_size,
	     error ) != 1 )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_GET_FAILED,
		 "%s: unable to retrieve UTF-16 data string size.",
		 function );

		return( -1 );
	}
	return( 1 );
}

/* Retrieves the UTF-16 encoded description
 * The size should include the end of string character
 * Returns 1 if successful, 0 if value is not available or -1 on error
 */
int liblnk_file_get_utf16_description(
     liblnk_file_t *file,
     uint16_t *utf16_string,
     size_t utf16_string_size,
     libcerror_error_t **error )
{
	liblnk_internal_file_t *internal_file = NULL;
	static char *function                 = "liblnk_file_get_utf16_description";

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
	if( internal_file->description == NULL )
	{
		return( 0 );
	}
	if( liblnk_data_string_get_utf16_string(
	     internal_file->description,
	     internal_file->io_handle->ascii_codepage,
	     utf16_string,
	     utf16_string_size,
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

/* Retrieves the size of the UTF-8 encoded relative path
 * The size includes the end of string character
 * Returns 1 if successful, 0 if value is not available or -1 on error
 */
int liblnk_file_get_utf8_relative_path_size(
     liblnk_file_t *file,
     size_t *utf8_string_size,
     libcerror_error_t **error )
{
	liblnk_internal_file_t *internal_file = NULL;
	static char *function                 = "liblnk_file_get_utf8_relative_path_size";

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
	if( internal_file->relative_path == NULL )
	{
		return( 0 );
	}
	if( liblnk_data_string_get_utf8_string_size(
	     internal_file->relative_path,
	     internal_file->io_handle->ascii_codepage,
	     utf8_string_size,
	     error ) != 1 )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_GET_FAILED,
		 "%s: unable to retrieve UTF-8 data string size.",
		 function );

		return( -1 );
	}
	return( 1 );
}

/* Retrieves the UTF-8 encoded relative path
 * The size should include the end of string character
 * Returns 1 if successful, 0 if value is not available or -1 on error
 */
int liblnk_file_get_utf8_relative_path(
     liblnk_file_t *file,
     uint8_t *utf8_string,
     size_t utf8_string_size,
     libcerror_error_t **error )
{
	liblnk_internal_file_t *internal_file = NULL;
	static char *function                 = "liblnk_file_get_utf8_relative_path";

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
	if( internal_file->relative_path == NULL )
	{
		return( 0 );
	}
	if( liblnk_data_string_get_utf8_string(
	     internal_file->relative_path,
	     internal_file->io_handle->ascii_codepage,
	     utf8_string,
	     utf8_string_size,
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

/* Retrieves the size of the UTF-16 encoded relative path
 * The size includes the end of string character
 * Returns 1 if successful, 0 if value is not available or -1 on error
 */
int liblnk_file_get_utf16_relative_path_size(
     liblnk_file_t *file,
     size_t *utf16_string_size,
     libcerror_error_t **error )
{
	liblnk_internal_file_t *internal_file = NULL;
	static char *function                 = "liblnk_file_get_utf16_relative_path_size";

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
	if( internal_file->relative_path == NULL )
	{
		return( 0 );
	}
	if( liblnk_data_string_get_utf16_string_size(
	     internal_file->relative_path,
	     internal_file->io_handle->ascii_codepage,
	     utf16_string_size,
	     error ) != 1 )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_GET_FAILED,
		 "%s: unable to retrieve UTF-16 data string size.",
		 function );

		return( -1 );
	}
	return( 1 );
}

/* Retrieves the UTF-16 encoded relative path
 * The size should include the end of string character
 * Returns 1 if successful, 0 if value is not available or -1 on error
 */
int liblnk_file_get_utf16_relative_path(
     liblnk_file_t *file,
     uint16_t *utf16_string,
     size_t utf16_string_size,
     libcerror_error_t **error )
{
	liblnk_internal_file_t *internal_file = NULL;
	static char *function                 = "liblnk_file_get_utf16_relative_path";

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
	if( internal_file->relative_path == NULL )
	{
		return( 0 );
	}
	if( liblnk_data_string_get_utf16_string(
	     internal_file->relative_path,
	     internal_file->io_handle->ascii_codepage,
	     utf16_string,
	     utf16_string_size,
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

/* Retrieves the size of the UTF-8 encoded working directory
 * The size includes the end of string character
 * Returns 1 if successful, 0 if value is not available or -1 on error
 */
int liblnk_file_get_utf8_working_directory_size(
     liblnk_file_t *file,
     size_t *utf8_string_size,
     libcerror_error_t **error )
{
	liblnk_internal_file_t *internal_file = NULL;
	static char *function                 = "liblnk_file_get_utf8_working_directory_size";

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
	if( internal_file->working_directory == NULL )
	{
		return( 0 );
	}
	if( liblnk_data_string_get_utf8_string_size(
	     internal_file->working_directory,
	     internal_file->io_handle->ascii_codepage,
	     utf8_string_size,
	     error ) != 1 )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_GET_FAILED,
		 "%s: unable to retrieve UTF-8 data string size.",
		 function );

		return( -1 );
	}
	return( 1 );
}

/* Retrieves the UTF-8 encoded working directory
 * The size should include the end of string character
 * Returns 1 if successful, 0 if value is not available or -1 on error
 */
int liblnk_file_get_utf8_working_directory(
     liblnk_file_t *file,
     uint8_t *utf8_string,
     size_t utf8_string_size,
     libcerror_error_t **error )
{
	liblnk_internal_file_t *internal_file = NULL;
	static char *function                 = "liblnk_file_get_utf8_working_directory";

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
	if( internal_file->working_directory == NULL )
	{
		return( 0 );
	}
	if( liblnk_data_string_get_utf8_string(
	     internal_file->working_directory,
	     internal_file->io_handle->ascii_codepage,
	     utf8_string,
	     utf8_string_size,
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

/* Retrieves the size of the UTF-16 encoded working directory
 * The size includes the end of string character
 * Returns 1 if successful, 0 if value is not available or -1 on error
 */
int liblnk_file_get_utf16_working_directory_size(
     liblnk_file_t *file,
     size_t *utf16_string_size,
     libcerror_error_t **error )
{
	liblnk_internal_file_t *internal_file = NULL;
	static char *function                 = "liblnk_file_get_utf16_working_directory_size";

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
	if( internal_file->working_directory == NULL )
	{
		return( 0 );
	}
	if( liblnk_data_string_get_utf16_string_size(
	     internal_file->working_directory,
	     internal_file->io_handle->ascii_codepage,
	     utf16_string_size,
	     error ) != 1 )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_GET_FAILED,
		 "%s: unable to retrieve UTF-16 data string size.",
		 function );

		return( -1 );
	}
	return( 1 );
}

/* Retrieves the UTF-16 encoded working directory
 * The size should include the end of string character
 * Returns 1 if successful, 0 if value is not available or -1 on error
 */
int liblnk_file_get_utf16_working_directory(
     liblnk_file_t *file,
     uint16_t *utf16_string,
     size_t utf16_string_size,
     libcerror_error_t **error )
{
	liblnk_internal_file_t *internal_file = NULL;
	static char *function                 = "liblnk_file_get_utf16_working_directory";

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
	if( internal_file->working_directory == NULL )
	{
		return( 0 );
	}
	if( liblnk_data_string_get_utf16_string(
	     internal_file->working_directory,
	     internal_file->io_handle->ascii_codepage,
	     utf16_string,
	     utf16_string_size,
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

/* Retrieves the size of the UTF-8 encoded command line arguments
 * The size includes the end of string character
 * Returns 1 if successful, 0 if value is not available or -1 on error
 */
int liblnk_file_get_utf8_command_line_arguments_size(
     liblnk_file_t *file,
     size_t *utf8_string_size,
     libcerror_error_t **error )
{
	liblnk_internal_file_t *internal_file = NULL;
	static char *function                 = "liblnk_file_get_utf8_command_line_arguments_size";

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
	if( internal_file->command_line_arguments == NULL )
	{
		return( 0 );
	}
	if( liblnk_data_string_get_utf8_string_size(
	     internal_file->command_line_arguments,
	     internal_file->io_handle->ascii_codepage,
	     utf8_string_size,
	     error ) != 1 )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_GET_FAILED,
		 "%s: unable to retrieve UTF-8 data string size.",
		 function );

		return( -1 );
	}
	return( 1 );
}

/* Retrieves the UTF-8 encoded command line arguments
 * The size should include the end of string character
 * Returns 1 if successful, 0 if value is not available or -1 on error
 */
int liblnk_file_get_utf8_command_line_arguments(
     liblnk_file_t *file,
     uint8_t *utf8_string,
     size_t utf8_string_size,
     libcerror_error_t **error )
{
	liblnk_internal_file_t *internal_file = NULL;
	static char *function                 = "liblnk_file_get_utf8_command_line_arguments";

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
	if( internal_file->command_line_arguments == NULL )
	{
		return( 0 );
	}
	if( liblnk_data_string_get_utf8_string(
	     internal_file->command_line_arguments,
	     internal_file->io_handle->ascii_codepage,
	     utf8_string,
	     utf8_string_size,
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

/* Retrieves the size of the UTF-16 encoded command line arguments
 * The size includes the end of string character
 * Returns 1 if successful, 0 if value is not available or -1 on error
 */
int liblnk_file_get_utf16_command_line_arguments_size(
     liblnk_file_t *file,
     size_t *utf16_string_size,
     libcerror_error_t **error )
{
	liblnk_internal_file_t *internal_file = NULL;
	static char *function                 = "liblnk_file_get_utf16_command_line_arguments_size";

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
	if( internal_file->command_line_arguments == NULL )
	{
		return( 0 );
	}
	if( liblnk_data_string_get_utf16_string_size(
	     internal_file->command_line_arguments,
	     internal_file->io_handle->ascii_codepage,
	     utf16_string_size,
	     error ) != 1 )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_GET_FAILED,
		 "%s: unable to retrieve UTF-16 data string size.",
		 function );

		return( -1 );
	}
	return( 1 );
}

/* Retrieves the UTF-16 encoded command line arguments
 * The size should include the end of string character
 * Returns 1 if successful, 0 if value is not available or -1 on error
 */
int liblnk_file_get_utf16_command_line_arguments(
     liblnk_file_t *file,
     uint16_t *utf16_string,
     size_t utf16_string_size,
     libcerror_error_t **error )
{
	liblnk_internal_file_t *internal_file = NULL;
	static char *function                 = "liblnk_file_get_utf16_command_line_arguments";

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
	if( internal_file->command_line_arguments == NULL )
	{
		return( 0 );
	}
	if( liblnk_data_string_get_utf16_string(
	     internal_file->command_line_arguments,
	     internal_file->io_handle->ascii_codepage,
	     utf16_string,
	     utf16_string_size,
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

/* Retrieves the size of the UTF-8 encoded icon location
 * The size includes the end of string character
 * Returns 1 if successful, 0 if value is not available or -1 on error
 */
int liblnk_file_get_utf8_icon_location_size(
     liblnk_file_t *file,
     size_t *utf8_string_size,
     libcerror_error_t **error )
{
	liblnk_internal_file_t *internal_file = NULL;
	static char *function                 = "liblnk_file_get_utf8_icon_location_size";

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
	if( internal_file->icon_location == NULL )
	{
		return( 0 );
	}
	if( liblnk_data_string_get_utf8_string_size(
	     internal_file->icon_location,
	     internal_file->io_handle->ascii_codepage,
	     utf8_string_size,
	     error ) != 1 )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_GET_FAILED,
		 "%s: unable to retrieve UTF-8 data string size.",
		 function );

		return( -1 );
	}
	return( 1 );
}

/* Retrieves the UTF-8 encoded icon location
 * The size should include the end of string character
 * Returns 1 if successful, 0 if value is not available or -1 on error
 */
int liblnk_file_get_utf8_icon_location(
     liblnk_file_t *file,
     uint8_t *utf8_string,
     size_t utf8_string_size,
     libcerror_error_t **error )
{
	liblnk_internal_file_t *internal_file = NULL;
	static char *function                 = "liblnk_file_get_utf8_icon_location";

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
	if( internal_file->icon_location == NULL )
	{
		return( 0 );
	}
	if( liblnk_data_string_get_utf8_string(
	     internal_file->icon_location,
	     internal_file->io_handle->ascii_codepage,
	     utf8_string,
	     utf8_string_size,
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

/* Retrieves the size of the UTF-16 encoded icon location
 * The size includes the end of string character
 * Returns 1 if successful, 0 if value is not available or -1 on error
 */
int liblnk_file_get_utf16_icon_location_size(
     liblnk_file_t *file,
     size_t *utf16_string_size,
     libcerror_error_t **error )
{
	liblnk_internal_file_t *internal_file = NULL;
	static char *function                 = "liblnk_file_get_utf16_icon_location_size";

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
	if( internal_file->icon_location == NULL )
	{
		return( 0 );
	}
	if( liblnk_data_string_get_utf16_string_size(
	     internal_file->icon_location,
	     internal_file->io_handle->ascii_codepage,
	     utf16_string_size,
	     error ) != 1 )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_GET_FAILED,
		 "%s: unable to retrieve UTF-16 data string size.",
		 function );

		return( -1 );
	}
	return( 1 );
}

/* Retrieves the UTF-16 encoded icon location
 * The size should include the end of string character
 * Returns 1 if successful, 0 if value is not available or -1 on error
 */
int liblnk_file_get_utf16_icon_location(
     liblnk_file_t *file,
     uint16_t *utf16_string,
     size_t utf16_string_size,
     libcerror_error_t **error )
{
	liblnk_internal_file_t *internal_file = NULL;
	static char *function                 = "liblnk_file_get_utf16_icon_location";

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
	if( internal_file->icon_location == NULL )
	{
		return( 0 );
	}
	if( liblnk_data_string_get_utf16_string(
	     internal_file->icon_location,
	     internal_file->io_handle->ascii_codepage,
	     utf16_string,
	     utf16_string_size,
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

/* Retrieves the size of the UTF-8 encoded environment variables location
 * The size includes the end of string character
 * Returns 1 if successful, 0 if value is not available or -1 on error
 */
int liblnk_file_get_utf8_environment_variables_location_size(
     liblnk_file_t *file,
     size_t *utf8_string_size,
     libcerror_error_t **error )
{
	liblnk_internal_file_t *internal_file = NULL;
	static char *function                 = "liblnk_file_get_utf8_environment_variables_location_size";

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
	if( internal_file->environment_variables_location == NULL )
	{
		return( 0 );
	}
	if( liblnk_data_string_get_utf8_string_size(
	     internal_file->environment_variables_location,
	     internal_file->io_handle->ascii_codepage,
	     utf8_string_size,
	     error ) != 1 )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_GET_FAILED,
		 "%s: unable to retrieve UTF-8 data string size.",
		 function );

		return( -1 );
	}
	return( 1 );
}

/* Retrieves the UTF-8 encoded environment variables location
 * The size should include the end of string character
 * Returns 1 if successful, 0 if value is not available or -1 on error
 */
int liblnk_file_get_utf8_environment_variables_location(
     liblnk_file_t *file,
     uint8_t *utf8_string,
     size_t utf8_string_size,
     libcerror_error_t **error )
{
	liblnk_internal_file_t *internal_file = NULL;
	static char *function                 = "liblnk_file_get_utf8_environment_variables_location";

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
	if( internal_file->environment_variables_location == NULL )
	{
		return( 0 );
	}
	if( liblnk_data_string_get_utf8_string(
	     internal_file->environment_variables_location,
	     internal_file->io_handle->ascii_codepage,
	     utf8_string,
	     utf8_string_size,
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

/* Retrieves the size of the UTF-16 encoded environment variables location
 * The size includes the end of string character
 * Returns 1 if successful, 0 if value is not available or -1 on error
 */
int liblnk_file_get_utf16_environment_variables_location_size(
     liblnk_file_t *file,
     size_t *utf16_string_size,
     libcerror_error_t **error )
{
	liblnk_internal_file_t *internal_file = NULL;
	static char *function                 = "liblnk_file_get_utf16_environment_variables_location_size";

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
	if( internal_file->environment_variables_location == NULL )
	{
		return( 0 );
	}
	if( liblnk_data_string_get_utf16_string_size(
	     internal_file->environment_variables_location,
	     internal_file->io_handle->ascii_codepage,
	     utf16_string_size,
	     error ) != 1 )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_GET_FAILED,
		 "%s: unable to retrieve UTF-16 data string size.",
		 function );

		return( -1 );
	}
	return( 1 );
}

/* Retrieves the UTF-16 encoded environment variables location
 * The size should include the end of string character
 * Returns 1 if successful, 0 if value is not available or -1 on error
 */
int liblnk_file_get_utf16_environment_variables_location(
     liblnk_file_t *file,
     uint16_t *utf16_string,
     size_t utf16_string_size,
     libcerror_error_t **error )
{
	liblnk_internal_file_t *internal_file = NULL;
	static char *function                 = "liblnk_file_get_utf16_environment_variables_location";

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
	if( internal_file->environment_variables_location == NULL )
	{
		return( 0 );
	}
	if( liblnk_data_string_get_utf16_string(
	     internal_file->environment_variables_location,
	     internal_file->io_handle->ascii_codepage,
	     utf16_string,
	     utf16_string_size,
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

/* Retrieves the link target identifier data
 * The data contains a shell item (identifier) list
 * Returns 1 if successful, 0 if value is not available or -1 on error
 */
int liblnk_file_get_link_target_identifier_data(
     liblnk_file_t *file,
     uint8_t **data,
     size_t *data_size,
     libcerror_error_t **error )
{
	liblnk_internal_file_t *internal_file = NULL;
	static char *function                 = "liblnk_file_get_link_target_identifier_data";

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
	if( data_size == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid data size.",
		 function );

		return( -1 );
	}
	if( internal_file->link_target_identifier == NULL )
	{
		return( 0 );
	}
	*data      = internal_file->link_target_identifier->data;
	*data_size = internal_file->link_target_identifier->data_size;

	return( 1 );
}

/* Retrieves the link target identifier data size
 * The link target identifier contains a shell item (identifier) list
 * Returns 1 if successful, 0 if value is not available or -1 on error
 */
int liblnk_file_get_link_target_identifier_data_size(
     liblnk_file_t *file,
     size_t *data_size,
     libcerror_error_t **error )
{
	liblnk_internal_file_t *internal_file = NULL;
	static char *function                 = "liblnk_file_get_link_target_identifier_data_size";

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
	if( data_size == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid data size.",
		 function );

		return( -1 );
	}
	if( internal_file->link_target_identifier == NULL )
	{
		return( 0 );
	}
	*data_size = internal_file->link_target_identifier->data_size;

	return( 1 );
}

/* Retrieves the link target identifier data
 * The link target identifier contains a shell item (identifier) list
 * Returns 1 if successful, 0 if value is not available or -1 on error
 */
int liblnk_file_copy_link_target_identifier_data(
     liblnk_file_t *file,
     uint8_t *data,
     size_t data_size,
     libcerror_error_t **error )
{
	liblnk_internal_file_t *internal_file = NULL;
	static char *function                 = "liblnk_file_copy_link_target_identifier_data";

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
	if( data_size > (size_t) SSIZE_MAX )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_VALUE_EXCEEDS_MAXIMUM,
		 "%s: invalid data size value exceeds maximum.",
		 function );

		return( -1 );
	}
	if( internal_file->link_target_identifier == NULL )
	{
		return( 0 );
	}
	if( data_size < internal_file->link_target_identifier->data_size )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_VALUE_TOO_SMALL,
		 "%s: data value too small.",
		 function );

		return( -1 );
	}
	if( memory_copy(
	     data,
	     internal_file->link_target_identifier->data,
	     internal_file->link_target_identifier->data_size ) == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_MEMORY,
		 LIBCERROR_MEMORY_ERROR_COPY_FAILED,
		 "%s: unable to copy link target identifier data.",
		 function );

		return( -1 );
	}
	return( 1 );
}

