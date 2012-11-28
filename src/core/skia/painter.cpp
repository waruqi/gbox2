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
#include "path.h"

/* ///////////////////////////////////////////////////////////////////////
 * macros
 */

#ifdef SK_SCALAR_IS_FLOAT
# 	define kMatrix22Elem 					SK_Scalar1
#else
# 	define kMatrix22Elem 					SK_Fract1
#endif

#ifdef TB_CONFIG_BINARY_SMALL
# 	define G2_SKIA_STACK_GROW 				(32)
# 	define G2_SKIA_CACHE_SIZE 				(4)
#else
# 	define G2_SKIA_STACK_GROW 				(64)
# 	define G2_SKIA_CACHE_SIZE 				(8)
#endif


/* ///////////////////////////////////////////////////////////////////////
 * types
 */

// the painter type
typedef struct __g2_skia_painter_t
{
	// the context
	tb_handle_t 		context;

	// the canvas
	SkCanvas* 			canvas;

	// the matrix
	g2_matrix_t 		matrix;
	tb_stack_t* 		matrix_stack;

	// the style
	SkPaint* 			style;
	tb_stack_t* 		style_stack;
	tb_stack_t* 		style_cache;

}g2_skia_painter_t;

/* ///////////////////////////////////////////////////////////////////////
 * helper
 */
static __tb_inline__ tb_void_t g2_skia_matrix_update(g2_skia_painter_t* spainter)
{
	SkMatrix mx;
	g2_matrix_t const* matrix = &spainter->matrix;
	mx.setAll( 	matrix->sx, matrix->kx, matrix->tx
			, 	matrix->ky, matrix->sy, matrix->ty
			, 	0, 0, kMatrix22Elem);
	spainter->canvas->setMatrix(mx);
}
static tb_bool_t g2_skia_style_stack_item_free(tb_stack_t* stack, tb_pointer_t* item, tb_bool_t* bdel, tb_pointer_t data)
{
	tb_assert_and_check_return_val(stack && bdel, TB_FALSE);

	// free style item
	if (item) 
	{
		tb_handle_t style = (tb_handle_t)*item;
		if (style) g2_style_exit(style);
		*item = TB_NULL;
	}

	// ok
	return TB_TRUE;
}

/* ///////////////////////////////////////////////////////////////////////
 * implementation
 */
