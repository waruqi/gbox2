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
#define TB_TRACE_IMPL_TAG 		"gl2x"

/* ///////////////////////////////////////////////////////////////////////
 * includes
 */
#include "program.h"

/* ///////////////////////////////////////////////////////////////////////
 * macros
 */

// maxn
#ifdef TB_CONFIG_MEMORY_MODE_SMALL
# 	define G2_GL2X_PROGRAM_SHADER_MAXN 			(8)
# 	define G2_GL2X_PROGRAM_LOCATION_MAXN 		(32)
#else
# 	define G2_GL2X_PROGRAM_SHADER_MAXN 			(16)
# 	define G2_GL2X_PROGRAM_LOCATION_MAXN 		(64)
#endif

/* ///////////////////////////////////////////////////////////////////////
 * types
 */

// the gl2x program type
typedef struct __g2_gl2x_program_t
{
	// the type
	tb_size_t 		type;

	// the program
	GLuint 			program;

	// the shaders
	GLuint 			shaders[G2_GL2X_PROGRAM_SHADER_MAXN];
	tb_size_t 		shadern;

	// the locations
	GLint 			location[G2_GL2X_PROGRAM_LOCATION_MAXN];

}g2_gl2x_program_t;

/* ///////////////////////////////////////////////////////////////////////
 * shader
 */

static GLuint g2_gl2x_program_shader(tb_char_t const* data, tb_size_t type)
{
	// init shader
	GLuint shader = glCreateShader((GLenum)type);
	tb_assert_and_check_return_val(shader, 0);

	// init source
	glShaderSource(shader, 1, (GLchar const**)&data, TB_NULL);

	// compile shader
	glCompileShader(shader);

	// ok?
	GLint ok = GL_FALSE;
	glGetShaderiv(shader, GL_COMPILE_STATUS, &ok);
	if (ok == GL_FALSE)
	{
		// trace
		GLchar s[1024] = {0};
		glGetShaderInfoLog(shader, 1024, 0, s);
		tb_trace_impl("shader: compile failed: %s", s);

		// remove it
		glDeleteShader(shader);
		return 0;
	}

	// ok
	return shader;
}

/* ///////////////////////////////////////////////////////////////////////
 * implementation
 */

tb_handle_t g2_gl2x_program_init()
{
	return tb_malloc0(sizeof(g2_gl2x_program_t));
}
tb_void_t g2_gl2x_program_exit(tb_handle_t program)
{
	// check
	g2_gl2x_program_t* gprogram = (g2_gl2x_program_t*)program;
	tb_assert_and_check_return(gprogram);

	// exit shaders
	tb_size_t i = 0;
	for (i = 0; i < gprogram->shadern; i++)
	{
		if (gprogram->shaders[i]) glDeleteShader(gprogram->shaders[i]);
		gprogram->shaders[i] = 0;
	}
	gprogram->shadern = 0;

	// exit gprogram
	if (gprogram->program) glDeleteProgram(gprogram->program);
	gprogram->program = 0;

	// free it
	tb_free(gprogram);
}
tb_bool_t g2_gl2x_program_load(tb_handle_t program, tb_char_t const* shader, tb_size_t type)
{
	// check
	g2_gl2x_program_t* gprogram = (g2_gl2x_program_t*)program;
	tb_assert_and_check_return_val(gprogram && gprogram->shadern < G2_GL2X_PROGRAM_SHADER_MAXN && shader && type, TB_FALSE);

	// load shader
	gprogram->shaders[gprogram->shadern] = g2_gl2x_program_shader(shader, type);
	tb_assert_and_check_return_val(gprogram->shaders[gprogram->shadern], TB_FALSE);
	gprogram->shadern++;

	// ok
	return TB_TRUE;
}
tb_bool_t g2_gl2x_program_make(tb_handle_t program)
{
	// check
	g2_gl2x_program_t* gprogram = (g2_gl2x_program_t*)program;
	tb_assert_and_check_return_val(gprogram && !gprogram->program && gprogram->shadern, TB_FALSE);

	// init program
	gprogram->program = glCreateProgram();
	tb_assert_and_check_return_val(gprogram->program, TB_FALSE);

	// attach shaders
	tb_size_t i = 0;
	for (i = 0; i < gprogram->shadern; i++)
		if (gprogram->shaders[i]) glAttachShader(gprogram->program, gprogram->shaders[i]);

	// link
	glLinkProgram(gprogram->program);

	// ok?
	GLint ok = 0;
	glGetProgramiv(gprogram->program, GL_LINK_STATUS, &ok);
	if (!ok) 
	{
		// trace
		GLchar s[1024] = {0};
		glGetProgramInfoLog(gprogram, 1024, 0, s);
		tb_trace_impl("shader: link failed: %s", s);

		// remove it
		glDeleteProgram(gprogram->program);
		gprogram->program = 0;
		return TB_FALSE;
	}

	// exit shaders
	for (i = 0; i < gprogram->shadern; i++)
	{
		if (gprogram->shaders[i]) glDeleteShader(gprogram->shaders[i]);
		gprogram->shaders[i] = 0;
	}
	gprogram->shadern = 0;

	// ok
	return TB_TRUE;
}
tb_void_t g2_gl2x_program_uses(tb_handle_t program)
{
	// check
	g2_gl2x_program_t* gprogram = (g2_gl2x_program_t*)program;
	tb_assert_and_check_return_val(gprogram && gprogram->program, TB_FALSE);

	// use it
	glUseProgram(gprogram->program);
}
GLint g2_gl2x_program_attr(tb_handle_t program, tb_char_t const* name)
{
	// check
	g2_gl2x_program_t* gprogram = (g2_gl2x_program_t*)program;
	tb_assert_and_check_return_val(gprogram && gprogram->program && name, -1);

	return glGetAttribLocation(gprogram->program, name);
}
GLint g2_gl2x_program_unif(tb_handle_t program, tb_char_t const* name)
{
	// check
	g2_gl2x_program_t* gprogram = (g2_gl2x_program_t*)program;
	tb_assert_and_check_return_val(gprogram && gprogram->program && name, -1);

	return glGetUniformLocation(gprogram->program, name);
}
tb_size_t g2_gl2x_program_type(tb_handle_t program)
{
	// check
	g2_gl2x_program_t* gprogram = (g2_gl2x_program_t*)program;
	tb_assert_and_check_return_val(gprogram, 0);

	return gprogram->type;
}
tb_void_t g2_gl2x_program_type_set(tb_handle_t program, tb_size_t type)
{
	// check
	g2_gl2x_program_t* gprogram = (g2_gl2x_program_t*)program;
	tb_assert_and_check_return(gprogram);

	gprogram->type = type;
}
GLint g2_gl2x_program_location(tb_handle_t program, tb_size_t index)
{
	// check
	g2_gl2x_program_t* gprogram = (g2_gl2x_program_t*)program;
	tb_assert_and_check_return_val(gprogram && index < G2_GL2X_PROGRAM_LOCATION_MAXN, -1);

	return gprogram->location[index];
}
tb_void_t g2_gl2x_program_location_set(tb_handle_t program, tb_size_t index, GLuint location)
{
	// check
	g2_gl2x_program_t* gprogram = (g2_gl2x_program_t*)program;
	tb_assert_and_check_return(gprogram && index < G2_GL2X_PROGRAM_LOCATION_MAXN);

	gprogram->location[index] = location;
}

