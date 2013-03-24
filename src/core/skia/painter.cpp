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

// matrix
#ifdef SK_SCALAR_IS_FLOAT
# 	define kMatrix22Elem 					SK_Scalar1
#else
# 	define kMatrix22Elem 					SK_Fract1
#endif

// matrix
#ifdef TB_CONFIG_BINARY_SMALL
# 	define G2_GL_MATRIX_GROW 				(32)
#else
# 	define G2_GL_MATRIX_GROW 				(64)
#endif

// cache
#ifdef TB_CONFIG_BINARY_SMALL
# 	define G2_GL_CACHE_PATH_SIZE 			(8)
# 	define G2_GL_CACHE_STYLE_SIZE 			(4)
# 	define G2_GL_CACHE_CLIPPER_SIZE 		(4)
#else
# 	define G2_GL_CACHE_PATH_SIZE 			(16)
# 	define G2_GL_CACHE_STYLE_SIZE 			(8)
# 	define G2_GL_CACHE_CLIPPER_SIZE 		(8)
#endif

// pcache
#ifdef TB_CONFIG_BINARY_SMALL
# 	define G2_GL_PCACHE_MAXN 				(36)
#else
# 	define G2_GL_PCACHE_MAXN 				(64)
#endif

/* ///////////////////////////////////////////////////////////////////////
 * types
 */

// the skia painter type
typedef struct __g2_skia_painter_t
{
	// the context
	tb_handle_t 		context;

	// the data
	tb_pointer_t 		data;

	// the canvas
	SkCanvas* 			canvas;

	// the matrix
	g2_matrix_t 		matrix;

	// the stack
	tb_stack_t* 		stack_matrix;
	tb_handle_t 		stack_path;
	tb_handle_t 		stack_style;
	tb_handle_t 		stack_clipper;

	// the cache
	tb_handle_t 		pcache;

}g2_skia_painter_t;

/* ///////////////////////////////////////////////////////////////////////
 * helper
 */
