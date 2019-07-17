/*
 * File functions
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
#include <memory.h>
#include <narrow_string.h>
#include <types.h>
#include <wide_string.h>

#include "liblnk_codepage.h"
#include "liblnk_data_block.h"
#include "liblnk_data_block_strings.h"
#include "liblnk_data_string.h"
#include "liblnk_debug.h"
#include "liblnk_definitions.h"
#include "liblnk_distributed_link_tracker_properties.h"
#include "liblnk_file.h"
#include "liblnk_file_header.h"
#include "liblnk_io_handle.h"
#include "liblnk_known_folder_location.h"
#include "liblnk_libbfio.h"
#include "liblnk_libcerror.h"
#include "liblnk_libcnotify.h"
#include "liblnk_libfwps.h"
#include "liblnk_libuna.h"
#include "liblnk_link_target_identifier.h"
#include "liblnk_location_information.h"
#include "liblnk_special_folder_location.h"
#include "liblnk_types.h"

/* Creates a file
 * Make sure the value file is referencing, is set to NULL
 * Returns 1 if successful or -1 on error
 */
int liblnk_file_initialize(
     liblnk_file_t **file,
     libcerror_error_t **error )
{
	liblnk_internal_file_t *internal_file = NULL;
	static char *function                 = "liblnk_file_initialize";

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
	if( *file != NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_VALUE_ALREADY_SET,
		 "%s: invalid file value already set.",
		 function );

		return( -1 );
	}
	internal_file = memory_allocate_structure(
	                 liblnk_internal_file_t );

	if( internal_file == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_MEMORY,
		 LIBCERROR_MEMORY_ERROR_INSUFFICIENT,
		 "%s: unable to create file.",
		 function );

		goto on_error;
	}
	if( memory_set(
	     internal_file,
	     0,
	     sizeof( liblnk_internal_file_t ) ) == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_MEMORY,
		 LIBCERROR_MEMORY_ERROR_SET_FAILED,
		 "%s: unable to clear file.",
		 function );

		goto on_error;
	}
	if( liblnk_io_handle_initialize(
	     &( internal_file->io_handle ),
	     error ) != 1 )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_INITIALIZE_FAILED,
		 "%s: unable to create IO handle.",
		 function );

		goto on_error;
	}
	*file = (liblnk_file_t *) internal_file;

	return( 1 );

on_error:
	if( internal_file != NULL )
	{
		memory_free(
		 internal_file );
	}
	return( -1 );
}

/* Frees a file
 * Returns 1 if successful or -1 on error
 */
int liblnk_file_free(
     liblnk_file_t **file,
     libcerror_error_t **error )
{
	liblnk_internal_file_t *internal_file = NULL;
	static char *function                 = "liblnk_file_free";
	int result                            = 1;

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
	if( *file != NULL )
	{
		internal_file = (liblnk_internal_file_t *) *file;

		if( internal_file->file_io_handle != NULL )
		{
			if( liblnk_file_close(
			     *file,
			     error ) != 0 )
			{
				libcerror_error_set(
				 error,
				 LIBCERROR_ERROR_DOMAIN_IO,
				 LIBCERROR_IO_ERROR_CLOSE_FAILED,
				 "%s: unable to close file.",
				 function );

				result = -1;
			}
		}
		*file = NULL;

		if( liblnk_io_handle_free(
		     &( internal_file->io_handle ),
		     error ) != 1 )
		{
			libcerror_error_set(
			 error,
			 LIBCERROR_ERROR_DOMAIN_RUNTIME,
			 LIBCERROR_RUNTIME_ERROR_FINALIZE_FAILED,
			 "%s: unable to free IO handle.",
			 function );

			result = -1;
		}
		memory_free(
		 internal_file );
	}
	return( result );
}

/* Signals the file to abort its current activity
 * Returns 1 if successful or -1 on error
 */
int liblnk_file_signal_abort(
     liblnk_file_t *file,
     libcerror_error_t **error )
{
	liblnk_internal_file_t *internal_file = NULL;
	static char *function                 = "liblnk_file_signal_abort";

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
	internal_file->io_handle->abort = 1;

	return( 1 );
}

/* Opens a file
 * Returns 1 if successful or -1 on error
 */
int liblnk_file_open(
     liblnk_file_t *file,
     const char *filename,
     int access_flags,
     libcerror_error_t **error )
{
	libbfio_handle_t *file_io_handle      = NULL;
	liblnk_internal_file_t *internal_file = NULL;
	static char *function                 = "liblnk_file_open";
	size_t filename_length                = 0;

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

	if( filename == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid filename.",
		 function );

		return( -1 );
	}
	if( ( ( access_flags & LIBLNK_ACCESS_FLAG_READ ) == 0 )
	 && ( ( access_flags & LIBLNK_ACCESS_FLAG_WRITE ) == 0 ) )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_UNSUPPORTED_VALUE,
		 "%s: unsupported accesss flags.",
		 function );

		return( -1 );
	}
	if( ( access_flags & LIBLNK_ACCESS_FLAG_WRITE ) != 0 )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_UNSUPPORTED_VALUE,
		 "%s: write access currently not supported.",
		 function );

		return( -1 );
	}
	if( libbfio_file_initialize(
	     &file_io_handle,
	     error ) != 1 )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_INITIALIZE_FAILED,
		 "%s: unable to create file IO handle.",
		 function );

		goto on_error;
	}
#if defined( HAVE_DEBUG_OUTPUT )
	if( libbfio_handle_set_track_offsets_read(
	     file_io_handle,
	     1,
	     error ) != 1 )
	{
                libcerror_error_set(
                 error,
                 LIBCERROR_ERROR_DOMAIN_RUNTIME,
                 LIBCERROR_RUNTIME_ERROR_SET_FAILED,
                 "%s: unable to set track offsets read in file IO handle.",
                 function );

		goto on_error;
	}
#endif
	filename_length = narrow_string_length(
	                   filename );

	if( libbfio_file_set_name(
	     file_io_handle,
	     filename,
	     filename_length + 1,
	     error ) != 1 )
	{
                libcerror_error_set(
                 error,
                 LIBCERROR_ERROR_DOMAIN_RUNTIME,
                 LIBCERROR_RUNTIME_ERROR_SET_FAILED,
                 "%s: unable to set filename in file IO handle.",
                 function );

                goto on_error;
	}
	if( liblnk_file_open_file_io_handle(
	     file,
	     file_io_handle,
	     access_flags,
	     error ) != 1 )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_IO,
		 LIBCERROR_IO_ERROR_OPEN_FAILED,
		 "%s: unable to open file: %s.",
		 function,
		 filename );

                goto on_error;
	}
	internal_file->file_io_handle_created_in_library = 1;

	return( 1 );

on_error:
	if( file_io_handle != NULL )
	{
		libbfio_handle_free(
		 &file_io_handle,
		 NULL );
	}
	return( -1 );
}

#if defined( HAVE_WIDE_CHARACTER_TYPE )

/* Opens a file
 * Returns 1 if successful or -1 on error
 */
int liblnk_file_open_wide(
     liblnk_file_t *file,
     const wchar_t *filename,
     int access_flags,
     libcerror_error_t **error )
{
	libbfio_handle_t *file_io_handle      = NULL;
	liblnk_internal_file_t *internal_file = NULL;
	static char *function                 = "liblnk_file_open_wide";
	size_t filename_length                = 0;

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

	if( filename == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid filename.",
		 function );

		return( -1 );
	}
	if( ( ( access_flags & LIBLNK_ACCESS_FLAG_READ ) == 0 )
	 && ( ( access_flags & LIBLNK_ACCESS_FLAG_WRITE ) == 0 ) )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_UNSUPPORTED_VALUE,
		 "%s: unsupported access flags.",
		 function );

		return( -1 );
	}
	if( ( access_flags & LIBLNK_ACCESS_FLAG_WRITE ) != 0 )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_UNSUPPORTED_VALUE,
		 "%s: write access currently not supported.",
		 function );

		return( -1 );
	}
	if( libbfio_file_initialize(
	     &file_io_handle,
	     error ) != 1 )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_INITIALIZE_FAILED,
		 "%s: unable to create file IO handle.",
		 function );

		goto on_error;
	}
