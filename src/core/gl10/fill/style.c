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
 * @file		style.c
 *
 */

/* ///////////////////////////////////////////////////////////////////////
 * includes
 */
#include "style.h"

/* ///////////////////////////////////////////////////////////////////////
 * implementation
 */
tb_bool_t g2_gl10_fill_style_init(g2_gl10_painter_t* painter)
{
	// style
	tb_handle_t 	style = painter->style_usr;

	// mode
	tb_size_t 		mode = g2_style_mode(style);

	// flag
	tb_size_t 		flag = g2_style_flag(style);

	// shader
	tb_handle_t 	shader = g2_style_shader(style);

	// has fill?
	tb_check_return_val(mode & G2_STYLE_MODE_FILL, TB_FALSE);

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

	// enter matrix
	g2_gl10_matrix_set(painter->matrix_gl, &painter->matrix);
	glMatrixMode(GL_MODELVIEW);
	glPushMatrix();
	glMultMatrixf(painter->matrix_gl);

	// fill color
	if (!shader)
	{
		// init color
		g2_color_t color = g2_style_color(style);
		glColor4f(color.r / 256., color.g / 256., color.b / 256., color.a / 256.);
	}

	// ok
	return TB_TRUE;
}
tb_void_t g2_gl10_fill_style_draw(g2_gl10_painter_t* painter, g2_gl10_rect_t const* bounds)
{
	// style
	tb_handle_t 	style = painter->style_usr;

	// mode
	tb_size_t 		mode = g2_style_mode(style);

	// flag
	tb_size_t 		flag = g2_style_flag(style);

	// shader
	tb_handle_t 	shader = g2_style_shader(style);

	// fill color
	if (!shader)
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
		glEnableClientState(GL_VERTEX_ARRAY);
		glVertexPointer(2, GL_FLOAT, 0, vertices);
		glDrawArrays(GL_TRIANGLE_STRIP, 0, 4);
		glDisableClientState(GL_VERTEX_ARRAY);
	}
}
tb_void_t g2_gl10_fill_style_exit(g2_gl10_painter_t* painter)
{
	// leave matrix
	glPopMatrix();
}

