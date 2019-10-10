/*
 * Info handle
 *
 * Copyright (C) 2009-2019, Joachim Metz <joachim.metz@gmail.com>
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
#include <narrow_string.h>
#include <system_string.h>
#include <types.h>
#include <wide_string.h>

#include "info_handle.h"
#include "lnktools_libcerror.h"
#include "lnktools_libclocale.h"
#include "lnktools_libfdatetime.h"
#include "lnktools_libfguid.h"
#include "lnktools_libfwsi.h"
#include "lnktools_liblnk.h"
#include "shell_items.h"

#define INFO_HANDLE_NOTIFY_STREAM	stdout

/* Prints the file attribute flags to the notify stream
 */
void info_handle_file_attribute_flags_fprint(
      uint32_t file_attribute_flags,
      FILE *notify_stream )
{
	if( ( file_attribute_flags & LIBLNK_FILE_ATTRIBUTE_FLAG_READ_ONLY ) != 0 )
	{
		fprintf(
		 notify_stream,
		 "\t\tIs read-only (FILE_ATTRIBUTE_READ_ONLY)\n" );
	}
	if( ( file_attribute_flags & LIBLNK_FILE_ATTRIBUTE_FLAG_HIDDEN ) != 0 )
	{
		fprintf(
		 notify_stream,
		 "\t\tIs hidden (FILE_ATTRIBUTE_HIDDEN)\n" );
	}
	if( ( file_attribute_flags & LIBLNK_FILE_ATTRIBUTE_FLAG_SYSTEM ) != 0 )
	{
		fprintf(
		 notify_stream,
		 "\t\tIs system (FILE_ATTRIBUTE_SYSTEM)\n" );
	}

	if( ( file_attribute_flags & LIBLNK_FILE_ATTRIBUTE_FLAG_DIRECTORY ) != 0 )
	{
		fprintf(
		 notify_stream,
		 "\t\tIs directory (FILE_ATTRIBUTE_DIRECTORY)\n" );
	}
	if( ( file_attribute_flags & LIBLNK_FILE_ATTRIBUTE_FLAG_ARCHIVE ) != 0 )
	{
		fprintf(
		 notify_stream,
		 "\t\tShould be archived (FILE_ATTRIBUTE_ARCHIVE)\n" );
	}
	if( ( file_attribute_flags & LIBLNK_FILE_ATTRIBUTE_FLAG_DEVICE ) != 0 )
	{
		fprintf(
		 notify_stream,
		 "\t\tIs device (FILE_ATTRIBUTE_DEVICE)\n" );
	}
	if( ( file_attribute_flags & LIBLNK_FILE_ATTRIBUTE_FLAG_NORMAL ) != 0 )
	{
		fprintf(
		 notify_stream,
		 "\t\tIs normal (FILE_ATTRIBUTE_NORMAL)\n" );
	}
	if( ( file_attribute_flags & LIBLNK_FILE_ATTRIBUTE_FLAG_TEMPORARY ) != 0 )
	{
		fprintf(
		 notify_stream,
		 "\t\tIs temporary (FILE_ATTRIBUTE_TEMPORARY)\n" );
	}
	if( ( file_attribute_flags & LIBLNK_FILE_ATTRIBUTE_FLAG_SPARSE_FILE ) != 0 )
	{
		fprintf(
		 notify_stream,
		 "\t\tIs a sparse file (FILE_ATTRIBUTE_SPARSE_FILE)\n" );
	}
	if( ( file_attribute_flags & LIBLNK_FILE_ATTRIBUTE_FLAG_REPARSE_POINT ) != 0 )
	{
		fprintf(
		 notify_stream,
		 "\t\tIs a reparse point or symbolic link (FILE_ATTRIBUTE_FLAG_REPARSE_POINT)\n" );
	}
	if( ( file_attribute_flags & LIBLNK_FILE_ATTRIBUTE_FLAG_COMPRESSED ) != 0 )
	{
		fprintf(
		 notify_stream,
		 "\t\tIs compressed (FILE_ATTRIBUTE_COMPRESSED)\n" );
	}
	if( ( file_attribute_flags & LIBLNK_FILE_ATTRIBUTE_FLAG_OFFLINE ) != 0 )
	{
		fprintf(
		 notify_stream,
		 "\t\tIs offline (FILE_ATTRIBUTE_OFFLINE)\n" );
	}
	if( ( file_attribute_flags & LIBLNK_FILE_ATTRIBUTE_FLAG_NOT_CONTENT_INDEXED ) != 0 )
	{
		fprintf(
		 notify_stream,
		 "\t\tContent should not be indexed (FILE_ATTRIBUTE_NOT_CONTENT_INDEXED)\n" );
	}
	if( ( file_attribute_flags & LIBLNK_FILE_ATTRIBUTE_FLAG_ENCRYPTED ) != 0 )
	{
		fprintf(
		 notify_stream,
		 "\t\tIs encrypted (FILE_ATTRIBUTE_ENCRYPTED)\n" );
	}

	if( ( file_attribute_flags & LIBLNK_FILE_ATTRIBUTE_FLAG_VIRTUAL ) != 0 )
	{
		fprintf(
		 notify_stream,
		 "\t\tIs virtual (FILE_ATTRIBUTE_VIRTUAL)\n" );
	}
}

