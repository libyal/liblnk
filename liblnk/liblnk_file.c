/*
 * liblnk file
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
#include <narrow_string.h>
#include <memory.h>
#include <types.h>
#include <wide_string.h>

#include <liberror.h>
#include <libnotify.h>

#include <liblnk/codepage.h>

#include "liblnk_data_string.h"
#include "liblnk_definitions.h"
#include "liblnk_io_handle.h"
#include "liblnk_file.h"
#include "liblnk_file_information.h"
#include "liblnk_libbfio.h"
#include "liblnk_location_information.h"
#include "liblnk_shell_item_identifiers.h"

#include "lnk_file_header.h"

/* Initialize a file
 * Make sure the value file is pointing to is set to NULL
 * Returns 1 if successful or -1 on error
 */
int liblnk_file_initialize(
     liblnk_file_t **file,
     liberror_error_t **error )
{
	liblnk_internal_file_t *internal_file = NULL;
	static char *function                 = "liblnk_file_initialize";

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
	if( *file == NULL )
	{
		internal_file = (liblnk_internal_file_t *) memory_allocate(
		                                            sizeof( liblnk_internal_file_t ) );

		if( internal_file == NULL )
		{
			liberror_error_set(
			 error,
			 LIBERROR_ERROR_DOMAIN_MEMORY,
			 LIBERROR_MEMORY_ERROR_INSUFFICIENT,
			 "%s: unable to create file.",
			 function );

			return( -1 );
		}
		if( memory_set(
		     internal_file,
		     0,
		     sizeof( liblnk_internal_file_t ) ) == NULL )
		{
			liberror_error_set(
			 error,
			 LIBERROR_ERROR_DOMAIN_MEMORY,
			 LIBERROR_MEMORY_ERROR_SET_FAILED,
			 "%s: unable to clear file.",
			 function );

			memory_free(
			 internal_file );

			return( -1 );
		}
		if( liblnk_file_information_initialize(
		     &( internal_file->file_information ),
		     error ) != 1 )
		{
			liberror_error_set(
			 error,
			 LIBERROR_ERROR_DOMAIN_RUNTIME,
			 LIBERROR_RUNTIME_ERROR_INITIALIZE_FAILED,
			 "%s: unable to initialize file information.",
			 function );

			memory_free(
			 internal_file );

			return( -1 );
		}
		if( liblnk_io_handle_initialize(
		     &( internal_file->io_handle ),
		     error ) != 1 )
		{
			liberror_error_set(
			 error,
			 LIBERROR_ERROR_DOMAIN_RUNTIME,
			 LIBERROR_RUNTIME_ERROR_INITIALIZE_FAILED,
			 "%s: unable to initialize io handle.",
			 function );

			liblnk_file_information_free(
			 &( internal_file->file_information ),
			 NULL );
			memory_free(
			 internal_file );

			return( -1 );
		}
		internal_file->ascii_codepage = LIBLNK_CODEPAGE_WINDOWS_1250;

		*file = (liblnk_file_t *) internal_file;
	}
	return( 1 );
}

/* Frees an exisisting file
 * Returns 1 if successful or -1 on error
 */
