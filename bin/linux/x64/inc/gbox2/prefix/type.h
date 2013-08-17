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
#include "pixfmt.h"
#include "float.h"
#include "color.h"

/* ///////////////////////////////////////////////////////////////////////
 * macros
 */

/* ///////////////////////////////////////////////////////////////////////
 * types
 */

// the quality enum
typedef enum __g2_quality_e
{
	G2_QUALITY_LOW 	= 0
,	G2_QUALITY_MID 	= 1
,	G2_QUALITY_TOP 	= 2

}g2_quality_e;

// the float type
#ifdef G2_CONFIG_FLOAT_FIXED
typedef tb_fixed_t 		g2_float_t;
#else
typedef tb_float_t 		g2_float_t;
#endif

// the pixel type
typedef tb_uint32_t 	g2_pixel_t;

// the point type
typedef struct __g2_point_t
{
	g2_float_t 			x;
	g2_float_t 			y;

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
	g2_point_t 			p0;
	g2_point_t 			p1;

}g2_line_t;

// the iline type
typedef struct __g2_iline_t
{
	g2_ipoint_t 		p0;
	g2_ipoint_t 		p1;

}g2_iline_t;

// the triangle type
typedef struct __g2_triangle_t
{
	g2_point_t 			p0;
	g2_point_t 			p1;
	g2_point_t 			p2;

}g2_triangle_t;

// the itriangle type
typedef struct __g2_itriangle_t
{
	g2_ipoint_t 		p0;
	g2_ipoint_t 		p1;
	g2_ipoint_t 		p2;

}g2_itriangle_t;

// the rect type
typedef struct __g2_rect_t
{
	g2_float_t 			x;
	g2_float_t 			y;
	g2_float_t 			w;
	g2_float_t 			h;

}g2_rect_t;

// the irect type
typedef struct __g2_irect_t
{
	tb_long_t 			x;
	tb_long_t 			y;
	tb_size_t 			w;
	tb_size_t 			h;

}g2_irect_t;

// the circle type
typedef struct __g2_circle_t
{
	// the center point
	g2_point_t 			c;

	// the radius
	g2_float_t 			r;

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
	g2_float_t 			rx;
	g2_float_t 			ry;

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
	// the center point
	g2_point_t 			c0;

	// the radius of x & y
	g2_float_t 			rx;
	g2_float_t 			ry;

	// the start angle
	g2_float_t 			ab;

	// the sweep angle, 0 - 360
	g2_float_t 			an;

}g2_arc_t;

// the iarc type
typedef struct __g2_iarc_t
{
	// the center point
	g2_ipoint_t 		c0;

	// the radius of x & y
	tb_size_t 			rx;
	tb_size_t 			ry;

	// the start angle
	tb_long_t 			ab;

	// the sweep angle, 0 - 360
	tb_size_t 			an;

}g2_iarc_t;

// the gradient type
typedef struct __g2_gradient_t
{
	// the color
	g2_color_t* 		color;

	// the radio
	g2_float_t* 		radio;

	// the count
	tb_size_t 			count;

}g2_gradient_t;

// the shape type enum
typedef enum __g2_shape_type_e
{
 	G2_SHAPE_TYPE_NONE 			= 0
, 	G2_SHAPE_TYPE_ARC 			= 1
, 	G2_SHAPE_TYPE_PATH 			= 2
, 	G2_SHAPE_TYPE_LINE 			= 3
, 	G2_SHAPE_TYPE_RECT 			= 4
, 	G2_SHAPE_TYPE_POINT 		= 5
, 	G2_SHAPE_TYPE_CIRCLE 		= 6
, 	G2_SHAPE_TYPE_ELLIPSE 		= 7
, 	G2_SHAPE_TYPE_TRIANGLE 		= 8

}g2_shape_type_e;

