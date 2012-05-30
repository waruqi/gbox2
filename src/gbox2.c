/*!The Graphic 2D Box Library
 * 
 * GBox2 is free software; you can redistribute it and/or modify
 * it under the terms of the GNU Lesser General Public License as published by
 * the Free Software Foundation; either version 2.1 of the License, or
 * (at your option) any later version.
 * 
 * GBox2 is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU Lesser General Public License for more details.
 * 
 * You should have received a copy of the GNU Lesser General Public License
 * along with GBox2; 
 * If not, see <a href="http://www.gnu.org/licenses/"> http://www.gnu.org/licenses/</a>
 * 
 * Copyright (C) 2009 - 2012, ruki All rights reserved.
 *
 * @author		ruki
 * @file		gbox2.c
 *
 */

/* ///////////////////////////////////////////////////////////////////////
 * includes
 */
#include "gbox2.h"

/* ///////////////////////////////////////////////////////////////////////
 * implementation
 */

tb_char_t const* g2_version()
{
	static tb_char_t version_data[32] = {0};
	static tb_size_t version_size = 0;
	
	if (!version_size)
	{
		version_size = tb_snprintf(version_data, 32, "gbox2-v%u.%u.%u", G2_VERSION_MAJOR, G2_VERSION_MINOR, G2_VERSION_ALTER);
		version_data[version_size] = '\0';
	}
	return version_data;
}
