/* 
 * Info handle
 *
 * Copyright (c) 2009-2012, Joachim Metz <joachim.metz@gmail.com>
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
#include <file_stream.h>
#include <memory.h>
#include <types.h>

#include "info_handle.h"
#include "lnktools_libcerror.h"
#include "lnktools_libclocale.h"
#include "lnktools_libcstring.h"
#include "lnktools_libfdatetime.h"
#include "lnktools_libfguid.h"
#include "lnktools_libfwsi.h"
#include "lnktools_liblnk.h"

#define INFO_HANDLE_NOTIFY_STREAM	stdout

/* Initializes the info handle
 * Returns 1 if successful or -1 on error
 */
int info_handle_initialize(
     info_handle_t **info_handle,
     libcerror_error_t **error )
{
	static char *function = "info_handle_initialize";

	if( info_handle == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid info handle.",
		 function );

		return( -1 );
	}
	if( *info_handle != NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_VALUE_ALREADY_SET,
		 "%s: invalid info handle value already set.",
		 function );

		return( -1 );
	}
	*info_handle = memory_allocate_structure(
	                info_handle_t );

	if( *info_handle == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_MEMORY,
		 LIBCERROR_MEMORY_ERROR_INSUFFICIENT,
		 "%s: unable to create info handle.",
		 function );

		goto on_error;
	}
	if( memory_set(
	     *info_handle,
	     0,
	     sizeof( info_handle_t ) ) == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_MEMORY,
		 LIBCERROR_MEMORY_ERROR_SET_FAILED,
		 "%s: unable to clear info handle.",
		 function );

		goto on_error;
	}
	if( liblnk_file_initialize(
	     &( ( *info_handle )->input_file ),
	     error ) != 1 )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_INITIALIZE_FAILED,
		 "%s: unable to initialize input file.",
		 function );

		goto on_error;
	}
	( *info_handle )->ascii_codepage = LIBLNK_CODEPAGE_WINDOWS_1252;
	( *info_handle )->notify_stream  = INFO_HANDLE_NOTIFY_STREAM;

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
     libcerror_error_t **error )
{
	static char *function = "info_handle_free";
	int result            = 1;

	if( info_handle == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid info handle.",
		 function );

		return( -1 );
	}
	if( *info_handle != NULL )
	{
		if( liblnk_file_free(
		     &( ( *info_handle )->input_file ),
		     error ) != 1 )
		{
			libcerror_error_set(
			 error,
			 LIBCERROR_ERROR_DOMAIN_RUNTIME,
			 LIBCERROR_RUNTIME_ERROR_FINALIZE_FAILED,
			 "%s: unable to free input file.",
			 function );

			result = -1;
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
     libcerror_error_t **error )
{
	static char *function = "info_handle_signal_abort";

	if( info_handle == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
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
			libcerror_error_set(
			 error,
			 LIBCERROR_ERROR_DOMAIN_RUNTIME,
			 LIBCERROR_RUNTIME_ERROR_SET_FAILED,
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
     libcerror_error_t **error )
{
	static char *function  = "info_handle_set_ascii_codepage";
	size_t string_length   = 0;
	uint32_t feature_flags = 0;
	int result             = 0;

	if( info_handle == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid info handle.",
		 function );

		return( -1 );
	}
	feature_flags = LIBCLOCALE_CODEPAGE_FEATURE_FLAG_HAVE_KOI8
	              | LIBCLOCALE_CODEPAGE_FEATURE_FLAG_HAVE_WINDOWS;

	string_length = libcstring_system_string_length(
	                 string );

#if defined( LIBCSTRING_HAVE_WIDE_SYSTEM_CHARACTER )
	result = libclocale_codepage_copy_from_string_wide(
	          &( info_handle->ascii_codepage ),
	          string,
	          string_length,
	          feature_flags,
	          error );
#else
	result = libclocale_codepage_copy_from_string(
	          &( info_handle->ascii_codepage ),
	          string,
	          string_length,
	          feature_flags,
	          error );
#endif
	if( result == -1 )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_GET_FAILED,
		 "%s: unable to determine ASCII codepage.",
		 function );

		return( -1 );
	}
	return( result );
}

/* Opens the input
 * Returns 1 if successful or -1 on error
 */
int info_handle_open_input(
     info_handle_t *info_handle,
     const libcstring_system_character_t *filename,
     libcerror_error_t **error )
{
	static char *function = "info_handle_open_input";

	if( info_handle == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid info handle.",
		 function );

		return( -1 );
	}
	if( liblnk_file_set_ascii_codepage(
	     info_handle->input_file,
	     info_handle->ascii_codepage,
	     error ) != 1 )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_SET_FAILED,
		 "%s: unable to set ASCII codepage in input file.",
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
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_IO,
		 LIBCERROR_IO_ERROR_OPEN_FAILED,
		 "%s: unable to open input file.",
		 function );

		return( -1 );
	}
	return( 1 );
}

/* Closes the input
 * Returns the 0 if succesful or -1 on error
 */
int info_handle_close_input(
     info_handle_t *info_handle,
     libcerror_error_t **error )
{
	static char *function = "info_handle_close_input";

	if( info_handle == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid info handle.",
		 function );

		return( -1 );
	}
	if( liblnk_file_close(
	     info_handle->input_file,
	     error ) != 0 )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_IO,
		 LIBCERROR_IO_ERROR_CLOSE_FAILED,
		 "%s: unable to close input file.",
		 function );

		return( -1 );
	}
	return( 0 );
}

/* Prints the data flags
 * Returns 1 if successful or -1 on error
 */
