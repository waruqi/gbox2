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
 * @file		program.h
 *
 */
#ifndef G2_CORE_GL2x_PROGRAM_H
#define G2_CORE_GL2x_PROGRAM_H

/* ///////////////////////////////////////////////////////////////////////
 * includes
 */
#include "prefix.h"

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
	// the shaders
	GLuint 			shaders[G2_GL2X_PROGRAM_SHADER_MAXN];
	tb_size_t 		shadern;

	// the program
	GLuint 			program;

	// exit
	tb_void_t 		(*exit)(struct __g2_gl2x_program_t* program);

}g2_gl2x_program_t;

/* ///////////////////////////////////////////////////////////////////////
 * interfaces
 */

// init & exit
tb_bool_t 			g2_gl2x_program_init(g2_gl2x_program_t* program);
tb_void_t 			g2_gl2x_program_exit(g2_gl2x_program_t* program);

// init program: color
g2_gl2x_program_t* 	g2_gl2x_program_init_color();

// load shader
tb_bool_t 			g2_gl2x_program_load(g2_gl2x_program_t* program, tb_char_t const* shader, tb_size_t type);

// make program
tb_bool_t 			g2_gl2x_program_make(g2_gl2x_program_t* program);

// uses program
tb_void_t 			g2_gl2x_program_uses(g2_gl2x_program_t* program);

// the attribute location
tb_pointer_t 		g2_gl2x_program_attr(g2_gl2x_program_t* program, tb_char_t const* name);

// the uniform location
tb_pointer_t 		g2_gl2x_program_unif(g2_gl2x_program_t* program, tb_char_t const* name);


#endif
