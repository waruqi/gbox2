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
 * @file		style.h
 *
 */
#ifndef G2_CORE_STYLE_H
#define G2_CORE_STYLE_H

// c plus plus
#ifdef __cplusplus
extern "C" {
#endif

/* ///////////////////////////////////////////////////////////////////////
 * includes
 */
#include "prefix.h"

/* ///////////////////////////////////////////////////////////////////////
 * types
 */

// the style mode type
typedef enum __g2_style_mode_t
{
	G2_STYLE_MODE_NONE 			= 0 //!< none
,	G2_STYLE_MODE_FILL 			= 1 //!< fill
,	G2_STYLE_MODE_STOK 			= 2 //!< stok
,	G2_STYLE_MODE_FILL_STOK 	= 3 //!< fill & stok

}g2_style_mode_t;

// the style flag type
typedef enum __g2_style_flag_t
{
	G2_STYLE_FLAG_NONE 			= 0 //!< none
,	G2_STYLE_FLAG_ANTI_ALIAS 	= 1 //!< antialiasing
,	G2_STYLE_FLAG_BITMAP_FILTER = 2 //!< bitmap filter

}g2_style_flag_t;

// the style cap type
typedef enum __g2_style_cap_t
{
	G2_STYLE_CAP_NONE 			= 0 //!< none
,	G2_STYLE_CAP_BUTT 			= 1 //!< no extension
,	G2_STYLE_CAP_ROUND 			= 2 //!< a semi-circle extension
,	G2_STYLE_CAP_SQUARE			= 3 //!< a half square extension

}g2_style_cap_t;

// the style join type
typedef enum __g2_style_join_t
{
	G2_STYLE_JOIN_NONE 			= 0 //!< none
,	G2_STYLE_JOIN_MITER 		= 1 //!< a sharp join
,	G2_STYLE_JOIN_ROUND 		= 2 //!< a round join
,	G2_STYLE_JOIN_BEVEL			= 3 //!< a flat bevel join

}g2_style_join_t;

// the style type
typedef struct __g2_style_t
{
	// the style mode
	tb_size_t 			mode 	: 4;

	// the style flag
	tb_size_t 			flag 	: 4;

	// the pen join
	tb_size_t 			join 	: 4;

	// the pen cap
	tb_size_t 			cap 	: 4;

	// the style color
	g2_color_t 			color;

	// the pen width
	g2_float_t 			width;

	// the shader
	tb_handle_t 		shader;

}g2_style_t;

/* ///////////////////////////////////////////////////////////////////////
 * interfaces
 */

// init & exit
tb_handle_t 	g2_style_init();
tb_void_t 		g2_style_exit(tb_handle_t style);

// clear
tb_void_t 		g2_style_clear(tb_handle_t style);

// copy
tb_void_t 		g2_style_copy(tb_handle_t style, tb_handle_t copy);

// mode
tb_size_t 		g2_style_mode(tb_handle_t style);
tb_void_t 		g2_style_mode_set(tb_handle_t style, tb_size_t mode);

// flag
tb_size_t 		g2_style_flag(tb_handle_t style);
tb_void_t 		g2_style_flag_set(tb_handle_t style, tb_size_t flag);

// color
g2_color_t 		g2_style_color(tb_handle_t style);
tb_void_t 		g2_style_color_set(tb_handle_t style, g2_color_t color);

// alpha
tb_byte_t 		g2_style_alpha(tb_handle_t style);
tb_void_t 		g2_style_alpha_set(tb_handle_t style, tb_byte_t alpha);

// width
g2_float_t 		g2_style_width(tb_handle_t style);
tb_void_t 		g2_style_width_set(tb_handle_t style, g2_float_t width);

// cap
tb_size_t 		g2_style_cap(tb_handle_t style);
tb_void_t 		g2_style_cap_set(tb_handle_t style, tb_size_t cap);

// join
tb_size_t 		g2_style_join(tb_handle_t style);
tb_void_t 		g2_style_join_set(tb_handle_t style, tb_size_t join);

// shader
tb_handle_t 	g2_style_shader(tb_handle_t style);
tb_void_t 		g2_style_shader_set(tb_handle_t style, tb_handle_t shader);

// c plus plus
#ifdef __cplusplus
}
#endif

#endif
