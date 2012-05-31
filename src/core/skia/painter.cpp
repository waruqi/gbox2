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
 * @file		painter.cpp
 *
 */

/* ///////////////////////////////////////////////////////////////////////
 * includes
 */
#include "prefix.h"

/* ///////////////////////////////////////////////////////////////////////
 * types
 */

// the painter type
typedef struct __g2_skia_painter_t
{
	// the surface
	SkBitmap* 			surface;

	// the canvas
	SkCanvas* 			canvas;

	// the style
	SkPaint* 			style_def;
	SkPaint* 			style_usr;

}g2_skia_painter_t;


/* ///////////////////////////////////////////////////////////////////////
 * implementation
 */
static tb_void_t g2_skia_exit(tb_handle_t painter)
{
	g2_skia_painter_t* spainter = static_cast<g2_skia_painter_t*>(painter);
	tb_assert_and_check_return(spainter);

	// free style
	if (spainter->style_def) delete spainter->style_def;

	// free canvas
	if (spainter->canvas) delete spainter->canvas;

	// free it
	delete spainter;
}
static tb_handle_t g2_skia_init(tb_handle_t surface)
{
	// check
	tb_assert_and_check_return_val(surface, TB_NULL);

	// alloc
	g2_skia_painter_t* spainter = new g2_skia_painter_t;
	tb_assert_and_check_return_val(spainter, TB_NULL);

	// init surface
	spainter->surface = static_cast<SkBitmap*>(surface);

	// init canvas
	spainter->canvas = new SkCanvas(*spainter->surface);
	tb_assert_and_check_goto(spainter->canvas, fail);
	spainter->canvas->resetMatrix();

	// init style
	spainter->style_def = new SkPaint();
	spainter->style_usr = spainter->style_def;
	tb_assert_and_check_goto(spainter->style_def, fail);

	// ok
	return spainter;

fail:
	if (spainter) g2_skia_exit(spainter);
	return TB_NULL;
}
static tb_void_t g2_skia_save(tb_handle_t painter)
{
	g2_skia_painter_t* spainter = static_cast<g2_skia_painter_t*>(painter);
	tb_assert_and_check_return(spainter && spainter->canvas);

	spainter->canvas->save();
}
static tb_void_t g2_skia_load(tb_handle_t painter)
{	
	g2_skia_painter_t* spainter = static_cast<g2_skia_painter_t*>(painter);
	tb_assert_and_check_return(spainter && spainter->canvas);

	spainter->canvas->restore();
}
static tb_handle_t g2_skia_style(tb_handle_t painter)
{
	g2_skia_painter_t* spainter = static_cast<g2_skia_painter_t*>(painter);
	tb_assert_and_check_return_val(spainter, TB_NULL);

	return spainter->style_usr;
}
static tb_void_t g2_skia_style_set(tb_handle_t painter, tb_handle_t style)
{
	g2_skia_painter_t* spainter = static_cast<g2_skia_painter_t*>(painter);
	tb_assert_and_check_return(spainter);

	spainter->style_usr = style? static_cast<SkPaint*>(style) : spainter->style_def;
}
static tb_handle_t g2_skia_clipper(tb_handle_t painter, tb_handle_t clipper)
{
}
static tb_handle_t g2_skia_path(tb_handle_t painter, tb_handle_t path)
{
}
static tb_void_t g2_skia_clear(tb_handle_t painter)
{
}
static tb_void_t g2_skia_draw(tb_handle_t painter)
{
}
static tb_void_t g2_skia_draw_arc(tb_handle_t painter, g2_arc_t const* arc)
{
}
static tb_void_t g2_skia_draw_pie(tb_handle_t painter, g2_pie_t const* pie)
{
}
static tb_void_t g2_skia_draw_rect(tb_handle_t painter, g2_rect_t const* rect)
{
}
static tb_void_t g2_skia_draw_line(tb_handle_t painter, g2_line_t const* line)
{
}
static tb_void_t g2_skia_draw_chord(tb_handle_t painter, g2_chord_t const* chord)
{
}
static tb_void_t g2_skia_draw_curve1(tb_handle_t painter, g2_curve1_t const* curve1)
{
}
static tb_void_t g2_skia_draw_curve2(tb_handle_t painter, g2_curve2_t const* curve2)
{
}
static tb_void_t g2_skia_draw_circle(tb_handle_t painter, g2_circle_t const* circle)
{
}
static tb_void_t g2_skia_draw_ellipse(tb_handle_t painter, g2_ellipse_t const* ellipse)
{
}
static tb_void_t g2_skia_draw_polygon(tb_handle_t painter, g2_polygon_t const* polygon)
{
}
static tb_void_t g2_skia_draw_triangle(tb_handle_t painter, g2_triangle_t const* triangle)
{
}

