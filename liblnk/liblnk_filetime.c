/*
 * Filetime functions
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
#include <endian.h>
#include <narrow_string.h>
#include <types.h>

#include <liberror.h>

#include "liblnk_definitions.h"
#include "liblnk_filetime.h"

/* Converts a byte stream into a filetime
 * Returns 1 if successful or -1 on error
 */
int liblnk_filetime_from_byte_stream(
     liblnk_filetime_t *filetime,
     uint8_t *byte_stream,
     size_t byte_stream_size,
     uint8_t byte_order,
     liberror_error_t **error )
{
	static char *function = "liblnk_filetime_from_byte_stream";

	if( filetime == NULL )
	{
		liberror_error_set(
		 error,
		 LIBERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid filetime.",
		 function );

		return( -1 );
	}
	if( byte_stream == NULL )
	{
		liberror_error_set(
		 error,
		 LIBERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid byte stream.",
		 function );

		return( -1 );
	}
	if( byte_stream_size < 8 )
	{
		liberror_error_set(
		 error,
		 LIBERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBERROR_ARGUMENT_ERROR_VALUE_TOO_SMALL,
		 "%s: byte stream too small.",
		 function );

		return( -1 );
	}
	if( byte_stream_size > (size_t) SSIZE_MAX )
	{
		liberror_error_set(
		 error,
		 LIBERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBERROR_ARGUMENT_ERROR_VALUE_EXCEEDS_MAXIMUM,
		 "%s: byte stream size exceeds maximum.",
		 function );

		return( -1 );
	}
	if( ( byte_order != LIBLNK_ENDIAN_BIG )
	 && ( byte_order != LIBLNK_ENDIAN_LITTLE ) )
	{
		liberror_error_set(
		 error,
		 LIBERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBERROR_ARGUMENT_ERROR_UNSUPPORTED_VALUE,
		 "%s: unsupported byte order.",
		 function );

		return( -1 );
	}
	if( byte_order == LIBLNK_ENDIAN_LITTLE )
	{
		endian_little_convert_32bit(
		 filetime->lower,
		 byte_stream );

		byte_stream += 4;

		endian_little_convert_32bit(
		filetime->upper,
		byte_stream );
	}
	else if( byte_order == LIBLNK_ENDIAN_BIG )
	{
		endian_big_convert_32bit(
		 filetime->upper,
		 byte_stream );

		byte_stream += 4;

		endian_big_convert_32bit(
		filetime->lower,
		byte_stream );
	}
	return( 1 );
}

/* Converts the filetime into a string
 * Returns 1 if successful or -1 on error
 */
