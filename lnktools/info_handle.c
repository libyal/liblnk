/* 
 * Info handle
 *
 * Copyright (c) 2009-2011, Joachim Metz <jbmetz@users.sourceforge.net>
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

#include <libcstring.h>
#include <liberror.h>

#include "info_handle.h"
#include "lnkinput.h"
#include "lnktools_libfdatetime.h"
#include "lnktools_liblnk.h"

#define INFO_HANDLE_NOTIFY_STREAM	stdout

/* Initializes the info handle
 * Returns 1 if successful or -1 on error
 */
int info_handle_initialize(
     info_handle_t **info_handle,
     liberror_error_t **error )
{
	static char *function = "info_handle_initialize";

	if( info_handle == NULL )
	{
		liberror_error_set(
		 error,
		 LIBERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid info handle.",
		 function );

		return( -1 );
	}
	if( *info_handle == NULL )
	{
		*info_handle = memory_allocate_structure(
		                info_handle_t );

		if( *info_handle == NULL )
		{
			liberror_error_set(
			 error,
			 LIBERROR_ERROR_DOMAIN_MEMORY,
			 LIBERROR_MEMORY_ERROR_INSUFFICIENT,
			 "%s: unable to create info handle.",
			 function );

			goto on_error;
		}
		if( memory_set(
		     *info_handle,
		     0,
		     sizeof( info_handle_t ) ) == NULL )
		{
			liberror_error_set(
			 error,
			 LIBERROR_ERROR_DOMAIN_MEMORY,
			 LIBERROR_MEMORY_ERROR_SET_FAILED,
			 "%s: unable to clear info handle.",
			 function );

			goto on_error;
		}
		if( liblnk_file_initialize(
		     &( ( *info_handle )->input_file ),
		     error ) != 1 )
		{
			liberror_error_set(
			 error,
			 LIBERROR_ERROR_DOMAIN_RUNTIME,
			 LIBERROR_RUNTIME_ERROR_INITIALIZE_FAILED,
			 "%s: unable to initialize input file.",
			 function );

			goto on_error;
		}
		( *info_handle )->notify_stream = INFO_HANDLE_NOTIFY_STREAM;
	}
	return( 1 );

on_error:
	if( *info_handle != NULL )
	{
		memory_free(
		 *info_handle );

		*info_handle = NULL;
	}
	return( -1 );
}

/* Frees the info handle and its elements
 * Returns 1 if successful or -1 on error
 */
int info_handle_free(
     info_handle_t **info_handle,
     liberror_error_t **error )
{
	static char *function = "info_handle_free";
	int result            = 1;

	if( info_handle == NULL )
	{
		liberror_error_set(
		 error,
		 LIBERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid info handle.",
		 function );

		return( -1 );
	}
	if( *info_handle != NULL )
	{
		if( ( *info_handle )->input_file != NULL )
		{
			if( liblnk_file_free(
			     &( ( *info_handle )->input_file ),
			     error ) != 1 )
			{
				liberror_error_set(
				 error,
				 LIBERROR_ERROR_DOMAIN_RUNTIME,
				 LIBERROR_RUNTIME_ERROR_FINALIZE_FAILED,
				 "%s: unable to free input file.",
				 function );

				result = -1;
			}
		}
		memory_free(
		 *info_handle );

		*info_handle = NULL;
	}
	return( result );
}

/* Signals the info handle to abort
 * Returns 1 if successful or -1 on error
 */
int info_handle_signal_abort(
     info_handle_t *info_handle,
     liberror_error_t **error )
{
	static char *function = "info_handle_signal_abort";

	if( info_handle == NULL )
	{
		liberror_error_set(
		 error,
		 LIBERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid info handle.",
		 function );

		return( -1 );
	}
	info_handle->abort = 1;

	if( info_handle->input_file != NULL )
	{
		if( liblnk_file_signal_abort(
		     info_handle->input_file,
		     error ) != 1 )
		{
			liberror_error_set(
			 error,
			 LIBERROR_ERROR_DOMAIN_RUNTIME,
			 LIBERROR_RUNTIME_ERROR_SET_FAILED,
			 "%s: unable to signal input file to abort.",
			 function );

			return( -1 );
		}
	}
	return( 1 );
}

