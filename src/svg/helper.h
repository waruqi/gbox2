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
 * @file		helper.h
 *
 */
#ifndef G2_SVG_HELPER_H
#define G2_SVG_HELPER_H

/* ///////////////////////////////////////////////////////////////////////
 * includes
 */
#include "prefix.h"

/* ///////////////////////////////////////////////////////////////////////
 * inlines
 */
static __tb_inline__ tb_char_t const* g2_svg_skip_float(tb_char_t const* p)
{
	// skip sign
	if (*p == '-') p++;

	// skip '0'
	while (*p == '0') p++;
	
	// skip float
	tb_size_t bdecimal = 0;
	while (*p)
	{
		// is decimal?
		if (*p == '.')
		{
			if (!bdecimal) 
			{
				bdecimal = 1;
				p++;
				continue ;
			}
			else break;
		}

		// skip digit
		if (!tb_isdigit(*p)) break;

		// next
		p++;
	}

	// ok
	return p;
}
static __tb_inline__ tb_char_t const* g2_svg_skip_separator(tb_char_t const* p)
{
	while (*p && (tb_isspace(*p) || *p == ',')) p++;
	return p;
}

#endif