int info_handle_data_flags_fprint(
     info_handle_t *info_handle,
     libcerror_error_t **error )
{
	static char *function = "info_handle_data_flags_fprint";
	uint32_t data_flags   = 0;

	if( info_handle == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid info handle.",
		 function );

		return( -1 );
	}
	if( liblnk_file_get_data_flags(
	     info_handle->input_file,
	     &data_flags,
	     error ) != 1 )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_GET_FAILED,
		 "%s: unable to retrieve data flags.",
		 function );

		return( -1 );
	}
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
	if( ( data_flags & LIBLNK_DATA_FLAG_HAS_ENVIRONMENT_VARIABLES_LOCATION_BLOCK ) != 0 )
	{
		fprintf(
		 info_handle->notify_stream,
		 "\tContains an environment variables block\n" );
	}
/* TODO */
	if( ( data_flags & LIBLNK_DATA_FLAG_HAS_ICON_LOCATION_BLOCK ) != 0 )
	{
		fprintf(
		 info_handle->notify_stream,
		 "\tContains an icon location block\n" );
	}
/* TODO */
	if( ( data_flags & LIBLNK_DATA_FLAG_NO_DISTRIBUTED_LINK_TRACKING_DATA_BLOCK ) != 0 )
	{
		fprintf(
		 info_handle->notify_stream,
		 "\tContains no distributed link tracking data block\n" );
	}
/* TODO */
	fprintf(
	 info_handle->notify_stream,
	 "\n" );

	return( 1 );
}

/* Prints the link information
 * Returns 1 if successful or -1 on error
 */
