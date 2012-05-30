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
 * @file		type.h
 *
 */
#ifndef G2_PREFIX_TYPE_H
#define G2_PREFIX_TYPE_H

/* ///////////////////////////////////////////////////////////////////////
 * includes
 */
#include "config.h"

/* ///////////////////////////////////////////////////////////////////////
 * macros
 */

/* ///////////////////////////////////////////////////////////////////////
 * types
 */

// scalar
#ifdef G2_CONFIG_SCALAR_FIXED
typedef tb_fixed_t 		g2_scalar_t;
#else
typedef tb_float_t 		g2_scalar_t;
#endif

// the pixel type
typedef tb_uint32_t 	g2_pixel_t;

// the alpha type
typedef tb_byte_t 		g2_alpha_t;

// the point type
typedef struct __g2_point_t
{
	g2_scalar_t 		x;
	g2_scalar_t 		y;

}g2_point_t;

// the ipoint type
typedef struct __g2_ipoint_t
{
	tb_long_t 			x;
	tb_long_t 			y;

}g2_ipoint_t;

// the line type
typedef struct __g2_line_t
{
	g2_point_t 			p1;
	g2_point_t 			p2;

}g2_line_t;

// the iline type
typedef struct __g2_iline_t
{
	g2_ipoint_t 		p1;
	g2_ipoint_t 		p2;

}g2_iline_t;

// the triangle type
typedef struct __g2_triangle_t
{
	g2_point_t 			p1;
	g2_point_t 			p2;
	g2_point_t 			p3;

}g2_triangle_t;

// the itriangle type
typedef struct __g2_itriangle_t
{
	g2_ipoint_t 		p1;
	g2_ipoint_t 		p2;
	g2_ipoint_t 		p3;

}g2_itriangle_t;

// the rect type
typedef struct __g2_rect_t
{
	g2_scalar_t 		x;
	g2_scalar_t 		y;
	g2_scalar_t 		w;
	g2_scalar_t 		h;

}g2_rect_t;

// the irect type
typedef struct __g2_irect_t
{
	tb_long_t 			x;
	tb_long_t 			y;
	tb_size_t 			w;
	tb_size_t 			h;

}g2_irect_t;

// the lines type
typedef struct __g2_lines_t
{
	// the points data
	g2_point_t* 		pts;
	// the points size
	tb_size_t 			ptn;

	// the lines data
	tb_size_t* 			lns;
	// the lines size
	tb_size_t 			lnn;

}g2_lines_t;

// the ilines type
typedef struct __g2_ilines_t
{
	// the points data
	g2_ipoint_t* 		pts;
	// the points size
	tb_size_t 			ptn;

	// the lines data
	tb_size_t* 			lns;
	// the lines size
	tb_size_t 			lnn;

}g2_ilines_t;

// the polygon type
typedef g2_lines_t 		g2_polygon_t;

// the ipolygon type
typedef g2_ilines_t 	g2_ipolygon_t;

// the curve1 type
typedef struct __g2_curve1_t
{
	// the endpoint
	g2_point_t 			p1;
	g2_point_t 			p2;

	// the control point
	g2_point_t 			cp;

}g2_curve1_t;

// the icurve1 type
typedef struct __g2_icurve1_t
{
	// the endpoint
	g2_ipoint_t 		p1;
	g2_ipoint_t 		p2;

	// the control point
	g2_ipoint_t 		cp;

}g2_icurve1_t;

// the curve2 type
typedef struct __g2_curve2_t
{
	// the endpoint
	g2_point_t 			p1;
	g2_point_t 			p2;

	// the control point
	g2_point_t 			c1;
	g2_point_t 			c2;

}g2_curve2_t;

// the icurve2 type
typedef struct __g2_icurve2_t
{
	// the endpoint
	g2_ipoint_t 		p1;
	g2_ipoint_t 		p2;

	// the control point
	g2_ipoint_t 		c1;
	g2_ipoint_t 		c2;

}g2_icurve2_t;

// the circle type
typedef struct __g2_circle_t
{
	// the center point
	g2_point_t 			c;

	// the radius
	g2_scalar_t 		r;

}g2_circle_t;

// the icircle type
typedef struct __g2_icircle_t
{
	// the center point
	g2_ipoint_t 		c;

	// the radius
	tb_size_t 			r;

}g2_icircle_t;

// the ellipse type
typedef struct __g2_ellipse_t
{
	// the center point
	g2_point_t 			c0;

	// the radius of x & y
	g2_scalar_t 		rx;
	g2_scalar_t 		ry;

}g2_ellipse_t;

// the iellipse type
typedef struct __g2_iellipse_t
{
	// the center point
	g2_ipoint_t 		c0;

	// the radius of x & y
	tb_size_t 			rx;
	tb_size_t 			ry;

}g2_iellipse_t;

// the arc type
typedef struct __g2_arc_t
{
	// the ellipse 
	g2_ellipse_t 		e0;

	// the start angle
	g2_scalar_t 		ab;

	// the sweep angle, 0 - 360
	g2_scalar_t 		an;

}g2_arc_t;

// the iarc type
typedef struct __g2_iarc_t
{
	// the ellipse 	
	g2_iellipse_t 		e0;

	// the start angle
	tb_long_t 			ab;

	// the sweep angle, 0 - 360
	tb_size_t 			an;

}g2_iarc_t;

// the chord type
typedef g2_arc_t 		g2_chord_t;

// the pie type
typedef g2_arc_t 		g2_pie_t;

// the text type
typedef struct __g2_text_t
{
	// the postion 
	g2_point_t 			pt;

	// the text
	tb_char_t const* 	data;
	tb_size_t 			size;

}g2_text_t;


/*!the color type
 *
 * @code
 * union __g2_color2pixel_t
 * {
 * 		g2_color_t c;
 * 		g2_pixel_t p;
 *
 * 	}c2p;
 * 	c2p.c = c;
 * 	return c2p.p;
 * @endcode
 *
 */
#ifdef TB_WORDS_BIGENDIAN
typedef struct __g2_color_t
{
	tb_byte_t 			a;
	tb_byte_t 			r;
	tb_byte_t 			g;
	tb_byte_t 			b;

}g2_color_t;
#else
typedef struct __g2_color_t
{
	tb_byte_t 			b;
	tb_byte_t 			g;
	tb_byte_t 			r;
	tb_byte_t 			a;

}g2_color_t;
#endif

// the transforam matrix type
typedef struct __g2_matrix_t
{
	g2_scalar_t 		xx, xy;
	g2_scalar_t 		yx, yy;
	g2_scalar_t 		tx, ty;

}g2_matrix_t;

typedef int g2_path_t;


#endif


