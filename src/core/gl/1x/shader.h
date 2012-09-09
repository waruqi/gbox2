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
 * @file		shader.h
 *
 */
#ifndef G2_CORE_GL1x_SHADER_H
#define G2_CORE_GL1x_SHADER_H

/* ///////////////////////////////////////////////////////////////////////
 * includes
 */
#include "prefix.h"

/* ///////////////////////////////////////////////////////////////////////
 * types
 */

// the gl1x shader type constants
typedef enum __g2_gl1x_shader_type_t
{
	G2_GL1x_SHADER_TYPE_NONE 				= 0
,	G2_GL1x_SHADER_TYPE_GRADIENT_LINEAR 	= 1
,	G2_GL1x_SHADER_TYPE_GRADIENT_RADIAL 	= 2
,	G2_GL1x_SHADER_TYPE_GRADIENT_RADIAL2 	= 3
,	G2_GL1x_SHADER_TYPE_BITMAP 				= 4

}g2_gl1x_shader_type_t;

// the gl1x shader flag constants
typedef enum __g2_gl1x_shader_flag_t
{
	G2_GL1x_SHADER_FLAG_NONE 				= 0
,	G2_GL1x_SHADER_FLAG_ALPHA 				= 1

}g2_gl1x_shader_flag_t;

// the gl1x shader type
typedef struct __g2_gl1x_shader_t
{
	// the type
	tb_size_t 				type;

	// the flag
	tb_size_t 				flag;

	// the wrap
	tb_size_t 				wrap;

	// the refn
	tb_size_t 				refn;

	// the width
	tb_size_t 				width;

	// the height
	tb_size_t 				height;

	// the context
	tb_handle_t 			context;

	// the texture
	tb_uint_t* 				texture;

	// the matrix
	g2_matrix_t 			matrix;

}g2_gl1x_shader_t;

#endif
