/*
 * Link information functions
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
#include <narrow_string.h>
#include <memory.h>
#include <types.h>
#include <wide_string.h>

#include <liberror.h>
#include <libnotify.h>

#include "liblnk_definitions.h"
#include "liblnk_file.h"
#include "liblnk_file_information.h"
#include "liblnk_location_information.h"
#include "liblnk_shell_item_identifiers.h"

/* Retrieves the data flags
 * The data flags contain information about the available link information
 * Returns 1 if successful or -1 on error
 */
int liblnk_file_get_data_flags(
     liblnk_file_t *file,
     uint32_t *data_flags,
     liberror_error_t **error )
{
	liblnk_internal_file_t *internal_file = NULL;
	static char *function                 = "liblnk_file_get_data_flags";

	if( file == NULL )
	{
		liberror_error_set(
		 error,
		 LIBERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid file.",
		 function );

		return( -1 );
	}
	internal_file = (liblnk_internal_file_t *) file;

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
	*data_flags = internal_file->data_flags;

	return( 1 );
}

/* Retrieves the file attribute flags
 * The file attribute flags are only set if the link refers to a file
 * Returns 1 if successful or -1 on error
 */
int liblnk_file_get_file_attribute_flags(
     liblnk_file_t *file,
     uint32_t *file_attribute_flags,
     liberror_error_t **error )
{
	liblnk_internal_file_t *internal_file = NULL;
	static char *function                 = "liblnk_file_get_file_attribute_flags";

	if( file == NULL )
	{
		liberror_error_set(
		 error,
		 LIBERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid file.",
		 function );

		return( -1 );
	}
	internal_file = (liblnk_internal_file_t *) file;

	if( internal_file->file_information == NULL )
	{
		liberror_error_set(
		 error,
		 LIBERROR_ERROR_DOMAIN_RUNTIME,
		 LIBERROR_RUNTIME_ERROR_VALUE_MISSING,
		 "%s: invalid file - missing file information.",
		 function );

		return( -1 );
	}
	if( file_attribute_flags == NULL )
	{
		liberror_error_set(
		 error,
		 LIBERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid file attribute flags.",
		 function );

		return( -1 );
	}
	*file_attribute_flags = internal_file->file_information->file_attribute_flags;

	return( 1 );
}

/* Retrieves the 64-bit filetime value containing the creation date and time
 * The creation time is only set when the link refers to a file
 * Returns 1 if successful or -1 on error
 */
int liblnk_file_get_creation_time(
     liblnk_file_t *file,
     uint64_t *creation_time,
     liberror_error_t **error )
{
	liblnk_internal_file_t *internal_file = NULL;
	static char *function                 = "liblnk_file_get_creation_time";

	if( file == NULL )
	{
		liberror_error_set(
		 error,
		 LIBERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid file.",
		 function );

		return( -1 );
	}
	internal_file = (liblnk_internal_file_t *) file;

	if( internal_file->file_information == NULL )
	{
		liberror_error_set(
		 error,
		 LIBERROR_ERROR_DOMAIN_RUNTIME,
		 LIBERROR_RUNTIME_ERROR_VALUE_MISSING,
		 "%s: invalid file - missing file information.",
		 function );

		return( -1 );
	}
	if( creation_time == NULL )
	{
		liberror_error_set(
		 error,
		 LIBERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid creation time.",
		 function );

		return( -1 );
	}
	*creation_time = internal_file->file_information->creation_time;

	return( 1 );
}

/* Retrieves the 64-bit filetime value containing the last modification date and time
 * The modification time is only set when the link refers to a file
 * Returns 1 if successful or -1 on error
 */
int liblnk_file_get_modification_time(
     liblnk_file_t *file,
     uint64_t *modification_time,
     liberror_error_t **error )
{
	liblnk_internal_file_t *internal_file = NULL;
	static char *function                 = "liblnk_file_get_modification_time";

	if( file == NULL )
	{
		liberror_error_set(
		 error,
		 LIBERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid file.",
		 function );

		return( -1 );
	}
	internal_file = (liblnk_internal_file_t *) file;

	if( internal_file->file_information == NULL )
	{
		liberror_error_set(
		 error,
		 LIBERROR_ERROR_DOMAIN_RUNTIME,
		 LIBERROR_RUNTIME_ERROR_VALUE_MISSING,
		 "%s: invalid file - missing file information.",
		 function );

		return( -1 );
	}
	if( modification_time == NULL )
	{
		liberror_error_set(
		 error,
		 LIBERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid modification time.",
		 function );

		return( -1 );
	}
	*modification_time = internal_file->file_information->modification_time;

	return( 1 );
}

/* Retrieves the 64-bit filetime value containing the last access date and time
 * The access time is only set when the link refers to a file
 * Returns 1 if successful or -1 on error
 */
int liblnk_file_get_access_time(
     liblnk_file_t *file,
     uint64_t *access_time,
     liberror_error_t **error )
{
	liblnk_internal_file_t *internal_file = NULL;
	static char *function                 = "liblnk_file_get_access_time";

	if( file == NULL )
	{
		liberror_error_set(
		 error,
		 LIBERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid file.",
		 function );

		return( -1 );
	}
	internal_file = (liblnk_internal_file_t *) file;

	if( internal_file->file_information == NULL )
	{
		liberror_error_set(
		 error,
		 LIBERROR_ERROR_DOMAIN_RUNTIME,
		 LIBERROR_RUNTIME_ERROR_VALUE_MISSING,
		 "%s: invalid file - missing file information.",
		 function );

		return( -1 );
	}
	if( access_time == NULL )
	{
		liberror_error_set(
		 error,
		 LIBERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid access time.",
		 function );

		return( -1 );
	}
	*access_time = internal_file->file_information->access_time;

	return( 1 );
}

/* Retrieves the file size
 * The file size are only set if the link refers to a file
 * Returns 1 if successful or -1 on error
 */
int liblnk_file_get_file_size(
     liblnk_file_t *file,
     uint32_t *file_size,
     liberror_error_t **error )
{
	liblnk_internal_file_t *internal_file = NULL;
	static char *function                 = "liblnk_file_get_file_size";

	if( file == NULL )
	{
		liberror_error_set(
		 error,
		 LIBERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid file.",
		 function );

		return( -1 );
	}
	internal_file = (liblnk_internal_file_t *) file;

	if( internal_file->file_information == NULL )
	{
		liberror_error_set(
		 error,
		 LIBERROR_ERROR_DOMAIN_RUNTIME,
		 LIBERROR_RUNTIME_ERROR_VALUE_MISSING,
		 "%s: invalid file - missing file information.",
		 function );

		return( -1 );
	}
	if( file_size == NULL )
	{
		liberror_error_set(
		 error,
		 LIBERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid file size.",
		 function );

		return( -1 );
	}
	*file_size = internal_file->file_information->file_size;

	return( 1 );
}

