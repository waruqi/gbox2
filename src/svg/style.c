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
 * @file		style.c
 *
 */

/* ///////////////////////////////////////////////////////////////////////
 * includes
 */
#include "style.h"

/* ///////////////////////////////////////////////////////////////////////
 * implementation
 */
tb_bool_t g2_svg_style_init(g2_svg_style_t* style)
{
	tb_assert_and_check_return_val(style, TB_FALSE);

	// init style
	style->mode 			= G2_SVG_STYLE_MODE_NONE;
	style->join 			= G2_SVG_STYLE_JOIN_INHERIT;
	style->cap 				= G2_SVG_STYLE_CAP_INHERIT;
	style->width 			= 0;
	style->fill.mode 		= G2_SVG_STYLE_PAINT_MODE_INHERIT;
	style->fill.flag 		= G2_SVG_STYLE_PAINT_FLAG_NONE;
	style->fill.color 		= G2_COLOR_BLACK;
	style->stroke.mode 		= G2_SVG_STYLE_PAINT_MODE_INHERIT;
	style->stroke.flag 		= G2_SVG_STYLE_PAINT_FLAG_NONE;
	style->stroke.color 	= G2_COLOR_BLACK;

	// init url
	tb_pstring_init(&style->fill.url);
	tb_pstring_init(&style->stroke.url);
	tb_pstring_init(&style->clippath.url);

	return TB_TRUE;
}
tb_void_t g2_svg_style_exit(g2_svg_style_t* style)
{
	if (style)
	{
		// exit url
		tb_pstring_exit(&style->fill.url);
		tb_pstring_exit(&style->stroke.url);
		tb_pstring_exit(&style->clippath.url);
	}
}