int liblnk_file_free(
     liblnk_file_t **file,
     liberror_error_t **error )
{
	liblnk_internal_file_t *internal_file = NULL;
	static char *function                 = "liblnk_file_free";
	int result                            = 1;

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
	if( *file != NULL )
	{
		internal_file = (liblnk_internal_file_t *) *file;

		if( ( internal_file->file_information != NULL )
		 && ( liblnk_file_information_free(
		       &( internal_file->file_information ),
		       error ) != 1 ) )
		{
			liberror_error_set(
			 error,
			 LIBERROR_ERROR_DOMAIN_RUNTIME,
			 LIBERROR_RUNTIME_ERROR_FINALIZE_FAILED,
			 "%s: unable to free file information.",
			 function );

			result = -1;
		}
		if( ( internal_file->shell_item_identifiers != NULL )
		 && ( liblnk_shell_item_identifiers_free(
		       &( internal_file->shell_item_identifiers ),
		       error ) != 1 ) )
		{
			liberror_error_set(
			 error,
			 LIBERROR_ERROR_DOMAIN_RUNTIME,
			 LIBERROR_RUNTIME_ERROR_FINALIZE_FAILED,
			 "%s: unable to free shell item identifiers.",
			 function );

			result = -1;
		}
		if( ( internal_file->location_information != NULL )
		 && ( liblnk_location_information_free(
		       &( internal_file->location_information ),
		       error ) != 1 ) )
		{
			liberror_error_set(
			 error,
			 LIBERROR_ERROR_DOMAIN_RUNTIME,
			 LIBERROR_RUNTIME_ERROR_FINALIZE_FAILED,
			 "%s: unable to free location information.",
			 function );

			result = -1;
		}
		if( ( internal_file->description != NULL )
		 && ( liblnk_data_string_free(
		       &( internal_file->description ),
		       error ) != 1 ) )
		{
			liberror_error_set(
			 error,
			 LIBERROR_ERROR_DOMAIN_RUNTIME,
			 LIBERROR_RUNTIME_ERROR_FINALIZE_FAILED,
			 "%s: unable to free description.",
			 function );

			result = -1;
		}
		if( ( internal_file->relative_path != NULL )
		 && ( liblnk_data_string_free(
		       &( internal_file->relative_path ),
		       error ) != 1 ) )
		{
			liberror_error_set(
			 error,
			 LIBERROR_ERROR_DOMAIN_RUNTIME,
			 LIBERROR_RUNTIME_ERROR_FINALIZE_FAILED,
			 "%s: unable to free relative path.",
			 function );

			result = -1;
		}
		if( ( internal_file->working_directory != NULL )
		 && ( liblnk_data_string_free(
		       &( internal_file->working_directory ),
		       error ) != 1 ) )
		{
			liberror_error_set(
			 error,
			 LIBERROR_ERROR_DOMAIN_RUNTIME,
			 LIBERROR_RUNTIME_ERROR_FINALIZE_FAILED,
			 "%s: unable to free working directory.",
			 function );

			result = -1;
		}
		if( ( internal_file->command_line_arguments != NULL )
		 && ( liblnk_data_string_free(
		       &( internal_file->command_line_arguments ),
		       error ) != 1 ) )
		{
			liberror_error_set(
			 error,
			 LIBERROR_ERROR_DOMAIN_RUNTIME,
			 LIBERROR_RUNTIME_ERROR_FINALIZE_FAILED,
			 "%s: unable to free command line arguments.",
			 function );

			result = -1;
		}
		if( ( internal_file->custom_icon_filename != NULL )
		 && ( liblnk_data_string_free(
		       &( internal_file->custom_icon_filename ),
		       error ) != 1 ) )
		{
			liberror_error_set(
			 error,
			 LIBERROR_ERROR_DOMAIN_RUNTIME,
			 LIBERROR_RUNTIME_ERROR_FINALIZE_FAILED,
			 "%s: unable to free custom icon filename.",
			 function );

			result = -1;
		}
		if( ( internal_file->io_handle != NULL )
		 && ( liblnk_io_handle_free(
		       &( internal_file->io_handle ),
		       error ) != 1 ) )
		{
			liberror_error_set(
			 error,
			 LIBERROR_ERROR_DOMAIN_RUNTIME,
			 LIBERROR_RUNTIME_ERROR_FINALIZE_FAILED,
			 "%s: unable to free io handle.",
			 function );

			result = -1;
		}
		memory_free(
		 internal_file );

		*file = NULL;
	}
	return( result );
}

/* Signals the liblnk file to abort its current activity
 * Returns 1 if successful or -1 on error
 */
int liblnk_file_signal_abort(
     liblnk_file_t *file,
     liberror_error_t **error )
{
	static char *function = "liblnk_file_signal_abort";

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
	( (liblnk_internal_file_t *) file )->abort = 1;

	return( 1 );
}

/* Opens a Windows Shortcut file
 * Returns 1 if successful or -1 on error
 */
