/*
 * Shell items functions
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

#include "lnktools_libcerror.h"
#include "lnktools_libfdatetime.h"
#include "lnktools_libfguid.h"
#include "lnktools_libfwsi.h"
#include "lnktools_libuna.h"
#include "shell_items.h"

/* Prints the file attribute flags to the notify stream
 */
void shell_items_file_attribute_flags_fprint(
      uint32_t file_attribute_flags,
      FILE *notify_stream )
{
	if( ( file_attribute_flags & LIBFWSI_FILE_ATTRIBUTE_FLAG_READ_ONLY ) != 0 )
	{
		fprintf(
		 notify_stream,
		 "\t\t\tIs read-only (FILE_ATTRIBUTE_READ_ONLY)\n" );
	}
	if( ( file_attribute_flags & LIBFWSI_FILE_ATTRIBUTE_FLAG_HIDDEN ) != 0 )
	{
		fprintf(
		 notify_stream,
		 "\t\t\tIs hidden (FILE_ATTRIBUTE_HIDDEN)\n" );
	}
	if( ( file_attribute_flags & LIBFWSI_FILE_ATTRIBUTE_FLAG_SYSTEM ) != 0 )
	{
		fprintf(
		 notify_stream,
		 "\t\t\tIs system (FILE_ATTRIBUTE_SYSTEM)\n" );
	}

	if( ( file_attribute_flags & LIBFWSI_FILE_ATTRIBUTE_FLAG_DIRECTORY ) != 0 )
	{
		fprintf(
		 notify_stream,
		 "\t\t\tIs directory (FILE_ATTRIBUTE_DIRECTORY)\n" );
	}
	if( ( file_attribute_flags & LIBFWSI_FILE_ATTRIBUTE_FLAG_ARCHIVE ) != 0 )
	{
		fprintf(
		 notify_stream,
		 "\t\t\tShould be archived (FILE_ATTRIBUTE_ARCHIVE)\n" );
	}
	if( ( file_attribute_flags & LIBFWSI_FILE_ATTRIBUTE_FLAG_DEVICE ) != 0 )
	{
		fprintf(
		 notify_stream,
		 "\t\t\tIs device (FILE_ATTRIBUTE_DEVICE)\n" );
	}
	if( ( file_attribute_flags & LIBFWSI_FILE_ATTRIBUTE_FLAG_NORMAL ) != 0 )
	{
		fprintf(
		 notify_stream,
		 "\t\t\tIs normal (FILE_ATTRIBUTE_NORMAL)\n" );
	}
	if( ( file_attribute_flags & LIBFWSI_FILE_ATTRIBUTE_FLAG_TEMPORARY ) != 0 )
	{
		fprintf(
		 notify_stream,
		 "\t\t\tIs temporary (FILE_ATTRIBUTE_TEMPORARY)\n" );
	}
	if( ( file_attribute_flags & LIBFWSI_FILE_ATTRIBUTE_FLAG_SPARSE_FILE ) != 0 )
	{
		fprintf(
		 notify_stream,
		 "\t\t\tIs a sparse file (FILE_ATTRIBUTE_SPARSE_FILE)\n" );
	}
	if( ( file_attribute_flags & LIBFWSI_FILE_ATTRIBUTE_FLAG_REPARSE_POINT ) != 0 )
	{
		fprintf(
		 notify_stream,
		 "\t\t\tIs a reparse point or symbolic link (FILE_ATTRIBUTE_FLAG_REPARSE_POINT)\n" );
	}
	if( ( file_attribute_flags & LIBFWSI_FILE_ATTRIBUTE_FLAG_COMPRESSED ) != 0 )
	{
		fprintf(
		 notify_stream,
		 "\t\t\tIs compressed (FILE_ATTRIBUTE_COMPRESSED)\n" );
	}
	if( ( file_attribute_flags & LIBFWSI_FILE_ATTRIBUTE_FLAG_OFFLINE ) != 0 )
	{
		fprintf(
		 notify_stream,
		 "\t\t\tIs offline (FILE_ATTRIBUTE_OFFLINE)\n" );
	}
	if( ( file_attribute_flags & LIBFWSI_FILE_ATTRIBUTE_FLAG_NOT_CONTENT_INDEXED ) != 0 )
	{
		fprintf(
		 notify_stream,
		 "\t\t\tContent should not be indexed (FILE_ATTRIBUTE_NOT_CONTENT_INDEXED)\n" );
	}
	if( ( file_attribute_flags & LIBFWSI_FILE_ATTRIBUTE_FLAG_ENCRYPTED ) != 0 )
	{
		fprintf(
		 notify_stream,
		 "\t\t\tIs encrypted (FILE_ATTRIBUTE_ENCRYPTED)\n" );
	}

	if( ( file_attribute_flags & LIBFWSI_FILE_ATTRIBUTE_FLAG_VIRTUAL ) != 0 )
	{
		fprintf(
		 notify_stream,
		 "\t\t\tIs virtual (FILE_ATTRIBUTE_VIRTUAL)\n" );
	}
}

