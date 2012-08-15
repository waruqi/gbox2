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
#include "style.h"

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

	// data ...
,	G2_SVG_ELEMENT_TYPE_DATA

}g2_svg_element_type_t;

// the svg painter type
typedef struct __g2_svg_painter_t
{
	// the painter
	tb_handle_t 				painter;

	// the pool
	tb_handle_t 				pool;

	// the hash
	tb_hash_t* 					hash;

	// is loaded?
	tb_bool_t 					load;

}g2_svg_painter_t;

/// the svg element type
typedef struct __g2_svg_element_t
{
	// the element type
	tb_size_t 					type;

	// the element id
	tb_pstring_t 				id;

	// the next
	struct __g2_svg_element_t* 	next;

	// the childs
	struct __g2_svg_element_t* 	head;
	struct __g2_svg_element_t* 	tail;

	// the parent
	struct __g2_svg_element_t* 	parent;

	// the style
	g2_svg_style_t const* 		style;

	// the transform
	g2_matrix_t const* 			transform;

	// writ it
	tb_void_t 					(*writ)(struct __g2_svg_element_t const* element, tb_gstream_t* gst);

	// fill it
	tb_void_t 					(*fill)(struct __g2_svg_element_t const* element, g2_svg_painter_t* painter);

	// stok it
	tb_void_t 					(*stok)(struct __g2_svg_element_t const* element, g2_svg_painter_t* painter);

	// exit it
	tb_void_t 					(*exit)(struct __g2_svg_element_t* element);

}g2_svg_element_t;

/// the svg element type for <g ...>
typedef struct __g2_svg_element_g_t
{
	// the base
	g2_svg_element_t 			base;

	// the style
	g2_svg_style_t 				style;

	// the transform
	g2_matrix_t 				transform;

}g2_svg_element_g_t;

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
	
	// the painter
	g2_svg_painter_t 			painter;

}g2_svg_element_svg_t;

/// the svg element type for <use ...>
typedef struct __g2_svg_element_use_t
{
	// the base
	g2_svg_element_t 			base;

	// the xlink-href
	tb_pstring_t 				href;

	// the style
	g2_svg_style_t 				style;

	// the transform
	g2_matrix_t 				transform;

	// the rect
	g2_rect_t 					rect;

}g2_svg_element_use_t;

/// the svg element type for <>data</> or cdata
typedef struct __g2_svg_element_data_t
{
	// the base
	g2_svg_element_t 			base;

	// the data
	tb_pstring_t 				data;

}g2_svg_element_data_t;

/// the svg element type for <path ...>
typedef struct __g2_svg_element_path_t
{
	// the base
	g2_svg_element_t 			base;

	// the style
	g2_svg_style_t 				style;

	// the transform
	g2_matrix_t 				transform;

	// the path
	tb_handle_t 				path;

}g2_svg_element_path_t;

/// the svg element type for <rect ...>
typedef struct __g2_svg_element_rect_t
{
	// the base
	g2_svg_element_t 			base;

	// the style
	g2_svg_style_t 				style;

	// the transform
	g2_matrix_t 				transform;

	// the rect
	g2_rect_t 					rect;

}g2_svg_element_rect_t;

/// the svg element type for <line ...>
typedef struct __g2_svg_element_line_t
{
	// the base
	g2_svg_element_t 			base;

	// the style
	g2_svg_style_t 				style;

	// the transform
	g2_matrix_t 				transform;

	// the line
	g2_line_t 					line;

}g2_svg_element_line_t;

/// the svg element type for <text ...>
typedef struct __g2_svg_element_text_t
{
	// the base
	g2_svg_element_t 			base;

	// the style
	g2_svg_style_t 				style;

	// the transform
	g2_matrix_t 				transform;

	// the rect
	g2_rect_t 					rect;

	// the text
	tb_pstring_t 				text;

}g2_svg_element_text_t;

/// the svg element type for <image ...>
typedef struct __g2_svg_element_image_t
{
	// the base
	g2_svg_element_t 			base;

	// the href
	tb_pstring_t 				href;

	// the style
	g2_svg_style_t 				style;

	// the transform
	g2_matrix_t 				transform;

	// the rect
	g2_rect_t 					rect;

}g2_svg_element_image_t;

/// the svg element type for <circle ...>
typedef struct __g2_svg_element_circle_t
{
	// the base
	g2_svg_element_t 			base;

	// the style
	g2_svg_style_t 				style;

	// the transform
	g2_matrix_t 				transform;

	// the circle
	g2_circle_t 				circle;

}g2_svg_element_circle_t;

/// the svg element type for <ellipse ...>
typedef struct __g2_svg_element_ellipse_t
{
	// the base
	g2_svg_element_t 			base;

	// the style
	g2_svg_style_t 				style;

	// the transform
	g2_matrix_t 				transform;

	// the ellipse
	g2_ellipse_t 				ellipse;

}g2_svg_element_ellipse_t;

/// the svg element type for <polygon ...>
typedef struct __g2_svg_element_polygon_t
{
	// the base
	g2_svg_element_t 			base;

	// the style
	g2_svg_style_t 				style;

	// the transform
	g2_matrix_t 				transform;

	// the path
	tb_handle_t 				path;

}g2_svg_element_polygon_t;

/// the svg element type for <polyline ...>
typedef struct __g2_svg_element_polyline_t
{
	// the base
	g2_svg_element_t 			base;

	// the style
	g2_svg_style_t 				style;

	// the transform
	g2_matrix_t 				transform;

	// the path
	tb_handle_t 				path;

}g2_svg_element_polyline_t;

