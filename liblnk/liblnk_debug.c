/*
 * Debug functions
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
#include <memory.h>
#include <types.h>

#include <liberror.h>
#include <libnotify.h>

#include "liblnk_debug.h"
#include "liblnk_definitions.h"
#include "liblnk_libbfio.h"
#include "liblnk_string.h"

#if defined( HAVE_DEBUG_OUTPUT )

/* Prints the data flags
 * Returns 1 if successful or -1 on error
 */
int liblnk_debug_print_data_flags(
     uint32_t data_flags,
     liberror_error_t **error )
{
	static char *function = "liblnk_debug_print_data_flags";

	libnotify_verbose_printf(
	 "%s: data flags: 0x%08" PRIx32 "\n",
	 function,
	 data_flags );

	if( ( data_flags & LIBLNK_DATA_FLAG_HAS_LINK_TARGET_IDENTIFIER ) == LIBLNK_DATA_FLAG_HAS_LINK_TARGET_IDENTIFIER )
	{
		libnotify_verbose_printf(
		 "\tContains link target identifier (HasTargetIDList)\n" );
	}
	if( ( data_flags & LIBLNK_DATA_FLAG_HAS_LOCATION_INFORMATION ) == LIBLNK_DATA_FLAG_HAS_LOCATION_INFORMATION )
	{
		libnotify_verbose_printf(
		 "\tContains location information (HasLinkInfo)\n" );
	}
	if( ( data_flags & LIBLNK_DATA_FLAG_HAS_DESCRIPTION_STRING ) == LIBLNK_DATA_FLAG_HAS_DESCRIPTION_STRING )
	{
		libnotify_verbose_printf(
		 "\tContains description string (HasName)\n" );
	}
	if( ( data_flags & LIBLNK_DATA_FLAG_HAS_RELATIVE_PATH_STRING ) == LIBLNK_DATA_FLAG_HAS_RELATIVE_PATH_STRING )
	{
		libnotify_verbose_printf(
		 "\tContains relative path string (HasRelativePath)\n" );
	}
	if( ( data_flags & LIBLNK_DATA_FLAG_HAS_WORKING_DIRECTORY_STRING ) == LIBLNK_DATA_FLAG_HAS_WORKING_DIRECTORY_STRING )
	{
		libnotify_verbose_printf(
		 "\tContains working directory string (HasWorkingDir)\n" );
	}
	if( ( data_flags & LIBLNK_DATA_FLAG_HAS_COMMAND_LINE_ARGUMENTS_STRING ) == LIBLNK_DATA_FLAG_HAS_COMMAND_LINE_ARGUMENTS_STRING )
	{
		libnotify_verbose_printf(
		 "\tContains command line arguments string (HasArguments)\n" );
	}
	if( ( data_flags & LIBLNK_DATA_FLAG_HAS_ICON_LOCATION_STRING ) == LIBLNK_DATA_FLAG_HAS_ICON_LOCATION_STRING )
	{
		libnotify_verbose_printf(
		 "\tContains icon location string (HasIconLocation)\n" );
	}
	if( ( data_flags & LIBLNK_DATA_FLAG_IS_UNICODE ) == LIBLNK_DATA_FLAG_IS_UNICODE )
	{
		libnotify_verbose_printf(
		 "\tString are in Unicode (IsUnicode)\n" );
	}
	if( ( data_flags & LIBLNK_DATA_FLAG_FORCE_NO_LOCATION_INFORMATION ) == LIBLNK_DATA_FLAG_FORCE_NO_LOCATION_INFORMATION )
	{
		libnotify_verbose_printf(
		 "\tIgnore the location information (ForceNoLinkInfo)\n" );
	}
	if( ( data_flags & LIBLNK_DATA_FLAG_HAS_ENVIRONMENT_VARIABLES_LOCATION_BLOCK ) == LIBLNK_DATA_FLAG_HAS_ENVIRONMENT_VARIABLES_LOCATION_BLOCK )
	{
		libnotify_verbose_printf(
		 "\tContains environment variables location block (HasExpString)\n" );
	}
	if( ( data_flags & LIBLNK_DATA_FLAG_RUN_IN_SEPARATE_PROCESS ) == LIBLNK_DATA_FLAG_RUN_IN_SEPARATE_PROCESS )
	{
		libnotify_verbose_printf(
		 "\tRun in separate process (RunInSeparateProcess)\n" );
	}

	if( ( data_flags & LIBLNK_DATA_FLAG_HAS_DARWIN_IDENTIFIER ) == LIBLNK_DATA_FLAG_HAS_DARWIN_IDENTIFIER )
	{
		libnotify_verbose_printf(
		 "\tContains Darwin properites location block (HasDarwinID)\n" );
	}
	if( ( data_flags & LIBLNK_DATA_FLAG_RUN_AS_USER ) == LIBLNK_DATA_FLAG_RUN_AS_USER )
	{
		libnotify_verbose_printf(
		 "\tRun as user (RunAsUser)\n" );
	}
	if( ( data_flags & LIBLNK_DATA_FLAG_HAS_ICON_LOCATION_BLOCK ) == LIBLNK_DATA_FLAG_HAS_ICON_LOCATION_BLOCK )
	{
		libnotify_verbose_printf(
		 "\tContains icon location block (HasExpIcon)\n" );
	}
	if( ( data_flags & LIBLNK_DATA_FLAG_NO_PIDL_ALIAS ) == LIBLNK_DATA_FLAG_NO_PIDL_ALIAS )
	{
		libnotify_verbose_printf(
		 "\t(NoPidlAlias)\n" );
	}

	if( ( data_flags & LIBLNK_DATA_FLAG_RUN_WITH_SHIM_LAYER ) == LIBLNK_DATA_FLAG_RUN_WITH_SHIM_LAYER )
	{
		libnotify_verbose_printf(
		 "\tContains shim layer properties block (RunWithShimLayer)\n" );
	}
	if( ( data_flags & LIBLNK_DATA_FLAG_NO_DISTRIBUTED_LINK_TRACKING_DATA_BLOCK ) == LIBLNK_DATA_FLAG_NO_DISTRIBUTED_LINK_TRACKING_DATA_BLOCK )
	{
		libnotify_verbose_printf(
		 "\tDoes not contain distributed link tracking data block (ForceNoLinkTrack)\n" );
	}
	if( ( data_flags & LIBLNK_DATA_FLAG_HAS_METADATA_PROPERTY_STORE_DATA_BLOCK ) == LIBLNK_DATA_FLAG_HAS_METADATA_PROPERTY_STORE_DATA_BLOCK )
	{
		libnotify_verbose_printf(
		 "\tContains metadata property store block (HasTargetMetadata)\n" );
	}

	if( ( data_flags & 0x00100000 ) == 0x00100000 )
	{
		libnotify_verbose_printf(
		 "\t(DisableLinkPathTracking)\n" );
	}
	if( ( data_flags & 0x00200000 ) == 0x00200000 )
	{
		libnotify_verbose_printf(
		 "\t(DisableKnownFolderTracking)\n" );
	}
	if( ( data_flags & 0x00400000 ) == 0x00400000 )
	{
		libnotify_verbose_printf(
		 "\t(AllowLinkToLink)\n" );
	}
	if( ( data_flags & 0x00800000 ) == 0x00800000 )
	{
		libnotify_verbose_printf(
		 "\t(UnaliasOnSave)\n" );
	}
	if( ( data_flags & 0x01000000 ) == 0x01000000 )
	{
		libnotify_verbose_printf(
		 "\t(PreferEnvironmentPath)\n" );
	}
	if( ( data_flags & 0x02000000 ) == 0x02000000 )
	{
		libnotify_verbose_printf(
		 "\t(KeepLocalIDListForUNCTarget)\n" );
	}

	libnotify_verbose_printf(
	 "\n" );

	return( 1 );
}