int liblnk_file_open(
     liblnk_file_t *file,
     const char *filename,
     int flags,
     liberror_error_t **error )
{
	libbfio_handle_t *file_io_handle      = NULL;
	liblnk_internal_file_t *internal_file = NULL;
	static char *function                 = "liblnk_file_open";

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
	if( filename == NULL )
	{
		liberror_error_set(
		 error,
		 LIBERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid filename.",
		 function );

		return( -1 );
	}
	if( ( ( flags & LIBLNK_FLAG_READ ) != LIBLNK_FLAG_READ )
	 && ( ( flags & LIBLNK_FLAG_WRITE ) != LIBLNK_FLAG_WRITE ) )
	{
		liberror_error_set(
		 error,
		 LIBERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBERROR_ARGUMENT_ERROR_UNSUPPORTED_VALUE,
		 "%s: unsupported flags.",
		 function );

		return( -1 );
	}
	if( ( flags & LIBLNK_FLAG_WRITE ) == LIBLNK_FLAG_WRITE )
	{
		liberror_error_set(
		 error,
		 LIBERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBERROR_ARGUMENT_ERROR_UNSUPPORTED_VALUE,
		 "%s: write access to Windows Shortcut files currently not supported.",
		 function );

		return( -1 );
	}
	internal_file = (liblnk_internal_file_t *) file;

	if( libbfio_file_initialize(
	     &file_io_handle,
	     error ) != 1 )
	{
		liberror_error_set(
		 error,
		 LIBERROR_ERROR_DOMAIN_RUNTIME,
		 LIBERROR_RUNTIME_ERROR_INITIALIZE_FAILED,
		 "%s: unable to initialize file io handle.",
		 function );

		return( -1 );
	}
#if defined( HAVE_DEBUG_OUTPUT )
	if( libbfio_handle_set_track_offsets_read(
	     file_io_handle,
	     1,
	     error ) != 1 )
	{
                liberror_error_set(
                 error,
                 LIBERROR_ERROR_DOMAIN_RUNTIME,
                 LIBERROR_RUNTIME_ERROR_SET_FAILED,
                 "%s: unable to set track offsets read in file io handle.",
                 function );

                return( -1 );
	}
#endif
	if( libbfio_file_set_name(
	     file_io_handle,
	     filename,
	     narrow_string_length(
	      filename ) + 1,
	     error ) != 1 )
	{
                liberror_error_set(
                 error,
                 LIBERROR_ERROR_DOMAIN_RUNTIME,
                 LIBERROR_RUNTIME_ERROR_SET_FAILED,
                 "%s: unable to set filename in file io handle.",
                 function );

                return( -1 );
	}
	if( liblnk_file_open_file_io_handle(
	     file,
	     file_io_handle,
	     flags,
	     error ) != 1 )
	{
		liberror_error_set(
		 error,
		 LIBERROR_ERROR_DOMAIN_IO,
		 LIBERROR_IO_ERROR_OPEN_FAILED,
		 "%s: unable to open file: %s.",
		 function,
		 filename );

		return( -1 );
	}
	internal_file->io_handle->handle_created_in_library = 1;

	return( 1 );
}

#if defined( HAVE_WIDE_CHARACTER_TYPE )

/* Opens a Windows Shortcut file
 * Returns 1 if successful or -1 on error
 */