// the shape type
typedef struct __g2_shape_t
{
	// the type
	tb_size_t 			type;

	// the shape
	union
	{
		// the arc
		g2_arc_t 		arc;

		// the path
		tb_handle_t 	path;

		// the line
		g2_line_t 		line;

		// the rect
		g2_rect_t 		rect;

		// the point
		g2_point_t 		point;

		// the circle
		g2_circle_t 	circle;
	
		// the ellipse
		g2_ellipse_t 	ellipse;

		// the triangle
		g2_triangle_t 	triangle;

	}u;

}g2_shape_t;


/* ////////////////////////////////////////////////////////////////////////
 * inline
 */

// make point
static __tb_inline__ g2_point_t g2_point_make(g2_float_t x, g2_float_t y)
{
	g2_point_t pt;

	pt.x = x;
	pt.y = y;

	return pt;
}

// make point with integer
static __tb_inline__ g2_point_t g2_point_imake(tb_long_t x, tb_long_t y)
{
	g2_point_t pt;

	pt.x = g2_long_to_float(x);
	pt.y = g2_long_to_float(y);

	return pt;
}

// make ipoint
static __tb_inline__ g2_ipoint_t g2_ipoint_make(tb_long_t x, tb_long_t y)
{
	g2_ipoint_t pt;

	pt.x = x;
	pt.y = y;

	return pt;
}

// ipoint => point
static __tb_inline__ g2_point_t g2_ipoint_to_point(g2_ipoint_t const* point)
{
	g2_point_t pt;
	
	pt.x = g2_long_to_float(point->x);
	pt.y = g2_long_to_float(point->y);

	return pt;
}

// make rect
static __tb_inline__ g2_rect_t g2_rect_make(g2_float_t x, g2_float_t y, g2_float_t w, g2_float_t h)
{
	g2_rect_t r;

	r.x = x;
	r.y = y;
	r.w = w;
	r.h = h;

	return r;
}

// make rect with integer
static __tb_inline__ g2_rect_t g2_rect_imake(tb_long_t x, tb_long_t y, tb_size_t w, tb_size_t h)
{
	g2_rect_t r;

	r.x = g2_long_to_float(x);
	r.y = g2_long_to_float(y);
	r.w = g2_long_to_float(w);
	r.h = g2_long_to_float(h);

	return r;
}

// make irect
static __tb_inline__ g2_irect_t g2_irect_make(tb_long_t x, tb_long_t y, tb_size_t w, tb_size_t h)
{
	g2_irect_t r;

	r.x = x;
	r.y = y;
	r.w = w;
	r.h = h;

	return r;
}

// irect => rect
static __tb_inline__ g2_rect_t g2_irect_to_rect(g2_irect_t const* rect)
{
	g2_rect_t r;
	
	r.x = g2_long_to_float(rect->x);
	r.y = g2_long_to_float(rect->y);
	r.w = g2_long_to_float(rect->w);
	r.h = g2_long_to_float(rect->h);

	return r;
}

// inflate rect
static __tb_inline__ tb_void_t g2_rect_inflate(g2_rect_t* rect, g2_float_t inc)
{
	rect->x -= inc;
	rect->y -= inc;
	rect->w += inc + inc;
	rect->h += inc + inc;
}

// deflate rect
static __tb_inline__ tb_void_t g2_rect_deflate(g2_rect_t* rect, g2_float_t dec)
{
	g2_float_t dec2 = dec + dec;

	rect->x += dec;
	rect->y += dec;
	if (rect->w >= dec2) rect->w -= dec2;
	if (rect->h >= dec2) rect->h -= dec2;
}

// inflate irect
static __tb_inline__ tb_void_t g2_irect_inflate(g2_irect_t* rect, tb_size_t inc)
{
	rect->x -= inc;
	rect->y -= inc;
	rect->w += inc + inc;
	rect->h += inc + inc;
}

// deflate irect
static __tb_inline__ tb_void_t g2_irect_deflate(g2_irect_t* rect, tb_size_t dec)
{
	tb_size_t dec2 = dec + dec;

	rect->x += dec;
	rect->y += dec;
	if (rect->w >= dec2) rect->w -= dec2;
	if (rect->h >= dec2) rect->h -= dec2;
}

