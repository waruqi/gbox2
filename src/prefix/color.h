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

/* ///////////////////////////////////////////////////////////////////////
 * includes
 */
#include "config.h"

/* ///////////////////////////////////////////////////////////////////////
 * macros
 */

// the color constants
#define G2_DEFINE_COLOR_CONST(color, r, g, b, a) static g2_color_t const g_g2_default_color_##color = {r, g, b, a};
#define G2_COLOR_BLACK 				g_g2_default_color_black
#define G2_COLOR_WHITE 				g_g2_default_color_white
#define G2_COLOR_RED				g_g2_default_color_red
#define G2_COLOR_GREEN 				g_g2_default_color_green
#define G2_COLOR_YELLOW 			g_g2_default_color_yellow
#define G2_COLOR_BLUE				g_g2_default_color_blue
#define G2_COLOR_PINK				g_g2_default_color_pink
#define G2_COLOR_BROWN 				g_g2_default_color_brown
#define G2_COLOR_ORANGE 			g_g2_default_color_orange
#define G2_COLOR_TRANSPARENT 		g_g2_default_color_transparent
#define G2_COLOR_DEFAULT 			G2_COLOR_BLACK

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

/* ////////////////////////////////////////////////////////////////////////
 * globals
 */

#ifdef TB_WORDS_BIGENDIAN
// define color constants: (a, r, g, b)
G2_DEFINE_COLOR_CONST(black, 		255, 	0, 		0, 		0)
G2_DEFINE_COLOR_CONST(white, 		255, 	255, 	255, 	255)
G2_DEFINE_COLOR_CONST(red, 			255, 	255, 	0, 		0)
G2_DEFINE_COLOR_CONST(green, 		255, 	0, 		255, 	0)
G2_DEFINE_COLOR_CONST(blue, 		255, 	0, 		0, 		255)
G2_DEFINE_COLOR_CONST(yellow, 		255, 	255, 	255, 	0)
G2_DEFINE_COLOR_CONST(pink, 		255, 	255, 	0, 		255)
G2_DEFINE_COLOR_CONST(brown, 		255, 	128, 	0, 		0)
G2_DEFINE_COLOR_CONST(orange, 		255, 	255, 	128, 	0)
G2_DEFINE_COLOR_CONST(transparent, 	0, 		0, 		0, 		0)
#else
// define color constants: (b, g, r, a)
G2_DEFINE_COLOR_CONST(black, 		0, 		0, 		0, 		255)
G2_DEFINE_COLOR_CONST(white, 		255, 	255, 	255, 	255)
G2_DEFINE_COLOR_CONST(red, 			0, 		0, 		255, 	255)
G2_DEFINE_COLOR_CONST(green, 		0, 		255, 	0, 		255)
G2_DEFINE_COLOR_CONST(blue, 		255, 	0, 		0, 		255)
G2_DEFINE_COLOR_CONST(yellow, 		0, 		255, 	255, 	255)
G2_DEFINE_COLOR_CONST(pink, 		255, 	0, 		255, 	255)
G2_DEFINE_COLOR_CONST(brown, 		0, 		0, 		128, 	255)
G2_DEFINE_COLOR_CONST(orange, 		0, 		128, 	255, 	255)
G2_DEFINE_COLOR_CONST(transparent, 	0, 		0, 		0, 		0)
#endif


#endif


