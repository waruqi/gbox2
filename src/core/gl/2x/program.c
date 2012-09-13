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

tb_bool_t g2_gl2x_program_init(g2_gl2x_program_t* program)
{
	// make
	tb_assert_and_check_return_val(program, TB_FALSE);

	// init
	tb_memset(program, 0, sizeof(g2_gl2x_program_t));
	program->program = glCreateProgram();
	tb_assert_and_check_return_val(program->program, TB_FALSE);

	// ok
	return TB_TRUE;
}
tb_void_t g2_gl2x_program_exit(g2_gl2x_program_t* program)
{
	// check
	tb_assert_and_check_return(program);

	// exit it
	if (program->exit) program->exit(program);

	// exit shaders
	tb_size_t i = 0;
	for (i = 0; i < program->shadern; i++)
	{
		if (program->shaders[i]) glDeleteShader(program->shaders[i]);
		program->shaders[i] = 0;
	}
	program->shadern = 0;

	// exit program
	if (program->program) glDeleteProgram(program->program);
	program->program = 0;
}
tb_bool_t g2_gl2x_program_load(g2_gl2x_program_t* program, tb_char_t const* shader, tb_size_t type)
{
	// check
	tb_assert_and_check_return_val(program && program->shadern < G2_GL2X_PROGRAM_SHADER_MAXN && shader && type, TB_FALSE);

	// load shader
	program->shaders[program->shadern] = g2_gl2x_program_shader(shader, type);
	tb_assert_and_check_return_val(program->shaders[program->shadern], TB_FALSE);
	program->shadern++;

	// attach shader
	glAttachShader(program->program, program->shaders[program->shadern - 1]);

	// ok
	return TB_TRUE;
}
tb_bool_t g2_gl2x_program_make(g2_gl2x_program_t* program)
{
	// check
	tb_assert_and_check_return_val(program && program->shadern, TB_FALSE);

	// link
	glLinkProgram(program->program);

	// ok?
	GLint ok = GL_FALSE;
	glGetProgramiv(program, GL_LINK_STATUS, &ok);
	if (ok == GL_FALSE) 
	{
		GLchar s[1024] = {0};
		glGetProgramInfoLog(program, sizeof(s), 0, &s[0]);
		tb_trace_impl("shader: link failed: %s", s);
		return TB_FALSE;
	}

	// exit shaders
	tb_size_t i = 0;
	for (i = 0; i < program->shadern; i++)
	{
		if (program->shaders[i]) glDeleteShader(program->shaders[i]);
		program->shaders[i] = 0;
	}
	program->shadern = 0;

	// ok
	return TB_TRUE;
}
tb_void_t g2_gl2x_program_uses(g2_gl2x_program_t* program)
{
	// check
	tb_assert_and_check_return_val(program && program->program, TB_FALSE);

	// use it
	glUseProgram(program->program);
}
tb_pointer_t g2_gl2x_program_attr(g2_gl2x_program_t* program, tb_char_t const* name)
{
	// check
	tb_assert_and_check_return_val(program && program->program && name, TB_NULL);

	return glGetAttribLocation(program->program, name);
}
tb_pointer_t g2_gl2x_program_unif(g2_gl2x_program_t* program, tb_char_t const* name)
{
	// check
	tb_assert_and_check_return_val(program && program->program && name, TB_NULL);

	return glGetUniformLocation(program->program, name);
}
