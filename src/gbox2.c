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
 * globals
 */
static tb_size_t 		g_quality = G2_QUALITY_LOW;

/* ///////////////////////////////////////////////////////////////////////
 * implementation
 */
tb_version_t const* g2_version()
{
	// init version
	static tb_version_t s_version = {0};
	if (!s_version.major)
	{
		s_version.major = G2_VERSION_MAJOR;
		s_version.minor = G2_VERSION_MINOR;
		s_version.alter = G2_VERSION_ALTER;
		s_version.build = G2_CONFIG_VERSION_BUILD;
	}

	return &s_version;
}
tb_size_t g2_quality()
{
	return tb_atomic_get(&g_quality);
}
tb_void_t g2_quality_set(tb_size_t quality)
{
	tb_atomic_set(&g_quality, quality);
}