#if defined( HAVE_DEBUG_OUTPUT )
	if( libbfio_handle_set_track_offsets_read(
	     file_io_handle,
	     1,
	     error ) != 1 )
	{
                libcerror_error_set(
                 error,
                 LIBCERROR_ERROR_DOMAIN_RUNTIME,
                 LIBCERROR_RUNTIME_ERROR_SET_FAILED,
                 "%s: unable to set track offsets read in file IO handle.",
                 function );

		goto on_error;
	}
#endif
	filename_length = wide_string_length(
	                   filename );

	if( libbfio_file_set_name_wide(
	     file_io_handle,
	     filename,
	     filename_length + 1,
	     error ) != 1 )
	{
                libcerror_error_set(
                 error,
                 LIBCERROR_ERROR_DOMAIN_RUNTIME,
                 LIBCERROR_RUNTIME_ERROR_SET_FAILED,
                 "%s: unable to set filename in file IO handle.",
                 function );

		goto on_error;
	}
	if( liblnk_file_open_file_io_handle(
	     file,
	     file_io_handle,
	     access_flags,
	     error ) != 1 )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_IO,
		 LIBCERROR_IO_ERROR_OPEN_FAILED,
		 "%s: unable to open file: %ls.",
		 function,
		 filename );

		goto on_error;
	}
	internal_file->file_io_handle_created_in_library = 1;

	return( 1 );

on_error:
	if( file_io_handle != NULL )
	{
		libbfio_handle_free(
		 &file_io_handle,
		 NULL );
	}
	return( -1 );
}

#endif /* defined( HAVE_WIDE_CHARACTER_TYPE ) */

/* Opens a file using a Basic File IO (bfio) handle
 * Returns 1 if successful or -1 on error
 */
int liblnk_file_open_file_io_handle(
     liblnk_file_t *file,
     libbfio_handle_t *file_io_handle,
     int access_flags,
     libcerror_error_t **error )
{
	liblnk_internal_file_t *internal_file = NULL;
	static char *function                 = "liblnk_file_open_file_io_handle";
	int bfio_access_flags                 = 0;
	int file_io_handle_is_open            = 0;
	int file_io_handle_opened_in_library  = 0;

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

	if( internal_file->file_io_handle != NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_VALUE_ALREADY_SET,
		 "%s: invalid file - file IO handle already set.",
		 function );

		return( -1 );
	}
	if( file_io_handle == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid file IO handle.",
		 function );

		return( -1 );
	}
	if( ( ( access_flags & LIBLNK_ACCESS_FLAG_READ ) == 0 )
	 && ( ( access_flags & LIBLNK_ACCESS_FLAG_WRITE ) == 0 ) )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_UNSUPPORTED_VALUE,
		 "%s: unsupported access flags.",
		 function );

		return( -1 );
	}
	if( ( access_flags & LIBLNK_ACCESS_FLAG_WRITE ) != 0 )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_UNSUPPORTED_VALUE,
		 "%s: write access currently not supported.",
		 function );

		return( -1 );
	}
	if( ( access_flags & LIBLNK_ACCESS_FLAG_READ ) != 0 )
	{
		bfio_access_flags = LIBBFIO_ACCESS_FLAG_READ;
	}
	file_io_handle_is_open = libbfio_handle_is_open(
	                          file_io_handle,
	                          error );

	if( file_io_handle_is_open == -1 )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_IO,
		 LIBCERROR_IO_ERROR_OPEN_FAILED,
		 "%s: unable to open file.",
		 function );

		goto on_error;
	}
	else if( file_io_handle_is_open == 0 )
	{
		if( libbfio_handle_open(
		     file_io_handle,
		     bfio_access_flags,
		     error ) != 1 )
		{
			libcerror_error_set(
			 error,
			 LIBCERROR_ERROR_DOMAIN_IO,
			 LIBCERROR_IO_ERROR_OPEN_FAILED,
			 "%s: unable to open file IO handle.",
			 function );

			goto on_error;
		}
		file_io_handle_opened_in_library = 1;
	}
	if( liblnk_file_open_read(
	     internal_file,
	     file_io_handle,
	     error ) != 1 )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_IO,
		 LIBCERROR_IO_ERROR_READ_FAILED,
		 "%s: unable to read from file IO handle.",
		 function );

		goto on_error;
	}
	internal_file->file_io_handle                   = file_io_handle;
	internal_file->file_io_handle_opened_in_library = file_io_handle_opened_in_library;

	return( 1 );

on_error:
	if( ( file_io_handle_is_open == 0 )
	 && ( file_io_handle_opened_in_library != 0 ) )
	{
		libbfio_handle_close(
		 file_io_handle,
		 error );
	}
	return( -1 );
}

/* Closes a file
 * Returns 0 if successful or -1 on error
 */
int liblnk_file_close(
     liblnk_file_t *file,
     libcerror_error_t **error )
{
	liblnk_internal_file_t *internal_file = NULL;
	static char *function                 = "liblnk_file_close";
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

	if( internal_file->file_io_handle == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_VALUE_MISSING,
		 "%s: invalid file - missing file IO handle.",
		 function );

		return( -1 );
	}
#if defined( HAVE_DEBUG_OUTPUT )
	if( libcnotify_verbose != 0 )
	{
		if( internal_file->file_io_handle_created_in_library != 0 )
		{
			if( liblnk_debug_print_read_offsets(
			     internal_file->file_io_handle,
			     error ) != 1 )
			{
				libcerror_error_set(
				 error,
				 LIBCERROR_ERROR_DOMAIN_RUNTIME,
				 LIBCERROR_RUNTIME_ERROR_PRINT_FAILED,
				 "%s: unable to print the read offsets.",
				 function );

				result = -1;
			}
		}
	}