// make line
static __tb_inline__ g2_line_t g2_line_make(g2_float_t x0, g2_float_t y0, g2_float_t x1, g2_float_t y1)
{
	g2_line_t l;

	l.p0.x = x0;
	l.p0.y = y0;
	l.p1.x = x1;
	l.p1.y = y1;

	return l;
}

// make line with integer
static __tb_inline__ g2_line_t g2_line_imake(tb_long_t x0, tb_long_t y0, tb_size_t x1, tb_size_t y1)
{
	g2_line_t l;

	l.p0.x = g2_long_to_float(x0);
	l.p0.y = g2_long_to_float(y0);
	l.p1.x = g2_long_to_float(x1);
	l.p1.y = g2_long_to_float(y1);

	return l;
}

// make iline
static __tb_inline__ g2_iline_t g2_iline_make(tb_long_t x0, tb_long_t y0, tb_size_t x1, tb_size_t y1)
{
	g2_iline_t l;

	l.p0.x = x0;
	l.p0.y = y0;
	l.p1.x = x1;
	l.p1.y = y1;

	return l;
}

// iline => line
static __tb_inline__ g2_line_t g2_iline_to_line(g2_iline_t const* line)
{
	g2_line_t l;

	l.p0 = g2_ipoint_to_point(&line->p0);
	l.p1 = g2_ipoint_to_point(&line->p1);

	return l;
}

// make triangle
static __tb_inline__ g2_triangle_t g2_triangle_make(g2_float_t x0, g2_float_t y0, g2_float_t x1, g2_float_t y1, g2_float_t x2, g2_float_t y2)
{
	g2_triangle_t t;

	t.p0.x = x0;
	t.p0.y = y0;
	t.p1.x = x1;
	t.p1.y = y1;
	t.p2.x = x2;
	t.p2.y = y2;

	return t;
}

// make triangle with integer
static __tb_inline__ g2_triangle_t g2_triangle_imake(tb_long_t x0, tb_long_t y0, tb_size_t x1, tb_size_t y1, tb_size_t x2, tb_size_t y2)
{
	g2_triangle_t t;

	t.p0.x = g2_long_to_float(x0);
	t.p0.y = g2_long_to_float(y0);
	t.p1.x = g2_long_to_float(x1);
	t.p1.y = g2_long_to_float(y1);
	t.p2.x = g2_long_to_float(x2);
	t.p2.y = g2_long_to_float(y2);

	return t;
}

// make itriangle
static __tb_inline__ g2_itriangle_t g2_itriangle_make(tb_long_t x0, tb_long_t y0, tb_size_t x1, tb_size_t y1, tb_size_t x2, tb_size_t y2)
{
	g2_itriangle_t t;

	t.p0.x = x0;
	t.p0.y = y0;
	t.p1.x = x1;
	t.p1.y = y1;
	t.p2.x = x2;
	t.p2.y = y2;

	return t;
}

// itriangle => triangle
static __tb_inline__ g2_triangle_t g2_itriangle_to_triangle(g2_itriangle_t const* triangle)
{
	g2_triangle_t t;

	t.p0 = g2_ipoint_to_point(&triangle->p0);
	t.p1 = g2_ipoint_to_point(&triangle->p1);
	t.p2 = g2_ipoint_to_point(&triangle->p2);

	return t;
}

// make circle
static __tb_inline__ g2_circle_t g2_circle_make(g2_float_t x0, g2_float_t y0, g2_float_t r)
{
	g2_circle_t c;

	c.c.x 	= x0;
	c.c.y 	= y0;
	c.r 	= r;

	return c;
}

// make circle with integer
static __tb_inline__ g2_circle_t g2_circle_imake(tb_long_t x0, tb_long_t y0, tb_size_t r)
{
	g2_circle_t c;

	c.c.x 	= g2_long_to_float(x0);
	c.c.y 	= g2_long_to_float(y0);
	c.r 	= g2_long_to_float(r);

	return c;
}

// make icircle
static __tb_inline__ g2_icircle_t g2_icircle_make(tb_long_t x0, tb_long_t y0, tb_size_t r)
{
	g2_icircle_t c;

	c.c.x 	= x0;
	c.c.y 	= y0;
	c.r 	= r;

	return c;
}

