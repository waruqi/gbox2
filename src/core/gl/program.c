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
 * @file		program.c
 *
 */

/* ///////////////////////////////////////////////////////////////////////
 * trace
 */
#define TB_TRACE_IMPL_TAG 		"gl"

/* ///////////////////////////////////////////////////////////////////////
 * includes
 */
#include "program.h"

/* ///////////////////////////////////////////////////////////////////////
 * macros
 */

// maxn
#ifdef TB_CONFIG_MEMORY_MODE_SMALL
# 	define G2_GL_PROGRAM_SHADER_MAXN 		(8)
# 	define G2_GL_PROGRAM_LOCATION_MAXN 		(32)
#else
# 	define G2_GL_PROGRAM_SHADER_MAXN 		(16)
# 	define G2_GL_PROGRAM_LOCATION_MAXN 		(64)
#endif

/* ///////////////////////////////////////////////////////////////////////
 * types
 */

// the gl program type
typedef struct __g2_gl_program_t
{
	// the type
	tb_size_t 			type;

	// the program
	g2_GLuint_t 		program;

	// the shaders
	g2_GLuint_t 		shaders[G2_GL_PROGRAM_SHADER_MAXN];
	tb_size_t 			shadern;

	// the locations
	g2_GLint_t 			location[G2_GL_PROGRAM_LOCATION_MAXN];

}g2_gl_program_t;

/* ///////////////////////////////////////////////////////////////////////
 * shader
 */

static g2_GLuint_t g2_gl_program_shader(tb_char_t const* data, tb_size_t type)
{
	// init shader
	g2_GLuint_t shader = g2_glCreateShader((g2_GLenum_t)type);
	tb_assert_and_check_return_val(shader, 0);

	// init source
	g2_glShaderSource(shader, 1, (g2_GLchar_t const**)&data, tb_null);

	// compile shader
	g2_glCompileShader(shader);

	// ok?
	g2_GLint_t ok = G2_GL_FALSE;
	g2_glGetShaderiv(shader, G2_GL_COMPILE_STATUS, &ok);
	if (ok == G2_GL_FALSE)
	{
		// trace
		g2_GLchar_t s[1024] = {0};
		g2_glGetShaderInfoLog(shader, 1024, 0, s);
		tb_trace_impl("shader: compile failed: %s", s);

		// remove it
		g2_glDeleteShader(shader);
		return 0;
	}

	// ok
	return shader;
}

/* ///////////////////////////////////////////////////////////////////////
 * implementation
 */

tb_handle_t g2_gl_program_init()
{
	return tb_malloc0(sizeof(g2_gl_program_t));
}
tb_void_t g2_gl_program_exit(tb_handle_t program)
{
	// check
	g2_gl_program_t* gprogram = (g2_gl_program_t*)program;
	tb_assert_and_check_return(gprogram);

	// exit shaders
	tb_size_t i = 0;
	for (i = 0; i < gprogram->shadern; i++)
	{
		if (gprogram->shaders[i]) g2_glDeleteShader(gprogram->shaders[i]);
		gprogram->shaders[i] = 0;
	}
	gprogram->shadern = 0;

	// exit gprogram
	if (gprogram->program) g2_glDeleteProgram(gprogram->program);
	gprogram->program = 0;

	// free it
	tb_free(gprogram);
}
tb_bool_t g2_gl_program_load(tb_handle_t program, tb_char_t const* shader, tb_size_t type)
{
	// check
	g2_gl_program_t* gprogram = (g2_gl_program_t*)program;
	tb_assert_and_check_return_val(gprogram && gprogram->shadern < G2_GL_PROGRAM_SHADER_MAXN && shader && type, tb_false);

	// load shader
	gprogram->shaders[gprogram->shadern] = g2_gl_program_shader(shader, type);
	tb_assert_and_check_return_val(gprogram->shaders[gprogram->shadern], tb_false);
	gprogram->shadern++;

	// ok
	return tb_true;
}
tb_bool_t g2_gl_program_make(tb_handle_t program)
{
	// check
	g2_gl_program_t* gprogram = (g2_gl_program_t*)program;
	tb_assert_and_check_return_val(gprogram && !gprogram->program && gprogram->shadern, tb_false);

	// init program
	gprogram->program = g2_glCreateProgram();
	tb_assert_and_check_return_val(gprogram->program, tb_false);

	// attach shaders
	tb_size_t i = 0;
	for (i = 0; i < gprogram->shadern; i++)
		if (gprogram->shaders[i]) g2_glAttachShader(gprogram->program, gprogram->shaders[i]);

	// link
	g2_glLinkProgram(gprogram->program);

	// ok?
	g2_GLint_t ok = 0;
	g2_glGetProgramiv(gprogram->program, G2_GL_LINK_STATUS, &ok);
	if (!ok) 
	{
		// trace
		g2_GLchar_t s[1024] = {0};
		g2_glGetProgramInfoLog(gprogram, 1024, 0, s);
		tb_trace_impl("shader: link failed: %s", s);

		// remove it
		g2_glDeleteProgram(gprogram->program);
		gprogram->program = 0;
		return tb_false;
	}

	// exit shaders
	for (i = 0; i < gprogram->shadern; i++)
	{
		if (gprogram->shaders[i]) g2_glDeleteShader(gprogram->shaders[i]);
		gprogram->shaders[i] = 0;
	}
	gprogram->shadern = 0;

	// ok
	return tb_true;
}
tb_void_t g2_gl_program_uses(tb_handle_t program)
{
	// check
	g2_gl_program_t* gprogram = (g2_gl_program_t*)program;
	tb_assert_and_check_return_val(gprogram && gprogram->program, tb_false);

	// use it
	g2_glUseProgram(gprogram->program);
}
g2_GLint_t g2_gl_program_attr(tb_handle_t program, tb_char_t const* name)
{
	// check
	g2_gl_program_t* gprogram = (g2_gl_program_t*)program;
	tb_assert_and_check_return_val(gprogram && gprogram->program && name, -1);

	return g2_glGetAttribLocation(gprogram->program, name);
}
g2_GLint_t g2_gl_program_unif(tb_handle_t program, tb_char_t const* name)
{
	// check
	g2_gl_program_t* gprogram = (g2_gl_program_t*)program;
	tb_assert_and_check_return_val(gprogram && gprogram->program && name, -1);

	return g2_glGetUniformLocation(gprogram->program, name);
}
tb_size_t g2_gl_program_type(tb_handle_t program)
{
	// check
	g2_gl_program_t* gprogram = (g2_gl_program_t*)program;
	tb_assert_and_check_return_val(gprogram, 0);

	return gprogram->type;
}
tb_void_t g2_gl_program_type_set(tb_handle_t program, tb_size_t type)
{
	// check
	g2_gl_program_t* gprogram = (g2_gl_program_t*)program;
	tb_assert_and_check_return(gprogram);

	gprogram->type = type;
}
g2_GLint_t g2_gl_program_location(tb_handle_t program, tb_size_t index)
{
	// check
	g2_gl_program_t* gprogram = (g2_gl_program_t*)program;
	tb_assert_and_check_return_val(gprogram && index < G2_GL_PROGRAM_LOCATION_MAXN, -1);

	return gprogram->location[index];
}
tb_void_t g2_gl_program_location_set(tb_handle_t program, tb_size_t index, g2_GLuint_t location)
{
	// check
	g2_gl_program_t* gprogram = (g2_gl_program_t*)program;
	tb_assert_and_check_return(gprogram && index < G2_GL_PROGRAM_LOCATION_MAXN);

	gprogram->location[index] = location;
}

