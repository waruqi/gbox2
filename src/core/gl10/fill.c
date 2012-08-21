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
 * includes
 */
#include "fill.h"
#include "fill/style.h"

/* ///////////////////////////////////////////////////////////////////////
 * implementation
 */
tb_void_t g2_gl10_fill_rect(g2_gl10_painter_t* painter, g2_rect_t const* rect)
{
	// init fill style
	if (g2_gl10_fill_style_init(painter))
	{
		// init position
		tb_float_t x0 = g2_float_to_tb(rect->x);
		tb_float_t y0 = g2_float_to_tb(rect->y);
		tb_float_t x1 = g2_float_to_tb(rect->x + rect->w - 1);
		tb_float_t y1 = g2_float_to_tb(rect->y + rect->h - 1);

		// init rect
		tb_float_t vertices[8];
		vertices[0] = x0;
		vertices[1] = y0;
		vertices[2] = x1;
		vertices[3] = y0;
		vertices[4] = x0;
		vertices[5] = y1;
		vertices[6] = x1;
		vertices[7] = y1;

		// draw rect
		glEnableClientState(GL_VERTEX_ARRAY);
		glVertexPointer(2, GL_FLOAT, 0, vertices);
		glDrawArrays(GL_TRIANGLE_STRIP, 0, 4);
		glDisableClientState(GL_VERTEX_ARRAY);

		// exit fill style
		g2_gl10_fill_style_exit(painter);
	}
}
tb_void_t g2_gl10_fill_path(g2_gl10_painter_t* painter, g2_gl10_path_t const* path)
{
	// init fill style
	if (g2_gl10_fill_style_init(painter))
	{
		// check
		tb_assert(path->fill.data && tb_vector_size(path->fill.data));
		tb_assert(path->fill.size && tb_vector_size(path->fill.size));

		// init stencil
		glEnable(GL_STENCIL_TEST);
		glStencilFunc(GL_ALWAYS, 0, 0);
		glStencilOp(GL_INVERT, GL_INVERT, GL_INVERT);
		glColorMask(GL_FALSE, GL_FALSE, GL_FALSE, GL_FALSE);

		// init vertices
		glEnableClientState(GL_VERTEX_ARRAY);
		glVertexPointer(2, GL_FLOAT, 0, tb_vector_data(path->fill.data));

		// draw path to stencil
		tb_int_t 	head = 0;
		tb_int_t 	size = 0;
		tb_size_t 	itor = tb_iterator_head(path->fill.size);
		tb_size_t 	tail = tb_iterator_tail(path->fill.size);
		for (; itor != tail; itor++)
		{
			size = tb_iterator_item(path->fill.size, itor);
			glDrawArrays(GL_TRIANGLE_FAN, head, size);
			head += size;
		}

		// exit vertices
		glDisableClientState(GL_VERTEX_ARRAY);

		// init stencil for odd
		glStencilFunc(GL_EQUAL, 1, 1);
		glStencilOp(GL_ZERO, GL_ZERO, GL_ZERO);
		glColorMask(GL_TRUE, GL_TRUE, GL_TRUE, GL_TRUE);

		// draw fill style with stencil
		g2_gl10_fill_style_draw(painter, &path->fill.rect);

		// exit fill style
		g2_gl10_fill_style_exit(painter);

		// exit stencil
		glColorMask(GL_TRUE, GL_TRUE, GL_TRUE, GL_TRUE);
		glDisable(GL_STENCIL_TEST);
	}
}
tb_void_t g2_gl10_fill_circle(g2_gl10_painter_t* painter, g2_circle_t const* circle)
{

}
tb_void_t g2_gl10_fill_ellipse(g2_gl10_painter_t* painter, g2_ellipse_t const* ellipse)
{

}
tb_void_t g2_gl10_fill_triangle(g2_gl10_painter_t* painter, g2_triangle_t const* triangle)
{

}

