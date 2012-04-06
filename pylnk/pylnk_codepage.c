/*
 * Codepage functions
 *
 * Copyright (c) 2009-2012, Joachim Metz <jbmetz@users.sourceforge.net>
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
#include <types.h>

#include "pylnk_libcerror.h"
#include "pylnk_libcstring.h"
#include "pylnk_codepage.h"

/* Determines the codepage from a string
 * Returns 1 if successful, 0 if unsupported value or -1 on error
 */
int pylnk_codepage_from_string(
     int *codepage,
     const char *string,
     size_t string_length,
     uint32_t feature_flags,
     libcerror_error_t **error )
{
	static char *function    = "pylnk_codepage_from_string";
	size_t string_index      = 0;
	uint32_t supported_flags = 0;
	int codepage_set         = PYLNK_CODEPAGE_SET_UNDEFINED;

	if( codepage == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid codepage.",
		 function );

		return( -1 );
	}
	if( string == NULL )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid string.",
		 function );

		return( -1 );
	}
	if( string_length > (size_t) SSIZE_MAX )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_VALUE_EXCEEDS_MAXIMUM,
		 "%s: invalid string length value exceeds maximum.",
		 function );

		return( -1 );
	}
	supported_flags = PYLNK_CODEPAGE_FEATURE_FLAG_HAVE_ISO_8859_CODEPAGES
	                | PYLNK_CODEPAGE_FEATURE_FLAG_HAVE_KOI8_CODEPAGES
	                | PYLNK_CODEPAGE_FEATURE_FLAG_HAVE_WINDOWS_CODEPAGES;

	if( ( feature_flags & ~( supported_flags ) ) != 0 )
	{
		libcerror_error_set(
		 error,
		 LIBCERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBCERROR_ARGUMENT_ERROR_UNSUPPORTED_VALUE,
		 "%s: unsupported feature flags value: 0x%08" PRIx32 ".",
		 function,
		 feature_flags );

		return( -1 );
	}
	*codepage = PYLNK_CODEPAGE_UNDEFINED;

	if( string_length == 5 )
	{
		if( libcstring_system_string_compare_no_case(
		     string,
		     _LIBCSTRING_SYSTEM_STRING( "ascii" ),
		     5 ) == 0 )
		{
			*codepage = PYLNK_CODEPAGE_ASCII;

			string_index = 5;
		}
	}
	if( ( feature_flags & PYLNK_CODEPAGE_FEATURE_FLAG_HAVE_ISO_8859_CODEPAGES ) != 0 )
	{
		/* Supported string formats:
		 * iso8859-1, iso8859_1, iso-8859-1, iso-8859_1, iso_8859-1, iso_8859_1
		 */
		if( string_length >= 8 )
		{
			if( libcstring_system_string_compare_no_case(
			     string,
			     _LIBCSTRING_SYSTEM_STRING( "iso" ),
			     3 ) == 0 )
			{
				string_index = 3;

				if( ( string[ string_index ] == '-' )
				 || ( string[ string_index ] == '_' ) )
				{
					string_index++;
				}
				if( ( string[ string_index     ] == '8' )
				 && ( string[ string_index + 1 ] == '8' )
				 && ( string[ string_index + 2 ] == '5' )
				 && ( string[ string_index + 3 ] == '9' ) )
				{
					string_index += 4;

					if( string_index < string_length )
					{
						if( ( string[ string_index ] == '-' )
						 || ( string[ string_index ] == '_' ) )
						{
							string_index++;

							codepage_set = PYLNK_CODEPAGE_SET_ISO_8859;
						}
					}
				}
			}
		}
	}
	if( ( feature_flags & PYLNK_CODEPAGE_FEATURE_FLAG_HAVE_KOI8_CODEPAGES ) != 0 )
	{
		/* Supported string formats:
		 * koi8, koi8-r, koi8_r
		 */
		if( string_length >= 4 )
		{
			if( libcstring_system_string_compare_no_case(
			     string,
			     _LIBCSTRING_SYSTEM_STRING( "koi8" ),
			     4 ) == 0 )
			{
				string_index = 4;

				codepage_set = PYLNK_CODEPAGE_SET_KOI8;

				if( string_index < string_length )
				{
					if( ( string[ string_index ] == '-' )
					 || ( string[ string_index ] == '_' ) )
					{
						string_index++;
					}
				}
			}
		}
	}
	if( ( feature_flags & PYLNK_CODEPAGE_FEATURE_FLAG_HAVE_WINDOWS_CODEPAGES ) != 0 )
	{
		/* Supported string formats:
		 * cp1252, ms1252, windows1252, windows-1252, windows_1252
		 */
		if( string_length >= 7 )
		{
			if( libcstring_system_string_compare_no_case(
			     string,
			     _LIBCSTRING_SYSTEM_STRING( "windows" ),
			     7 ) == 0 )
			{
				string_index = 7;

				codepage_set = PYLNK_CODEPAGE_SET_WINDOWS;

				if( string_index < string_length )
				{
					if( ( string[ string_index ] == '-' )
					 || ( string[ string_index ] == '_' ) )
					{
						string_index++;
					}
				}
			}
		}
		else if( string_length >= 2 )
		{
			if( libcstring_system_string_compare_no_case(
			     string,
			     _LIBCSTRING_SYSTEM_STRING( "cp" ),
			     2 ) == 0 )
			{
				string_index = 2;

				codepage_set = PYLNK_CODEPAGE_SET_GENERIC;
			}
			else if( libcstring_system_string_compare_no_case(
			          string,
			          _LIBCSTRING_SYSTEM_STRING( "ms" ),
			          2 ) == 0 )
			{
				string_index = 2;

				codepage_set = PYLNK_CODEPAGE_SET_WINDOWS;
			}
		}
	}
	if( codepage_set == PYLNK_CODEPAGE_SET_ISO_8859 )
	{
		if( ( string_index + 1 ) == string_length )
		{
			switch( string[ string_index ] )
			{
				case '1':
					*codepage = PYLNK_CODEPAGE_ISO_8859_1;
					break;

				case '2':
					*codepage = PYLNK_CODEPAGE_ISO_8859_2;
					break;

				case '3':
					*codepage = PYLNK_CODEPAGE_ISO_8859_3;
					break;

				case '4':
					*codepage = PYLNK_CODEPAGE_ISO_8859_4;
					break;

				case '5':
					*codepage = PYLNK_CODEPAGE_ISO_8859_5;
					break;

				case '6':
					*codepage = PYLNK_CODEPAGE_ISO_8859_6;
					break;

				case '7':
					*codepage = PYLNK_CODEPAGE_ISO_8859_7;
					break;

				case '8':
					*codepage = PYLNK_CODEPAGE_ISO_8859_8;
					break;

				case '9':
					*codepage = PYLNK_CODEPAGE_ISO_8859_9;
					break;

				default:
					break;
			}
		}
		else if( ( string_index + 2 ) == string_length )
		{
			if( string[ string_index ] == '1' )
			{
				string_index++;

				switch( string[ string_index ] )
				{
					case '0':
						*codepage = PYLNK_CODEPAGE_ISO_8859_10;
						break;

					case '1':
						*codepage = PYLNK_CODEPAGE_ISO_8859_11;
						break;

					case '3':
						*codepage = PYLNK_CODEPAGE_ISO_8859_13;
						break;

					case '4':
						*codepage = PYLNK_CODEPAGE_ISO_8859_14;
						break;

					case '5':
						*codepage = PYLNK_CODEPAGE_ISO_8859_15;
						break;

					case '6':
						*codepage = PYLNK_CODEPAGE_ISO_8859_16;
						break;

					default:
						break;
				}
			}
		}
	}
	if( codepage_set == PYLNK_CODEPAGE_SET_KOI8 )
	{
		if( ( string_index + 1 ) == string_length )
		{
			switch( string[ string_index ] )
			{
				case 'r':
				case 'R':
					*codepage = PYLNK_CODEPAGE_KOI8_R;
					break;

				case 'u':
				case 'U':
					*codepage = PYLNK_CODEPAGE_KOI8_U;
					break;

				default:
					break;
			}
		}
	}
	if( ( codepage_set == PYLNK_CODEPAGE_SET_GENERIC )
	 || ( codepage_set == PYLNK_CODEPAGE_SET_WINDOWS ) )
	{
		if( ( string_index + 3 ) == string_length )
		{
			switch( string[ string_index ] )
			{
				case '8':
					if( ( string[ string_index + 1 ] == '7' )
					 && ( string[ string_index + 2 ] == '4' ) )
					{
						*codepage = PYLNK_CODEPAGE_WINDOWS_874;
					}
					break;

				case '9':
					if( ( string[ string_index + 1 ] == '3' )
					 && ( string[ string_index + 2 ] == '2' ) )
					{
						*codepage = PYLNK_CODEPAGE_WINDOWS_932;
					}
					else if( ( string[ string_index + 1 ] == '3' )
					      && ( string[ string_index + 2 ] == '6' ) )
					{
						*codepage = PYLNK_CODEPAGE_WINDOWS_936;
					}
					else if( ( string[ string_index + 1 ] == '4' )
					      && ( string[ string_index + 2 ] == '9' ) )
					{
						*codepage = PYLNK_CODEPAGE_WINDOWS_949;
					}
					else if( ( string[ string_index + 1 ] == '5' )
					      && ( string[ string_index + 2 ] == '0' ) )
					{
						*codepage = PYLNK_CODEPAGE_WINDOWS_949;
					}
					break;

				default:
					break;
			}
		}
		else if( ( string_index + 4 ) == string_length )
		{
			if( ( string[ string_index     ] == '1' )
			 && ( string[ string_index + 1 ] == '2' )
			 && ( string[ string_index + 2 ] == '5' ) )
			{
				switch( string[ string_index + 3 ] )
				{
					case '0':
						*codepage = PYLNK_CODEPAGE_WINDOWS_1250;
						break;

					case '1':
						*codepage = PYLNK_CODEPAGE_WINDOWS_1251;
						break;

					case '2':
						*codepage = PYLNK_CODEPAGE_WINDOWS_1252;
						break;

					case '3':
						*codepage = PYLNK_CODEPAGE_WINDOWS_1253;
						break;

					case '4':
						*codepage = PYLNK_CODEPAGE_WINDOWS_1254;
						break;

					case '5':
						*codepage = PYLNK_CODEPAGE_WINDOWS_1255;
						break;

					case '6':
						*codepage = PYLNK_CODEPAGE_WINDOWS_1256;
						break;

					case '7':
						*codepage = PYLNK_CODEPAGE_WINDOWS_1257;
						break;

					case '8':
						*codepage = PYLNK_CODEPAGE_WINDOWS_1258;
						break;

					default:
						break;
				}
			}
		}
	}
	if( *codepage != PYLNK_CODEPAGE_UNDEFINED )
	{
		return( 1 );
	}
	return( 0 );
}

