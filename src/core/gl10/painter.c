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
#include "prefix.h"
#include "context.h"

/* ///////////////////////////////////////////////////////////////////////
 * macros
 */

// the mcstack grow
#ifdef TB_CONFIG_BINARY_SMALL
# 	define G2_GL10_MCSTACK_GROW 				(32)
#else
# 	define G2_GL10_MCSTACK_GROW 				(64)
#endif

/* ///////////////////////////////////////////////////////////////////////
 * types
 */

// the gl110 matrix and clip item type for stack
typedef struct __g2_gl10_mcitem_t
{
	// the mode
	tb_size_t 					mode;

	// the matrix
	g2_matrix_t 				matrix;

	// the clipper
	tb_handle_t 				clipper;

}g2_gl10_mcitem_t;

// the gl10 painter type
typedef struct __g2_gl10_painter_t
{
	// the context
	g2_gl10_context_t* 			context;

	// the matrix
	g2_matrix_t 				matrix;
	GLfloat 					matrix_gl[16];

	// the style
	tb_handle_t 				style_def;
	tb_handle_t 				style_usr;

	// the matrix and clipper stack
	tb_stack_t* 				mcstack;

}g2_gl10_painter_t;

/* ///////////////////////////////////////////////////////////////////////
 * gl10 
 */
static __tb_inline__ tb_void_t g2_gl10_matrix_init(GLfloat* gmatrix)
{
	gmatrix[0] 	= 1.0f;
	gmatrix[1] 	= 0.0f;
	gmatrix[2] 	= 0.0f;
	gmatrix[3] 	= 0.0f;
	gmatrix[4] 	= 0.0f;
	gmatrix[5] 	= 1.0f;
	gmatrix[6] 	= 0.0f; 
	gmatrix[7] 	= 0.0f;       
	gmatrix[8] 	= 0.0f;
	gmatrix[9] 	= 0.0f; 
	gmatrix[10] = 1.0f; 
	gmatrix[11] = 0.0f; 
	gmatrix[12] = 0.0f; 
	gmatrix[13] = 0.0f; 
	gmatrix[14] = 1.0f;
	gmatrix[15] = 1.0f;
}
static __tb_inline__ tb_void_t g2_gl10_matrix_set(GLfloat* gmatrix, g2_matrix_t const* matrix)
{
	gmatrix[0] 	= g2_float_to_tb(matrix->sx);
	gmatrix[1] 	= g2_float_to_tb(matrix->ky);
	gmatrix[2] 	= 0.0f;
	gmatrix[3] 	= 0.0f;
	gmatrix[4] 	= g2_float_to_tb(matrix->kx);
	gmatrix[5] 	= g2_float_to_tb(matrix->sy);
	gmatrix[6] 	= 0.0f; 
	gmatrix[7] 	= 0.0f;       
	gmatrix[8] 	= 0.0f;
	gmatrix[9] 	= 0.0f; 
	gmatrix[10] = 1.0f; 
	gmatrix[11] = 0.0f; 
	gmatrix[12] = g2_float_to_tb(matrix->tx); 
	gmatrix[13] = g2_float_to_tb(matrix->ty); 
	gmatrix[14] = 1.0f;
	gmatrix[15] = 1.0f;
}

/* ///////////////////////////////////////////////////////////////////////
 * implementation
 */
