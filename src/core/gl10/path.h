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
 * @file		path.h
 *
 */
#ifndef G2_CORE_GL10_PATH_H
#define G2_CORE_GL10_PATH_H

/* ///////////////////////////////////////////////////////////////////////
 * includes
 */
#include "prefix.h"

/* ///////////////////////////////////////////////////////////////////////
 * types
 */

// the gl10 path itor type
typedef struct __g2_gl10_path_itor_t
{
	// the code
	tb_size_t 				code;

	// the data
	tb_size_t 				data;

}g2_gl10_path_itor_t;

// the gl10 path type
typedef struct __g2_gl10_path_t
{
	// is opened?
	tb_size_t 				open;

	// the code, vector<tb_byte_t>
	tb_vector_t* 			code;

	// the data, vector<g2_point_t>
	tb_vector_t* 			data;

	// the fill, vector<...>
	tb_vector_t* 			fill;

	// the stok, vector<...>
	tb_vector_t* 			stok;

	// the itor
	g2_gl10_path_itor_t 	itor;

}g2_gl10_path_t;

/* ///////////////////////////////////////////////////////////////////////
 * interfaces
 */

// make fill path for gl10
tb_bool_t g2_gl10_path_make_fill(g2_gl10_path_t* path);

// make stok path for gl10
tb_bool_t g2_gl10_path_make_stok(g2_gl10_path_t* path);

#endif
