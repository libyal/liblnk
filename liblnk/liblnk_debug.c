/*
 * Debug functions
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
#include <memory.h>
#include <narrow_string.h>
#include <system_string.h>
#include <types.h>
#include <wide_string.h>

#include "liblnk_debug.h"
#include "liblnk_definitions.h"
#include "liblnk_libbfio.h"
#include "liblnk_libcerror.h"
#include "liblnk_libcnotify.h"
#include "liblnk_libfdatetime.h"
#include "liblnk_libfguid.h"
#include "liblnk_libuna.h"

#if defined( HAVE_DEBUG_OUTPUT )

/* Prints the data flags
 */
void liblnk_debug_print_data_flags(
      uint32_t data_flags )
{
	if( ( data_flags & LIBLNK_DATA_FLAG_HAS_LINK_TARGET_IDENTIFIER ) != 0 )
	{
		libcnotify_printf(
		 "\tContains link target identifier (HasTargetIDList)\n" );
	}
	if( ( data_flags & LIBLNK_DATA_FLAG_HAS_LOCATION_INFORMATION ) != 0 )
	{
		libcnotify_printf(
		 "\tContains location information (HasLinkInfo)\n" );
	}
	if( ( data_flags & LIBLNK_DATA_FLAG_HAS_DESCRIPTION_STRING ) != 0 )
	{
		libcnotify_printf(
		 "\tContains description string (HasName)\n" );
	}
	if( ( data_flags & LIBLNK_DATA_FLAG_HAS_RELATIVE_PATH_STRING ) != 0 )
	{
		libcnotify_printf(
		 "\tContains relative path string (HasRelativePath)\n" );
	}
	if( ( data_flags & LIBLNK_DATA_FLAG_HAS_WORKING_DIRECTORY_STRING ) != 0 )
	{
		libcnotify_printf(
		 "\tContains working directory string (HasWorkingDir)\n" );
	}
	if( ( data_flags & LIBLNK_DATA_FLAG_HAS_COMMAND_LINE_ARGUMENTS_STRING ) != 0 )
	{
		libcnotify_printf(
		 "\tContains command line arguments string (HasArguments)\n" );
	}
	if( ( data_flags & LIBLNK_DATA_FLAG_HAS_ICON_LOCATION_STRING ) != 0 )
	{
		libcnotify_printf(
		 "\tContains icon location string (HasIconLocation)\n" );
	}
	if( ( data_flags & LIBLNK_DATA_FLAG_IS_UNICODE ) != 0 )
	{
		libcnotify_printf(
		 "\tString are in Unicode (IsUnicode)\n" );
	}
	if( ( data_flags & LIBLNK_DATA_FLAG_FORCE_NO_LOCATION_INFORMATION ) != 0 )
	{
		libcnotify_printf(
		 "\tIgnore the location information (ForceNoLinkInfo)\n" );
	}
	if( ( data_flags & LIBLNK_DATA_FLAG_HAS_ENVIRONMENT_VARIABLES_LOCATION_BLOCK ) != 0 )
	{
		libcnotify_printf(
		 "\tContains environment variables location block (HasExpString)\n" );
	}
	if( ( data_flags & LIBLNK_DATA_FLAG_RUN_IN_SEPARATE_PROCESS ) != 0 )
	{
		libcnotify_printf(
		 "\tRun in separate process (RunInSeparateProcess)\n" );
	}

	if( ( data_flags & 0x00000800UL ) != 0 )
	{
		libcnotify_printf(
		 "\t0x00000800 (reserved)\n" );
	}

	if( ( data_flags & LIBLNK_DATA_FLAG_HAS_DARWIN_IDENTIFIER ) != 0 )
	{
		libcnotify_printf(
		 "\tContains Darwin properites location block (HasDarwinID)\n" );
	}
	if( ( data_flags & LIBLNK_DATA_FLAG_RUN_AS_USER ) != 0 )
	{
		libcnotify_printf(
		 "\tRun as user (RunAsUser)\n" );
	}
	if( ( data_flags & LIBLNK_DATA_FLAG_HAS_ICON_LOCATION_BLOCK ) != 0 )
	{
		libcnotify_printf(
		 "\tContains icon location block (HasExpIcon)\n" );
	}
	if( ( data_flags & LIBLNK_DATA_FLAG_NO_PIDL_ALIAS ) != 0 )
	{
		libcnotify_printf(
		 "\t(NoPidlAlias)\n" );
	}

	if( ( data_flags & LIBLNK_DATA_FLAG_RUN_WITH_SHIM_LAYER ) != 0 )
	{
		libcnotify_printf(
		 "\tContains shim layer properties block (RunWithShimLayer)\n" );
	}
	if( ( data_flags & LIBLNK_DATA_FLAG_NO_DISTRIBUTED_LINK_TRACKING_DATA_BLOCK ) != 0 )
	{
		libcnotify_printf(
		 "\tDoes not contain distributed link tracking data block (ForceNoLinkTrack)\n" );
	}
	if( ( data_flags & LIBLNK_DATA_FLAG_HAS_METADATA_PROPERTY_STORE_DATA_BLOCK ) != 0 )
	{
		libcnotify_printf(
		 "\tContains metadata property store block (HasTargetMetadata)\n" );
	}

	if( ( data_flags & 0x00100000UL ) != 0 )
	{
		libcnotify_printf(
		 "\t0x00100000 (DisableLinkPathTracking)\n" );
	}
	if( ( data_flags & 0x00200000UL ) != 0 )
	{
		libcnotify_printf(
		 "\t0x00200000 (DisableKnownFolderTracking)\n" );
	}
	if( ( data_flags & 0x00400000UL ) != 0 )
	{
		libcnotify_printf(
		 "\t0x00400000 (AllowLinkToLink)\n" );
	}
	if( ( data_flags & 0x00800000UL ) != 0 )
	{
		libcnotify_printf(
		 "\t0x00800000 (UnaliasOnSave)\n" );
	}
	if( ( data_flags & 0x01000000UL ) != 0 )
	{
		libcnotify_printf(
		 "\t0x01000000 (PreferEnvironmentPath)\n" );
	}
	if( ( data_flags & 0x02000000UL ) != 0 )
	{
		libcnotify_printf(
		 "\t0x02000000 (KeepLocalIDListForUNCTarget)\n" );
	}
}