static __tb_inline__ tb_void_t g2_skia_context_apply(g2_skia_painter_t* spainter)
{
	// surface
	SkBitmap const* surface = static_cast<SkBitmap const*>(g2_context_surface(spainter->context));
	tb_assert_and_check_return(surface);

	// if the data address is changed, re-attach device
	if (spainter->data != surface->getPixels())
	{
		spainter->data = surface->getPixels();
		spainter->canvas->setBitmapDevice(*surface);
	}
}
static __tb_inline__ tb_void_t g2_skia_matrix_apply(g2_skia_painter_t* spainter)
{
	SkMatrix mx;
	g2_matrix_t const* matrix = &spainter->matrix;
	mx.setAll( 	matrix->sx, matrix->kx, matrix->tx
			, 	matrix->ky, matrix->sy, matrix->ty
			, 	0, 0, kMatrix22Elem);
	spainter->canvas->setMatrix(mx);
}
static __tb_inline__ tb_void_t g2_skia_clipper_apply(g2_skia_painter_t* spainter)
{
	// clipper
	tb_handle_t clipper = g2_clipper(spainter);

	// no clipper item?
	tb_size_t 	size = g2_clipper_size(clipper);
	tb_check_return(size);

	// anti-aliasing?
	bool anti = false;
	if (g2_quality() == G2_QUALITY_TOP) anti = true;

	// walk
	tb_size_t i = 0;
	for (i = 0; i < size; i++)
	{
		// item
		g2_clipper_item_t const* item = g2_clipper_item(clipper, i);
		if (item)
		{
			// mode
			SkRegion::Op op = SkRegion::kIntersect_Op;
			switch (item->mode)
			{
			case G2_CLIPPER_MODE_INTERSECT:
				op = SkRegion::kIntersect_Op;
				break;
			case G2_CLIPPER_MODE_UNION:
				op = SkRegion::kUnion_Op;
				break;
			case G2_CLIPPER_MODE_REPLACE:
				op = SkRegion::kReplace_Op;
				break;
			case G2_CLIPPER_MODE_SUBTRACT:
				op = SkRegion::kDifference_Op;
				break;
			default:
				tb_assert(0);
				break;
			}

			// apply matrix
			SkMatrix mx;
			g2_matrix_t const* matrix = &item->matrix;
			mx.setAll( 	matrix->sx, matrix->kx, matrix->tx
					, 	matrix->ky, matrix->sy, matrix->ty
					, 	0, 0, kMatrix22Elem);
			spainter->canvas->setMatrix(mx);

			// clip
			switch (item->type)
			{
			case G2_CLIPPER_ITEM_RECT:
				spainter->canvas->clipRect(SkRect::MakeXYWH(item->u.rect.x, item->u.rect.y, item->u.rect.w, item->u.rect.h), op, anti);
				break;
			case G2_CLIPPER_ITEM_PATH:
				spainter->canvas->clipPath(*static_cast<const G2SkiaPath*>(item->u.path), op, anti);
				break;
			case G2_CLIPPER_ITEM_CIRCLE:
				{
					// init shape
					g2_shape_t shape = {0};
					shape.type = G2_SHAPE_TYPE_CIRCLE;
					shape.u.circle = item->u.circle;

					// get path from pcache first
					tb_handle_t path = g2_pcache_get(spainter->pcache, &shape);
					if (!path)
					{
						// init path from cache
						path = g2_pcache_add(spainter->pcache, &shape);
						tb_assert_and_check_return(path);

						// add circle to path
						g2_path_add_circle(path, &item->u.circle);
					}

					spainter->canvas->clipPath(*static_cast<G2SkiaPath const*>(path), op, anti);
				}
				break;
			case G2_CLIPPER_ITEM_ELLIPSE:
				{
					// init shape
					g2_shape_t shape = {0};
					shape.type = G2_SHAPE_TYPE_ELLIPSE;
					shape.u.ellipse = item->u.ellipse;

					// get path from pcache first
					tb_handle_t path = g2_pcache_get(spainter->pcache, &shape);
					if (!path)
					{
						// init path from cache
						path = g2_pcache_add(spainter->pcache, &shape);
						tb_assert_and_check_return(path);

						// add ellipse to path
						g2_path_add_ellipse(path, &item->u.ellipse);
					}
	
					spainter->canvas->clipPath(*static_cast<G2SkiaPath const*>(path), op, anti);
				}
				break;
			case G2_CLIPPER_ITEM_TRIANGLE:
				{
					// init shape
					g2_shape_t shape = {0};
					shape.type = G2_SHAPE_TYPE_TRIANGLE;
					shape.u.triangle = item->u.triangle;

					// get path from pcache first
					tb_handle_t path = g2_pcache_get(spainter->pcache, &shape);
					if (!path)
					{
						// init path from cache
						path = g2_pcache_add(spainter->pcache, &shape);
						tb_assert_and_check_return(path);

						// add triangle to path
						g2_path_add_triangle(path, &item->u.triangle);
					}

					spainter->canvas->clipPath(*static_cast<G2SkiaPath const*>(path), op, anti);
				}
				break;
			default:
				break;
			}
		}
	}
}
static __tb_inline__ tb_void_t g2_skia_state_enter(g2_skia_painter_t* spainter)
{
	// apply context
	g2_skia_context_apply(spainter);

	// save
	spainter->canvas->save();

	// apply clipper
	g2_skia_clipper_apply(spainter);

	// apply matrix
	g2_skia_matrix_apply(spainter);
}
static __tb_inline__ tb_void_t g2_skia_state_leave(g2_skia_painter_t* spainter)
{
	// restore
	spainter->canvas->restore();
}
static tb_bool_t g2_skia_style_stack_item_free(tb_stack_t* stack, tb_pointer_t* item, tb_bool_t* bdel, tb_pointer_t data)
{
	tb_assert_and_check_return_val(stack && bdel, tb_false);

	// free style item
	if (item) 
	{
		tb_handle_t style = (tb_handle_t)*item;
		if (style) g2_style_exit(style);
		*item = tb_null;
	}

	// ok
	return tb_true;
}
static tb_bool_t g2_skia_clipper_stack_item_free(tb_stack_t* stack, tb_pointer_t* item, tb_bool_t* bdel, tb_pointer_t data)
{
	tb_assert_and_check_return_val(stack && bdel, tb_false);

	// free clipper item
	if (item) 
	{
		tb_handle_t clipper = (tb_handle_t)*item;
		if (clipper) g2_clipper_exit(clipper);
		*item = tb_null;
	}

	// ok
	return tb_true;
}
static tb_void_t g2_skia_clipper_hash_item_free(tb_item_func_t* func, tb_pointer_t item)
{
	if (item) 
	{
		tb_handle_t path = *((tb_handle_t const*)item);
		if (path) g2_path_exit(path);
	}
}
/* ///////////////////////////////////////////////////////////////////////
 * implementation
 */
