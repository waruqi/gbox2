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
 * trace
 */
#define TB_TRACE_IMPL_TAG 		"gl2x"

/* ///////////////////////////////////////////////////////////////////////
 * includes
 */
#include "context.h"
#include "program/program.h"

/* ///////////////////////////////////////////////////////////////////////
 * macros
 */

// extensions
#define G2_GL2x_CONTEXT_EXT_INIT(ext) 			if (!tb_strncmp(p, "GL_" #ext, l)) context->extensions[G2_GL_EXT_##ext] = 1;

/* ///////////////////////////////////////////////////////////////////////
 * version & compatibility
 */

static __tb_inline__ tb_byte_t g2_gl2x_context_version()
{
	// version 
	tb_char_t const* version = glGetString(GL_VERSION);
	tb_assert_and_check_return_val(version && tb_isdigit(version[0]) && version[1] == '.' && tb_isdigit(version[2]), 0);

	// major & minor
	tb_byte_t major = version[0] - '0';
	tb_byte_t minor = version[2] - '0';

	// trace
	tb_trace_impl("version: %s: %x, gpu: %s", version, ((major << 4) + minor), glGetString(GL_RENDERER));

	// [0x10, 0x19] 
	return ((major << 4) + minor);
}
static __tb_inline__ tb_void_t g2_gl2x_context_extensions(g2_gl2x_context_t* context)
{
	tb_char_t const* 	p = glGetString(GL_EXTENSIONS);
	tb_size_t 			n = tb_strlen(p);
	tb_char_t const* 	e = p + n;
	tb_assert_and_check_return(p && n);

	while (p < e)
	{
		// find
		tb_char_t const* 	q = tb_strchr(p, ' ');
		tb_size_t 			l = q? q - p : tb_strlen(p);

		// init
		G2_GL2x_CONTEXT_EXT_INIT(ARB_texture_non_power_of_two);
	
		// next
		p += l + 1;
	}
}

/* ///////////////////////////////////////////////////////////////////////
 * implementation
 */
tb_handle_t g2_context_init_gl2x(tb_size_t pixfmt, tb_size_t width, tb_size_t height)
{
	// check
	tb_assert_and_check_return_val(G2_PIXFMT_OK(pixfmt) && width && height, TB_NULL);

	// check type
	tb_assert_static(sizeof(GLfloat) == sizeof(tb_float_t));

	// check pixfmt
	tb_assert_and_check_return_val( 	G2_PIXFMT(pixfmt) == G2_PIXFMT_ARGB8888
									|| 	G2_PIXFMT(pixfmt) == G2_PIXFMT_ARGB4444 
									|| 	G2_PIXFMT(pixfmt) == G2_PIXFMT_RGB565, TB_NULL);

	// alloc
	g2_gl2x_context_t* gcontext = tb_malloc0(sizeof(g2_gl2x_context_t));
	tb_assert_and_check_return_val(gcontext, TB_NULL);

	// init version 
	gcontext->version = g2_gl2x_context_version();
	tb_assert_and_check_goto(gcontext->version >= 0x20, fail);

	// init extensions
	g2_gl2x_context_extensions(gcontext);
	tb_assert_and_check_goto(gcontext->extensions[G2_GL_EXT_ARB_texture_non_power_of_two], fail);

	// init surface
	gcontext->surface = g2_bitmap_init(pixfmt, width, height, 0);
	tb_assert_and_check_goto(gcontext->surface, fail);

	// init programs
	gcontext->programs[G2_GL2X_PROGRAM_TYPE_COLOR] = g2_gl2x_program_init_color();
	tb_assert_and_check_goto(gcontext->programs[G2_GL2X_PROGRAM_TYPE_COLOR], fail);

	// init viewport
	glViewport(0, 0, width, height);

	// init project matrix
	g2_gl_matrix_init(gcontext->matrix);
#if 1
	gcontext->matrix[0] = 2.0f / (tb_float_t)width;
	gcontext->matrix[5] = -2.0f / (tb_float_t)height;
	gcontext->matrix[12] = -1.0f;
	gcontext->matrix[13] = 1.0f;
#endif

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
	glDisable(GL_TEXTURE_2D);

	// ok
	return gcontext;

fail:
	if (gcontext) g2_context_exit(gcontext);
	return TB_NULL;
}
tb_void_t g2_context_exit(tb_handle_t context)
{
	g2_gl2x_context_t* gcontext = (g2_gl2x_context_t*)context;
	if (gcontext) 
	{
		// exit programs 
		tb_size_t i = 0;
		for (i = 0; i < G2_GL2X_PROGRAM_TYPE_MAXN; i++)
			if (gcontext->programs[i]) g2_gl2x_program_exit(gcontext->programs[i]);

		// free surface
		if (gcontext->surface) g2_bitmap_exit(gcontext->surface);

		// free it
		tb_free(gcontext);
	}
}
tb_handle_t g2_context_surface(tb_handle_t context)
{
	g2_gl2x_context_t* gcontext = (g2_gl2x_context_t*)context;
	tb_assert_and_check_return_val(gcontext, TB_NULL);

	return gcontext->surface;
}
tb_handle_t g2_context_resize(tb_handle_t context, tb_size_t width, tb_size_t height)
{
	g2_gl2x_context_t* gcontext = (g2_gl2x_context_t*)context;
	tb_assert_and_check_return_val(gcontext && width && height, TB_NULL);

	// update surface
	if (!g2_bitmap_resize(gcontext->surface, width, height)) return TB_NULL;

	// update viewport
	glViewport(0, 0, width, height);

	// update project matrix
//	gcontext->matrix[0] = 2.0f / (tb_float_t)width;
//	gcontext->matrix[5] = -2.0f / (tb_float_t)height;

	// ok
	return context;
}

