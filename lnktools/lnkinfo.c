/*
 * Shows information obtained from a Windows Shortcut File (LNK)
 *
 * Copyright (c) 2009-2010, Joachim Metz <jbmetz@users.sourceforge.net>
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

#include <liberror.h>

#include <stdio.h>

#if defined( HAVE_UNISTD_H )
#include <unistd.h>
#endif

#if defined( HAVE_STDLIB_H ) || defined( WINAPI )
#include <stdlib.h>
#endif

/* Define HAVE_LOCAL_LIBFDATETIME for local use of libfdatetime
 */
#if defined( HAVE_LOCAL_LIBFDATETIME )

#include <libfdatetime_date_time_values.h>
#include <libfdatetime_definitions.h>
#include <libfdatetime_error.h>
#include <libfdatetime_fat_date_time.h>
#include <libfdatetime_filetime.h>
#include <libfdatetime_types.h>

#elif defined( HAVE_LIBFDATETIME_H )

/* If libtool DLL support is enabled set LIBFDATETIME_DLL_IMPORT
 * before including libfdatetime.h
 */
#if defined( _WIN32 ) && defined( DLL_IMPORT )
#define LIBFDATETIME_DLL_IMPORT
#endif

#include <libfdatetime.h>

#else
#error Missing libfdatetime.h
#endif

/* If libtool DLL support is enabled set LIBLNK_DLL_IMPORT
 * before including liblnk.h
 */
#if defined( _WIN32 ) && defined( DLL_EXPORT )
#define LIBLNK_DLL_IMPORT
#endif

#include <liblnk.h>

#include <libsystem.h>

#include "lnkinput.h"
#include "lnkoutput.h"

/* Prints the executable usage information
 */
void usage_fprint(
      FILE *stream )
{
	if( stream == NULL )
	{
		return;
	}
	fprintf( stream, "Use lnkinfo to determine information about a Windows Shortcut File (LNK).\n\n" );

	fprintf( stream, "Usage: lnkinfo [ -c codepage ] [ -hvV ] source\n\n" );

	fprintf( stream, "\tsource: the source file\n\n" );

	fprintf( stream, "\t-c:     codepage of ASCII strings, options: ascii, windows-874, windows-1250,\n"
	                 "\t        windows-1251, windows-1252 (default), windows-1253, windows-1254,\n"
	                 "\t        windows-1255, windows-1256, windows-1257 or windows-1258\n" );
	fprintf( stream, "\t-h:     shows this help\n" );
	fprintf( stream, "\t-v:     verbose output to stderr\n" );
	fprintf( stream, "\t-V:     print version\n" );
}

/* Prints file information
 * Returns 1 if successful or -1 on error
 */