/* Prints the extension block to the notify stream
 * Returns 1 if successful or -1 on error
 */
int shell_items_extension_block_fprint(
     libfwsi_extension_block_t *extension_block,
     int extension_block_index,
     FILE *notify_stream,
     libcerror_error_t **error )
{
	static char *function = "shell_items_extension_block_fprint";
	uint32_t signature    = 0;

	fprintf(
	 notify_stream,
	 "\tExtension block: %d\n",
	 extension_block_index );

	if( libfwsi_extension_block_get_signature(
	     extension_block,
	     &signature,
	     error ) != 1 )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_GET_FAILED,
		 "%s: unable to retrieve signature.",
		 function );

		return( -1 );
	}
	fprintf(
	 notify_stream,
	 "\t\tSignature\t\t: 0x%08" PRIx32 "",
	 signature );

	switch( signature )
	{
		case 0xbeef0004UL:
			fprintf(
			 notify_stream,
			 " (File entry extension)" );
			break;

		default:
			break;
	}
	fprintf(
	 notify_stream,
	 "\n" );

	switch( signature )
	{
		case 0xbeef0004UL:
			if( shell_items_file_entry_extension_fprint(
			     extension_block,
			     notify_stream,
			     error ) == -1 )
			{
				libcerror_error_set(
				 error,
				 LIBCERROR_ERROR_DOMAIN_RUNTIME,
				 LIBCERROR_RUNTIME_ERROR_PRINT_FAILED,
				 "%s: unable to print file entry extension block.",
				 function );

				return( -1 );
			}
			break;

		default:
			break;
	}
	return( 1 );
}

/* Prints the file entry extension to the notify stream
 * Returns 1 if successful or -1 on error
 */
int shell_items_file_entry_extension_fprint(
     libfwsi_extension_block_t *extension_block,
     FILE *notify_stream,
     libcerror_error_t **error )
{
	system_character_t date_time_string[ 48 ];

	libfdatetime_fat_date_time_t *fat_date_time = NULL;
	system_character_t *value_string            = NULL;
	static char *function                       = "shell_items_file_entry_extension_fprint";
	size_t value_string_size                    = 0;
	uint64_t value_64bit                        = 0;
	uint32_t value_32bit                        = 0;
	int result                                  = 0;

#if defined( HAVE_WIDE_SYSTEM_CHARACTER )
	result = libfwsi_file_entry_extension_get_utf16_long_name_size(
		  extension_block,
		  &value_string_size,
		  error );
#else
	result = libfwsi_file_entry_extension_get_utf8_long_name_size(
		  extension_block,
		  &value_string_size,
		  error );
#endif
	if( result == -1 )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_GET_FAILED,
		 "%s: unable to retrieve long name size.",
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
		result = libfwsi_file_entry_extension_get_utf16_long_name(
			  extension_block,
			  (uint16_t *) value_string,
			  value_string_size,
			  error );
#else
		result = libfwsi_file_entry_extension_get_utf8_long_name(
			  extension_block,
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
			 "%s: unable to retrieve long name.",
			 function );

			goto on_error;
		}
		fprintf(
		 notify_stream,
		 "\t\tLong name\t\t: %" PRIs_SYSTEM "\n",
		 value_string );

		memory_free(
		 value_string );

		value_string = NULL;
	}
#if defined( HAVE_WIDE_SYSTEM_CHARACTER )
	result = libfwsi_file_entry_extension_get_utf16_localized_name_size(
		  extension_block,
		  &value_string_size,
		  error );
#else
	result = libfwsi_file_entry_extension_get_utf8_localized_name_size(
		  extension_block,
		  &value_string_size,
		  error );
#endif
	if( result == -1 )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_GET_FAILED,
		 "%s: unable to retrieve localized name size.",
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
		result = libfwsi_file_entry_extension_get_utf16_localized_name(
			  extension_block,
			  (uint16_t *) value_string,
			  value_string_size,
			  error );