/* Creates an info handle
 * Make sure the value info_handle is referencing, is set to NULL
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

/* Frees an info handle
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
     const system_character_t *string,
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
	feature_flags = LIBCLOCALE_CODEPAGE_FEATURE_FLAG_HAVE_WINDOWS;

	string_length = system_string_length(
	                 string );

#if defined( HAVE_WIDE_SYSTEM_CHARACTER )
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
     const system_character_t *filename,
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
#if defined( HAVE_WIDE_SYSTEM_CHARACTER )
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

/* Prints a FILETIME value
 * Returns 1 if successful or -1 on error
 */
int info_handle_filetime_value_fprint(
     info_handle_t *info_handle,
     const char *value_name,
     uint64_t value_64bit,
     libcerror_error_t **error )
{
	system_character_t date_time_string[ 48 ];

	libfdatetime_filetime_t *filetime = NULL;
	static char *function             = "info_handle_filetime_value_fprint";
	int result                        = 0;

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
	if( value_64bit == 0 )
	{
		fprintf(
		 info_handle->notify_stream,
		 "%s: Not set (0)\n",
		 value_name );
	}
	else
	{
		if( libfdatetime_filetime_initialize(
		     &filetime,
		     error ) != 1 )
		{
			libcerror_error_set(
			 error,
			 LIBCERROR_ERROR_DOMAIN_RUNTIME,
			 LIBCERROR_RUNTIME_ERROR_INITIALIZE_FAILED,
			 "%s: unable to create FILETIME.",
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
			 "%s: unable to copy 64-bit value to FILETIME.",
			 function );

			goto on_error;
		}
#if defined( HAVE_WIDE_SYSTEM_CHARACTER )
		result = libfdatetime_filetime_copy_to_utf16_string(
			  filetime,
			  (uint16_t *) date_time_string,
			  48,
			  LIBFDATETIME_STRING_FORMAT_TYPE_CTIME | LIBFDATETIME_STRING_FORMAT_FLAG_DATE_TIME_NANO_SECONDS,
			  error );
#else
		result = libfdatetime_filetime_copy_to_utf8_string(
			  filetime,
			  (uint8_t *) date_time_string,
			  48,
			  LIBFDATETIME_STRING_FORMAT_TYPE_CTIME | LIBFDATETIME_STRING_FORMAT_FLAG_DATE_TIME_NANO_SECONDS,
			  error );
#endif
		if( result != 1 )
		{
			libcerror_error_set(
			 error,
			 LIBCERROR_ERROR_DOMAIN_RUNTIME,
			 LIBCERROR_RUNTIME_ERROR_COPY_FAILED,
			 "%s: unable to copy FILETIME to string.",
			 function );

			goto on_error;
		}
		fprintf(
		 info_handle->notify_stream,
		 "%s: %" PRIs_SYSTEM " UTC\n",
		 value_name,
		 date_time_string );

		if( libfdatetime_filetime_free(
		     &filetime,
		     error ) != 1 )
		{
			libcerror_error_set(
			 error,
			 LIBCERROR_ERROR_DOMAIN_RUNTIME,
			 LIBCERROR_RUNTIME_ERROR_FINALIZE_FAILED,
			 "%s: unable to free FILETIME.",
			 function );

			goto on_error;
		}
	}
	return( 1 );

on_error:
	if( filetime != NULL )
	{
		libfdatetime_filetime_free(
		 &filetime,
		 NULL );
	}
	return( -1 );
}

