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
 * @file		color.h
 *
 */
#ifndef G2_PREFIX_COLOR_H
#define G2_PREFIX_COLOR_H

// c plus plus
#ifdef __cplusplus
extern "C" {
#endif

/* ///////////////////////////////////////////////////////////////////////
 * includes
 */
#include "config.h"

/* ///////////////////////////////////////////////////////////////////////
 * macros
 */

// the color initializer
#ifdef TB_WORDS_BIGENDIAN
// {a, r, g, b}
# 	define G2_COLOR_INIT_BLACK 			{ 255, 	0, 		0, 		0 	}
# 	define G2_COLOR_INIT_BLUE 			{ 255, 	0, 		0, 		255 }
# 	define G2_COLOR_INIT_BROWN 			{ 255, 	128, 	0, 		0 	}
# 	define G2_COLOR_INIT_GREEN 			{ 255, 	0, 		255, 	0 	}
# 	define G2_COLOR_INIT_ORANGE 		{ 255, 	255, 	128, 	0 	}
# 	define G2_COLOR_INIT_PINK 			{ 255, 	255, 	0, 		255 }
# 	define G2_COLOR_INIT_RED 			{ 255, 	255, 	0, 		0 	}
# 	define G2_COLOR_INIT_YELLOW 		{ 255, 	255, 	255, 	0 	}
# 	define G2_COLOR_INIT_WHITE 			{ 255, 	255, 	255, 	255 }
#else
// {b, g, r, a}
# 	define G2_COLOR_INIT_BLACK 			{ 0, 	0, 		0, 		255 }
# 	define G2_COLOR_INIT_BLUE 			{ 255, 	0, 		0, 		255 }
# 	define G2_COLOR_INIT_BROWN 			{ 0, 	0, 		128, 	255 }
# 	define G2_COLOR_INIT_GREEN 			{ 0, 	255, 	0, 		255 }
# 	define G2_COLOR_INIT_ORANGE 		{ 0, 	128, 	255, 	255 }
# 	define G2_COLOR_INIT_PINK 			{ 255, 	0, 		255, 	255 }
# 	define G2_COLOR_INIT_RED 			{ 0, 	0, 		255, 	255 }
# 	define G2_COLOR_INIT_YELLOW 		{ 0, 	255, 	255, 	255 }
# 	define G2_COLOR_INIT_WHITE 			{ 255, 	255, 	255, 	255 }
#endif

// the color contants
#define G2_COLOR_BLACK 					(g2_color_from_index(0)->color)
#define G2_COLOR_BLUE 					(g2_color_from_index(1)->color)
#define G2_COLOR_BROWN 					(g2_color_from_index(2)->color)
#define G2_COLOR_GREEN 					(g2_color_from_index(3)->color)
#define G2_COLOR_ORANGE 				(g2_color_from_index(4)->color)
#define G2_COLOR_PINK 					(g2_color_from_index(5)->color)
#define G2_COLOR_RED 					(g2_color_from_index(6)->color)
#define G2_COLOR_YELLOW 				(g2_color_from_index(7)->color)
#define G2_COLOR_WHITE 					(g2_color_from_index(8)->color)
#define G2_COLOR_DEFAULT 				G2_COLOR_BLACK

/* ///////////////////////////////////////////////////////////////////////
 * types
 */

/*!the color type
 *
 * @code
 * union __g2_c2p_t
 * {
 * 		g2_color_t c;
 * 		g2_pixel_t p;
 *
 * }c2p;
 * c2p.c = c;
 * return c2p.p;
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

// the named color type
typedef struct __g2_named_color_t
{
	// the name
	tb_char_t const* 	name;

	// the color
	g2_color_t 			color;

}g2_named_color_t;

/* ////////////////////////////////////////////////////////////////////////
 * inline
 */

// make
static __tb_inline__ g2_color_t g2_color_make(tb_byte_t a, tb_byte_t r, tb_byte_t g, tb_byte_t b)
{
	g2_color_t c;

	c.a = a;
	c.r = r;
	c.g = g;
	c.b = b;

	return c;
}

// pixel
static __tb_inline__ tb_uint32_t g2_color_pixel(g2_color_t color)
{
	union __g2_c2p_t
	{
		g2_color_t 	c;
		tb_uint32_t p;

	}c2p;
	c2p.c = color;
	return c2p.p;
}

// color
static __tb_inline__ g2_color_t g2_pixel_color(tb_uint32_t pixel)
{
	union __g2_p2c_t
	{
		g2_color_t 	c;
		tb_uint32_t p;

	}p2c;
	p2c.p = pixel;
	return p2c.c;
}

/* ////////////////////////////////////////////////////////////////////////
 * interfaces
 */

// name => color
g2_named_color_t const* g2_color_from_name(tb_char_t const* name);

// index => color
g2_named_color_t const* g2_color_from_index(tb_size_t index);

// c plus plus
#ifdef __cplusplus
}
#endif


#endif


