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
#include "prefix.h"
#include "context.h"

/* ///////////////////////////////////////////////////////////////////////
 * implementation
 */
tb_handle_t g2_context_init_gl10(tb_size_t width, tb_size_t height)
{
	// check
	tb_assert_and_check_return_val(width && height, TB_NULL);

	// alloc
	g2_gl10_context_t* gcontext = tb_malloc0(sizeof(g2_gl10_context_t));
	tb_assert_and_check_return_val(gcontext, TB_NULL);

	// init
	gcontext->width = width;
	gcontext->height = height;

	// init viewport
	glViewport(0, 0, width, height);

	// init matrix
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
#ifndef TB_CONFIG_OS_ANDROID
	gluOrtho2D(0.0, (GLfloat)width, 0.0, (GLfloat)height);
#endif
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();

	// ok
	return gcontext;
}
tb_void_t g2_context_exit(tb_handle_t context)
{
	if (context) tb_free(context);
}
tb_size_t g2_context_width(tb_handle_t context)
{
	g2_gl10_context_t* gcontext = (g2_gl10_context_t*)context;
	tb_assert_and_check_return_val(gcontext, 0);

	return gcontext->width;
}
tb_size_t g2_context_height(tb_handle_t context)
{
	g2_gl10_context_t* gcontext = (g2_gl10_context_t*)context;
	tb_assert_and_check_return_val(gcontext, 0);

	return gcontext->height;
}
tb_void_t g2_context_resize(tb_handle_t context, tb_size_t width, tb_size_t height)
{
	g2_gl10_context_t* gcontext = (g2_gl10_context_t*)context;
	tb_assert_and_check_return(gcontext && width && height);

	// update width & height
	gcontext->width = width;
	gcontext->height = height;

	// update viewport
	glViewport(0, 0, width, height);

	// update matrix
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
#ifndef TB_CONFIG_OS_ANDROID
	gluOrtho2D(0.0, (GLfloat)width, 0.0, (GLfloat)height);
#endif
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
}

