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
 * @file		style.h
 *
 */
#ifndef G2_SVG_PARSER_STYLE_H
#define G2_SVG_PARSER_STYLE_H

/* ///////////////////////////////////////////////////////////////////////
 * includes
 */
#include "prefix.h"
#include "float.h"
#include "separator.h"

/* ///////////////////////////////////////////////////////////////////////
 * inlines
 */
static __tb_inline__ tb_char_t const* g2_svg_parser_style_paint(tb_char_t const* p, g2_svg_style_paint_t* paint)
{
	if (*p == '#')
	{
		// init
		union __g2_p2c_t
		{
			g2_color_t c;
			g2_pixel_t p;

		}p2c;

		// skip '#'
		p++;

		// pixel: argb
		p2c.p = tb_s16tou32(p);

		// skip pixel
		tb_size_t n = 0;
		for (; tb_isdigit16(*p); p++, n++) ;

		// only three digits? expand it. e.g. #123 => #112233
		if (n == 3) p2c.p = (((p2c.p >> 8) & 0x0f) << 20) | (((p2c.p >> 8) & 0x0f) << 16) | (((p2c.p >> 4) & 0x0f) << 12) | (((p2c.p >> 4) & 0x0f) << 8) | ((p2c.p & 0x0f) << 4) | (p2c.p & 0x0f);

		// no alpha? opaque it
		if (!(p2c.p & 0xff000000)) p2c.p |= 0xff000000;

		// color
		paint->mode = G2_SVG_STYLE_PAINT_MODE_VALUE;
		paint->color = p2c.c;
	}
	else if (!tb_strnicmp(p, "none", 4)) 
	{
		paint->mode = G2_SVG_STYLE_PAINT_MODE_NONE;
		p += 4;
	}

	// ok
	return p;
}
static __tb_inline__ tb_char_t const* g2_svg_parser_style_fill(tb_char_t const* p, g2_svg_style_t* style)
{
	// skip space
	while (tb_isspace(*p)) p++;

	// mode
	style->mode |= G2_SVG_STYLE_MODE_FILL;

	// fill
	return g2_svg_parser_style_paint(p, &style->fill);
}
static __tb_inline__ tb_char_t const* g2_svg_parser_style_stroke(tb_char_t const* p, g2_svg_style_t* style)
{
	// skip space
	while (tb_isspace(*p)) p++;

	// mode
	style->mode |= G2_SVG_STYLE_MODE_STROKE;

	// stroke
	return g2_svg_parser_style_paint(p, &style->stroke);
}
static __tb_inline__ tb_char_t const* g2_svg_parser_style_stroke_width(tb_char_t const* p, g2_svg_style_t* style)
{
	// skip space
	while (tb_isspace(*p)) p++;

	// mode
	style->mode |= G2_SVG_STYLE_MODE_STROKE;

	// width
	return g2_svg_parser_float(p, &style->width);
}
static __tb_inline__ tb_char_t const* g2_svg_parser_style_stroke_linejoin(tb_char_t const* p, g2_svg_style_t* style)
{
	// skip space
	while (tb_isspace(*p)) p++;

	// mode
	style->mode |= G2_SVG_STYLE_MODE_STROKE;

	// join
	if (!tb_strnicmp(p, "miter", 5)) style->join = G2_SVG_STYLE_JOIN_MITER;
	else if (!tb_strnicmp(p, "round", 5)) style->join = G2_SVG_STYLE_JOIN_ROUND;
	else if (!tb_strnicmp(p, "bevel", 5)) style->join = G2_SVG_STYLE_JOIN_BEVEL;
	
	// skip join
	if (style->join) p += 5;

	// ok
	return p;
}
static __tb_inline__ tb_char_t const* g2_svg_parser_style(tb_char_t const* p, g2_svg_style_t* style)
{
	// check
	tb_assert(style);

	// done
	while (*p)
	{
		if (!tb_isspace(*p))
		{
			if (!tb_strnicmp(p, "fill:", 5))
				p = g2_svg_parser_style_fill(p + 5, style);
			else if (!tb_strnicmp(p, "stroke:", 7))
				p = g2_svg_parser_style_stroke(p + 7, style);
			else if (!tb_strnicmp(p, "stroke-width:", 13))
				p = g2_svg_parser_style_stroke_width(p + 13, style);
			else if (!tb_strnicmp(p, "stroke-linejoin:", 16))
				p = g2_svg_parser_style_stroke_linejoin(p + 16, style);
			else p++;
		}
		else p++;
	}
	return p;
}
#endif