int liblnk_file_open_wide(
     liblnk_file_t *file,
     const wchar_t *filename,
     int flags,
     liberror_error_t **error )
{
	libbfio_handle_t *file_io_handle      = NULL;
	liblnk_internal_file_t *internal_file = NULL;
	static char *function                 = "liblnk_file_open_wide";

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
	if( filename == NULL )
	{
		liberror_error_set(
		 error,
		 LIBERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid filename.",
		 function );

		return( -1 );
	}
	if( ( ( flags & LIBLNK_FLAG_READ ) != LIBLNK_FLAG_READ )
	 && ( ( flags & LIBLNK_FLAG_WRITE ) != LIBLNK_FLAG_WRITE ) )
	{
		liberror_error_set(
		 error,
		 LIBERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBERROR_ARGUMENT_ERROR_UNSUPPORTED_VALUE,
		 "%s: unsupported flags.",
		 function );

		return( -1 );
	}
	if( ( flags & LIBLNK_FLAG_WRITE ) == LIBLNK_FLAG_WRITE )
	{
		liberror_error_set(
		 error,
		 LIBERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBERROR_ARGUMENT_ERROR_UNSUPPORTED_VALUE,
		 "%s: write access to Windows Shortcut files currently not supported.",
		 function );

		return( -1 );
	}
	internal_file = (liblnk_internal_file_t *) file;

	if( libbfio_file_initialize(
	     &file_io_handle,
	     error ) != 1 )
	{
		liberror_error_set(
		 error,
		 LIBERROR_ERROR_DOMAIN_RUNTIME,
		 LIBERROR_RUNTIME_ERROR_INITIALIZE_FAILED,
		 "%s: unable to initialize file io handle.",
		 function );

		return( -1 );
	}
#if defined( HAVE_DEBUG_OUTPUT )
	if( libbfio_handle_set_track_offsets_read(
	     file_io_handle,
	     1,
	     error ) != 1 )
	{
                liberror_error_set(
                 error,
                 LIBERROR_ERROR_DOMAIN_RUNTIME,
                 LIBERROR_RUNTIME_ERROR_SET_FAILED,
                 "%s: unable to set track offsets read in file io handle.",
                 function );

                return( -1 );
	}
#endif
	if( libbfio_file_set_name_wide(
	     file_io_handle,
	     filename,
	     narrow_string_length(
	      filename ) + 1,
	     error ) != 1 )
	{
                liberror_error_set(
                 error,
                 LIBERROR_ERROR_DOMAIN_RUNTIME,
                 LIBERROR_RUNTIME_ERROR_SET_FAILED,
                 "%s: unable to set filename in file io handle.",
                 function );

                return( -1 );
	}
	if( liblnk_file_open_file_io_handle(
	     file,
	     file_io_handle,
	     flags,
	     error ) != 1 )
	{
		liberror_error_set(
		 error,
		 LIBERROR_ERROR_DOMAIN_IO,
		 LIBERROR_IO_ERROR_OPEN_FAILED,
		 "%s: unable to open file: %ls.",
		 function,
		 filename );

		return( -1 );
	}
	internal_file->io_handle->handle_created_in_library = 1;

	return( 1 );
}

#endif

/* Opens a Windows Shortcut file using a Basic File IO (bfio) handle
 * Returns 1 if successful or -1 on error
 */
int liblnk_file_open_file_io_handle(
     liblnk_file_t *file,
     libbfio_handle_t *file_io_handle,
     int flags,
     liberror_error_t **error )
{
	liblnk_internal_file_t *internal_file = NULL;
	static char *function                 = "liblnk_file_open_file_io_handle";
	int file_io_flags                     = 0;

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
	if( ( ( flags & LIBLNK_FLAG_READ ) != LIBLNK_FLAG_READ )
	 && ( ( flags & LIBLNK_FLAG_WRITE ) != LIBLNK_FLAG_WRITE ) )
	{
		liberror_error_set(
		 error,
		 LIBERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBERROR_ARGUMENT_ERROR_UNSUPPORTED_VALUE,
		 "%s: unsupported flags.",
		 function );

		return( -1 );
	}
	if( ( flags & LIBLNK_FLAG_WRITE ) == LIBLNK_FLAG_WRITE )
	{
		liberror_error_set(
		 error,
		 LIBERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBERROR_ARGUMENT_ERROR_UNSUPPORTED_VALUE,
		 "%s: write access to personal folder files currently not supported.",
		 function );

		return( -1 );
	}
	internal_file = (liblnk_internal_file_t *) file;

	if( ( flags & LIBLNK_FLAG_READ ) == LIBLNK_FLAG_READ )
	{
		file_io_flags = LIBBFIO_FLAG_READ;
	}
	if( liblnk_io_handle_open(
	     internal_file->io_handle,
	     file_io_handle,
	     file_io_flags,
	     error ) != 1 )
	{
		liberror_error_set(
		 error,
		 LIBERROR_ERROR_DOMAIN_IO,
		 LIBERROR_IO_ERROR_OPEN_FAILED,
		 "%s: unable to open file handle.",
		 function );

		return( -1 );
	}
	if( liblnk_file_open_read(
	     internal_file,
	     error ) != 1 )
	{
		liberror_error_set(
		 error,
		 LIBERROR_ERROR_DOMAIN_IO,
		 LIBERROR_IO_ERROR_READ_FAILED,
		 "%s: unable to read from file handle.",
		 function );

		return( -1 );
	}
	return( 1 );
}