#endif
	if( internal_file->file_io_handle_opened_in_library != 0 )
	{
		if( libbfio_handle_close(
		     internal_file->file_io_handle,
		     error ) != 0 )
		{
			libcerror_error_set(
			 error,
			 LIBCERROR_ERROR_DOMAIN_IO,
			 LIBCERROR_IO_ERROR_CLOSE_FAILED,
			 "%s: unable to close file IO handle.",
			 function );

			result = -1;
		}
		internal_file->file_io_handle_opened_in_library = 0;
	}
	if( internal_file->file_io_handle_created_in_library != 0 )
	{
		if( libbfio_handle_free(
		     &( internal_file->file_io_handle ),
		     error ) != 1 )
		{
			libcerror_error_set(
			 error,
			 LIBCERROR_ERROR_DOMAIN_RUNTIME,
			 LIBCERROR_RUNTIME_ERROR_FINALIZE_FAILED,
			 "%s: unable to free file IO handle.",
			 function );

			result = -1;
		}
		internal_file->file_io_handle_created_in_library = 0;
	}
	internal_file->file_io_handle = NULL;

	if( liblnk_io_handle_clear(
	     internal_file->io_handle,
	     error ) != 1 )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_FINALIZE_FAILED,
		 "%s: unable to clear IO handle.",
		 function );

		result = -1;
	}
	if( internal_file->file_information != NULL )
	{
		if( liblnk_file_header_free(
		     &( internal_file->file_information ),
		     error ) != 1 )
		{
			libcerror_error_set(
			 error,
			 LIBCERROR_ERROR_DOMAIN_RUNTIME,
			 LIBCERROR_RUNTIME_ERROR_FINALIZE_FAILED,
			 "%s: unable to free file information.",
			 function );

			result = -1;
		}
	}
	if( internal_file->link_target_identifier != NULL )
	{
		if( liblnk_link_target_identifier_free(
		     &( internal_file->link_target_identifier ),
		     error ) != 1 )
		{
			libcerror_error_set(
			 error,
			 LIBCERROR_ERROR_DOMAIN_RUNTIME,
			 LIBCERROR_RUNTIME_ERROR_FINALIZE_FAILED,
			 "%s: unable to free link target identifier.",
			 function );

			result = -1;
		}
	}
	if( internal_file->location_information != NULL )
	{
		if( liblnk_location_information_free(
		     &( internal_file->location_information ),
		     error ) != 1 )
		{
			libcerror_error_set(
			 error,
			 LIBCERROR_ERROR_DOMAIN_RUNTIME,
			 LIBCERROR_RUNTIME_ERROR_FINALIZE_FAILED,
			 "%s: unable to free location information.",
			 function );

			result = -1;
		}
	}
	if( internal_file->description != NULL )
	{
		if( liblnk_data_string_free(
		     &( internal_file->description ),
		     error ) != 1 )
		{
			libcerror_error_set(
			 error,
			 LIBCERROR_ERROR_DOMAIN_RUNTIME,
			 LIBCERROR_RUNTIME_ERROR_FINALIZE_FAILED,
			 "%s: unable to free description.",
			 function );

			result = -1;
		}
	}
	if( internal_file->relative_path != NULL )
	{
		if( liblnk_data_string_free(
		     &( internal_file->relative_path ),
		     error ) != 1 )
		{
			libcerror_error_set(
			 error,
			 LIBCERROR_ERROR_DOMAIN_RUNTIME,
			 LIBCERROR_RUNTIME_ERROR_FINALIZE_FAILED,
			 "%s: unable to free relative path.",
			 function );

			result = -1;
		}
	}
	if( internal_file->working_directory != NULL )
	{
		if( liblnk_data_string_free(
		     &( internal_file->working_directory ),
		     error ) != 1 )
		{
			libcerror_error_set(
			 error,
			 LIBCERROR_ERROR_DOMAIN_RUNTIME,
			 LIBCERROR_RUNTIME_ERROR_FINALIZE_FAILED,
			 "%s: unable to free working directory.",
			 function );

			result = -1;
		}
	}
	if( internal_file->command_line_arguments != NULL )
	{
		if( liblnk_data_string_free(
		     &( internal_file->command_line_arguments ),
		     error ) != 1 )
		{
			libcerror_error_set(
			 error,
			 LIBCERROR_ERROR_DOMAIN_RUNTIME,
			 LIBCERROR_RUNTIME_ERROR_FINALIZE_FAILED,
			 "%s: unable to free command line arguments.",
			 function );

			result = -1;
		}
	}
	if( internal_file->icon_location != NULL )
	{
		if( liblnk_data_string_free(
		     &( internal_file->icon_location ),
		     error ) != 1 )
		{
			libcerror_error_set(
			 error,
			 LIBCERROR_ERROR_DOMAIN_RUNTIME,
			 LIBCERROR_RUNTIME_ERROR_FINALIZE_FAILED,
			 "%s: unable to free icon location.",
			 function );

			result = -1;
		}
	}
	if( internal_file->environment_variables_location != NULL )
	{
		if( liblnk_data_string_free(
		     &( internal_file->environment_variables_location ),
		     error ) != 1 )
		{
			libcerror_error_set(
			 error,
			 LIBCERROR_ERROR_DOMAIN_RUNTIME,
			 LIBCERROR_RUNTIME_ERROR_FINALIZE_FAILED,
			 "%s: unable to free environment variables location.",
			 function );

			result = -1;
		}
	}
	if( internal_file->darwin_application_identifier != NULL )
	{
		if( liblnk_data_string_free(
		     &( internal_file->darwin_application_identifier ),
		     error ) != 1 )
		{
			libcerror_error_set(
			 error,
			 LIBCERROR_ERROR_DOMAIN_RUNTIME,
			 LIBCERROR_RUNTIME_ERROR_FINALIZE_FAILED,
			 "%s: unable to free darwin application identifier.",
			 function );

			result = -1;
		}
	}
	if( internal_file->special_folder_location != NULL )
	{
		if( liblnk_special_folder_location_free(
		     &( internal_file->special_folder_location ),
		     error ) != 1 )
		{
			libcerror_error_set(
			 error,
			 LIBCERROR_ERROR_DOMAIN_RUNTIME,
			 LIBCERROR_RUNTIME_ERROR_FINALIZE_FAILED,
			 "%s: unable to free special folder location.",
			 function );

			result = -1;
		}
	}
	if( internal_file->known_folder_location != NULL )
	{
		if( liblnk_known_folder_location_free(
		     &( internal_file->known_folder_location ),
		     error ) != 1 )
		{
			libcerror_error_set(
			 error,
			 LIBCERROR_ERROR_DOMAIN_RUNTIME,
			 LIBCERROR_RUNTIME_ERROR_FINALIZE_FAILED,
			 "%s: unable to free known folder location.",
			 function );

			result = -1;
		}
	}
	if( internal_file->distributed_link_tracker_properties != NULL )
	{
		if( liblnk_distributed_link_tracker_properties_free(
		     &( internal_file->distributed_link_tracker_properties ),
		     error ) != 1 )
		{
			libcerror_error_set(
			 error,
			 LIBCERROR_ERROR_DOMAIN_RUNTIME,
			 LIBCERROR_RUNTIME_ERROR_FINALIZE_FAILED,
			 "%s: unable to free distributed link tracker properties.",
			 function );

			result = -1;
		}
	}
	return( result );
}

/* Opens a file for reading
 * Returns 1 if successful or -1 on error
 */
int liblnk_file_open_read(
     liblnk_internal_file_t *internal_file,
     libbfio_handle_t *file_io_handle,
     libcerror_error_t **error )
{
	liblnk_data_block_t *data_block     = NULL;
	static char *function               = "liblnk_file_open_read";
	off64_t file_offset                 = 0;
	size_t data_block_data_size         = 0;
	ssize_t read_count                  = 0;

#if defined( HAVE_DEBUG_OUTPUT )
        libfwps_storage_t *property_storage = NULL;

	uint8_t *trailing_data              = NULL;
	size_t trailing_data_size           = 0;
#endif

	if( internal_file == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid file.",
		 function );

		return( -1 );
	}
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
	if( internal_file->file_information != NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_VALUE_ALREADY_SET,
		 "%s: invalid file - file information value already set.",
		 function );

		return( -1 );
	}
	if( internal_file->link_target_identifier != NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_VALUE_ALREADY_SET,
		 "%s: invalid file - link target identifier value already set.",
		 function );

		return( -1 );
	}
	if( internal_file->location_information != NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_VALUE_ALREADY_SET,
		 "%s: invalid file - location information value already set.",
		 function );

		return( -1 );
	}
	if( internal_file->description != NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_VALUE_ALREADY_SET,
		 "%s: invalid file - description value already set.",
		 function );

		return( -1 );
	}
	if( internal_file->relative_path != NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_VALUE_ALREADY_SET,
		 "%s: invalid file - relative path value already set.",
		 function );

		return( -1 );
	}
	if( internal_file->working_directory != NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_VALUE_ALREADY_SET,
		 "%s: invalid file - working directory value already set.",
		 function );

		return( -1 );
	}
	if( internal_file->command_line_arguments != NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_VALUE_ALREADY_SET,
		 "%s: invalid file - command line arguments value already set.",
		 function );

		return( -1 );
	}
	if( internal_file->icon_location != NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_VALUE_ALREADY_SET,
		 "%s: invalid file - icon location value already set.",
		 function );

		return( -1 );
	}
	if( internal_file->environment_variables_location != NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_VALUE_ALREADY_SET,
		 "%s: invalid file - environment variables location value already set.",
		 function );

		return( -1 );
	}
	if( internal_file->darwin_application_identifier != NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_VALUE_ALREADY_SET,
		 "%s: invalid file - darwin application identifier value already set.",
		 function );

		return( -1 );
	}
	if( internal_file->special_folder_location != NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_VALUE_ALREADY_SET,
		 "%s: invalid file - special folder location value already set.",
		 function );

		return( -1 );
	}
	if( internal_file->known_folder_location != NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_VALUE_ALREADY_SET,
		 "%s: invalid file - known folder location value already set.",
		 function );

		return( -1 );
	}
	if( internal_file->distributed_link_tracker_properties != NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_VALUE_ALREADY_SET,
		 "%s: invalid file - distributed link tracker properties value already set.",
		 function );

		return( -1 );
	}
	if( liblnk_file_header_initialize(
	     &( internal_file->file_information ),
	     error ) != 1 )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_INITIALIZE_FAILED,
		 "%s: unable to create file header.",
		 function );

		goto on_error;
	}
