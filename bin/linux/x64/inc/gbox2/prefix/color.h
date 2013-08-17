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

// init color from argb
#ifdef TB_WORDS_BIGENDIAN
# 	define G2_COLOR_INIT_ARGB(a, r, g, b) 		{ a, r, g, b }
#else
# 	define G2_COLOR_INIT_ARGB(a, r, g, b) 		{ b, g, r, a }
#endif

// init color from name & argb
#define G2_COLOR_INIT_NAME(name, a, r, g, b) 	{name, G2_COLOR_INIT_ARGB(a, r, g, b)}

// init color contants
#define G2_COLOR_INIT_BLACK 			G2_COLOR_INIT_NAME( "black", 		0xff, 	0x00, 	0x00, 	0x00 	)
#define G2_COLOR_INIT_BLUE 				G2_COLOR_INIT_NAME( "blue", 		0xff, 	0x00, 	0x00, 	0xff 	)
#define G2_COLOR_INIT_BROWN 			G2_COLOR_INIT_NAME( "brown", 		0xff, 	0x80, 	0x00, 	0x00 	)
#define G2_COLOR_INIT_DARKBLUE 			G2_COLOR_INIT_NAME( "darkblue", 	0xff, 	0x00, 	0x00, 	0x8b 	)
#define G2_COLOR_INIT_GOLD 				G2_COLOR_INIT_NAME( "gold", 		0xff, 	0xff, 	0xd7, 	0x00 	)
#define G2_COLOR_INIT_GRAY 				G2_COLOR_INIT_NAME( "gray", 		0xff, 	0x80, 	0x80, 	0x80 	)
#define G2_COLOR_INIT_GREY 				G2_COLOR_INIT_NAME( "grey", 		0xff, 	0x80, 	0x80, 	0x80 	)
#define G2_COLOR_INIT_GREEN 			G2_COLOR_INIT_NAME( "green", 		0xff, 	0x00, 	0xff, 	0x00 	)
#define G2_COLOR_INIT_LIGHTBLUE 		G2_COLOR_INIT_NAME( "lightblue", 	0xff, 	0xad, 	0xd8, 	0xa6 	)
#define G2_COLOR_INIT_LIGHTGRAY 		G2_COLOR_INIT_NAME( "lightgray", 	0xff, 	0xd3, 	0xd3, 	0xd3 	)
#define G2_COLOR_INIT_LIGHTGREY 		G2_COLOR_INIT_NAME( "lightgrey", 	0xff, 	0xd3, 	0xd3, 	0xd3 	)
#define G2_COLOR_INIT_LIGHTPINK 		G2_COLOR_INIT_NAME( "lightpink", 	0xff, 	0xff, 	0xb6, 	0xc1 	)
#define G2_COLOR_INIT_LIGHTYELLOW 		G2_COLOR_INIT_NAME( "lightyellow", 	0xff, 	0xff, 	0xff, 	0xe0 	)
#define G2_COLOR_INIT_NAVY 				G2_COLOR_INIT_NAME( "navy", 		0xff, 	0x00, 	0x00, 	0x80 	)
#define G2_COLOR_INIT_ORANGE 			G2_COLOR_INIT_NAME( "orange", 		0xff, 	0xff, 	0xa5, 	0x00 	)
#define G2_COLOR_INIT_PINK 				G2_COLOR_INIT_NAME( "pink", 		0xff, 	0xff, 	0x00, 	0xff 	)
#define G2_COLOR_INIT_PURPLE 			G2_COLOR_INIT_NAME( "purple", 		0xff, 	0x80, 	0x00, 	0x80 	)
#define G2_COLOR_INIT_RED 				G2_COLOR_INIT_NAME( "red", 			0xff, 	0xff, 	0x00, 	0x00 	)
#define G2_COLOR_INIT_SNOW 				G2_COLOR_INIT_NAME( "snow", 		0xff, 	0xff, 	0xfa, 	0xfa 	)
#define G2_COLOR_INIT_TOMATO 			G2_COLOR_INIT_NAME( "tomato", 		0xff, 	0xff, 	0x63, 	0x47 	)
#define G2_COLOR_INIT_YELLOW 			G2_COLOR_INIT_NAME( "yellow", 		0xff, 	0xff, 	0xff, 	0x00 	)
#define G2_COLOR_INIT_WHEAT 			G2_COLOR_INIT_NAME( "wheat", 		0xff, 	0xf5, 	0xde, 	0xb3 	)
#define G2_COLOR_INIT_WHITE 			G2_COLOR_INIT_NAME( "white", 		0xff, 	0xff, 	0xff, 	0xff 	)

// the color contants
#define G2_COLOR_BLACK 					(g2_color_from_index(0)->color)
#define G2_COLOR_BLUE 					(g2_color_from_index(1)->color)
#define G2_COLOR_BROWN 					(g2_color_from_index(2)->color)
#define G2_COLOR_DARKBLUE 				(g2_color_from_index(3)->color)
#define G2_COLOR_GOLD 					(g2_color_from_index(4)->color)
#define G2_COLOR_GRAY 					(g2_color_from_index(5)->color)
#define G2_COLOR_GREEN 					(g2_color_from_index(6)->color)
#define G2_COLOR_GREY 					(g2_color_from_index(7)->color)
#define G2_COLOR_LIGHTBLUE 				(g2_color_from_index(8)->color)
#define G2_COLOR_LIGHTGRAY 				(g2_color_from_index(9)->color)
#define G2_COLOR_LIGHTGREY 				(g2_color_from_index(10)->color)
#define G2_COLOR_LIGHTPINK 				(g2_color_from_index(11)->color)
#define G2_COLOR_LIGHTYELLOW 			(g2_color_from_index(12)->color)
#define G2_COLOR_NAVY					(g2_color_from_index(13)->color)
#define G2_COLOR_ORANGE 				(g2_color_from_index(14)->color)
#define G2_COLOR_PINK 					(g2_color_from_index(15)->color)
#define G2_COLOR_PURPLE 				(g2_color_from_index(16)->color)
#define G2_COLOR_RED 					(g2_color_from_index(17)->color)
#define G2_COLOR_SNOW 					(g2_color_from_index(18)->color)
#define G2_COLOR_TOMATO 				(g2_color_from_index(19)->color)
#define G2_COLOR_YELLOW 				(g2_color_from_index(20)->color)
#define G2_COLOR_WHEAT 					(g2_color_from_index(21)->color)
#define G2_COLOR_WHITE 					(g2_color_from_index(22)->color)
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


