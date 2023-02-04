/*
 * Distributed link tracking data block functions
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
#include <types.h>

#include "liblnk_data_block.h"
#include "liblnk_definitions.h"
#include "liblnk_distributed_link_tracker_properties.h"
#include "liblnk_libcerror.h"

/* Reads a distributed link tracking data block
 * Returns 1 if successful or -1 on error
 */
int liblnk_distributed_link_tracking_data_block_read(
     liblnk_data_block_t *data_block,
     libcerror_error_t **error )
{
	liblnk_distributed_link_tracker_properties_t *distributed_link_tracker_properties = NULL;
	liblnk_internal_data_block_t *internal_data_block                                 = NULL;
	static char *function                                                             = "liblnk_distributed_link_tracking_data_block_read";

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

	if( liblnk_distributed_link_tracker_properties_initialize(
	     &distributed_link_tracker_properties,
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
	     distributed_link_tracker_properties,
	     data_block,
	     internal_data_block->ascii_codepage,
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
	internal_data_block->value      = (intptr_t *) distributed_link_tracker_properties;
	internal_data_block->free_value = (int(*)(intptr_t **, libcerror_error_t **)) &liblnk_distributed_link_tracker_properties_free;

	return( 1 );

on_error:
	if( distributed_link_tracker_properties != NULL )
	{
		liblnk_distributed_link_tracker_properties_free(
		 &distributed_link_tracker_properties,
		 NULL );
	}
	return( -1 );
}

/* Retrieves the size of the UTF-8 encoded machine identifier
 * The size includes the end of string character
 * Returns 1 if successful or -1 on error
 */
int liblnk_distributed_link_tracking_data_block_get_utf8_machine_identifier_size(
     liblnk_data_block_t *data_block,
     size_t *utf8_string_size,
     libcerror_error_t **error )
{
	liblnk_internal_data_block_t *internal_data_block = NULL;
	static char *function                             = "liblnk_distributed_link_tracking_data_block_get_utf8_machine_identifier_size";

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

	if( internal_data_block->value == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_VALUE_MISSING,
		 "%s: invalid data block - missing value.",
		 function );

		return( -1 );
	}
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
	if( internal_data_block->signature != LIBLNK_DATA_BLOCK_SIGNATURE_DISTRIBUTED_LINK_TRACKER_PROPERTIES )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_UNSUPPORTED_VALUE,
		 "%s: invalid data block - unsupported signature.",
		 function );

		return( -1 );
	}
	if( liblnk_distributed_link_tracker_properties_get_utf8_machine_identifier_size(
	     (liblnk_distributed_link_tracker_properties_t *) internal_data_block->value,
	     utf8_string_size,
	     internal_data_block->ascii_codepage,
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
 * Returns 1 if successful or -1 on error
 */
int liblnk_distributed_link_tracking_data_block_get_utf8_machine_identifier(
     liblnk_data_block_t *data_block,
     uint8_t *utf8_string,
     size_t utf8_string_size,
     libcerror_error_t **error )
{
	liblnk_internal_data_block_t *internal_data_block = NULL;
	static char *function                             = "liblnk_distributed_link_tracking_data_block_get_utf8_machine_identifier";

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

	if( internal_data_block->value == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_VALUE_MISSING,
		 "%s: invalid data block - missing value.",
		 function );

		return( -1 );
	}
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
	if( internal_data_block->signature != LIBLNK_DATA_BLOCK_SIGNATURE_DISTRIBUTED_LINK_TRACKER_PROPERTIES )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_UNSUPPORTED_VALUE,
		 "%s: invalid data block - unsupported signature.",
		 function );

		return( -1 );
	}
	if( liblnk_distributed_link_tracker_properties_get_utf8_machine_identifier(
	     (liblnk_distributed_link_tracker_properties_t *) internal_data_block->value,
	     utf8_string,
	     utf8_string_size,
	     internal_data_block->ascii_codepage,
	     error ) != 1 )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_GET_FAILED,
		 "%s: unable to retrieve UTF-8 machine identifier string.",
		 function );

		return( -1 );
	}
	return( 1 );
}