/* Prints the file attribute flags
 */
void liblnk_debug_print_file_attribute_flags(
      uint32_t file_attribute_flags )
{
	if( ( file_attribute_flags & LIBLNK_FILE_ATTRIBUTE_FLAG_READ_ONLY ) != 0 )
	{
		libcnotify_printf(
		 "\tIs read-only (FILE_ATTRIBUTE_READ_ONLY)\n" );
	}
	if( ( file_attribute_flags & LIBLNK_FILE_ATTRIBUTE_FLAG_HIDDEN ) != 0 )
	{
		libcnotify_printf(
		 "\tIs hidden (FILE_ATTRIBUTE_HIDDEN)\n" );
	}
	if( ( file_attribute_flags & LIBLNK_FILE_ATTRIBUTE_FLAG_SYSTEM ) != 0 )
	{
		libcnotify_printf(
		 "\tIs system (FILE_ATTRIBUTE_SYSTEM)\n" );
	}

	if( ( file_attribute_flags & LIBLNK_FILE_ATTRIBUTE_FLAG_DIRECTORY ) != 0 )
	{
		libcnotify_printf(
		 "\tIs directory (FILE_ATTRIBUTE_DIRECTORY)\n" );
	}
	if( ( file_attribute_flags & LIBLNK_FILE_ATTRIBUTE_FLAG_ARCHIVE ) != 0 )
	{
		libcnotify_printf(
		 "\tShould be archived (FILE_ATTRIBUTE_ARCHIVE)\n" );
	}
	if( ( file_attribute_flags & LIBLNK_FILE_ATTRIBUTE_FLAG_DEVICE ) != 0 )
	{
		libcnotify_printf(
		 "\tIs device (FILE_ATTRIBUTE_DEVICE)\n" );
	}
	if( ( file_attribute_flags & LIBLNK_FILE_ATTRIBUTE_FLAG_NORMAL ) != 0 )
	{
		libcnotify_printf(
		 "\tIs normal (FILE_ATTRIBUTE_NORMAL)\n" );
	}
	if( ( file_attribute_flags & LIBLNK_FILE_ATTRIBUTE_FLAG_TEMPORARY ) != 0 )
	{
		libcnotify_printf(
		 "\tIs temporary (FILE_ATTRIBUTE_TEMPORARY)\n" );
	}
	if( ( file_attribute_flags & LIBLNK_FILE_ATTRIBUTE_FLAG_SPARSE_FILE ) != 0 )
	{
		libcnotify_printf(
		 "\tIs a sparse file (FILE_ATTRIBUTE_SPARSE_FILE)\n" );
	}
	if( ( file_attribute_flags & LIBLNK_FILE_ATTRIBUTE_FLAG_REPARSE_POINT ) != 0 )
	{
		libcnotify_printf(
		 "\tIs a reparse point or symbolic link (FILE_ATTRIBUTE_FLAG_REPARSE_POINT)\n" );
	}
	if( ( file_attribute_flags & LIBLNK_FILE_ATTRIBUTE_FLAG_COMPRESSED ) != 0 )
	{
		libcnotify_printf(
		 "\tIs compressed (FILE_ATTRIBUTE_COMPRESSED)\n" );
	}
	if( ( file_attribute_flags & LIBLNK_FILE_ATTRIBUTE_FLAG_OFFLINE ) != 0 )
	{
		libcnotify_printf(
		 "\tIs offline (FILE_ATTRIBUTE_OFFLINE)\n" );
	}
	if( ( file_attribute_flags & LIBLNK_FILE_ATTRIBUTE_FLAG_NOT_CONTENT_INDEXED ) != 0 )
	{
		libcnotify_printf(
		 "\tContent should not be indexed (FILE_ATTRIBUTE_NOT_CONTENT_INDEXED)\n" );
	}
	if( ( file_attribute_flags & LIBLNK_FILE_ATTRIBUTE_FLAG_ENCRYPTED ) != 0 )
	{
		libcnotify_printf(
		 "\tIs encrypted (FILE_ATTRIBUTE_ENCRYPTED)\n" );
	}

	if( ( file_attribute_flags & LIBLNK_FILE_ATTRIBUTE_FLAG_VIRTUAL ) != 0 )
	{
		libcnotify_printf(
		 "\tIs virtual (FILE_ATTRIBUTE_VIRTUAL)\n" );
	}
}

