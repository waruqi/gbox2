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
 * @file		matrix.h
 *
 */
#ifndef G2_CORE_GL_MATRIX_H
#define G2_CORE_GL_MATRIX_H

/* ///////////////////////////////////////////////////////////////////////
 * includes
 */
#include "prefix.h"

/* ///////////////////////////////////////////////////////////////////////
 * inlines
 */
static __tb_inline__ tb_void_t g2_gl_matrix_init(tb_float_t* gmatrix)
{
	gmatrix[0] 	= 1.0f;
	gmatrix[1] 	= 0.0f;
	gmatrix[2] 	= 0.0f;
	gmatrix[3] 	= 0.0f;
	gmatrix[4] 	= 0.0f;
	gmatrix[5] 	= 1.0f;
	gmatrix[6] 	= 0.0f; 
	gmatrix[7] 	= 0.0f;       
	gmatrix[8] 	= 0.0f;
	gmatrix[9] 	= 0.0f; 
	gmatrix[10] = -1.0f; 
	gmatrix[11] = 0.0f; 
	gmatrix[12] = 0.0f; 
	gmatrix[13] = 0.0f; 
	gmatrix[14] = 1.0f;
	gmatrix[15] = 1.0f;
}
static __tb_inline__ tb_void_t g2_gl_matrix_set(tb_float_t* gmatrix, g2_matrix_t const* matrix)
{
	gmatrix[0] 	= g2_float_to_tb(matrix->sx);
	gmatrix[1] 	= g2_float_to_tb(matrix->ky);
	gmatrix[2] 	= 0.0f;
	gmatrix[3] 	= 0.0f;
	gmatrix[4] 	= g2_float_to_tb(matrix->kx);
	gmatrix[5] 	= g2_float_to_tb(matrix->sy);
	gmatrix[6] 	= 0.0f; 
	gmatrix[7] 	= 0.0f;       
	gmatrix[8] 	= 0.0f;
	gmatrix[9] 	= 0.0f; 
	gmatrix[10] = -1.0f; 
	gmatrix[11] = 0.0f; 
	gmatrix[12] = g2_float_to_tb(matrix->tx); 
	gmatrix[13] = g2_float_to_tb(matrix->ty); 
	gmatrix[14] = 1.0f;
	gmatrix[15] = 1.0f;
}
#endif
