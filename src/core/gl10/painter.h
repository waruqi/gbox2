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
 * @file		painter.h
 *
 */
#ifndef G2_CORE_GL10_PAINTER_H
#define G2_CORE_GL10_PAINTER_H

/* ///////////////////////////////////////////////////////////////////////
 * includes
 */
#include "context.h"

/* ///////////////////////////////////////////////////////////////////////
 * types
 */

// the gl110 matrix and clip item type for stack
typedef struct __g2_gl10_mcitem_t
{
	// the mode
	tb_size_t 					mode;

	// the matrix
	g2_matrix_t 				matrix;

	// the clipper
	tb_handle_t 				clipper;

}g2_gl10_mcitem_t;

// the gl10 painter type
typedef struct __g2_gl10_painter_t
{
	// the context
	g2_gl10_context_t* 			context;

	// the matrix
	g2_matrix_t 				matrix;

	// the style
	tb_handle_t 				style_def;
	tb_handle_t 				style_usr;

	// the vertices, vector<tb_float_t[2]>
	tb_vector_t* 				vertices;

	// the matrix and clipper stack
	tb_stack_t* 				mcstack;

}g2_gl10_painter_t;


#endif