/* Prints the drive type
 */
const char *liblnk_debug_print_drive_type(
             uint32_t drive_type )
{
	switch( drive_type )
	{
		case LIBLNK_DRIVE_TYPE_UNKNOWN:
			return( "Unknown" );

		case LIBLNK_DRIVE_TYPE_NO_ROOT_DIR:
			return( "No root directory" );

		case LIBLNK_DRIVE_TYPE_REMOVABLE:
			return( "Removable" );

		case LIBLNK_DRIVE_TYPE_FIXED:
			return( "Fixed" );

		case LIBLNK_DRIVE_TYPE_REMOTE:
			return( "Remote" );

		case LIBLNK_DRIVE_TYPE_CDROM:
			return( "CDROM" );

		case LIBLNK_DRIVE_TYPE_RAMDISK:
			return( "RAM disk" );
	}
	return( "_UNKNOWN_" );
}

/* Prints the network provider type
 */
const char *liblnk_debug_print_network_provider_type(
             uint32_t network_provider_type )
{
	switch( network_provider_type )
	{
		case 0x001a0000:
			return( "WNNC_NET_AVID" );

		case 0x001b0000:
			return( "WNNC_NET_DOCUSPACE" );

		case 0x001c0000:
			return( "WNNC_NET_MANGOSOFT" );

		case 0x001d0000:
			return( "WNNC_NET_SERNET" );

		case 0x001e0000:
			return( "WNNC_NET_RIVERFRONT1" );

		case 0x001f0000:
			return( "WNNC_NET_RIVERFRONT2" );

		case 0x00200000:
			return( "WNNC_NET_DECORB" );

		case 0x00210000:
			return( "WNNC_NET_PROTSTOR" );

		case 0x00220000:
			return( "WNNC_NET_FJ_REDIR" );

		case 0x00230000:
			return( "WNNC_NET_DISTINCT" );

		case 0x00240000:
			return( "WNNC_NET_TWINS" );

		case 0x00250000:
			return( "WNNC_NET_RDR2SAMPLE" );

		case 0x00260000:
			return( "WNNC_NET_CSC" );

		case 0x00270000:
			return( "WNNC_NET_3IN1" );

		case 0x00290000:
			return( "WNNC_NET_EXTENDNET" );

		case 0x002a0000:
			return( "WNNC_NET_STAC" );

		case 0x002b0000:
			return( "WNNC_NET_FOXBAT" );

		case 0x002c0000:
			return( "WNNC_NET_YAHOO" );

		case 0x002d0000:
			return( "WNNC_NET_EXIFS" );

		case 0x002e0000:
			return( "WNNC_NET_DAV" );

		case 0x002f0000:
			return( "WNNC_NET_KNOWARE" );

		case 0x00300000:
			return( "WNNC_NET_OBJECT_DIRE" );

		case 0x00310000:
			return( "WNNC_NET_MASFAX" );

		case 0x00320000:
			return( "WNNC_NET_HOB_NFS" );

		case 0x00330000:
			return( "WNNC_NET_SHIVA" );

		case 0x00340000:
			return( "WNNC_NET_IBMAL" );

		case 0x00350000:
			return( "WNNC_NET_LOCK" );

		case 0x00360000:
			return( "WNNC_NET_TERMSRV" );

		case 0x00370000:
			return( "WNNC_NET_SRT" );

		case 0x00380000:
			return( "WNNC_NET_QUINCY" );

		case 0x00390000:
			return( "WNNC_NET_OPENAFS" );

		case 0x003a0000:
			return( "WNNC_NET_AVID1" );

		case 0x003b0000:
			return( "WNNC_NET_DFS" );

		case 0x003c0000:
			return( "WNNC_NET_KWNP" );

		case 0x003d0000:
			return( "WNNC_NET_ZENWORKS" );

		case 0x003e0000:
			return( "WNNC_NET_DRIVEONWEB" );

		case 0x003f0000:
			return( "WNNC_NET_VMWARE" );

		case 0x00400000:
			return( "WNNC_NET_RSFX" );

		case 0x00410000:
			return( "WNNC_NET_MFILES" );

		case 0x00420000:
			return( "WNNC_NET_MS_NFS" );

		case 0x00430000:
			return( "WNNC_NET_GOOGLE" );
	}
	return( "_UNKNOWN_" );
}