/* Prints the file attribute flags
 * Returns 1 if successful or -1 on error
 */
int liblnk_debug_print_file_attribute_flags(
     uint32_t file_attribute_flags,
     liberror_error_t **error )
{
	static char *function = "liblnk_debug_print_file_attribute_flags";

	libnotify_verbose_printf(
	 "%s: file attribute flags: 0x%08" PRIx32 "\n",
	 function,
	 file_attribute_flags );

	if( ( file_attribute_flags & LIBLNK_FILE_ATTRIBUTE_FLAG_READ_ONLY ) == LIBLNK_FILE_ATTRIBUTE_FLAG_READ_ONLY )
	{
		libnotify_verbose_printf(
		 "\tIs read-only (FILE_ATTRIBUTE_READ_ONLY)\n" );
	}
	if( ( file_attribute_flags & LIBLNK_FILE_ATTRIBUTE_FLAG_HIDDEN ) == LIBLNK_FILE_ATTRIBUTE_FLAG_HIDDEN )
	{
		libnotify_verbose_printf(
		 "\tIs hidden (FILE_ATTRIBUTE_HIDDEN)\n" );
	}
	if( ( file_attribute_flags & LIBLNK_FILE_ATTRIBUTE_FLAG_SYSTEM ) == LIBLNK_FILE_ATTRIBUTE_FLAG_SYSTEM )
	{
		libnotify_verbose_printf(
		 "\tIs system (FILE_ATTRIBUTE_SYSTEM)\n" );
	}

	if( ( file_attribute_flags & LIBLNK_FILE_ATTRIBUTE_FLAG_DIRECTORY ) == LIBLNK_FILE_ATTRIBUTE_FLAG_DIRECTORY )
	{
		libnotify_verbose_printf(
		 "\tIs directory (FILE_ATTRIBUTE_DIRECTORY)\n" );
	}
	if( ( file_attribute_flags & LIBLNK_FILE_ATTRIBUTE_FLAG_ARCHIVE ) == LIBLNK_FILE_ATTRIBUTE_FLAG_ARCHIVE )
	{
		libnotify_verbose_printf(
		 "\tShould be archived (FILE_ATTRIBUTE_ARCHIVE)\n" );
	}
	if( ( file_attribute_flags & LIBLNK_FILE_ATTRIBUTE_FLAG_DEVICE ) == LIBLNK_FILE_ATTRIBUTE_FLAG_DEVICE )
	{
		libnotify_verbose_printf(
		 "\tIs device (FILE_ATTRIBUTE_DEVICE)\n" );
	}
	if( ( file_attribute_flags & LIBLNK_FILE_ATTRIBUTE_FLAG_NORMAL ) == LIBLNK_FILE_ATTRIBUTE_FLAG_NORMAL )
	{
		libnotify_verbose_printf(
		 "\tIs normal (FILE_ATTRIBUTE_NORMAL)\n" );
	}
	if( ( file_attribute_flags & LIBLNK_FILE_ATTRIBUTE_FLAG_TEMPORARY ) == LIBLNK_FILE_ATTRIBUTE_FLAG_TEMPORARY )
	{
		libnotify_verbose_printf(
		 "\tIs temporary (FILE_ATTRIBUTE_TEMPORARY)\n" );
	}
	if( ( file_attribute_flags & LIBLNK_FILE_ATTRIBUTE_FLAG_SPARSE_FILE ) == LIBLNK_FILE_ATTRIBUTE_FLAG_SPARSE_FILE )
	{
		libnotify_verbose_printf(
		 "\tIs a sparse file (FILE_ATTRIBUTE_SPARSE_FILE)\n" );
	}
	if( ( file_attribute_flags & LIBLNK_FILE_ATTRIBUTE_FLAG_REPARSE_POINT ) == LIBLNK_FILE_ATTRIBUTE_FLAG_REPARSE_POINT )
	{
		libnotify_verbose_printf(
		 "\tIs a reparse point or symbolic link (FILE_ATTRIBUTE_FLAG_REPARSE_POINT)\n" );
	}
	if( ( file_attribute_flags & LIBLNK_FILE_ATTRIBUTE_FLAG_COMPRESSED ) == LIBLNK_FILE_ATTRIBUTE_FLAG_COMPRESSED )
	{
		libnotify_verbose_printf(
		 "\tIs compressed (FILE_ATTRIBUTE_COMPRESSED)\n" );
	}
	if( ( file_attribute_flags & LIBLNK_FILE_ATTRIBUTE_FLAG_OFFLINE ) == LIBLNK_FILE_ATTRIBUTE_FLAG_OFFLINE )
	{
		libnotify_verbose_printf(
		 "\tIs offline (FILE_ATTRIBUTE_OFFLINE)\n" );
	}
	if( ( file_attribute_flags & LIBLNK_FILE_ATTRIBUTE_FLAG_NOT_CONTENT_INDEXED ) == LIBLNK_FILE_ATTRIBUTE_FLAG_NOT_CONTENT_INDEXED )
	{
		libnotify_verbose_printf(
		 "\tContent should not be indexed (FILE_ATTRIBUTE_NOT_CONTENT_INDEXED)\n" );
	}
	if( ( file_attribute_flags & LIBLNK_FILE_ATTRIBUTE_FLAG_ENCRYPTED ) == LIBLNK_FILE_ATTRIBUTE_FLAG_ENCRYPTED )
	{
		libnotify_verbose_printf(
		 "\tIs encrypted (FILE_ATTRIBUTE_ENCRYPTED)\n" );
	}

	if( ( file_attribute_flags & LIBLNK_FILE_ATTRIBUTE_FLAG_VIRTUAL ) == LIBLNK_FILE_ATTRIBUTE_FLAG_VIRTUAL )
	{
		libnotify_verbose_printf(
		 "\tIs virtual (FILE_ATTRIBUTE_VIRTUAL)\n" );
	}
	libnotify_verbose_printf(
	 "\n" );

	return( 1 );
}