/* ///////////////////////////////////////////////////////////////////////
 * interfaces
 */

extern "C"
{
	tb_handle_t g2_init(tb_handle_t surface)
	{
		return g2_skia_init(surface);
	}
	tb_void_t g2_exit(tb_handle_t painter)
	{
		g2_skia_exit(painter);
	}
	tb_void_t g2_save(tb_handle_t painter)
	{
		g2_skia_save(painter);
	}
	tb_void_t g2_load(tb_handle_t painter)
	{
		g2_skia_load(painter);
	}
	tb_handle_t g2_style(tb_handle_t painter)
	{
		return g2_skia_style(painter);
	}
	tb_void_t g2_style_set(tb_handle_t painter, tb_handle_t style)
	{
		g2_skia_style_set(painter, style);
	}
	tb_handle_t g2_clipper(tb_handle_t painter, tb_handle_t clipper)
	{
		return g2_skia_clipper(painter, clipper);
	}
	tb_handle_t g2_path(tb_handle_t painter, tb_handle_t path)
	{
		return g2_skia_path(painter, path);
	}
	tb_void_t g2_clear(tb_handle_t painter)
	{
		g2_skia_clear(painter);
	}
	tb_void_t g2_draw(tb_handle_t painter)
	{
		g2_skia_draw(painter);
	}
	tb_void_t g2_draw_arc(tb_handle_t painter, g2_arc_t const* arc)
	{
		g2_skia_draw_arc(painter, arc);
	}
	tb_void_t g2_draw_pie(tb_handle_t painter, g2_pie_t const* pie)
	{
		g2_skia_draw_pie(painter, pie);
	}
	tb_void_t g2_draw_rect(tb_handle_t painter, g2_rect_t const* rect)
	{
		g2_skia_draw_rect(painter, rect);
	}
	tb_void_t g2_draw_line(tb_handle_t painter, g2_line_t const* line)
	{
		g2_skia_draw_line(painter, line);
	}
	tb_void_t g2_draw_chord(tb_handle_t painter, g2_chord_t const* chord)
	{
		g2_skia_draw_chord(painter, chord);
	}
	tb_void_t g2_draw_curve1(tb_handle_t painter, g2_curve1_t const* curve1)
	{
		g2_skia_draw_curve1(painter, curve1);
	}
	tb_void_t g2_draw_curve2(tb_handle_t painter, g2_curve2_t const* curve2)
	{
		g2_skia_draw_curve2(painter, curve2);
	}
	tb_void_t g2_draw_circle(tb_handle_t painter, g2_circle_t const* circle)
	{
		g2_skia_draw_circle(painter, circle);
	}
	tb_void_t g2_draw_ellipse(tb_handle_t painter, g2_ellipse_t const* ellipse)
	{
		g2_skia_draw_ellipse(painter, ellipse);
	}
	tb_void_t g2_draw_polygon(tb_handle_t painter, g2_polygon_t const* polygon)
	{
		g2_skia_draw_polygon(painter, polygon);
	}
	tb_void_t g2_draw_triangle(tb_handle_t painter, g2_triangle_t const* triangle)
	{
		g2_skia_draw_triangle(painter, triangle);
	}
}

