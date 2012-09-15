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
 * types
 */

// the gl2x program type
typedef enum __g2_gl2x_program_type_t
{
	G2_GL2X_PROGRAM_TYPE_NONE 	= 0
,	G2_GL2X_PROGRAM_TYPE_COLOR 	= 1
, 	G2_GL2X_PROGRAM_TYPE_MAXN 	= 2

}g2_gl2x_program_type_t;

// the gl2x program location type
typedef enum __g2_gl2x_program_location_t
{
	G2_GL2X_PROGRAM_LOCATION_COLOR 				= 0
,	G2_GL2X_PROGRAM_LOCATION_VERTICES 			= 1
,	G2_GL2X_PROGRAM_LOCATION_MATRIX_MODEL 		= 2
,	G2_GL2X_PROGRAM_LOCATION_MATRIX_PROJECT 	= 3

}g2_gl2x_program_location_t;

/* ///////////////////////////////////////////////////////////////////////
 * interfaces
 */

// init & exit
tb_handle_t 		g2_gl2x_program_init();
tb_void_t 			g2_gl2x_program_exit(tb_handle_t program);

// load shader
tb_bool_t 			g2_gl2x_program_load(tb_handle_t program, tb_char_t const* shader, tb_size_t type);

// make program
tb_bool_t 			g2_gl2x_program_make(tb_handle_t program);

// uses program
tb_void_t 			g2_gl2x_program_uses(tb_handle_t program);

// the attribute location
GLint 				g2_gl2x_program_attr(tb_handle_t program, tb_char_t const* name);

// the uniform location
GLint 				g2_gl2x_program_unif(tb_handle_t program, tb_char_t const* name);

// the type
tb_size_t 			g2_gl2x_program_type(tb_handle_t program);
tb_void_t 			g2_gl2x_program_type_set(tb_handle_t program, tb_size_t type);

// the location
GLint 				g2_gl2x_program_location(tb_handle_t program, tb_size_t index);
tb_void_t 			g2_gl2x_program_location_set(tb_handle_t program, tb_size_t index, GLuint GLint);


#endif
