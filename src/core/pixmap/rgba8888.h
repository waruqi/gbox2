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
 * @file		rgba8888.h
 *
 */
#ifndef G2_CORE_PIXMAP_RGBA8888_H
#define G2_CORE_PIXMAP_RGBA8888_H

/* ///////////////////////////////////////////////////////////////////////
 * includes
 */
#include "prefix.h"
#include "rgbx8888.h"

/* ///////////////////////////////////////////////////////////////////////
 * interfaces
 */


/* ///////////////////////////////////////////////////////////////////////
 * globals
 */

static g2_pixmap_t const g_pixmap_lo_rgba8888 =
{ 	
	"rgba8888"
, 	32
, 	4
, 	G2_PIXFMT_RGBA8888
, 	g2_pixmap_rgbx8888_pixel
, 	g2_pixmap_rgbx8888_color
,	g2_pixmap_rgb32_pixel_get_l
,	g2_pixmap_rgb32_pixel_set_lo
, 	g2_pixmap_rgb32_pixel_cpy_o
,	g2_pixmap_rgbx8888_color_get_l
,	g2_pixmap_rgbx8888_color_set_lo
, 	g2_pixmap_rgb32_pixels_set_lo
};

static g2_pixmap_t const g_pixmap_bo_rgba8888 =
{ 	
	"rgba8888"
, 	32
, 	4
, 	G2_PIXFMT_RGBA8888
, 	g2_pixmap_rgbx8888_pixel
, 	g2_pixmap_rgbx8888_color
,	g2_pixmap_rgb32_pixel_get_b
,	g2_pixmap_rgb32_pixel_set_bo
, 	g2_pixmap_rgb32_pixel_cpy_o
,	g2_pixmap_rgbx8888_color_get_b
,	g2_pixmap_rgbx8888_color_set_bo
, 	g2_pixmap_rgb32_pixels_set_bo
};

static g2_pixmap_t const g_pixmap_la_rgba8888 =
{ 	
	"rgba8888"
, 	32
, 	4
, 	G2_PIXFMT_RGBA8888
, 	g2_pixmap_rgbx8888_pixel
, 	g2_pixmap_rgbx8888_color
,	g2_pixmap_rgb32_pixel_get_l
,	g2_pixmap_xrgb8888_pixel_set_la
, 	g2_pixmap_xrgb8888_pixel_cpy_la
,	g2_pixmap_rgbx8888_color_get_l
,	g2_pixmap_rgbx8888_color_set_la
, 	g2_pixmap_xrgb8888_pixels_set_la
};

static g2_pixmap_t const g_pixmap_ba_rgba8888 =
{ 	
	"rgba8888"
, 	32
, 	4
, 	G2_PIXFMT_RGBA8888
, 	g2_pixmap_rgbx8888_pixel
, 	g2_pixmap_rgbx8888_color
,	g2_pixmap_rgb32_pixel_get_b
,	g2_pixmap_xrgb8888_pixel_set_ba
, 	g2_pixmap_xrgb8888_pixel_cpy_ba
,	g2_pixmap_rgbx8888_color_get_b
,	g2_pixmap_rgbx8888_color_set_ba
, 	g2_pixmap_xrgb8888_pixels_set_ba
};


#endif

