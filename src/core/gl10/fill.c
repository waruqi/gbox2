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
 * @file		fill.c
 *
 */

/* ///////////////////////////////////////////////////////////////////////
 * trace
 */
#define TB_TRACE_IMPL_TAG 		"fill"

/* ///////////////////////////////////////////////////////////////////////
 * includes
 */
#include "fill.h"
#include "rect.h"
#include "shader.h"
#include "matrix.h"
#include "../soft/split/split.h"

/* ///////////////////////////////////////////////////////////////////////
 * types
 */

// the gl10 fill flag type
typedef enum __g2_gl10_fill_flag_t
{
	G2_GL10_FILL_FLAG_NONE 		= 0
,	G2_GL10_FILL_FLAG_RECT 		= 1
,	G2_GL10_FILL_FLAG_STENCIL 	= 2
,	G2_GL10_FILL_FLAG_CONVEX 	= 4

}g2_gl10_fill_flag_t;

// the gl10 fill type
typedef struct __g2_gl10_fill_t
{
	// the painter
	g2_gl10_painter_t* 	painter;

	// the style 
	tb_handle_t 		style;

	// the flag
	tb_size_t 			flag;

}g2_gl10_fill_t;

/* ///////////////////////////////////////////////////////////////////////
 * implementation
 */
