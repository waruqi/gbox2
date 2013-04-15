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
	// check
	tb_assert_and_check_return_val(style, tb_false);

	// clear
	tb_memset(style, 0, sizeof(g2_svg_style_t));

	// init
	style->mode 			= G2_SVG_STYLE_MODE_NONE;
	style->opacity 			= G2_ONE;

	// init fill
	style->fill.mode 		= G2_SVG_STYLE_PAINT_MODE_INHERIT;
	style->fill.flag 		= G2_SVG_STYLE_PAINT_FLAG_NONE;
	style->fill.color 		= G2_COLOR_BLACK;
	style->fill.opacity 	= G2_ONE;
	tb_pstring_init(&style->fill.url);

	// init stroke
	style->stok.mode 		= G2_SVG_STYLE_PAINT_MODE_INHERIT;
	style->stok.flag 		= G2_SVG_STYLE_PAINT_FLAG_NONE;
	style->stok.color 	= G2_COLOR_BLACK;
	style->stok.opacity 	= G2_ONE;
	style->join 			= G2_SVG_STYLE_JOIN_INHERIT;
	style->cap 				= G2_SVG_STYLE_CAP_INHERIT;
	style->width 			= 0;
	tb_pstring_init(&style->stok.url);

	// init font
	style->font.style 		= G2_SVG_STYLE_FONT_STYLE_INHERIT;
	style->font.weight 		= G2_SVG_STYLE_FONT_WEIGHT_INHERIT;
	tb_pstring_init(&style->font.family);

	// init text
	style->text.anchor 		= G2_SVG_STYLE_TEXT_ANCHOR_INHERIT;

	// init clippath
	style->clippath.mode 	= G2_SVG_STYLE_CLIPPATH_MODE_INHERIT;
	tb_pstring_init(&style->clippath.url);

	// ok
	return tb_true;
}
tb_void_t g2_svg_style_exit(g2_svg_style_t* style)
{
	if (style)
	{
		// exit fill
		tb_pstring_exit(&style->fill.url);

		// exit stroke
		tb_pstring_exit(&style->stok.url);

		// exit font
		tb_pstring_exit(&style->font.family);

		// exit clippath
		tb_pstring_exit(&style->clippath.url);
	}
}

