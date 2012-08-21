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
 * @file		context.c
 *
 */

/* ///////////////////////////////////////////////////////////////////////
 * includes
 */
#include "context.h"

/* ///////////////////////////////////////////////////////////////////////
 * implementation
 */
tb_handle_t g2_context_init_gl10(tb_size_t pixfmt, tb_size_t width, tb_size_t height)
{
	// check
	tb_assert_and_check_return_val(G2_PIXFMT_OK(pixfmt) && width && height, TB_NULL);

	// check type
	tb_assert_static(sizeof(GLfloat) == sizeof(tb_float_t));
	tb_assert_static(sizeof(GLint) == sizeof(tb_int_t));
	tb_assert_static(sizeof(GLuint) == sizeof(tb_uint_t));

	// check pixfmt
	tb_assert_and_check_return_val( 	G2_PIXFMT(pixfmt) == G2_PIXFMT_ARGB8888
									|| 	G2_PIXFMT(pixfmt) == G2_PIXFMT_ARGB4444 
									|| 	G2_PIXFMT(pixfmt) == G2_PIXFMT_RGB565, TB_NULL);

	// alloc
	g2_gl10_context_t* gcontext = tb_malloc0(sizeof(g2_gl10_context_t));
	tb_assert_and_check_return_val(gcontext, TB_NULL);

	// init surface
	gcontext->surface = g2_bitmap_init(pixfmt, width, height, 0);
	tb_assert_and_check_goto(gcontext->surface, fail);

	// init viewport
	glViewport(0, 0, width, height);

	// init matrix
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glOrtho(0.0, (tb_float_t)width, 0.0, (tb_float_t)height, -1.0f, 1.0f);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();

	// ok
	return gcontext;

fail:
	if (gcontext) g2_context_exit(gcontext);
	return TB_NULL;
}
tb_void_t g2_context_exit(tb_handle_t context)
{
	g2_gl10_context_t* gcontext = (g2_gl10_context_t*)context;
	if (gcontext) 
	{
		// free surface
		if (gcontext->surface) g2_bitmap_exit(gcontext->surface);

		// free it
		tb_free(gcontext);
	}
}
tb_handle_t g2_context_surface(tb_handle_t context)
{
	g2_gl10_context_t* gcontext = (g2_gl10_context_t*)context;
	tb_assert_and_check_return_val(gcontext, TB_NULL);

	return gcontext->surface;
}
tb_handle_t g2_context_resize(tb_handle_t context, tb_size_t width, tb_size_t height)
{
	g2_gl10_context_t* gcontext = (g2_gl10_context_t*)context;
	tb_assert_and_check_return_val(gcontext && width && height, TB_NULL);

	// update surface
	if (!g2_bitmap_resize(gcontext->surface, width, height)) return TB_NULL;

	// update viewport
	glViewport(0, 0, width, height);

	// update matrix
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glOrtho(0.0, (tb_float_t)width, 0.0, (tb_float_t)height, -1.0f, 1.0f);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();

	// ok
	return context;
}

