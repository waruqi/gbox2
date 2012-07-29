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
#ifndef G2_SVG_WRITER_STYLE_H
#define G2_SVG_WRITER_STYLE_H

/* ///////////////////////////////////////////////////////////////////////
 * includes
 */
#include "prefix.h"

/* ///////////////////////////////////////////////////////////////////////
 * inlines
 */
static __tb_inline__ tb_void_t g2_svg_writer_style_fill(tb_gstream_t* gst, g2_svg_style_t* style)
{
	// fill: value
	if (style->fill.mode == G2_SVG_STYLE_PAINT_MODE_VALUE)
	{
		union __g2_c2p_t
		{
			g2_color_t c;
			g2_pixel_t p;

		}c2p;
		c2p.c = style->fill.color;
		tb_gstream_printf(gst, "fill:#%06x", c2p.c.a != 0xff? c2p.p : (c2p.p & 0x00ffffff));
	}
	// fill: none
	else if (style->fill.mode == G2_SVG_STYLE_PAINT_MODE_NONE)
		tb_gstream_printf(gst, "fill:none");
}
static __tb_inline__ tb_void_t g2_svg_writer_style_stroke(tb_gstream_t* gst, g2_svg_style_t* style)
{
	// init
	tb_size_t separator = 0;

	// stroke: value
	if (style->stroke.mode == G2_SVG_STYLE_PAINT_MODE_VALUE)
	{
		union __g2_c2p_t
		{
			g2_color_t c;
			g2_pixel_t p;

		}c2p;
		c2p.c = style->stroke.color;
		tb_gstream_printf(gst, "stroke:#%06x", c2p.c.a != 0xff? c2p.p : (c2p.p & 0x00ffffff));
		separator = 1;
	}
	// stroke: none
	else if (style->stroke.mode == G2_SVG_STYLE_PAINT_MODE_NONE)
	{
		tb_gstream_printf(gst, "stroke:none");
		separator = 1;
	}

	// stroke width
	if (g2_nz(style->width)) 
	{
		if (separator) tb_gstream_printf(gst, "; ");
		tb_gstream_printf(gst, "stroke-width:%f", g2_float_to_tb(style->width));
		separator = 1;
	}

	// stroke linecap
	static tb_char_t const* caps[] =
	{
		"butt"
	, 	"round"
	, 	"square"
	};
	if (style->cap && style->cap - 1 < tb_arrayn(caps)) 
	{
		if (separator) tb_gstream_printf(gst, "; ");
		tb_gstream_printf(gst, "stroke-linecap:%s", caps[style->cap - 1]);
		separator = 1;
	}

	// stroke linejoin
	static tb_char_t const* joins[] =
	{
		"miter"
	, 	"round"
	, 	"bevel"
	};
	if (style->join && style->join - 1 < tb_arrayn(joins)) 
	{
		if (separator) tb_gstream_printf(gst, "; ");
		tb_gstream_printf(gst, "stroke-linejoin:%s", joins[style->join - 1]);
		separator = 1;
	}
}
static __tb_inline__ tb_void_t g2_svg_writer_style(tb_gstream_t* gst, g2_svg_style_t* style)
{
	// check
	tb_assert(gst && style);

	// has style
	if (style->mode)
	{
		// enter
		tb_gstream_printf(gst, " style=\"");

		// fill?
		if (style->mode & G2_SVG_STYLE_MODE_FILL) g2_svg_writer_style_fill(gst, style);
		
		// separator
		if (style->mode == G2_SVG_STYLE_MODE_FILL_STROKE) tb_gstream_printf(gst, "; ");

		// stroke?
		if (style->mode & G2_SVG_STYLE_MODE_STROKE) g2_svg_writer_style_stroke(gst, style);

		// leave
		tb_gstream_printf(gst, "\"");
	}
}

#endif


