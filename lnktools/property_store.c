/*
 * Property store functions
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
#include <file_stream.h>
#include <memory.h>
#include <narrow_string.h>
#include <system_string.h>
#include <types.h>
#include <wide_string.h>

#include "lnktools_libcerror.h"
#include "lnktools_libfguid.h"
#include "lnktools_libfwps.h"
#include "property_store.h"

uint8_t property_store_format_class_identifier_system1[ 16 ] = {
	0xb1, 0x16, 0x6d, 0x44, 0xad, 0x8d, 0x70, 0x48, 0xa7, 0x48, 0x40, 0x2e, 0xa4, 0x3d, 0x78, 0x8c };

uint8_t property_store_format_class_identifier_system2[ 16 ] = {
	0x30, 0xf1, 0x25, 0xb7, 0xef, 0x47, 0x1a, 0x10, 0xa5, 0xf1, 0x02, 0x60, 0x8c, 0x9e, 0xeb, 0xac };

uint8_t property_store_format_class_identifier_system3[ 16 ] = {
	0x55, 0x28, 0x4c, 0x9f, 0x79, 0x9f, 0x39, 0x4b, 0xa8, 0xd0, 0xe1, 0xd4, 0x2d, 0xe1, 0xd5, 0xf3 };

uint8_t property_store_format_class_identifier_tile[ 16 ] = {
	0x4d, 0x0b, 0xd4, 0x86, 0x69, 0x90, 0x3c, 0x44, 0x81, 0x9a, 0x2a, 0x54, 0x09, 0x0d, 0xcc, 0xec };

uint8_t property_store_format_class_identifier_winx_hash[ 16 ] = {
	0x7b, 0x2d, 0x8d, 0xfb, 0xd1, 0x90, 0x34, 0x4e, 0xbf, 0x60, 0x6e, 0xac, 0x09, 0x92, 0x2b, 0xbf };

/* Prints the property record to the notify stream
 * Returns 1 if successful or -1 on error
 */