#else
		result = libfwsi_file_entry_extension_get_utf8_localized_name(
			  extension_block,
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
			 "%s: unable to retrieve localized name.",
			 function );

			goto on_error;
		}
		fprintf(
		 notify_stream,
		 "\t\tLocalized name\t\t: %" PRIs_SYSTEM "\n",
		 value_string );

		memory_free(
		 value_string );

		value_string = NULL;
	}
	if( libfdatetime_fat_date_time_initialize(
	     &fat_date_time,
	     error ) != 1 )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_INITIALIZE_FAILED,
		 "%s: unable to create FAT date time.",
		 function );

		goto on_error;
	}
	if( libfwsi_file_entry_extension_get_creation_time(
	     extension_block,
	     &value_32bit,
	     error ) != 1 )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_GET_FAILED,
		 "%s: unable to retrieve creation time.",
		 function );

		goto on_error;
	}
	if( value_32bit != 0 )
	{
		if( libfdatetime_fat_date_time_copy_from_32bit(
		     fat_date_time,
		     value_32bit,
		     error ) != 1 )
		{
			libcerror_error_set(
			 error,
			 LIBCERROR_ERROR_DOMAIN_RUNTIME,
			 LIBCERROR_RUNTIME_ERROR_COPY_FAILED,
			 "%s: unable to copy FAT date time from 32-bit value.",
			 function );

			goto on_error;
		}
#if defined( HAVE_WIDE_SYSTEM_CHARACTER )
		result = libfdatetime_fat_date_time_copy_to_utf16_string(
			  fat_date_time,
			  (uint16_t *) date_time_string,
			  48,
			  LIBFDATETIME_STRING_FORMAT_TYPE_CTIME | LIBFDATETIME_STRING_FORMAT_FLAG_DATE_TIME,
			  error );
#else
		result = libfdatetime_fat_date_time_copy_to_utf8_string(
			  fat_date_time,
			  (uint8_t *) date_time_string,
			  48,
			  LIBFDATETIME_STRING_FORMAT_TYPE_CTIME | LIBFDATETIME_STRING_FORMAT_FLAG_DATE_TIME,
			  error );
#endif
		if( result != 1 )
		{
			libcerror_error_set(
			 error,
			 LIBCERROR_ERROR_DOMAIN_RUNTIME,
			 LIBCERROR_RUNTIME_ERROR_COPY_FAILED,
			 "%s: unable to copy FAT date time to string.",
			 function );

			goto on_error;
		}
		fprintf(
		 notify_stream,
		 "\t\tCreation time\t\t: %" PRIs_SYSTEM "\n",
		 date_time_string );
	}
	else
	{
		fprintf(
		 notify_stream,
		 "\t\tCreation time\t\t: Not set (0)\n" );
	}
	if( libfwsi_file_entry_extension_get_access_time(
	     extension_block,
	     &value_32bit,
	     error ) != 1 )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_GET_FAILED,
		 "%s: unable to retrieve access time.",
		 function );

		goto on_error;
	}
	if( value_32bit != 0 )
	{
		if( libfdatetime_fat_date_time_copy_from_32bit(
		     fat_date_time,
		     value_32bit,
		     error ) != 1 )
		{
			libcerror_error_set(
			 error,
			 LIBCERROR_ERROR_DOMAIN_RUNTIME,
			 LIBCERROR_RUNTIME_ERROR_COPY_FAILED,
			 "%s: unable to copy FAT date time from 32-bit value.",
			 function );

			goto on_error;
		}
#if defined( HAVE_WIDE_SYSTEM_CHARACTER )
		result = libfdatetime_fat_date_time_copy_to_utf16_string(
			  fat_date_time,
			  (uint16_t *) date_time_string,
			  48,
			  LIBFDATETIME_STRING_FORMAT_TYPE_CTIME | LIBFDATETIME_STRING_FORMAT_FLAG_DATE_TIME,
			  error );
#else
		result = libfdatetime_fat_date_time_copy_to_utf8_string(
			  fat_date_time,
			  (uint8_t *) date_time_string,
			  48,
			  LIBFDATETIME_STRING_FORMAT_TYPE_CTIME | LIBFDATETIME_STRING_FORMAT_FLAG_DATE_TIME,
			  error );
#endif
		if( result != 1 )
		{
			libcerror_error_set(
			 error,
			 LIBCERROR_ERROR_DOMAIN_RUNTIME,
			 LIBCERROR_RUNTIME_ERROR_COPY_FAILED,
			 "%s: unable to copy FAT date time to string.",
			 function );

			goto on_error;
		}
		fprintf(
		 notify_stream,
		 "\t\tAccess time\t\t: %" PRIs_SYSTEM "\n",
		 date_time_string );
	}
	else
	{
		fprintf(
		 notify_stream,
		 "\t\tAccess time\t\t: Not set (0)\n" );
	}
	if( libfdatetime_fat_date_time_free(
	     &fat_date_time,
	     error ) != 1 )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_FINALIZE_FAILED,
		 "%s: unable to free FAT date time.",
		 function );

		goto on_error;
	}
	result = libfwsi_file_entry_extension_get_file_reference(
	          extension_block,
	          &value_64bit,
	          error );

	if( result == -1 )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_GET_FAILED,
		 "%s: unable to retrieve file reference.",
		 function );

		goto on_error;
	}
	else if( result != 0 )
	{
		fprintf(
		 notify_stream,
		 "\t\tNTFS file reference\t: MFT entry: %" PRIu64 ", sequence: %" PRIu64 "\n",
		 value_64bit & 0xffffffffffffUL,
		 value_64bit >> 48 );
	}
	return( 1 );