static tb_void_t g2_skia_exit(tb_handle_t painter)
{
	g2_skia_painter_t* spainter = static_cast<g2_skia_painter_t*>(painter);
	tb_assert_and_check_return(spainter);

	// exit matrix stack
	if (spainter->matrix_stack) tb_stack_exit(spainter->matrix_stack);
	spainter->matrix_stack = TB_NULL;

	// exit style
	if (spainter->style) g2_style_exit(spainter->style);
	spainter->style = TB_NULL;

	// exit style cache
	if (spainter->style_cache) 
	{
		tb_stack_walk(spainter->style_cache, g2_skia_style_stack_item_free, TB_NULL);
		tb_stack_exit(spainter->style_cache);
	}
	spainter->style_cache = TB_NULL;
	
	// exit style stack
	if (spainter->style_stack) 
	{
		tb_stack_walk(spainter->style_stack, g2_skia_style_stack_item_free, TB_NULL);
		tb_stack_exit(spainter->style_stack);
	}
	spainter->style_stack = TB_NULL;

	// exit canvas
	if (spainter->canvas) delete spainter->canvas;
	spainter->canvas = TB_NULL;

	// exit it
	tb_free(spainter);
}
static tb_handle_t g2_skia_init(tb_handle_t context)
{
	// check
	tb_assert_and_check_return_val(context, TB_NULL);

	// init variables
	tb_size_t i = 0;

	// init surface
	SkBitmap const* surface = static_cast<SkBitmap const*>(g2_context_surface(context));
	tb_assert_and_check_return_val(surface, TB_NULL);

	// alloc
	g2_skia_painter_t* spainter = (g2_skia_painter_t*)tb_malloc0(sizeof(g2_skia_painter_t));
	tb_assert_and_check_return_val(spainter, TB_NULL);

	// init context
	spainter->context = context;
	
	// init canvas
	spainter->canvas = new SkCanvas(*surface);
	tb_assert_and_check_goto(spainter->canvas, fail);
	spainter->canvas->resetMatrix();

	// init matrix
	g2_matrix_clear(&spainter->matrix);

	// init matrix stack
	spainter->matrix_stack = tb_stack_init(G2_SKIA_STACK_GROW, tb_item_func_ifm(sizeof(g2_matrix_t), TB_NULL, TB_NULL));
	tb_assert_and_check_goto(spainter->matrix_stack, fail);

	// init style
	spainter->style = static_cast<SkPaint*>(g2_style_init());
	tb_assert_and_check_goto(spainter->style, fail);

	// init style stack
	spainter->style_stack = tb_stack_init(G2_SKIA_STACK_GROW, tb_item_func_ptr());
	tb_assert_and_check_goto(spainter->style_stack, fail);

	// init style cache
	spainter->style_cache = tb_stack_init(G2_SKIA_CACHE_SIZE, tb_item_func_ptr());
	tb_assert_and_check_goto(spainter->style_cache, fail);
	for (i = 0; i < G2_SKIA_CACHE_SIZE; i++)
	{
		// init
		tb_handle_t style = g2_style_init();
		tb_assert_and_check_goto(style, fail);

		// put
		tb_stack_put(spainter->style_cache, style);
	}

	// ok
	return spainter;

fail:
	if (spainter) g2_skia_exit(spainter);
	return TB_NULL;
}
static tb_size_t g2_skia_pixfmt(tb_handle_t painter)
{
	g2_skia_painter_t* spainter = static_cast<g2_skia_painter_t*>(painter);
	tb_assert_and_check_return_val(spainter && spainter->context, G2_PIXFMT_NONE);

	return g2_bitmap_pixfmt(spainter->context);
}
static tb_handle_t g2_skia_context(tb_handle_t painter)
{
	g2_skia_painter_t* spainter = static_cast<g2_skia_painter_t*>(painter);
	tb_assert_and_check_return_val(spainter, TB_NULL);

	return spainter->context;
}
static tb_handle_t g2_skia_style(tb_handle_t painter)
{
	g2_skia_painter_t* spainter = static_cast<g2_skia_painter_t*>(painter);
	tb_assert_and_check_return_val(spainter, TB_NULL);

	return spainter->style;
}
static tb_handle_t g2_skia_style_save(tb_handle_t painter)
{
	g2_skia_painter_t* spainter = static_cast<g2_skia_painter_t*>(painter);
	tb_assert_and_check_return_val(spainter && spainter->style_cache && spainter->style_stack, TB_NULL);

	// init a new style from cache first
	tb_handle_t style = TB_NULL;
	if (tb_stack_size(spainter->style_cache))
	{
		// get
		style = (tb_handle_t)tb_stack_top(spainter->style_cache);
		tb_assert_and_check_return_val(spainter->style_cache, TB_NULL);

		// pop
		tb_stack_pop(spainter->style_cache);
	}
	// init a new style
	else style = g2_style_init();
	tb_assert_and_check_return_val(style, TB_NULL);

	// save the old style
	tb_stack_put(spainter->style_stack, spainter->style);

	// copy the new style
	g2_style_copy(style, spainter->style);
	spainter->style = (SkPaint*)style;

	// ok
	return spainter->style;
}
static tb_void_t g2_skia_style_load(tb_handle_t painter)
{
	g2_skia_painter_t* spainter = static_cast<g2_skia_painter_t*>(painter);
	tb_assert_and_check_return(spainter && spainter->style_cache && spainter->style_stack);

	// load the top style
	tb_handle_t style = (tb_handle_t)tb_stack_top(spainter->style_stack);
	tb_assert_and_check_return(style);
	tb_stack_pop(spainter->style_stack);

	// free style to cache first
	if (spainter->style && tb_stack_size(spainter->style_cache) < G2_SKIA_CACHE_SIZE)
		tb_stack_put(spainter->style_cache, spainter->style);
	// free style
	else g2_style_exit(spainter->style);

	// copy the top style
	spainter->style = (SkPaint*)style;
}
static g2_matrix_t* g2_skia_matrix(tb_handle_t painter)
{
	g2_skia_painter_t* spainter = static_cast<g2_skia_painter_t*>(painter);
	tb_assert_and_check_return_val(spainter, TB_NULL);

	return &spainter->matrix;
}
static g2_matrix_t* g2_skia_matrix_save(tb_handle_t painter)
{
	g2_skia_painter_t* spainter = static_cast<g2_skia_painter_t*>(painter);
	tb_assert_and_check_return_val(spainter && spainter->matrix_stack, TB_NULL);

	// save matrix
	tb_stack_put(spainter->matrix_stack, &spainter->matrix);

	// ok
	return &spainter->matrix;
}
static tb_void_t g2_skia_matrix_load(tb_handle_t painter)
{
	g2_skia_painter_t* spainter = static_cast<g2_skia_painter_t*>(painter);
	tb_assert_and_check_return(spainter && spainter->matrix_stack);

	// init matrix
	g2_matrix_t const* matrix = (g2_matrix_t const*)tb_stack_top(spainter->matrix_stack);
	tb_assert_and_check_return(matrix);

	// load matrix
	spainter->matrix = *matrix;

	// pop it
	tb_stack_pop(spainter->matrix_stack);
}
static tb_handle_t g2_skia_clipper(tb_handle_t painter)
{
	g2_skia_painter_t* spainter = static_cast<g2_skia_painter_t*>(painter);
	tb_assert_and_check_return_val(spainter, TB_NULL);

	tb_trace_noimpl();
	return TB_NULL;
}
static tb_handle_t g2_skia_clipper_save(tb_handle_t painter)
{
	g2_skia_painter_t* spainter = static_cast<g2_skia_painter_t*>(painter);
	tb_assert_and_check_return_val(spainter, TB_NULL);

	tb_trace_noimpl();
	return TB_NULL;
}
static tb_void_t g2_skia_clipper_load(tb_handle_t painter)
{
	g2_skia_painter_t* spainter = static_cast<g2_skia_painter_t*>(painter);
	tb_assert_and_check_return(spainter);

	tb_trace_noimpl();
}
static tb_void_t g2_skia_draw_clear(tb_handle_t painter, g2_color_t color)
{
	g2_skia_painter_t* spainter = static_cast<g2_skia_painter_t*>(painter);
	tb_assert_and_check_return(spainter && spainter->canvas);

	spainter->canvas->clear(g2_skia_color_to_sk(color));
}
static tb_void_t g2_skia_draw_path(tb_handle_t painter, tb_handle_t path)
{
	g2_skia_painter_t* spainter = static_cast<g2_skia_painter_t*>(painter);
	tb_assert_and_check_return(spainter && spainter->canvas && spainter->style && path);

	// update matrix
	g2_skia_matrix_update(spainter);

	// draw
	spainter->canvas->drawPath(*((G2SkiaPath const*)path), *spainter->style);
}
static tb_void_t g2_skia_draw_arc(tb_handle_t painter, g2_arc_t const* arc)
{
	g2_skia_painter_t* spainter = static_cast<g2_skia_painter_t*>(painter);
	tb_assert_and_check_return(spainter && spainter->canvas && spainter->style && arc);

	// update matrix
	g2_skia_matrix_update(spainter);

	// draw
	spainter->canvas->drawArc(SkRect::MakeXYWH(arc->c0.x - arc->rx, arc->c0.y - arc->ry, SkScalarMul(arc->rx, SkIntToScalar(2)), SkScalarMul(arc->ry, SkIntToScalar(2))), arc->ab, arc->an, false, *spainter->style);
}
static tb_void_t g2_skia_draw_rect(tb_handle_t painter, g2_rect_t const* rect)
{
	g2_skia_painter_t* spainter = static_cast<g2_skia_painter_t*>(painter);
	tb_assert_and_check_return(spainter && spainter->canvas && spainter->style && rect);

	// update matrix
	g2_skia_matrix_update(spainter);

	// draw
	spainter->canvas->drawRect(SkRect::MakeXYWH(rect->x, rect->y, rect->w, rect->h), *spainter->style);
}
static tb_void_t g2_skia_draw_line(tb_handle_t painter, g2_line_t const* line)
{
	g2_skia_painter_t* spainter = static_cast<g2_skia_painter_t*>(painter);
	tb_assert_and_check_return(spainter && spainter->canvas && spainter->style && line);

	// update matrix
	g2_skia_matrix_update(spainter);

	// draw
	spainter->canvas->drawLine(line->p0.x, line->p0.y, line->p1.x, line->p1.y, *spainter->style);
}
static tb_void_t g2_skia_draw_point(tb_handle_t painter, g2_point_t const* point)
{
	g2_skia_painter_t* spainter = static_cast<g2_skia_painter_t*>(painter);
	tb_assert_and_check_return(spainter && spainter->canvas && spainter->style && point);

	// update matrix
	g2_skia_matrix_update(spainter);

	// draw
	spainter->canvas->drawPoint(point->x, point->y, *spainter->style);
}
static tb_void_t g2_skia_draw_circle(tb_handle_t painter, g2_circle_t const* circle)
{
	g2_skia_painter_t* spainter = static_cast<g2_skia_painter_t*>(painter);
	tb_assert_and_check_return(spainter && spainter->canvas && spainter->style && circle);

	// update matrix
	g2_skia_matrix_update(spainter);

	// draw
	spainter->canvas->drawCircle(circle->c.x, circle->c.y, circle->r, *spainter->style);
}
static tb_void_t g2_skia_draw_ellipse(tb_handle_t painter, g2_ellipse_t const* ellipse)
{
	g2_skia_painter_t* spainter = static_cast<g2_skia_painter_t*>(painter);
	tb_assert_and_check_return(spainter && spainter->canvas && spainter->style && ellipse);

	// update matrix
	g2_skia_matrix_update(spainter);

	// draw
	spainter->canvas->drawOval(SkRect::MakeXYWH(ellipse->c0.x - ellipse->rx, ellipse->c0.y - ellipse->ry, SkScalarMul(ellipse->rx, SkIntToScalar(2)), SkScalarMul(ellipse->ry, SkIntToScalar(2))), *spainter->style);
}
static tb_void_t g2_skia_draw_triangle(tb_handle_t painter, g2_triangle_t const* triangle)
{
	g2_skia_painter_t* spainter = static_cast<g2_skia_painter_t*>(painter);
	tb_assert_and_check_return(spainter && spainter->canvas && spainter->style && triangle);
 
	// update matrix
	g2_skia_matrix_update(spainter);

	// draw
	G2SkiaPath path;
    path.incReserve(3);
	path.moveTo(triangle->p0.x, triangle->p0.y);
	path.lineTo(triangle->p1.x, triangle->p1.y);
	path.lineTo(triangle->p2.x, triangle->p2.y);
	path.close();
	spainter->canvas->drawPath(path, *spainter->style);
}

