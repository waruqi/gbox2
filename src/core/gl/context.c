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
#define TB_TRACE_IMPL_TAG 		"gl"

/* ///////////////////////////////////////////////////////////////////////
 * includes
 */
#include "context.h"
#include "program/program.h"

/* ///////////////////////////////////////////////////////////////////////
 * macros
 */

// grow
#ifdef TB_CONFIG_MEMORY_MODE_SMALL
# 	define G2_GL_SHADERS_GROW 				(32)
#else
# 	define G2_GL_SHADERS_GROW 				(128)
#endif

// extensions
#define G2_GL_CONTEXT_EXT_INIT(ext) 		if (!tb_strncmp(p, "GL_" #ext, l)) context->extensions[G2_GL_EXT_##ext] = 1;

/* ///////////////////////////////////////////////////////////////////////
 * version & compatibility
 */

static __tb_inline__ tb_byte_t g2_gl_context_version()
{
	// version 
	tb_char_t const* version = glGetString(GL_VERSION);
	tb_assert_and_check_return_val(version && tb_isdigit(version[0]) && version[1] == '.' && tb_isdigit(version[2]), 0);

	// major & minor
	tb_byte_t major = version[0] - '0';
	tb_byte_t minor = version[2] - '0';

	// trace
	tb_trace_impl("version: %s: %x", version, ((major << 4) + minor));

	// [0x10, 0x19] 
	return ((major << 4) + minor);
}
static __tb_inline__ tb_void_t g2_gl_context_extensions(g2_gl_context_t* context)
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
		G2_GL_CONTEXT_EXT_INIT(ARB_texture_non_power_of_two);
	
		// next
		p += l + 1;
	}
}

/* ///////////////////////////////////////////////////////////////////////
 * texture & shader
 */

GLuint* g2_gl_context_texture_alc(g2_gl_context_t* context)
{
	// init
	GLuint* 	itor = TB_NULL;
	GLuint* 	data = context->texture;
	tb_byte_t* 	used = context->used;
	tb_size_t 	pred = context->texture_pred;

	// check
	tb_assert_and_check_return_val(pred < G2_GL_TEXTURE_MAXN, 0);

	// pred?
	if (!(used[pred] & G2_GL_TEXTURE_USED))
	{
		// use it
		itor = &data[pred];
		used[pred] |= G2_GL_TEXTURE_USED;

		// pred next
		if (pred + 1 < G2_GL_TEXTURE_MAXN) pred++;
		else pred = 0;
	}
	else
	{
		// find
		tb_size_t i = 0;
		for (i = 0; i < G2_GL_TEXTURE_MAXN; i++)
		{
			// free?
			if (!(used[i] & G2_GL_TEXTURE_USED))
			{
				// use it
				itor = &data[i];
				used[i] |= G2_GL_TEXTURE_USED;

				// pred next
				if (i + 1 < G2_GL_TEXTURE_MAXN) pred = i + 1;
				else pred = 0;

				// ok
				break;
			}
		}
	}
	
	// pred
	context->texture_pred = pred;

	// ok?
	return itor;
}
tb_void_t g2_gl_context_texture_del(g2_gl_context_t* context, GLuint const* texture)
{
	// check
	tb_assert_and_check_return(texture);

	// init
	tb_byte_t* 	used = context->used;
	tb_size_t 	pred = context->texture_pred;
	tb_size_t 	itor = texture - context->texture;

	// free it
	if (used[itor] & G2_GL_TEXTURE_USED)
	{
		pred = itor;
		used[itor] &= ~G2_GL_TEXTURE_USED;
	}
	
	// pred
	context->texture_pred = pred;
}
g2_gl_shader_t* g2_gl_context_shader_alc(g2_gl_context_t* context)
{
	// init
	g2_gl_shader_t* 	itor = TB_NULL;
	g2_gl_shader_t* 	data = context->shaders;
	tb_byte_t* 			used = context->used;
	tb_size_t 			pred = context->shaders_pred;

	// check
	tb_assert_and_check_return_val(pred < G2_GL_TEXTURE_MAXN, 0);

	// pred?
	if (!(used[pred] & G2_GL_SHADERS_USED))
	{
		// use it
		itor = &data[pred];
		used[pred] |= G2_GL_SHADERS_USED;

		// pred next
		if (pred + 1 < G2_GL_TEXTURE_MAXN) pred++;
		else pred = 0;
	}
	else
	{
		// find
		tb_size_t i = 0;
		for (i = 0; i < G2_GL_TEXTURE_MAXN; i++)
		{
			// free?
			if (!(used[i] & G2_GL_SHADERS_USED))
			{
				// use it
				itor = &data[i];
				used[i] |= G2_GL_SHADERS_USED;

				// pred next
				if (i + 1 < G2_GL_TEXTURE_MAXN) pred = i + 1;
				else pred = 0;

				// ok
				break;
			}
		}
	}
	
	// pred
	context->shaders_pred = pred;

	// clear
	if (itor) tb_memset(itor, 0, sizeof(g2_gl_shader_t));

	// ok?
	return itor;
}
tb_void_t g2_gl_context_shader_del(g2_gl_context_t* context, g2_gl_shader_t const* shader)
{
	// check
	tb_assert_and_check_return(context && shader);

	// init
	tb_byte_t* 	used = context->used;
	tb_size_t 	pred = context->shaders_pred;
	tb_size_t 	itor = shader - context->shaders;

	// free it
	if (used[itor] & G2_GL_SHADERS_USED)
	{
		pred = itor;
		used[itor] &= ~G2_GL_SHADERS_USED;
	}
	
	// pred
	context->shaders_pred = pred;
}

/* ///////////////////////////////////////////////////////////////////////
 * implementation
 */