#if defined( HAVE_DEBUG_OUTPUT )
	if( libcnotify_verbose != 0 )
	{
		libcnotify_printf(
		 "Reading file header:\n" );
	}
#endif
	if( libbfio_handle_get_size(
	     file_io_handle,
	     &( internal_file->io_handle->file_size ),
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
	if( liblnk_file_header_read_file_io_handle(
	     internal_file->file_information,
	     file_io_handle,
	     error ) != 1 )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_IO,
		 LIBCERROR_IO_ERROR_READ_FAILED,
		 "%s: unable to read file header.",
		 function );

		goto on_error;
	}
	file_offset = 76;

	if( ( internal_file->file_information->data_flags & LIBLNK_DATA_FLAG_IS_UNICODE ) != 0 )
	{
		internal_file->io_handle->is_unicode = 1;
	}
	else
	{
		internal_file->io_handle->is_unicode = 0;
	}
	if( ( internal_file->file_information->data_flags & LIBLNK_DATA_FLAG_HAS_LINK_TARGET_IDENTIFIER ) != 0 )
	{
		if( liblnk_link_target_identifier_initialize(
		     &( internal_file->link_target_identifier ),
		     error ) != 1 )
		{
			libcerror_error_set(
			 error,
			 LIBCERROR_ERROR_DOMAIN_RUNTIME,
			 LIBCERROR_RUNTIME_ERROR_INITIALIZE_FAILED,
			 "%s: unable to create link target identifier.",
			 function );

			goto on_error;
		}
#if defined( HAVE_DEBUG_OUTPUT )
		if( libcnotify_verbose != 0 )
		{
			libcnotify_printf(
			 "Reading link target identifier:\n" );
		}
#endif
		read_count = liblnk_link_target_identifier_read(
		              internal_file->link_target_identifier,
		              internal_file->io_handle,
		              file_io_handle,
		              file_offset,
		              error );

		if( read_count <= -1 )
		{
			libcerror_error_set(
			 error,
			 LIBCERROR_ERROR_DOMAIN_IO,
			 LIBCERROR_IO_ERROR_READ_FAILED,
			 "%s: unable to read link target identifier.",
			 function );

			goto on_error;
		}
		file_offset += read_count;
	}
	if( ( internal_file->file_information->data_flags & LIBLNK_DATA_FLAG_HAS_LOCATION_INFORMATION ) != 0 )
	{
		if( liblnk_location_information_initialize(
		     &( internal_file->location_information ),
		     error ) != 1 )
		{
			libcerror_error_set(
			 error,
			 LIBCERROR_ERROR_DOMAIN_RUNTIME,
			 LIBCERROR_RUNTIME_ERROR_INITIALIZE_FAILED,
			 "%s: unable to create location information.",
			 function );

			goto on_error;
		}
#if defined( HAVE_DEBUG_OUTPUT )
		if( libcnotify_verbose != 0 )
		{
			libcnotify_printf(
			 "Reading location information:\n" );
		}
#endif
		read_count = liblnk_location_information_read(
		              internal_file->location_information,
		              internal_file->io_handle,
		              file_io_handle,
		              file_offset,
		              error );

		if( read_count <= -1 )
		{
			libcerror_error_set(
			 error,
			 LIBCERROR_ERROR_DOMAIN_IO,
			 LIBCERROR_IO_ERROR_READ_FAILED,
			 "%s: unable to read location information.",
			 function );

			goto on_error;
		}
		file_offset += read_count;
	}
	if( ( internal_file->file_information->data_flags & LIBLNK_DATA_FLAG_HAS_DESCRIPTION_STRING ) != 0 )
	{
		if( liblnk_data_string_initialize(
		     &( internal_file->description ),
		     error ) != 1 )
		{
			libcerror_error_set(
			 error,
			 LIBCERROR_ERROR_DOMAIN_RUNTIME,
			 LIBCERROR_RUNTIME_ERROR_INITIALIZE_FAILED,
			 "%s: unable to create description.",
			 function );

			goto on_error;
		}
#if defined( HAVE_DEBUG_OUTPUT )
		if( libcnotify_verbose != 0 )
		{
			libcnotify_printf(
			 "Reading description data string:\n" );
		}
#endif
		read_count = liblnk_data_string_read(
		              internal_file->description,
		              internal_file->io_handle,
		              file_io_handle,
		              file_offset,
		              error );

		if( read_count <= -1 )
		{
			libcerror_error_set(
			 error,
			 LIBCERROR_ERROR_DOMAIN_IO,
			 LIBCERROR_IO_ERROR_READ_FAILED,
			 "%s: unable to read description.",
			 function );

			goto on_error;
		}
		file_offset += read_count;
	}
	if( ( internal_file->file_information->data_flags & LIBLNK_DATA_FLAG_HAS_RELATIVE_PATH_STRING ) != 0 )
	{
		if( liblnk_data_string_initialize(
		     &( internal_file->relative_path ),
		     error ) != 1 )
		{
			libcerror_error_set(
			 error,
			 LIBCERROR_ERROR_DOMAIN_RUNTIME,
			 LIBCERROR_RUNTIME_ERROR_INITIALIZE_FAILED,
			 "%s: unable to create relative path.",
			 function );

			goto on_error;
		}
#if defined( HAVE_DEBUG_OUTPUT )
		if( libcnotify_verbose != 0 )
		{
			libcnotify_printf(
			 "Reading relative path data string:\n" );
		}
#endif
		read_count = liblnk_data_string_read(
		              internal_file->relative_path,
		              internal_file->io_handle,
		              file_io_handle,
		              file_offset,
		              error );

		if( read_count <= -1 )
		{
			libcerror_error_set(
			 error,
			 LIBCERROR_ERROR_DOMAIN_IO,
			 LIBCERROR_IO_ERROR_READ_FAILED,
			 "%s: unable to read relative path.",
			 function );

			goto on_error;
		}
		file_offset += read_count;
	}
	if( ( internal_file->file_information->data_flags & LIBLNK_DATA_FLAG_HAS_WORKING_DIRECTORY_STRING ) != 0 )
	{
		if( liblnk_data_string_initialize(
		     &( internal_file->working_directory ),
		     error ) != 1 )
		{
			libcerror_error_set(
			 error,
			 LIBCERROR_ERROR_DOMAIN_RUNTIME,
			 LIBCERROR_RUNTIME_ERROR_INITIALIZE_FAILED,
			 "%s: unable to create working directory.",
			 function );

			goto on_error;
		}
#if defined( HAVE_DEBUG_OUTPUT )
		if( libcnotify_verbose != 0 )
		{
			libcnotify_printf(
			 "Reading working directory data string:\n" );
		}
#endif
		read_count = liblnk_data_string_read(
		              internal_file->working_directory,
		              internal_file->io_handle,
		              file_io_handle,
		              file_offset,
		              error );

		if( read_count <= -1 )
		{
			libcerror_error_set(
			 error,
			 LIBCERROR_ERROR_DOMAIN_IO,
			 LIBCERROR_IO_ERROR_READ_FAILED,
			 "%s: unable to read working directory.",
			 function );

			goto on_error;
		}
		file_offset += read_count;
	}
	if( ( internal_file->file_information->data_flags & LIBLNK_DATA_FLAG_HAS_COMMAND_LINE_ARGUMENTS_STRING ) != 0 )
	{
		if( liblnk_data_string_initialize(
		     &( internal_file->command_line_arguments ),
		     error ) != 1 )
		{
			libcerror_error_set(
			 error,
			 LIBCERROR_ERROR_DOMAIN_RUNTIME,
			 LIBCERROR_RUNTIME_ERROR_INITIALIZE_FAILED,
			 "%s: unable to create command line arguments.",
			 function );

			goto on_error;
		}
#if defined( HAVE_DEBUG_OUTPUT )
		if( libcnotify_verbose != 0 )
		{
			libcnotify_printf(
			 "Reading command line arguments data string:\n" );
		}
#endif
		read_count = liblnk_data_string_read(
		              internal_file->command_line_arguments,
		              internal_file->io_handle,
		              file_io_handle,
		              file_offset,
		              error );

		if( read_count <= -1 )
		{
			libcerror_error_set(
			 error,
			 LIBCERROR_ERROR_DOMAIN_IO,
			 LIBCERROR_IO_ERROR_READ_FAILED,
			 "%s: unable to read command line arguments.",
			 function );

			goto on_error;
		}
		file_offset += read_count;
	}
	if( ( internal_file->file_information->data_flags & LIBLNK_DATA_FLAG_HAS_ICON_LOCATION_STRING ) != 0 )
	{
		if( liblnk_data_string_initialize(
		     &( internal_file->icon_location ),
		     error ) != 1 )
		{
			libcerror_error_set(
			 error,
			 LIBCERROR_ERROR_DOMAIN_RUNTIME,
			 LIBCERROR_RUNTIME_ERROR_INITIALIZE_FAILED,
			 "%s: unable to create icon location.",
			 function );

			goto on_error;
		}
#if defined( HAVE_DEBUG_OUTPUT )
		if( libcnotify_verbose != 0 )
		{
			libcnotify_printf(
			 "Reading icon location data string:\n" );
		}
#endif
		read_count = liblnk_data_string_read(
		              internal_file->icon_location,
		              internal_file->io_handle,
		              file_io_handle,
		              file_offset,
		              error );

		if( read_count <= -1 )
		{
			libcerror_error_set(
			 error,
			 LIBCERROR_ERROR_DOMAIN_IO,
			 LIBCERROR_IO_ERROR_READ_FAILED,
			 "%s: unable to read icon location.",
			 function );

			goto on_error;
		}
		file_offset += read_count;
	}
	if( file_offset < (off64_t) internal_file->io_handle->file_size )
	{
#ifdef TODO
/* TODO */
		if( ( file_information->data_flags & LIBLNK_DATA_FLAG_HAS_METADATA_PROPERTY_STORE_DATA_BLOCK ) != 0 )
		{
		}
#endif
#if defined( HAVE_DEBUG_OUTPUT )
		if( libcnotify_verbose != 0 )
		{
			libcnotify_printf(
			 "Reading extra data blocks:\n" );
		}
#endif
		while( file_offset < (off64_t) internal_file->io_handle->file_size )
		{
			if( liblnk_data_block_initialize(
			     &data_block,
			     error ) != 1 )
			{
				libcerror_error_set(
				 error,
				 LIBCERROR_ERROR_DOMAIN_RUNTIME,
				 LIBCERROR_RUNTIME_ERROR_INITIALIZE_FAILED,
				 "%s: unable to create data block.",
				 function );

				goto on_error;
			}
			read_count = liblnk_data_block_read(
			              data_block,
			              internal_file->io_handle,
			              file_io_handle,
			              file_offset,
			              error );

			if( read_count <= -1 )
			{
				libcerror_error_set(
				 error,
				 LIBCERROR_ERROR_DOMAIN_IO,
				 LIBCERROR_IO_ERROR_READ_FAILED,
				 "%s: unable to read data block.",
				 function );

				goto on_error;
			}
			file_offset += read_count;

			data_block_data_size = data_block->data_size;

			if( data_block_data_size > 0 )
			{
				switch( data_block->signature )
				{
					case LIBLNK_DATA_BLOCK_SIGNATURE_ENVIRONMENT_VARIABLES_LOCATION:
#if defined( HAVE_DEBUG_OUTPUT )
						if( libcnotify_verbose != 0 )
						{
							libcnotify_printf(
							 "Reading environment variables location data block:\n" );
						}
#endif
#if defined( HAVE_VERBOSE_OUTPUT )
						if( libcnotify_verbose != 0 )
						{
							if( ( internal_file->file_information->data_flags & LIBLNK_DATA_FLAG_HAS_ENVIRONMENT_VARIABLES_LOCATION_BLOCK ) == 0 )
							{
								libcnotify_printf(
								 "%s: environment variables location data block found but data flag was not set\n",
								 function );
							}
						}
#endif
						if( liblnk_data_string_initialize(
						     &( internal_file->environment_variables_location ),
						     error ) != 1 )
						{
							libcerror_error_set(
							 error,
							 LIBCERROR_ERROR_DOMAIN_RUNTIME,
							 LIBCERROR_RUNTIME_ERROR_INITIALIZE_FAILED,
							 "%s: unable to create environment variables location.",
							 function );

							goto on_error;
						}
						if( liblnk_data_block_strings_read(
						     internal_file->environment_variables_location,
						     data_block,
						     internal_file->io_handle,
						     error ) != 1 )
						{
							libcerror_error_set(
							 error,
							 LIBCERROR_ERROR_DOMAIN_IO,
							 LIBCERROR_IO_ERROR_READ_FAILED,
							 "%s: unable to read environment variables data block.",
							 function );

							goto on_error;
						}
						break;

					case LIBLNK_DATA_BLOCK_SIGNATURE_DISTRIBUTED_LINK_TRACKER_PROPERTIES:
#if defined( HAVE_DEBUG_OUTPUT )
						if( libcnotify_verbose != 0 )
						{
							libcnotify_printf(
							 "Reading distributed link tracker properties data block:\n" );
						}
#endif
#if defined( HAVE_VERBOSE_OUTPUT )
						if( libcnotify_verbose != 0 )
						{
							if( ( internal_file->file_information->data_flags & LIBLNK_DATA_FLAG_NO_DISTRIBUTED_LINK_TRACKING_DATA_BLOCK ) != 0 )
							{
								libcnotify_printf(
								 "%s: distributed link tracker properties data block found but data flag was not set\n",
								 function );
							}
						}
#endif
						if( liblnk_distributed_link_tracker_properties_initialize(
						     &( internal_file->distributed_link_tracker_properties ),
						     error ) != 1 )
						{
							libcerror_error_set(
							 error,
							 LIBCERROR_ERROR_DOMAIN_RUNTIME,
							 LIBCERROR_RUNTIME_ERROR_INITIALIZE_FAILED,
							 "%s: unable to create distributed link tracker properties.",
							 function );

							goto on_error;
						}
						if( liblnk_distributed_link_tracker_properties_read(
						     internal_file->distributed_link_tracker_properties,
						     data_block,
						     internal_file->io_handle,
						     error ) != 1 )
						{
							libcerror_error_set(
							 error,
							 LIBCERROR_ERROR_DOMAIN_IO,
							 LIBCERROR_IO_ERROR_READ_FAILED,
							 "%s: unable to read distributed link tracker properties data block.",
							 function );

							goto on_error;
						}
						break;

					case LIBLNK_DATA_BLOCK_SIGNATURE_SPECIAL_FOLDER_LOCATION:
#if defined( HAVE_DEBUG_OUTPUT )
						if( libcnotify_verbose != 0 )
						{
							libcnotify_printf(
							 "Reading special folder location data block:\n" );
						}
#endif
						if( liblnk_special_folder_location_initialize(
						     &( internal_file->special_folder_location ),
						     error ) != 1 )
						{
							libcerror_error_set(
							 error,
							 LIBCERROR_ERROR_DOMAIN_RUNTIME,
							 LIBCERROR_RUNTIME_ERROR_INITIALIZE_FAILED,
							 "%s: unable to create special folder location.",
							 function );

							goto on_error;
						}
						if( liblnk_special_folder_location_read_data_block(
						     internal_file->special_folder_location,
						     data_block,
						     error ) != 1 )
						{
							libcerror_error_set(
							 error,
							 LIBCERROR_ERROR_DOMAIN_IO,
							 LIBCERROR_IO_ERROR_READ_FAILED,
							 "%s: unable to read special folder location data block.",
							 function );

							goto on_error;
						}
						break;

					case LIBLNK_DATA_BLOCK_SIGNATURE_DARWIN_PROPERTIES:
#if defined( HAVE_DEBUG_OUTPUT )
						if( libcnotify_verbose != 0 )
						{
							libcnotify_printf(
							 "Reading darwin application identifier data block:\n" );
						}
#endif
#if defined( HAVE_VERBOSE_OUTPUT )
						if( libcnotify_verbose != 0 )
						{
							if( ( internal_file->file_information->data_flags & LIBLNK_DATA_FLAG_HAS_DARWIN_IDENTIFIER ) == 0 )
							{
								libcnotify_printf(
								 "%s: darwin application identifier data block found but data flag was not set\n",
								 function );
							}
						}
#endif
						if( liblnk_data_string_initialize(
						     &( internal_file->darwin_application_identifier ),
						     error ) != 1 )
						{
							libcerror_error_set(
							 error,
							 LIBCERROR_ERROR_DOMAIN_RUNTIME,
							 LIBCERROR_RUNTIME_ERROR_INITIALIZE_FAILED,
							 "%s: unable to create darwin application identifier.",
							 function );

							goto on_error;
						}
						if( liblnk_data_block_strings_read(
						     internal_file->darwin_application_identifier,
						     data_block,
						     internal_file->io_handle,
						     error ) != 1 )
						{
							libcerror_error_set(
							 error,
							 LIBCERROR_ERROR_DOMAIN_IO,
							 LIBCERROR_IO_ERROR_READ_FAILED,
							 "%s: unable to read darwin application identifier data block.",
							 function );

							goto on_error;
						}
						break;

					case LIBLNK_DATA_BLOCK_SIGNATURE_ICON_LOCATION:
#if defined( HAVE_DEBUG_OUTPUT )
						if( libcnotify_verbose != 0 )
						{
							libcnotify_printf(
							 "Reading icon location data block:\n" );
						}
#endif
#if defined( HAVE_VERBOSE_OUTPUT )
						if( libcnotify_verbose != 0 )
						{
							if( ( internal_file->file_information->data_flags & LIBLNK_DATA_FLAG_HAS_ICON_LOCATION_BLOCK ) == 0 )
							{
								libcnotify_printf(
								 "%s: icon location data block found but data flag was not set\n",
								 function );
							}
						}
#endif
						if( internal_file->icon_location != NULL )
						{
							if( liblnk_data_string_free(
							     &( internal_file->icon_location ),
							     error ) != 1 )
							{
								libcerror_error_set(
								 error,
								 LIBCERROR_ERROR_DOMAIN_RUNTIME,
								 LIBCERROR_RUNTIME_ERROR_FINALIZE_FAILED,
								 "%s: unable to free icon location.",
								 function );

								goto on_error;
							}
						}
						if( liblnk_data_string_initialize(
						     &( internal_file->icon_location ),
						     error ) != 1 )
						{
							libcerror_error_set(
							 error,
							 LIBCERROR_ERROR_DOMAIN_RUNTIME,
							 LIBCERROR_RUNTIME_ERROR_INITIALIZE_FAILED,
							 "%s: unable to create icon location.",
							 function );

							goto on_error;
						}
						if( liblnk_data_block_strings_read(
						     internal_file->icon_location,
						     data_block,
						     internal_file->io_handle,
						     error ) != 1 )
						{
							libcerror_error_set(
							 error,
							 LIBCERROR_ERROR_DOMAIN_IO,
							 LIBCERROR_IO_ERROR_READ_FAILED,
							 "%s: unable to read icon location data block.",
							 function );

							goto on_error;
						}
						break;

					case LIBLNK_DATA_BLOCK_SIGNATURE_KNOWN_FOLDER_LOCATION:
#if defined( HAVE_DEBUG_OUTPUT )
						if( libcnotify_verbose != 0 )
						{
							libcnotify_printf(
							 "Reading known folder location data block:\n" );
						}
#endif
						if( liblnk_known_folder_location_initialize(
						     &( internal_file->known_folder_location ),
						     error ) != 1 )
						{
							libcerror_error_set(
							 error,
							 LIBCERROR_ERROR_DOMAIN_RUNTIME,
							 LIBCERROR_RUNTIME_ERROR_INITIALIZE_FAILED,
							 "%s: unable to create known folder location.",
							 function );

							goto on_error;
						}
						if( liblnk_known_folder_location_read_data_block(
						     internal_file->known_folder_location,
						     data_block,
						     error ) != 1 )
						{
							libcerror_error_set(
							 error,
							 LIBCERROR_ERROR_DOMAIN_IO,
							 LIBCERROR_IO_ERROR_READ_FAILED,
							 "%s: unable to read known folder location data block.",
							 function );

							goto on_error;
						}
						break;

					case LIBLNK_DATA_BLOCK_SIGNATURE_METADATA_PROPERTY_STORE:
#if defined( HAVE_DEBUG_OUTPUT )
						if( libcnotify_verbose != 0 )
						{
							if( data_block == NULL )
							{
								libcerror_error_set(
								 error,
								 LIBCERROR_ERROR_DOMAIN_RUNTIME,
								 LIBCERROR_RUNTIME_ERROR_VALUE_MISSING,
								 "%s: missing data block.",
								 function );

								goto on_error;
							}
/* TODO add support for more than one store */
							if( libfwps_storage_initialize(
							     &property_storage,
							     error ) != 1 )
							{
								libcerror_error_set(
								 error,
								 LIBCERROR_ERROR_DOMAIN_RUNTIME,
								 LIBCERROR_RUNTIME_ERROR_INITIALIZE_FAILED,
								 "%s: unable to create property storage.",
								 function );

								goto on_error;
							}
							if( libfwps_storage_copy_from_byte_stream(
							     property_storage,
							     &( data_block->data[ 4 ] ),
							     data_block->data_size - 4,
							     internal_file->io_handle->ascii_codepage,
							     error ) != 1 )
							{
								libcerror_error_set(
								 error,
								 LIBCERROR_ERROR_DOMAIN_RUNTIME,
								 LIBCERROR_RUNTIME_ERROR_COPY_FAILED,
								 "%s: unable to copy byte stream to property storage.",
								 function );

								goto on_error;
							}
							if( libfwps_storage_free(
							     &property_storage,
							     error ) != 1 )
							{
								libcerror_error_set(
								 error,
								 LIBCERROR_ERROR_DOMAIN_RUNTIME,
								 LIBCERROR_RUNTIME_ERROR_FINALIZE_FAILED,
								 "%s: unable to free property storage.",
								 function );

								goto on_error;
							}
						}
#endif
						break;

					default:
#if defined( HAVE_DEBUG_OUTPUT )
						if( libcnotify_verbose != 0 )
						{
							libcnotify_printf(
							 "%s: unsupported extra data block type.\n\n",
							 function );
						}
#endif
						break;
				}
			}
			if( liblnk_data_block_free(
			     &data_block,
			     error ) != 1 )
			{
				libcerror_error_set(
				 error,
				 LIBCERROR_ERROR_DOMAIN_RUNTIME,
				 LIBCERROR_RUNTIME_ERROR_FINALIZE_FAILED,
				 "%s: unable to free data block.",
				 function );

				goto on_error;
			}
			if( data_block_data_size == 0 )
			{
				break;
			}
		}
	}
