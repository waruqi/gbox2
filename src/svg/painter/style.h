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
	// no fill? next it
	tb_check_return_val(style->mode & G2_SVG_STYLE_MODE_FILL, TB_FALSE);

	// fill
	g2_style_clear(g2_style(painter->painter));
	g2_style_mode_set(g2_style(painter->painter), G2_STYLE_MODE_FILL);

	// fill it
	switch (style->fill.mode)
	{
	case G2_SVG_STYLE_PAINT_MODE_VALUE:
		g2_style_color_set(g2_style(painter->painter), style->fill.color);
		break;
	case G2_SVG_STYLE_PAINT_MODE_URL:
	default:
		return TB_FALSE;
	}

	// opacity
	if (style->fill.flag & G2_SVG_STYLE_PAINT_FLAG_HAS_OPACITY)
		g2_style_alpha_set(g2_style(painter->painter), (tb_byte_t)g2_float_to_long(style->fill.opacity * 256));

	// ok
	return TB_TRUE;
}
static __tb_inline__ tb_bool_t g2_svg_painter_style_stok(g2_svg_painter_t* painter, g2_svg_style_t const* style)
{
	// no stroke? next it
	tb_check_return_val(style->mode & G2_SVG_STYLE_MODE_STROKE, TB_FALSE);

	// stroke
	g2_style_clear(g2_style(painter->painter));
	g2_style_mode_set(g2_style(painter->painter), G2_STYLE_MODE_STROKE);

	// stroke it
	switch (style->stroke.mode)
	{
	case G2_SVG_STYLE_PAINT_MODE_VALUE:
		g2_style_color_set(g2_style(painter->painter), style->stroke.color);
		break;
	case G2_SVG_STYLE_PAINT_MODE_URL:
	default:
		return TB_FALSE;
	}

	// width
	if (g2_nz(style->width)) g2_style_width_set(g2_style(painter->painter), style->width);
	
	// join
	if (style->join) g2_style_join_set(g2_style(painter->painter), style->join);

	// join
	if (style->cap) g2_style_cap_set(g2_style(painter->painter), style->cap);

	// opacity
	if (style->stroke.flag & G2_SVG_STYLE_PAINT_FLAG_HAS_OPACITY)
		g2_style_alpha_set(g2_style(painter->painter), (tb_byte_t)g2_float_to_long(style->stroke.opacity * 256));

	// ok
	return TB_TRUE;
}
static __tb_inline__ tb_void_t g2_svg_painter_style_walk(g2_svg_style_t* applied, g2_svg_style_t const* style)
{
	// check
	tb_assert_and_check_return(applied && style);

	// has fill?
	if (style->mode & G2_SVG_STYLE_MODE_FILL)
	{
		// no inherit? fill it
		applied->mode |= G2_SVG_STYLE_MODE_FILL;
		if (!applied->fill.mode)
		{
			applied->fill.mode = style->fill.mode;
			switch (style->fill.mode)
			{
			case G2_SVG_STYLE_PAINT_MODE_VALUE:
				applied->fill.color = style->fill.color;
				break;
			case G2_SVG_STYLE_PAINT_MODE_URL:
				tb_pstring_strcpy(&applied->fill.url, &style->fill.url);
				break;
			default:
				break;
			}
		}

		// has opacity?
		if (!(applied->fill.flag & G2_SVG_STYLE_PAINT_FLAG_HAS_OPACITY) 
			&& style->fill.flag & G2_SVG_STYLE_PAINT_FLAG_HAS_OPACITY)
		{
			applied->fill.flag |= G2_SVG_STYLE_PAINT_FLAG_HAS_OPACITY;
			applied->fill.opacity = style->fill.opacity;
		}
	}

	// has stroke?
	if (style->mode & G2_SVG_STYLE_MODE_STROKE)
	{
		// no inherit? stroke it
		applied->mode |= G2_SVG_STYLE_MODE_STROKE;
		if (!applied->stroke.mode)
		{
			applied->stroke.mode = style->stroke.mode;
			switch (style->stroke.mode)
			{
			case G2_SVG_STYLE_PAINT_MODE_VALUE:
				applied->stroke.color = style->stroke.color;
				break;
			case G2_SVG_STYLE_PAINT_MODE_URL:
				tb_pstring_strcpy(&applied->stroke.url, &style->stroke.url);
				break;
			default:
				break;
			}
		}

		// cap
		if (!applied->cap) applied->cap = style->cap;

		// join
		if (!applied->join) applied->join = style->join;

		// width
		if (g2_ez(applied->width)) applied->width = style->width;

		// has opacity?
		if (!(applied->stroke.flag & G2_SVG_STYLE_PAINT_FLAG_HAS_OPACITY) 
			&& style->stroke.flag & G2_SVG_STYLE_PAINT_FLAG_HAS_OPACITY)
		{
			applied->stroke.flag |= G2_SVG_STYLE_PAINT_FLAG_HAS_OPACITY;
			applied->stroke.opacity = style->stroke.opacity;
		}
	}
}


#endif