/* Retrieves the size of the UTF-16 encoded machine identifier
 * The size includes the end of string character
 * Returns 1 if successful or -1 on error
 */
int liblnk_distributed_link_tracking_data_block_get_utf16_machine_identifier_size(
     liblnk_data_block_t *data_block,
     size_t *utf16_string_size,
     libcerror_error_t **error )
{
	liblnk_internal_data_block_t *internal_data_block = NULL;
	static char *function                             = "liblnk_distributed_link_tracking_data_block_get_utf16_machine_identifier_size";

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

	if( internal_data_block->value == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_VALUE_MISSING,
		 "%s: invalid data block - missing value.",
		 function );

		return( -1 );
	}
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
	if( internal_data_block->signature != LIBLNK_DATA_BLOCK_SIGNATURE_DISTRIBUTED_LINK_TRACKER_PROPERTIES )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_UNSUPPORTED_VALUE,
		 "%s: invalid data block - unsupported signature.",
		 function );

		return( -1 );
	}
	if( liblnk_distributed_link_tracker_properties_get_utf16_machine_identifier_size(
	     (liblnk_distributed_link_tracker_properties_t *) internal_data_block->value,
	     utf16_string_size,
	     internal_data_block->ascii_codepage,
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
 * Returns 1 if successful or -1 on error
 */
int liblnk_distributed_link_tracking_data_block_get_utf16_machine_identifier(
     liblnk_data_block_t *data_block,
     uint16_t *utf16_string,
     size_t utf16_string_size,
     libcerror_error_t **error )
{
	liblnk_internal_data_block_t *internal_data_block = NULL;
	static char *function                             = "liblnk_distributed_link_tracking_data_block_get_utf16_machine_identifier";

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

	if( internal_data_block->value == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_VALUE_MISSING,
		 "%s: invalid data block - missing value.",
		 function );

		return( -1 );
	}
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
	if( internal_data_block->signature != LIBLNK_DATA_BLOCK_SIGNATURE_DISTRIBUTED_LINK_TRACKER_PROPERTIES )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_UNSUPPORTED_VALUE,
		 "%s: invalid data block - unsupported signature.",
		 function );

		return( -1 );
	}
	if( liblnk_distributed_link_tracker_properties_get_utf16_machine_identifier(
	     (liblnk_distributed_link_tracker_properties_t *) internal_data_block->value,
	     utf16_string,
	     utf16_string_size,
	     internal_data_block->ascii_codepage,
	     error ) != 1 )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_GET_FAILED,
		 "%s: unable to retrieve UTF-16 machine identifier string.",
		 function );

		return( -1 );
	}
	return( 1 );
}

/* Retrieves the droid volume identifier
 * The identifier is a GUID stored in little-endian and is 16 bytes of size
 * Returns 1 if successful or -1 on error
 */
int liblnk_distributed_link_tracking_data_block_get_droid_volume_identifier(
     liblnk_data_block_t *data_block,
     uint8_t *guid_data,
     size_t guid_data_size,
     libcerror_error_t **error )
{
	liblnk_internal_data_block_t *internal_data_block = NULL;
	static char *function                             = "liblnk_distributed_link_tracking_data_block_get_droid_volume_identifier";

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

	if( internal_data_block->value == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_VALUE_MISSING,
		 "%s: invalid data block - missing value.",
		 function );

		return( -1 );
	}
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
	if( internal_data_block->signature != LIBLNK_DATA_BLOCK_SIGNATURE_DISTRIBUTED_LINK_TRACKER_PROPERTIES )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_UNSUPPORTED_VALUE,
		 "%s: invalid data block - unsupported signature.",
		 function );

		return( -1 );
	}
	if( liblnk_distributed_link_tracker_properties_get_droid_volume_identifier(
	     (liblnk_distributed_link_tracker_properties_t *) internal_data_block->value,
	     guid_data,
	     guid_data_size,
	     error ) != 1 )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_GET_FAILED,
		 "%s: unable to retrieve droid volume identifier.",
		 function );

		return( -1 );
	}
	return( 1 );
}

/* Retrieves the droid file identifier
 * The identifier is a GUID stored in little-endian and is 16 bytes of size
 * Returns 1 if successful or -1 on error
 */