/// the svg element type for <clipPath ...>
typedef struct __g2_svg_element_clippath_t
{
	// the base
	g2_svg_element_t 			base;

	// the transform
	g2_matrix_t 				transform;

	// the units
	tb_size_t 					units;

	// the style
	g2_svg_style_t 				style;

}g2_svg_element_clippath_t;

/// the svg element type for <textPath ...>
typedef struct __g2_svg_element_textpath_t
{
	// the base
	g2_svg_element_t 			base;

	// the xlink-href
	tb_pstring_t 				href;

	// the style
	g2_svg_style_t 				style;

	// the transform
	g2_matrix_t 				transform;

}g2_svg_element_textpath_t;

/// the svg element type for <stop ...>
typedef struct __g2_svg_element_stop_t
{
	// the base
	g2_svg_element_t 			base;

	// the color
	g2_color_t 					color;

	// the offset
	g2_float_t 					offset;

}g2_svg_element_stop_t;

/// the svg element type for <linearGradient ...>
typedef struct __g2_svg_element_linear_gradient_t
{
	// the base
	g2_svg_element_t 			base;

	// the xlink-href
	tb_pstring_t 				href;

	// the transform
	g2_matrix_t 				transform;

	// the units
	tb_size_t 					units;

	// the spread
	tb_size_t 					spread;

	// the pb & pe
	g2_point_t 					pb;
	g2_point_t 					pe;

}g2_svg_element_linear_gradient_t;

/// the svg element type for <radialGradient ...>
typedef struct __g2_svg_element_radial_gradient_t
{
	// the base
	g2_svg_element_t 			base;

	// the xlink-href
	tb_pstring_t 				href;

	// the transform
	g2_matrix_t 				transform;

	// the units
	tb_size_t 					units;

	// the spread
	tb_size_t 					spread;

	// the cp & fp
	g2_circle_t 				cp;
	g2_point_t 					fp;

}g2_svg_element_radial_gradient_t;

/* ///////////////////////////////////////////////////////////////////////
 * interfaces
 */

/// init element
g2_svg_element_t* 	g2_svg_element_init(tb_handle_t reader);

/// init element: none tag
g2_svg_element_t* 	g2_svg_element_init_none(tb_handle_t reader);

/// init element: <g ...>
g2_svg_element_t* 	g2_svg_element_init_g(tb_handle_t reader);

/// init element: <svg ...>
g2_svg_element_t* 	g2_svg_element_init_svg(tb_handle_t reader);

/// init element: <use ...>
g2_svg_element_t* 	g2_svg_element_init_use(tb_handle_t reader);

/// init element: <>data</> or cdata
g2_svg_element_t* 	g2_svg_element_init_data(tb_handle_t reader);

/// init element: <text ...>
g2_svg_element_t* 	g2_svg_element_init_text(tb_handle_t reader);

/// init element: <path ...>
g2_svg_element_t* 	g2_svg_element_init_path(tb_handle_t reader);

/// init element: <rect ...>
g2_svg_element_t* 	g2_svg_element_init_rect(tb_handle_t reader);

/// init element: <line ...>
g2_svg_element_t* 	g2_svg_element_init_line(tb_handle_t reader);

/// init element: <image ...>
g2_svg_element_t* 	g2_svg_element_init_image(tb_handle_t reader);

/// init element: <circle ...>
g2_svg_element_t* 	g2_svg_element_init_circle(tb_handle_t reader);

/// init element: <ellipse ...>
g2_svg_element_t* 	g2_svg_element_init_ellipse(tb_handle_t reader);

/// init element: <polygon ...>
g2_svg_element_t* 	g2_svg_element_init_polygon(tb_handle_t reader);

/// init element: <polyline ...>
g2_svg_element_t* 	g2_svg_element_init_polyline(tb_handle_t reader);

/// init element: <clipPath ...>
g2_svg_element_t* 	g2_svg_element_init_clippath(tb_handle_t reader);

/// init element: <textPath ...>
g2_svg_element_t* 	g2_svg_element_init_textpath(tb_handle_t reader);

/// init element: <stop ...>
g2_svg_element_t* 	g2_svg_element_init_stop(tb_handle_t reader);

/// init element: <linearGradient ...>
g2_svg_element_t* 	g2_svg_element_init_linear_gradient(tb_handle_t reader);

/// init element: <radialGradient ...>
g2_svg_element_t* 	g2_svg_element_init_radial_gradient(tb_handle_t reader);

/// exit element
tb_void_t 			g2_svg_element_exit(g2_svg_element_t* element);

/// draw element
tb_void_t 			g2_svg_element_draw(g2_svg_element_t* element, tb_handle_t painter);

/// the element name
tb_char_t const* 	g2_svg_element_name(g2_svg_element_t const* element);

/// insert the next element
tb_void_t 			g2_svg_element_insert_next(g2_svg_element_t* element, g2_svg_element_t* next);

/// remove the next element
tb_void_t 			g2_svg_element_remove_next(g2_svg_element_t* element);

/// append the element to the head
tb_void_t 			g2_svg_element_append_head(g2_svg_element_t* element, g2_svg_element_t* child);

/// append the element to the tail
tb_void_t 			g2_svg_element_append_tail(g2_svg_element_t* element, g2_svg_element_t* child);

#endif