int property_store_record_fprint(
     const uint8_t *property_set_identifier,
     libfwps_record_t *property_record,
     int record_index,
     FILE *notify_stream,
     libcerror_error_t **error )
{
	uint8_t guid_data[ 16 ];

	system_character_t guid_string[ 48 ];

	libfguid_identifier_t *guid      = NULL;
	system_character_t *value_string = NULL;
	const char *description          = "Unknown";
	static char *function            = "property_store_record_fprint";
	size_t value_string_size         = 0;
	uint64_t value_64bit             = 0;
	uint32_t entry_type              = 0;
	uint32_t value_32bit             = 0;
	uint32_t value_type              = 0;
	uint16_t value_16bit             = 0;
	uint8_t value_8bit               = 0;
	double value_floating_point      = 0.0;
	int result                       = 0;

	if( property_set_identifier == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid property set identifier.",
		 function );

		return( -1 );
	}
	result = libfwps_record_get_entry_type(
	          property_record,
	          &entry_type,
	          error );

	if( result == -1 )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_GET_FAILED,
		 "%s: unable to retrieve entry type.",
		 function );

		goto on_error;
	}
	else if( result != 0 )
	{
		if( memory_compare(
		     property_set_identifier,
		     property_store_format_class_identifier_system1,
		     16 ) == 0 )
		{
			switch( entry_type )
			{
				case 104:
					description = "System.VolumeId";
					break;

				default:
					break;
			}
		}
		else if( memory_compare(
		          property_set_identifier,
		          property_store_format_class_identifier_system2,
		          16 ) == 0 )
		{
			switch( entry_type )
			{
				case 10:
					description = "System.ItemNameDisplay";
					break;

				default:
					break;
			}
		}
		else if( memory_compare(
		          property_set_identifier,
		          property_store_format_class_identifier_system3,
		          16 ) == 0 )
		{
			switch( entry_type )
			{
				case 2:
					description = "System.AppUserModel.RelaunchCommand";
					break;

				case 3:
					description = "System.AppUserModel.RelaunchIconResource";
					break;

				case 4:
					description = "System.AppUserModel.RelaunchDisplayNameResource";
					break;

				case 5:
					description = "System.AppUserModel.ID";
					break;

				case 6:
					description = "System.AppUserModel.IsDestListSeparator";
					break;

				case 7:
					description = "PKEY_AppUserModel_IsDestListLink";
					break;

				case 8:
					description = "System.AppUserModel.ExcludeFromShowInNewInstall";
					break;

				case 9:
					description = "System.AppUserModel.PreventPinning";
					break;

				case 10:
					description = "PKEY_AppUserModel_BestShortcut";
					break;

				case 11:
					description = "System.AppUserModel.IsDualMode";
					break;

				case 12:
					description = "System.AppUserModel.StartPinOption";
					break;

				case 13:
					description = "PKEY_AppUserModel_Relevance";
					break;

				case 14:
					description = "System.AppUserModel.HostEnvironment";
					break;

				case 18:
					description = "System.AppUserModel.InstalledBy";
					break;

				case 23:
					description = "System.AppUserModel.ExcludedFromLauncher";
					break;

				case 26:
					description = "System.AppUserModel.ToastActivatorCLSID";
					break;

				default:
					break;
			}
		}
		else if( memory_compare(
		          property_set_identifier,
		          property_store_format_class_identifier_tile,
		          16 ) == 0 )
		{
			switch( entry_type )
			{
				case 2:
					description = "PKEY_Tile_SmallLogoPath";
					break;

				case 4:
					description = "PKEY_Tile_Background";
					break;

				case 5:
					description = "PKEY_Tile_Foreground";
					break;

				case 11:
					description = "PKEY_Tile_LongDisplayName";
					break;

				case 12:
					description = "PKEY_Tile_Square150x150LogoPath";
					break;

				case 13:
					description = "PKEY_Tile_Wide310x150LogoPath";
					break;

				case 14:
					description = "PKEY_Tile_Flags";
					break;

				case 15:
					description = "PKEY_Tile_BadgeLogoPath";
					break;

				case 16:
					description = "PKEY_Tile_SuiteDisplayName";
					break;

				case 17:
					description = "PKEY_Tile_SuiteSortName";
					break;

				case 18:
					description = "PKEY_Tile_DisplayNameLanguage";
					break;

				case 19:
					description = "PKEY_Tile_Square310x310LogoPath";
					break;

				case 20:
					description = "PKEY_Tile_Square70x70LogoPath";
					break;

				case 21:
					description = "PKEY_Tile_FencePost";
					break;

				case 22:
					description = "PKEY_Tile_InstallProgress";
					break;

				case 23:
					description = "PKEY_Tile_EncodedTargetPath";
					break;

				default:
					break;
			}
		}
		else if( memory_compare(
		          property_set_identifier,
		          property_store_format_class_identifier_winx_hash,
		          16 ) == 0 )
		{
			switch( entry_type )
			{
				case 2:
					description = "PKEY_Winx_Hash";
					break;

				default:
					break;
			}
		}
		fprintf(
		 notify_stream,
		 "\t\tProperty: %d\t\t: %s\n",
		 entry_type,
		 description );
	}