/* Closes a Windows Shortcut file
 * Returns 0 if successful or -1 on error
 */
int liblnk_file_close(
     liblnk_file_t *file,
     liberror_error_t **error )
{
	liblnk_internal_file_t *internal_file = NULL;
	static char *function                 = "liblnk_file_close";
	int result                            = 0;

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

	if( internal_file->io_handle == NULL )
	{
		liberror_error_set(
		 error,
		 LIBERROR_ERROR_DOMAIN_RUNTIME,
		 LIBERROR_RUNTIME_ERROR_VALUE_MISSING,
		 "%s: invalid file - missing io handle.",
		 function );

		return( -1 );
	}
	result = liblnk_io_handle_close(
	          internal_file->io_handle,
	          error );

	if( result != 0 )
	{
		liberror_error_set(
		 error,
		 LIBERROR_ERROR_DOMAIN_IO,
		 LIBERROR_IO_ERROR_CLOSE_FAILED,
		 "%s: unable to close io handle.",
		 function );
	}
	return( result );
}

/* Opens a Windows Shortcut file for reading
 * Returns 1 if successful or -1 on error
 */
int liblnk_file_open_read(
     liblnk_internal_file_t *internal_file,
     liberror_error_t **error )
{
	static char *function = "liblnk_file_open_read";
	off64_t file_offset   = 0;
	ssize_t read_count    = 0;

	if( internal_file == NULL )
	{
		liberror_error_set(
		 error,
		 LIBERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid internal file.",
		 function );

		return( -1 );
	}
	if( internal_file->io_handle == NULL )
	{
		liberror_error_set(
		 error,
		 LIBERROR_ERROR_DOMAIN_RUNTIME,
		 LIBERROR_RUNTIME_ERROR_VALUE_MISSING,
		 "%s: invalid internal file - missing io handle.",
		 function );

		return( -1 );
	}
#if defined( HAVE_VERBOSE_OUTPUT )
	libnotify_verbose_printf(
	 "Reading file header:\n" );
#endif
	if( liblnk_io_handle_read_file_header(
	     internal_file->io_handle,
	     &( internal_file->data_flags ),
	     internal_file->class_identifier,
	     16,
	     internal_file->file_information,
	     error ) != 1 )
	{
		liberror_error_set(
		 error,
		 LIBERROR_ERROR_DOMAIN_IO,
		 LIBERROR_IO_ERROR_READ_FAILED,
		 "%s: unable to read file header.",
		 function );

		return( -1 );
	}
	file_offset = sizeof( lnk_file_header_t );

	if( ( internal_file->data_flags & LIBLNK_DATA_FLAG_CONTAINS_SHELL_ITEMS ) == LIBLNK_DATA_FLAG_CONTAINS_SHELL_ITEMS )
	{
		if( liblnk_shell_item_identifiers_initialize(
		     &( internal_file->shell_item_identifiers ),
		     error ) != 1 )
		{
			liberror_error_set(
			 error,
			 LIBERROR_ERROR_DOMAIN_RUNTIME,
			 LIBERROR_RUNTIME_ERROR_INITIALIZE_FAILED,
			 "%s: unable to initialize shell item identifiers.",
			 function );

			return( -1 );
		}
#if defined( HAVE_VERBOSE_OUTPUT )
		libnotify_verbose_printf(
		 "Reading shell items:\n" );
#endif
		read_count = liblnk_shell_item_identifiers_read(
		              internal_file->shell_item_identifiers,
		              internal_file->io_handle->file_io_handle,
		              file_offset,
		              error );

		if( read_count <= -1 )
		{
			liberror_error_set(
			 error,
			 LIBERROR_ERROR_DOMAIN_IO,
			 LIBERROR_IO_ERROR_READ_FAILED,
			 "%s: unable to read shell item identifiers.",
			 function );

			return( -1 );
		}
		file_offset += read_count;
	}
	if( ( internal_file->data_flags & LIBLNK_DATA_FLAG_CONTAINS_LOCATION_INFORMATION ) == LIBLNK_DATA_FLAG_CONTAINS_LOCATION_INFORMATION )
	{
		if( liblnk_location_information_initialize(
		     &( internal_file->location_information ),
		     error ) != 1 )
		{
			liberror_error_set(
			 error,
			 LIBERROR_ERROR_DOMAIN_RUNTIME,
			 LIBERROR_RUNTIME_ERROR_INITIALIZE_FAILED,
			 "%s: unable to initialize location information.",
			 function );

			return( -1 );
		}
#if defined( HAVE_VERBOSE_OUTPUT )
		libnotify_verbose_printf(
		 "Reading location information:\n" );
#endif
		read_count = liblnk_location_information_read(
		              internal_file->location_information,
		              internal_file->io_handle->file_io_handle,
		              file_offset,
		              error );

		if( read_count <= -1 )
		{
			liberror_error_set(
			 error,
			 LIBERROR_ERROR_DOMAIN_IO,
			 LIBERROR_IO_ERROR_READ_FAILED,
			 "%s: unable to read location information.",
			 function );

			return( -1 );
		}
		file_offset += read_count;
	}
	if( ( internal_file->data_flags & LIBLNK_DATA_FLAG_CONTAINS_DESCRIPTION_DATA_STRING ) == LIBLNK_DATA_FLAG_CONTAINS_DESCRIPTION_DATA_STRING )
	{
		if( liblnk_data_string_initialize(
		     &( internal_file->description ),
		     error ) != 1 )
		{
			liberror_error_set(
			 error,
			 LIBERROR_ERROR_DOMAIN_RUNTIME,
			 LIBERROR_RUNTIME_ERROR_INITIALIZE_FAILED,
			 "%s: unable to initialize description.",
			 function );

			return( -1 );
		}
#if defined( HAVE_VERBOSE_OUTPUT )
		libnotify_verbose_printf(
		 "Reading description data string:\n" );
#endif
		read_count = liblnk_data_string_read(
		              internal_file->description,
		              internal_file->io_handle->file_io_handle,
		              file_offset,
		              error );

		if( read_count <= -1 )
		{
			liberror_error_set(
			 error,
			 LIBERROR_ERROR_DOMAIN_IO,
			 LIBERROR_IO_ERROR_READ_FAILED,
			 "%s: unable to read description.",
			 function );

			return( -1 );
		}
		file_offset += read_count;
	}
	if( ( internal_file->data_flags & LIBLNK_DATA_FLAG_CONTAINS_RELATIVE_PATH_DATA_STRING ) == LIBLNK_DATA_FLAG_CONTAINS_RELATIVE_PATH_DATA_STRING )
	{
		if( liblnk_data_string_initialize(
		     &( internal_file->relative_path ),
		     error ) != 1 )
		{
			liberror_error_set(
			 error,
			 LIBERROR_ERROR_DOMAIN_RUNTIME,
			 LIBERROR_RUNTIME_ERROR_INITIALIZE_FAILED,
			 "%s: unable to initialize relative path.",
			 function );

			return( -1 );
		}
#if defined( HAVE_VERBOSE_OUTPUT )
		libnotify_verbose_printf(
		 "Reading relative path data string:\n" );
#endif
		read_count = liblnk_data_string_read(
		              internal_file->relative_path,
		              internal_file->io_handle->file_io_handle,
		              file_offset,
		              error );

		if( read_count <= -1 )
		{
			liberror_error_set(
			 error,
			 LIBERROR_ERROR_DOMAIN_IO,
			 LIBERROR_IO_ERROR_READ_FAILED,
			 "%s: unable to read relative path.",
			 function );

			return( -1 );
		}
		file_offset += read_count;
	}
	if( ( internal_file->data_flags & LIBLNK_DATA_FLAG_CONTAINS_WORKING_DIRECTORY_DATA_STRING ) == LIBLNK_DATA_FLAG_CONTAINS_WORKING_DIRECTORY_DATA_STRING )
	{
		if( liblnk_data_string_initialize(
		     &( internal_file->working_directory ),
		     error ) != 1 )
		{
			liberror_error_set(
			 error,
			 LIBERROR_ERROR_DOMAIN_RUNTIME,
			 LIBERROR_RUNTIME_ERROR_INITIALIZE_FAILED,
			 "%s: unable to initialize working directory.",
			 function );

			return( -1 );
		}
#if defined( HAVE_VERBOSE_OUTPUT )
		libnotify_verbose_printf(
		 "Reading working directory data string:\n" );
#endif
		read_count = liblnk_data_string_read(
		              internal_file->working_directory,
		              internal_file->io_handle->file_io_handle,
		              file_offset,
		              error );

		if( read_count <= -1 )
		{
			liberror_error_set(
			 error,
			 LIBERROR_ERROR_DOMAIN_IO,
			 LIBERROR_IO_ERROR_READ_FAILED,
			 "%s: unable to read working directory.",
			 function );

			return( -1 );
		}
		file_offset += read_count;
	}
	if( ( internal_file->data_flags & LIBLNK_DATA_FLAG_CONTAINS_COMMAND_LINE_ARGUMENTS_DATA_STRING ) == LIBLNK_DATA_FLAG_CONTAINS_COMMAND_LINE_ARGUMENTS_DATA_STRING )
	{
		if( liblnk_data_string_initialize(
		     &( internal_file->command_line_arguments ),
		     error ) != 1 )
		{
			liberror_error_set(
			 error,
			 LIBERROR_ERROR_DOMAIN_RUNTIME,
			 LIBERROR_RUNTIME_ERROR_INITIALIZE_FAILED,
			 "%s: unable to initialize command line arguments.",
			 function );

			return( -1 );
		}
#if defined( HAVE_VERBOSE_OUTPUT )
		libnotify_verbose_printf(
		 "Reading command line arguments data string:\n" );
#endif
		read_count = liblnk_data_string_read(
		              internal_file->command_line_arguments,
		              internal_file->io_handle->file_io_handle,
		              file_offset,
		              error );

		if( read_count <= -1 )
		{
			liberror_error_set(
			 error,
			 LIBERROR_ERROR_DOMAIN_IO,
			 LIBERROR_IO_ERROR_READ_FAILED,
			 "%s: unable to read command line arguments.",
			 function );

			return( -1 );
		}
		file_offset += read_count;
	}
	if( ( internal_file->data_flags & LIBLNK_DATA_FLAG_CONTAINS_CUSTOM_ICON_FILENAME_DATA_STRING ) == LIBLNK_DATA_FLAG_CONTAINS_CUSTOM_ICON_FILENAME_DATA_STRING )
	{
		if( liblnk_data_string_initialize(
		     &( internal_file->custom_icon_filename ),
		     error ) != 1 )
		{
			liberror_error_set(
			 error,
			 LIBERROR_ERROR_DOMAIN_RUNTIME,
			 LIBERROR_RUNTIME_ERROR_INITIALIZE_FAILED,
			 "%s: unable to initialize custom icon filename.",
			 function );

			return( -1 );
		}
#if defined( HAVE_VERBOSE_OUTPUT )
		libnotify_verbose_printf(
		 "Reading custom icon filename data string:\n" );
#endif
		read_count = liblnk_data_string_read(
		              internal_file->custom_icon_filename,
		              internal_file->io_handle->file_io_handle,
		              file_offset,
		              error );

		if( read_count <= -1 )
		{
			liberror_error_set(
			 error,
			 LIBERROR_ERROR_DOMAIN_IO,
			 LIBERROR_IO_ERROR_READ_FAILED,
			 "%s: unable to read custom icon filename.",
			 function );

			return( -1 );
		}
		file_offset += read_count;
	}
	/* TODO read other parts */
#if defined( HAVE_DEBUG_OUTPUT )
	uint8_t *trailing_data    = NULL;
	size64_t file_size        = 0;
	size_t trailing_data_size = 0;

	if( libbfio_handle_get_size(
	     internal_file->io_handle->file_io_handle,
	     &file_size,
	     error ) != 1 )
	{
		liberror_error_set(
		 error,
		 LIBERROR_ERROR_DOMAIN_RUNTIME,
		 LIBERROR_RUNTIME_ERROR_GET_FAILED,
		 "%s: unable to retrieve file size.",
		 function );

		return( -1 );
	}
	if( file_offset < (off64_t) file_size )
	{
		trailing_data_size = file_size - file_offset;

		trailing_data = (uint8_t *) memory_allocate(
		                             sizeof( uint8_t ) * trailing_data_size );

		if( trailing_data == NULL )
		{
			liberror_error_set(
			 error,
			 LIBERROR_ERROR_DOMAIN_MEMORY,
			 LIBERROR_MEMORY_ERROR_INSUFFICIENT,
			 "%s: unable to create trailing data.",
			 function );

			return( -1 );
		}
		read_count = libbfio_handle_read(
			      internal_file->io_handle->file_io_handle,
			      trailing_data,
			      trailing_data_size,
			      error );

		if( read_count != (ssize_t) trailing_data_size )
		{
			liberror_error_set(
			 error,
			 LIBERROR_ERROR_DOMAIN_IO,
			 LIBERROR_IO_ERROR_READ_FAILED,
			 "%s: unable to read trailing data.",
			 function );

			return( -1 );
		}
		libnotify_verbose_printf(
		 "%s: trailing data:\n",
		 function );
		libnotify_verbose_print_data(
		 trailing_data,
		 trailing_data_size );
	}
#endif

	return( 1 );
}

