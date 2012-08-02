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
static __tb_inline__ tb_bool_t g2_svg_painter_style_fill(g2_svg_painter_t* painter, g2_svg_style_t const* style)
{
	// has fill?
	tb_check_return_val(style->mode & G2_SVG_STYLE_MODE_FILL, TB_FALSE);

	// init
	tb_size_t separator = 0;

	// fill: value
	switch (style->fill.mode)
	{
	case G2_SVG_STYLE_PAINT_MODE_VALUE:
		{
		}
	case G2_SVG_STYLE_PAINT_MODE_URL:
	case G2_SVG_STYLE_PAINT_MODE_NONE:
	default:
		break;
	}

	return TB_FALSE;
}
static __tb_inline__ tb_bool_t g2_svg_painter_style_stroke(g2_svg_painter_t* painter, g2_svg_style_t const* style)
{

	return TB_FALSE;
}

#endif


