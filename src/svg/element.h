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
,	G2_SVG_ELEMENT_TYPE_DEFS
,	G2_SVG_ELEMENT_TYPE_DESC
,	G2_SVG_ELEMENT_TYPE_ELLIPSE
,	G2_SVG_ELEMENT_TYPE_FECOLORMATRIX
,	G2_SVG_ELEMENT_TYPE_FEGAUSSIANBLUR
,	G2_SVG_ELEMENT_TYPE_FEMERGE
,	G2_SVG_ELEMENT_TYPE_FEMERGENODE
,	G2_SVG_ELEMENT_TYPE_FILTER
,	G2_SVG_ELEMENT_TYPE_G
,	G2_SVG_ELEMENT_TYPE_GLYPH
,	G2_SVG_ELEMENT_TYPE_IMAGE
,	G2_SVG_ELEMENT_TYPE_LINE
,	G2_SVG_ELEMENT_TYPE_LINEARGRADIENT
,	G2_SVG_ELEMENT_TYPE_MASK
,	G2_SVG_ELEMENT_TYPE_METADATA
,	G2_SVG_ELEMENT_TYPE_PATH
,	G2_SVG_ELEMENT_TYPE_POLYGON
,	G2_SVG_ELEMENT_TYPE_POLYLINE
,	G2_SVG_ELEMENT_TYPE_RADIALGRADIENT
,	G2_SVG_ELEMENT_TYPE_RECT
,	G2_SVG_ELEMENT_TYPE_SCRIPT
,	G2_SVG_ELEMENT_TYPE_SVG
,	G2_SVG_ELEMENT_TYPE_STOP
,	G2_SVG_ELEMENT_TYPE_SYMBOL
,	G2_SVG_ELEMENT_TYPE_TEXT
,	G2_SVG_ELEMENT_TYPE_TITLE
,	G2_SVG_ELEMENT_TYPE_TSPAN
,	G2_SVG_ELEMENT_TYPE_USE
,	G2_SVG_ELEMENT_TYPE_VIDEO

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

	// exit it
	tb_void_t 					(*exit)(struct __g2_svg_element_t* element);

}g2_svg_element_t;

/// the svg element type for <a ...>
typedef struct __g2_svg_element_a_t
{
	// the base
	g2_svg_element_t 			base;

}g2_svg_element_a_t;

/// the svg element type for <g ...>
typedef struct __g2_svg_element_g_t
{
	// the base
	g2_svg_element_t 			base;

}g2_svg_element_g_t;

/// the svg element type for <use ...>
typedef struct __g2_svg_element_use_t
{
	// the base
	g2_svg_element_t 			base;

}g2_svg_element_use_t;

/// the svg element type for <svg ...>
typedef struct __g2_svg_element_svg_t
{
	// the base
	g2_svg_element_t 			base;

}g2_svg_element_svg_t;

/// the svg element type for <defs ...>
typedef struct __g2_svg_element_defs_t
{
	// the base
	g2_svg_element_t 			base;

}g2_svg_element_defs_t;

/// the svg element type for <path ...>
typedef struct __g2_svg_element_path_t
{
	// the base
	g2_svg_element_t 			base;

}g2_svg_element_path_t;

/// the svg element type for <stop ...>
typedef struct __g2_svg_element_stop_t
{
	// the base
	g2_svg_element_t 			base;

}g2_svg_element_stop_t;

/// the svg element type for <rect ...>
typedef struct __g2_svg_element_rect_t
{
	// the base
	g2_svg_element_t 			base;

}g2_svg_element_rect_t;

/// the svg element type for <text ...>
typedef struct __g2_svg_element_text_t
{
	// the base
	g2_svg_element_t 			base;

}g2_svg_element_text_t;

/// the svg element type for <line ...>
typedef struct __g2_svg_element_line_t
{
	// the base
	g2_svg_element_t 			base;

}g2_svg_element_line_t;

/// the svg element type for <desc ...>
typedef struct __g2_svg_element_desc_t
{
	// the base
	g2_svg_element_t 			base;

}g2_svg_element_desc_t;

/// the svg element type for <mask ...>
typedef struct __g2_svg_element_mask_t
{
	// the base
	g2_svg_element_t 			base;

}g2_svg_element_mask_t;

/// the svg element type for <tspan ...>
typedef struct __g2_svg_element_tspan_t
{
	// the base
	g2_svg_element_t 			base;

}g2_svg_element_tspan_t;

/// the svg element type for <glyph ...>
typedef struct __g2_svg_element_glyph_t
{
	// the base
	g2_svg_element_t 			base;

}g2_svg_element_glyph_t;

