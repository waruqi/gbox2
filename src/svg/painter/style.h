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
#ifndef G2_SVG_PAINTER_STYLE_H
#define G2_SVG_PAINTER_STYLE_H

/* ///////////////////////////////////////////////////////////////////////
 * includes
 */
#include "prefix.h"

/* ///////////////////////////////////////////////////////////////////////
 * inlines
 */
static __tb_inline__ tb_void_t g2_svg_painter_style_fill(g2_svg_painter_t* painter, g2_svg_style_t const* style)
{
	// check
	tb_assert_and_check_return(painter->style);

	// has fill?
	tb_check_return(style->mode & G2_SVG_STYLE_MODE_FILL);

	// fill it
	switch (style->fill.mode)
	{
	case G2_SVG_STYLE_PAINT_MODE_VALUE:
		g2_style_color_set(painter->style, style->fill.color);
		break;
	case G2_SVG_STYLE_PAINT_MODE_URL:
	case G2_SVG_STYLE_PAINT_MODE_NONE:
	default:
		break;
	}
}
static __tb_inline__ tb_void_t g2_svg_painter_style_stroke(g2_svg_painter_t* painter, g2_svg_style_t const* style)
{
	tb_assert_and_check_return(painter->style);

	// has stroke?
	tb_check_return(style->mode & G2_SVG_STYLE_MODE_STROKE);

	// width
	if (g2_nz(style->width)) g2_style_width_set(painter->style, style->width);
	
	// join
	if (style->join) g2_style_join_set(painter->style, style->join);

	// join
	if (style->cap) g2_style_cap_set(painter->style, style->cap);

	// stroke it
	switch (style->stroke.mode)
	{
	case G2_SVG_STYLE_PAINT_MODE_VALUE:
		g2_style_color_set(painter->style, style->stroke.color);
		break;
	case G2_SVG_STYLE_PAINT_MODE_URL:
	case G2_SVG_STYLE_PAINT_MODE_NONE:
	default:
		break;
	}
}

#endif


