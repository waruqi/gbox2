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
 * @file		painter.c
 *
 */
/* ///////////////////////////////////////////////////////////////////////
 * includes
 */
#include "painter.h"
#include "fill.h"

/* ///////////////////////////////////////////////////////////////////////
 * macros
 */

// the vertices grow
#ifdef TB_CONFIG_BINARY_SMALL
# 	define G2_GL_VERTICES_GROW 				(256)
#else
# 	define G2_GL_VERTICES_GROW 				(512)
#endif

// matrix
#ifdef TB_CONFIG_BINARY_SMALL
# 	define G2_GL_MATRIX_STACK_GROW 			(32)
# 	define G2_GL_MATRIX_CACHE_SIZE 			(4)
#else
# 	define G2_GL_MATRIX_STACK_GROW 			(64)
# 	define G2_GL_MATRIX_CACHE_SIZE 			(8)
#endif

// style
#ifdef TB_CONFIG_BINARY_SMALL
# 	define G2_GL_STYLE_STACK_GROW 			(32)
# 	define G2_GL_STYLE_CACHE_SIZE 			(4)
#else
# 	define G2_GL_STYLE_STACK_GROW 			(64)
# 	define G2_GL_STYLE_CACHE_SIZE 			(8)
#endif

// clipper
#ifdef TB_CONFIG_BINARY_SMALL
# 	define G2_GL_CLIPPER_STACK_GROW 		(32)
# 	define G2_GL_CLIPPER_CACHE_SIZE 		(4)
# 	define G2_GL_CLIPPER_HASH_SIZE 			(8)
#else
# 	define G2_GL_CLIPPER_STACK_GROW 		(64)
# 	define G2_GL_CLIPPER_CACHE_SIZE 		(8)
# 	define G2_GL_CLIPPER_HASH_SIZE 			(16)
#endif
#define G2_GL_CLIPPER_HASH_ITEM_MAXN 		(G2_GL_CLIPPER_HASH_SIZE * G2_GL_CLIPPER_HASH_SIZE)

/* ///////////////////////////////////////////////////////////////////////
 * helper
 */
static tb_bool_t g2_gl_style_stack_item_free(tb_stack_t* stack, tb_pointer_t* item, tb_bool_t* bdel, tb_pointer_t data)
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
static tb_bool_t g2_gl_clipper_stack_item_free(tb_stack_t* stack, tb_pointer_t* item, tb_bool_t* bdel, tb_pointer_t data)
{
	tb_assert_and_check_return_val(stack && bdel, TB_FALSE);

	// free clipper item
	if (item) 
	{
		tb_handle_t clipper = (tb_handle_t)*item;
		if (clipper) g2_clipper_exit(clipper);
		*item = TB_NULL;
	}

	// ok
	return TB_TRUE;
}
static tb_void_t g2_gl_clipper_hash_item_free(tb_item_func_t* func, tb_pointer_t item)
{
	if (item) g2_path_exit(item);
}
/* ///////////////////////////////////////////////////////////////////////
 * implementation
 */
