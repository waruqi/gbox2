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
 * @file		clipper.h
 *
 */
#ifndef G2_CORE_CLIPPER_H
#define G2_CORE_CLIPPER_H

// c plus plus
#ifdef __cplusplus
extern "C" {
#endif

/* ///////////////////////////////////////////////////////////////////////
 * includes
 */
#include "prefix.h"
#include "matrix.h"

/* ///////////////////////////////////////////////////////////////////////
 * types
 */

// the clipper mode enum
typedef enum __g2_clipper_mode_e
{
	G2_CLIPPER_MODE_NONE 		= 0x00
,	G2_CLIPPER_MODE_SUBTRACT 	= 0x01
,	G2_CLIPPER_MODE_INTERSECT 	= 0x02
,	G2_CLIPPER_MODE_UNION 		= 0x03
,	G2_CLIPPER_MODE_REPLACE 	= 0x04

}g2_clipper_mode_e;

// the clipper item enum
typedef enum __g2_clipper_item_e
{
	G2_CLIPPER_ITEM_RECT 		= 0
, 	G2_CLIPPER_ITEM_PATH 		= 1
, 	G2_CLIPPER_ITEM_CIRCLE 		= 2
, 	G2_CLIPPER_ITEM_ELLIPSE 	= 3
, 	G2_CLIPPER_ITEM_TRIANGLE 	= 4

}g2_clipper_item_e;

// the clipper item type
typedef struct __g2_clipper_item_t
{
	// the clip mode
	tb_size_t 			mode 	: 16;

	// the clip type
	tb_size_t 			type 	: 16;

	// the clip item
	union 
	{
		// rect
		g2_rect_t 		rect;
		
		// path
		tb_handle_t 	path;
			
		// circle
		g2_circle_t 	circle;

		// ellipse
		g2_ellipse_t 	ellipse;

		// triangle
		g2_triangle_t 	triangle;

	}u;

	// the clip matrix
	g2_matrix_t 		matrix;

}g2_clipper_item_t;

/* ///////////////////////////////////////////////////////////////////////
 * interfaces
 */

// init & exit
tb_handle_t 				g2_clipper_init(tb_noarg_t);
tb_void_t 					g2_clipper_exit(tb_handle_t clipper);

// size
tb_size_t 					g2_clipper_size(tb_handle_t clipper);

// item
g2_clipper_item_t const* 	g2_clipper_item(tb_handle_t clipper, tb_size_t item);

// clear
tb_void_t 					g2_clipper_clear(tb_handle_t clipper);

// copy
tb_void_t 					g2_clipper_copy(tb_handle_t clipper, tb_handle_t copy);

// matrix
tb_void_t 					g2_clipper_matrix(tb_handle_t clipper, 			g2_matrix_t const* matrix);

// path
tb_void_t 					g2_clipper_path(tb_handle_t clipper, 			tb_size_t mode, tb_handle_t path);

// triangle
tb_void_t 					g2_clipper_triangle(tb_handle_t clipper, 		tb_size_t mode, g2_triangle_t const* triangle);
tb_void_t 					g2_clipper_triangle2(tb_handle_t clipper, 		tb_size_t mode, g2_float_t x0, g2_float_t y0, g2_float_t x1, g2_float_t y1, g2_float_t x2, g2_float_t y2);

// itriangle
tb_void_t 					g2_clipper_itriangle(tb_handle_t clipper, 		tb_size_t mode, g2_itriangle_t const* triangle);
tb_void_t 					g2_clipper_itriangle2(tb_handle_t clipper, 		tb_size_t mode, tb_long_t x0, tb_long_t y0, tb_long_t x1, tb_long_t y1, tb_long_t x2, tb_long_t y2);

// rect
tb_void_t 					g2_clipper_rect(tb_handle_t clipper, 			tb_size_t mode, g2_rect_t const* rect);
tb_void_t 					g2_clipper_rect2(tb_handle_t clipper, 			tb_size_t mode, g2_float_t x, g2_float_t y, g2_float_t w, g2_float_t h);

// irect
tb_void_t 					g2_clipper_irect(tb_handle_t clipper, 			tb_size_t mode, g2_irect_t const* rect);
tb_void_t 					g2_clipper_irect2(tb_handle_t clipper, 			tb_size_t mode, tb_long_t x, tb_long_t y, tb_size_t w, tb_size_t h);

// circle
tb_void_t 					g2_clipper_circle(tb_handle_t clipper, 			tb_size_t mode, g2_circle_t const* circle);
tb_void_t 					g2_clipper_circle2(tb_handle_t clipper, 		tb_size_t mode, g2_float_t x0, g2_float_t y0, g2_float_t r);

// icircle
tb_void_t 					g2_clipper_icircle(tb_handle_t clipper, 		tb_size_t mode, g2_icircle_t const* circle);
tb_void_t 					g2_clipper_icircle2(tb_handle_t clipper, 		tb_size_t mode, tb_long_t x0, tb_long_t y0, tb_size_t r);

// ellipse
tb_void_t 					g2_clipper_ellipse(tb_handle_t clipper, 		tb_size_t mode, g2_ellipse_t const* ellipse);
tb_void_t 					g2_clipper_ellipse2(tb_handle_t clipper, 		tb_size_t mode, g2_float_t x0, g2_float_t y0, g2_float_t rx, g2_float_t ry);

// iellipse
tb_void_t 					g2_clipper_iellipse(tb_handle_t clipper, 		tb_size_t mode, g2_iellipse_t const* ellipse);
tb_void_t 					g2_clipper_iellipse2(tb_handle_t clipper, 		tb_size_t mode, tb_long_t x0, tb_long_t y0, tb_size_t rx, tb_size_t ry);

// c plus plus
#ifdef __cplusplus
}
#endif

#endif