on_error:
	if( fat_date_time != NULL )
	{
		libfdatetime_fat_date_time_free(
		 &fat_date_time,
		 NULL );
	}
	if( value_string != NULL )
	{
		memory_free(
		 value_string );
	}
	return( -1 );
}

/* Prints the shell item to the notify stream
 * Returns 1 if successful or -1 on error
 */
int shell_items_item_fprint(
     libfwsi_item_t *shell_item,
     int shell_item_index,
     FILE *notify_stream,
     libcerror_error_t **error )
{
	libfwsi_extension_block_t *extension_block = NULL;
	static char *function                      = "shell_items_item_fprint";
	uint32_t signature                         = 0;
	uint8_t class_type                         = 0;
	int extension_block_index                  = 0;
	int item_type                              = 0;
	int number_of_extension_blocks             = 0;

	if( shell_item_index == 0 )
	{
		fprintf(
		 notify_stream,
		 "\tShell item\n" );
	}
	else
	{
		fprintf(
		 notify_stream,
		 "\tShell item: %d\n",
		 shell_item_index );
	}
	if( libfwsi_item_get_type(
	     shell_item,
	     &item_type,
	     error ) != 1 )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_GET_FAILED,
		 "%s: unable to retrieve item type.",
		 function );

		goto on_error;
	}
	if( libfwsi_item_get_class_type(
	     shell_item,
	     &class_type,
	     error ) != 1 )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_GET_FAILED,
		 "%s: unable to retrieve class type.",
		 function );

		goto on_error;
	}
	if( libfwsi_item_get_signature(
	     shell_item,
	     &signature,
	     error ) != 1 )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_GET_FAILED,
		 "%s: unable to retrieve signature.",
		 function );

		goto on_error;
	}
	fprintf(
	 notify_stream,
	 "\t\tItem type\t\t: " );

	switch( item_type )
	{
		case LIBFWSI_ITEM_TYPE_CDBURN:
			fprintf(
			 notify_stream,
			 "CD burn" );
			break;

		case LIBFWSI_ITEM_TYPE_COMPRESSED_FOLDER:
			fprintf(
			 notify_stream,
			 "Compressed folder" );
			break;

		case LIBFWSI_ITEM_TYPE_CONTROL_PANEL:
			fprintf(
			 notify_stream,
			 "Control panel" );
			break;

		case LIBFWSI_ITEM_TYPE_CONTROL_PANEL_CATEGORY:
			fprintf(
			 notify_stream,
			 "Control panel category" );
			break;

		case LIBFWSI_ITEM_TYPE_CONTROL_PANEL_CPL_FILE:
			fprintf(
			 notify_stream,
			 "Control panel CPL file" );
			break;

		case LIBFWSI_ITEM_TYPE_DELEGATE:
			fprintf(
			 notify_stream,
			 "Delegate" );
			break;

		case LIBFWSI_ITEM_TYPE_FILE_ENTRY:
			fprintf(
			 notify_stream,
			 "File entry" );
			break;

		case LIBFWSI_ITEM_TYPE_NETWORK_LOCATION:
			fprintf(
			 notify_stream,
			 "Network location" );
			break;

		case LIBFWSI_ITEM_TYPE_GAME_FOLDER:
			fprintf(
			 notify_stream,
			 "Game folder" );
			break;

		case LIBFWSI_ITEM_TYPE_MTP_FILE_ENTRY:
			fprintf(
			 notify_stream,
			 "MTP file entry" );
			break;

		case LIBFWSI_ITEM_TYPE_MTP_VOLUME:
			fprintf(
			 notify_stream,
			 "MTP volume" );
			break;

		case LIBFWSI_ITEM_TYPE_ROOT_FOLDER:
			fprintf(
			 notify_stream,
			 "Root folder" );
			break;

		case LIBFWSI_ITEM_TYPE_URI:
			fprintf(
			 notify_stream,
			 "URI" );
			break;

		case LIBFWSI_ITEM_TYPE_USERS_PROPERTY_VIEW:
			fprintf(
			 notify_stream,
			 "Users property view" );
			break;

		case LIBFWSI_ITEM_TYPE_VOLUME:
			fprintf(
			 notify_stream,
			 "Volume" );
			break;

		case LIBFWSI_ITEM_TYPE_UNKNOWN_0x74:
			fprintf(
			 notify_stream,
			 "Unknown 0x74" );
			break;

		case LIBFWSI_ITEM_TYPE_UNKNOWN:
		default:
			fprintf(
			 notify_stream,
			 "Unknown" );
			break;
	}
	fprintf(
	 notify_stream,
	 "\n" );

	if( class_type != 0 )
	{
		fprintf(
		 notify_stream,
		 "\t\tClass type indicator\t: 0x%02" PRIx8 "",
		 class_type );

		switch( item_type )
		{
			case LIBFWSI_ITEM_TYPE_FILE_ENTRY:
				if( class_type == 0x30 )
				{
					fprintf(
					 notify_stream,
					 " (File entry)" );
				}
				else if( ( class_type & 0x01 ) != 0 )
				{
					fprintf(
					 notify_stream,
					 " (File entry: Directory)" );
				}
				else
				{
					fprintf(
					 notify_stream,
					 " (File entry: File)" );
				}
				break;

			case LIBFWSI_ITEM_TYPE_NETWORK_LOCATION:
				fprintf(
				 notify_stream,
				 " (Network location)" );
				break;

			case LIBFWSI_ITEM_TYPE_ROOT_FOLDER:
				fprintf(
				 notify_stream,
				 " (Root folder)" );
				break;

			case LIBFWSI_ITEM_TYPE_URI:
				fprintf(
				 notify_stream,
				 " (URI)" );
				break;

			case LIBFWSI_ITEM_TYPE_VOLUME:
				fprintf(
				 notify_stream,
				 " (Volume)" );
				break;

			default:
				break;
		}
		fprintf(
		 notify_stream,
		 "\n" );
	}
	switch( item_type )
	{
		case LIBFWSI_ITEM_TYPE_FILE_ENTRY:
			if( shell_items_file_entry_fprint(
			     shell_item,
			     notify_stream,
			     error ) == -1 )
			{
				libcerror_error_set(
				 error,
				 LIBCERROR_ERROR_DOMAIN_RUNTIME,
				 LIBCERROR_RUNTIME_ERROR_PRINT_FAILED,
				 "%s: unable to print file entry shell item.",
				 function );

				goto on_error;
			}
			break;

		case LIBFWSI_ITEM_TYPE_NETWORK_LOCATION:
			if( shell_items_network_location_fprint(
			     shell_item,
			     notify_stream,
			     error ) == -1 )
			{
				libcerror_error_set(
				 error,
				 LIBCERROR_ERROR_DOMAIN_RUNTIME,
				 LIBCERROR_RUNTIME_ERROR_PRINT_FAILED,
				 "%s: unable to print network location shell item.",
				 function );

				goto on_error;
			}
			break;

		case LIBFWSI_ITEM_TYPE_ROOT_FOLDER:
			if( shell_items_root_folder_fprint(
			     shell_item,
			     notify_stream,
			     error ) == -1 )
			{
				libcerror_error_set(
				 error,
				 LIBCERROR_ERROR_DOMAIN_RUNTIME,
				 LIBCERROR_RUNTIME_ERROR_PRINT_FAILED,
				 "%s: unable to print root folder shell item.",
				 function );

				goto on_error;
			}
			break;

		case LIBFWSI_ITEM_TYPE_VOLUME:
			if( shell_items_volume_fprint(
			     shell_item,
			     notify_stream,
			     error ) == -1 )
			{
				libcerror_error_set(
				 error,
				 LIBCERROR_ERROR_DOMAIN_RUNTIME,
				 LIBCERROR_RUNTIME_ERROR_PRINT_FAILED,
				 "%s: unable to print volume shell item.",
				 function );

				goto on_error;
			}
			break;

		default:
			break;
	}
	if( libfwsi_item_get_number_of_extension_blocks(
	     shell_item,
	     &number_of_extension_blocks,
	     error ) != 1 )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_GET_FAILED,
		 "%s: unable to retrieve number of extension blocks.",
		 function );

		goto on_error;
	}
