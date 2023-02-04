/*
 * Data block functions
 *
 * Copyright (C) 2009-2023, Joachim Metz <joachim.metz@gmail.com>
 *
 * Refer to AUTHORS for acknowledgements.
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU Lesser General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU Lesser General Public License
 * along with this program.  If not, see <https://www.gnu.org/licenses/>.
 */

#include <common.h>
#include <byte_stream.h>
#include <memory.h>
#include <types.h>

#include "liblnk_data_block.h"
#include "liblnk_libbfio.h"
#include "liblnk_libcerror.h"
#include "liblnk_libcnotify.h"

/* Creates a data block
 * Make sure the value data_block is referencing, is set to NULL
 * Returns 1 if successful or -1 on error
 */
int liblnk_data_block_initialize(
     liblnk_data_block_t **data_block,
     libcerror_error_t **error )
{
	liblnk_internal_data_block_t *internal_data_block = NULL;
	static char *function                             = "liblnk_data_block_initialize";

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
	internal_data_block = memory_allocate_structure(
	                       liblnk_internal_data_block_t );

	if( internal_data_block == NULL )
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
	     internal_data_block,
	     0,
	     sizeof( liblnk_internal_data_block_t ) ) == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_MEMORY,
		 LIBCERROR_MEMORY_ERROR_SET_FAILED,
		 "%s: unable to clear data block.",
		 function );

		goto on_error;
	}
	*data_block = (liblnk_data_block_t *) internal_data_block;

	return( 1 );

on_error:
	if( internal_data_block != NULL )
	{
		memory_free(
		 internal_data_block );
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
		*data_block = NULL;
	}
	return( 1 );
}

/* Frees a data block
 * Returns 1 if successful or -1 on error
 */
int liblnk_internal_data_block_free(
     liblnk_internal_data_block_t **internal_data_block,
     libcerror_error_t **error )
{
	static char *function = "liblnk_internal_data_block_free";
	int result            = 1;

	if( internal_data_block == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid data block.",
		 function );

		return( -1 );
	}
	if( *internal_data_block != NULL )
	{
		if( ( *internal_data_block )->value != NULL )
		{
			if( ( *internal_data_block )->free_value != NULL )
			{
				if( ( *internal_data_block )->free_value(
				     &( ( *internal_data_block )->value ),
				     error ) != 1 )
				{
					libcerror_error_set(
					 error,
					 LIBCERROR_ERROR_DOMAIN_RUNTIME,
					 LIBCERROR_RUNTIME_ERROR_FINALIZE_FAILED,
					 "%s: unable to free data block value.",
					 function );

					result = -1;
				}
			}
		}
		if( ( *internal_data_block )->data != NULL )
		{
			memory_free(
			 ( *internal_data_block )->data );
		}
		memory_free(
		 *internal_data_block );

		*internal_data_block = NULL;
	}
	return( result );
}

/* Sets the data of a data block
 * Returns 1 if successful or -1 on error
 */
int liblnk_data_block_set_data(
     liblnk_data_block_t *data_block,
     const uint8_t *data,
     size_t data_size,
     libcerror_error_t **error )
{
	liblnk_internal_data_block_t *internal_data_block = NULL;
	static char *function                             = "liblnk_data_block_set_data";

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
	internal_data_block = (liblnk_internal_data_block_t *) data_block;

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
	if( data_size > MEMORY_MAXIMUM_ALLOCATION_SIZE )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_VALUE_OUT_OF_BOUNDS,
		 "%s: invalid data size value out of bounds.",
		 function );

		return( -1 );
	}
	internal_data_block->data = (uint8_t *) memory_allocate(
	                                         sizeof( uint8_t ) * data_size );

	if( internal_data_block->data == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_MEMORY,
		 LIBCERROR_MEMORY_ERROR_INSUFFICIENT,
		 "%s: unable to create data block data.",
		 function );

		goto on_error;
	}
	internal_data_block->data_size = data_size;

	if( memory_copy(
	     internal_data_block->data,
	     data,
	     data_size ) == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_MEMORY,
		 LIBCERROR_MEMORY_ERROR_COPY_FAILED,
		 "%s: unable to copy data.",
		 function );

		goto on_error;
	}
	return( 1 );

on_error:
	if( internal_data_block->data != NULL )
	{
		memory_free(
		 internal_data_block->data );

		internal_data_block->data = NULL;
	}
	internal_data_block->size = 0;

	return( -1 );
}

/* Reads a data block
 * Returns 1 if successful or -1 on error
 */
