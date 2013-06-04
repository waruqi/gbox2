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
#ifndef G2_CORE_GL_PATH_H
#define G2_CORE_GL_PATH_H

/* ///////////////////////////////////////////////////////////////////////
 * includes
 */
#include "prefix.h"

/* ///////////////////////////////////////////////////////////////////////
 * types
 */

// the gl path itor type
typedef struct __g2_gl_path_itor_t
{
	// the code
	tb_size_t 				code;

	// the data
	tb_size_t 				data;

}g2_gl_path_itor_t;

// the gl path fill type
typedef struct __g2_gl_path_fill_t
{
	// the rect bounds
	g2_gl_rect_t 			rect;

	// the data, vector<tb_float_t[2]>
	tb_vector_t* 			data;

	// the size, vector<tb_uint16_t>
	tb_vector_t* 			size;

}g2_gl_path_fill_t;

// the gl path stok type
typedef struct __g2_gl_path_stok_t
{
	// the data, vector<tb_float_t[2]>
	tb_vector_t* 			data;

	// the size, vector<tb_uint16_t>
	tb_vector_t* 			size;

}g2_gl_path_stok_t;

// the gl path flag type
typedef enum __g2_gl_path_flag_t
{
	G2_GL_PATH_FLAG_NONE 	= 0 	//< none
,	G2_GL_PATH_FLAG_OPEN 	= 1 	//< is opened?
,	G2_GL_PATH_FLAG_MOVE 	= 2 	//< has move-to?
,	G2_GL_PATH_FLAG_LINE 	= 4 	//< has line-to?
,	G2_GL_PATH_FLAG_QUAD 	= 8 	//< has quad-to?
,	G2_GL_PATH_FLAG_CUBE 	= 16 	//< has cube-to?

}g2_gl_path_flag_t;

// the gl path like type
typedef enum __g2_gl_path_like_t
{
	G2_GL_PATH_LIKE_NONE 	= 0 	//< none
,	G2_GL_PATH_LIKE_LINE 	= 1 	//< like line?
,	G2_GL_PATH_LIKE_RECT 	= 2 	//< like rect?
,	G2_GL_PATH_LIKE_TRIG 	= 3 	//< like triangle?
,	G2_GL_PATH_LIKE_CONX 	= 4 	//< like convex polygon?

}g2_gl_path_like_t;

// the gl path type
typedef struct __g2_gl_path_t
{
	// the flag
	tb_size_t 				flag;

	// the like
	tb_size_t 				like;

	// the liked line
	g2_line_t 				line;

	// the liked triangle
	g2_triangle_t			trig;

	// the liked rect or the bounds
	g2_gl_rect_t 			rect;

	// the last head
	g2_point_t 				head;

	// the code, vector<tb_byte_t>
	tb_vector_t* 			code;

	// the data, vector<tb_float_t[2]>
	tb_vector_t* 			data;

	// the size, vector<tb_uint16_t>
	tb_vector_t* 			size;

	// the fill path
	g2_gl_path_fill_t 		fill;

	// the stok path
	g2_gl_path_stok_t 		stok;

	// the itor
	g2_gl_path_itor_t 		itor;

}g2_gl_path_t;

/* ///////////////////////////////////////////////////////////////////////
 * interfaces
 */

// make fill path for gl
tb_bool_t g2_gl_path_make_fill(g2_gl_path_t* path);

// make stok path for gl
tb_bool_t g2_gl_path_make_stok(g2_gl_path_t* path);

// make like path for gl
tb_void_t g2_gl_path_make_like(g2_gl_path_t* path);

#endif