#ifdef TODO
	fprintf(
	 notify_stream,
	 "\t\tNumber of extension blocks\t: %d\n",
	 number_of_extension_blocks );
#endif

	for( extension_block_index = 0;
	     extension_block_index < number_of_extension_blocks;
	     extension_block_index++ )
	{
		if( libfwsi_item_get_extension_block(
		     shell_item,
		     extension_block_index,
		     &extension_block,
		     error ) != 1 )
		{
			libcerror_error_set(
			 error,
			 LIBCERROR_ERROR_DOMAIN_RUNTIME,
			 LIBCERROR_RUNTIME_ERROR_GET_FAILED,
			 "%s: unable to retrieve extension block: %d.",
			 function,
			 extension_block_index );

			goto on_error;
		}
		if( shell_items_extension_block_fprint(
		     extension_block,
		     extension_block_index + 1,
		     notify_stream,
		     error ) == -1 )
		{
			libcerror_error_set(
			 error,
			 LIBCERROR_ERROR_DOMAIN_RUNTIME,
			 LIBCERROR_RUNTIME_ERROR_PRINT_FAILED,
			 "%s: unable to print extension block: %d.",
			 function,
			 extension_block_index );

			goto on_error;
		}
		if( libfwsi_extension_block_free(
		     &extension_block,
		     error ) != 1 )
		{
			libcerror_error_set(
			 error,
			 LIBCERROR_ERROR_DOMAIN_RUNTIME,
			 LIBCERROR_RUNTIME_ERROR_FINALIZE_FAILED,
			 "%s: unable to free extension block: %d.",
			 function,
			 extension_block_index );

			goto on_error;
		}
	}
	fprintf(
	 notify_stream,
	 "\n" );

	return( 1 );