int liblnk_distributed_link_tracking_data_block_get_droid_file_identifier(
     liblnk_data_block_t *data_block,
     uint8_t *guid_data,
     size_t guid_data_size,
     libcerror_error_t **error )
{
	liblnk_internal_data_block_t *internal_data_block = NULL;
	static char *function                             = "liblnk_distributed_link_tracking_data_block_get_droid_file_identifier";

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

	if( internal_data_block->value == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_VALUE_MISSING,
		 "%s: invalid data block - missing value.",
		 function );

		return( -1 );
	}
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
	if( internal_data_block->signature != LIBLNK_DATA_BLOCK_SIGNATURE_DISTRIBUTED_LINK_TRACKER_PROPERTIES )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_UNSUPPORTED_VALUE,
		 "%s: invalid data block - unsupported signature.",
		 function );

		return( -1 );
	}
	if( liblnk_distributed_link_tracker_properties_get_droid_file_identifier(
	     (liblnk_distributed_link_tracker_properties_t *) internal_data_block->value,
	     guid_data,
	     guid_data_size,
	     error ) != 1 )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_GET_FAILED,
		 "%s: unable to retrieve droid file identifier.",
		 function );

		return( -1 );
	}
	return( 1 );
}

/* Retrieves the birth droid volume identifier
 * The identifier is a GUID stored in little-endian and is 16 bytes of size
 * Returns 1 if successful or -1 on error
 */
int liblnk_distributed_link_tracking_data_block_get_birth_droid_volume_identifier(
     liblnk_data_block_t *data_block,
     uint8_t *guid_data,
     size_t guid_data_size,
     libcerror_error_t **error )
{
	liblnk_internal_data_block_t *internal_data_block = NULL;
	static char *function                             = "liblnk_distributed_link_tracking_data_block_get_birth_droid_volume_identifier";

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

	if( internal_data_block->value == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_VALUE_MISSING,
		 "%s: invalid data block - missing value.",
		 function );

		return( -1 );
	}
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
	if( internal_data_block->signature != LIBLNK_DATA_BLOCK_SIGNATURE_DISTRIBUTED_LINK_TRACKER_PROPERTIES )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_UNSUPPORTED_VALUE,
		 "%s: invalid data block - unsupported signature.",
		 function );

		return( -1 );
	}
	if( liblnk_distributed_link_tracker_properties_get_birth_droid_volume_identifier(
	     (liblnk_distributed_link_tracker_properties_t *) internal_data_block->value,
	     guid_data,
	     guid_data_size,
	     error ) != 1 )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_GET_FAILED,
		 "%s: unable to retrieve birth droid volume identifier.",
		 function );

		return( -1 );
	}
	return( 1 );
}

/* Retrieves the birth droid file identifier
 * The identifier is a GUID stored in little-endian and is 16 bytes of size
 * Returns 1 if successful or -1 on error
 */
int liblnk_distributed_link_tracking_data_block_get_birth_droid_file_identifier(
     liblnk_data_block_t *data_block,
     uint8_t *guid_data,
     size_t guid_data_size,
     libcerror_error_t **error )
{
	liblnk_internal_data_block_t *internal_data_block = NULL;
	static char *function                             = "liblnk_distributed_link_tracking_data_block_get_birth_droid_file_identifier";

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

	if( internal_data_block->value == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_VALUE_MISSING,
		 "%s: invalid data block - missing value.",
		 function );

		return( -1 );
	}
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
	if( internal_data_block->signature != LIBLNK_DATA_BLOCK_SIGNATURE_DISTRIBUTED_LINK_TRACKER_PROPERTIES )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_UNSUPPORTED_VALUE,
		 "%s: invalid data block - unsupported signature.",
		 function );

		return( -1 );
	}
	if( liblnk_distributed_link_tracker_properties_get_birth_droid_file_identifier(
	     (liblnk_distributed_link_tracker_properties_t *) internal_data_block->value,
	     guid_data,
	     guid_data_size,
	     error ) != 1 )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_GET_FAILED,
		 "%s: unable to retrieve birth droid file identifier.",
		 function );

		return( -1 );
	}
	return( 1 );
}