/* TODO get name if no entry_type */

	if( libfwps_record_get_value_type(
	     property_record,
	     &value_type,
	     error ) != 1 )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_GET_FAILED,
		 "%s: unable to retrieve value type.",
		 function );

		goto on_error;
	}
	fprintf(
	 notify_stream,
	 "\t\tValue: 0x%04" PRIx32 "\t\t:",
	 value_type );

	switch( value_type )
	{
		case LIBFWPS_VALUE_TYPE_INTEGER_8BIT_SIGNED:
		case LIBFWPS_VALUE_TYPE_INTEGER_8BIT_UNSIGNED:
			if( libfwps_record_get_data_as_8bit_integer(
			     property_record,
			     &value_8bit,
			     error ) != 1 )
			{
				libcerror_error_set(
				 error,
				 LIBCERROR_ERROR_DOMAIN_RUNTIME,
				 LIBCERROR_RUNTIME_ERROR_GET_FAILED,
				 "%s: unable to retrieve 8-bit integer value.",
				 function );

				goto on_error;
			}
			if( value_type == LIBFWPS_VALUE_TYPE_INTEGER_8BIT_SIGNED )
			{
				fprintf(
				 notify_stream,
				 " %" PRIi8 "",
				 (int8_t) value_8bit );
			}
			else
			{
				fprintf(
				 notify_stream,
				 " %" PRIu8 "",
				 value_8bit );
			}
			break;

		case LIBFWPS_VALUE_TYPE_INTEGER_16BIT_SIGNED:
		case LIBFWPS_VALUE_TYPE_INTEGER_16BIT_UNSIGNED:
			if( libfwps_record_get_data_as_16bit_integer(
			     property_record,
			     &value_16bit,
			     error ) != 1 )
			{
				libcerror_error_set(
				 error,
				 LIBCERROR_ERROR_DOMAIN_RUNTIME,
				 LIBCERROR_RUNTIME_ERROR_GET_FAILED,
				 "%s: unable to retrieve 16-bit integer value.",
				 function );

				goto on_error;
			}
			if( value_type == LIBFWPS_VALUE_TYPE_INTEGER_16BIT_SIGNED )
			{
				fprintf(
				 notify_stream,
				 " %" PRIi16 "",
				 (int16_t) value_16bit );
			}
			else
			{
				fprintf(
				 notify_stream,
				 " %" PRIu16 "",
				 value_16bit );
			}
			break;

		case LIBFWPS_VALUE_TYPE_INTEGER_32BIT_SIGNED:
		case LIBFWPS_VALUE_TYPE_INTEGER_32BIT_UNSIGNED:
			if( libfwps_record_get_data_as_32bit_integer(
			     property_record,
			     &value_32bit,
			     error ) != 1 )
			{
				libcerror_error_set(
				 error,
				 LIBCERROR_ERROR_DOMAIN_RUNTIME,
				 LIBCERROR_RUNTIME_ERROR_GET_FAILED,
				 "%s: unable to retrieve 32-bit integer value.",
				 function );

				goto on_error;
			}
			if( value_type == LIBFWPS_VALUE_TYPE_INTEGER_32BIT_SIGNED )
			{
				fprintf(
				 notify_stream,
				 " %" PRIi32 "",
				 (int32_t) value_32bit );
			}
			else
			{
				fprintf(
				 notify_stream,
				 " %" PRIu32 "",
				 value_32bit );
			}
			break;

		case LIBFWPS_VALUE_TYPE_INTEGER_64BIT_SIGNED:
		case LIBFWPS_VALUE_TYPE_INTEGER_64BIT_UNSIGNED:
			if( libfwps_record_get_data_as_64bit_integer(
			     property_record,
			     &value_64bit,
			     error ) != 1 )
			{
				libcerror_error_set(
				 error,
				 LIBCERROR_ERROR_DOMAIN_RUNTIME,
				 LIBCERROR_RUNTIME_ERROR_GET_FAILED,
				 "%s: unable to retrieve 64-bit integer value.",
				 function );

				goto on_error;
			}
			if( value_type == LIBFWPS_VALUE_TYPE_INTEGER_64BIT_SIGNED )
			{
				fprintf(
				 notify_stream,
				 " %" PRIi64 "",
				 (int64_t) value_64bit );
			}
			else
			{
				fprintf(
				 notify_stream,
				 " %" PRIu64 "",
				 value_64bit );
			}
			break;

		case LIBFWPS_VALUE_TYPE_FLOAT_32BIT:
		case LIBFWPS_VALUE_TYPE_DOUBLE_64BIT:
			if( libfwps_record_get_data_as_floating_point(
			     property_record,
			     &value_floating_point,
			     error ) != 1 )
			{
				libcerror_error_set(
				 error,
				 LIBCERROR_ERROR_DOMAIN_RUNTIME,
				 LIBCERROR_RUNTIME_ERROR_GET_FAILED,
				 "%s: unable to retrieve floating point value.",
				 function );

				goto on_error;
			}
			fprintf(
			 notify_stream,
			 " %F",
			 value_floating_point );

			break;

		case LIBFWPS_VALUE_TYPE_STRING_ASCII:
		case LIBFWPS_VALUE_TYPE_STRING_UNICODE:
#if defined( HAVE_WIDE_SYSTEM_CHARACTER )
			result = libfwps_record_get_data_as_utf16_string_size(
			          property_record,
				  &value_string_size,
				  error );
#else
			result = libfwps_record_get_data_as_utf8_string_size(
			          property_record,
				  &value_string_size,
				  error );
#endif
			if( result == -1 )
			{
				libcerror_error_set(
				 error,
				 LIBCERROR_ERROR_DOMAIN_RUNTIME,
				 LIBCERROR_RUNTIME_ERROR_GET_FAILED,
				 "%s: unable to retrieve value string size.",
				 function );

				goto on_error;
			}
			if( ( result != 0 )
			 && ( value_string_size > 0 ) )
			{
				value_string = system_string_allocate(
				                value_string_size );

				if( value_string == NULL )
				{
					libcerror_error_set(
					 error,
					 LIBCERROR_ERROR_DOMAIN_MEMORY,
					 LIBCERROR_MEMORY_ERROR_INSUFFICIENT,
					 "%s: unable to create value string.",
					 function );

					goto on_error;
				}
#if defined( HAVE_WIDE_SYSTEM_CHARACTER )
				result = libfwps_record_get_data_as_utf16_string(
				          property_record,
					  (uint16_t *) value_string,
					  value_string_size,
					  error );
#else
				result = libfwps_record_get_data_as_utf8_string(
				          property_record,
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
					 "%s: unable to retrieve value string.",
					 function );

					goto on_error;
				}
				fprintf(
				 notify_stream,
				 " %" PRIs_SYSTEM "",
				 value_string );

				memory_free(
				 value_string );

				value_string = NULL;
			}
			break;

		case LIBFWPS_VALUE_TYPE_GUID:
			if( libfwps_record_get_data_as_guid(
			     property_record,
			     guid_data,
			     16,
			     error ) != 1 )
			{
				libcerror_error_set(
				 error,
				 LIBCERROR_ERROR_DOMAIN_RUNTIME,
				 LIBCERROR_RUNTIME_ERROR_GET_FAILED,
				 "%s: unable to retrieve GUID value.",
				 function );

				goto on_error;
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
			 notify_stream,
			 " %" PRIs_SYSTEM "",
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
			break;

		default:
			break;
	}
	fprintf(
	 notify_stream,
	 "\n\n" );

	return( 1 );

