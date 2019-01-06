/*
 * The network share information definition of a Windows Shortcut File (LNK)
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

#if !defined( _LNK_NETWORK_SHARE_INFORMATION_H )
#define _LNK_NETWORK_SHARE_INFORMATION_H

#include <common.h>
#include <types.h>

#if defined( __cplusplus )
extern "C" {
#endif

typedef struct lnk_network_share_information lnk_network_share_information_t;

struct lnk_network_share_information
{
	/* The size of the network share information
	 * Consists of 4 bytes
	 */
	uint8_t size[ 4 ];

	/* The network share type
	 * Consists of 4 bytes
	 */
	uint8_t network_share_type[ 4 ];

	/* The offset of the network share name
	 * Consists of 4 bytes
	 */
	uint8_t network_share_name_offset[ 4 ];

	/* The offset of the device name
	 * Consists of 4 bytes
	 */
	uint8_t device_name_offset[ 4 ];

	/* The network provide type
	 * Consists of 4 bytes
	 */
	uint8_t network_provider_type[ 4 ];

	/* The following values are only available if the network share name offset > 20
	 */

	/* The offset of the unicode network share name
	 * Consists of 4 bytes
	 */
	uint8_t unicode_network_share_name_offset[ 4 ];

	/* The offset of the unicode device name
	 * Consists of 4 bytes
	 */
	uint8_t unicode_device_name_offset[ 4 ];
};

#if defined( __cplusplus )
}
#endif

#endif /* !defined( _LNK_NETWORK_SHARE_INFORMATION_H ) */

