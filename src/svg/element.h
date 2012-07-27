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
 * @file		element.h
 *
 */
#ifndef G2_SVG_ELEMENT_H
#define G2_SVG_ELEMENT_H

/* ///////////////////////////////////////////////////////////////////////
 * includes
 */
#include "prefix.h"

/* ///////////////////////////////////////////////////////////////////////
 * types
 */

/// the element type
typedef enum __g2_svg_element_type_t
{
	G2_SVG_ELEMENT_TYPE_NONE
,	G2_SVG_ELEMENT_TYPE_A
,	G2_SVG_ELEMENT_TYPE_ANIMATE
,	G2_SVG_ELEMENT_TYPE_ANIMATECOLOR
,	G2_SVG_ELEMENT_TYPE_ANIMATEMOTION
,	G2_SVG_ELEMENT_TYPE_ANIMATETRANSFORM
,	G2_SVG_ELEMENT_TYPE_CIRCLE
,	G2_SVG_ELEMENT_TYPE_CLIPPATH
,	G2_SVG_ELEMENT_TYPE_CURSOR
,	G2_SVG_ELEMENT_TYPE_DEFS
,	G2_SVG_ELEMENT_TYPE_DESC
,	G2_SVG_ELEMENT_TYPE_ELLIPSE
,	G2_SVG_ELEMENT_TYPE_FEBLEND
,	G2_SVG_ELEMENT_TYPE_FECOLORMATRIX
,	G2_SVG_ELEMENT_TYPE_FECOMPONENTTRANSFER
,	G2_SVG_ELEMENT_TYPE_FECOMPOSITE
,	G2_SVG_ELEMENT_TYPE_FECONVOLVEMATRIX
,	G2_SVG_ELEMENT_TYPE_FEDIFFUSELIGHTING
,	G2_SVG_ELEMENT_TYPE_FEDISPLACEMENTMAP
,	G2_SVG_ELEMENT_TYPE_FEFLOOD
,	G2_SVG_ELEMENT_TYPE_FEGAUSSIANBLUR
,	G2_SVG_ELEMENT_TYPE_FEIMAGE
,	G2_SVG_ELEMENT_TYPE_FEMERGE
,	G2_SVG_ELEMENT_TYPE_FEMERGENODE
,	G2_SVG_ELEMENT_TYPE_FEMORPHOLOGY
,	G2_SVG_ELEMENT_TYPE_FEOFFSET
,	G2_SVG_ELEMENT_TYPE_FESPECULARLIGHTING
,	G2_SVG_ELEMENT_TYPE_FETILE
,	G2_SVG_ELEMENT_TYPE_FETURBULENCE
,	G2_SVG_ELEMENT_TYPE_FILTER
,	G2_SVG_ELEMENT_TYPE_FONT
,	G2_SVG_ELEMENT_TYPE_FONTFACE
,	G2_SVG_ELEMENT_TYPE_FONTFACEFORMAT
,	G2_SVG_ELEMENT_TYPE_FONTFACENAME
,	G2_SVG_ELEMENT_TYPE_FONTFACESRC
,	G2_SVG_ELEMENT_TYPE_FONTFACEURI
,	G2_SVG_ELEMENT_TYPE_FOREIGNOBJECT
,	G2_SVG_ELEMENT_TYPE_G
,	G2_SVG_ELEMENT_TYPE_GLYPH
,	G2_SVG_ELEMENT_TYPE_HKERN
,	G2_SVG_ELEMENT_TYPE_IMAGE
,	G2_SVG_ELEMENT_TYPE_LINE
,	G2_SVG_ELEMENT_TYPE_LINEARGRADIENT
,	G2_SVG_ELEMENT_TYPE_MASK
,	G2_SVG_ELEMENT_TYPE_METADATA
,	G2_SVG_ELEMENT_TYPE_MISSINGGLYPH
,	G2_SVG_ELEMENT_TYPE_OPERATORSCRIPT
,	G2_SVG_ELEMENT_TYPE_PARAGRAPH
,	G2_SVG_ELEMENT_TYPE_PATH
,	G2_SVG_ELEMENT_TYPE_PATTERN
,	G2_SVG_ELEMENT_TYPE_POLYGON
,	G2_SVG_ELEMENT_TYPE_POLYLINE
,	G2_SVG_ELEMENT_TYPE_RADIALGRADIENT
,	G2_SVG_ELEMENT_TYPE_RECT
,	G2_SVG_ELEMENT_TYPE_SCRIPT
,	G2_SVG_ELEMENT_TYPE_STOP
,	G2_SVG_ELEMENT_TYPE_SVG
,	G2_SVG_ELEMENT_TYPE_SVGTESTCASE
,	G2_SVG_ELEMENT_TYPE_SWITCH
,	G2_SVG_ELEMENT_TYPE_SYMBOL
,	G2_SVG_ELEMENT_TYPE_TEXT
,	G2_SVG_ELEMENT_TYPE_TEXTPATH
,	G2_SVG_ELEMENT_TYPE_TITLE
,	G2_SVG_ELEMENT_TYPE_TSPAN
,	G2_SVG_ELEMENT_TYPE_USE
,	G2_SVG_ELEMENT_TYPE_VIDEO
,	G2_SVG_ELEMENT_TYPE_VIEW
,	G2_SVG_ELEMENT_TYPE_VKERN

}g2_svg_element_type_t;

