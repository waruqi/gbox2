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
#ifndef G2_SVG_STYLE_H
#define G2_SVG_STYLE_H

/* ///////////////////////////////////////////////////////////////////////
 * includes
 */
#include "prefix.h"

/* ///////////////////////////////////////////////////////////////////////
 * types
 */

// the svg style mode type
typedef enum __g2_svg_style_mode_t
{
	G2_SVG_STYLE_MODE_NONE 			= 0 	//!< none
,	G2_SVG_STYLE_MODE_FILL 			= 1 	//!< fill
,	G2_SVG_STYLE_MODE_STROKE 		= 2 	//!< stroke
,	G2_SVG_STYLE_MODE_FILL_STROKE 	= 3 	//!< fill & stroke

}g2_svg_style_mode_t;

// the svg style paint type
typedef enum __g2_svg_style_paint_mode_t
{
	G2_SVG_STYLE_PAINT_MODE_INHERIT = 0 	//!< inherit
,	G2_SVG_STYLE_PAINT_MODE_NONE 	= 1 	//!< none
,	G2_SVG_STYLE_PAINT_MODE_VALUE 	= 2 	//!< value

}g2_svg_style_paint_mode_t;

// the svg style cap type
typedef enum __g2_svg_style_cap_t
{
	G2_SVG_STYLE_CAP_INHERIT 		= 0 	//!< inherit
,	G2_SVG_STYLE_CAP_BUTT 			= 1 	//!< no extension
,	G2_SVG_STYLE_CAP_ROUND 			= 2 	//!< a semi-circle extension
,	G2_SVG_STYLE_CAP_SQUARE			= 3 	//!< a half square extension

}g2_svg_style_cap_t;

// the svg style join type
typedef enum __g2_svg_style_join_t
{
	G2_SVG_STYLE_JOIN_INHERIT 		= 0 	//!< inherit
,	G2_SVG_STYLE_JOIN_MITER 		= 1 	//!< a sharp join
,	G2_SVG_STYLE_JOIN_ROUND 		= 2 	//!< a round join
,	G2_SVG_STYLE_JOIN_BEVEL			= 3 	//!< a flat bevel join

}g2_svg_style_join_t;

// the svg style paint type
typedef struct __g2_svg_style_paint_t
{
	// the paint mode
	tb_size_t 					mode;

	// the paint color
	g2_color_t 					color;

}g2_svg_style_paint_t;

// the svg style type
typedef struct __g2_svg_style_t
{
	// the style mode
	tb_byte_t 					mode 		: 2;

	// the stroke join
	tb_byte_t 					join 		: 2;

	// the stroke cap
	tb_byte_t 					cap 		: 2;

	// the stroke width
	g2_float_t 					width;

	// the fill paint
	g2_svg_style_paint_t 		fill;

	// the stroke color
	g2_svg_style_paint_t 		stroke;

}g2_svg_style_t;

/* ///////////////////////////////////////////////////////////////////////
 * interfaces
 */

// init & exit
tb_bool_t 		g2_svg_style_init(g2_svg_style_t* style);
tb_void_t 		g2_svg_style_exit(g2_svg_style_t* style);

#endif