/* Sets the ascii codepage
 * Returns 1 if successful or -1 on error
 */
int info_handle_set_ascii_codepage(
     info_handle_t *info_handle,
     const libcstring_system_character_t *string,
     liberror_error_t **error )
{
	static char *function = "info_handle_set_ascii_codepage";
	int result            = 0;

	if( info_handle == NULL )
	{
		liberror_error_set(
		 error,
		 LIBERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid info handle.",
		 function );

		return( -1 );
	}
	result = lnkinput_determine_ascii_codepage(
	          string,
	          &( info_handle->ascii_codepage ),
	          error );

	if( result == -1 )
	{
		liberror_error_set(
		 error,
		 LIBERROR_ERROR_DOMAIN_RUNTIME,
		 LIBERROR_RUNTIME_ERROR_GET_FAILED,
		 "%s: unable to determine ASCII codepage.",
		 function );

		return( -1 );
	}
	return( result );
}

/* Opens the info handle
 * Returns 1 if successful or -1 on error
 */
int info_handle_open(
     info_handle_t *info_handle,
     const libcstring_system_character_t *filename,
     liberror_error_t **error )
{
	static char *function = "info_handle_open";

	if( info_handle == NULL )
	{
		liberror_error_set(
		 error,
		 LIBERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid info handle.",
		 function );

		return( -1 );
	}
#if defined( LIBCSTRING_HAVE_WIDE_SYSTEM_CHARACTER )
	if( liblnk_file_open_wide(
	     info_handle->input_file,
	     filename,
	     LIBLNK_OPEN_READ,
	     error ) != 1 )
#else
	if( liblnk_file_open(
	     info_handle->input_file,
	     filename,
	     LIBLNK_OPEN_READ,
	     error ) != 1 )
#endif
	{
		liberror_error_set(
		 error,
		 LIBERROR_ERROR_DOMAIN_IO,
		 LIBERROR_IO_ERROR_OPEN_FAILED,
		 "%s: unable to open input file.",
		 function );

		return( -1 );
	}
	return( 1 );
}

/* Closes the info handle
 * Returns the 0 if succesful or -1 on error
 */
int info_handle_close(
     info_handle_t *info_handle,
     liberror_error_t **error )
{
	static char *function = "info_handle_close";

	if( info_handle == NULL )
	{
		liberror_error_set(
		 error,
		 LIBERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid info handle.",
		 function );

		return( -1 );
	}
	if( liblnk_file_close(
	     info_handle->input_file,
	     error ) != 0 )
	{
		liberror_error_set(
		 error,
		 LIBERROR_ERROR_DOMAIN_IO,
		 LIBERROR_IO_ERROR_CLOSE_FAILED,
		 "%s: unable to close input file.",
		 function );

		return( -1 );
	}
	return( 0 );
}

/* Prints the link target identifier information
 * Returns 1 if successful or -1 on error
 */