on_error:
	if( extension_block != NULL )
	{
		libfwsi_extension_block_free(
		 &extension_block,
		 NULL );
	}
	return( -1 );
}

/* Prints the root folder shell item to the notify stream
 * Returns 1 if successful or -1 on error
 */
int shell_items_root_folder_fprint(
     libfwsi_item_t *shell_item,
     FILE *notify_stream,
     libcerror_error_t **error )
{
	uint8_t guid_data[ 16 ];

	system_character_t guid_string[ 48 ];

	libfguid_identifier_t *guid = NULL;
	static char *function       = "shell_items_root_folder_fprint";
	int result                  = 0;

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
	if( libfwsi_root_folder_get_shell_folder_identifier(
	     shell_item,
	     guid_data,
	     16,
	     error ) != 1 )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_GET_FAILED,
		 "%s: unable to retrieve shell folder identifier.",
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
	 "\t\tShell folder identifier\t: %" PRIs_SYSTEM "\n",
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
	 notify_stream,
	 "\t\tShell folder name\t: %s\n",
	 libfwsi_shell_folder_identifier_get_name(
	  guid_data ) );

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

/* Prints the volume shell item to the notify stream
 * Returns 1 if successful or -1 on error
 */
int shell_items_volume_fprint(
     libfwsi_item_t *shell_item,
     FILE *notify_stream,
     libcerror_error_t **error )
{
	system_character_t *value_string = NULL;
	static char *function            = "shell_items_volume_fprint";
	size_t value_string_size         = 0;
	int result                       = 0;

#if defined( HAVE_WIDE_SYSTEM_CHARACTER )
	result = libfwsi_volume_get_utf16_name_size(
		  shell_item,
		  &value_string_size,
		  error );
#else
	result = libfwsi_volume_get_utf8_name_size(
		  shell_item,
		  &value_string_size,
		  error );
#endif
	if( result != 1 )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_GET_FAILED,
		 "%s: unable to retrieve name size.",
		 function );

		goto on_error;
	}
	if( value_string_size > 0 )
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
		result = libfwsi_volume_get_utf16_name(
			  shell_item,
			  (uint16_t *) value_string,
			  value_string_size,
			  error );
#else
		result = libfwsi_volume_get_utf8_name(
			  shell_item,
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
			 "%s: unable to retrieve name.",
			 function );

			goto on_error;
		}
		fprintf(
		 notify_stream,
		 "\t\tVolume name\t\t: %" PRIs_SYSTEM "\n",
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

/* Prints the file entry shell item to the notify stream
 * Returns 1 if successful or -1 on error
 */
int shell_items_file_entry_fprint(
     libfwsi_item_t *shell_item,
     FILE *notify_stream,
     libcerror_error_t **error )
{
	system_character_t date_time_string[ 48 ];

	libfdatetime_fat_date_time_t *fat_date_time = NULL;
	system_character_t *value_string            = NULL;
	static char *function                       = "shell_items_file_entry_fprint";
	size_t value_string_size                    = 0;
	uint32_t value_32bit                        = 0;
	int result                                  = 0;

#if defined( HAVE_WIDE_SYSTEM_CHARACTER )
	result = libfwsi_file_entry_get_utf16_name_size(
		  shell_item,
		  &value_string_size,
		  error );
#else
	result = libfwsi_file_entry_get_utf8_name_size(
		  shell_item,
		  &value_string_size,
		  error );
#endif
	if( result != 1 )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_GET_FAILED,
		 "%s: unable to retrieve name size.",
		 function );

		goto on_error;
	}
	if( value_string_size > 0 )
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
		result = libfwsi_file_entry_get_utf16_name(
			  shell_item,
			  (uint16_t *) value_string,
			  value_string_size,
			  error );