/* Prints a FILETIME value
 * Returns 1 if successful or -1 on error
 */
int liblnk_debug_print_filetime_value(
     const char *function_name,
     const char *value_name,
     const uint8_t *byte_stream,
     size_t byte_stream_size,
     int byte_order,
     uint32_t string_format_flags,
     libcerror_error_t **error )
{
	char date_time_string[ 32 ];

	libfdatetime_filetime_t *filetime = NULL;
	static char *function             = "liblnk_debug_print_filetime_value";

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
	if( libfdatetime_filetime_copy_from_byte_stream(
	     filetime,
	     byte_stream,
	     byte_stream_size,
	     byte_order,
	     error ) != 1 )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_COPY_FAILED,
		 "%s: unable to copy byte stream to FILETIME.",
		 function );

		goto on_error;
	}
	if( libfdatetime_filetime_copy_to_utf8_string(
	     filetime,
	     (uint8_t *) date_time_string,
	     32,
	     string_format_flags,
	     error ) != 1 )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_COPY_FAILED,
		 "%s: unable to copy FILETIME to string.",
		 function );

		goto on_error;
	}
	libcnotify_printf(
	 "%s: %s: %s UTC\n",
	 function_name,
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

/* Prints a GUID/UUID value
 * Returns 1 if successful or -1 on error
 */
int liblnk_debug_print_guid_value(
     const char *function_name,
     const char *value_name,
     const uint8_t *byte_stream,
     size_t byte_stream_size,
     int byte_order,
     uint32_t string_format_flags,
     libcerror_error_t **error )
{
        system_character_t guid_string[ 48 ];

        libfguid_identifier_t *guid = NULL;
	static char *function       = "liblnk_debug_print_guid_value";

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
	     byte_stream,
	     byte_stream_size,
	     byte_order,
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
	if( libfguid_identifier_copy_to_utf8_string(
	     guid,
	     (uint8_t *) guid_string,
	     48,
	     string_format_flags,
	     error ) != 1 )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_COPY_FAILED,
		 "%s: unable to copy GUID to string.",
		 function );

		goto on_error;
	}
	libcnotify_printf(
	 "%s: %s: %s\n",
	 function_name,
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

/* Prints a string value
 * Returns 1 if successful or -1 on error
 */
int liblnk_debug_print_string_value(
     const char *function_name,
     const char *value_name,
     const uint8_t *byte_stream,
     size_t byte_stream_size,
     int ascii_codepage,
     libcerror_error_t **error )
{
	system_character_t *string = NULL;
	static char *function      = "liblnk_debug_print_string_value";
	size_t string_size         = 0;
	int result                 = 0;

	if( ( byte_stream == NULL )
	 || ( byte_stream_size == 0 ) )
	{
		libcnotify_printf(
		 "%s: %s: \n",
		 function_name,
		 value_name );

		return( 1 );
	}
#if defined( HAVE_WIDE_SYSTEM_CHARACTER )
	result = libuna_utf16_string_size_from_byte_stream(
		  byte_stream,
		  byte_stream_size,
		  ascii_codepage,
		  &string_size,
		  error );
#else
	result = libuna_utf8_string_size_from_byte_stream(
		  byte_stream,
		  byte_stream_size,
		  ascii_codepage,
		  &string_size,
		  error );
#endif
	if( result != 1 )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_GET_FAILED,
		 "%s: unable to determine size of string.",
		 function );

		goto on_error;
	}
	if( ( string_size > (size_t) SSIZE_MAX )
	 || ( ( sizeof( system_character_t ) * string_size ) > (size_t) SSIZE_MAX ) )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_VALUE_EXCEEDS_MAXIMUM,
		 "%s: invalid string size value exceeds maximum.",
		 function );

		goto on_error;
	}
	string = system_string_allocate(
	          string_size );

	if( string == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_MEMORY,
		 LIBCERROR_MEMORY_ERROR_INSUFFICIENT,
		 "%s: unable to create string.",
		 function );

		goto on_error;
	}