tb_handle_t g2_init(tb_handle_t context)
{
	// check
	tb_assert_and_check_return_val(context, TB_NULL);

	// alloc
	g2_gl10_painter_t* gpainter = tb_malloc0(sizeof(g2_gl10_painter_t));
	tb_assert_and_check_return_val(gpainter, TB_NULL);

	// init context
	gpainter->context = (g2_gl10_context_t*)context;

	// init style
	gpainter->style_def = g2_style_init();
	gpainter->style_usr = gpainter->style_def;
	tb_assert_and_check_goto(gpainter->style_def, fail);

	// init matrix
	g2_matrix_clear(&gpainter->matrix);
	g2_gl10_matrix_init(gpainter->matrix_gl);

	// init stack
	gpainter->mcstack = tb_stack_init(G2_GL10_MCSTACK_GROW, tb_item_func_ifm(sizeof(g2_gl10_mcitem_t), TB_NULL, TB_NULL));
	tb_assert_and_check_goto(gpainter->mcstack, fail);

	// ok
	return gpainter;

fail:
	if (gpainter) g2_exit(gpainter);
	return TB_NULL;
}
tb_void_t g2_exit(tb_handle_t painter)
{
	g2_gl10_painter_t* gpainter = (g2_gl10_painter_t*)painter;
	if (gpainter)
	{
		// exit mcstack
		if (gpainter->mcstack) tb_stack_exit(gpainter->mcstack);

		// free it
		tb_free(gpainter);
	}
}
tb_size_t g2_save(tb_handle_t painter, tb_size_t mode)
{	
	g2_gl10_painter_t* gpainter = (g2_gl10_painter_t*)painter;
	tb_assert_and_check_return_val(gpainter && gpainter->mcstack, 0);

	// no mode?
	tb_assert_and_check_return_val(mode, tb_stack_size(gpainter->mcstack));

	// init item
	g2_gl10_mcitem_t item = {0}; 
	item.mode = mode;

	// save matrix
	if (mode & G2_SAVE_MODE_MATRIX)
		item.matrix = gpainter->matrix;

	// save clipper
	if (mode & G2_SAVE_MODE_CLIP)
		tb_trace_noimpl();

	// put item
	tb_stack_put(gpainter->mcstack, &item);

	// ok
	return tb_stack_size(gpainter->mcstack);
}
tb_void_t g2_load(tb_handle_t painter)
{
	g2_gl10_painter_t* gpainter = (g2_gl10_painter_t*)painter;
	tb_assert_and_check_return(gpainter && gpainter->mcstack);

	// init item
	g2_gl10_mcitem_t* item = tb_stack_top(gpainter->mcstack);
	tb_assert_and_check_return(item);

	// load matrix
	if (item->mode & G2_SAVE_MODE_MATRIX)
		gpainter->matrix = item->matrix;

	// load clipper
	if (item->mode & G2_SAVE_MODE_CLIP)
		tb_trace_noimpl();

	// pop item
	tb_stack_pop(gpainter->mcstack);
}
tb_handle_t g2_style(tb_handle_t painter)
{
	g2_gl10_painter_t* gpainter = (g2_gl10_painter_t*)painter;
	tb_assert_and_check_return_val(gpainter, TB_NULL);

	return gpainter->style_usr;
}
tb_void_t g2_style_set(tb_handle_t painter, tb_handle_t style)
{
	g2_gl10_painter_t* gpainter = (g2_gl10_painter_t*)painter;
	tb_assert_and_check_return(gpainter);

	gpainter->style_usr = style? style : gpainter->style_def;
}
g2_matrix_t const* g2_matrix(tb_handle_t painter)
{
	g2_gl10_painter_t* gpainter = (g2_gl10_painter_t*)painter;
	tb_assert_and_check_return_val(gpainter, TB_NULL);

	return &gpainter->matrix;
}
tb_bool_t g2_rotate(tb_handle_t painter, g2_float_t degrees)
{
	g2_gl10_painter_t* gpainter = (g2_gl10_painter_t*)painter;
	tb_assert_and_check_return_val(gpainter, TB_FALSE);

	return g2_matrix_rotate(&gpainter->matrix, degrees);
}
tb_bool_t g2_skew(tb_handle_t painter, g2_float_t kx, g2_float_t ky)
{
	g2_gl10_painter_t* gpainter = (g2_gl10_painter_t*)painter;
	tb_assert_and_check_return_val(gpainter, TB_FALSE);

	return g2_matrix_skew(&gpainter->matrix, kx, ky);
}
tb_bool_t g2_scale(tb_handle_t painter, g2_float_t sx, g2_float_t sy)
{
	g2_gl10_painter_t* gpainter = (g2_gl10_painter_t*)painter;
	tb_assert_and_check_return_val(gpainter, TB_FALSE);

	return g2_matrix_scale(&gpainter->matrix, sx, sy);
}
tb_bool_t g2_translate(tb_handle_t painter, g2_float_t dx, g2_float_t dy)
{
	g2_gl10_painter_t* gpainter = (g2_gl10_painter_t*)painter;
	tb_assert_and_check_return_val(gpainter, TB_FALSE);

	return g2_matrix_translate(&gpainter->matrix, dx, dy);
}
tb_bool_t g2_multiply(tb_handle_t painter, g2_matrix_t const* matrix)
{
	g2_gl10_painter_t* gpainter = (g2_gl10_painter_t*)painter;
	tb_assert_and_check_return_val(gpainter && matrix, TB_FALSE);

	return g2_matrix_multiply(&gpainter->matrix, matrix);
}
tb_void_t g2_matrix_set(tb_handle_t painter, g2_matrix_t const* matrix)
{
	g2_gl10_painter_t* gpainter = (g2_gl10_painter_t*)painter;
	tb_assert_and_check_return(gpainter);

	if (matrix) gpainter->matrix = *matrix;
	else g2_matrix_clear(&gpainter->matrix);
}
tb_bool_t g2_clip_path(tb_handle_t painter, tb_size_t mode, tb_handle_t path)
{
	tb_trace_noimpl();
	return TB_NULL;
}
tb_bool_t g2_clip_rect(tb_handle_t painter, tb_size_t mode, g2_rect_t const* rect)
{
	tb_trace_noimpl();
	return TB_NULL;
}
tb_void_t g2_clear(tb_handle_t painter, g2_color_t color)
{
	// clear
	glClearColor(color.r / 256., color.g / 256., color.b / 256., color.a / 256.);
	glClear(GL_COLOR_BUFFER_BIT);
}
tb_void_t g2_draw_path(tb_handle_t painter, tb_handle_t path)
{
	tb_trace_noimpl();
}
tb_void_t g2_draw_arc(tb_handle_t painter, g2_arc_t const* arc)
{
	tb_trace_noimpl();
}
tb_void_t g2_draw_rect(tb_handle_t painter, g2_rect_t const* rect)
{
	g2_gl10_painter_t* gpainter = (g2_gl10_painter_t*)painter;
	tb_assert_and_check_return(gpainter && gpainter->style_usr && rect);

	// mode
	tb_size_t mode = g2_style_mode(gpainter->style_usr);

	// flag
	tb_size_t flag = g2_style_flag(gpainter->style_usr);

	// shader
	tb_handle_t shader = g2_style_shader(gpainter->style_usr);

	// width
	tb_float_t width = g2_style_width(gpainter->style_usr);

	// color
	g2_color_t color = g2_style_color(gpainter->style_usr);

	// position
	tb_float_t x0 = g2_float_to_tb(rect->x);
	tb_float_t y0 = g2_float_to_tb(rect->y);
	tb_float_t x1 = g2_float_to_tb(rect->x + rect->w - 1);
	tb_float_t y1 = g2_float_to_tb(rect->y + rect->h - 1);

	// antialiasing?
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

	// matrix
	g2_gl10_matrix_set(gpainter->matrix_gl, &gpainter->matrix);
	glMatrixMode(GL_MODELVIEW);
	glPushMatrix();
	glMultMatrixf(gpainter->matrix_gl);

	// fill
	if (mode & G2_STYLE_MODE_FILL)
	{
		if (shader)
		{
		}
		else glColor4f(color.r / 256., color.g / 256., color.b / 256., color.a / 256.);

		// draw
//		glRectf(x0, y0, x1, y1);


		GLfloat vertices[8];

		vertices[0] = x0;
		vertices[1] = y0;

		vertices[2] = x1;
		vertices[3] = y0;

		vertices[4] = x0;
		vertices[5] = y1;

		vertices[6] = x1;
		vertices[7] = y1;

		glEnableClientState(GL_VERTEX_ARRAY);
		glVertexPointer(2, GL_FLOAT, 0, vertices);
		glDrawArrays(GL_TRIANGLE_STRIP, 0, 4);
		glDisableClientState(GL_VERTEX_ARRAY);
	}

	glPopMatrix();

#if 0
	// stroke
	if (mode & G2_STYLE_MODE_STROKE)
	{
		glLineWidth(g2_float_to_tb(width));
		glColor4f(color.r / 256., color.g / 256., color.b / 256., color.a / 256.);
#if 0
		glBegin(GL_QUADS);
		glVertex2f(x0, y0);
		glVertex2f(x1, y0);
		glVertex2f(x1, y1);
		glVertex2f(x0, y1);
		glEnd();
#endif

		GLfloat vertices[8];

		vertices[0] = x0;
		vertices[1] = y0;

		vertices[2] = x1;
		vertices[3] = y0;

		vertices[4] = x0;
		vertices[5] = y1;

		vertices[6] = x1;
		vertices[7] = y1;

		glEnableClientState(GL_VERTEX_ARRAY);
		glVertexPointer(2, GL_FLOAT, 0, vertices);
		glDrawArrays(GL_TRIANGLES, 0, 4);
		glDisableClientState(GL_VERTEX_ARRAY);
	}
#endif
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
	tb_trace_noimpl();
}
tb_void_t g2_draw_ellipse(tb_handle_t painter, g2_ellipse_t const* ellipse)
{
	tb_trace_noimpl();
}
tb_void_t g2_draw_triangle(tb_handle_t painter, g2_triangle_t const* triangle)
{
	tb_trace_noimpl();
}