/* Prints a GUID value
 * Returns 1 if successful or -1 on error
 */
int info_handle_guid_value_fprint(
     info_handle_t *info_handle,
     const char *value_name,
     const uint8_t *guid_data,
     libcerror_error_t **error )
{
	system_character_t guid_string[ 48 ];

	libfguid_identifier_t *guid = NULL;
	static char *function       = "info_handle_guid_value_fprint";
	int result                  = 0;

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
#if defined( HAVE_WIDE_SYSTEM_CHARACTER )
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
	fprintf(
	 info_handle->notify_stream,
	 "%s: %" PRIs_SYSTEM "\n",
	 value_name,
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
	return( 1 );

on_error:
	if( guid != NULL )
	{
		libfguid_identifier_free(
		 &guid,
		 NULL );
	}
	return( -1 );
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
	system_character_t *value_string = NULL;
	static char *function            = "info_handle_link_information_fprint";
	size_t value_string_size         = 0;
	uint64_t value_64bit             = 0;
	uint32_t value_32bit             = 0;
	uint16_t value_16bit             = 0;
	int result                       = 0;

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
	fprintf(
	 info_handle->notify_stream,
	 "Link information:\n" );

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
	if( info_handle_filetime_value_fprint(
	     info_handle,
	     "\tCreation time\t\t\t",
	     value_64bit,
	     error ) != 1 )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_PRINT_FAILED,
		 "%s: unable to print FILETIME value.",
		 function );

		goto on_error;
	}
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
	if( info_handle_filetime_value_fprint(
	     info_handle,
	     "\tModification time\t\t",
	     value_64bit,
	     error ) != 1 )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_PRINT_FAILED,
		 "%s: unable to print FILETIME value.",
		 function );

		goto on_error;
	}
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
	if( info_handle_filetime_value_fprint(
	     info_handle,
	     "\tAccess time\t\t\t",
	     value_64bit,
	     error ) != 1 )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_PRINT_FAILED,
		 "%s: unable to print FILETIME value.",
		 function );

		goto on_error;
	}
	if( liblnk_file_get_file_size(
	     info_handle->input_file,
	     &value_32bit,
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
	fprintf(
	 info_handle->notify_stream,
	 "\tFile size\t\t\t: %" PRIu32 " bytes\n",
	 value_32bit );

	if( liblnk_file_get_icon_index(
	     info_handle->input_file,
	     &value_32bit,
	     error ) != 1 )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_GET_FAILED,
		 "%s: unable to retrieve icon index.",
		 function );

		goto on_error;
	}
	fprintf(
	 info_handle->notify_stream,
	 "\tIcon index\t\t\t: %" PRIi32 "\n",
	 (int32_t) value_32bit );

	if( liblnk_file_get_show_window_value(
	     info_handle->input_file,
	     &value_32bit,
	     error ) != 1 )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_GET_FAILED,
		 "%s: unable to retrieve show window value.",
		 function );

		goto on_error;
	}
	fprintf(
	 info_handle->notify_stream,
	 "\tShow Window value\t\t: 0x%08" PRIx32 "\n",
	 value_32bit );

	if( liblnk_file_get_hot_key_value(
	     info_handle->input_file,
	     &value_16bit,
	     error ) != 1 )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_GET_FAILED,
		 "%s: unable to retrieve hot key value.",
		 function );

		goto on_error;
	}
	fprintf(
	 info_handle->notify_stream,
	 "\tHot Key value\t\t\t: %" PRIu16 "\n",
	 value_16bit );

	if( liblnk_file_get_file_attribute_flags(
	     info_handle->input_file,
	     &value_32bit,
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
	fprintf(
	 info_handle->notify_stream,
	 "\tFile attribute flags\t\t: 0x%08" PRIx32 "\n",
	 value_32bit );
	info_handle_file_attribute_flags_fprint(
	 value_32bit,
	 info_handle->notify_stream );

	result = liblnk_file_get_drive_type(
	          info_handle->input_file,
	          &value_32bit,
	          error );

	if( result == -1 )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_GET_FAILED,
		 "%s: unable to retrieve drive type.",
		 function );

		goto on_error;
	}
	else if( result != 0 )
	{
		fprintf(
		 info_handle->notify_stream,
		 "\tDrive type\t\t\t: " );

		switch( value_32bit )
		{
			case LIBLNK_DRIVE_TYPE_UNKNOWN:
				fprintf(
				 info_handle->notify_stream,
				 "Not set" );
				break;

			case LIBLNK_DRIVE_TYPE_NO_ROOT_DIR:
				fprintf(
				 info_handle->notify_stream,
				 "No root directory" );
				break;

			case LIBLNK_DRIVE_TYPE_REMOVABLE:
				fprintf(
				 info_handle->notify_stream,
				 "Removable" );
				break;

			case LIBLNK_DRIVE_TYPE_FIXED:
				fprintf(
				 info_handle->notify_stream,
				 "Fixed" );
				break;

			case LIBLNK_DRIVE_TYPE_REMOTE:
				fprintf(
				 info_handle->notify_stream,
				 "Remote" );
				break;

			case LIBLNK_DRIVE_TYPE_CDROM:
				fprintf(
				 info_handle->notify_stream,
				 "CDROM" );
				break;

			case LIBLNK_DRIVE_TYPE_RAMDISK:
				fprintf(
				 info_handle->notify_stream,
				 "RAM disk" );
				break;

			default:
				fprintf(
				 info_handle->notify_stream,
				 "Unknown" );
				break;
		}
		fprintf(
		 info_handle->notify_stream,
		 " (%" PRIu32 ")\n",
		 value_32bit );
	}
	result = liblnk_file_get_drive_serial_number(
	          info_handle->input_file,
	          &value_32bit,
	          error );

	if( result == -1 )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_GET_FAILED,
		 "%s: unable to retrieve drive serial number.",
		 function );

		goto on_error;
	}
	else if( result != 0 )
	{
		fprintf(
		 info_handle->notify_stream,
		 "\tDrive serial number\t\t: 0x%08" PRIx32 "\n",
		 value_32bit );
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
#if defined( HAVE_WIDE_SYSTEM_CHARACTER )
		result = liblnk_file_get_utf16_volume_label_size(
		          info_handle->input_file,
		          &value_string_size,
		          error );
#else
		result = liblnk_file_get_utf8_volume_label_size(
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
			 "%s: unable to retrieve volume label string size.",
			 function );

			goto on_error;
		}
		else if( ( result != 0 )
		      && ( value_string_size > 0 ) )
		{
			if( value_string_size > ( (size_t) SSIZE_MAX / sizeof( system_character_t ) ) )
			{
				libcerror_error_set(
				 error,
				 LIBCERROR_ERROR_DOMAIN_RUNTIME,
				 LIBCERROR_RUNTIME_ERROR_VALUE_EXCEEDS_MAXIMUM,
				 "%s: invalid volume label string size value exceeds maximum.",
				 function );

				goto on_error;
			}
			value_string = system_string_allocate(
			                value_string_size );

			if( value_string == NULL )
			{
				libcerror_error_set(
				 error,
				 LIBCERROR_ERROR_DOMAIN_MEMORY,
				 LIBCERROR_MEMORY_ERROR_INSUFFICIENT,
				 "%s: unable to create volume label string.",
				 function );

				goto on_error;
			}
#if defined( HAVE_WIDE_SYSTEM_CHARACTER )
			result = liblnk_file_get_utf16_volume_label(
			          info_handle->input_file,
			          (uint16_t *) value_string,
			          value_string_size,
			          error );
#else
			result = liblnk_file_get_utf8_volume_label(
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
				 "%s: unable to retrieve volume label.",
				 function );

				goto on_error;
			}
			fprintf(
			 info_handle->notify_stream,
			 "\tVolume label\t\t\t: %" PRIs_SYSTEM "\n",
			 value_string );

			memory_free(
			 value_string );

			value_string = NULL;
		}
