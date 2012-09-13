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
#define G2_GL2X_PROGRAM_SHADER_MAXN 		(8)

/* ///////////////////////////////////////////////////////////////////////
 * types
 */

// the gl2x program type
typedef struct __g2_gl2x_program_t
{
	// the type
	tb_size_t 		type;

	// the shaders
	GLuint 			shaders[G2_GL2X_PROGRAM_SHADER_MAXN];
	tb_size_t 		shadern;

	// the program
	GLuint 			program;

}g2_gl2x_program_t;

/* ///////////////////////////////////////////////////////////////////////
 * shader
 */

static GLuint g2_gl2x_program_shader(tb_char_t const* data, tb_size_t type)
{
	// init shader
	GLuint shader = glCreateShader((GLenum)type);
	tb_assert_and_check_return_val(shader, TB_NULL);

	// init source
	GLint size = tb_strlen(data);
	glShaderSource(shader, 1, &data, &size);

	// compile shader
	glCompileShader(shader);

	// ok?
	GLint ok = GL_FALSE;
	glGetShaderiv(shader, GL_COMPILE_STATUS, &ok);
	if (ok == GL_FALSE)
	{
		GLchar s[1024] = {0};
		glGetShaderInfoLog(shader, sizeof(s), 0, &s[0]);
		tb_trace_impl("shader: compile failed: %s", s);
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
	// make
	g2_gl2x_program_t* program = tb_malloc0(sizeof(g2_gl2x_program_t));
	tb_assert_and_check_return_val(program, TB_NULL);

	// init
	program->program = glCreateProgram();
	tb_assert_and_check_goto(program->program, fail);

	// ok
	return program;

fail:
	if (program) g2_gl2x_program_exit(program);
	return TB_NULL;
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

	// attach shader
	glAttachShader(gprogram->program, gprogram->shaders[gprogram->shadern - 1]);

	// ok
	return TB_TRUE;
}
tb_bool_t g2_gl2x_program_make(tb_handle_t program)
{
	// check
	g2_gl2x_program_t* gprogram = (g2_gl2x_program_t*)program;
	tb_assert_and_check_return_val(gprogram && gprogram->shadern, TB_FALSE);

	// link
	glLinkProgram(gprogram->program);

	// ok?
	GLint ok = GL_FALSE;
	glGetProgramiv(gprogram, GL_LINK_STATUS, &ok);
	if (ok == GL_FALSE) 
	{
		GLchar s[1024] = {0};
		glGetProgramInfoLog(gprogram, sizeof(s), 0, &s[0]);
		tb_trace_impl("shader: link failed: %s", s);
		return TB_FALSE;
	}

	// exit shaders
	tb_size_t i = 0;
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
tb_pointer_t g2_gl2x_program_attr(tb_handle_t program, tb_char_t const* name)
{
	// check
	g2_gl2x_program_t* gprogram = (g2_gl2x_program_t*)program;
	tb_assert_and_check_return_val(gprogram && gprogram->program && name, TB_NULL);

	return glGetAttribLocation(gprogram->program, name);
}
tb_pointer_t g2_gl2x_program_unif(tb_handle_t program, tb_char_t const* name)
{
	// check
	g2_gl2x_program_t* gprogram = (g2_gl2x_program_t*)program;
	tb_assert_and_check_return_val(gprogram && gprogram->program && name, TB_NULL);

	return glGetUniformLocation(gprogram->program, name);
}