int info_handle_link_information_fprint(
     info_handle_t *info_handle,
     libcerror_error_t **error )
{
	libcstring_system_character_t filetime_string[ 32 ];

	libfdatetime_filetime_t *filetime           = NULL;
	libcstring_system_character_t *value_string = NULL;
	static char *function                       = "info_handle_link_information_fprint";
	size_t value_string_size                    = 0;
	uint64_t value_64bit                        = 0;
	uint32_t file_attribute_flags               = 0;
	int result                                  = 0;

	if( info_handle == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid info handle.",
		 function );

		return( -1 );
	}
	result = liblnk_file_link_refers_to_file(
	          info_handle->input_file,
	          error );

	if( result == -1 )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_GET_FAILED,
		 "%s: unable to determine if the shortcut refers to a file.",
		 function );

		goto on_error;
	}
	else if( result != 0 )
	{
		fprintf(
		 info_handle->notify_stream,
		 "Link information:\n" );

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
		if( liblnk_file_get_file_attribute_flags(
		     info_handle->input_file,
		     &file_attribute_flags,
		     error ) != 1 )
		{
			libcerror_error_set(
			 error,
			 LIBCERROR_ERROR_DOMAIN_RUNTIME,
			 LIBCERROR_RUNTIME_ERROR_GET_FAILED,
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
			libcerror_error_set(
			 error,
			 LIBCERROR_ERROR_DOMAIN_RUNTIME,
			 LIBCERROR_RUNTIME_ERROR_GET_FAILED,
			 "%s: unable to retrieve file creation time.",
			 function );

			goto on_error;
		}
		if( libfdatetime_filetime_copy_from_64bit(
		     filetime,
		     value_64bit,
		     error ) != 1 )
		{
			libcerror_error_set(
			 error,
			 LIBCERROR_ERROR_DOMAIN_RUNTIME,
			 LIBCERROR_RUNTIME_ERROR_COPY_FAILED,
			 "%s: unable to copy 64-bit value to filetime.",
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
		fprintf(
		 info_handle->notify_stream,
		 "\tCreation time\t\t\t: %" PRIs_LIBCSTRING_SYSTEM " UTC\n",
		 filetime_string );

		/* Modification time
		 */
		if( liblnk_file_get_file_modification_time(
		     info_handle->input_file,
		     &value_64bit,
		     error ) != 1 )
		{
			libcerror_error_set(
			 error,
			 LIBCERROR_ERROR_DOMAIN_RUNTIME,
			 LIBCERROR_RUNTIME_ERROR_GET_FAILED,
			 "%s: unable to retrieve file modification time.",
			 function );

			goto on_error;
		}
		if( libfdatetime_filetime_copy_from_64bit(
		     filetime,
		     value_64bit,
		     error ) != 1 )
		{
			libcerror_error_set(
			 error,
			 LIBCERROR_ERROR_DOMAIN_RUNTIME,
			 LIBCERROR_RUNTIME_ERROR_COPY_FAILED,
			 "%s: unable to copy 64-bit value to filetime.",
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
		fprintf(
		 info_handle->notify_stream,
		 "\tModification time\t\t: %" PRIs_LIBCSTRING_SYSTEM " UTC\n",
		 filetime_string );

		/* Access time
		 */
		if( liblnk_file_get_file_access_time(
		     info_handle->input_file,
		     &value_64bit,
		     error ) != 1 )
		{
			libcerror_error_set(
			 error,
			 LIBCERROR_ERROR_DOMAIN_RUNTIME,
			 LIBCERROR_RUNTIME_ERROR_GET_FAILED,
			 "%s: unable to retrieve file access time.",
			 function );

			goto on_error;
		}
		if( libfdatetime_filetime_copy_from_64bit(
		     filetime,
		     value_64bit,
		     error ) != 1 )
		{
			libcerror_error_set(
			 error,
			 LIBCERROR_ERROR_DOMAIN_RUNTIME,
			 LIBCERROR_RUNTIME_ERROR_COPY_FAILED,
			 "%s: unable to copy 64-bit value to filetime.",
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
		fprintf(
		 info_handle->notify_stream,
		 "\tAccess time\t\t\t: %" PRIs_LIBCSTRING_SYSTEM " UTC\n",
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
			libcerror_error_set(
			 error,
			 LIBCERROR_ERROR_DOMAIN_RUNTIME,
			 LIBCERROR_RUNTIME_ERROR_GET_FAILED,
			 "%s: unable to retrieve local path string size.",
			 function );

			goto on_error;
		}
		else if( result != 0 )
		{
			if( ( value_string_size > (size_t) SSIZE_MAX )
			 || ( ( sizeof( libcstring_system_character_t ) * value_string_size )  > (size_t) SSIZE_MAX ) )
			{
				libcerror_error_set(
				 error,
				 LIBCERROR_ERROR_DOMAIN_RUNTIME,
				 LIBCERROR_RUNTIME_ERROR_VALUE_EXCEEDS_MAXIMUM,
				 "%s: invalid local path string size value exceeds maximum.",
				 function );

				goto on_error;
			}
			value_string = libcstring_system_string_allocate(
			                value_string_size );

			if( value_string == NULL )
			{
				libcerror_error_set(
				 error,
				 LIBCERROR_ERROR_DOMAIN_MEMORY,
				 LIBCERROR_MEMORY_ERROR_INSUFFICIENT,
				 "%s: unable to create local path string.",
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
				libcerror_error_set(
				 error,
				 LIBCERROR_ERROR_DOMAIN_RUNTIME,
				 LIBCERROR_RUNTIME_ERROR_GET_FAILED,
				 "%s: unable to retrieve local path.",
				 function );

				goto on_error;
			}
			fprintf(
			 info_handle->notify_stream,
			 "\tLocal path\t\t\t: %s\n",
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
			libcerror_error_set(
			 error,
			 LIBCERROR_ERROR_DOMAIN_RUNTIME,
			 LIBCERROR_RUNTIME_ERROR_GET_FAILED,
			 "%s: unable to retrieve network path string size.",
			 function );

			goto on_error;
		}
		else if( result != 0 )
		{
			if( ( value_string_size > (size_t) SSIZE_MAX )
			 || ( ( sizeof( libcstring_system_character_t ) * value_string_size )  > (size_t) SSIZE_MAX ) )
			{
				libcerror_error_set(
				 error,
				 LIBCERROR_ERROR_DOMAIN_RUNTIME,
				 LIBCERROR_RUNTIME_ERROR_VALUE_EXCEEDS_MAXIMUM,
				 "%s: invalid network path string size value exceeds maximum.",
				 function );

				goto on_error;
			}
			value_string = libcstring_system_string_allocate(
			                value_string_size );

			if( value_string == NULL )
			{
				libcerror_error_set(
				 error,
				 LIBCERROR_ERROR_DOMAIN_MEMORY,
				 LIBCERROR_MEMORY_ERROR_INSUFFICIENT,
				 "%s: unable to create network path string.",
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
				libcerror_error_set(
				 error,
				 LIBCERROR_ERROR_DOMAIN_RUNTIME,
				 LIBCERROR_RUNTIME_ERROR_GET_FAILED,
				 "%s: unable to retrieve local path.",
				 function );

				goto on_error;
			}
			fprintf(
			 info_handle->notify_stream,
			 "\tNetwork path\t\t\t: %s\n",
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
     libcerror_error_t **error )
{
	libcstring_system_character_t *value_string = NULL;
	static char *function                       = "info_handle_description_fprint";
	size_t value_string_size                    = 0;
	int result                                  = 0;

	if( info_handle == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid info handle.",
		 function );

		return( -1 );
	}
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
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_GET_FAILED,
		 "%s: unable to retrieve description string size.",
		 function );

		goto on_error;
	}
	else if( result != 0 )
	{
		if( ( value_string_size > (size_t) SSIZE_MAX )
		 || ( ( sizeof( libcstring_system_character_t ) * value_string_size )  > (size_t) SSIZE_MAX ) )
		{
			libcerror_error_set(
			 error,
			 LIBCERROR_ERROR_DOMAIN_RUNTIME,
			 LIBCERROR_RUNTIME_ERROR_VALUE_EXCEEDS_MAXIMUM,
			 "%s: invalid description string size value exceeds maximum.",
			 function );

			goto on_error;
		}
		value_string = libcstring_system_string_allocate(
				value_string_size );

		if( value_string == NULL )
		{
			libcerror_error_set(
			 error,
			 LIBCERROR_ERROR_DOMAIN_MEMORY,
			 LIBCERROR_MEMORY_ERROR_INSUFFICIENT,
			 "%s: unable to create description string.",
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
			libcerror_error_set(
			 error,
			 LIBCERROR_ERROR_DOMAIN_RUNTIME,
			 LIBCERROR_RUNTIME_ERROR_GET_FAILED,
			 "%s: unable to retrieve description.",
			 function );

			goto on_error;
		}
		fprintf(
		 info_handle->notify_stream,
		 "\tDescription\t\t\t: %s\n",
		 value_string );

		memory_free(
		 value_string );

		value_string = NULL;
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

/* Prints the relative path
 * Returns 1 if successful or -1 on error
 */
int info_handle_relative_path_fprint(
     info_handle_t *info_handle,
     libcerror_error_t **error )
{
	libcstring_system_character_t *value_string = NULL;
	static char *function                       = "info_handle_relative_path_fprint";
	size_t value_string_size                    = 0;
	int result                                  = 0;

	if( info_handle == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid info handle.",
		 function );

		return( -1 );
	}
#if defined( LIBCSTRING_HAVE_WIDE_SYSTEM_CHARACTER )
	result = liblnk_file_get_utf16_relative_path_size(
		  info_handle->input_file,
		  &value_string_size,
		  error );
#else
	result = liblnk_file_get_utf8_relative_path_size(
		  info_handle->input_file,
		  &value_string_size,
		  error );
#endif
	if( result == -1 )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_GET_FAILED,
		 "%s: unable to retrieve relative path string size.",
		 function );

		goto on_error;
	}
	else if( result != 0 )
	{
		if( ( value_string_size > (size_t) SSIZE_MAX )
		 || ( ( sizeof( libcstring_system_character_t ) * value_string_size )  > (size_t) SSIZE_MAX ) )
		{
			libcerror_error_set(
			 error,
			 LIBCERROR_ERROR_DOMAIN_RUNTIME,
			 LIBCERROR_RUNTIME_ERROR_VALUE_EXCEEDS_MAXIMUM,
			 "%s: invalid relative path string size value exceeds maximum.",
			 function );

			goto on_error;
		}
		value_string = libcstring_system_string_allocate(
				value_string_size );

		if( value_string == NULL )
		{
			libcerror_error_set(
			 error,
			 LIBCERROR_ERROR_DOMAIN_MEMORY,
			 LIBCERROR_MEMORY_ERROR_INSUFFICIENT,
			 "%s: unable to create relative path string.",
			 function );

			goto on_error;
		}
#if defined( LIBCSTRING_HAVE_WIDE_SYSTEM_CHARACTER )
		result = liblnk_file_get_utf16_relative_path(
			  info_handle->input_file,
			  (uint16_t *) value_string,
			  value_string_size,
			  error );
#else
		result = liblnk_file_get_utf8_relative_path(
			  info_handle->input_file,
			  (uint8_t *) value_string,
			  value_string_size,
			  error );
#endif
		if( result == -1 )
		{
			libcerror_error_set(
			 error,
			 LIBCERROR_ERROR_DOMAIN_RUNTIME,
			 LIBCERROR_RUNTIME_ERROR_GET_FAILED,
			 "%s: unable to retrieve relative path.",
			 function );

			goto on_error;
		}
		fprintf(
		 info_handle->notify_stream,
		 "\tRelative path\t\t\t: %s\n",
		 value_string );

		memory_free(
		 value_string );

		value_string = NULL;
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

/* Prints the working directory
 * Returns 1 if successful or -1 on error
 */
int info_handle_working_directory_fprint(
     info_handle_t *info_handle,
     libcerror_error_t **error )
{
	libcstring_system_character_t *value_string = NULL;
	static char *function                       = "info_handle_working_directory_fprint";
	size_t value_string_size                    = 0;
	int result                                  = 0;

	if( info_handle == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid info handle.",
		 function );

		return( -1 );
	}
#if defined( LIBCSTRING_HAVE_WIDE_SYSTEM_CHARACTER )
	result = liblnk_file_get_utf16_working_directory_size(
		  info_handle->input_file,
		  &value_string_size,
		  error );
#else
	result = liblnk_file_get_utf8_working_directory_size(
		  info_handle->input_file,
		  &value_string_size,
		  error );
#endif
	if( result == -1 )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_GET_FAILED,
		 "%s: unable to retrieve working directory string size.",
		 function );

		goto on_error;
	}
	else if( result != 0 )
	{
		if( ( value_string_size > (size_t) SSIZE_MAX )
		 || ( ( sizeof( libcstring_system_character_t ) * value_string_size )  > (size_t) SSIZE_MAX ) )
		{
			libcerror_error_set(
			 error,
			 LIBCERROR_ERROR_DOMAIN_RUNTIME,
			 LIBCERROR_RUNTIME_ERROR_VALUE_EXCEEDS_MAXIMUM,
			 "%s: invalid working directory string size value exceeds maximum.",
			 function );

			goto on_error;
		}
		value_string = libcstring_system_string_allocate(
				value_string_size );

		if( value_string == NULL )
		{
			libcerror_error_set(
			 error,
			 LIBCERROR_ERROR_DOMAIN_MEMORY,
			 LIBCERROR_MEMORY_ERROR_INSUFFICIENT,
			 "%s: unable to create working directory string.",
			 function );

			goto on_error;
		}
#if defined( LIBCSTRING_HAVE_WIDE_SYSTEM_CHARACTER )
		result = liblnk_file_get_utf16_working_directory(
			  info_handle->input_file,
			  (uint16_t *) value_string,
			  value_string_size,
			  error );
#else
		result = liblnk_file_get_utf8_working_directory(
			  info_handle->input_file,
			  (uint8_t *) value_string,
			  value_string_size,
			  error );
#endif
		if( result == -1 )
		{
			libcerror_error_set(
			 error,
			 LIBCERROR_ERROR_DOMAIN_RUNTIME,
			 LIBCERROR_RUNTIME_ERROR_GET_FAILED,
			 "%s: unable to retrieve working directory.",
			 function );

			goto on_error;
		}
		fprintf(
		 info_handle->notify_stream,
		 "\tWorking directory\t\t: %s\n",
		 value_string );

		memory_free(
		 value_string );

		value_string = NULL;
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

/* Prints the command line arguments
 * Returns 1 if successful or -1 on error
 */
int info_handle_command_line_arguments_fprint(
     info_handle_t *info_handle,
     libcerror_error_t **error )
{
	libcstring_system_character_t *value_string = NULL;
	static char *function                       = "info_handle_command_line_arguments_fprint";
	size_t value_string_size                    = 0;
	int result                                  = 0;

	if( info_handle == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid info handle.",
		 function );

		return( -1 );
	}
#if defined( LIBCSTRING_HAVE_WIDE_SYSTEM_CHARACTER )
	result = liblnk_file_get_utf16_command_line_arguments_size(
		  info_handle->input_file,
		  &value_string_size,
		  error );
#else
	result = liblnk_file_get_utf8_command_line_arguments_size(
		  info_handle->input_file,
		  &value_string_size,
		  error );
#endif
	if( result == -1 )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_GET_FAILED,
		 "%s: unable to retrieve command line arguments string size.",
		 function );

		goto on_error;
	}
	else if( result != 0 )
	{
		if( ( value_string_size > (size_t) SSIZE_MAX )
		 || ( ( sizeof( libcstring_system_character_t ) * value_string_size )  > (size_t) SSIZE_MAX ) )
		{
			libcerror_error_set(
			 error,
			 LIBCERROR_ERROR_DOMAIN_RUNTIME,
			 LIBCERROR_RUNTIME_ERROR_VALUE_EXCEEDS_MAXIMUM,
			 "%s: invalid command line arguments string size value exceeds maximum.",
			 function );

			goto on_error;
		}
		value_string = libcstring_system_string_allocate(
				value_string_size );

		if( value_string == NULL )
		{
			libcerror_error_set(
			 error,
			 LIBCERROR_ERROR_DOMAIN_MEMORY,
			 LIBCERROR_MEMORY_ERROR_INSUFFICIENT,
			 "%s: unable to create command line arguments string.",
			 function );

			goto on_error;
		}
#if defined( LIBCSTRING_HAVE_WIDE_SYSTEM_CHARACTER )
		result = liblnk_file_get_utf16_command_line_arguments(
			  info_handle->input_file,
			  (uint16_t *) value_string,
			  value_string_size,
			  error );
#else
		result = liblnk_file_get_utf8_command_line_arguments(
			  info_handle->input_file,
			  (uint8_t *) value_string,
			  value_string_size,
			  error );
#endif
		if( result == -1 )
		{
			libcerror_error_set(
			 error,
			 LIBCERROR_ERROR_DOMAIN_RUNTIME,
			 LIBCERROR_RUNTIME_ERROR_GET_FAILED,
			 "%s: unable to retrieve command line arguments.",
			 function );

			goto on_error;
		}
		fprintf(
		 info_handle->notify_stream,
		 "\tCommand line arguments\t\t: %s\n",
		 value_string );

		memory_free(
		 value_string );

		value_string = NULL;
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

/* Prints the icon location
 * Returns 1 if successful or -1 on error
 */
int info_handle_icon_location_fprint(
     info_handle_t *info_handle,
     libcerror_error_t **error )
{
	libcstring_system_character_t *value_string = NULL;
	static char *function                       = "info_handle_icon_location_fprint";
	size_t value_string_size                    = 0;
	int result                                  = 0;

	if( info_handle == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid info handle.",
		 function );

		return( -1 );
	}
#if defined( LIBCSTRING_HAVE_WIDE_SYSTEM_CHARACTER )
	result = liblnk_file_get_utf16_icon_location_size(
		  info_handle->input_file,
		  &value_string_size,
		  error );
#else
	result = liblnk_file_get_utf8_icon_location_size(
		  info_handle->input_file,
		  &value_string_size,
		  error );
#endif
	if( result == -1 )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_GET_FAILED,
		 "%s: unable to retrieve icon location string size.",
		 function );

		goto on_error;
	}
	else if( result != 0 )
	{
		if( ( value_string_size > (size_t) SSIZE_MAX )
		 || ( ( sizeof( libcstring_system_character_t ) * value_string_size )  > (size_t) SSIZE_MAX ) )
		{
			libcerror_error_set(
			 error,
			 LIBCERROR_ERROR_DOMAIN_RUNTIME,
			 LIBCERROR_RUNTIME_ERROR_VALUE_EXCEEDS_MAXIMUM,
			 "%s: invalid icon location string size value exceeds maximum.",
			 function );

			goto on_error;
		}
		value_string = libcstring_system_string_allocate(
				value_string_size );

		if( value_string == NULL )
		{
			libcerror_error_set(
			 error,
			 LIBCERROR_ERROR_DOMAIN_MEMORY,
			 LIBCERROR_MEMORY_ERROR_INSUFFICIENT,
			 "%s: unable to create icon location string.",
			 function );

			goto on_error;
		}
#if defined( LIBCSTRING_HAVE_WIDE_SYSTEM_CHARACTER )
		result = liblnk_file_get_utf16_icon_location(
			  info_handle->input_file,
			  (uint16_t *) value_string,
			  value_string_size,
			  error );
#else
		result = liblnk_file_get_utf8_icon_location(
			  info_handle->input_file,
			  (uint8_t *) value_string,
			  value_string_size,
			  error );
#endif
		if( result == -1 )
		{
			libcerror_error_set(
			 error,
			 LIBCERROR_ERROR_DOMAIN_RUNTIME,
			 LIBCERROR_RUNTIME_ERROR_GET_FAILED,
			 "%s: unable to retrieve icon location.",
			 function );

			goto on_error;
		}
		fprintf(
		 info_handle->notify_stream,
		 "\tIcon location\t\t\t: %s\n",
		 value_string );

		memory_free(
		 value_string );

		value_string = NULL;
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

/* Prints the environment variables location
 * Returns 1 if successful or -1 on error
 */
int info_handle_environment_variables_location_fprint(
     info_handle_t *info_handle,
     libcerror_error_t **error )
{
	libcstring_system_character_t *value_string = NULL;
	static char *function                       = "info_handle_environment_variables_location_fprint";
	size_t value_string_size                    = 0;
	int result                                  = 0;

	if( info_handle == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid info handle.",
		 function );

		return( -1 );
	}
#if defined( LIBCSTRING_HAVE_WIDE_SYSTEM_CHARACTER )
	result = liblnk_file_get_utf16_environment_variables_location_size(
		  info_handle->input_file,
		  &value_string_size,
		  error );
#else
	result = liblnk_file_get_utf8_environment_variables_location_size(
		  info_handle->input_file,
		  &value_string_size,
		  error );
#endif
	if( result == -1 )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_GET_FAILED,
		 "%s: unable to retrieve environment variables location string size.",
		 function );

		goto on_error;
	}
	else if( result != 0 )
	{
		if( ( value_string_size > (size_t) SSIZE_MAX )
		 || ( ( sizeof( libcstring_system_character_t ) * value_string_size )  > (size_t) SSIZE_MAX ) )
		{
			libcerror_error_set(
			 error,
			 LIBCERROR_ERROR_DOMAIN_RUNTIME,
			 LIBCERROR_RUNTIME_ERROR_VALUE_EXCEEDS_MAXIMUM,
			 "%s: invalid environment variables location string size value exceeds maximum.",
			 function );

			goto on_error;
		}
		value_string = libcstring_system_string_allocate(
				value_string_size );

		if( value_string == NULL )
		{
			libcerror_error_set(
			 error,
			 LIBCERROR_ERROR_DOMAIN_MEMORY,
			 LIBCERROR_MEMORY_ERROR_INSUFFICIENT,
			 "%s: unable to create environment variables location string.",
			 function );

			goto on_error;
		}
#if defined( LIBCSTRING_HAVE_WIDE_SYSTEM_CHARACTER )
		result = liblnk_file_get_utf16_environment_variables_location(
			  info_handle->input_file,
			  (uint16_t *) value_string,
			  value_string_size,
			  error );
#else
		result = liblnk_file_get_utf8_environment_variables_location(
			  info_handle->input_file,
			  (uint8_t *) value_string,
			  value_string_size,
			  error );
#endif
		if( result == -1 )
		{
			libcerror_error_set(
			 error,
			 LIBCERROR_ERROR_DOMAIN_RUNTIME,
			 LIBCERROR_RUNTIME_ERROR_GET_FAILED,
			 "%s: unable to retrieve environment variables location.",
			 function );

			goto on_error;
		}
		fprintf(
		 info_handle->notify_stream,
		 "\tEnvironment variables location\t: %s\n",
		 value_string );

		memory_free(
		 value_string );

		value_string = NULL;
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

/* Prints the link target identifier
 * Returns 1 if successful or -1 on error
 */
int info_handle_link_target_identifier_fprint(
     info_handle_t *info_handle,
     libcerror_error_t **error )
{
	libfwsi_item_t *item                    = NULL;
	libfwsi_item_list_t *item_list          = NULL;
	uint8_t *link_target_identifier_data    = NULL;
	static char *function                   = "info_handle_link_target_identifier_fprint";
	size_t link_target_identifier_data_size = 0;
	uint8_t item_type                       = 0;
	int item_index                          = 0;
	int number_of_items                     = 0;
	int result                              = 0;

	if( info_handle == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid info handle.",
		 function );

		return( -1 );
	}
	result = liblnk_file_get_link_target_identifier_data(
	          info_handle->input_file,
	          &link_target_identifier_data,
	          &link_target_identifier_data_size,
	          error );

	if( result == -1 )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_GET_FAILED,
		 "%s: unable to retrieve link target identifier data.",
		 function );

		goto on_error;
	}
	else if( result != 0 )
	{
		fprintf(
		 info_handle->notify_stream,
		 "Link target identifier:\n" );

		if( libfwsi_item_list_initialize(
		     &item_list,
		     error ) != 1 )
		{
			libcerror_error_set(
			 error,
			 LIBCERROR_ERROR_DOMAIN_RUNTIME,
			 LIBCERROR_RUNTIME_ERROR_INITIALIZE_FAILED,
			 "%s: unable to create item list.",
			 function );

			goto on_error;
		}
		if( libfwsi_item_list_copy_from_byte_stream(
		     item_list,
		     link_target_identifier_data,
		     link_target_identifier_data_size,
		     error ) != 1 )
		{
			libcerror_error_set(
			 error,
			 LIBCERROR_ERROR_DOMAIN_RUNTIME,
			 LIBCERROR_RUNTIME_ERROR_COPY_FAILED,
			 "%s: unable to copy item list from byte stream.",
			 function );

			goto on_error;
		}
		if( libfwsi_item_list_get_number_of_items(
		     item_list,
		     &number_of_items,
		     error ) != 1 )
		{
			libcerror_error_set(
			 error,
			 LIBCERROR_ERROR_DOMAIN_RUNTIME,
			 LIBCERROR_RUNTIME_ERROR_GET_FAILED,
			 "%s: unable to retrieve number of items.",
			 function );

			goto on_error;
		}
		for( item_index = 0;
		     item_index < number_of_items;
		     item_index++ )
		{
			if( libfwsi_item_list_get_item(
			     item_list,
			     item_index,
			     &item,
			     error ) != 1 )
			{
				libcerror_error_set(
				 error,
				 LIBCERROR_ERROR_DOMAIN_RUNTIME,
				 LIBCERROR_RUNTIME_ERROR_GET_FAILED,
				 "%s: unable to retrieve item: %d.",
				 function,
				 item_index );

				goto on_error;
			}
			if( libfwsi_item_get_type(
			     item,
			     &item_type,
			     error ) != 1 )
			{
				libcerror_error_set(
				 error,
				 LIBCERROR_ERROR_DOMAIN_RUNTIME,
				 LIBCERROR_RUNTIME_ERROR_GET_FAILED,
				 "%s: unable to retrieve item: %d type.",
				 function,
				 item_index );

				goto on_error;
			}
/* TODO */
/* TODO the item is currently managed by the list
			if( libfwsi_item_free(
			     &item,
			     error ) != 1 )
			{
				libcerror_error_set(
				 error,
				 LIBCERROR_ERROR_DOMAIN_RUNTIME,
				 LIBCERROR_RUNTIME_ERROR_FINALIZE_FAILED,
				 "%s: unable to free item: %d.",
				 function,
				 item_index );

				goto on_error;
			}
*/
		}
		if( libfwsi_item_list_free(
		     &item_list,
		     error ) != 1 )
		{
			libcerror_error_set(
			 error,
			 LIBCERROR_ERROR_DOMAIN_RUNTIME,
			 LIBCERROR_RUNTIME_ERROR_FINALIZE_FAILED,
			 "%s: unable to free item list.",
			 function );

			goto on_error;
		}
		fprintf(
		 info_handle->notify_stream,
		 "\n" );
	}
	return( 1 );

on_error:
/* TODO the item is currently managed by the list
	if( item != NULL )
	{
		libfwsi_item_free(
		 &item,
		 NULL );
	}
*/
	if( item_list != NULL )
	{
		libfwsi_item_list_free(
		 &item_list,
		 NULL );
	}
	return( -1 );
}

/* Prints the distributed link tracking data
 * Returns 1 if successful or -1 on error
 */
int info_handle_distributed_link_tracking_fprint(
     info_handle_t *info_handle,
     libcerror_error_t **error )
{
	uint8_t guid_data[ 16 ];

	libcstring_system_character_t guid_string[ 48 ];

	libfguid_identifier_t *guid                 = NULL;
	libcstring_system_character_t *value_string = NULL;
	static char *function                       = "info_handle_distributed_link_tracking_fprint";
	size_t value_string_size                    = 0;
	int result                                  = 0;

	if( info_handle == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid info handle.",
		 function );

		return( -1 );
	}
	result = liblnk_file_has_distributed_link_tracking_data(
	          info_handle->input_file,
	          error );

	if( result == -1 )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_GET_FAILED,
		 "%s: unable to determine if file contains distributed link tracking data.",
		 function );

		goto on_error;
	}
	else if( result != 0 )
	{
		fprintf(
		 info_handle->notify_stream,
		 "Distributed link tracking data:\n" );

#if defined( LIBCSTRING_HAVE_WIDE_SYSTEM_CHARACTER )
		result = liblnk_file_get_utf16_machine_identifier_size(
			  info_handle->input_file,
			  &value_string_size,
			  error );
#else
		result = liblnk_file_get_utf8_machine_identifier_size(
			  info_handle->input_file,
			  &value_string_size,
			  error );
#endif
		if( result != 1 )
		{
			libcerror_error_set(
			 error,
			 LIBCERROR_ERROR_DOMAIN_RUNTIME,
			 LIBCERROR_RUNTIME_ERROR_GET_FAILED,
			 "%s: unable to retrieve machine identifier string size.",
			 function );

			goto on_error;
		}
		if( ( value_string_size > (size_t) SSIZE_MAX )
		 || ( ( sizeof( libcstring_system_character_t ) * value_string_size )  > (size_t) SSIZE_MAX ) )
		{
			libcerror_error_set(
			 error,
			 LIBCERROR_ERROR_DOMAIN_RUNTIME,
			 LIBCERROR_RUNTIME_ERROR_VALUE_EXCEEDS_MAXIMUM,
			 "%s: invalid machine identifier size value exceeds maximum.",
			 function );

			goto on_error;
		}
		value_string = libcstring_system_string_allocate(
				value_string_size );

		if( value_string == NULL )
		{
			libcerror_error_set(
			 error,
			 LIBCERROR_ERROR_DOMAIN_MEMORY,
			 LIBCERROR_MEMORY_ERROR_INSUFFICIENT,
			 "%s: unable to create machine identifier string.",
			 function );

			goto on_error;
		}
#if defined( LIBCSTRING_HAVE_WIDE_SYSTEM_CHARACTER )
		result = liblnk_file_get_utf16_machine_identifier(
			  info_handle->input_file,
			  (uint16_t *) value_string,
			  value_string_size,
			  error );
#else
		result = liblnk_file_get_utf8_machine_identifier(
			  info_handle->input_file,
			  (uint8_t *) value_string,
			  value_string_size,
			  error );
#endif
		if( result != 1 )
		{
			libcerror_error_set(
			 error,
			 LIBCERROR_ERROR_DOMAIN_RUNTIME,
			 LIBCERROR_RUNTIME_ERROR_GET_FAILED,
			 "%s: unable to retrieve machine identifier.",
			 function );

			goto on_error;
		}
		fprintf(
		 info_handle->notify_stream,
		 "\tMachine identifier\t\t: %s\n",
		 value_string );

		memory_free(
		 value_string );

		value_string = NULL;

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
		if( liblnk_file_get_droid_volume_identifier(
		     info_handle->input_file,
		     guid_data,
		     16,
		     error ) != 1 )
		{
			libcerror_error_set(
			 error,
			 LIBCERROR_ERROR_DOMAIN_RUNTIME,
			 LIBCERROR_RUNTIME_ERROR_GET_FAILED,
			 "%s: unable to retrieve droid volume identifier.",
			 function );

			goto on_error;
		}
		if( libfguid_identifier_copy_from_byte_stream(
		     guid,
		     guid_data,
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
			  LIBFGUID_STRING_FORMAT_USE_LOWER_CASE,
			  error );
#else
		result = libfguid_identifier_copy_to_utf8_string(
			  guid,
			  (uint8_t *) guid_string,
			  48,
			  LIBFGUID_STRING_FORMAT_USE_LOWER_CASE,
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
		fprintf(
		 info_handle->notify_stream,
		 "\tDroid volume identifier\t\t: %" PRIs_LIBCSTRING_SYSTEM "\n",
		 guid_string );

		if( liblnk_file_get_droid_file_identifier(
		     info_handle->input_file,
		     guid_data,
		     16,
		     error ) != 1 )
		{
			libcerror_error_set(
			 error,
			 LIBCERROR_ERROR_DOMAIN_RUNTIME,
			 LIBCERROR_RUNTIME_ERROR_GET_FAILED,
			 "%s: unable to retrieve droid file identifier.",
			 function );

			goto on_error;
		}
		if( libfguid_identifier_copy_from_byte_stream(
		     guid,
		     guid_data,
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
			  LIBFGUID_STRING_FORMAT_USE_LOWER_CASE,
			  error );
#else
		result = libfguid_identifier_copy_to_utf8_string(
			  guid,
			  (uint8_t *) guid_string,
			  48,
			  LIBFGUID_STRING_FORMAT_USE_LOWER_CASE,
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
		fprintf(
		 info_handle->notify_stream,
		 "\tDroid file identifier\t\t: %" PRIs_LIBCSTRING_SYSTEM "\n",
		 guid_string );

		if( liblnk_file_get_birth_droid_volume_identifier(
		     info_handle->input_file,
		     guid_data,
		     16,
		     error ) != 1 )
		{
			libcerror_error_set(
			 error,
			 LIBCERROR_ERROR_DOMAIN_RUNTIME,
			 LIBCERROR_RUNTIME_ERROR_GET_FAILED,
			 "%s: unable to retrieve birth droid volume identifier.",
			 function );

			goto on_error;
		}
		if( libfguid_identifier_copy_from_byte_stream(
		     guid,
		     guid_data,
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
			  LIBFGUID_STRING_FORMAT_USE_LOWER_CASE,
			  error );
#else
		result = libfguid_identifier_copy_to_utf8_string(
			  guid,
			  (uint8_t *) guid_string,
			  48,
			  LIBFGUID_STRING_FORMAT_USE_LOWER_CASE,
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
		fprintf(
		 info_handle->notify_stream,
		 "\tBirth droid volume identifier\t: %" PRIs_LIBCSTRING_SYSTEM "\n",
		 guid_string );

		if( liblnk_file_get_birth_droid_file_identifier(
		     info_handle->input_file,
		     guid_data,
		     16,
		     error ) != 1 )
		{
			libcerror_error_set(
			 error,
			 LIBCERROR_ERROR_DOMAIN_RUNTIME,
			 LIBCERROR_RUNTIME_ERROR_GET_FAILED,
			 "%s: unable to retrieve birth droid file identifier.",
			 function );

			goto on_error;
		}
		if( libfguid_identifier_copy_from_byte_stream(
		     guid,
		     guid_data,
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
			  LIBFGUID_STRING_FORMAT_USE_LOWER_CASE,
			  error );
#else
		result = libfguid_identifier_copy_to_utf8_string(
			  guid,
			  (uint8_t *) guid_string,
			  48,
			  LIBFGUID_STRING_FORMAT_USE_LOWER_CASE,
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
		fprintf(
		 info_handle->notify_stream,
		 "\tBirth droid file identifier\t: %" PRIs_LIBCSTRING_SYSTEM "\n",
		 guid_string );

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
		fprintf(
		 info_handle->notify_stream,
		 "\n" );
	}
	return( 1 );

on_error:
	if( value_string != NULL )
	{
		memory_free(
		 value_string );
	}
	if( guid != NULL )
	{
		libfguid_identifier_free(
		 &guid,
		 NULL );
	}
	return( -1 );
}

/* Prints the file information
 * Returns 1 if successful or -1 on error
 */
int info_handle_file_fprint(
     info_handle_t *info_handle,
     libcerror_error_t **error )
{
	static char *function = "info_handle_file_fprint";

	if( info_handle == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid info handle.",
		 function );

		return( -1 );
	}
	if( info_handle_data_flags_fprint(
	     info_handle,
	     error ) != 1 )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_PRINT_FAILED,
		 "%s: unable to print data flags.",
		 function );

		return( -1 );
	}
	if( info_handle_link_information_fprint(
	     info_handle,
	     error ) != 1 )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_PRINT_FAILED,
		 "%s: unable to print link information.",
		 function );

		return( -1 );
	}
	if( info_handle_description_fprint(
	     info_handle,
	     error ) != 1 )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_PRINT_FAILED,
		 "%s: unable to print description.",
		 function );

		return( -1 );
	}
	if( info_handle_relative_path_fprint(
	     info_handle,
	     error ) != 1 )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_PRINT_FAILED,
		 "%s: unable to print relative path.",
		 function );

		return( -1 );
	}
	if( info_handle_working_directory_fprint(
	     info_handle,
	     error ) != 1 )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_PRINT_FAILED,
		 "%s: unable to print working directory.",
		 function );

		return( -1 );
	}
	if( info_handle_command_line_arguments_fprint(
	     info_handle,
	     error ) != 1 )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_PRINT_FAILED,
		 "%s: unable to print command line arguments.",
		 function );

		return( -1 );
	}
	if( info_handle_icon_location_fprint(
	     info_handle,
	     error ) != 1 )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_PRINT_FAILED,
		 "%s: unable to print icon location.",
		 function );

		return( -1 );
	}
	if( info_handle_environment_variables_location_fprint(
	     info_handle,
	     error ) != 1 )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_PRINT_FAILED,
		 "%s: unable to print environment variables location.",
		 function );

		return( -1 );
	}
	fprintf(
	 info_handle->notify_stream,
	 "\n" );

	if( info_handle_link_target_identifier_fprint(
	     info_handle,
	     error ) != 1 )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_PRINT_FAILED,
		 "%s: unable to print link target identifier data.",
		 function );

		return( -1 );
	}
	if( info_handle_distributed_link_tracking_fprint(
	     info_handle,
	     error ) != 1 )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_PRINT_FAILED,
		 "%s: unable to print distributed link tracking data.",
		 function );

		return( -1 );
	}
/* TODO print more info */

	return( 1 );
}