#if defined( HAVE_WIDE_SYSTEM_CHARACTER )
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
		else if( ( result != 0 )
		      && ( value_string_size > 0 ) )
		{
			if( value_string_size > ( (size_t) SSIZE_MAX / sizeof( system_character_t ) ) )
			{
				libcerror_error_set(
				 error,
				 LIBCERROR_ERROR_DOMAIN_RUNTIME,
				 LIBCERROR_RUNTIME_ERROR_VALUE_EXCEEDS_MAXIMUM,
				 "%s: invalid local path string size value exceeds maximum.",
				 function );

				goto on_error;
			}
			value_string = system_string_allocate(
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
#if defined( HAVE_WIDE_SYSTEM_CHARACTER )
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
			 "\tLocal path\t\t\t: %" PRIs_SYSTEM "\n",
			 value_string );

			memory_free(
			 value_string );

			value_string = NULL;
		}
#if defined( HAVE_WIDE_SYSTEM_CHARACTER )
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
		else if( ( result != 0 )
		      && ( value_string_size > 0 ) )
		{
			if( value_string_size > ( (size_t) SSIZE_MAX / sizeof( system_character_t ) ) )
			{
				libcerror_error_set(
				 error,
				 LIBCERROR_ERROR_DOMAIN_RUNTIME,
				 LIBCERROR_RUNTIME_ERROR_VALUE_EXCEEDS_MAXIMUM,
				 "%s: invalid network path string size value exceeds maximum.",
				 function );

				goto on_error;
			}
			value_string = system_string_allocate(
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
#if defined( HAVE_WIDE_SYSTEM_CHARACTER )
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
			 "\tNetwork path\t\t\t: %" PRIs_SYSTEM "\n",
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

/* Prints the description
 * Returns 1 if successful or -1 on error
 */
int info_handle_description_fprint(
     info_handle_t *info_handle,
     libcerror_error_t **error )
{
	system_character_t *value_string = NULL;
	static char *function            = "info_handle_description_fprint";
	size_t value_string_size         = 0;
	int result                       = 0;

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
#if defined( HAVE_WIDE_SYSTEM_CHARACTER )
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
	else if( ( result != 0 )
	      && ( value_string_size > 0 ) )
	{
		if( value_string_size > ( (size_t) SSIZE_MAX / sizeof( system_character_t ) ) )
		{
			libcerror_error_set(
			 error,
			 LIBCERROR_ERROR_DOMAIN_RUNTIME,
			 LIBCERROR_RUNTIME_ERROR_VALUE_EXCEEDS_MAXIMUM,
			 "%s: invalid description string size value exceeds maximum.",
			 function );

			goto on_error;
		}
		value_string = system_string_allocate(
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
#if defined( HAVE_WIDE_SYSTEM_CHARACTER )
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
		 "\tDescription\t\t\t: %" PRIs_SYSTEM "\n",
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
	system_character_t *value_string = NULL;
	static char *function            = "info_handle_relative_path_fprint";
	size_t value_string_size         = 0;
	int result                       = 0;

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
#if defined( HAVE_WIDE_SYSTEM_CHARACTER )
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
	else if( ( result != 0 )
	      && ( value_string_size > 0 ) )
	{
		if( value_string_size > ( (size_t) SSIZE_MAX / sizeof( system_character_t ) ) )
		{
			libcerror_error_set(
			 error,
			 LIBCERROR_ERROR_DOMAIN_RUNTIME,
			 LIBCERROR_RUNTIME_ERROR_VALUE_EXCEEDS_MAXIMUM,
			 "%s: invalid relative path string size value exceeds maximum.",
			 function );

			goto on_error;
		}
		value_string = system_string_allocate(
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
#if defined( HAVE_WIDE_SYSTEM_CHARACTER )
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
		 "\tRelative path\t\t\t: %" PRIs_SYSTEM "\n",
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
	system_character_t *value_string = NULL;
	static char *function            = "info_handle_working_directory_fprint";
	size_t value_string_size         = 0;
	int result                       = 0;

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
#if defined( HAVE_WIDE_SYSTEM_CHARACTER )
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
	else if( ( result != 0 )
	      && ( value_string_size > 0 ) )
	{
		if( value_string_size > ( (size_t) SSIZE_MAX / sizeof( system_character_t ) ) )
		{
			libcerror_error_set(
			 error,
			 LIBCERROR_ERROR_DOMAIN_RUNTIME,
			 LIBCERROR_RUNTIME_ERROR_VALUE_EXCEEDS_MAXIMUM,
			 "%s: invalid working directory string size value exceeds maximum.",
			 function );

			goto on_error;
		}
		value_string = system_string_allocate(
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
#if defined( HAVE_WIDE_SYSTEM_CHARACTER )
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
		 "\tWorking directory\t\t: %" PRIs_SYSTEM "\n",
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
	system_character_t *value_string = NULL;
	static char *function            = "info_handle_command_line_arguments_fprint";
	size_t value_string_size         = 0;
	int result                       = 0;

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
#if defined( HAVE_WIDE_SYSTEM_CHARACTER )
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
	else if( ( result != 0 )
	      && ( value_string_size > 0 ) )
	{
		if( value_string_size > ( (size_t) SSIZE_MAX / sizeof( system_character_t ) ) )
		{
			libcerror_error_set(
			 error,
			 LIBCERROR_ERROR_DOMAIN_RUNTIME,
			 LIBCERROR_RUNTIME_ERROR_VALUE_EXCEEDS_MAXIMUM,
			 "%s: invalid command line arguments string size value exceeds maximum.",
			 function );

			goto on_error;
		}
		value_string = system_string_allocate(
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
#if defined( HAVE_WIDE_SYSTEM_CHARACTER )
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
		 "\tCommand line arguments\t\t: %" PRIs_SYSTEM "\n",
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
	system_character_t *value_string = NULL;
	static char *function            = "info_handle_icon_location_fprint";
	size_t value_string_size         = 0;
	int result                       = 0;

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
#if defined( HAVE_WIDE_SYSTEM_CHARACTER )
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
	else if( ( result != 0 )
	      && ( value_string_size > 0 ) )
	{
		if( value_string_size > ( (size_t) SSIZE_MAX / sizeof( system_character_t ) ) )
		{
			libcerror_error_set(
			 error,
			 LIBCERROR_ERROR_DOMAIN_RUNTIME,
			 LIBCERROR_RUNTIME_ERROR_VALUE_EXCEEDS_MAXIMUM,
			 "%s: invalid icon location string size value exceeds maximum.",
			 function );

			goto on_error;
		}
		value_string = system_string_allocate(
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
#if defined( HAVE_WIDE_SYSTEM_CHARACTER )
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
		 "\tIcon location\t\t\t: %" PRIs_SYSTEM "\n",
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
	system_character_t *value_string = NULL;
	static char *function            = "info_handle_environment_variables_location_fprint";
	size_t value_string_size         = 0;
	int result                       = 0;

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
#if defined( HAVE_WIDE_SYSTEM_CHARACTER )
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
	else if( ( result != 0 )
	      && ( value_string_size > 0 ) )
	{
		if( value_string_size > ( (size_t) SSIZE_MAX / sizeof( system_character_t ) ) )
		{
			libcerror_error_set(
			 error,
			 LIBCERROR_ERROR_DOMAIN_RUNTIME,
			 LIBCERROR_RUNTIME_ERROR_VALUE_EXCEEDS_MAXIMUM,
			 "%s: invalid environment variables location string size value exceeds maximum.",
			 function );

			goto on_error;
		}
		value_string = system_string_allocate(
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
#if defined( HAVE_WIDE_SYSTEM_CHARACTER )
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
		 "\tEnvironment variables location\t: %" PRIs_SYSTEM "\n",
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
	libfwsi_item_list_t *shell_item_list    = NULL;
	uint8_t *link_target_identifier_data    = NULL;
	static char *function                   = "info_handle_link_target_identifier_fprint";
	size_t link_target_identifier_data_size = 0;
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
	result = liblnk_file_get_link_target_identifier_data_size(
	          info_handle->input_file,
	          &link_target_identifier_data_size,
	          error );

	if( result == -1 )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_GET_FAILED,
		 "%s: unable to retrieve link target identifier data size.",
		 function );

		goto on_error;
	}
	else if( result != 0 )
	{
		link_target_identifier_data = (uint8_t *) memory_allocate(
		                                           sizeof( uint8_t ) * link_target_identifier_data_size );

		if( link_target_identifier_data == NULL )
		{
			libcerror_error_set(
			 error,
			 LIBCERROR_ERROR_DOMAIN_MEMORY,
			 LIBCERROR_MEMORY_ERROR_INSUFFICIENT,
			 "%s: unable to create link target identifier data.",
			 function );

			goto on_error;
		}
		result = liblnk_file_copy_link_target_identifier_data(
			  info_handle->input_file,
			  link_target_identifier_data,
			  link_target_identifier_data_size,
			  error );

		if( result != 1 )
		{
			libcerror_error_set(
			 error,
			 LIBCERROR_ERROR_DOMAIN_RUNTIME,
			 LIBCERROR_RUNTIME_ERROR_COPY_FAILED,
			 "%s: unable to copy link target identifier data.",
			 function );

			goto on_error;
		}
		fprintf(
		 info_handle->notify_stream,
		 "Link target identifier:\n" );

		if( libfwsi_item_list_initialize(
		     &shell_item_list,
		     error ) != 1 )
		{
			libcerror_error_set(
			 error,
			 LIBCERROR_ERROR_DOMAIN_RUNTIME,
			 LIBCERROR_RUNTIME_ERROR_INITIALIZE_FAILED,
			 "%s: unable to create shell item list.",
			 function );

			goto on_error;
		}
		if( libfwsi_item_list_copy_from_byte_stream(
		     shell_item_list,
		     link_target_identifier_data,
		     link_target_identifier_data_size,
		     info_handle->ascii_codepage,
		     error ) != 1 )
		{
			libcerror_error_set(
			 error,
			 LIBCERROR_ERROR_DOMAIN_RUNTIME,
			 LIBCERROR_RUNTIME_ERROR_COPY_FAILED,
			 "%s: unable to copy shell item list from byte stream.",
			 function );

			goto on_error;
		}
		if( shell_items_item_list_fprint(
		     shell_item_list,
		     info_handle->notify_stream,
		     error ) == -1 )
		{
			libcerror_error_set(
			 error,
			 LIBCERROR_ERROR_DOMAIN_RUNTIME,
			 LIBCERROR_RUNTIME_ERROR_PRINT_FAILED,
			 "%s: unable to print shell item list.",
			 function );

			goto on_error;
		}
		if( libfwsi_item_list_free(
		     &shell_item_list,
		     error ) != 1 )
		{
			libcerror_error_set(
			 error,
			 LIBCERROR_ERROR_DOMAIN_RUNTIME,
			 LIBCERROR_RUNTIME_ERROR_FINALIZE_FAILED,
			 "%s: unable to free shell item list.",
			 function );

			goto on_error;
		}
		fprintf(
		 info_handle->notify_stream,
		 "\n" );

		memory_free(
		 link_target_identifier_data );

		link_target_identifier_data = NULL;
	}
	return( 1 );

on_error:
	if( shell_item_list != NULL )
	{
		libfwsi_item_list_free(
		 &shell_item_list,
		 NULL );
	}
	if( link_target_identifier_data != NULL )
	{
		memory_free(
		 link_target_identifier_data );
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

	system_character_t *value_string = NULL;
	static char *function            = "info_handle_distributed_link_tracking_fprint";
	size_t value_string_size         = 0;
	int result                       = 0;

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

#if defined( HAVE_WIDE_SYSTEM_CHARACTER )
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
		if( ( value_string_size == 0 )
		 || ( value_string_size > ( (size_t) SSIZE_MAX / sizeof( system_character_t ) ) ) )
		{
			libcerror_error_set(
			 error,
			 LIBCERROR_ERROR_DOMAIN_RUNTIME,
			 LIBCERROR_RUNTIME_ERROR_VALUE_OUT_OF_BOUNDS,
			 "%s: invalid machine identifier size value out of bounds.",
			 function );

			goto on_error;
		}
		value_string = system_string_allocate(
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
#if defined( HAVE_WIDE_SYSTEM_CHARACTER )
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
		 "\tMachine identifier\t\t: %" PRIs_SYSTEM "\n",
		 value_string );

		memory_free(
		 value_string );

		value_string = NULL;

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
		if( info_handle_guid_value_fprint(
		     info_handle,
		     "\tDroid volume identifier\t\t",
		     guid_data,
		     error ) != 1 )
		{
			libcerror_error_set(
			 error,
			 LIBCERROR_ERROR_DOMAIN_RUNTIME,
			 LIBCERROR_RUNTIME_ERROR_PRINT_FAILED,
			 "%s: unable to print GUID value.",
			 function );

			goto on_error;
		}
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
		if( info_handle_guid_value_fprint(
		     info_handle,
		     "\tDroid file identifier\t\t",
		     guid_data,
		     error ) != 1 )
		{
			libcerror_error_set(
			 error,
			 LIBCERROR_ERROR_DOMAIN_RUNTIME,
			 LIBCERROR_RUNTIME_ERROR_PRINT_FAILED,
			 "%s: unable to print GUID value.",
			 function );

			goto on_error;
		}
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
		if( info_handle_guid_value_fprint(
		     info_handle,
		     "\tBirth droid volume identifier\t",
		     guid_data,
		     error ) != 1 )
		{
			libcerror_error_set(
			 error,
			 LIBCERROR_ERROR_DOMAIN_RUNTIME,
			 LIBCERROR_RUNTIME_ERROR_PRINT_FAILED,
			 "%s: unable to print GUID value.",
			 function );

			goto on_error;
		}
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
		if( info_handle_guid_value_fprint(
		     info_handle,
		     "\tBirth droid file identifier\t",
		     guid_data,
		     error ) != 1 )
		{
			libcerror_error_set(
			 error,
			 LIBCERROR_ERROR_DOMAIN_RUNTIME,
			 LIBCERROR_RUNTIME_ERROR_PRINT_FAILED,
			 "%s: unable to print GUID value.",
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