on_error:
	if( guid != NULL )
	{
		libfguid_identifier_free(
		 &guid,
		 NULL );
	}
	if( value_string != NULL )
	{
		memory_free(
		 value_string );
	}
	return( -1 );
}

/* Prints the property set to the notify stream
 * Returns 1 if successful or -1 on error
 */
int property_store_set_fprint(
     libfwps_set_t *property_set,
     FILE *notify_stream,
     libcerror_error_t **error )
{
	uint8_t property_set_identifier[ 16 ];

	system_character_t guid_string[ 48 ];

	libfguid_identifier_t *guid       = NULL;
	libfwps_record_t *property_record = NULL;
	static char *function             = "property_store_set_fprint";
	int number_of_records             = 0;
	int record_index                  = 0;
	int result                        = 0;

	if( libfwps_set_get_identifier(
	     property_set,
	     property_set_identifier,
	     16,
	     error ) != 1 )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_GET_FAILED,
		 "%s: unable to retrieve property set identifier.",
		 function );

		goto on_error;
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
	     property_set_identifier,
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
	 notify_stream,
	 "\tProperty set\t\t\t: %" PRIs_SYSTEM "\n",
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
	if( libfwps_set_get_number_of_records(
	     property_set,
	     &number_of_records,
	     error ) != 1 )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_GET_FAILED,
		 "%s: unable to retrieve number of records.",
		 function );

		goto on_error;
	}
	for( record_index = 0;
	     record_index < number_of_records;
	     record_index++ )
	{
		if( libfwps_set_get_record_by_index(
		     property_set,
		     record_index,
		     &property_record,
		     error ) != 1 )
		{
			libcerror_error_set(
			 error,
			 LIBCERROR_ERROR_DOMAIN_RUNTIME,
			 LIBCERROR_RUNTIME_ERROR_GET_FAILED,
			 "%s: unable to retrieve property record: %d.",
			 function,
			 record_index );

			goto on_error;
		}
		if( property_store_record_fprint(
		     property_set_identifier,
		     property_record,
		     record_index + 1,
		     notify_stream,
		     error ) == -1 )
		{
			libcerror_error_set(
			 error,
			 LIBCERROR_ERROR_DOMAIN_RUNTIME,
			 LIBCERROR_RUNTIME_ERROR_PRINT_FAILED,
			 "%s: unable to print property record: %d.",
			 function,
			 record_index );

			goto on_error;
		}
		if( libfwps_record_free(
		     &property_record,
		     error ) != 1 )
		{
			libcerror_error_set(
			 error,
			 LIBCERROR_ERROR_DOMAIN_RUNTIME,
			 LIBCERROR_RUNTIME_ERROR_FINALIZE_FAILED,
			 "%s: unable to free property record: %d.",
			 function,
			 record_index );

			goto on_error;
		}
	}
	return( 1 );

