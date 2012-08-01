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
	G2_SVG_STYLE_MODE_NONE 					= 0 	//!< none
,	G2_SVG_STYLE_MODE_FILL 					= 1 	//!< fill
,	G2_SVG_STYLE_MODE_STROKE 				= 2 	//!< stroke
,	G2_SVG_STYLE_MODE_CLIPPATH 				= 4 	//!< clippath
,	G2_SVG_STYLE_MODE_FONT 					= 8 	//!< font
,	G2_SVG_STYLE_MODE_TEXT 					= 16 	//!< text

}g2_svg_style_mode_t;

// the svg style cap type
typedef enum __g2_svg_style_cap_t
{
	G2_SVG_STYLE_CAP_INHERIT 				= 0 	//!< inherit
,	G2_SVG_STYLE_CAP_BUTT 					= 1 	//!< no extension
,	G2_SVG_STYLE_CAP_ROUND 					= 2 	//!< a semi-circle extension
,	G2_SVG_STYLE_CAP_SQUARE					= 3 	//!< a half square extension

}g2_svg_style_cap_t;

// the svg style join type
typedef enum __g2_svg_style_join_t
{
	G2_SVG_STYLE_JOIN_INHERIT 				= 0 	//!< inherit
,	G2_SVG_STYLE_JOIN_MITER 				= 1 	//!< a sharp join
,	G2_SVG_STYLE_JOIN_ROUND 				= 2 	//!< a round join
,	G2_SVG_STYLE_JOIN_BEVEL					= 3 	//!< a flat bevel join

}g2_svg_style_join_t;

// the svg style gradient spread type
typedef enum __g2_svg_style_gradient_spread_t
{
	G2_SVG_STYLE_GRADIENT_SPREAD_NONE 		= 0 	//!< none
,	G2_SVG_STYLE_GRADIENT_SPREAD_PAD 		= 1 	//!< spread pad
,	G2_SVG_STYLE_GRADIENT_SPREAD_REFLECT 	= 2 	//!< spread reflect
,	G2_SVG_STYLE_GRADIENT_SPREAD_REPEAT		= 3 	//!< spread repeat

}g2_svg_style_gradient_spread_t;

// the svg style units type
typedef enum __g2_svg_style_units_t
{
	G2_SVG_STYLE_UNITS_NONE 				= 0 	//!< none
,	G2_SVG_STYLE_UNITS_USER 				= 1 	//!< user space on use
,	G2_SVG_STYLE_UNITS_OBJB 				= 2 	//!< object bounding box

}g2_svg_style_units_t;

// the svg style paint mode type
typedef enum __g2_svg_style_paint_mode_t
{
	G2_SVG_STYLE_PAINT_MODE_INHERIT 		= 0 	//!< inherit
,	G2_SVG_STYLE_PAINT_MODE_NONE 			= 1 	//!< none
,	G2_SVG_STYLE_PAINT_MODE_VALUE 			= 2 	//!< value
,	G2_SVG_STYLE_PAINT_MODE_URL 			= 3 	//!< url

}g2_svg_style_paint_mode_t;

// the svg style paint flag type
typedef enum __g2_svg_style_paint_flag_t
{
	G2_SVG_STYLE_PAINT_FLAG_NONE 			= 0 	//!< inherit
,	G2_SVG_STYLE_PAINT_FLAG_HAS_OPACITY 	= 1 	//!< opacity

}g2_svg_style_paint_flag_t;

// the svg style paint type
typedef struct __g2_svg_style_paint_t
{
	// the paint mode
	tb_size_t 					mode;

	// the paint flag
	tb_size_t 					flag;

	// the paint opacity
	g2_float_t 					opacity;

	// the paint color
	g2_color_t 					color;

	// the url
	tb_pstring_t 				url;

}g2_svg_style_paint_t;

// the svg style clippath mode type
typedef enum __g2_svg_style_clippath_mode_t
{
	G2_SVG_STYLE_CLIPPATH_MODE_INHERIT 		= 0 	//!< inherit
,	G2_SVG_STYLE_CLIPPATH_MODE_NONE 		= 1 	//!< none
,	G2_SVG_STYLE_CLIPPATH_MODE_URL 			= 2 	//!< url

}g2_svg_style_clippatht_mode_t;