#if defined( HAVE_DEBUG_OUTPUT )
	if( libcnotify_verbose != 0 )
	{
		if( file_offset < (off64_t) internal_file->io_handle->file_size )
		{
			trailing_data_size = (size_t) ( internal_file->io_handle->file_size - file_offset );

			trailing_data = (uint8_t *) memory_allocate(
						     sizeof( uint8_t ) * trailing_data_size );

			if( trailing_data == NULL )
			{
				libcerror_error_set(
				 error,
				 LIBCERROR_ERROR_DOMAIN_MEMORY,
				 LIBCERROR_MEMORY_ERROR_INSUFFICIENT,
				 "%s: unable to create trailing data.",
				 function );

				goto on_error;
			}
			read_count = libbfio_handle_read_buffer(
				      file_io_handle,
				      trailing_data,
				      trailing_data_size,
				      error );

			if( read_count != (ssize_t) trailing_data_size )
			{
				libcerror_error_set(
				 error,
				 LIBCERROR_ERROR_DOMAIN_IO,
				 LIBCERROR_IO_ERROR_READ_FAILED,
				 "%s: unable to read trailing data.",
				 function );

				memory_free(
				 trailing_data );

				goto on_error;
			}
			file_offset += read_count;

			libcnotify_printf(
			 "%s: trailing data:\n",
			 function );
			libcnotify_print_data(
			 trailing_data,
			 trailing_data_size,
			 LIBCNOTIFY_PRINT_DATA_FLAG_GROUP_DATA );

			memory_free(
			 trailing_data );

			trailing_data = NULL;
		}
	}
