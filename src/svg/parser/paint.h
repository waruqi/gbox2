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
 * @file		paint.h
 *
 */
#ifndef G2_SVG_PARSER_PAINT_H
#define G2_SVG_PARSER_PAINT_H

/* ///////////////////////////////////////////////////////////////////////
 * includes
 */
#include "prefix.h"
#include "float.h"
#include "separator.h"

/* ///////////////////////////////////////////////////////////////////////
 * inlines
 */
static __tb_inline__ tb_char_t const* g2_svg_parser_paint_fill_pixel(tb_char_t const* p, tb_handle_t style)
{
	// init
	union __g2_p2c_t
	{
		g2_color_t c;
		g2_pixel_t p;

	}p2c;

	// skip '#'
	p++;

	// skip space
	while (*p && tb_isspace(*p)) p++;

	// pixel
	p2c.p = tb_s16tou32(p);

	// skip pixel
	while (*p && tb_isdigit16(*p)) p++;

	// set color
	g2_style_color_set(style, p2c.c);

	// trace
	tb_trace_impl("color: %#x", p2c.p);

	// ok
	return p;
}
static __tb_inline__ tb_char_t const* g2_svg_parser_paint_fill(tb_char_t const* p, tb_handle_t style)
{
	// check
	tb_assert(style);

	// done
	while (*p)
	{
		if (!tb_isspace(*p))
		{
			if (*p == '#')
				p = g2_svg_parser_paint_fill_pixel(p, style);
			else p++;
		}
		else p++;
	}
	return p;
}

#endif