#if defined( HAVE_WIDE_SYSTEM_CHARACTER )
	result = libuna_utf16_string_copy_from_byte_stream(
		  (libuna_utf16_character_t *) string,
		  string_size,
		  byte_stream,
		  byte_stream_size,
		  ascii_codepage,
		  error );
#else
	result = libuna_utf8_string_copy_from_byte_stream(
		  (libuna_utf8_character_t *) string,
		  string_size,
		  byte_stream,
		  byte_stream_size,
		  ascii_codepage,
		  error );
#endif
	if( result != 1 )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_SET_FAILED,
		 "%s: unable to set string.",
		 function );

		goto on_error;
	}
	libcnotify_printf(
	 "%s: %s: %s\n",
	 function_name,
	 value_name,
	 string );

	memory_free(
	 string );

	return( 1 );

on_error:
	if( string != NULL )
	{
		memory_free(
		 string );
	}
	return( -1 );
}

/* Prints an UTF-16 string value
 * Returns 1 if successful or -1 on error
 */
int liblnk_debug_print_utf16_string_value(
     const char *function_name,
     const char *value_name,
     const uint8_t *byte_stream,
     size_t byte_stream_size,
     int byte_order,
     libcerror_error_t **error )
{
	system_character_t *string = NULL;
	static char *function      = "liblnk_debug_print_utf16_string_value";
	size_t string_size         = 0;
	int result                 = 0;

	if( ( byte_stream == NULL )
	 || ( byte_stream_size == 0 ) )
	{
		libcnotify_printf(
		 "%s: %s:\n",
		 function_name,
		 value_name );

		return( 1 );
	}
#if defined( HAVE_WIDE_SYSTEM_CHARACTER )
	result = libuna_utf16_string_size_from_utf16_stream(
	          byte_stream,
	          byte_stream_size,
	          byte_order,
	          &string_size,
	          error );
#else
	result = libuna_utf8_string_size_from_utf16_stream(
	          byte_stream,
	          byte_stream_size,
	          byte_order,
	          &string_size,
	          error );
#endif
	if( result != 1 )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_GET_FAILED,
		 "%s: unable to determine size of string.",
		 function );

		goto on_error;
	}
	if( string_size > ( (size_t) SSIZE_MAX / sizeof( system_character_t ) ) )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_VALUE_EXCEEDS_MAXIMUM,
		 "%s: invalid string size value exceeds maximum.",
		 function );

		goto on_error;
	}
	libcnotify_printf(
	 "%s: %s:",
	 function_name,
	 value_name );

	if( string_size > 0 )
	{
		string = system_string_allocate(
		          string_size );

		if( string == NULL )
		{
			libcerror_error_set(
			 error,
			 LIBCERROR_ERROR_DOMAIN_MEMORY,
			 LIBCERROR_MEMORY_ERROR_INSUFFICIENT,
			 "%s: unable to create string.",
			 function );

			goto on_error;
		}
#if defined( HAVE_WIDE_SYSTEM_CHARACTER )
		result = libuna_utf16_string_copy_from_utf16_stream(
		          (libuna_utf16_character_t *) string,
		          string_size,
		          byte_stream,
		          byte_stream_size,
		          byte_order,
		          error );
#else
		result = libuna_utf8_string_copy_from_utf16_stream(
		          (libuna_utf8_character_t *) string,
		          string_size,
		          byte_stream,
		          byte_stream_size,
		          byte_order,
		          error );
#endif
		if( result != 1 )
		{
			libcerror_error_set(
			 error,
			 LIBCERROR_ERROR_DOMAIN_RUNTIME,
			 LIBCERROR_RUNTIME_ERROR_SET_FAILED,
			 "%s: unable to set string.",
			 function );

			goto on_error;
		}
		libcnotify_printf(
		 " %s",
		 string );

		memory_free(
		 string );
	}
	libcnotify_printf(
	 "\n" );

	return( 1 );