/* Prints the nework provider type
 * Returns 1 if successful or -1 on error
 */
int liblnk_debug_print_network_provider_type(
     uint32_t network_provider_type,
     liberror_error_t **error )
{
	static char *function = "liblnk_debug_print_network_provider_type";

	libnotify_verbose_printf(
	 "%s: network provider type: 0x%08" PRIx32 " (",
	 function,
	 network_provider_type );

	switch( network_provider_type )
	{
		case 0x001a0000:
			libnotify_verbose_printf(
			 "WNNC_NET_AVID" );
			break;

		case 0x001b0000:
			libnotify_verbose_printf(
			 "WNNC_NET_DOCUSPACE" );
			break;

		case 0x001c0000:
			libnotify_verbose_printf(
			 "WNNC_NET_MANGOSOFT" );
			break;

		case 0x001d0000:
			libnotify_verbose_printf(
			 "WNNC_NET_SERNET" );
			break;

		case 0x001e0000:
			libnotify_verbose_printf(
			 "WNNC_NET_RIVERFRONT1" );
			break;

		case 0x001f0000:
			libnotify_verbose_printf(
			 "WNNC_NET_RIVERFRONT2" );
			break;

		case 0x00200000:
			libnotify_verbose_printf(
			 "WNNC_NET_DECORB" );
			break;

		case 0x00210000:
			libnotify_verbose_printf(
			 "WNNC_NET_PROTSTOR" );
			break;

		case 0x00220000:
			libnotify_verbose_printf(
			 "WNNC_NET_FJ_REDIR" );
			break;

		case 0x00230000:
			libnotify_verbose_printf(
			 "WNNC_NET_DISTINCT" );
			break;

		case 0x00240000:
			libnotify_verbose_printf(
			 "WNNC_NET_TWINS" );
			break;

		case 0x00250000:
			libnotify_verbose_printf(
			 "WNNC_NET_RDR2SAMPLE" );
			break;

		case 0x00260000:
			libnotify_verbose_printf(
			 "WNNC_NET_CSC" );
			break;

		case 0x00270000:
			libnotify_verbose_printf(
			 "WNNC_NET_3IN1" );
			break;

		case 0x00290000:
			libnotify_verbose_printf(
			 "WNNC_NET_EXTENDNET" );
			break;

		case 0x002a0000:
			libnotify_verbose_printf(
			 "WNNC_NET_STAC" );
			break;

		case 0x002b0000:
			libnotify_verbose_printf(
			 "WNNC_NET_FOXBAT" );
			break;

		case 0x002c0000:
			libnotify_verbose_printf(
			 "WNNC_NET_YAHOO" );
			break;

		case 0x002d0000:
			libnotify_verbose_printf(
			 "WNNC_NET_EXIFS" );
			break;

		case 0x002e0000:
			libnotify_verbose_printf(
			 "WNNC_NET_DAV" );
			break;

		case 0x002f0000:
			libnotify_verbose_printf(
			 "WNNC_NET_KNOWARE" );
			break;

		case 0x00300000:
			libnotify_verbose_printf(
			 "WNNC_NET_OBJECT_DIRE" );
			break;

		case 0x00310000:
			libnotify_verbose_printf(
			 "WNNC_NET_MASFAX" );
			break;

		case 0x00320000:
			libnotify_verbose_printf(
			 "WNNC_NET_HOB_NFS" );
			break;

		case 0x00330000:
			libnotify_verbose_printf(
			 "WNNC_NET_SHIVA" );
			break;

		case 0x00340000:
			libnotify_verbose_printf(
			 "WNNC_NET_IBMAL" );
			break;

		case 0x00350000:
			libnotify_verbose_printf(
			 "WNNC_NET_LOCK" );
			break;

		case 0x00360000:
			libnotify_verbose_printf(
			 "WNNC_NET_TERMSRV" );
			break;

		case 0x00370000:
			libnotify_verbose_printf(
			 "WNNC_NET_SRT" );
			break;

		case 0x00380000:
			libnotify_verbose_printf(
			 "WNNC_NET_QUINCY" );
			break;

		case 0x00390000:
			libnotify_verbose_printf(
			 "WNNC_NET_OPENAFS" );
			break;

		case 0x003a0000:
			libnotify_verbose_printf(
			 "WNNC_NET_AVID1" );
			break;

		case 0x003b0000:
			libnotify_verbose_printf(
			 "WNNC_NET_DFS" );
			break;

		case 0x003c0000:
			libnotify_verbose_printf(
			 "WNNC_NET_KWNP" );
			break;

		case 0x003d0000:
			libnotify_verbose_printf(
			 "WNNC_NET_ZENWORKS" );
			break;

		case 0x003e0000:
			libnotify_verbose_printf(
			 "WNNC_NET_DRIVEONWEB" );
			break;

		case 0x003f0000:
			libnotify_verbose_printf(
			 "WNNC_NET_VMWARE" );
			break;

		case 0x00400000:
			libnotify_verbose_printf(
			 "WNNC_NET_RSFX" );
			break;

		case 0x00410000:
			libnotify_verbose_printf(
			 "WNNC_NET_MFILES" );
			break;

		case 0x00420000:
			libnotify_verbose_printf(
			 "WNNC_NET_MS_NFS" );
			break;

		case 0x00430000:
			libnotify_verbose_printf(
			 "WNNC_NET_GOOGLE" );
			break;
	}
	libnotify_verbose_printf(
	 ")\n" );

	return( 1 );
}

