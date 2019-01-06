/*
 * Data string functions
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
#include <byte_stream.h>
#include <memory.h>
#include <types.h>

#include "liblnk_data_block.h"
#include "liblnk_definitions.h"
#include "liblnk_libbfio.h"
#include "liblnk_libcerror.h"
#include "liblnk_libcnotify.h"
#include "liblnk_libuna.h"

/* Creates a data block
 * Make sure the value data_block is referencing, is set to NULL
 * Returns 1 if successful or -1 on error
 */
int liblnk_data_block_initialize(
     liblnk_data_block_t **data_block,
     libcerror_error_t **error )
{
	static char *function = "liblnk_data_block_initialize";

	if( data_block == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid data block.",
		 function );

		return( -1 );
	}
	if( *data_block != NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_VALUE_ALREADY_SET,
		 "%s: invalid data block value already set.",
		 function );

		return( -1 );
	}
	*data_block = memory_allocate_structure(
	               liblnk_data_block_t );

	if( *data_block == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_MEMORY,
		 LIBCERROR_MEMORY_ERROR_INSUFFICIENT,
		 "%s: unable to create data block.",
		 function );

		goto on_error;
	}
	if( memory_set(
	     *data_block,
	     0,
	     sizeof( liblnk_data_block_t ) ) == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_MEMORY,
		 LIBCERROR_MEMORY_ERROR_SET_FAILED,
		 "%s: unable to clear data block.",
		 function );

		goto on_error;
	}
	return( 1 );

on_error:
	if( *data_block != NULL )
	{
		memory_free(
		 *data_block );

		*data_block = NULL;
	}
	return( -1 );
}

/* Frees a data block
 * Returns 1 if successful or -1 on error
 */
int liblnk_data_block_free(
     liblnk_data_block_t **data_block,
     libcerror_error_t **error )
{
	static char *function = "liblnk_data_block_free";

	if( data_block == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid data block.",
		 function );

		return( -1 );
	}
	if( *data_block != NULL )
	{
		if( ( *data_block )->data != NULL )
		{
			memory_free(
			 ( *data_block )->data );
		}
		memory_free(
		 *data_block );

		*data_block = NULL;
	}
	return( 1 );
}

/* Reads a data block
 * Returns the number of bytes read if successful or -1 on error
 */
ssize_t liblnk_data_block_read(
         liblnk_data_block_t *data_block,
         liblnk_io_handle_t *io_handle,
         libbfio_handle_t *file_io_handle,
         off64_t data_block_offset,
         libcerror_error_t **error )
{
	uint8_t data_block_size_data[ 4 ];

	static char *function = "liblnk_io_handle_read_data_blocks";
	ssize_t read_count    = 0;

	if( data_block == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid data block.",
		 function );

		return( -1 );
	}
	if( io_handle == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid IO handle.",
		 function );

		return( -1 );
	}
#if defined( HAVE_DEBUG_OUTPUT )
	if( libcnotify_verbose != 0 )
	{
		libcnotify_printf(
		 "%s: reading data block at offset: %" PRIi64 " (0x%08" PRIx64 ")\n",
		 function,
		 data_block_offset,
		 data_block_offset );
	}
#endif
	if( libbfio_handle_seek_offset(
	     file_io_handle,
	     data_block_offset,
	     SEEK_SET,
	     error ) == -1 )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_IO,
		 LIBCERROR_IO_ERROR_SEEK_FAILED,
		 "%s: unable to seek data blocks offset: %" PRIi64 ".",
		 function,
		 data_block_offset );

		goto on_error;
	}
	read_count = libbfio_handle_read_buffer(
		      file_io_handle,
		      data_block_size_data,
		      4,
		      error );

	if( read_count != (ssize_t) 4 )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_IO,
		 LIBCERROR_IO_ERROR_READ_FAILED,
		 "%s: unable to read data block size.",
		 function );

		goto on_error;
	}
	data_block_offset += read_count;

	byte_stream_copy_to_uint32_little_endian(
	 data_block_size_data,
	 data_block->data_size );

#if defined( HAVE_DEBUG_OUTPUT )
	if( libcnotify_verbose != 0 )
	{
		libcnotify_printf(
		 "%s: data block size\t\t\t: %" PRIu32 "\n",
		 function,
		 data_block->data_size );
	}
#endif
	if( data_block->data_size > 0 )
	{
		if( data_block->data_size < 4 )
		{
			libcerror_error_set(
			 error,
			 LIBCERROR_ERROR_DOMAIN_RUNTIME,
			 LIBCERROR_RUNTIME_ERROR_VALUE_OUT_OF_BOUNDS,
			 "%s: data block size too small.",
			 function );

			goto on_error;
		}
		data_block->data_size -= 4;

		if( ( data_block_offset + (off64_t) data_block->data_size ) > (off64_t) io_handle->file_size )
		{
			libcerror_error_set(
			 error,
			 LIBCERROR_ERROR_DOMAIN_RUNTIME,
			 LIBCERROR_RUNTIME_ERROR_VALUE_OUT_OF_BOUNDS,
			 "%s: data block size exceeds file size.",
			 function );

			goto on_error;
		}
		data_block->data = (uint8_t *) memory_allocate(
		                                sizeof( uint8_t ) * data_block->data_size );

		if( data_block->data == NULL )
		{
			libcerror_error_set(
			 error,
			 LIBCERROR_ERROR_DOMAIN_MEMORY,
			 LIBCERROR_MEMORY_ERROR_INSUFFICIENT,
			 "%s: unable to create data block data.",
			 function );

			goto on_error;
		}
		read_count = libbfio_handle_read_buffer(
			      file_io_handle,
			      data_block->data,
			      data_block->data_size,
			      error );

		if( read_count != (ssize_t) data_block->data_size )
		{
			libcerror_error_set(
			 error,
			 LIBCERROR_ERROR_DOMAIN_IO,
			 LIBCERROR_IO_ERROR_READ_FAILED,
			 "%s: unable to read data block data.",
			 function );

			goto on_error;
		}
		read_count += 4;

		if( data_block->data_size < 4 )
		{
			libcerror_error_set(
			 error,
			 LIBCERROR_ERROR_DOMAIN_RUNTIME,
			 LIBCERROR_RUNTIME_ERROR_VALUE_OUT_OF_BOUNDS,
			 "%s: data block size too small.",
			 function );

			goto on_error;
		}
		byte_stream_copy_to_uint32_little_endian(
		 data_block->data,
		 data_block->signature );

#if defined( HAVE_DEBUG_OUTPUT )
		if( libcnotify_verbose != 0 )
		{
			libcnotify_printf(
			 "%s: data block signature\t\t\t: 0x%08" PRIx32 "\n",
			 function,
			 data_block->signature );

			if( data_block->data_size > 4 )
			{
				libcnotify_printf(
				 "%s: data block data:\n",
				 function );
				libcnotify_print_data(
				 &( data_block->data[ 4 ] ),
				 data_block->data_size - 4,
				 LIBCNOTIFY_PRINT_DATA_FLAG_GROUP_DATA );
			}
		}
#endif
	}
	return( read_count );

on_error:
	if( data_block->data != NULL )
	{
		memory_free(
		 data_block->data );

		data_block->data = NULL;
	}
	data_block->data_size = 0;

	return( -1 );
}