int info_handle_link_target_identifier_fprint(
     info_handle_t *info_handle,
     liberror_error_t **error )
{
	libcstring_system_character_t filetime_string[ 32 ];

	libfdatetime_filetime_t *filetime           = NULL;
	libcstring_system_character_t *value_string = NULL;
	static char *function                       = "info_handle_link_target_identifier_fprint";
	size_t value_string_size                    = 0;
	uint64_t value_64bit                        = 0;
	uint32_t file_attribute_flags               = 0;
	int result                                  = 0;

	if( info_handle == NULL )
	{
		liberror_error_set(
		 error,
		 LIBERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid info handle.",
		 function );

		return( -1 );
	}
	result = liblnk_file_link_refers_to_file(
	          info_handle->input_file,
	          error );

	if( result == -1 )
	{
		liberror_error_set(
		 error,
		 LIBERROR_ERROR_DOMAIN_RUNTIME,
		 LIBERROR_RUNTIME_ERROR_GET_FAILED,
		 "%s: unable to determine if the shortcut refers to a file.",
		 function );

		goto on_error;
	}
	else if( result != 0 )
	{
		fprintf(
		 info_handle->notify_stream,
		 "Linked file information:\n" );

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

			goto on_error;
		}
		if( liblnk_file_get_file_attribute_flags(
		     info_handle->input_file,
		     &file_attribute_flags,
		     error ) != 1 )
		{
			liberror_error_set(
			 error,
			 LIBERROR_ERROR_DOMAIN_RUNTIME,
			 LIBERROR_RUNTIME_ERROR_GET_FAILED,
			 "%s: unable to retrieve file attribute flags.",
			 function );

			goto on_error;
		}
		/* Creation time
		 */
		if( liblnk_file_get_file_creation_time(
		     info_handle->input_file,
		     &value_64bit,
		     error ) != 1 )
		{
			liberror_error_set(
			 error,
			 LIBERROR_ERROR_DOMAIN_RUNTIME,
			 LIBERROR_RUNTIME_ERROR_GET_FAILED,
			 "%s: unable to retrieve file creation time.",
			 function );

			goto on_error;
		}
		if( libfdatetime_filetime_copy_from_64bit(
		     filetime,
		     value_64bit,
		     error ) != 1 )
		{
			liberror_error_set(
			 error,
			 LIBERROR_ERROR_DOMAIN_RUNTIME,
			 LIBERROR_RUNTIME_ERROR_COPY_FAILED,
			 "%s: unable to copy 64-bit value to filetime.",
			 function );

			goto on_error;
		}
#if defined( LIBCSTRING_HAVE_WIDE_SYSTEM_CHARACTER )
		result = libfdatetime_filetime_copy_to_utf16_string(
			  filetime,
			  (uint16_t *) filetime_string,
			  32,
			  LIBFDATETIME_STRING_FORMAT_FLAG_DATE_TIME_MICRO_SECONDS,
			  LIBFDATETIME_DATE_TIME_FORMAT_CTIME,
			  error );
#else
		result = libfdatetime_filetime_copy_to_utf8_string(
			  filetime,
			  (uint8_t *) filetime_string,
			  32,
			  LIBFDATETIME_STRING_FORMAT_FLAG_DATE_TIME_MICRO_SECONDS,
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

			goto on_error;
		}
		fprintf(
		 info_handle->notify_stream,
		 "\tCreation time\t\t: %" PRIs_LIBCSTRING_SYSTEM " UTC\n",
		 filetime_string );

		/* Modification time
		 */
		if( liblnk_file_get_file_modification_time(
		     info_handle->input_file,
		     &value_64bit,
		     error ) != 1 )
		{
			liberror_error_set(
			 error,
			 LIBERROR_ERROR_DOMAIN_RUNTIME,
			 LIBERROR_RUNTIME_ERROR_GET_FAILED,
			 "%s: unable to retrieve file modification time.",
			 function );

			goto on_error;
		}
		if( libfdatetime_filetime_copy_from_64bit(
		     filetime,
		     value_64bit,
		     error ) != 1 )
		{
			liberror_error_set(
			 error,
			 LIBERROR_ERROR_DOMAIN_RUNTIME,
			 LIBERROR_RUNTIME_ERROR_COPY_FAILED,
			 "%s: unable to copy 64-bit value to filetime.",
			 function );

			goto on_error;
		}
#if defined( LIBCSTRING_HAVE_WIDE_SYSTEM_CHARACTER )
		result = libfdatetime_filetime_copy_to_utf16_string(
			  filetime,
			  (uint16_t *) filetime_string,
			  32,
			  LIBFDATETIME_STRING_FORMAT_FLAG_DATE_TIME_MICRO_SECONDS,
			  LIBFDATETIME_DATE_TIME_FORMAT_CTIME,
			  error );
#else
		result = libfdatetime_filetime_copy_to_utf8_string(
			  filetime,
			  (uint8_t *) filetime_string,
			  32,
			  LIBFDATETIME_STRING_FORMAT_FLAG_DATE_TIME_MICRO_SECONDS,
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

			goto on_error;
		}
		fprintf(
		 info_handle->notify_stream,
		 "\tModification time\t: %" PRIs_LIBCSTRING_SYSTEM " UTC\n",
		 filetime_string );

		/* Access time
		 */
		if( liblnk_file_get_file_access_time(
		     info_handle->input_file,
		     &value_64bit,
		     error ) != 1 )
		{
			liberror_error_set(
			 error,
			 LIBERROR_ERROR_DOMAIN_RUNTIME,
			 LIBERROR_RUNTIME_ERROR_GET_FAILED,
			 "%s: unable to retrieve file access time.",
			 function );

			goto on_error;
		}
		if( libfdatetime_filetime_copy_from_64bit(
		     filetime,
		     value_64bit,
		     error ) != 1 )
		{
			liberror_error_set(
			 error,
			 LIBERROR_ERROR_DOMAIN_RUNTIME,
			 LIBERROR_RUNTIME_ERROR_COPY_FAILED,
			 "%s: unable to copy 64-bit value to filetime.",
			 function );

			goto on_error;
		}
#if defined( LIBCSTRING_HAVE_WIDE_SYSTEM_CHARACTER )
		result = libfdatetime_filetime_copy_to_utf16_string(
			  filetime,
			  (uint16_t *) filetime_string,
			  32,
			  LIBFDATETIME_STRING_FORMAT_FLAG_DATE_TIME_MICRO_SECONDS,
			  LIBFDATETIME_DATE_TIME_FORMAT_CTIME,
			  error );
#else
		result = libfdatetime_filetime_copy_to_utf8_string(
			  filetime,
			  (uint8_t *) filetime_string,
			  32,
			  LIBFDATETIME_STRING_FORMAT_FLAG_DATE_TIME_MICRO_SECONDS,
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

			goto on_error;
		}
		fprintf(
		 info_handle->notify_stream,
		 "\tAccess time\t\t: %" PRIs_LIBCSTRING_SYSTEM " UTC\n",
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

			goto on_error;
		}
#if defined( LIBCSTRING_HAVE_WIDE_SYSTEM_CHARACTER )
		result = liblnk_file_get_utf16_local_path_size(
		          info_handle->input_file,
		          &value_string_size,
		          error );
#else
		result = liblnk_file_get_utf8_local_path_size(
		          info_handle->input_file,
		          &value_string_size,
		          error );
#endif
		if( result == -1 )
		{
			liberror_error_set(
			 error,
			 LIBERROR_ERROR_DOMAIN_RUNTIME,
			 LIBERROR_RUNTIME_ERROR_GET_FAILED,
			 "%s: unable to retrieve local path size.",
			 function );

			goto on_error;
		}
		else if( result != 0 )
		{
			value_string = libcstring_system_string_allocate(
			                value_string_size );

			if( value_string == NULL )
			{
				liberror_error_set(
				 error,
				 LIBERROR_ERROR_DOMAIN_MEMORY,
				 LIBERROR_MEMORY_ERROR_INSUFFICIENT,
				 "%s: unable to create local path value string.",
				 function );

				goto on_error;
			}
#if defined( LIBCSTRING_HAVE_WIDE_SYSTEM_CHARACTER )
			result = liblnk_file_get_utf16_local_path(
			          info_handle->input_file,
			          (uint16_t *) value_string,
			          value_string_size,
			          error );
#else
			result = liblnk_file_get_utf8_local_path(
			          info_handle->input_file,
			          (uint8_t *) value_string,
			          value_string_size,
			          error );
#endif
			if( result == -1 )
			{
				liberror_error_set(
				 error,
				 LIBERROR_ERROR_DOMAIN_RUNTIME,
				 LIBERROR_RUNTIME_ERROR_GET_FAILED,
				 "%s: unable to retrieve local path.",
				 function );

				goto on_error;
			}
			fprintf(
			 info_handle->notify_stream,
			 "\tLocal path\t\t: %s\n",
			 value_string );

			memory_free(
			 value_string );

			value_string = NULL;
		}
#if defined( LIBCSTRING_HAVE_WIDE_SYSTEM_CHARACTER )
		result = liblnk_file_get_utf16_network_path_size(
		          info_handle->input_file,
		          &value_string_size,
		          error );
#else
		result = liblnk_file_get_utf8_network_path_size(
		          info_handle->input_file,
		          &value_string_size,
		          error );
#endif
		if( result == -1 )
		{
			liberror_error_set(
			 error,
			 LIBERROR_ERROR_DOMAIN_RUNTIME,
			 LIBERROR_RUNTIME_ERROR_GET_FAILED,
			 "%s: unable to retrieve local path size.",
			 function );

			goto on_error;
		}
		else if( result != 0 )
		{
			value_string = libcstring_system_string_allocate(
			                value_string_size );

			if( value_string == NULL )
			{
				liberror_error_set(
				 error,
				 LIBERROR_ERROR_DOMAIN_MEMORY,
				 LIBERROR_MEMORY_ERROR_INSUFFICIENT,
				 "%s: unable to create local path value string.",
				 function );

				goto on_error;
			}
#if defined( LIBCSTRING_HAVE_WIDE_SYSTEM_CHARACTER )
			result = liblnk_file_get_utf16_network_path(
			          info_handle->input_file,
			          (uint16_t *) value_string,
			          value_string_size,
			          error );
#else
			result = liblnk_file_get_utf8_network_path(
			          info_handle->input_file,
			          (uint8_t *) value_string,
			          value_string_size,
			          error );
#endif
			if( result == -1 )
			{
				liberror_error_set(
				 error,
				 LIBERROR_ERROR_DOMAIN_RUNTIME,
				 LIBERROR_RUNTIME_ERROR_GET_FAILED,
				 "%s: unable to retrieve local path.",
				 function );

				goto on_error;
			}
			fprintf(
			 info_handle->notify_stream,
			 "\tNetwork path\t\t: %s\n",
			 value_string );

			memory_free(
			 value_string );

			value_string = NULL;
		}
	}
	return( 1 );