static __tb_inline__ tb_void_t g2_skia_exit(tb_handle_t painter)
{
	g2_skia_painter_t* spainter = static_cast<g2_skia_painter_t*>(painter);
	tb_assert_and_check_return(spainter);

	// exit matrix stack
	if (spainter->stack_matrix) tb_stack_exit(spainter->stack_matrix);
	spainter->stack_matrix = tb_null;

	// exit path stack
	if (spainter->stack_path) g2_cstack_exit(spainter->stack_path);
	spainter->stack_path = tb_null;

	// exit style stack
	if (spainter->stack_style) g2_cstack_exit(spainter->stack_style);
	spainter->stack_style = tb_null;

	// exit clipper stack
	if (spainter->stack_clipper) g2_cstack_exit(spainter->stack_clipper);
	spainter->stack_clipper = tb_null;

	// exit pcache
	if (spainter->pcache) g2_pcache_exit(spainter->pcache);
	spainter->pcache = tb_null;

	// exit canvas
	if (spainter->canvas) delete spainter->canvas;
	spainter->canvas = tb_null;

	// exit it
	tb_free(spainter);
}
static __tb_inline__ tb_handle_t g2_skia_init(tb_handle_t context)
{
	// check
	tb_assert_and_check_return_val(context, tb_null);

	// init func
	g2_cstack_func_t func_path 		= {g2_path_init, 		g2_path_exit, 		g2_path_copy};
	g2_cstack_func_t func_style 	= {g2_style_init, 		g2_style_exit, 		g2_style_copy};
	g2_cstack_func_t func_clipper 	= {g2_clipper_init, 	g2_clipper_exit, 	g2_clipper_copy};

	// init surface
	SkBitmap const* surface = static_cast<SkBitmap const*>(g2_context_surface(context));
	tb_assert_and_check_return_val(surface, tb_null);

	// alloc
	g2_skia_painter_t* spainter = (g2_skia_painter_t*)tb_malloc0(sizeof(g2_skia_painter_t));
	tb_assert_and_check_return_val(spainter, tb_null);

	// init context
	spainter->context = context;
	spainter->data = (tb_pointer_t)surface->getPixels();
	
	// init canvas
	spainter->canvas = new SkCanvas(*surface);
	tb_assert_and_check_goto(spainter->canvas, fail);
	spainter->canvas->resetMatrix();

	// init matrix
	g2_matrix_clear(&spainter->matrix);

	// init matrix stack
	spainter->stack_matrix = tb_stack_init(G2_GL_MATRIX_GROW, tb_item_func_ifm(sizeof(g2_matrix_t), tb_null, tb_null));
	tb_assert_and_check_goto(spainter->stack_matrix, fail);

	// init style stack
	spainter->stack_style = g2_cstack_init(G2_GL_CACHE_STYLE_SIZE, &func_style);
	tb_assert_and_check_goto(spainter->stack_style, fail);

	// init clipper stack
	spainter->stack_clipper = g2_cstack_init(G2_GL_CACHE_CLIPPER_SIZE, &func_clipper);
	tb_assert_and_check_goto(spainter->stack_clipper, fail);

	// init path stack
	spainter->stack_path = g2_cstack_init(G2_GL_CACHE_PATH_SIZE, &func_path);
	tb_assert_and_check_goto(spainter->stack_path, fail);

	// init pcache
	spainter->pcache = g2_pcache_init(G2_GL_PCACHE_MAXN);
	tb_assert_and_check_goto(spainter->pcache, fail);

	// ok
	return spainter;

fail:
	if (spainter) g2_skia_exit(spainter);
	return tb_null;
}
static __tb_inline__ tb_size_t g2_skia_pixfmt(tb_handle_t painter)
{
	g2_skia_painter_t* spainter = static_cast<g2_skia_painter_t*>(painter);
	tb_assert_and_check_return_val(spainter && spainter->context, G2_PIXFMT_NONE);

	return g2_bitmap_pixfmt(spainter->context);
}
static __tb_inline__ tb_handle_t g2_skia_context(tb_handle_t painter)
{
	g2_skia_painter_t* spainter = static_cast<g2_skia_painter_t*>(painter);
	tb_assert_and_check_return_val(spainter, tb_null);

	return spainter->context;
}
static __tb_inline__ tb_handle_t g2_skia_path(tb_handle_t painter)
{
	g2_skia_painter_t* spainter = (g2_skia_painter_t*)painter;
	tb_assert_and_check_return_val(spainter && spainter->stack_path, tb_null);

	return g2_cstack_object(spainter->stack_path);
}
static __tb_inline__ tb_handle_t g2_skia_save_path(tb_handle_t painter)
{
	g2_skia_painter_t* spainter = (g2_skia_painter_t*)painter;
	tb_assert_and_check_return_val(spainter && spainter->stack_path, tb_null);

	// save
	return g2_cstack_save(spainter->stack_path);
}
static __tb_inline__ tb_void_t g2_skia_load_path(tb_handle_t painter)
{
	g2_skia_painter_t* spainter = (g2_skia_painter_t*)painter;
	tb_assert_and_check_return(spainter && spainter->stack_path);

	// load
	g2_cstack_load(spainter->stack_path);
}
static __tb_inline__ g2_matrix_t* g2_skia_matrix(tb_handle_t painter)
{
	g2_skia_painter_t* spainter = (g2_skia_painter_t*)painter;
	tb_assert_and_check_return_val(spainter, tb_null);

	return &spainter->matrix;
}
static __tb_inline__ g2_matrix_t* g2_skia_save_matrix(tb_handle_t painter)
{
	g2_skia_painter_t* spainter = (g2_skia_painter_t*)painter;
	tb_assert_and_check_return_val(spainter && spainter->stack_matrix, tb_null);

	// save matrix
	tb_stack_put(spainter->stack_matrix, &spainter->matrix);

	// ok
	return &spainter->matrix;
}
static __tb_inline__ tb_void_t g2_skia_load_matrix(tb_handle_t painter)
{
	g2_skia_painter_t* spainter = (g2_skia_painter_t*)painter;
	tb_assert_and_check_return(spainter && spainter->stack_matrix);

	// init matrix
	g2_matrix_t const* matrix = (g2_matrix_t const*)tb_stack_top(spainter->stack_matrix);
	tb_assert_and_check_return(matrix);

	// load matrix
	spainter->matrix = *matrix;

	// pop it
	tb_stack_pop(spainter->stack_matrix);
}
static __tb_inline__ tb_handle_t g2_skia_style(tb_handle_t painter)
{
	g2_skia_painter_t* spainter = (g2_skia_painter_t*)painter;
	tb_assert_and_check_return_val(spainter && spainter->stack_style, tb_null);

	return g2_cstack_object(spainter->stack_style);
}
static __tb_inline__ tb_handle_t g2_skia_save_style(tb_handle_t painter)
{
	g2_skia_painter_t* spainter = (g2_skia_painter_t*)painter;
	tb_assert_and_check_return_val(spainter && spainter->stack_style, tb_null);

	// save
	return g2_cstack_save(spainter->stack_style);
}
static __tb_inline__ tb_void_t g2_skia_load_style(tb_handle_t painter)
{
	g2_skia_painter_t* spainter = (g2_skia_painter_t*)painter;
	tb_assert_and_check_return(spainter && spainter->stack_style);

	// load
	g2_cstack_load(spainter->stack_style);
}
static __tb_inline__ tb_handle_t g2_skia_clipper(tb_handle_t painter)
{
	g2_skia_painter_t* spainter = (g2_skia_painter_t*)painter;
	tb_assert_and_check_return_val(spainter && spainter->stack_clipper, tb_null);

	return g2_cstack_object(spainter->stack_clipper);
}
static __tb_inline__ tb_handle_t g2_skia_save_clipper(tb_handle_t painter)
{
	g2_skia_painter_t* spainter = (g2_skia_painter_t*)painter;
	tb_assert_and_check_return_val(spainter && spainter->stack_clipper, tb_null);

	// save
	return g2_cstack_save(spainter->stack_clipper);
}
static __tb_inline__ tb_void_t g2_skia_load_clipper(tb_handle_t painter)
{
	g2_skia_painter_t* spainter = (g2_skia_painter_t*)painter;
	tb_assert_and_check_return(spainter && spainter->stack_clipper);

	// load
	g2_cstack_load(spainter->stack_clipper);
}
static __tb_inline__ tb_void_t g2_skia_draw_clear(tb_handle_t painter, g2_color_t color)
{
	g2_skia_painter_t* spainter = static_cast<g2_skia_painter_t*>(painter);
	tb_assert_and_check_return(spainter && spainter->canvas);

	// apply context
	g2_skia_context_apply(spainter);

	// clear
	spainter->canvas->clear(g2_skia_color_to_sk(color));
}
static __tb_inline__ tb_void_t g2_skia_draw_path(tb_handle_t painter, tb_handle_t path)
{
	g2_skia_painter_t* spainter = static_cast<g2_skia_painter_t*>(painter);
	tb_assert_and_check_return(spainter && spainter->canvas && path);

	// style
	SkPaint* style = (SkPaint*)g2_style(painter);
	tb_assert_and_check_return(style);
 
	// state: enter
	g2_skia_state_enter(spainter);

	// draw
	spainter->canvas->drawPath(*((G2SkiaPath const*)path), *style);

	// state: leave
	g2_skia_state_leave(spainter);
}
static __tb_inline__ tb_void_t g2_skia_draw_arc(tb_handle_t painter, g2_arc_t const* arc)
{
	g2_skia_painter_t* spainter = static_cast<g2_skia_painter_t*>(painter);
	tb_assert_and_check_return(spainter && spainter->canvas && arc);

	// style
	SkPaint* style = (SkPaint*)g2_style(painter);
	tb_assert_and_check_return(style);
 
	// state: enter
	g2_skia_state_enter(spainter);

	// draw
	spainter->canvas->drawArc(SkRect::MakeXYWH(arc->c0.x - arc->rx, arc->c0.y - arc->ry, SkScalarMul(arc->rx, SkIntToScalar(2)), SkScalarMul(arc->ry, SkIntToScalar(2))), arc->ab, arc->an, false, *style);
	
	// state: leave
	g2_skia_state_leave(spainter);
}
static __tb_inline__ tb_void_t g2_skia_draw_rect(tb_handle_t painter, g2_rect_t const* rect)
{
	g2_skia_painter_t* spainter = static_cast<g2_skia_painter_t*>(painter);
	tb_assert_and_check_return(spainter && spainter->canvas && rect);

	// style
	SkPaint* style = (SkPaint*)g2_style(painter);
	tb_assert_and_check_return(style);
 
	// state: enter
	g2_skia_state_enter(spainter);

	// draw
	spainter->canvas->drawRect(SkRect::MakeXYWH(rect->x, rect->y, rect->w, rect->h), *style);
	
	// state: leave
	g2_skia_state_leave(spainter);
}
static __tb_inline__ tb_void_t g2_skia_draw_line(tb_handle_t painter, g2_line_t const* line)
{
	g2_skia_painter_t* spainter = static_cast<g2_skia_painter_t*>(painter);
	tb_assert_and_check_return(spainter && spainter->canvas && line);

	// style
	SkPaint* style = (SkPaint*)g2_style(painter);
	tb_assert_and_check_return(style);
 
	// state: enter
	g2_skia_state_enter(spainter);

	// draw
	spainter->canvas->drawLine(line->p0.x, line->p0.y, line->p1.x, line->p1.y, *style);
	
	// state: leave
	g2_skia_state_leave(spainter);
}
static __tb_inline__ tb_void_t g2_skia_draw_point(tb_handle_t painter, g2_point_t const* point)
{
	g2_skia_painter_t* spainter = static_cast<g2_skia_painter_t*>(painter);
	tb_assert_and_check_return(spainter && spainter->canvas && point);

	// style
	SkPaint* style = (SkPaint*)g2_style(painter);
	tb_assert_and_check_return(style);
 
	// state: enter
	g2_skia_state_enter(spainter);

	// draw
	spainter->canvas->drawPoint(point->x, point->y, *style);
	
	// state: leave
	g2_skia_state_leave(spainter);
}
static __tb_inline__ tb_void_t g2_skia_draw_circle(tb_handle_t painter, g2_circle_t const* circle)
{
	g2_skia_painter_t* spainter = static_cast<g2_skia_painter_t*>(painter);
	tb_assert_and_check_return(spainter && spainter->canvas && circle);

	// style
	SkPaint* style = (SkPaint*)g2_style(painter);
	tb_assert_and_check_return(style);
 
	// state: enter
	g2_skia_state_enter(spainter);

	// draw
	spainter->canvas->drawCircle(circle->c.x, circle->c.y, circle->r, *style);

	// state: leave
	g2_skia_state_leave(spainter);
}
static __tb_inline__ tb_void_t g2_skia_draw_ellipse(tb_handle_t painter, g2_ellipse_t const* ellipse)
{
	g2_skia_painter_t* spainter = static_cast<g2_skia_painter_t*>(painter);
	tb_assert_and_check_return(spainter && spainter->canvas && ellipse);

	// style
	SkPaint* style = (SkPaint*)g2_style(painter);
	tb_assert_and_check_return(style);
 
	// state: enter
	g2_skia_state_enter(spainter);

	// draw
	spainter->canvas->drawOval(SkRect::MakeXYWH(ellipse->c0.x - ellipse->rx, ellipse->c0.y - ellipse->ry, ellipse->rx + ellipse->rx, ellipse->ry + ellipse->ry), *style);
	
	// state: leave
	g2_skia_state_leave(spainter);
}
static __tb_inline__ tb_void_t g2_skia_draw_triangle(tb_handle_t painter, g2_triangle_t const* triangle)
{
	g2_skia_painter_t* spainter = static_cast<g2_skia_painter_t*>(painter);
	tb_assert_and_check_return(spainter && spainter->canvas && triangle);

	// style
	SkPaint* style = (SkPaint*)g2_style(painter);
	tb_assert_and_check_return(style);
 
	// state: enter
	g2_skia_state_enter(spainter);

	// draw
	G2SkiaPath path;
    path.incReserve(3);
	path.moveTo(triangle->p0.x, triangle->p0.y);
	path.lineTo(triangle->p1.x, triangle->p1.y);
	path.lineTo(triangle->p2.x, triangle->p2.y);
	path.close();
	spainter->canvas->drawPath(path, *style);
	
	// state: leave
	g2_skia_state_leave(spainter);
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
	tb_handle_t g2_path(tb_handle_t painter)
	{
		return g2_skia_path(painter);
	}
	tb_handle_t g2_save_path(tb_handle_t painter)
	{
		return g2_skia_save_path(painter);
	}
	tb_void_t g2_load_path(tb_handle_t painter)
	{
		g2_skia_load_path(painter);
	}
	tb_handle_t g2_style(tb_handle_t painter)
	{
		return g2_skia_style(painter);
	}
	tb_handle_t g2_save_style(tb_handle_t painter)
	{
		return g2_skia_save_style(painter);
	}
	tb_void_t g2_load_style(tb_handle_t painter)
	{
		g2_skia_load_style(painter);
	}
	g2_matrix_t* g2_matrix(tb_handle_t painter)
	{
		return g2_skia_matrix(painter);				
	}
	g2_matrix_t* g2_save_matrix(tb_handle_t painter)
	{
		return g2_skia_save_matrix(painter);
	}
	tb_void_t g2_load_matrix(tb_handle_t painter)
	{
		g2_skia_load_matrix(painter);
	}
	tb_handle_t g2_clipper(tb_handle_t painter)
	{
		return g2_skia_clipper(painter);				
	}
	tb_handle_t g2_save_clipper(tb_handle_t painter)
	{
		return g2_skia_save_clipper(painter);
	}
	tb_void_t g2_load_clipper(tb_handle_t painter)
	{
		g2_skia_load_clipper(painter);
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