on_error:
	if( property_record != NULL )
	{
		libfwps_record_free(
		 &property_record,
		 NULL );
	}
	if( guid != NULL )
	{
		libfguid_identifier_free(
		 &guid,
		 NULL );
	}
	return( -1 );
}

/* Prints the property store to the notify stream
 * Returns 1 if successful or -1 on error
 */
int property_store_fprint(
     libfwps_store_t *property_store,
     FILE *notify_stream,
     libcerror_error_t **error )
{
	libfwps_set_t *property_set = NULL;
	static char *function       = "property_store_fprint";
	int number_of_sets          = 0;
	int set_index               = 0;

	if( libfwps_store_get_number_of_sets(
	     property_store,
	     &number_of_sets,
	     error ) != 1 )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_GET_FAILED,
		 "%s: unable to retrieve number of sets.",
		 function );

		goto on_error;
	}
	for( set_index = 0;
	     set_index < number_of_sets;
	     set_index++ )
	{
		if( libfwps_store_get_set_by_index(
		     property_store,
		     set_index,
		     &property_set,
		     error ) != 1 )
		{
			libcerror_error_set(
			 error,
			 LIBCERROR_ERROR_DOMAIN_RUNTIME,
			 LIBCERROR_RUNTIME_ERROR_GET_FAILED,
			 "%s: unable to retrieve property set: %d.",
			 function,
			 set_index );

			goto on_error;
		}
		if( property_store_set_fprint(
		     property_set,
		     notify_stream,
		     error ) == -1 )
		{
			libcerror_error_set(
			 error,
			 LIBCERROR_ERROR_DOMAIN_RUNTIME,
			 LIBCERROR_RUNTIME_ERROR_PRINT_FAILED,
			 "%s: unable to print property set: %d.",
			 function,
			 set_index );

			goto on_error;
		}
		if( libfwps_set_free(
		     &property_set,
		     error ) != 1 )
		{
			libcerror_error_set(
			 error,
			 LIBCERROR_ERROR_DOMAIN_RUNTIME,
			 LIBCERROR_RUNTIME_ERROR_FINALIZE_FAILED,
			 "%s: unable to free property set: %d.",
			 function,
			 set_index );

			goto on_error;
		}
	}
	return( 1 );

on_error:
	if( property_set != NULL )
	{
		libfwps_set_free(
		 &property_set,
		 NULL );
	}
	return( -1 );
}

