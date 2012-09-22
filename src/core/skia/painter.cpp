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
# 	define kMatrix22Elem 	SK_Scalar1
#else
# 	define kMatrix22Elem 	SK_Fract1
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

	// the style
	SkPaint* 			style_def;
	SkPaint* 			style_usr;

}g2_skia_painter_t;


/* ///////////////////////////////////////////////////////////////////////
 * implementation
 */
static __tb_inline__ tb_void_t g2_skia_apply_matrix(g2_skia_painter_t* spainter)
{
	SkMatrix mx;
	mx.setAll( 	spainter->matrix.sx, spainter->matrix.kx, spainter->matrix.tx
			, 	spainter->matrix.ky, spainter->matrix.sy, spainter->matrix.ty
			, 	0, 0, kMatrix22Elem);
	spainter->canvas->setMatrix(mx);
}
static tb_void_t g2_skia_exit(tb_handle_t painter)
{
	g2_skia_painter_t* spainter = static_cast<g2_skia_painter_t*>(painter);
	tb_assert_and_check_return(spainter);

	// free style
	if (spainter->style_def) g2_style_exit(spainter->style_def);

	// free canvas
	if (spainter->canvas) delete spainter->canvas;

	// free it
	delete spainter;
}
static tb_handle_t g2_skia_init(tb_handle_t context)
{
	// check
	tb_assert_and_check_return_val(context, TB_NULL);

	// init surface
	SkBitmap const* surface = static_cast<SkBitmap const*>(g2_context_surface(context));
	tb_assert_and_check_return_val(surface, TB_NULL);

	// alloc
	g2_skia_painter_t* spainter = new g2_skia_painter_t;
	tb_assert_and_check_return_val(spainter, TB_NULL);

	// init context
	spainter->context = context;
	
	// init canvas
	spainter->canvas = new SkCanvas(*surface);
	tb_assert_and_check_goto(spainter->canvas, fail);

	// init matrix
	g2_matrix_clear(&spainter->matrix);
	g2_skia_apply_matrix(spainter);

	// init style
	spainter->style_def = static_cast<SkPaint*>(g2_style_init());
	spainter->style_usr = spainter->style_def;
	tb_assert_and_check_goto(spainter->style_def, fail);

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
static tb_size_t g2_skia_save(tb_handle_t painter, tb_size_t mode)
{
	g2_skia_painter_t* spainter = static_cast<g2_skia_painter_t*>(painter);
	tb_assert_and_check_return_val(spainter && spainter->canvas, 0);

	return spainter->canvas->save(static_cast<SkCanvas::SaveFlags>(mode));
}
static tb_void_t g2_skia_load(tb_handle_t painter)
{	
	g2_skia_painter_t* spainter = static_cast<g2_skia_painter_t*>(painter);
	tb_assert_and_check_return(spainter && spainter->canvas);

	spainter->canvas->restore();
}
static tb_handle_t g2_skia_context(tb_handle_t painter)
{
	g2_skia_painter_t* spainter = static_cast<g2_skia_painter_t*>(painter);
	tb_assert_and_check_return_val(spainter, TB_NULL);

	return spainter->context;
}
static tb_void_t g2_skia_context_set(tb_handle_t painter, tb_handle_t context)
{
	g2_skia_painter_t* spainter = static_cast<g2_skia_painter_t*>(painter);
	tb_assert_and_check_return(spainter && spainter->canvas && context);

	// surface
	SkBitmap const* surface = static_cast<SkBitmap const*>(g2_context_surface(context));
	tb_assert_and_check_return(surface);

	// update context
	spainter->context = context;

	// update canvas
	spainter->canvas->setBitmapDevice(*surface);
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
static g2_matrix_t const* g2_skia_matrix(tb_handle_t painter)
{
	g2_skia_painter_t* spainter = static_cast<g2_skia_painter_t*>(painter);
	tb_assert_and_check_return_val(spainter, TB_NULL);

	return &spainter->matrix;
}
static tb_void_t g2_skia_matrix_set(tb_handle_t painter, g2_matrix_t const* matrix)
{
	g2_skia_painter_t* spainter = static_cast<g2_skia_painter_t*>(painter);
	tb_assert_and_check_return(spainter && spainter->canvas);

	// set matrix
	if (matrix) spainter->matrix = *matrix;
	else g2_matrix_clear(&spainter->matrix);

	// apply
	g2_skia_apply_matrix(spainter);
}
static tb_bool_t g2_skia_rotate(tb_handle_t painter, g2_float_t degrees)
{
	g2_skia_painter_t* spainter = static_cast<g2_skia_painter_t*>(painter);
	tb_assert_and_check_return_val(spainter && spainter->canvas, TB_FALSE);

	// rotate
	tb_bool_t ok = g2_matrix_rotate(&spainter->matrix, degrees); 

	// apply
	g2_skia_apply_matrix(spainter);

	// ok?
	return ok;
}
static tb_bool_t g2_skia_scale(tb_handle_t painter, g2_float_t sx, g2_float_t sy)
{
	g2_skia_painter_t* spainter = static_cast<g2_skia_painter_t*>(painter);
	tb_assert_and_check_return_val(spainter && spainter->canvas, TB_FALSE);

	// scale
	tb_bool_t ok = g2_matrix_scale(&spainter->matrix, sx, sy); 

	// apply
	g2_skia_apply_matrix(spainter);

	// ok?
	return ok;
}
static tb_bool_t g2_skia_skew(tb_handle_t painter, g2_float_t kx, g2_float_t ky)
{
	g2_skia_painter_t* spainter = static_cast<g2_skia_painter_t*>(painter);
	tb_assert_and_check_return_val(spainter && spainter->canvas, TB_FALSE);

	// skew
	tb_bool_t ok = g2_matrix_skew(&spainter->matrix, kx, ky); 

	// apply
	g2_skia_apply_matrix(spainter);

	// ok?
	return ok;
}
static tb_bool_t g2_skia_translate(tb_handle_t painter, g2_float_t dx, g2_float_t dy)
{
	g2_skia_painter_t* spainter = static_cast<g2_skia_painter_t*>(painter);
	tb_assert_and_check_return_val(spainter && spainter->canvas, TB_FALSE);

	// translate
	tb_bool_t ok = g2_matrix_translate(&spainter->matrix, dx, dy); 

	// apply
	g2_skia_apply_matrix(spainter);

	// ok?
	return ok;
}
static tb_bool_t g2_skia_multiply(tb_handle_t painter, g2_matrix_t const* matrix)
{
	g2_skia_painter_t* spainter = static_cast<g2_skia_painter_t*>(painter);
	tb_assert_and_check_return_val(spainter && spainter->canvas && matrix, TB_FALSE);

	// multiply
	tb_bool_t ok = g2_matrix_multiply(&spainter->matrix, matrix); 

	// apply
	g2_skia_apply_matrix(spainter);

	// ok?
	return ok;
}
static tb_bool_t g2_skia_clip_path(tb_handle_t painter, tb_size_t mode, tb_handle_t path)
{
	g2_skia_painter_t* spainter = static_cast<g2_skia_painter_t*>(painter);
	tb_assert_and_check_return_val(spainter && spainter->canvas && path, TB_FALSE);

	bool 			anti = mode & G2_CLIP_MODE_ANTI_ALIAS? true : false;
	SkRegion::Op 	op = SkRegion::kIntersect_Op;

	mode &= ~G2_CLIP_MODE_ANTI_ALIAS;
	switch (mode)
	{
	case G2_CLIP_MODE_INTERSECT:
		op = SkRegion::kIntersect_Op;
		break;
	case G2_CLIP_MODE_UNION:
		op = SkRegion::kUnion_Op;
		break;
	case G2_CLIP_MODE_REPLACE:
		op = SkRegion::kReplace_Op;
		break;
	case G2_CLIP_MODE_SUBTRACT:
		op = SkRegion::kDifference_Op;
		break;
	default:
		tb_assert(0);
		break;
	}

	if (g2_quality() == G2_QUALITY_TOP) anti = true;
	return spainter->canvas->clipPath(*static_cast<const G2SkiaPath*>(path), op, anti)? TB_TRUE : TB_FALSE;
}
static tb_bool_t g2_skia_clip_rect(tb_handle_t painter, tb_size_t mode, g2_rect_t const* rect)
{
	g2_skia_painter_t* spainter = static_cast<g2_skia_painter_t*>(painter);
	tb_assert_and_check_return_val(spainter && spainter->canvas && rect, TB_FALSE);

	bool 			anti = mode & G2_CLIP_MODE_ANTI_ALIAS? true : false;
	SkRegion::Op 	op = SkRegion::kIntersect_Op;

	mode &= ~G2_CLIP_MODE_ANTI_ALIAS;
	switch (mode)
	{
	case G2_CLIP_MODE_INTERSECT:
		op = SkRegion::kIntersect_Op;
		break;
	case G2_CLIP_MODE_UNION:
		op = SkRegion::kUnion_Op;
		break;
	case G2_CLIP_MODE_REPLACE:
		op = SkRegion::kReplace_Op;
		break;
	case G2_CLIP_MODE_SUBTRACT:
		op = SkRegion::kDifference_Op;
		break;
	default:
		tb_assert(0);
		break;
	}

	if (g2_quality() == G2_QUALITY_TOP) anti = true;
	return spainter->canvas->clipRect(SkRect::MakeXYWH(rect->x, rect->y, rect->w, rect->h), op, anti)? TB_TRUE : TB_FALSE;
}
static tb_void_t g2_skia_clear(tb_handle_t painter, g2_color_t color)
{
	g2_skia_painter_t* spainter = static_cast<g2_skia_painter_t*>(painter);
	tb_assert_and_check_return(spainter && spainter->canvas);

	spainter->canvas->clear(g2_skia_color_to_sk(color));
}
static tb_void_t g2_skia_draw_path(tb_handle_t painter, tb_handle_t path)
{
	g2_skia_painter_t* spainter = static_cast<g2_skia_painter_t*>(painter);
	tb_assert_and_check_return(spainter && spainter->canvas && spainter->style_usr && path);

	spainter->canvas->drawPath(*((G2SkiaPath const*)path), *spainter->style_usr);
}
static tb_void_t g2_skia_draw_arc(tb_handle_t painter, g2_arc_t const* arc)
{
	g2_skia_painter_t* spainter = static_cast<g2_skia_painter_t*>(painter);
	tb_assert_and_check_return(spainter && spainter->canvas && spainter->style_usr && arc);

	spainter->canvas->drawArc(SkRect::MakeXYWH(arc->c0.x - arc->rx, arc->c0.y - arc->ry, SkScalarMul(arc->rx, SkIntToScalar(2)), SkScalarMul(arc->ry, SkIntToScalar(2))), arc->ab, arc->an, false, *spainter->style_usr);
}
static tb_void_t g2_skia_draw_rect(tb_handle_t painter, g2_rect_t const* rect)
{
	g2_skia_painter_t* spainter = static_cast<g2_skia_painter_t*>(painter);
	tb_assert_and_check_return(spainter && spainter->canvas && spainter->style_usr && rect);

	spainter->canvas->drawRect(SkRect::MakeXYWH(rect->x, rect->y, rect->w, rect->h), *spainter->style_usr);
}
static tb_void_t g2_skia_draw_line(tb_handle_t painter, g2_line_t const* line)
{
	g2_skia_painter_t* spainter = static_cast<g2_skia_painter_t*>(painter);
	tb_assert_and_check_return(spainter && spainter->canvas && spainter->style_usr && line);

	spainter->canvas->drawLine(line->p0.x, line->p0.y, line->p1.x, line->p1.y, *spainter->style_usr);
}
static tb_void_t g2_skia_draw_point(tb_handle_t painter, g2_point_t const* point)
{
	g2_skia_painter_t* spainter = static_cast<g2_skia_painter_t*>(painter);
	tb_assert_and_check_return(spainter && spainter->canvas && spainter->style_usr && point);

	spainter->canvas->drawPoint(point->x, point->y, *spainter->style_usr);
}
static tb_void_t g2_skia_draw_circle(tb_handle_t painter, g2_circle_t const* circle)
{
	g2_skia_painter_t* spainter = static_cast<g2_skia_painter_t*>(painter);
	tb_assert_and_check_return(spainter && spainter->canvas && spainter->style_usr && circle);

	spainter->canvas->drawCircle(circle->c.x, circle->c.y, circle->r, *spainter->style_usr);
}
static tb_void_t g2_skia_draw_ellipse(tb_handle_t painter, g2_ellipse_t const* ellipse)
{
	g2_skia_painter_t* spainter = static_cast<g2_skia_painter_t*>(painter);
	tb_assert_and_check_return(spainter && spainter->canvas && spainter->style_usr && ellipse);

	spainter->canvas->drawOval(SkRect::MakeXYWH(ellipse->c0.x - ellipse->rx, ellipse->c0.y - ellipse->ry, SkScalarMul(ellipse->rx, SkIntToScalar(2)), SkScalarMul(ellipse->ry, SkIntToScalar(2))), *spainter->style_usr);
}
static tb_void_t g2_skia_draw_triangle(tb_handle_t painter, g2_triangle_t const* triangle)
{
	g2_skia_painter_t* spainter = static_cast<g2_skia_painter_t*>(painter);
	tb_assert_and_check_return(spainter && spainter->canvas && spainter->style_usr && triangle);
 
	G2SkiaPath path;
    path.incReserve(3);
	path.moveTo(triangle->p0.x, triangle->p0.y);
	path.lineTo(triangle->p1.x, triangle->p1.y);
	path.lineTo(triangle->p2.x, triangle->p2.y);
	path.close();

	spainter->canvas->drawPath(path, *spainter->style_usr);
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
	tb_size_t g2_save(tb_handle_t painter, tb_size_t mode)
	{
		return g2_skia_save(painter, mode);
	}
	tb_void_t g2_load(tb_handle_t painter)
	{
		g2_skia_load(painter);
	}
	tb_handle_t g2_context(tb_handle_t painter)
	{
		return g2_skia_context(painter);
	}
	tb_void_t g2_context_set(tb_handle_t painter, tb_handle_t context)
	{
		g2_skia_context_set(painter, context);
	}
	tb_handle_t g2_style(tb_handle_t painter)
	{
		return g2_skia_style(painter);
	}
	tb_void_t g2_style_set(tb_handle_t painter, tb_handle_t style)
	{
		g2_skia_style_set(painter, style);
	}
	g2_matrix_t const* g2_matrix(tb_handle_t painter)
	{
		return g2_skia_matrix(painter);				
	}
	tb_bool_t g2_rotate(tb_handle_t painter, g2_float_t degrees)
	{
		return g2_skia_rotate(painter, degrees);		
	}
	tb_bool_t g2_skew(tb_handle_t painter, g2_float_t kx, g2_float_t ky)
	{
		return g2_skia_scale(painter, kx, ky);
	}
	tb_bool_t g2_scale(tb_handle_t painter, g2_float_t sx, g2_float_t sy)
	{
		return g2_skia_scale(painter, sx, sy);
	}
	tb_bool_t g2_translate(tb_handle_t painter, g2_float_t dx, g2_float_t dy)
	{
		return g2_skia_translate(painter, dx, dy);		
	}
	tb_bool_t g2_multiply(tb_handle_t painter, g2_matrix_t const* matrix)
	{
		return g2_skia_multiply(painter, matrix);		
	}
	tb_void_t g2_matrix_set(tb_handle_t painter, g2_matrix_t const* matrix)
	{
		g2_skia_matrix_set(painter, matrix);		
	}
	tb_bool_t g2_clip_path(tb_handle_t painter, tb_size_t mode, tb_handle_t path)
	{
		return g2_skia_clip_path(painter, mode, path);
	}
	tb_bool_t g2_clip_rect(tb_handle_t painter, tb_size_t mode, g2_rect_t const* rect)
	{
		return g2_skia_clip_rect(painter, mode, rect);
	}
	tb_void_t g2_clear(tb_handle_t painter, g2_color_t color)
	{
		g2_skia_clear(painter, color);
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

