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
	// init
	tb_size_t separator = 0;

	// fill: value
	if (style->fill.mode == G2_SVG_STYLE_PAINT_MODE_VALUE)
	{
		g2_pixel_t pixel = g2_color_pixel(style->fill.color);
		tb_gstream_printf(gst, "fill:#%06x", style->fill.color.a != 0xff? pixel : (pixel & 0x00ffffff));
		separator = 1;
	}
	// fill: url
	else if (style->fill.mode == G2_SVG_STYLE_PAINT_MODE_URL)
	{
		tb_gstream_printf(gst, "fill:url(%s)", tb_pstring_cstr(&style->fill.url));
		separator = 1;
	}
	// fill: none
	else if (style->fill.mode == G2_SVG_STYLE_PAINT_MODE_NONE)
	{
		tb_gstream_printf(gst, "fill:none");
		separator = 1;
	}

	// fill-opacity
	if (style->fill.flag & G2_SVG_STYLE_PAINT_FLAG_HAS_OPACITY) 
	{
		if (separator) tb_gstream_printf(gst, "; ");
		tb_gstream_printf(gst, "fill-opacity:%f", g2_float_to_tb(style->fill.opacity));
		separator = 1;
	}
}
static __tb_inline__ tb_void_t g2_svg_writer_style_stroke(tb_gstream_t* gst, g2_svg_style_t* style)
{
	// init
	tb_size_t separator = 0;

	// stroke: value
	if (style->stroke.mode == G2_SVG_STYLE_PAINT_MODE_VALUE)
	{
		g2_pixel_t pixel = g2_color_pixel(style->stroke.color);
		tb_gstream_printf(gst, "stroke:#%06x", style->stroke.color.a != 0xff? pixel : (pixel & 0x00ffffff));
		separator = 1;
	}
	// stroke: url
	else if (style->stroke.mode == G2_SVG_STYLE_PAINT_MODE_URL)
		tb_gstream_printf(gst, "stroke:url(%s)", tb_pstring_cstr(&style->stroke.url));
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

	// stroke-opacity
	if (style->stroke.flag & G2_SVG_STYLE_PAINT_FLAG_HAS_OPACITY) 
	{
		if (separator) tb_gstream_printf(gst, "; ");
		tb_gstream_printf(gst, "stroke-opacity:%f", g2_float_to_tb(style->stroke.opacity));
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