/* Returns a string representation of the codepage
 * Codecs and aliases are defined: http://docs.python.org/library/codecs.html#standard-encodings
 * Returns 1 if successful or NULL if codepage is not supported
 */
const char *pylnk_codepage_to_string(
             int codepage )
{
	switch( codepage )
	{
		case PYLNK_CODEPAGE_ASCII:
			return( "ascii" );

		case PYLNK_CODEPAGE_ISO_8859_1:
			return( "iso-8859-1" );

		case PYLNK_CODEPAGE_ISO_8859_2:
			return( "iso-8859-2" );

		case PYLNK_CODEPAGE_ISO_8859_3:
			return( "iso-8859-3" );

		case PYLNK_CODEPAGE_ISO_8859_4:
			return( "iso-8859-4" );

		case PYLNK_CODEPAGE_ISO_8859_5:
			return( "iso-8859-5" );

		case PYLNK_CODEPAGE_ISO_8859_6:
			return( "iso-8859-6" );

		case PYLNK_CODEPAGE_ISO_8859_7:
			return( "iso-8859-7" );

		case PYLNK_CODEPAGE_ISO_8859_8:
			return( "iso-8859-8" );

		case PYLNK_CODEPAGE_ISO_8859_9:
			return( "iso-8859-9" );

		case PYLNK_CODEPAGE_ISO_8859_10:
			return( "iso-8859-10" );

		case PYLNK_CODEPAGE_ISO_8859_11:
			return( "iso-8859-11" );

		case PYLNK_CODEPAGE_ISO_8859_13:
			return( "iso-8859-13" );

		case PYLNK_CODEPAGE_ISO_8859_14:
			return( "iso-8859-14" );

		case PYLNK_CODEPAGE_ISO_8859_15:
			return( "iso-8859-15" );

		case PYLNK_CODEPAGE_ISO_8859_16:
			return( "iso-8859-16" );

		case PYLNK_CODEPAGE_KOI8_R:
			return( "koi8_r" );

		case PYLNK_CODEPAGE_KOI8_U:
			return( "koi8_u" );

		case PYLNK_CODEPAGE_WINDOWS_874:
			return( "cp874" );

		case PYLNK_CODEPAGE_WINDOWS_932:
			return( "cp932" );

		case PYLNK_CODEPAGE_WINDOWS_936:
			return( "cp936" );

		case PYLNK_CODEPAGE_WINDOWS_949:
			return( "cp949" );

		case PYLNK_CODEPAGE_WINDOWS_950:
			return( "cp950" );

		case PYLNK_CODEPAGE_WINDOWS_1250:
			return( "cp1250" );

		case PYLNK_CODEPAGE_WINDOWS_1251:
			return( "cp1251" );

		case PYLNK_CODEPAGE_WINDOWS_1252:
			return( "cp1252" );

		case PYLNK_CODEPAGE_WINDOWS_1253:
			return( "cp1253" );

		case PYLNK_CODEPAGE_WINDOWS_1254:
			return( "cp1254" );

		case PYLNK_CODEPAGE_WINDOWS_1255:
			return( "cp1255" );

		case PYLNK_CODEPAGE_WINDOWS_1256:
			return( "cp1256" );

		case PYLNK_CODEPAGE_WINDOWS_1257:
			return( "cp1257" );

		case PYLNK_CODEPAGE_WINDOWS_1258:
			return( "cp1258" );

		default:
			break;
	}
	return( NULL );
}

