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
 * @file		stok.c
 *
 */

/* ///////////////////////////////////////////////////////////////////////
 * trace
 */
#define TB_TRACE_IMPL_TAG 		"stok"

/* ///////////////////////////////////////////////////////////////////////
 * includes
 */
#include "stok.h"
#include "fill.h"
#include "draw.h"

/* ///////////////////////////////////////////////////////////////////////
 * interfaces
 */
tb_void_t g2_gl_stok_arc(g2_gl_painter_t* painter, g2_arc_t const* arc)
{
	// the style
	tb_handle_t style = g2_style(painter);
	tb_assert_and_check_return(style);

	// the width
	g2_float_t width = g2_style_width(style);

	// width > 1?
	if (g2_b1(width))
	{
		// done
		tb_size_t cap = g2_style_cap(style);
		switch (cap)
		{
		case G2_STYLE_CAP_ROUND:
			{
			}
			break;
		case G2_STYLE_CAP_BUTT:
			{
			}
			break;
		case G2_STYLE_CAP_SQUARE:
		default:
			{
			}
			break;
		}
	}
	// width == 1?
	else if (g2_e1(width))
		g2_gl_draw_arc(painter, G2_STYLE_MODE_STOK, arc);
}
tb_void_t g2_gl_stok_line(g2_gl_painter_t* painter, g2_line_t const* line)
{
	// the style
	tb_handle_t style = g2_style(painter);
	tb_assert_and_check_return(style);

	// the width
	g2_float_t width = g2_style_width(style);

	// width > 1?
	if (g2_b1(width))
	{
		// done
		tb_size_t cap = g2_style_cap(style);
		switch (cap)
		{
		case G2_STYLE_CAP_ROUND:
			{
			}
			break;
		case G2_STYLE_CAP_BUTT:
			{
			}
			break;
		case G2_STYLE_CAP_SQUARE:
		default:
			{
			}
			break;
		}
	}
	// width == 1?
	else if (g2_e1(width))
		g2_gl_draw_line(painter, G2_STYLE_MODE_STOK, line);
}
tb_void_t g2_gl_stok_rect(g2_gl_painter_t* painter, g2_rect_t const* rect)
{
	// the style
	tb_handle_t style = g2_style(painter);
	tb_assert_and_check_return(style);

	// the width
	g2_float_t width = g2_style_width(style);

	// width > 1?
	if (g2_b1(width))
	{
		// done
		tb_size_t cap = g2_style_cap(style);
		switch (cap)
		{
		case G2_STYLE_CAP_ROUND:
			{
			}
			break;
		case G2_STYLE_CAP_BUTT:
			{
			}
			break;
		case G2_STYLE_CAP_SQUARE:
		default:
			{
			}
			break;
		}
	}
	// width == 1?
	else if (g2_e1(width))
		g2_gl_draw_rect(painter, G2_STYLE_MODE_STOK, rect);
}
tb_void_t g2_gl_stok_path(g2_gl_painter_t* painter, g2_gl_path_t const* path)
{
	// the style
	tb_handle_t style = g2_style(painter);
	tb_assert_and_check_return(style);

	// the width
	g2_float_t width = g2_style_width(style);

	// width > 1?
	if (g2_b1(width))
	{
		// done
		tb_size_t cap = g2_style_cap(style);
		switch (cap)
		{
		case G2_STYLE_CAP_ROUND:
			{
			}
			break;
		case G2_STYLE_CAP_BUTT:
			{
			}
			break;
		case G2_STYLE_CAP_SQUARE:
		default:
			{
			}
			break;
		}
	}
	// width == 1?
	else if (g2_e1(width))
		g2_gl_draw_path(painter, G2_STYLE_MODE_STOK, path);
}
tb_void_t g2_gl_stok_point(g2_gl_painter_t* painter, g2_point_t const* point)
{
	// the style
	tb_handle_t style = g2_style(painter);
	tb_assert_and_check_return(style);

	// the width
	g2_float_t width = g2_style_width(style);

	// width > 1?
	if (g2_b1(width))
	{
		// done
		tb_size_t cap = g2_style_cap(style);
		switch (cap)
		{
		case G2_STYLE_CAP_ROUND:
			{
				// init circle
				g2_circle_t circle;
				circle.c.x = point->x;
				circle.c.y = point->y;
				circle.r = g2_rsh(width, 1);

				// fill circle
				g2_save_style(painter);
				g2_mode(painter, G2_STYLE_MODE_FILL);
				g2_gl_fill_circle(painter, &circle);
				g2_load_style(painter);
			}
			break;
		case G2_STYLE_CAP_BUTT:
		case G2_STYLE_CAP_SQUARE:
		default:
			{
				// init rect
				g2_rect_t rect;
				rect.x = point->x - g2_rsh(width, 1);
				rect.y = point->y - g2_rsh(width, 1);
				rect.w = width;
				rect.h = width;
			
				// fill rect
				g2_save_style(painter);
				g2_mode(painter, G2_STYLE_MODE_FILL);
				g2_gl_fill_rect(painter, &rect);
				g2_load_style(painter);
			}
			break;
		}
	}
	// width == 1?
	else if (g2_e1(width))
		g2_gl_draw_point(painter, G2_STYLE_MODE_STOK, point);
}
tb_void_t g2_gl_stok_circle(g2_gl_painter_t* painter, g2_circle_t const* circle)
{
	// the style
	tb_handle_t style = g2_style(painter);
	tb_assert_and_check_return(style);

	// the width
	g2_float_t width = g2_style_width(style);

	// width > 1?
	if (g2_b1(width))
	{
		// done
		tb_size_t cap = g2_style_cap(style);
		switch (cap)
		{
		case G2_STYLE_CAP_ROUND:
			{
			}
			break;
		case G2_STYLE_CAP_BUTT:
			{
			}
			break;
		case G2_STYLE_CAP_SQUARE:
		default:
			{
			}
			break;
		}
	}
	// width == 1?
	else if (g2_e1(width))
		g2_gl_draw_circle(painter, G2_STYLE_MODE_STOK, circle);
}
tb_void_t g2_gl_stok_ellipse(g2_gl_painter_t* painter, g2_ellipse_t const* ellipse)
{	
	// the style
	tb_handle_t style = g2_style(painter);
	tb_assert_and_check_return(style);

	// the width
	g2_float_t width = g2_style_width(style);

	// width > 1?
	if (g2_b1(width))
	{
		// done
		tb_size_t cap = g2_style_cap(style);
		switch (cap)
		{
		case G2_STYLE_CAP_ROUND:
			{
			}
			break;
		case G2_STYLE_CAP_BUTT:
			{
			}
			break;
		case G2_STYLE_CAP_SQUARE:
		default:
			{
			}
			break;
		}
	}
	// width == 1?
	else if (g2_e1(width))
		g2_gl_draw_ellipse(painter, G2_STYLE_MODE_STOK, ellipse);
}
tb_void_t g2_gl_stok_triangle(g2_gl_painter_t* painter, g2_triangle_t const* triangle)
{
	// the style
	tb_handle_t style = g2_style(painter);
	tb_assert_and_check_return(style);

	// the width
	g2_float_t width = g2_style_width(style);

	// width > 1?
	if (g2_b1(width))
	{
		// done
		tb_size_t cap = g2_style_cap(style);
		switch (cap)
		{
		case G2_STYLE_CAP_ROUND:
			{
			}
			break;
		case G2_STYLE_CAP_BUTT:
			{
			}
			break;
		case G2_STYLE_CAP_SQUARE:
		default:
			{
			}
			break;
		}
	}
	// width == 1?
	else if (g2_e1(width))
		g2_gl_draw_triangle(painter, G2_STYLE_MODE_STOK, triangle);
}