int liblnk_filetime_to_string(
     liblnk_filetime_t *filetime,
     uint8_t *string,
     size_t string_size,
     liberror_error_t **error )
{
	char *month_string     = NULL;
	static char *function  = "liblnk_filetime_to_string";
	uint64_t filetimestamp = 0;
	uint32_t remainder     = 0;
	uint16_t days_in_year  = 0;
	uint16_t year          = 0;
	uint8_t days_in_month  = 0;
	uint8_t seconds        = 0;
	uint8_t minutes        = 0;
	uint8_t hours          = 0;
	uint8_t month          = 0;
	uint8_t day            = 0;
	int print_count        = 0;

	if( filetime == NULL )
	{
		liberror_error_set(
		 error,
		 LIBERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid filetime.",
		 function );

		return( -1 );
	}
	if( string == NULL )
	{
		liberror_error_set(
		 error,
		 LIBERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBERROR_ARGUMENT_ERROR_INVALID_VALUE,
		 "%s: invalid string.",
		 function );

		return( -1 );
	}
	if( string_size < LIBLNK_FILETIME_STRING_SIZE )
	{
		liberror_error_set(
		 error,
		 LIBERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBERROR_ARGUMENT_ERROR_VALUE_TOO_SMALL,
		 "%s: string too small.",
		 function );

		return( -1 );
	}
	if( string_size > (size_t) SSIZE_MAX )
	{
		liberror_error_set(
		 error,
		 LIBERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBERROR_ARGUMENT_ERROR_VALUE_EXCEEDS_MAXIMUM,
		 "%s: invalid string size value exceeds maximum.",
		 function );

		return( -1 );
	}
	/* Combine the lower and upper filetime parts into a single filetime timestamp
	 */
	filetimestamp = ( (uint64_t) ( filetime->upper ) << 32 ) + filetime->lower;

	/* The timestamp is in units of 100 nano seconds correct the value to seconds
	 */
	remainder      = filetimestamp % 10000000;
	filetimestamp /= 10000000;

	/* There are 60 seconds in a minute correct the value to minutes
	 */
	seconds        = filetimestamp % 60;
	filetimestamp /= 60;

	/* There are 60 minutes in an hour correct the value to hours
	 */
	minutes        = filetimestamp % 60;
	filetimestamp /= 60;

	/* There are 24 hours in a day correct the value to days
	 */
	hours          = filetimestamp % 24;
	filetimestamp /= 24;

        /* Add 1 day to compensate that Jan 1 1601 is represented as 0
	 */
	filetimestamp += 1;

	/* Determine the amount of years starting at '1 Jan 1601 00:00:00'
	 * correct the value to days within the year
	 */
	year = 1601;

	while( filetimestamp > 0 )
	{
		/* Check for a leap year
		 * The year is ( ( dividable by 4 ) and ( not dividable by 100 ) ) or ( dividable by 400 )
		 */
		if( ( ( ( year % 4 ) == 0 )
		  && ( ( year % 100 ) != 0 ) )
		 || ( ( year % 400 ) == 0 ) )
		{
			days_in_year = 366;
		}
		else
		{
			days_in_year = 365;
		}
		if( filetimestamp <= days_in_year )
		{
			break;
		}
		filetimestamp -= days_in_year;

		year++;
	}
	if( year > 9999 )
	{
		liberror_error_set(
		 error,
		 LIBERROR_ERROR_DOMAIN_ARGUMENTS,
		 LIBERROR_ARGUMENT_ERROR_UNSUPPORTED_VALUE,
		 "%s: unsupported year: %" PRIu16 "",
		 function,
		 year );

		return( -1 );
	}
	/* Determine the month correct the value to days within the month
	 */
	month = 1;

	while( filetimestamp > 0 )
	{
		/* February (2)
		*/
		if( month == 2 )
		{
			if( ( ( ( year % 4 ) == 0 )
			  && ( ( year % 100 ) != 0 ) )
			 || ( ( year % 400 ) == 0 ) )
			{
				days_in_month = 29;
			}
			else
			{
				days_in_month = 28;
			}
		}
		/* April (4), June (6), September (9), November (11)
		 */
		else if( ( month == 4 )
		 || ( month == 6 )
		 || ( month == 9 )
		 || ( month == 11 ) )
		{
			days_in_month = 30;
		}
		/* January (1), March (3), May (5), July (7), August (8), October (10), December (12)
		 */
		else if( ( month == 1 )
		 || ( month == 3 )
		 || ( month == 5 )
		 || ( month == 7 )
		 || ( month == 8 )
		 || ( month == 10 )
		 || ( month == 12 ) )
		{
			days_in_month = 31;
		}
		/* This should never happen, but just in case
		 */
		else
		{
			liberror_error_set(
			 error,
			 LIBERROR_ERROR_DOMAIN_ARGUMENTS,
			 LIBERROR_ARGUMENT_ERROR_UNSUPPORTED_VALUE,
			 "%s: unsupported month: %" PRIu8 "",
			 function,
			 month );

			return( -1 );
		}
		if( filetimestamp <= days_in_month )
		{
			break;
		}
		filetimestamp -= days_in_month;

		month++;
	}
	switch( month )
	{
		case 1:
			month_string = "Jan";
			break;
		case 2:
			month_string = "Feb";
			break;
		case 3:
			month_string = "Mar";
			break;
		case 4:
			month_string = "Apr";
			break;
		case 5:
			month_string = "May";
			break;
		case 6:
			month_string = "Jun";
			break;
		case 7:
			month_string = "Jul";
			break;
		case 8:
			month_string = "Aug";
			break;
		case 9:
			month_string = "Sep";
			break;
		case 10:
			month_string = "Oct";
			break;
		case 11:
			month_string = "Nov";
			break;
		case 12:
			month_string = "Dec";
			break;

		default:
			liberror_error_set(
			 error,
			 LIBERROR_ERROR_DOMAIN_RUNTIME,
			 LIBERROR_RUNTIME_ERROR_UNSUPPORTED_VALUE,
			 "%s: unsupported month: %" PRIu8 "",
			 function,
			 month );

			return( -1 );
	}
	/* Determine the day
	 */
	day = (uint8_t) filetimestamp;

	/* Create the time string
	 */
	print_count = narrow_string_snprintf(
	               (char *) string,
	               string_size,
	               "%s %02u, %04u %02u:%02u:%02u UTC",
	               month_string,
	               day,
	               year,
	               hours,
	               minutes,
	               seconds );

	if( ( print_count < 0 )
	 || ( (size_t) print_count > string_size ) )
	{
		liberror_error_set(
		 error,
		 LIBERROR_ERROR_DOMAIN_RUNTIME,
		 LIBERROR_RUNTIME_ERROR_SET_FAILED,
		 "%s: unable to set string.",
		 function );

		return( -1 );
	}
	return( 1 );
}