on_error:
	if( value_string != NULL )
	{
		memory_free(
		 value_string );
	}
	if( filetime != NULL )
	{
		libfdatetime_filetime_free(
		 &filetime,
		 NULL );
	}
	return( -1 );
}

/* Prints the description
 * Returns 1 if successful or -1 on error
 */
int info_handle_description_fprint(
     info_handle_t *info_handle,
     uint32_t data_flags,
     liberror_error_t **error )
{
	libcstring_system_character_t *value_string = NULL;
	static char *function                       = "info_handle_description_fprint";
	size_t value_string_size                    = 0;
	int result                                  = 0;

	if( info_handle == NULL )
	{
		liberror_error_set(
		 error,
		 LIBERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid info handle.",
		 function );

		return( -1 );
	}
	if( ( data_flags & LIBLNK_DATA_FLAG_HAS_DESCRIPTION_STRING ) != 0 )
	{
#if defined( LIBCSTRING_HAVE_WIDE_SYSTEM_CHARACTER )
		result = liblnk_file_get_utf16_description_size(
		          info_handle->input_file,
		          &value_string_size,
		          error );
#else
		result = liblnk_file_get_utf8_description_size(
		          info_handle->input_file,
		          &value_string_size,
		          error );
#endif
		if( result == -1 )
		{
			liberror_error_set(
			 error,
			 LIBERROR_ERROR_DOMAIN_RUNTIME,
			 LIBERROR_RUNTIME_ERROR_GET_FAILED,
			 "%s: unable to retrieve description size.",
			 function );

			goto on_error;
		}
		else if( result != 0 )
		{
			value_string = libcstring_system_string_allocate(
			                value_string_size );

			if( value_string == NULL )
			{
				liberror_error_set(
				 error,
				 LIBERROR_ERROR_DOMAIN_MEMORY,
				 LIBERROR_MEMORY_ERROR_INSUFFICIENT,
				 "%s: unable to create local path value string.",
				 function );

				goto on_error;
			}
#if defined( LIBCSTRING_HAVE_WIDE_SYSTEM_CHARACTER )
			result = liblnk_file_get_utf16_description(
			          info_handle->input_file,
			          (uint16_t *) value_string,
			          value_string_size,
			          error );
#else
			result = liblnk_file_get_utf8_description(
			          info_handle->input_file,
			          (uint8_t *) value_string,
			          value_string_size,
			          error );
#endif
			if( result == -1 )
			{
				liberror_error_set(
				 error,
				 LIBERROR_ERROR_DOMAIN_RUNTIME,
				 LIBERROR_RUNTIME_ERROR_GET_FAILED,
				 "%s: unable to retrieve description.",
				 function );

				goto on_error;
			}
			fprintf(
			 info_handle->notify_stream,
			 "\tDescription\t\t: %s\n",
			 value_string );

			memory_free(
			 value_string );

			value_string = NULL;
		}
	}
	return( 1 );

on_error:
	if( value_string != NULL )
	{
		memory_free(
		 value_string );
	}
	return( -1 );
}