tb_handle_t g2_context_init_gl(tb_size_t pixfmt, tb_size_t width, tb_size_t height)
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
	g2_gl_context_t* gcontext = tb_malloc0(sizeof(g2_gl_context_t));
	tb_assert_and_check_return_val(gcontext, TB_NULL);

	// init version 
	gcontext->version = g2_gl_context_version();
//	gcontext->version = 0x10;
	tb_assert_and_check_goto(gcontext->version >= 0x10, fail);

	// init extensions
	g2_gl_context_extensions(gcontext);
	tb_assert_and_check_goto(gcontext->extensions[G2_GL_EXT_ARB_texture_non_power_of_two], fail);

	// init surface
	gcontext->surface = g2_bitmap_init(pixfmt, width, height, 0);
	tb_assert_and_check_goto(gcontext->surface, fail);

	// init used
	tb_memset(gcontext->used, 0, G2_GL_TEXTURE_MAXN);

	// init texture
 	glGenTextures(G2_GL_TEXTURE_MAXN, gcontext->texture);
	gcontext->texture_pred = 0;

	// init shaders
	tb_memset(gcontext->shaders, 0, G2_GL_TEXTURE_MAXN * sizeof(g2_gl_shader_t));
	gcontext->shaders_pred = 0;

	// init viewport
	glViewport(0, 0, width, height);

	// init programs
	if (gcontext->version >= 0x20)
	{
		tb_bool_t ok = TB_FALSE;
		do
		{
			// init color program
			gcontext->programs[G2_GL_PROGRAM_TYPE_COLOR] = g2_gl_program_init_color();
			tb_assert_and_check_break(gcontext->programs[G2_GL_PROGRAM_TYPE_COLOR]);

			// init bitmap program
			gcontext->programs[G2_GL_PROGRAM_TYPE_BITMAP] = g2_gl_program_init_bitmap();
			tb_assert_and_check_break(gcontext->programs[G2_GL_PROGRAM_TYPE_BITMAP]);

			// init gradient program
			gcontext->programs[G2_GL_PROGRAM_TYPE_GRADIENT] = g2_gl_program_init_gradient();
			tb_assert_and_check_break(gcontext->programs[G2_GL_PROGRAM_TYPE_GRADIENT]);

			// ok
			ok = TB_TRUE;

		} while (0);

		// failed? use gl v1.x api
		if (!ok) gcontext->version = 0x19;
	}

	// init matrix
	if (gcontext->version < 0x20)
	{
		glMatrixMode(GL_PROJECTION);
		glLoadIdentity();
		glOrtho(0.0f, (tb_float_t)width, (tb_float_t)height, 0.0f, -1.0f, 1.0f);
		glMatrixMode(GL_MODELVIEW);
	}
	else g2_gl_matrix_ortho(gcontext->matrix, 0.0f, (tb_float_t)width, (tb_float_t)height, 0.0f, -1.0f, 1.0f);

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
	glDisable(GL_TEXTURE_1D);
	glDisable(GL_TEXTURE_2D);

	if (gcontext->version < 0x20)
	{
		// disable vertices
		glDisableClientState(GL_VERTEX_ARRAY);

		// disable texcoords
		glDisableClientState(GL_TEXTURE_COORD_ARRAY);
	}

	// ok
	return gcontext;

fail:
	if (gcontext) g2_context_exit(gcontext);
	return TB_NULL;
}
tb_void_t g2_context_exit(tb_handle_t context)
{
	g2_gl_context_t* gcontext = (g2_gl_context_t*)context;
	if (gcontext) 
	{
		// exit programs 
		tb_size_t i = 0;
		for (i = 0; i < G2_GL_PROGRAM_TYPE_MAXN; i++)
		{
			if (gcontext->programs[i]) g2_gl_program_exit(gcontext->programs[i]);
			gcontext->programs[i] = 0;
		}

		// exit shaders
		if (gcontext->shaders)
		{
			tb_size_t 			i = 0;
			tb_byte_t const* 	used = gcontext->used;
			g2_gl_shader_t* 	data = gcontext->shaders;
			for (i = 0; i < G2_GL_TEXTURE_MAXN; i++)
			{
				if (used[i] & G2_GL_SHADERS_USED)
				{
					tb_assert(data[i].refn == 1);
					g2_shader_dec(&data[i]);
				}
			}
		}
		
		// exit texture
		glDeleteTextures(G2_GL_TEXTURE_MAXN, gcontext->texture);

		// free surface
		if (gcontext->surface) g2_bitmap_exit(gcontext->surface);

		// free it
		tb_free(gcontext);
	}
}
tb_handle_t g2_context_surface(tb_handle_t context)
{
	g2_gl_context_t* gcontext = (g2_gl_context_t*)context;
	tb_assert_and_check_return_val(gcontext, TB_NULL);

	return gcontext->surface;
}
tb_handle_t g2_context_resize(tb_handle_t context, tb_size_t width, tb_size_t height)
{
	g2_gl_context_t* gcontext = (g2_gl_context_t*)context;
	tb_assert_and_check_return_val(gcontext && width && height, TB_NULL);

	// update surface
	if (!g2_bitmap_resize(gcontext->surface, width, height)) return TB_NULL;

	// update viewport
	glViewport(0, 0, width, height);

	// update matrix	
	if (gcontext->version < 0x20)
	{
		glMatrixMode(GL_PROJECTION);
		glLoadIdentity();
		glOrtho(0.0f, (tb_float_t)width, (tb_float_t)height, 0.0f, -1.0f, 1.0f);
		glMatrixMode(GL_MODELVIEW);
	}
	else g2_gl_matrix_ortho(gcontext->matrix, 0.0f, (tb_float_t)width, (tb_float_t)height, 0.0f, -1.0f, 1.0f);

	// ok
	return context;
}