/// the svg element type
typedef struct __g2_svg_element_t
{
	// the element type
	tb_size_t 					type;

	// the next
	struct __g2_svg_element_t* 	next;

	// the childs
	struct __g2_svg_element_t* 	head;
	struct __g2_svg_element_t* 	tail;

	// the parent
	struct __g2_svg_element_t* 	parent;

	// dump
#ifdef G2_DEBUG
	tb_void_t 					(*dump)(struct __g2_svg_element_t const* element, tb_pstring_t* attr);
#endif

	// exit it
	tb_void_t 					(*exit)(struct __g2_svg_element_t* element);

}g2_svg_element_t;

/// the svg element type for <svg ...>
typedef struct __g2_svg_element_svg_t
{
	// the base
	g2_svg_element_t 			base;

	// the x
	g2_float_t 					x;

	// the y
	g2_float_t 					y;

	// the width
	g2_float_t 					width;

	// the height
	g2_float_t 					height;

	// the viewbox
	g2_rect_t 					viewbox;

}g2_svg_element_svg_t;

/// the svg element type for <path ...>
typedef struct __g2_svg_element_path_t
{
	// the base
	g2_svg_element_t 			base;

	// the path
	tb_handle_t 				path;

}g2_svg_element_path_t;

/// the svg element type for <rect ...>
typedef struct __g2_svg_element_rect_t
{
	// the base
	g2_svg_element_t 			base;

	// the rect
	g2_rect_t 					rect;

}g2_svg_element_rect_t;

/// the svg element type for <line ...>
typedef struct __g2_svg_element_line_t
{
	// the base
	g2_svg_element_t 			base;

	// the line
	g2_line_t 					line;

}g2_svg_element_line_t;

/// the svg element type for <circle ...>
typedef struct __g2_svg_element_circle_t
{
	// the base
	g2_svg_element_t 			base;

	// the circle
	g2_circle_t 				circle;

}g2_svg_element_circle_t;

/// the svg element type for <ellipse ...>
typedef struct __g2_svg_element_ellipse_t
{
	// the base
	g2_svg_element_t 			base;

	// the ellipse
	g2_ellipse_t 				ellipse;

}g2_svg_element_ellipse_t;

/* ///////////////////////////////////////////////////////////////////////
 * interfaces
 */

/// init element
g2_svg_element_t* 	g2_svg_element_init(tb_handle_t reader);

/// init element: none tag
g2_svg_element_t* 	g2_svg_element_init_none(tb_handle_t reader);

/// init element: <svg ...>
g2_svg_element_t* 	g2_svg_element_init_svg(tb_handle_t reader);

/// init element: <path ...>
g2_svg_element_t* 	g2_svg_element_init_path(tb_handle_t reader);

/// init element: <rect ...>
g2_svg_element_t* 	g2_svg_element_init_rect(tb_handle_t reader);

/// init element: <line ...>
g2_svg_element_t* 	g2_svg_element_init_line(tb_handle_t reader);

/// init element: <circle ...>
g2_svg_element_t* 	g2_svg_element_init_circle(tb_handle_t reader);

/// init element: <ellipse ...>
g2_svg_element_t* 	g2_svg_element_init_ellipse(tb_handle_t reader);

/// exit element
tb_void_t 			g2_svg_element_exit(g2_svg_element_t* element);

/// dump element
tb_void_t 			g2_svg_element_dump(g2_svg_element_t* element);

/// insert the next element
tb_void_t 			g2_svg_element_insert_next(g2_svg_element_t* element, g2_svg_element_t* next);

/// remove the next element
tb_void_t 			g2_svg_element_remove_next(g2_svg_element_t* element);

/// append the element to the head
tb_void_t 			g2_svg_element_append_head(g2_svg_element_t* element, g2_svg_element_t* child);

/// append the element to the tail
tb_void_t 			g2_svg_element_append_tail(g2_svg_element_t* element, g2_svg_element_t* child);

#endif