/// the svg element type for <title ...>
typedef struct __g2_svg_element_title_t
{
	// the base
	g2_svg_element_t 			base;

}g2_svg_element_title_t;

/// the svg element type for <video ...>
typedef struct __g2_svg_element_video_t
{
	// the base
	g2_svg_element_t 			base;

}g2_svg_element_video_t;

/// the svg element type for <image ...>
typedef struct __g2_svg_element_image_t
{
	// the base
	g2_svg_element_t 			base;

}g2_svg_element_image_t;

/// the svg element type for <script ...>
typedef struct __g2_svg_element_script_t
{
	// the base
	g2_svg_element_t 			base;

}g2_svg_element_script_t;

/// the svg element type for <symbol ...>
typedef struct __g2_svg_element_symbol_t
{
	// the base
	g2_svg_element_t 			base;

}g2_svg_element_symbol_t;

/// the svg element type for <filter ...>
typedef struct __g2_svg_element_filter_t
{
	// the base
	g2_svg_element_t 			base;

}g2_svg_element_filter_t;

/// the svg element type for <circle ...>
typedef struct __g2_svg_element_circle_t
{
	// the base
	g2_svg_element_t 			base;

}g2_svg_element_circle_t;

/// the svg element type for <ellipse ...>
typedef struct __g2_svg_element_ellipse_t
{
	// the base
	g2_svg_element_t 			base;

}g2_svg_element_ellipse_t;

/// the svg element type for <polygon ...>
typedef struct __g2_svg_element_polygon_t
{
	// the base
	g2_svg_element_t 			base;

}g2_svg_element_polygon_t;

/// the svg element type for <polyline ...>
typedef struct __g2_svg_element_polyline_t
{
	// the base
	g2_svg_element_t 			base;

}g2_svg_element_polyline_t;

/// the svg element type for <metadata ...>
typedef struct __g2_svg_element_metadata_t
{
	// the base
	g2_svg_element_t 			base;

}g2_svg_element_metadata_t;

/// the svg element type for <clipPath ...>
typedef struct __g2_svg_element_clippath_t
{
	// the base
	g2_svg_element_t 			base;

}g2_svg_element_clippath_t;

/// the svg element type for <linearGradient ...>
typedef struct __g2_svg_element_linear_gradient_t
{
	// the base
	g2_svg_element_t 			base;

}g2_svg_element_linear_gradient_t;

/// the svg element type for <radialGradient ...>
typedef struct __g2_svg_element_radial_gradient_t
{
	// the base
	g2_svg_element_t 			base;

}g2_svg_element_radial_gradient_t;

/// the svg element type for <feMerge ...>
typedef struct __g2_svg_element_fe_merge_t
{
	// the base
	g2_svg_element_t 			base;

}g2_svg_element_fe_merge_t;

/// the svg element type for <feMergeNode ...>
typedef struct __g2_svg_element_fe_merge_node_t
{
	// the base
	g2_svg_element_t 			base;

}g2_svg_element_fe_merge_node_t;

/// the svg element type for <feColorMatrix ...>
typedef struct __g2_svg_element_fe_color_matrix_t
{
	// the base
	g2_svg_element_t 			base;

}g2_svg_element_fe_color_matrix_t;

/// the svg element type for <feGaussianBlur ...>
typedef struct __g2_svg_element_fe_gaussian_blur_t
{
	// the base
	g2_svg_element_t 			base;

}g2_svg_element_fe_gaussian_blur_t;

/// the svg element type for <animate ...>
typedef struct __g2_svg_element_animate_t
{
	// the base
	g2_svg_element_t 			base;

}g2_svg_element_animate_t;

/// the svg element type for <animateColor ...>
typedef struct __g2_svg_element_animate_color_t
{
	// the base
	g2_svg_element_t 			base;

}g2_svg_element_animate_color_t;

/// the svg element type for <animateMotion ...>
typedef struct __g2_svg_element_animate_motion_t
{
	// the base
	g2_svg_element_t 			base;

}g2_svg_element_animate_motion_t;

/// the svg element type for <animateTransform ...>
typedef struct __g2_svg_element_animate_transform_t
{
	// the base
	g2_svg_element_t 			base;

}g2_svg_element_animate_transform_t;

/* ///////////////////////////////////////////////////////////////////////
 * interfaces
 */

/// init element
g2_svg_element_t* 	g2_svg_element_init(tb_handle_t reader);

/// init element: <a ...>
g2_svg_element_t* 	g2_svg_element_init_a(tb_handle_t reader);