#endif
	return( 1 );

on_error:
#if defined( HAVE_DEBUG_OUTPUT )
	if( trailing_data != NULL )
	{
		memory_free(
		 trailing_data );
	}
	if( property_storage != NULL )
	{
		libfwps_storage_free(
		 &property_storage,
		 NULL );
	}
#endif
	if( data_block != NULL )
	{
		liblnk_data_block_free(
		 &data_block,
		 NULL );
	}
	if( internal_file->distributed_link_tracker_properties != NULL )
	{
		liblnk_distributed_link_tracker_properties_free(
		 &( internal_file->distributed_link_tracker_properties ),
		 NULL );
	}
	if( internal_file->known_folder_location != NULL )
	{
		liblnk_known_folder_location_free(
		 &( internal_file->known_folder_location ),
		 NULL );
	}
	if( internal_file->special_folder_location != NULL )
	{
		liblnk_special_folder_location_free(
		 &( internal_file->special_folder_location ),
		 NULL );
	}
	if( internal_file->darwin_application_identifier != NULL )
	{
		liblnk_data_string_free(
		 &( internal_file->darwin_application_identifier ),
		 NULL );
	}
	if( internal_file->environment_variables_location != NULL )
	{
		liblnk_data_string_free(
		 &( internal_file->environment_variables_location ),
		 NULL );
	}
	if( internal_file->icon_location != NULL )
	{
		liblnk_data_string_free(
		 &( internal_file->icon_location ),
		 NULL );
	}
	if( internal_file->command_line_arguments != NULL )
	{
		liblnk_data_string_free(
		 &( internal_file->command_line_arguments ),
		 NULL );
	}
	if( internal_file->working_directory != NULL )
	{
		liblnk_data_string_free(
		 &( internal_file->working_directory ),
		 NULL );
	}
	if( internal_file->relative_path != NULL )
	{
		liblnk_data_string_free(
		 &( internal_file->relative_path ),
		 NULL );
	}
	if( internal_file->description != NULL )
	{
		liblnk_data_string_free(
		 &( internal_file->description ),
		 NULL );
	}
	if( internal_file->location_information != NULL )
	{
		liblnk_location_information_free(
		 &( internal_file->location_information ),
		 NULL );
	}
	if( internal_file->link_target_identifier != NULL )
	{
		liblnk_link_target_identifier_free(
		 &( internal_file->link_target_identifier ),
		 NULL );
	}
	if( internal_file->file_information != NULL )
	{
		liblnk_file_header_free(
		 &( internal_file->file_information ),
		 NULL );
	}
	return( -1 );
}