int lnkinfo_file_info_fprint(
     FILE *stream,
     liblnk_file_t *file,
     liblnk_error_t **error )
{
	libcstring_system_character_t filetime_string[ 24 ];

	libfdatetime_filetime_t *filetime           = NULL;
	libcstring_system_character_t *value_string = NULL;
	static char *function                       = "lnkinfo_file_info_fprint";
	size_t value_string_size                    = 0;
	uint64_t value_64bit                        = 0;
	uint32_t data_flags                         = 0;
	uint32_t file_attribute_flags               = 0;
	int result                                  = 0;

	if( stream == NULL )
	{
		liberror_error_set(
		 error,
		 LIBERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid stream.",
		 function );

		return( -1 );
	}
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
	if( liblnk_file_get_data_flags(
	     file,
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
	fprintf(
	 stream,
	 "Windows Shortcut information:\n" );

	if( ( data_flags & LIBLNK_DATA_FLAG_HAS_LINK_TARGET_IDENTIFIER ) != 0 )
	{
		fprintf(
		 stream,
		 "\tContains a link target identifier\n" );
	}
	fprintf(
	 stream,
	 "\n" );

	result = liblnk_file_link_refers_to_file(
	          file,
	          error );

	if( result == -1 )
	{
		liberror_error_set(
		 error,
		 LIBERROR_ERROR_DOMAIN_RUNTIME,
		 LIBERROR_RUNTIME_ERROR_GET_FAILED,
		 "%s: unable to determine if the shortcut refers to a file.",
		 function );

		return( -1 );
	}
	else if( result != 0 )
	{
		fprintf(
		 stream,
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

			return( -1 );
		}
		if( liblnk_file_get_file_attribute_flags(
		     file,
		     &file_attribute_flags,
		     error ) != 1 )
		{
			liberror_error_set(
			 error,
			 LIBERROR_ERROR_DOMAIN_RUNTIME,
			 LIBERROR_RUNTIME_ERROR_GET_FAILED,
			 "%s: unable to retrieve file attribute flags.",
			 function );

			libfdatetime_filetime_free(
			 &filetime,
			 NULL );

			return( -1 );
		}
		/* Creation time
		 */
		if( liblnk_file_get_file_creation_time(
		     file,
		     &value_64bit,
		     error ) != 1 )
		{
			liberror_error_set(
			 error,
			 LIBERROR_ERROR_DOMAIN_RUNTIME,
			 LIBERROR_RUNTIME_ERROR_GET_FAILED,
			 "%s: unable to retrieve file creation time.",
			 function );

			libfdatetime_filetime_free(
			 &filetime,
			 NULL );

			return( -1 );
		}
		if( libfdatetime_filetime_copy_from_uint64(
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

			libfdatetime_filetime_free(
			 &filetime,
			 NULL );

			return( -1 );
		}
#if defined( LIBCSTRING_HAVE_WIDE_SYSTEM_CHARACTER )
		result = libfdatetime_filetime_copy_to_utf16_string(
			  filetime,
			  (uint16_t *) filetime_string,
			  24,
			  LIBFDATETIME_STRING_FORMAT_FLAG_DATE_TIME,
			  LIBFDATETIME_DATE_TIME_FORMAT_CTIME,
			  error );
#else
		result = libfdatetime_filetime_copy_to_utf8_string(
			  filetime,
			  (uint8_t *) filetime_string,
			  24,
			  LIBFDATETIME_STRING_FORMAT_FLAG_DATE_TIME,
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

			libfdatetime_filetime_free(
			 &filetime,
			 NULL );

			return( -1 );
		}
		fprintf(
		 stream,
		 "\tCreation time\t\t: %" PRIs_LIBCSTRING_SYSTEM " UTC\n",
		 filetime_string );

		/* Modification time
		 */
		if( liblnk_file_get_file_modification_time(
		     file,
		     &value_64bit,
		     error ) != 1 )
		{
			liberror_error_set(
			 error,
			 LIBERROR_ERROR_DOMAIN_RUNTIME,
			 LIBERROR_RUNTIME_ERROR_GET_FAILED,
			 "%s: unable to retrieve file modification time.",
			 function );

			libfdatetime_filetime_free(
			 &filetime,
			 NULL );

			return( -1 );
		}
		if( libfdatetime_filetime_copy_from_uint64(
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

			libfdatetime_filetime_free(
			 &filetime,
			 NULL );

			return( -1 );
		}
#if defined( LIBCSTRING_HAVE_WIDE_SYSTEM_CHARACTER )
		result = libfdatetime_filetime_copy_to_utf16_string(
			  filetime,
			  (uint16_t *) filetime_string,
			  24,
			  LIBFDATETIME_STRING_FORMAT_FLAG_DATE_TIME,
			  LIBFDATETIME_DATE_TIME_FORMAT_CTIME,
			  error );
#else
		result = libfdatetime_filetime_copy_to_utf8_string(
			  filetime,
			  (uint8_t *) filetime_string,
			  24,
			  LIBFDATETIME_STRING_FORMAT_FLAG_DATE_TIME,
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

			libfdatetime_filetime_free(
			 &filetime,
			 NULL );

			return( -1 );
		}
		fprintf(
		 stream,
		 "\tModification time\t: %" PRIs_LIBCSTRING_SYSTEM " UTC\n",
		 filetime_string );

		/* Access time
		 */
		if( liblnk_file_get_file_access_time(
		     file,
		     &value_64bit,
		     error ) != 1 )
		{
			liberror_error_set(
			 error,
			 LIBERROR_ERROR_DOMAIN_RUNTIME,
			 LIBERROR_RUNTIME_ERROR_GET_FAILED,
			 "%s: unable to retrieve file access time.",
			 function );

			libfdatetime_filetime_free(
			 &filetime,
			 NULL );

			return( -1 );
		}
		if( libfdatetime_filetime_copy_from_uint64(
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

			libfdatetime_filetime_free(
			 &filetime,
			 NULL );

			return( -1 );
		}
#if defined( LIBCSTRING_HAVE_WIDE_SYSTEM_CHARACTER )
		result = libfdatetime_filetime_copy_to_utf16_string(
			  filetime,
			  (uint16_t *) filetime_string,
			  24,
			  LIBFDATETIME_STRING_FORMAT_FLAG_DATE_TIME,
			  LIBFDATETIME_DATE_TIME_FORMAT_CTIME,
			  error );
#else
		result = libfdatetime_filetime_copy_to_utf8_string(
			  filetime,
			  (uint8_t *) filetime_string,
			  24,
			  LIBFDATETIME_STRING_FORMAT_FLAG_DATE_TIME,
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

			libfdatetime_filetime_free(
			 &filetime,
			 NULL );

			return( -1 );
		}
		fprintf(
		 stream,
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

			return( -1 );
		}
#if defined( LIBCSTRING_HAVE_WIDE_SYSTEM_CHARACTER )
		result = liblnk_file_get_utf16_local_path_size(
		          file,
		          &value_string_size,
		          error );
#else
		result = liblnk_file_get_utf8_local_path_size(
		          file,
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

			return( -1 );
		}
		else if( result != 0 )
		{
			value_string = (libcstring_system_character_t *) memory_allocate(
			                                                  sizeof( libcstring_system_character_t ) * value_string_size );

			if( value_string == NULL )
			{
				liberror_error_set(
				 error,
				 LIBERROR_ERROR_DOMAIN_MEMORY,
				 LIBERROR_MEMORY_ERROR_INSUFFICIENT,
				 "%s: unable to create local path value string.",
				 function );

				return( -1 );
			}
#if defined( LIBCSTRING_HAVE_WIDE_SYSTEM_CHARACTER )
			result = liblnk_file_get_utf8_local_path(
			          file,
			          (uint16_t *) value_string,
			          value_string_size,
			          error );
#else
			result = liblnk_file_get_utf8_local_path(
			          file,
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

				memory_free(
				 value_string );

				return( -1 );
			}
			fprintf(
			 stream,
			 "\tLocal path\t\t: %s\n",
			 value_string );

			memory_free(
			 value_string );
		}
#if defined( LIBCSTRING_HAVE_WIDE_SYSTEM_CHARACTER )
		result = liblnk_file_get_utf16_network_path_size(
		          file,
		          &value_string_size,
		          error );
#else
		result = liblnk_file_get_utf8_network_path_size(
		          file,
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

			return( -1 );
		}
		else if( result != 0 )
		{
			value_string = (libcstring_system_character_t *) memory_allocate(
			                                                  sizeof( libcstring_system_character_t ) * value_string_size );

			if( value_string == NULL )
			{
				liberror_error_set(
				 error,
				 LIBERROR_ERROR_DOMAIN_MEMORY,
				 LIBERROR_MEMORY_ERROR_INSUFFICIENT,
				 "%s: unable to create local path value string.",
				 function );

				return( -1 );
			}
#if defined( LIBCSTRING_HAVE_WIDE_SYSTEM_CHARACTER )
			result = liblnk_file_get_utf16_network_path(
			          file,
			          (uint16_t *) value_string,
			          value_string_size,
			          error );
#else
			result = liblnk_file_get_utf8_network_path(
			          file,
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

				memory_free(
				 value_string );

				return( -1 );
			}
			fprintf(
			 stream,
			 "\tNetwork path\t\t: %s\n",
			 value_string );

			memory_free(
			 value_string );
		}
	}
	fprintf(
	 stream,
	 "\n" );

	return( 1 );
}

/* The main program
 */
#if defined( LIBCSTRING_HAVE_WIDE_SYSTEM_CHARACTER )
int wmain( int argc, wchar_t * const argv[] )
#else
int main( int argc, char * const argv[] )
#endif
{
	liblnk_error_t *error                 = NULL;
	liblnk_file_t *lnk_file               = NULL;
	libcstring_system_character_t *source = NULL;
	char *program                         = "lnkinfo";
	libcstring_system_integer_t option    = 0;
	int ascii_codepage                    = LIBLNK_CODEPAGE_WINDOWS_1252;
	int verbose                           = 0;

	libsystem_notify_set_stream(
	 stderr,
	 NULL );
	libsystem_notify_set_verbose(
	 1 );

        if( libsystem_initialize(
             &error ) != 1 )
	{
		fprintf(
		 stderr,
		 "Unable to initialize system values.\n" );

		libsystem_notify_print_error_backtrace(
		 error );
		liberror_error_free(
		 &error );

		return( EXIT_FAILURE );
	}
	lnkoutput_version_fprint(
	 stdout,
	 program );

	while( ( option = libsystem_getopt(
	                   argc,
	                   argv,
	                   _LIBCSTRING_SYSTEM_STRING( "c:hvV" ) ) ) != (libcstring_system_integer_t) -1 )
	{
		switch( option )
		{
			case (libcstring_system_integer_t) '?':
			default:
				fprintf(
				 stderr,
				 "Invalid argument: %" PRIs_LIBCSTRING_SYSTEM "\n",
				 argv[ optind ] );

				usage_fprint(
				 stdout );

				return( EXIT_FAILURE );

			case (libcstring_system_integer_t) 'c':
				if( lnkinput_determine_ascii_codepage(
				     optarg,
				     &ascii_codepage,
				     &error ) != 1 )
				{
					libsystem_notify_print_error_backtrace(
					 error );
					liberror_error_free(
					 &error );

					ascii_codepage = LIBLNK_CODEPAGE_WINDOWS_1252;

					fprintf(
					 stderr,
					 "Unsupported ASCII codepage defaulting to: windows-1252.\n" );
				}
				break;

			case (libcstring_system_integer_t) 'h':
				usage_fprint(
				 stdout );

				return( EXIT_SUCCESS );

			case (libcstring_system_integer_t) 'v':
				verbose = 1;

				break;

			case (libcstring_system_integer_t) 'V':
				lnkoutput_copyright_fprint(
				 stdout );

				return( EXIT_SUCCESS );
		}
	}
	if( optind == argc )
	{
		fprintf(
		 stderr,
		 "Missing source file.\n" );

		usage_fprint(
		 stdout );

		return( EXIT_FAILURE );
	}
	source = argv[ optind ];

	libsystem_notify_set_verbose(
	 verbose );
	liblnk_notify_set_stream(
	 stderr,
	 NULL );
	liblnk_notify_set_verbose(
	 verbose );

	if( liblnk_file_initialize(
	     &lnk_file,
	     &error ) != 1 )
	{
		fprintf(
		 stderr,
		 "Unable to initialize liblnk file.\n" );

		libsystem_notify_print_error_backtrace(
		 error );
		liblnk_error_free(
		 &error );

		return( EXIT_FAILURE );
	}
	if( liblnk_file_set_ascii_codepage(
	     lnk_file,
	     ascii_codepage,
	     &error ) != 1 )
	{
		fprintf(
		 stderr,
		 "Unable to set ASCII codepage.\n" );

		libsystem_notify_print_error_backtrace(
		 error );
		liblnk_error_free(
		 &error );

		liblnk_file_free(
		 &lnk_file,
		 NULL );

		return( EXIT_FAILURE );
	}
#if defined( LIBCSTRING_HAVE_WIDE_SYSTEM_CHARACTER )
	if( liblnk_file_open_wide(
	     lnk_file,
	     source,
	     LIBLNK_OPEN_READ,
	     &error ) != 1 )
#else
	if( liblnk_file_open(
	     lnk_file,
	     source,
	     LIBLNK_OPEN_READ,
	     &error ) != 1 )
#endif
	{
		fprintf(
		 stderr,
		 "Error opening file: %" PRIs_LIBCSTRING_SYSTEM ".\n",
		 argv[ optind ] );

		libsystem_notify_print_error_backtrace(
		 error );
		liblnk_error_free(
		 &error );

		liblnk_file_free(
		 &lnk_file,
		 NULL );

		return( EXIT_FAILURE );
	}
	if( lnkinfo_file_info_fprint(
	     stdout,
	     lnk_file,
	     &error ) != 1 )
	{
		fprintf(
		 stderr,
		 "Unable to print file information.\n" );

		libsystem_notify_print_error_backtrace(
		 error );
		liblnk_error_free(
		 &error );

		liblnk_file_free(
		 &lnk_file,
		 NULL );

		return( EXIT_FAILURE );
	}
	if( liblnk_file_close(
	     lnk_file,
	     &error ) != 0 )
	{
		fprintf(
		 stderr,
		 "Error closing file: %" PRIs_LIBCSTRING_SYSTEM ".\n",
		 argv[ optind ] );

		libsystem_notify_print_error_backtrace(
		 error );
		liblnk_error_free(
		 &error );

		liblnk_file_free(
		 &lnk_file,
		 NULL );

		return( EXIT_FAILURE );
	}
	if( liblnk_file_free(
	     &lnk_file,
	     &error ) != 1 )
	{
		fprintf(
		 stderr,
		 "Unable to free liblnk file.\n" );

		libsystem_notify_print_error_backtrace(
		 error );
		liblnk_error_free(
		 &error );

		return( EXIT_FAILURE );
	}
	return( EXIT_SUCCESS );
}