/* Prints the file information
 * Returns 1 if successful or -1 on error
 */
int info_handle_file_fprint(
     info_handle_t *info_handle,
     liberror_error_t **error )
{
	static char *function = "info_handle_file_fprint";
	uint32_t data_flags   = 0;

	if( info_handle == NULL )
	{
		liberror_error_set(
		 error,
		 LIBERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid info handle.",
		 function );

		return( -1 );
	}
	if( liblnk_file_get_data_flags(
	     info_handle->input_file,
	     &data_flags,
	     error ) != 1 )
	{
		liberror_error_set(
		 error,
		 LIBERROR_ERROR_DOMAIN_RUNTIME,
		 LIBERROR_RUNTIME_ERROR_GET_FAILED,
		 "%s: unable to retrieve data flags.",
		 function );

		return( -1 );
	}
/* TODO refactor to separate sub function */
	fprintf(
	 info_handle->notify_stream,
	 "Windows Shortcut information:\n" );

	if( ( data_flags & LIBLNK_DATA_FLAG_HAS_LINK_TARGET_IDENTIFIER ) != 0 )
	{
		fprintf(
		 info_handle->notify_stream,
		 "\tContains a link target identifier\n" );
	}
/* TODO: LIBLNK_DATA_FLAG_HAS_LOCATION_INFORMATION */
	if( ( data_flags & LIBLNK_DATA_FLAG_HAS_DESCRIPTION_STRING ) != 0 )
	{
		fprintf(
		 info_handle->notify_stream,
		 "\tContains a description string\n" );
	}
	if( ( data_flags & LIBLNK_DATA_FLAG_HAS_RELATIVE_PATH_STRING ) != 0 )
	{
		fprintf(
		 info_handle->notify_stream,
		 "\tContains a relative path string\n" );
	}
	if( ( data_flags & LIBLNK_DATA_FLAG_HAS_WORKING_DIRECTORY_STRING ) != 0 )
	{
		fprintf(
		 info_handle->notify_stream,
		 "\tContains a working directory string\n" );
	}
	if( ( data_flags & LIBLNK_DATA_FLAG_HAS_COMMAND_LINE_ARGUMENTS_STRING ) != 0 )
	{
		fprintf(
		 info_handle->notify_stream,
		 "\tContains a command line arguments string\n" );
	}
	if( ( data_flags & LIBLNK_DATA_FLAG_HAS_ICON_LOCATION_STRING ) != 0 )
	{
		fprintf(
		 info_handle->notify_stream,
		 "\tContains an icon location string\n" );
	}
/* TODO */
	fprintf(
	 info_handle->notify_stream,
	 "\n" );

	if( info_handle_link_target_identifier_fprint(
	     info_handle,
	     error ) != 1 )
	{
		liberror_error_set(
		 error,
		 LIBERROR_ERROR_DOMAIN_RUNTIME,
		 LIBERROR_RUNTIME_ERROR_PRINT_FAILED,
		 "%s: unable to print link target identifier.",
		 function );

		return( -1 );
	}
	if( info_handle_description_fprint(
	     info_handle,
	     data_flags,
	     error ) != 1 )
	{
		liberror_error_set(
		 error,
		 LIBERROR_ERROR_DOMAIN_RUNTIME,
		 LIBERROR_RUNTIME_ERROR_PRINT_FAILED,
		 "%s: unable to print description.",
		 function );

		return( -1 );
	}
/* TODO print more info */

	fprintf(
	 info_handle->notify_stream,
	 "\n" );

	return( 1 );
}