// the svg style clippath type
typedef struct __g2_svg_style_clippath_t
{
	// the clippath mode
	tb_size_t 					mode;

	// the url
	tb_pstring_t 				url;

}g2_svg_style_clippath_t;

// the svg style font weight type
typedef enum __g2_svg_style_font_weight_t
{
	G2_SVG_STYLE_FONT_WEIGHT_INHERIT 		= 0 	//!< inherit
,	G2_SVG_STYLE_FONT_WEIGHT_NORMAL 		= 1 	//!< normal
,	G2_SVG_STYLE_FONT_WEIGHT_BORD 			= 2 	//!< bord
,	G2_SVG_STYLE_FONT_WEIGHT_BOLDER 		= 3 	//!< bolder
,	G2_SVG_STYLE_FONT_WEIGHT_LIGHTER 		= 4 	//!< lighter
,	G2_SVG_STYLE_FONT_WEIGHT_100 			= 100 	//!< 100
,	G2_SVG_STYLE_FONT_WEIGHT_200 			= 200 	//!< 200
,	G2_SVG_STYLE_FONT_WEIGHT_300 			= 300 	//!< 300
,	G2_SVG_STYLE_FONT_WEIGHT_400 			= 400 	//!< 400
,	G2_SVG_STYLE_FONT_WEIGHT_500 			= 500 	//!< 500
,	G2_SVG_STYLE_FONT_WEIGHT_600 			= 600 	//!< 600
,	G2_SVG_STYLE_FONT_WEIGHT_700 			= 700 	//!< 700
,	G2_SVG_STYLE_FONT_WEIGHT_800 			= 800 	//!< 800
,	G2_SVG_STYLE_FONT_WEIGHT_900 			= 900 	//!< 900

}g2_svg_style_font_weight_t;

// the svg style font style type
typedef enum __g2_svg_style_font_style_t
{
	G2_SVG_STYLE_FONT_STYLE_INHERIT 		= 0 	//!< inherit
,	G2_SVG_STYLE_FONT_STYLE_NORMAL 			= 1 	//!< normal
,	G2_SVG_STYLE_FONT_STYLE_ITALIC 			= 2 	//!< italic
,	G2_SVG_STYLE_FONT_STYLE_OBLIQUE 		= 3 	//!< oblique

}g2_svg_style_font_style_t;

// the svg style font type
typedef struct __g2_svg_style_font_t
{
	// the font style
	tb_size_t 					style 		: 16;

	// the font weight
	tb_size_t 					weight 		: 16;

	// the font size
	g2_float_t 					size;

	// the font family
	tb_pstring_t 				family;

}g2_svg_style_font_t;

// the svg style text anchor type
typedef enum __g2_svg_style_text_anchor_t
{
	G2_SVG_STYLE_TEXT_ANCHOR_INHERIT 		= 0 	//!< inherit
,	G2_SVG_STYLE_TEXT_ANCHOR_START 			= 1 	//!< start
,	G2_SVG_STYLE_TEXT_ANCHOR_MIDDLE 		= 2 	//!< middle
,	G2_SVG_STYLE_TEXT_ANCHOR_END 			= 3 	//!< end

}g2_svg_style_text_anchor_t;

// the svg style text type
typedef struct __g2_svg_style_text_t
{
	// the text align
	tb_size_t 					align;

	// the text anchor
	tb_size_t 					anchor;

}g2_svg_style_text_t;

// the svg style type
typedef struct __g2_svg_style_t
{
	// the style mode
	tb_size_t 					mode 		: 28;

	// the stroke join
	tb_size_t 					join 		: 2;

	// the stroke cap
	tb_size_t 					cap 		: 2;

	// the stroke width
	g2_float_t 					width;

	// the fill paint
	g2_svg_style_paint_t 		fill;

	// the stroke paint
	g2_svg_style_paint_t 		stroke;

	// the clip path
	g2_svg_style_clippath_t 	clippath;

	// the font
	g2_svg_style_font_t 		font;

	// the text
	g2_svg_style_text_t 		text;

}g2_svg_style_t;

/* ///////////////////////////////////////////////////////////////////////
 * interfaces
 */

// init & exit
tb_bool_t 		g2_svg_style_init(g2_svg_style_t* style);
tb_void_t 		g2_svg_style_exit(g2_svg_style_t* style);

#endif