/* Prints the read offsets
 * Returns 1 if successful or -1 on error
 */
int liblnk_debug_print_read_offsets(
     libbfio_handle_t *file_io_handle,
     liberror_error_t **error )
{
	static char *function = "liblnk_debug_print_read_offsets";
	off64_t offset        = 0;
	size64_t size         = 0;
	int amount_of_offsets = 0;
	int offset_iterator   = 0;

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
	if( libbfio_handle_get_amount_of_offsets_read(
	     file_io_handle,
	     &amount_of_offsets,
	     error ) != 1 )
	{
		liberror_error_set(
		 error,
		 LIBERROR_ERROR_DOMAIN_RUNTIME,
		 LIBERROR_RUNTIME_ERROR_GET_FAILED,
		 "%s: unable to retrieve amount of offsets read.",
		 function );

		return( -1 );
	}
	libnotify_verbose_printf(
	 "Offsets read:\n" );

	for( offset_iterator = 0; offset_iterator < amount_of_offsets; offset_iterator++ )
	{
		if( libbfio_handle_get_offset_read(
		     file_io_handle,
		     offset_iterator,
		     &offset,
		     &size,
		     error ) != 1 )
		{
			liberror_error_set(
			 error,
			 LIBERROR_ERROR_DOMAIN_RUNTIME,
			 LIBERROR_RUNTIME_ERROR_GET_FAILED,
			 "%s: unable to retrieve offset: %d.",
			 function,
			 ( offset_iterator + 1 ) );

			return( -1 );
		}
		libnotify_verbose_printf(
		 "%08" PRIu64 " ( 0x%08" PRIx64 " ) - %08" PRIu64 " ( 0x%08" PRIx64 " ) size: %" PRIu64 "\n",
		 offset,
		 offset,
		 ( offset + size ),
		 ( offset + size ),
		 size );
	}
	libnotify_verbose_printf(
	 "\n" );

	return( 1 );
}

#endif