#else
		result = libfwsi_file_entry_get_utf8_name(
			  shell_item,
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
			 "%s: unable to retrieve name.",
			 function );

			goto on_error;
		}
		fprintf(
		 notify_stream,
		 "\t\tName\t\t\t: %" PRIs_SYSTEM "\n",
		 value_string );

		memory_free(
		 value_string );

		value_string = NULL;
	}
	if( libfdatetime_fat_date_time_initialize(
	     &fat_date_time,
	     error ) != 1 )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_INITIALIZE_FAILED,
		 "%s: unable to create FAT date time.",
		 function );

		goto on_error;
	}
	if( libfwsi_file_entry_get_modification_time(
	     shell_item,
	     &value_32bit,
	     error ) != 1 )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_GET_FAILED,
		 "%s: unable to retrieve modification time.",
		 function );

		goto on_error;
	}
	if( value_32bit != 0 )
	{
		if( libfdatetime_fat_date_time_copy_from_32bit(
		     fat_date_time,
		     value_32bit,
		     error ) != 1 )
		{
			libcerror_error_set(
			 error,
			 LIBCERROR_ERROR_DOMAIN_RUNTIME,
			 LIBCERROR_RUNTIME_ERROR_COPY_FAILED,
			 "%s: unable to copy FAT date time from 32-bit value.",
			 function );

			goto on_error;
		}
#if defined( HAVE_WIDE_SYSTEM_CHARACTER )
		result = libfdatetime_fat_date_time_copy_to_utf16_string(
			  fat_date_time,
			  (uint16_t *) date_time_string,
			  48,
			  LIBFDATETIME_STRING_FORMAT_TYPE_CTIME | LIBFDATETIME_STRING_FORMAT_FLAG_DATE_TIME,
			  error );
#else
		result = libfdatetime_fat_date_time_copy_to_utf8_string(
			  fat_date_time,
			  (uint8_t *) date_time_string,
			  48,
			  LIBFDATETIME_STRING_FORMAT_TYPE_CTIME | LIBFDATETIME_STRING_FORMAT_FLAG_DATE_TIME,
			  error );
#endif
		if( result != 1 )
		{
			libcerror_error_set(
			 error,
			 LIBCERROR_ERROR_DOMAIN_RUNTIME,
			 LIBCERROR_RUNTIME_ERROR_COPY_FAILED,
			 "%s: unable to copy FAT date time to string.",
			 function );

			goto on_error;
		}
		fprintf(
		 notify_stream,
		 "\t\tModification time\t: %" PRIs_SYSTEM "\n",
		 date_time_string );
	}
	else
	{
		fprintf(
		 notify_stream,
		 "\t\tModification time\t: Not set (0)\n" );
	}
	if( libfdatetime_fat_date_time_free(
	     &fat_date_time,
	     error ) != 1 )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_FINALIZE_FAILED,
		 "%s: unable to free FAT date time.",
		 function );

		goto on_error;
	}
	if( libfwsi_file_entry_get_file_attribute_flags(
	     shell_item,
	     &value_32bit,
	     error ) != 1 )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_GET_FAILED,
		 "%s: unable to retrieve file entry file attribute flags.",
		 function );

		goto on_error;
	}
	fprintf(
	 notify_stream,
	 "\t\tFile attribute flags\t: 0x%08" PRIx32 "\n",
	 value_32bit );
	shell_items_file_attribute_flags_fprint(
	 value_32bit,
	 notify_stream );

	return( 1 );

on_error:
	if( fat_date_time != NULL )
	{
		libfdatetime_fat_date_time_free(
		 &fat_date_time,
		 NULL );
	}
	if( value_string != NULL )
	{
		memory_free(
		 value_string );
	}
	return( -1 );
}

/* Prints the network location shell item to the notify stream
 * Returns 1 if successful or -1 on error
 */
int shell_items_network_location_fprint(
     libfwsi_item_t *shell_item,
     FILE *notify_stream,
     libcerror_error_t **error )
{
	system_character_t *value_string = NULL;
	static char *function            = "shell_items_network_location_fprint";
	size_t value_string_size         = 0;
	int result                       = 0;

#if defined( HAVE_WIDE_SYSTEM_CHARACTER )
	result = libfwsi_network_location_get_utf16_location_size(
		  shell_item,
		  &value_string_size,
		  error );
#else
	result = libfwsi_network_location_get_utf8_location_size(
		  shell_item,
		  &value_string_size,
		  error );
#endif
	if( result != 1 )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_GET_FAILED,
		 "%s: unable to retrieve location size.",
		 function );

		goto on_error;
	}
	if( value_string_size > 0 )
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
		result = libfwsi_network_location_get_utf16_location(
			  shell_item,
			  (uint16_t *) value_string,
			  value_string_size,
			  error );