/* ///////////////////////////////////////////////////////////////////////
 * interfaces
 */

extern "C"
{
	tb_handle_t g2_init(tb_handle_t context)
	{
		return g2_skia_init(context);
	}
	tb_void_t g2_exit(tb_handle_t painter)
	{
		g2_skia_exit(painter);
	}
	tb_size_t g2_pixfmt(tb_handle_t painter)
	{
		return g2_skia_pixfmt(painter);
	}
	tb_handle_t g2_context(tb_handle_t painter)
	{
		return g2_skia_context(painter);
	}
	tb_handle_t g2_style(tb_handle_t painter)
	{
		return g2_skia_style(painter);
	}
	tb_handle_t g2_style_save(tb_handle_t painter)
	{
		return g2_skia_style_save(painter);
	}
	tb_void_t g2_style_load(tb_handle_t painter)
	{
		g2_skia_style_load(painter);
	}
	g2_matrix_t* g2_matrix(tb_handle_t painter)
	{
		return g2_skia_matrix(painter);				
	}
	g2_matrix_t* g2_matrix_save(tb_handle_t painter)
	{
		return g2_skia_matrix_save(painter);
	}
	tb_void_t g2_matrix_load(tb_handle_t painter)
	{
		g2_skia_matrix_load(painter);
	}
	tb_handle_t g2_clipper(tb_handle_t painter)
	{
		return g2_skia_clipper(painter);				
	}
	tb_handle_t g2_clipper_save(tb_handle_t painter)
	{
		return g2_skia_clipper_save(painter);
	}
	tb_void_t g2_clipper_load(tb_handle_t painter)
	{
		g2_skia_clipper_load(painter);
	}
	tb_void_t g2_draw_clear(tb_handle_t painter, g2_color_t color)
	{
		g2_skia_draw_clear(painter, color);
	}
	tb_void_t g2_draw_path(tb_handle_t painter, tb_handle_t path)
	{
		g2_skia_draw_path(painter, path);
	}
	tb_void_t g2_draw_arc(tb_handle_t painter, g2_arc_t const* arc)
	{
		g2_skia_draw_arc(painter, arc);
	}
	tb_void_t g2_draw_rect(tb_handle_t painter, g2_rect_t const* rect)
	{
		g2_skia_draw_rect(painter, rect);
	}
	tb_void_t g2_draw_line(tb_handle_t painter, g2_line_t const* line)
	{
		g2_skia_draw_line(painter, line);
	}
	tb_void_t g2_draw_point(tb_handle_t painter, g2_point_t const* point)
	{
		g2_skia_draw_point(painter, point);
	}
	tb_void_t g2_draw_circle(tb_handle_t painter, g2_circle_t const* circle)
	{
		g2_skia_draw_circle(painter, circle);
	}
	tb_void_t g2_draw_ellipse(tb_handle_t painter, g2_ellipse_t const* ellipse)
	{
		g2_skia_draw_ellipse(painter, ellipse);
	}
	tb_void_t g2_draw_triangle(tb_handle_t painter, g2_triangle_t const* triangle)
	{
		g2_skia_draw_triangle(painter, triangle);
	}
}