static __tb_inline__ tb_void_t g2_gl10_fill_matrix_enter(g2_gl10_fill_t* fill)
{
	g2_gl10_matrix_set(fill->painter->matrix_gl, &fill->painter->matrix);
	glMatrixMode(GL_MODELVIEW);
	glPushMatrix();
	glMultMatrixf(fill->painter->matrix_gl);
}
static __tb_inline__ tb_void_t g2_gl10_fill_matrix_leave(g2_gl10_fill_t* fill)
{
	glPopMatrix();
}
static __tb_inline__ tb_void_t g2_gl10_fill_stencil_init(g2_gl10_fill_t* fill)
{
	glEnable(GL_STENCIL_TEST);
}
static __tb_inline__ tb_void_t g2_gl10_fill_stencil_exit(g2_gl10_fill_t* fill)
{
	glColorMask(GL_TRUE, GL_TRUE, GL_TRUE, GL_TRUE);
	glDisable(GL_STENCIL_TEST);
}
static __tb_inline__ tb_void_t g2_gl10_fill_stencil_enter(g2_gl10_fill_t* fill)
{
	glStencilFunc(GL_ALWAYS, 0, 0);
	glStencilOp(GL_INVERT, GL_INVERT, GL_INVERT);
	glColorMask(GL_FALSE, GL_FALSE, GL_FALSE, GL_FALSE);
}
static __tb_inline__ tb_void_t g2_gl10_fill_stencil_leave(g2_gl10_fill_t* fill)
{
	glStencilFunc(GL_EQUAL, 1, 1);
	glStencilOp(GL_ZERO, GL_ZERO, GL_ZERO);
	glColorMask(GL_TRUE, GL_TRUE, GL_TRUE, GL_TRUE);
}
static __tb_inline__ tb_bool_t g2_gl10_fill_context_init(g2_gl10_fill_t* fill)
{
	// style
	tb_handle_t 	style = fill->style;

	// mode
	tb_size_t 		mode = g2_style_mode(style);

	// flag
	tb_size_t 		flag = g2_style_flag(style);

	// shader
	tb_handle_t 	shader = g2_style_shader(style);

	// has fill?
	tb_check_return_val(mode & G2_STYLE_MODE_FILL, TB_FALSE);

	// enable antialiasing?
	if (flag & G2_STYLE_FLAG_ANTI_ALIAS)
	{
		// init smooth
		tb_size_t smooth = g2_quality() == G2_QUALITY_TOP? GL_NICEST : GL_FASTEST;

		// smooth point
		glDisable(GL_POINT_SMOOTH);
		glHint(GL_POINT_SMOOTH, smooth);

		// smooth line
		glDisable(GL_LINE_SMOOTH);
		glHint(GL_LINE_SMOOTH, smooth);

		// smooth polygon
#ifndef TB_CONFIG_OS_ANDROID
		glDisable(GL_POLYGON_SMOOTH);
		glHint(GL_POLYGON_SMOOTH, smooth);
#endif

		// multisample
		glEnable(GL_MULTISAMPLE);
	}
	else
	{
		glDisable(GL_POINT_SMOOTH);
		glDisable(GL_LINE_SMOOTH);
#ifndef TB_CONFIG_OS_ANDROID
		glDisable(GL_POLYGON_SMOOTH);
#endif
		glDisable(GL_MULTISAMPLE);
	}

	// enable vertices
	glEnableClientState(GL_VERTEX_ARRAY);

	// init color
	if (!shader)
	{
		g2_color_t color = g2_style_color(style);
		glColor4f(color.r / 256., color.g / 256., color.b / 256., color.a / 256.);

		// enable blend?
		if (color.a != 0xff) 
		{
			glEnable(GL_BLEND);
			glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
		}
		else glDisable(GL_BLEND);
	}

	// ok
	return TB_TRUE;
}
static __tb_inline__ tb_void_t g2_gl10_fill_context_exit(g2_gl10_fill_t* fill)
{
	// disable vertices
	glDisableClientState(GL_VERTEX_ARRAY);
	
	// disable antialiasing
	glDisable(GL_POINT_SMOOTH);
	glDisable(GL_LINE_SMOOTH);
#ifndef TB_CONFIG_OS_ANDROID
	glDisable(GL_POLYGON_SMOOTH);
#endif
	glDisable(GL_MULTISAMPLE);

	// disable blend
	glDisable(GL_BLEND);

	// disable texture 
	glActiveTexture(GL_TEXTURE0);
	glDisable(GL_TEXTURE_2D);
}
static __tb_inline__ tb_void_t g2_gl10_fill_style_draw(g2_gl10_fill_t* fill, g2_gl10_rect_t const* bounds)
{
	// style
	tb_handle_t 	style = fill->style;

	// mode
	tb_size_t 		mode = g2_style_mode(style);

	// flag
	tb_size_t 		flag = g2_style_flag(style);

	// rect or stencil?
	tb_check_return(fill->flag & (G2_GL10_FILL_FLAG_RECT | G2_GL10_FILL_FLAG_STENCIL));

	// fill shader
	g2_gl10_shader_t const* shader = g2_style_shader(style);
	if (shader)
	{
		if (shader->type == G2_GL10_SHADER_TYPE_BITMAP)
		{
			// init texture
    		glEnable(GL_TEXTURE_2D);
			glActiveTexture(GL_TEXTURE0);
			glBindTexture(GL_TEXTURE_2D, (tb_uint_t)shader->texture);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
 			glTexEnvi(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);
    
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
			
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT); 
			
			// texcoords
			tb_float_t texcoords[] = 
			{
				0.0f, 0.0f
			, 	1.0f, 0.0f
			, 	0.0f, 1.0f
			, 	1.0f, 1.0f
			};
			glTexCoordPointer(2, GL_FLOAT, 0, texcoords);

			static tb_byte_t* data = TB_NULL;
			if (!data)
			{
				data = tb_malloc(300 * 300 * 4);
				tb_memset(data, 0x55, 300 * 300 * 4);
			}
			glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, 300, 300, 0, GL_BGRA, GL_UNSIGNED_BYTE, data);

			// init rect
			tb_float_t vertices[8];
			vertices[0] = bounds->x1;
			vertices[1] = bounds->y1;
			vertices[2] = bounds->x2;
			vertices[3] = bounds->y1;
			vertices[4] = bounds->x1;
			vertices[5] = bounds->y2;
			vertices[6] = bounds->x2;
			vertices[7] = bounds->y2;

			// draw rect
			glVertexPointer(2, GL_FLOAT, 0, vertices);
			glDrawArrays(GL_TRIANGLE_STRIP, 0, 4);

			// exit texture
 			glActiveTexture(GL_TEXTURE0);
			glDisable(GL_TEXTURE_2D);
		}
	}
	else
	{
		// init rect
		tb_float_t vertices[8];
		vertices[0] = bounds->x1;
		vertices[1] = bounds->y1;
		vertices[2] = bounds->x2;
		vertices[3] = bounds->y1;
		vertices[4] = bounds->x1;
		vertices[5] = bounds->y2;
		vertices[6] = bounds->x2;
		vertices[7] = bounds->y2;

		// draw rect
		glVertexPointer(2, GL_FLOAT, 0, vertices);
		glDrawArrays(GL_TRIANGLE_STRIP, 0, 4);
	}
}
static __tb_inline__ tb_bool_t g2_gl10_fill_init(g2_gl10_fill_t* fill, g2_gl10_painter_t* painter, tb_size_t flag)
{
	// init fill
	fill->painter 	= painter;
	fill->style 	= painter->style_usr;
	fill->flag 		= flag;
	fill->flag 		= !(flag & G2_GL10_FILL_FLAG_CONVEX) || g2_style_shader(fill->style)? (flag | G2_GL10_FILL_FLAG_STENCIL) : flag;
	tb_assert_and_check_return_val(painter && painter->style_usr, TB_FALSE);

	// init context
	if (!g2_gl10_fill_context_init(fill)) return TB_FALSE;
	
	// enter matrix
	g2_gl10_fill_matrix_enter(fill);

	// use stencil?
	if (fill->flag & G2_GL10_FILL_FLAG_STENCIL)
	{
		// init stencil
		g2_gl10_fill_stencil_init(fill);

		// enter stencil
		g2_gl10_fill_stencil_enter(fill);
	}

	// ok
	return TB_TRUE;
}
static __tb_inline__ tb_void_t g2_gl10_fill_draw(g2_gl10_fill_t* fill, g2_gl10_rect_t* bounds)
{
	// leave stencil
	if (fill->flag & G2_GL10_FILL_FLAG_STENCIL)
		g2_gl10_fill_stencil_leave(fill);

	// draw style
	g2_gl10_fill_style_draw(fill, bounds);
}
static __tb_inline__ tb_void_t g2_gl10_fill_exit(g2_gl10_fill_t* fill)
{
	// leave matrix
	g2_gl10_fill_matrix_leave(fill);

	// exit stencil
	if (fill->flag & G2_GL10_FILL_FLAG_STENCIL) 
		g2_gl10_fill_stencil_exit(fill);

	// exit fill style
	g2_gl10_fill_context_exit(fill);
}
static tb_void_t g2_gl10_fill_split_circle_func(g2_soft_split_circle_t* split, g2_point_t const* pt)
{
	// vertices
	tb_vector_t* vertices = (tb_vector_t*)split->data;
	tb_assert_return(vertices);

	// data
	tb_float_t data[2];
	data[0] = g2_float_to_tb(pt->x);
	data[1] = g2_float_to_tb(pt->y);

	// add
	tb_vector_insert_tail(vertices, data);
}
static tb_void_t g2_gl10_fill_split_ellipse_func(g2_soft_split_ellipse_t* split, g2_point_t const* pt)
{
	// vertices
	tb_vector_t* vertices = (tb_vector_t*)split->data;
	tb_assert_return(vertices);

	// data
	tb_float_t data[2];
	data[0] = g2_float_to_tb(pt->x);
	data[1] = g2_float_to_tb(pt->y);

	// add
	tb_vector_insert_tail(vertices, data);
}
/* ///////////////////////////////////////////////////////////////////////
 * interfaces
 */
