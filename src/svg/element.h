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

// the svg element type
typedef enum __g2_svg_element_type_t
{
	G2_SVG_ELEMENT_TYPE_NONE 			= 0
,	G2_SVG_ELEMENT_TYPE_CIRClE 			= 1
,	G2_SVG_ELEMENT_TYPE_CLIPPATH		= 2
,	G2_SVG_ELEMENT_TYPE_DEFS			= 3
,	G2_SVG_ELEMENT_TYPE_ELLIPSE			= 4
,	G2_SVG_ELEMENT_TYPE_FECOLORMATRIX	= 5
,	G2_SVG_ELEMENT_TYPE_FILTER			= 6
,	G2_SVG_ELEMENT_TYPE_G				= 7
,	G2_SVG_ELEMENT_TYPE_IMAGE			= 8
,	G2_SVG_ELEMENT_TYPE_LINE			= 9
,	G2_SVG_ELEMENT_TYPE_LINEARGRADIENT	= 10
,	G2_SVG_ELEMENT_TYPE_MASK			= 11
,	G2_SVG_ELEMENT_TYPE_METADATA		= 12
,	G2_SVG_ELEMENT_TYPE_PATH			= 13
,	G2_SVG_ELEMENT_TYPE_POLYGON			= 14
,	G2_SVG_ELEMENT_TYPE_POLYLINE		= 15
,	G2_SVG_ELEMENT_TYPE_RADIALGRADIENT	= 16
,	G2_SVG_ELEMENT_TYPE_RECT			= 17
,	G2_SVG_ELEMENT_TYPE_SVG				= 18
,	G2_SVG_ELEMENT_TYPE_STOP			= 19
,	G2_SVG_ELEMENT_TYPE_SYMBOL			= 20
,	G2_SVG_ELEMENT_TYPE_TEXT			= 21
,	G2_SVG_ELEMENT_TYPE_TSPAN			= 22
,	G2_SVG_ELEMENT_TYPE_USE				= 23

}g2_svg_element_type_t;

// the svg element type
typedef struct __g2_svg_element_t
{

}g2_svg_element_t;

#endif