/* Retrieves the file ASCII codepage
 * Returns 1 if successful or -1 on error
 */
int liblnk_file_get_ascii_codepage(
     liblnk_file_t *file,
     int *ascii_codepage,
     libcerror_error_t **error )
{
	liblnk_internal_file_t *internal_file = NULL;
	static char *function                 = "liblnk_file_get_ascii_codepage";

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
	if( ascii_codepage == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid ASCII codepage.",
		 function );

		return( -1 );
	}
	*ascii_codepage = internal_file->io_handle->ascii_codepage;

	return( 1 );
}

/* Sets the file ASCII codepage
 * Returns 1 if successful or -1 on error
 */
int liblnk_file_set_ascii_codepage(
     liblnk_file_t *file,
     int ascii_codepage,
     libcerror_error_t **error )
{
	liblnk_internal_file_t *internal_file = NULL;
	static char *function                 = "liblnk_file_set_ascii_codepage";

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
	if( ( ascii_codepage != LIBLNK_CODEPAGE_ASCII )
	 && ( ascii_codepage != LIBLNK_CODEPAGE_WINDOWS_874 )
	 && ( ascii_codepage != LIBLNK_CODEPAGE_WINDOWS_932 )
	 && ( ascii_codepage != LIBLNK_CODEPAGE_WINDOWS_936 )
	 && ( ascii_codepage != LIBLNK_CODEPAGE_WINDOWS_949 )
	 && ( ascii_codepage != LIBLNK_CODEPAGE_WINDOWS_950 )
	 && ( ascii_codepage != LIBLNK_CODEPAGE_WINDOWS_1250 )
	 && ( ascii_codepage != LIBLNK_CODEPAGE_WINDOWS_1251 )
	 && ( ascii_codepage != LIBLNK_CODEPAGE_WINDOWS_1252 )
	 && ( ascii_codepage != LIBLNK_CODEPAGE_WINDOWS_1253 )
	 && ( ascii_codepage != LIBLNK_CODEPAGE_WINDOWS_1254 )
	 && ( ascii_codepage != LIBLNK_CODEPAGE_WINDOWS_1255 )
	 && ( ascii_codepage != LIBLNK_CODEPAGE_WINDOWS_1256 )
	 && ( ascii_codepage != LIBLNK_CODEPAGE_WINDOWS_1257 )
	 && ( ascii_codepage != LIBLNK_CODEPAGE_WINDOWS_1258 ) )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_UNSUPPORTED_VALUE,
		 "%s: unsupported ASCII codepage.",
		 function );

		return( -1 );
	}
	internal_file->io_handle->ascii_codepage = ascii_codepage;

	return( 1 );
}