tb_void_t g2_gl10_fill_rect(g2_gl10_painter_t* painter, g2_rect_t const* rect)
{
	// init bounds
	g2_gl10_rect_t bounds;
	bounds.x1 = g2_float_to_tb(rect->x);
	bounds.y1 = g2_float_to_tb(rect->y);
	bounds.x2 = g2_float_to_tb(rect->x + rect->w - 1);
	bounds.y2 = g2_float_to_tb(rect->y + rect->h - 1);
	tb_check_return(bounds.x1 < bounds.x2 && bounds.y1 < bounds.y2);

	// init fill
	g2_gl10_fill_t fill = {0};
	if (!g2_gl10_fill_init(&fill, painter, G2_GL10_FILL_FLAG_RECT | G2_GL10_FILL_FLAG_CONVEX)) return ;

	// draw fill
	g2_gl10_fill_draw(&fill, &bounds);

	// exit fill
	g2_gl10_fill_exit(&fill);
}
tb_void_t g2_gl10_fill_path(g2_gl10_painter_t* painter, g2_gl10_path_t const* path)
{
	// check
	tb_assert(path->fill.data && tb_vector_size(path->fill.data));
	tb_assert(path->fill.size && tb_vector_size(path->fill.size));
	tb_check_return(path->fill.rect.x1 < path->fill.rect.x2 && path->fill.rect.y1 < path->fill.rect.y2);
	
	// fill
	g2_gl10_fill_t fill = {0};

	// like rect?
	if (path->like == G2_GL10_PATH_LIKE_RECT)
	{
		// init fill
		if (!g2_gl10_fill_init(&fill, painter, G2_GL10_FILL_FLAG_RECT | G2_GL10_FILL_FLAG_CONVEX)) return ;

		// draw fill
		g2_gl10_fill_draw(&fill, &path->rect);

		// exit fill
		g2_gl10_fill_exit(&fill);

		// ok
		return ;
	}
	// like triangle?
	else if (path->like == G2_GL10_PATH_LIKE_TRIG)
	{
		// fill triangle
		g2_gl10_fill_triangle(painter, &path->trig);

		// ok
		return ;
	}

	// init fill
	if (!g2_gl10_fill_init(&fill, painter, path->like == G2_GL10_PATH_LIKE_CONX? G2_GL10_FILL_FLAG_CONVEX : G2_GL10_FILL_FLAG_NONE)) return ;

	// init vertices
	glVertexPointer(2, GL_FLOAT, 0, tb_vector_data(path->fill.data));

	// draw path
	tb_size_t 	head = 0;
	tb_size_t 	size = 0;
	tb_size_t 	itor = tb_iterator_head(path->fill.size);
	tb_size_t 	tail = tb_iterator_tail(path->fill.size);
	for (; itor != tail; itor++)
	{
		size = tb_iterator_item(path->fill.size, itor);
		glDrawArrays(GL_TRIANGLE_FAN, (tb_int_t)head, (tb_int_t)size);
		head += size;
	}

	// draw fill
	g2_gl10_fill_draw(&fill, &path->fill.rect);

	// exit fill
	g2_gl10_fill_exit(&fill);
}
tb_void_t g2_gl10_fill_circle(g2_gl10_painter_t* painter, g2_circle_t const* circle)
{
	// init bounds
	g2_gl10_rect_t bounds;
	bounds.x1 = circle->c.x - circle->r;
	bounds.y1 = circle->c.y - circle->r;
	bounds.x2 = circle->c.x + circle->r - 1;
	bounds.y2 = circle->c.y + circle->r - 1;
	tb_check_return(bounds.x1 < bounds.x2 && bounds.y1 < bounds.y2);
	
	// init vertices
	tb_assert_and_check_return(painter->vertices);
	tb_vector_clear(painter->vertices);

	// split circle, FIXME: cache it
	g2_soft_split_circle_t split;
	g2_soft_split_circle_init(&split, g2_gl10_fill_split_circle_func, painter->vertices);
	g2_soft_split_circle_done(&split, circle);

	// data & size
	tb_float_t* data = tb_vector_data(painter->vertices);
	tb_size_t 	size = tb_vector_size(painter->vertices);
	tb_assert_and_check_return(data && size > 2);

	// init fill
	g2_gl10_fill_t fill = {0};
	if (!g2_gl10_fill_init(&fill, painter, G2_GL10_FILL_FLAG_CONVEX)) return ;

	// draw vertices
	glVertexPointer(2, GL_FLOAT, 0, data);
	glDrawArrays(GL_TRIANGLE_FAN, 0, (tb_int_t)size);

	// draw fill
	g2_gl10_fill_draw(&fill, &bounds);

	// exit fill
	g2_gl10_fill_exit(&fill);
}
tb_void_t g2_gl10_fill_ellipse(g2_gl10_painter_t* painter, g2_ellipse_t const* ellipse)
{
	// init bounds
	g2_gl10_rect_t bounds;
	bounds.x1 = ellipse->c0.x - ellipse->rx;
	bounds.y1 = ellipse->c0.y - ellipse->ry;
	bounds.x2 = ellipse->c0.x + ellipse->rx - 1;
	bounds.y2 = ellipse->c0.y + ellipse->ry - 1;
	tb_check_return(bounds.x1 < bounds.x2 && bounds.y1 < bounds.y2);
	
	// init vertices
	tb_assert_and_check_return(painter->vertices);
	tb_vector_clear(painter->vertices);

	// split ellipse, FIXME: cache it
	g2_soft_split_ellipse_t split;
	g2_soft_split_ellipse_init(&split, g2_gl10_fill_split_ellipse_func, painter->vertices);
	g2_soft_split_ellipse_done(&split, ellipse);

	// data & size
	tb_float_t* data = tb_vector_data(painter->vertices);
	tb_size_t 	size = tb_vector_size(painter->vertices);
	tb_assert_and_check_return(data && size > 2);

	// init fill
	g2_gl10_fill_t fill = {0};
	if (!g2_gl10_fill_init(&fill, painter, G2_GL10_FILL_FLAG_CONVEX)) return ;

	// draw vertices
	glVertexPointer(2, GL_FLOAT, 0, data);
	glDrawArrays(GL_TRIANGLE_FAN, 0, (tb_int_t)size);

	// draw fill
	g2_gl10_fill_draw(&fill, &bounds);

	// exit fill
	g2_gl10_fill_exit(&fill);
}
tb_void_t g2_gl10_fill_triangle(g2_gl10_painter_t* painter, g2_triangle_t const* triangle)
{
	// init vertices
	tb_float_t vertices[6];
	vertices[0] = g2_float_to_tb(triangle->p0.x);
	vertices[1] = g2_float_to_tb(triangle->p0.y);
	vertices[2] = g2_float_to_tb(triangle->p1.x);
	vertices[3] = g2_float_to_tb(triangle->p1.y);
	vertices[4] = g2_float_to_tb(triangle->p2.x);
	vertices[5] = g2_float_to_tb(triangle->p2.y);

	// init bounds
	g2_gl10_rect_t bounds;
	g2_gl10_rect_init(&bounds, vertices[0], vertices[1]);
	g2_gl10_rect_done(&bounds, vertices[2], vertices[3]);
	g2_gl10_rect_done(&bounds, vertices[4], vertices[5]);
	tb_check_return(bounds.x1 < bounds.x2 && bounds.y1 < bounds.y2);

	// init fill
	g2_gl10_fill_t fill = {0};
	if (!g2_gl10_fill_init(&fill, painter, G2_GL10_FILL_FLAG_CONVEX)) return ;

	// draw vertices
	glVertexPointer(2, GL_FLOAT, 0, vertices);
	glDrawArrays(GL_TRIANGLE_STRIP, 0, 3);

	// draw fill
	g2_gl10_fill_draw(&fill, &bounds);

	// exit fill
	g2_gl10_fill_exit(&fill);
}