tb_handle_t g2_init(tb_handle_t context)
{
	// check
	tb_assert_and_check_return_val(context, TB_NULL);

	// init variables
	tb_size_t 		i = 0;
	tb_item_func_t 	clipper_hash_item_func = tb_item_func_ptr();

	// alloc
	g2_gl_painter_t* gpainter = tb_malloc0(sizeof(g2_gl_painter_t));
	tb_assert_and_check_return_val(gpainter, TB_NULL);

	// init context
	gpainter->context = (g2_gl_context_t*)context;

	// init vertices
	gpainter->vertices = tb_vector_init(G2_GL_VERTICES_GROW, tb_item_func_ifm(sizeof(tb_float_t) << 1, TB_NULL, TB_NULL));
	tb_assert_and_check_goto(gpainter->vertices, fail);

	// init matrix
	g2_matrix_clear(&gpainter->matrix);

	// init matrix stack
	gpainter->matrix_stack = tb_stack_init(G2_GL_MATRIX_STACK_GROW, tb_item_func_ifm(sizeof(g2_matrix_t), TB_NULL, TB_NULL));
	tb_assert_and_check_goto(gpainter->matrix_stack, fail);

	// init style
	gpainter->style = g2_style_init();
	tb_assert_and_check_goto(gpainter->style, fail);

	// init style stack
	gpainter->style_stack = tb_stack_init(G2_GL_STYLE_STACK_GROW, tb_item_func_ptr());
	tb_assert_and_check_goto(gpainter->style_stack, fail);

	// init style cache
	gpainter->style_cache = tb_stack_init(G2_GL_STYLE_CACHE_SIZE, tb_item_func_ptr());
	tb_assert_and_check_goto(gpainter->style_cache, fail);
	for (i = 0; i < G2_GL_STYLE_CACHE_SIZE; i++)
	{
		// init
		tb_handle_t style = g2_style_init();
		tb_assert_and_check_goto(style, fail);

		// put
		tb_stack_put(gpainter->style_cache, style);
	}

	// init clipper
	gpainter->clipper = g2_clipper_init();
	tb_assert_and_check_goto(gpainter->clipper, fail);

	// init clipper hash
	clipper_hash_item_func.free = g2_gl_clipper_hash_item_free;
	gpainter->clipper_hash = tb_hash_init(G2_GL_CLIPPER_HASH_SIZE, tb_item_func_ifm(sizeof(g2_shape_t), TB_NULL, TB_NULL), clipper_hash_item_func);
	tb_assert_and_check_goto(gpainter->clipper_hash, fail);

	// init clipper stack
	gpainter->clipper_stack = tb_stack_init(G2_GL_CLIPPER_STACK_GROW, tb_item_func_ptr());
	tb_assert_and_check_goto(gpainter->clipper_stack, fail);

	// init clipper cache
	gpainter->clipper_cache = tb_stack_init(G2_GL_CLIPPER_CACHE_SIZE, tb_item_func_ptr());
	tb_assert_and_check_goto(gpainter->clipper_cache, fail);
	for (i = 0; i < G2_GL_CLIPPER_CACHE_SIZE; i++)
	{
		// init
		tb_handle_t clipper = g2_clipper_init();
		tb_assert_and_check_goto(clipper, fail);

		// put
		tb_stack_put(gpainter->clipper_cache, clipper);
	}

	// ok
	return gpainter;

fail:
	if (gpainter) g2_exit(gpainter);
	return TB_NULL;
}
tb_void_t g2_exit(tb_handle_t painter)
{
	g2_gl_painter_t* gpainter = (g2_gl_painter_t*)painter;
	if (gpainter)
	{
		// exit vertices
		if (gpainter->vertices) tb_vector_exit(gpainter->vertices);

		// exit matrix stack
		if (gpainter->matrix_stack) tb_stack_exit(gpainter->matrix_stack);
		gpainter->matrix_stack = TB_NULL;

		// exit style
		if (gpainter->style) g2_style_exit(gpainter->style);
		gpainter->style = TB_NULL;

		// exit style cache
		if (gpainter->style_cache) 
		{
			tb_stack_walk(gpainter->style_cache, g2_gl_style_stack_item_free, TB_NULL);
			tb_stack_exit(gpainter->style_cache);
		}
		gpainter->style_cache = TB_NULL;
		
		// exit style stack
		if (gpainter->style_stack) 
		{
			tb_stack_walk(gpainter->style_stack, g2_gl_style_stack_item_free, TB_NULL);
			tb_stack_exit(gpainter->style_stack);
		}
		gpainter->style_stack = TB_NULL;

		// exit clipper
		if (gpainter->clipper) g2_style_exit(gpainter->clipper);
		gpainter->clipper = TB_NULL;

		// exit clipper hash
		if (gpainter->clipper_hash) tb_hash_exit(gpainter->clipper_hash);
		gpainter->clipper_hash = TB_NULL;

		// exit clipper cache
		if (gpainter->clipper_cache) 
		{
			tb_stack_walk(gpainter->clipper_cache, g2_gl_clipper_stack_item_free, TB_NULL);
			tb_stack_exit(gpainter->clipper_cache);
		}
		gpainter->clipper_cache = TB_NULL;
		
		// exit clipper stack
		if (gpainter->clipper_stack) 
		{
			tb_stack_walk(gpainter->clipper_stack, g2_gl_clipper_stack_item_free, TB_NULL);
			tb_stack_exit(gpainter->clipper_stack);
		}
		gpainter->clipper_stack = TB_NULL;

		// free it
		tb_free(gpainter);
	}
}
tb_size_t g2_pixfmt(tb_handle_t painter)
{
	g2_gl_painter_t* gpainter = (g2_gl_painter_t*)painter;
	tb_assert_and_check_return_val(gpainter && gpainter->context, G2_PIXFMT_NONE);

	return g2_bitmap_pixfmt(g2_context_surface(gpainter->context));
}
tb_handle_t g2_context(tb_handle_t painter)
{
	g2_gl_painter_t* gpainter = (g2_gl_painter_t*)painter;
	tb_assert_and_check_return_val(gpainter, TB_NULL);

	return (tb_handle_t)gpainter->context;
}
tb_handle_t g2_style(tb_handle_t painter)
{
	g2_gl_painter_t* gpainter = (g2_gl_painter_t*)painter;
	tb_assert_and_check_return_val(gpainter, TB_NULL);

	return gpainter->style;
}
tb_handle_t g2_save_style(tb_handle_t painter)
{
	g2_gl_painter_t* gpainter = (g2_gl_painter_t*)painter;
	tb_assert_and_check_return_val(gpainter && gpainter->style_cache && gpainter->style_stack, TB_NULL);

	// init a new style from cache first
	tb_handle_t style = TB_NULL;
	if (tb_stack_size(gpainter->style_cache))
	{
		// get
		style = (tb_handle_t)tb_stack_top(gpainter->style_cache);
		tb_assert_and_check_return_val(gpainter->style_cache, TB_NULL);

		// pop
		tb_stack_pop(gpainter->style_cache);
	}
	// init a new style
	else style = g2_style_init();
	tb_assert_and_check_return_val(style, TB_NULL);

	// save the old style
	tb_stack_put(gpainter->style_stack, gpainter->style);

	// copy the new style
	g2_style_copy(style, gpainter->style);
	gpainter->style = style;

	// ok
	return gpainter->style;
}
tb_void_t g2_load_style(tb_handle_t painter)
{
	g2_gl_painter_t* gpainter = (g2_gl_painter_t*)painter;
	tb_assert_and_check_return(gpainter && gpainter->style_cache && gpainter->style_stack);

	// load the top style
	tb_handle_t style = (tb_handle_t)tb_stack_top(gpainter->style_stack);
	tb_assert_and_check_return(style);
	tb_stack_pop(gpainter->style_stack);

	// free style to cache first
	if (gpainter->style && tb_stack_size(gpainter->style_cache) < G2_GL_STYLE_CACHE_SIZE)
		tb_stack_put(gpainter->style_cache, gpainter->style);
	// free style
	else g2_style_exit(gpainter->style);

	// copy the top style
	gpainter->style = style;
}
g2_matrix_t* g2_matrix(tb_handle_t painter)
{
	g2_gl_painter_t* gpainter = (g2_gl_painter_t*)painter;
	tb_assert_and_check_return_val(gpainter, TB_NULL);

	return &gpainter->matrix;
}
g2_matrix_t* g2_save_matrix(tb_handle_t painter)
{
	g2_gl_painter_t* gpainter = (g2_gl_painter_t*)painter;
	tb_assert_and_check_return_val(gpainter && gpainter->matrix_stack, TB_NULL);

	// save matrix
	tb_stack_put(gpainter->matrix_stack, &gpainter->matrix);

	// ok
	return &gpainter->matrix;
}
tb_void_t g2_load_matrix(tb_handle_t painter)
{
	g2_gl_painter_t* gpainter = (g2_gl_painter_t*)painter;
	tb_assert_and_check_return(gpainter && gpainter->matrix_stack);

	// init matrix
	g2_matrix_t const* matrix = (g2_matrix_t const*)tb_stack_top(gpainter->matrix_stack);
	tb_assert_and_check_return(matrix);

	// load matrix
	gpainter->matrix = *matrix;

	// pop it
	tb_stack_pop(gpainter->matrix_stack);
}
tb_handle_t g2_clipper(tb_handle_t painter)
{
	g2_gl_painter_t* gpainter = (g2_gl_painter_t*)painter;
	tb_assert_and_check_return_val(gpainter, TB_NULL);

	return gpainter->clipper;
}
tb_handle_t g2_save_clipper(tb_handle_t painter)
{
	g2_gl_painter_t* gpainter = (g2_gl_painter_t*)painter;
	tb_assert_and_check_return_val(gpainter && gpainter->clipper_cache && gpainter->clipper_stack, TB_NULL);

	// init a new clipper from cache first
	tb_handle_t clipper = TB_NULL;
	if (tb_stack_size(gpainter->clipper_cache))
	{
		// get
		clipper = (tb_handle_t)tb_stack_top(gpainter->clipper_cache);
		tb_assert_and_check_return_val(gpainter->clipper_cache, TB_NULL);

		// pop
		tb_stack_pop(gpainter->clipper_cache);
	}
	// init a new clipper
	else clipper = g2_clipper_init();
	tb_assert_and_check_return_val(clipper, TB_NULL);

	// save the old clipper
	tb_stack_put(gpainter->clipper_stack, gpainter->clipper);

	// copy the new clipper
	g2_clipper_copy(clipper, gpainter->clipper);
	gpainter->clipper = clipper;

	// ok
	return gpainter->clipper;
}
tb_void_t g2_load_clipper(tb_handle_t painter)
{
	g2_gl_painter_t* gpainter = (g2_gl_painter_t*)painter;
	tb_assert_and_check_return(gpainter && gpainter->clipper_cache && gpainter->clipper_stack);

	// load the top clipper
	tb_handle_t clipper = (tb_handle_t)tb_stack_top(gpainter->clipper_stack);
	tb_assert_and_check_return(clipper);
	tb_stack_pop(gpainter->clipper_stack);

	// free clipper to cache first
	if (gpainter->clipper && tb_stack_size(gpainter->clipper_cache) < G2_GL_CLIPPER_CACHE_SIZE)
		tb_stack_put(gpainter->clipper_cache, gpainter->clipper);
	// free clipper
	else g2_clipper_exit(gpainter->clipper);

	// copy the top clipper
	gpainter->clipper = clipper;
}
tb_void_t g2_draw_clear(tb_handle_t painter, g2_color_t color)
{
	// clear
	g2_glClearColor((tb_float_t)color.r / 0xff, (tb_float_t)color.g / 0xff, (tb_float_t)color.b / 0xff, (tb_float_t)color.a / 0xff);
	g2_glClear(G2_GL_COLOR_BUFFER_BIT | G2_GL_STENCIL_BUFFER_BIT);
}
tb_void_t g2_draw_path(tb_handle_t painter, tb_handle_t path)
{
	g2_gl_painter_t* gpainter = (g2_gl_painter_t*)painter;
	tb_assert_and_check_return(gpainter && gpainter->style && path);

	// like
	g2_gl_path_make_like((g2_gl_path_t*)path);

	// fill
	if (g2_gl_path_make_fill((g2_gl_path_t*)path))
		g2_gl_fill_path(gpainter, (g2_gl_path_t const*)path);
}
tb_void_t g2_draw_arc(tb_handle_t painter, g2_arc_t const* arc)
{
	tb_trace_noimpl();
}
tb_void_t g2_draw_rect(tb_handle_t painter, g2_rect_t const* rect)
{
	g2_gl_painter_t* gpainter = (g2_gl_painter_t*)painter;
	tb_assert_and_check_return(gpainter && gpainter->style && rect);

	// fill
	g2_gl_fill_rect(gpainter, rect);
}
tb_void_t g2_draw_line(tb_handle_t painter, g2_line_t const* line)
{
	tb_trace_noimpl();
}
tb_void_t g2_draw_point(tb_handle_t painter, g2_point_t const* point)
{
	tb_trace_noimpl();
}
tb_void_t g2_draw_circle(tb_handle_t painter, g2_circle_t const* circle)
{
	g2_gl_painter_t* gpainter = (g2_gl_painter_t*)painter;
	tb_assert_and_check_return(gpainter && gpainter->style && circle);

	// fill
	g2_gl_fill_circle(gpainter, circle);
}
tb_void_t g2_draw_ellipse(tb_handle_t painter, g2_ellipse_t const* ellipse)
{
	g2_gl_painter_t* gpainter = (g2_gl_painter_t*)painter;
	tb_assert_and_check_return(gpainter && gpainter->style && ellipse);

	// fill
	g2_gl_fill_ellipse(gpainter, ellipse);
}
tb_void_t g2_draw_triangle(tb_handle_t painter, g2_triangle_t const* triangle)
{
	g2_gl_painter_t* gpainter = (g2_gl_painter_t*)painter;
	tb_assert_and_check_return(gpainter && gpainter->style && triangle);

	// fill
	g2_gl_fill_triangle(gpainter, triangle);
}