on_error:
	if( string != NULL )
	{
		memory_free(
		 string );
	}
	return( -1 );
}

/* Prints the read offsets
 * Returns 1 if successful or -1 on error
 */
int liblnk_debug_print_read_offsets(
     libbfio_handle_t *file_io_handle,
     libcerror_error_t **error )
{
	static char *function = "liblnk_debug_print_read_offsets";
	off64_t offset        = 0;
	size64_t size         = 0;
	int number_of_offsets = 0;
	int offset_iterator   = 0;

	if( file_io_handle == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid file io handle.",
		 function );

		return( -1 );
	}
	if( libbfio_handle_get_number_of_offsets_read(
	     file_io_handle,
	     &number_of_offsets,
	     error ) != 1 )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_RUNTIME,
		 LIBCERROR_RUNTIME_ERROR_GET_FAILED,
		 "%s: unable to retrieve number of offsets read.",
		 function );

		return( -1 );
	}
	libcnotify_printf(
	 "Offsets read:\n" );

	for( offset_iterator = 0;
	     offset_iterator < number_of_offsets;
	     offset_iterator++ )
	{
		if( libbfio_handle_get_offset_read(
		     file_io_handle,
		     offset_iterator,
		     &offset,
		     &size,
		     error ) != 1 )
		{
			libcerror_error_set(
			 error,
			 LIBCERROR_ERROR_DOMAIN_RUNTIME,
			 LIBCERROR_RUNTIME_ERROR_GET_FAILED,
			 "%s: unable to retrieve offset: %d.",
			 function,
			 offset_iterator );

			return( -1 );
		}
		libcnotify_printf(
		 "%08" PRIi64 " ( 0x%08" PRIx64 " ) - %08" PRIi64 " ( 0x%08" PRIx64 " ) size: %" PRIu64 "\n",
		 offset,
		 offset,
		 offset + size,
		 offset + size,
		 size );
	}
	libcnotify_printf(
	 "\n" );

	return( 1 );
}

#endif /* defined( HAVE_DEBUG_OUTPUT ) */