#else
		result = libfwsi_network_location_get_utf8_location(
			  shell_item,
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
			 "%s: unable to retrieve location.",
			 function );

			goto on_error;
		}
		fprintf(
		 notify_stream,
		 "\t\tLocation\t\t: %" PRIs_SYSTEM "\n",
		 value_string );

		memory_free(
		 value_string );

		value_string = NULL;
	}
#if defined( HAVE_WIDE_SYSTEM_CHARACTER )
	result = libfwsi_network_location_get_utf16_description_size(
		  shell_item,
		  &value_string_size,
		  error );
#else
	result = libfwsi_network_location_get_utf8_description_size(
		  shell_item,
		  &value_string_size,
		  error );
#endif
	if( result == -1 )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_GET_FAILED,
		 "%s: unable to retrieve description size.",
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
		result = libfwsi_network_location_get_utf16_description(
			  shell_item,
			  (uint16_t *) value_string,
			  value_string_size,
			  error );
#else
		result = libfwsi_network_location_get_utf8_description(
			  shell_item,
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
		 notify_stream,
		 "\t\tDescription\t\t: %" PRIs_SYSTEM "\n",
		 value_string );

		memory_free(
		 value_string );

		value_string = NULL;
	}
#if defined( HAVE_WIDE_SYSTEM_CHARACTER )
	result = libfwsi_network_location_get_utf16_comments_size(
		  shell_item,
		  &value_string_size,
		  error );
#else
	result = libfwsi_network_location_get_utf8_comments_size(
		  shell_item,
		  &value_string_size,
		  error );
#endif
	if( result == -1 )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_GET_FAILED,
		 "%s: unable to retrieve comments size.",
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
		result = libfwsi_network_location_get_utf16_comments(
			  shell_item,
			  (uint16_t *) value_string,
			  value_string_size,
			  error );
#else
		result = libfwsi_network_location_get_utf8_comments(
			  shell_item,
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
			 "%s: unable to retrieve comments.",
			 function );

			goto on_error;
		}
		fprintf(
		 notify_stream,
		 "\t\tComments\t\t: %" PRIs_SYSTEM "\n",
		 value_string );

		memory_free(
		 value_string );

		value_string = NULL;
	}
	return( result );

on_error:
	if( value_string != NULL )
	{
		memory_free(
		 value_string );
	}
	return( -1 );
}

/* Prints the shell item list to the notify stream
 * Returns 1 if successful or -1 on error
 */
int shell_items_item_list_fprint(
     libfwsi_item_list_t *shell_item_list,
     FILE *notify_stream,
     libcerror_error_t **error )
{
	libfwsi_item_t *shell_item = NULL;
	static char *function      = "shell_items_item_list_fprint";
	int item_index             = 0;
	int number_of_items        = 0;

	fprintf(
	 notify_stream,
	 "\tShell item list\n" );

	if( libfwsi_item_list_get_number_of_items(
	     shell_item_list,
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
	fprintf(
	 notify_stream,
	 "\t\tNumber of items\t\t: %d\n",
	 number_of_items );

	fprintf(
	 notify_stream,
	 "\n" );

	for( item_index = 0;
	     item_index < number_of_items;
	     item_index++ )
	{
		if( libfwsi_item_list_get_item(
		     shell_item_list,
		     item_index,
		     &shell_item,
		     error ) != 1 )
		{
			libcerror_error_set(
			 error,
			 LIBCERROR_ERROR_DOMAIN_RUNTIME,
			 LIBCERROR_RUNTIME_ERROR_GET_FAILED,
			 "%s: unable to retrieve shell item: %d.",
			 function,
			 item_index );

			goto on_error;
		}
		if( shell_items_item_fprint(
		     shell_item,
		     item_index + 1,
		     notify_stream,
		     error ) == -1 )
		{
			libcerror_error_set(
			 error,
			 LIBCERROR_ERROR_DOMAIN_RUNTIME,
			 LIBCERROR_RUNTIME_ERROR_PRINT_FAILED,
			 "%s: unable to print shell item: %d.",
			 function,
			 item_index );

			goto on_error;
		}
		if( libfwsi_item_free(
		     &shell_item,
		     error ) != 1 )
		{
			libcerror_error_set(
			 error,
			 LIBCERROR_ERROR_DOMAIN_RUNTIME,
			 LIBCERROR_RUNTIME_ERROR_FINALIZE_FAILED,
			 "%s: unable to free shell item: %d.",
			 function,
			 item_index );

			goto on_error;
		}
	}
	fprintf(
	 notify_stream,
	 "\n" );

	return( 1 );

on_error:
	if( shell_item != NULL )
	{
		libfwsi_item_free(
		 &shell_item,
		 NULL );
	}
	return( -1 );
}

