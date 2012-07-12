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
 * types
 */
// the gl10 painter type
typedef struct __g2_gl10_painter_t
{
	// the context
	g2_gl10_context_t* 			context;

	// the style
	tb_handle_t 				style_def;
	tb_handle_t 				style_usr;

}g2_gl10_painter_t;

/* ///////////////////////////////////////////////////////////////////////
 * gl10 
 */

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
		// free it
		tb_free(gpainter);
	}
}
tb_size_t g2_save(tb_handle_t painter, tb_size_t mode)
{
	tb_trace_noimpl();
	return TB_NULL;
}
tb_void_t g2_load(tb_handle_t painter)
{
	tb_trace_noimpl();
}
tb_size_t g2_pixfmt(tb_handle_t painter)
{
	tb_trace_noimpl();
	return TB_NULL;
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
	tb_trace_noimpl();
	return TB_NULL;
}
tb_bool_t g2_rotate(tb_handle_t painter, g2_float_t degrees)
{
	tb_trace_noimpl();
	return TB_NULL;
}
tb_bool_t g2_skew(tb_handle_t painter, g2_float_t kx, g2_float_t ky)
{
	tb_trace_noimpl();
	return TB_NULL;
}
tb_bool_t g2_scale(tb_handle_t painter, g2_float_t sx, g2_float_t sy)
{
	tb_trace_noimpl();
	return TB_NULL;
}
tb_bool_t g2_translate(tb_handle_t painter, g2_float_t dx, g2_float_t dy)
{
	tb_trace_noimpl();
	return TB_NULL;
}
tb_bool_t g2_multiply(tb_handle_t painter, g2_matrix_t const* matrix)
{
	tb_trace_noimpl();
	return TB_NULL;
}
tb_void_t g2_matrix_set(tb_handle_t painter, g2_matrix_t const* matrix)
{
	tb_trace_noimpl();
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

	// width
	tb_float_t width = g2_style_width(gpainter->style_usr);

	// color
	g2_color_t color = g2_style_color(gpainter->style_usr);

	// position
	tb_float_t x0 = g2_float_to_tb(rect->x);
	tb_float_t y0 = g2_float_to_tb(rect->y);
	tb_float_t x1 = g2_float_to_tb(rect->x + rect->w - 1);
	tb_float_t y1 = g2_float_to_tb(rect->y + rect->h - 1);

	// fill
	if (mode & G2_STYLE_MODE_FILL)
	{
		glColor4f(color.r / 256., color.g / 256., color.b / 256., color.a / 256.);
		glRectf(x0, y0, x1, y1);
	}

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