// icircle => circle
static __tb_inline__ g2_circle_t g2_icircle_to_circle(g2_icircle_t const* circle)
{
	g2_circle_t c;

	c.c 	= g2_ipoint_to_point(&circle->c);
	c.r 	= g2_long_to_float(circle->r);

	return c;
}

// make ellipse
static __tb_inline__ g2_ellipse_t g2_ellipse_make(g2_float_t x0, g2_float_t y0, g2_float_t rx, g2_float_t ry)
{
	g2_ellipse_t e;

	e.c0.x 	= x0;
	e.c0.y 	= y0;
	e.rx 	= rx;
	e.ry 	= ry;

	return e;
}

// make ellipse with integer
static __tb_inline__ g2_ellipse_t g2_ellipse_imake(tb_long_t x0, tb_long_t y0, tb_size_t rx, tb_size_t ry)
{
	g2_ellipse_t e;

	e.c0.x 	= g2_long_to_float(x0);
	e.c0.y 	= g2_long_to_float(y0);
	e.rx 	= g2_long_to_float(rx);
	e.ry 	= g2_long_to_float(ry);

	return e;
}

// make iellipse
static __tb_inline__ g2_iellipse_t g2_iellipse_make(tb_long_t x0, tb_long_t y0, tb_size_t rx, tb_size_t ry)
{
	g2_iellipse_t e;

	e.c0.x 	= x0;
	e.c0.y 	= y0;
	e.rx 	= rx;
	e.ry 	= ry;

	return e;
}

// iellipse => ellipse
static __tb_inline__ g2_ellipse_t g2_iellipse_to_ellipse(g2_iellipse_t const* ellipse)
{
	g2_ellipse_t e;

	e.c0 	= g2_ipoint_to_point(&ellipse->c0);
	e.rx 	= g2_long_to_float(ellipse->rx);
	e.ry 	= g2_long_to_float(ellipse->ry);

	return e;
}

// make arc
static __tb_inline__ g2_arc_t g2_arc_make(g2_float_t x0, g2_float_t y0, g2_float_t rx, g2_float_t ry, g2_float_t ab, g2_float_t an)
{
	g2_arc_t a;

	a.c0.x 	= x0;
	a.c0.y 	= y0;
	a.rx 	= rx;
	a.ry 	= ry;
	a.ab 	= ab;
	a.an 	= an;

	return a;
}

// make arc with integer
static __tb_inline__ g2_arc_t g2_arc_imake(tb_long_t x0, tb_long_t y0, tb_size_t rx, tb_size_t ry, tb_size_t ab, tb_size_t an)
{
	g2_arc_t a;

	a.c0.x 	= g2_long_to_float(x0);
	a.c0.y 	= g2_long_to_float(y0);
	a.rx 	= g2_long_to_float(rx);
	a.ry 	= g2_long_to_float(ry);
	a.ab 	= g2_long_to_float(ab);
	a.an 	= g2_long_to_float(an);

	return a;
}

// make iarc
static __tb_inline__ g2_iarc_t g2_iarc_make(tb_long_t x0, tb_long_t y0, tb_size_t rx, tb_size_t ry, tb_size_t ab, tb_size_t an)
{
	g2_iarc_t a;

	a.c0.x 	= x0;
	a.c0.y 	= y0;
	a.rx 	= rx;
	a.ry 	= ry;
	a.ab 	= ab;
	a.an 	= an;

	return a;
}

// iarc => arc
static __tb_inline__ g2_arc_t g2_iarc_to_arc(g2_iarc_t const* arc)
{
	g2_arc_t a;

	a.c0 	= g2_ipoint_to_point(&arc->c0);
	a.rx 	= g2_long_to_float(arc->rx);
	a.ry 	= g2_long_to_float(arc->ry);
	a.ab 	= g2_long_to_float(arc->ab);
	a.an 	= g2_long_to_float(arc->an);

	return a;
}
#endif


