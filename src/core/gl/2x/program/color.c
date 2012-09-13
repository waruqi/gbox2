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
 * @file		color.c
 *
 */

/* ///////////////////////////////////////////////////////////////////////
 * trace
 */
#define TB_TRACE_IMPL_TAG 		"gl2x"

/* ///////////////////////////////////////////////////////////////////////
 * includes
 */
#include "prefix.h"

/* ///////////////////////////////////////////////////////////////////////
 * implementation
 */

tb_handle_t g2_gl2x_program_init_color()
{
	// init
	tb_handle_t program = g2_gl2x_program_init();
	tb_assert_and_check_return_val(program, TB_NULL);

	// the vertex shader
	tb_char_t const* vshader = 
		"precision mediump float; 												\n"
		" 																		\n"
		"attribute vec4 aColor; 												\n"
		"attribute vec4 aVertices; 												\n"
		" 																		\n"
		"varying vec4 vColor; 													\n"
		"uniform mat4 uMatrix; 													\n"
		" 																		\n"
		"void main() 															\n"
		"{ 																		\n"
		" 	vColor = aColor; 													\n"
		" 	gl_Position = uMatrix * aVertices; 									\n"                                                                  
		"} 																		\n";
	
	// the fragment shader
	tb_char_t const* fshader = 
		"precision mediump float; 												\n"
		" 																		\n"
		"varying vec4 vColor; 													\n"
		" 																		\n"
		"void main() 															\n"
		"{ 																		\n"
		"   gl_FragColor = vColor; 												\n"
		"} 																		\n";

	// load shader: vertex
	if (!g2_gl2x_program_load(program, vshader, GL_VERTEX_SHADER)) goto fail;
	
	// load shader: fragment
	if (!g2_gl2x_program_load(program, fshader, GL_FRAGMENT_SHADER)) goto fail;

	// make program
	if (!g2_gl2x_program_make(program)) goto fail;

	// ok
	return program;
fail:
	if (program) g2_gl2x_program_exit(program);
	return TB_NULL;
}