/* Retrieves the file ASCII codepage
 * Returns 1 if successful or -1 on error
 */
int liblnk_file_get_ascii_codepage(
     liblnk_file_t *file,
     int *ascii_codepage,
     liberror_error_t **error )
{
	liblnk_internal_file_t *internal_file = NULL;
	static char *function                 = "liblnk_file_get_ascii_codepage";

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

	if( ascii_codepage == NULL )
	{
		liberror_error_set(
		 error,
		 LIBERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid ASCII codepage.",
		 function );

		return( -1 );
	}
	*ascii_codepage = internal_file->ascii_codepage;

	return( 1 );
}

/* Sets the file ASCII codepage
 * Returns 1 if successful or -1 on error
 */
int liblnk_file_set_ascii_codepage(
     liblnk_file_t *file,
     int ascii_codepage,
     liberror_error_t **error )
{
	liblnk_internal_file_t *internal_file = NULL;
	static char *function                 = "liblnk_file_set_ascii_codepage";

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

	if( ( ascii_codepage != LIBLNK_CODEPAGE_ASCII )
	 || ( ascii_codepage != LIBLNK_CODEPAGE_WINDOWS_1250 )
	 || ( ascii_codepage != LIBLNK_CODEPAGE_WINDOWS_1251 )
	 || ( ascii_codepage != LIBLNK_CODEPAGE_WINDOWS_1252 )
	 || ( ascii_codepage != LIBLNK_CODEPAGE_WINDOWS_1253 )
	 || ( ascii_codepage != LIBLNK_CODEPAGE_WINDOWS_1254 )
	 || ( ascii_codepage != LIBLNK_CODEPAGE_WINDOWS_1256 )
	 || ( ascii_codepage != LIBLNK_CODEPAGE_WINDOWS_1257 )
	 || ( ascii_codepage != LIBLNK_CODEPAGE_WINDOWS_1258 ) )
	{
		liberror_error_set(
		 error,
		 LIBERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBERROR_ARGUMENT_ERROR_UNSUPPORTED_VALUE,
		 "%s: unsupported ASCII codepage.",
		 function );

		return( -1 );
	}
	internal_file->ascii_codepage = ascii_codepage;

	return( 1 );
}