int liblnk_data_block_read_data(
     liblnk_data_block_t *data_block,
     const uint8_t *data,
     size_t data_size,
     libcerror_error_t **error )
{
	liblnk_internal_data_block_t *internal_data_block = NULL;
	static char *function                             = "liblnk_data_block_read_data";

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
	internal_data_block = (liblnk_internal_data_block_t *) data_block;

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
	if( ( data_size < 4 )
	 || ( data_size > (size_t) SSIZE_MAX ) )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_VALUE_OUT_OF_BOUNDS,
		 "%s: invalid data size value out of bounds.",
		 function );

		return( -1 );
	}
#if defined( HAVE_DEBUG_OUTPUT )
	if( libcnotify_verbose != 0 )
	{
		libcnotify_printf(
		 "%s: data block data:\n",
		 function );
		libcnotify_print_data(
		 data,
		 data_size,
		 LIBCNOTIFY_PRINT_DATA_FLAG_GROUP_DATA );
	}
#endif /* defined( HAVE_DEBUG_OUTPUT ) */

	byte_stream_copy_to_uint32_little_endian(
	 data,
	 internal_data_block->signature );

#if defined( HAVE_DEBUG_OUTPUT )
	if( libcnotify_verbose != 0 )
	{
		libcnotify_printf(
		 "%s: data block signature\t\t\t: 0x%08" PRIx32 "\n",
		 function,
		 internal_data_block->signature );

		if( data_size > 4 )
		{
			libcnotify_printf(
			 "%s: data block data:\n",
			 function );
			libcnotify_print_data(
			 &( data[ 4 ] ),
			 data_size - 4,
			 LIBCNOTIFY_PRINT_DATA_FLAG_GROUP_DATA );
		}
	}
#endif /* defined( HAVE_DEBUG_OUTPUT ) */

	return( 1 );
}

/* Reads a data block
 * Returns the number of bytes read if successful or -1 on error
 */
int liblnk_data_block_read_file_io_handle(
     liblnk_data_block_t *data_block,
     liblnk_io_handle_t *io_handle,
     libbfio_handle_t *file_io_handle,
     off64_t file_offset,
     libcerror_error_t **error )
{
	uint8_t data_block_size_data[ 4 ];

	liblnk_internal_data_block_t *internal_data_block = NULL;
	static char *function                             = "liblnk_data_block_read_file_io_handle";
	ssize_t read_count                                = 0;

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
	internal_data_block = (liblnk_internal_data_block_t *) data_block;

	if( internal_data_block->data != NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_VALUE_ALREADY_SET,
		 "%s: invalid data block - data already set.",
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
		 file_offset,
		 file_offset );
	}
#endif
	read_count = libbfio_handle_read_buffer_at_offset(
		      file_io_handle,
		      data_block_size_data,
		      4,
		      file_offset,
		      error );

	if( read_count != (ssize_t) 4 )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_IO,
		 LIBCERROR_IO_ERROR_READ_FAILED,
		 "%s: unable to read data block size at offset: %" PRIi64 " (0x%08" PRIx64 ").",
		 function,
		 file_offset,
		 file_offset );

		goto on_error;
	}
	byte_stream_copy_to_uint32_little_endian(
	 data_block_size_data,
	 internal_data_block->size );

#if defined( HAVE_DEBUG_OUTPUT )
	if( libcnotify_verbose != 0 )
	{
		libcnotify_printf(
		 "%s: data block size\t\t\t: %" PRIu32 "\n",
		 function,
		 internal_data_block->size );
	}
