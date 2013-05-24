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
#include "stok.h"

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
 * implementation
 */
tb_handle_t g2_init(tb_handle_t context)
{
	// check
	tb_assert_and_check_return_val(context, tb_null);

	// init func
	g2_cstack_func_t func_path 		= {g2_path_init, 		g2_path_exit, 		g2_path_copy};
	g2_cstack_func_t func_style 	= {g2_style_init, 		g2_style_exit, 		g2_style_copy};
	g2_cstack_func_t func_clipper 	= {g2_clipper_init, 	g2_clipper_exit, 	g2_clipper_copy};

	// alloc
	g2_gl_painter_t* gpainter = tb_malloc0(sizeof(g2_gl_painter_t));
	tb_assert_and_check_return_val(gpainter, tb_null);

	// init context
	gpainter->context = (g2_gl_context_t*)context;

	// init matrix
	g2_matrix_clear(&gpainter->matrix);

	// init matrix stack
	gpainter->stack_matrix = tb_stack_init(G2_GL_MATRIX_GROW, tb_item_func_ifm(sizeof(g2_matrix_t), tb_null, tb_null));
	tb_assert_and_check_goto(gpainter->stack_matrix, fail);

	// init style stack
	gpainter->stack_style = g2_cstack_init(G2_GL_CACHE_STYLE_SIZE, &func_style);
	tb_assert_and_check_goto(gpainter->stack_style, fail);

	// init clipper stack
	gpainter->stack_clipper = g2_cstack_init(G2_GL_CACHE_CLIPPER_SIZE, &func_clipper);
	tb_assert_and_check_goto(gpainter->stack_clipper, fail);

	// init path stack
	gpainter->stack_path = g2_cstack_init(G2_GL_CACHE_PATH_SIZE, &func_path);
	tb_assert_and_check_goto(gpainter->stack_path, fail);

	// init pcache
	gpainter->pcache = g2_pcache_init(G2_GL_PCACHE_MAXN);
	tb_assert_and_check_goto(gpainter->pcache, fail);

	// ok
	return gpainter;

fail:
	if (gpainter) g2_exit(gpainter);
	return tb_null;
}
tb_void_t g2_exit(tb_handle_t painter)
{
	g2_gl_painter_t* gpainter = (g2_gl_painter_t*)painter;
	if (gpainter)
	{
		// exit matrix stack
		if (gpainter->stack_matrix) tb_stack_exit(gpainter->stack_matrix);
		gpainter->stack_matrix = tb_null;

		// exit path stack
		if (gpainter->stack_path) g2_cstack_exit(gpainter->stack_path);
		gpainter->stack_path = tb_null;

		// exit style stack
		if (gpainter->stack_style) g2_cstack_exit(gpainter->stack_style);
		gpainter->stack_style = tb_null;

		// exit clipper stack
		if (gpainter->stack_clipper) g2_cstack_exit(gpainter->stack_clipper);
		gpainter->stack_clipper = tb_null;

		// exit pcache
		if (gpainter->pcache) g2_pcache_exit(gpainter->pcache);
		gpainter->pcache = tb_null;

		// free it
		tb_free(gpainter);
	}
}
tb_size_t g2_pixfmt(tb_handle_t painter)
{
	// check
	g2_gl_painter_t* gpainter = (g2_gl_painter_t*)painter;
	tb_assert_and_check_return_val(gpainter && gpainter->context, G2_PIXFMT_NONE);

	return g2_bitmap_pixfmt(g2_context_surface(gpainter->context));
}
tb_handle_t g2_context(tb_handle_t painter)
{
	// check
	g2_gl_painter_t* gpainter = (g2_gl_painter_t*)painter;
	tb_assert_and_check_return_val(gpainter, tb_null);

	return (tb_handle_t)gpainter->context;
}
tb_handle_t g2_path(tb_handle_t painter)
{
	// check
	g2_gl_painter_t* gpainter = (g2_gl_painter_t*)painter;
	tb_assert_and_check_return_val(gpainter && gpainter->stack_path, tb_null);

	return g2_cstack_object(gpainter->stack_path);
}
tb_handle_t g2_save_path(tb_handle_t painter)
{
	// check
	g2_gl_painter_t* gpainter = (g2_gl_painter_t*)painter;
	tb_assert_and_check_return_val(gpainter && gpainter->stack_path, tb_null);

	// save
	return g2_cstack_save(gpainter->stack_path);
}
tb_void_t g2_load_path(tb_handle_t painter)
{
	// check
	g2_gl_painter_t* gpainter = (g2_gl_painter_t*)painter;
	tb_assert_and_check_return(gpainter && gpainter->stack_path);

	// load
	g2_cstack_load(gpainter->stack_path);
}
g2_matrix_t* g2_matrix(tb_handle_t painter)
{
	// check
	g2_gl_painter_t* gpainter = (g2_gl_painter_t*)painter;
	tb_assert_and_check_return_val(gpainter, tb_null);

	return &gpainter->matrix;
}
g2_matrix_t* g2_save_matrix(tb_handle_t painter)
{
	// check
	g2_gl_painter_t* gpainter = (g2_gl_painter_t*)painter;
	tb_assert_and_check_return_val(gpainter && gpainter->stack_matrix, tb_null);

	// save matrix
	tb_stack_put(gpainter->stack_matrix, &gpainter->matrix);

	// ok
	return &gpainter->matrix;
}
tb_void_t g2_load_matrix(tb_handle_t painter)
{
	// check
	g2_gl_painter_t* gpainter = (g2_gl_painter_t*)painter;
	tb_assert_and_check_return(gpainter && gpainter->stack_matrix);

	// init matrix
	g2_matrix_t const* matrix = (g2_matrix_t const*)tb_stack_top(gpainter->stack_matrix);
	tb_assert_and_check_return(matrix);

	// load matrix
	gpainter->matrix = *matrix;

	// pop it
	tb_stack_pop(gpainter->stack_matrix);
}
tb_handle_t g2_style(tb_handle_t painter)
{
	// check
	g2_gl_painter_t* gpainter = (g2_gl_painter_t*)painter;
	tb_assert_and_check_return_val(gpainter && gpainter->stack_style, tb_null);

	return g2_cstack_object(gpainter->stack_style);
}
tb_handle_t g2_save_style(tb_handle_t painter)
{
	// check
	g2_gl_painter_t* gpainter = (g2_gl_painter_t*)painter;
	tb_assert_and_check_return_val(gpainter && gpainter->stack_style, tb_null);

	// save
	return g2_cstack_save(gpainter->stack_style);
}
tb_void_t g2_load_style(tb_handle_t painter)
{
	// check
	g2_gl_painter_t* gpainter = (g2_gl_painter_t*)painter;
	tb_assert_and_check_return(gpainter && gpainter->stack_style);

	// load
	g2_cstack_load(gpainter->stack_style);
}
tb_handle_t g2_clipper(tb_handle_t painter)
{
	// check
	g2_gl_painter_t* gpainter = (g2_gl_painter_t*)painter;
	tb_assert_and_check_return_val(gpainter && gpainter->stack_clipper, tb_null);

	return g2_cstack_object(gpainter->stack_clipper);
}
tb_handle_t g2_save_clipper(tb_handle_t painter)
{
	// check
	g2_gl_painter_t* gpainter = (g2_gl_painter_t*)painter;
	tb_assert_and_check_return_val(gpainter && gpainter->stack_clipper, tb_null);

	// save
	return g2_cstack_save(gpainter->stack_clipper);
}
tb_void_t g2_load_clipper(tb_handle_t painter)
{
	// check
	g2_gl_painter_t* gpainter = (g2_gl_painter_t*)painter;
	tb_assert_and_check_return(gpainter && gpainter->stack_clipper);

	// load
	g2_cstack_load(gpainter->stack_clipper);
}
tb_void_t g2_draw_clear(tb_handle_t painter, g2_color_t color)
{
	// clear
	g2_glClearColor((tb_float_t)color.r / 0xff, (tb_float_t)color.g / 0xff, (tb_float_t)color.b / 0xff, (tb_float_t)color.a / 0xff);
	g2_glClear(G2_GL_COLOR_BUFFER_BIT | G2_GL_STENCIL_BUFFER_BIT);
}
tb_void_t g2_draw_path(tb_handle_t painter, tb_handle_t path)
{
	// check
	g2_gl_painter_t* gpainter = (g2_gl_painter_t*)painter;
	tb_assert_and_check_return(gpainter && path);
	
	// the style
	tb_handle_t style = g2_style(painter);
	tb_assert_and_check_return(style);

	// the mode
	tb_size_t mode = g2_style_mode(style);

	// null?
	tb_check_return(!g2_path_null(path));

	// make like
	g2_gl_path_make_like((g2_gl_path_t*)path);

	// make fill
	if ((mode & G2_STYLE_MODE_FILL) && g2_gl_path_make_fill((g2_gl_path_t*)path))
	{
		// fill path
		g2_gl_fill_path(gpainter, (g2_gl_path_t const*)path);
	}
	
	// make stok
	if ((mode & G2_STYLE_MODE_STOK)/* && g2_gl_path_make_stok((g2_gl_path_t*)path)*/)
	{
		// stok path
		g2_gl_stok_path(gpainter, (g2_gl_path_t const*)path);
	}
}
tb_void_t g2_draw_arc(tb_handle_t painter, g2_arc_t const* arc)
{
	// check
	g2_gl_painter_t* gpainter = (g2_gl_painter_t*)painter;
	tb_assert_and_check_return(gpainter && arc);
	
	// the style
	tb_handle_t style = g2_style(painter);
	tb_assert_and_check_return(style);

	// the mode
	tb_size_t mode = g2_style_mode(style);
	tb_assert_and_check_return(mode & G2_STYLE_MODE_STOK);

	// stok
	g2_gl_stok_arc(gpainter, arc);
}
tb_void_t g2_draw_rect(tb_handle_t painter, g2_rect_t const* rect)
{
	// check
	g2_gl_painter_t* gpainter = (g2_gl_painter_t*)painter;
	tb_assert_and_check_return(gpainter && rect);

	// the style
	tb_handle_t style = g2_style(painter);
	tb_assert_and_check_return(style);

	// the mode
	tb_size_t mode = g2_style_mode(style);

	// fill
	if (mode & G2_STYLE_MODE_FILL) g2_gl_fill_rect(gpainter, rect);

	// stok
	if (mode & G2_STYLE_MODE_STOK) g2_gl_stok_rect(gpainter, rect);
}
tb_void_t g2_draw_line(tb_handle_t painter, g2_line_t const* line)
{
	// check
	g2_gl_painter_t* gpainter = (g2_gl_painter_t*)painter;
	tb_assert_and_check_return(gpainter && line);

	// the style
	tb_handle_t style = g2_style(painter);
	tb_assert_and_check_return(style);

	// the mode
	tb_size_t mode = g2_style_mode(style);
	tb_assert_and_check_return(mode & G2_STYLE_MODE_STOK);

	// stok
	g2_gl_stok_line(gpainter, line);
}
tb_void_t g2_draw_point(tb_handle_t painter, g2_point_t const* point)
{
	// check
	g2_gl_painter_t* gpainter = (g2_gl_painter_t*)painter;
	tb_assert_and_check_return(gpainter && point);

	// the style
	tb_handle_t style = g2_style(painter);
	tb_assert_and_check_return(style);

	// the mode
	tb_size_t mode = g2_style_mode(style);
	tb_assert_and_check_return(mode & G2_STYLE_MODE_STOK);

	// stok
	g2_gl_stok_point(gpainter, point);
}
tb_void_t g2_draw_circle(tb_handle_t painter, g2_circle_t const* circle)
{
	// check
	g2_gl_painter_t* gpainter = (g2_gl_painter_t*)painter;
	tb_assert_and_check_return(gpainter && gpainter->pcache && circle);

	// init shape
	g2_shape_t shape = {0};
	shape.type = G2_SHAPE_TYPE_CIRCLE;
	shape.u.circle = *circle;

	// get path from pcache first
	tb_handle_t path = g2_pcache_get(gpainter->pcache, &shape);
	if (!path)
	{
		// init path from cache
		path = g2_pcache_add(gpainter->pcache, &shape);
		tb_assert_and_check_return(path);

		// add circle to path
		g2_path_add_circle(path, circle);
	}
	
	// draw path
	g2_draw_path(painter, path);
}
tb_void_t g2_draw_ellipse(tb_handle_t painter, g2_ellipse_t const* ellipse)
{
	// check
	g2_gl_painter_t* gpainter = (g2_gl_painter_t*)painter;
	tb_assert_and_check_return(gpainter && gpainter->pcache && ellipse);

	// init shape
	g2_shape_t shape = {0};
	shape.type = G2_SHAPE_TYPE_ELLIPSE;
	shape.u.ellipse = *ellipse;

	// get path from pcache first
	tb_handle_t path = g2_pcache_get(gpainter->pcache, &shape);
	if (!path)
	{
		// init path from cache
		path = g2_pcache_add(gpainter->pcache, &shape);
		tb_assert_and_check_return(path);

		// add ellipse to path
		g2_path_add_ellipse(path, ellipse);
	}
	
	// draw path
	g2_draw_path(painter, path);
}
tb_void_t g2_draw_triangle(tb_handle_t painter, g2_triangle_t const* triangle)
{
	// check
	g2_gl_painter_t* gpainter = (g2_gl_painter_t*)painter;
	tb_assert_and_check_return(gpainter && triangle);

	// the style
	tb_handle_t style = g2_style(painter);
	tb_assert_and_check_return(style);

	// the mode
	tb_size_t mode = g2_style_mode(style);

	// fill
	if (mode & G2_STYLE_MODE_FILL) g2_gl_fill_triangle(gpainter, triangle);

	// stok
	if (mode & G2_STYLE_MODE_STOK) g2_gl_stok_triangle(gpainter, triangle);
}