/// init element: <g ...>
g2_svg_element_t* 	g2_svg_element_init_g(tb_handle_t reader);

/// init element: <svg ...>
g2_svg_element_t* 	g2_svg_element_init_svg(tb_handle_t reader);

/// init element: <use ...>
g2_svg_element_t* 	g2_svg_element_init_use(tb_handle_t reader);

/// init element: unknown tag
g2_svg_element_t* 	g2_svg_element_init_none(tb_handle_t reader);

/// init element: <defs ...>
g2_svg_element_t* 	g2_svg_element_init_defs(tb_handle_t reader);

/// init element: <mask ...>
g2_svg_element_t* 	g2_svg_element_init_mask(tb_handle_t reader);

/// init element: <path ...>
g2_svg_element_t* 	g2_svg_element_init_path(tb_handle_t reader);

/// init element: <stop ...>
g2_svg_element_t* 	g2_svg_element_init_stop(tb_handle_t reader);

/// init element: <line ...>
g2_svg_element_t* 	g2_svg_element_init_line(tb_handle_t reader);

/// init element: <rect ...>
g2_svg_element_t* 	g2_svg_element_init_rect(tb_handle_t reader);

/// init element: <desc ...>
g2_svg_element_t* 	g2_svg_element_init_desc(tb_handle_t reader);

/// init element: <text ...>
g2_svg_element_t* 	g2_svg_element_init_text(tb_handle_t reader);

/// init element: <title ...>
g2_svg_element_t* 	g2_svg_element_init_title(tb_handle_t reader);

/// init element: <video ...>
g2_svg_element_t* 	g2_svg_element_init_video(tb_handle_t reader);

/// init element: <image ...>
g2_svg_element_t* 	g2_svg_element_init_image(tb_handle_t reader);

/// init element: <glyph ...>
g2_svg_element_t* 	g2_svg_element_init_glyph(tb_handle_t reader);

/// init element: <tspan ...>
g2_svg_element_t* 	g2_svg_element_init_tspan(tb_handle_t reader);

/// init element: <filter ...>
g2_svg_element_t* 	g2_svg_element_init_filter(tb_handle_t reader);

/// init element: <circle ...>
g2_svg_element_t* 	g2_svg_element_init_circle(tb_handle_t reader);

/// init element: <script ...>
g2_svg_element_t* 	g2_svg_element_init_script(tb_handle_t reader);

/// init element: <symbol ...>
g2_svg_element_t* 	g2_svg_element_init_symbol(tb_handle_t reader);

/// init element: <ellipse ...>
g2_svg_element_t* 	g2_svg_element_init_ellipse(tb_handle_t reader);

/// init element: <polygon ...>
g2_svg_element_t* 	g2_svg_element_init_polygon(tb_handle_t reader);

/// init element: <polyline ...>
g2_svg_element_t* 	g2_svg_element_init_polyline(tb_handle_t reader);

/// init element: <metadata ...>
g2_svg_element_t* 	g2_svg_element_init_metadata(tb_handle_t reader);

/// init element: <clipPath ...>
g2_svg_element_t* 	g2_svg_element_init_clippath(tb_handle_t reader);

/// init element: <linearGradient ...>
g2_svg_element_t* 	g2_svg_element_init_linear_gradient(tb_handle_t reader);

/// init element: <radialGradient ...>
g2_svg_element_t* 	g2_svg_element_init_radial_gradient(tb_handle_t reader);

/// init element: <feMerge ...>
g2_svg_element_t* 	g2_svg_element_init_fe_merge(tb_handle_t reader);

/// init element: <feMergeNode ...>
g2_svg_element_t* 	g2_svg_element_init_fe_merge_node(tb_handle_t reader);

/// init element: <feColorMatrix ...>
g2_svg_element_t* 	g2_svg_element_init_fe_color_matrix(tb_handle_t reader);

/// init element: <feGaussianBlur ...>
g2_svg_element_t* 	g2_svg_element_init_fe_gaussian_blur(tb_handle_t reader);

/// init element: <animate ...>
g2_svg_element_t* 	g2_svg_element_init_animate(tb_handle_t reader);

/// init element: <animateColor ...>
g2_svg_element_t* 	g2_svg_element_init_animate_color(tb_handle_t reader);

/// init element: <animateMotion ...>
g2_svg_element_t* 	g2_svg_element_init_animate_motion(tb_handle_t reader);

/// init element: <animateTransform ...>
g2_svg_element_t* 	g2_svg_element_init_animate_transform(tb_handle_t reader);

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