#endif
	if( internal_data_block->size > 0 )
	{
		if( ( internal_data_block->size < 4 )
		 || ( internal_data_block->size > ( MEMORY_MAXIMUM_ALLOCATION_SIZE + 4 ) ) )
		{
			libcerror_error_set(
			 error,
			 LIBCERROR_ERROR_DOMAIN_RUNTIME,
			 LIBCERROR_RUNTIME_ERROR_VALUE_OUT_OF_BOUNDS,
			 "%s: invalid data block size value out of bounds.",
			 function );

			goto on_error;
		}
		internal_data_block->data_size = internal_data_block->size - 4;

		internal_data_block->data = (uint8_t *) memory_allocate(
		                                         sizeof( uint8_t ) * internal_data_block->data_size );

		if( internal_data_block->data == NULL )
		{
			libcerror_error_set(
			 error,
			 LIBCERROR_ERROR_DOMAIN_MEMORY,
			 LIBCERROR_MEMORY_ERROR_INSUFFICIENT,
			 "%s: unable to create data block data.",
			 function );

			goto on_error;
		}
		if( (off64_t) internal_data_block->size > (off64_t) ( io_handle->file_size - file_offset ) )
		{
			libcerror_error_set(
			 error,
			 LIBCERROR_ERROR_DOMAIN_RUNTIME,
			 LIBCERROR_RUNTIME_ERROR_VALUE_OUT_OF_BOUNDS,
			 "%s: invalid data block size value exceeds file size.",
			 function );

			goto on_error;
		}
		read_count = libbfio_handle_read_buffer(
			      file_io_handle,
			      internal_data_block->data,
			      internal_data_block->data_size,
			      error );

		if( read_count != (ssize_t) internal_data_block->data_size )
		{
			libcerror_error_set(
			 error,
			 LIBCERROR_ERROR_DOMAIN_IO,
			 LIBCERROR_IO_ERROR_READ_FAILED,
			 "%s: unable to read data block data.",
			 function );

			goto on_error;
		}
		if( liblnk_data_block_read_data(
		     data_block,
		     internal_data_block->data,
		     internal_data_block->data_size,
		     error ) != 1 )
		{
			libcerror_error_set(
			 error,
			 LIBCERROR_ERROR_DOMAIN_IO,
			 LIBCERROR_IO_ERROR_READ_FAILED,
			 "%s: unable to read data block.",
			 function );

			goto on_error;
		}
	}
	internal_data_block->ascii_codepage = io_handle->ascii_codepage;

	return( 1 );

on_error:
	if( internal_data_block->data != NULL )
	{
		memory_free(
		 internal_data_block->data );

		internal_data_block->data = NULL;
	}
	internal_data_block->size = 0;

	return( -1 );
}

/* Retrieves the size
 * Returns 1 if successful or -1 on error
 */
int liblnk_internal_data_block_get_size(
     liblnk_internal_data_block_t *internal_data_block,
     uint32_t *size,
     libcerror_error_t **error )
{
	static char *function = "liblnk_internal_data_block_get_size";

	if( internal_data_block == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid data block.",
		 function );

		return( -1 );
	}
	if( size == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid size.",
		 function );

		return( -1 );
	}
	*size = internal_data_block->size;

	return( 1 );
}

/* Retrieves the signature
 * Returns 1 if successful or -1 on error
 */
int liblnk_data_block_get_signature(
     liblnk_data_block_t *data_block,
     uint32_t *signature,
     libcerror_error_t **error )
{
	liblnk_internal_data_block_t *internal_data_block = NULL;
	static char *function                             = "liblnk_data_block_get_signature";

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
	internal_data_block = (liblnk_internal_data_block_t *) data_block;

	if( internal_data_block->data_size < 4 )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_VALUE_OUT_OF_BOUNDS,
		 "%s: invalid data block - data size value out of bounds.",
		 function );

		return( -1 );
	}
	if( signature == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid signature.",
		 function );

		return( -1 );
	}
	*signature = internal_data_block->signature;

	return( 1 );
}

/* Retrieves the data block data size
 * Returns 1 if successful or -1 on error
 */
int liblnk_data_block_get_data_size(
     liblnk_data_block_t *data_block,
     size_t *data_size,
     libcerror_error_t **error )
{
	liblnk_internal_data_block_t *internal_data_block = NULL;
	static char *function                             = "liblnk_data_block_get_data_size";

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
	internal_data_block = (liblnk_internal_data_block_t *) data_block;

	if( internal_data_block->data_size < 4 )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_VALUE_OUT_OF_BOUNDS,
		 "%s: invalid data block - data size value out of bounds.",
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
	*data_size = (size_t) internal_data_block->data_size - 4;

	return( 1 );
}

/* Copies the data block data to the buffer
 * Returns 1 if successful or -1 on error
 */
int liblnk_data_block_copy_data(
     liblnk_data_block_t *data_block,
     uint8_t *data,
     size_t data_size,
     libcerror_error_t **error )
{
	liblnk_internal_data_block_t *internal_data_block = NULL;
	static char *function                             = "liblnk_data_block_copy_data";

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
	internal_data_block = (liblnk_internal_data_block_t *) data_block;

	if( internal_data_block->data_size < 4 )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_VALUE_OUT_OF_BOUNDS,
		 "%s: invalid data block - data size value out of bounds.",
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
	if( data_size < (size_t) ( internal_data_block->data_size - 4 ) )
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
	     &( internal_data_block->data[ 4 ] ),
	     internal_data_block->data_size - 4 ) == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_MEMORY,
		 LIBCERROR_MEMORY_ERROR_COPY_FAILED,
		 "%s: unable to copy data block data.",
		 function );

		return( -1 );
	}
	return( 1 );
}