/* -------------------------------------------------------------------------
 * Link information functions
 * ------------------------------------------------------------------------- */

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
	*data_flags = internal_file->file_information->data_flags;

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
	if( ( internal_file->file_information->data_flags & LIBLNK_DATA_FLAG_HAS_LOCATION_INFORMATION ) == 0 )
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
     uint64_t *filetime,
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
	if( filetime == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid filetime.",
		 function );

		return( -1 );
	}
	*filetime = internal_file->file_information->creation_time;

	return( 1 );
}

/* Retrieves the 64-bit filetime value containing the linked file's last modification date and time
 * The modification time is only set when the link refers to a file
 * Returns 1 if successful or -1 on error
 */
int liblnk_file_get_file_modification_time(
     liblnk_file_t *file,
     uint64_t *filetime,
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
	if( filetime == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid filetime.",
		 function );

		return( -1 );
	}
	*filetime = internal_file->file_information->modification_time;

	return( 1 );
}

/* Retrieves the 64-bit filetime value containing the linked file's last access date and time
 * The access time is only set when the link refers to a file
 * Returns 1 if successful or -1 on error
 */
int liblnk_file_get_file_access_time(
     liblnk_file_t *file,
     uint64_t *filetime,
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
	if( filetime == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid filetime.",
		 function );

		return( -1 );
	}
	*filetime = internal_file->file_information->access_time;

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

/* Retrieves the icon index
 * Returns 1 if successful or -1 on error
 */
int liblnk_file_get_icon_index(
     liblnk_file_t *file,
     uint32_t *icon_index,
     libcerror_error_t **error )
{
	liblnk_internal_file_t *internal_file = NULL;
	static char *function                 = "liblnk_file_get_icon_index";

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
	if( icon_index == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid icon index.",
		 function );

		return( -1 );
	}
	*icon_index = internal_file->file_information->icon_index;

	return( 1 );
}

/* Retrieves the show window value
 * Returns 1 if successful or -1 on error
 */
int liblnk_file_get_show_window_value(
     liblnk_file_t *file,
     uint32_t *show_window_value,
     libcerror_error_t **error )
{
	liblnk_internal_file_t *internal_file = NULL;
	static char *function                 = "liblnk_file_get_show_window_value";

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
	if( show_window_value == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid show window value.",
		 function );

		return( -1 );
	}
	*show_window_value = internal_file->file_information->size;

	return( 1 );
}

/* Retrieves the hot key value
 * Returns 1 if successful or -1 on error
 */
int liblnk_file_get_hot_key_value(
     liblnk_file_t *file,
     uint16_t *hot_key_value,
     libcerror_error_t **error )
{
	liblnk_internal_file_t *internal_file = NULL;
	static char *function                 = "liblnk_file_get_hot_key_value";

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
	if( hot_key_value == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid hot key value.",
		 function );

		return( -1 );
	}
	*hot_key_value = internal_file->file_information->size;

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
	if( ( internal_file->location_information->string_flags & LIBLNK_LOCATION_INFORMATION_STRING_FLAG_VOLUME_LABEL_IS_UNICODE ) != 0 )
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
	if( ( internal_file->location_information->string_flags & LIBLNK_LOCATION_INFORMATION_STRING_FLAG_VOLUME_LABEL_IS_UNICODE ) != 0 )
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

/* -------------------------------------------------------------------------
 * Distributed link tracking data functions
 * ------------------------------------------------------------------------- */

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
 * Returns 1 if successful, 0 if value is not available or -1 on error
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
		return( 0 );
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
 * Returns 1 if successful, 0 if value is not available or -1 on error
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
		return( 0 );
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
 * Returns 1 if successful, 0 if value is not available or -1 on error
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
		return( 0 );
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
 * Returns 1 if successful, 0 if value is not available or -1 on error
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
		return( 0 );
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
 * Returns 1 if successful, 0 if value is not available or -1 on error
 */
int liblnk_file_get_droid_volume_identifier(
     liblnk_file_t *file,
     uint8_t *guid_data,
     size_t guid_data_size,
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

	if( guid_data == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid GUID data.",
		 function );

		return( -1 );
	}
	if( guid_data_size > (size_t) SSIZE_MAX )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_VALUE_EXCEEDS_MAXIMUM,
		 "%s: GUID data size value exceeds maximum.",
		 function );

		return( -1 );
	}
	if( guid_data_size < 16 )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_VALUE_TOO_SMALL,
		 "%s: GUID data size value too small.",
		 function );

		return( -1 );
	}
	if( internal_file->distributed_link_tracker_properties == NULL )
	{
		return( 0 );
	}
	if( memory_copy(
	     guid_data,
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
 * Returns 1 if successful, 0 if value is not available or -1 on error
 */
int liblnk_file_get_droid_file_identifier(
     liblnk_file_t *file,
     uint8_t *guid_data,
     size_t guid_data_size,
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

	if( guid_data == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid GUID data.",
		 function );

		return( -1 );
	}
	if( guid_data_size > (size_t) SSIZE_MAX )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_VALUE_EXCEEDS_MAXIMUM,
		 "%s: GUID data size value exceeds maximum.",
		 function );

		return( -1 );
	}
	if( guid_data_size < 16 )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_VALUE_TOO_SMALL,
		 "%s: GUID data size value too small.",
		 function );

		return( -1 );
	}
	if( internal_file->distributed_link_tracker_properties == NULL )
	{
		return( 0 );
	}
	if( memory_copy(
	     guid_data,
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
 * Returns 1 if successful, 0 if value is not available or -1 on error
 */
int liblnk_file_get_birth_droid_volume_identifier(
     liblnk_file_t *file,
     uint8_t *guid_data,
     size_t guid_data_size,
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

	if( guid_data == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid GUID data.",
		 function );

		return( -1 );
	}
	if( guid_data_size > (size_t) SSIZE_MAX )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_VALUE_EXCEEDS_MAXIMUM,
		 "%s: GUID data size value exceeds maximum.",
		 function );

		return( -1 );
	}
	if( guid_data_size < 16 )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_VALUE_TOO_SMALL,
		 "%s: GUID data size value too small.",
		 function );

		return( -1 );
	}
	if( internal_file->distributed_link_tracker_properties == NULL )
	{
		return( 0 );
	}
	if( memory_copy(
	     guid_data,
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
 * Returns 1 if successful, 0 if value is not available or -1 on error
 */
int liblnk_file_get_birth_droid_file_identifier(
     liblnk_file_t *file,
     uint8_t *guid_data,
     size_t guid_data_size,
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

	if( guid_data == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid GUID data.",
		 function );

		return( -1 );
	}
	if( guid_data_size > (size_t) SSIZE_MAX )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_VALUE_EXCEEDS_MAXIMUM,
		 "%s: GUID data size value exceeds maximum.",
		 function );

		return( -1 );
	}
	if( guid_data_size < 16 )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_VALUE_TOO_SMALL,
		 "%s: GUID data size value too small.",
		 function );

		return( -1 );
	}
	if( internal_file->distributed_link_tracker_properties == NULL )
	{
		return( 0 );
	}
	if( memory_copy(
	     guid_data,
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

