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
 * @file		pixmap.c
 *
 */
/* ////////////////////////////////////////////////////////////////////////
 * includes
 */
#include "pixmap.h"
#include "pixmap/pal8.h"
#include "pixmap/rgb565.h"
#include "pixmap/rgb888.h"
#include "pixmap/argb1555.h"
#include "pixmap/xrgb1555.h"
#include "pixmap/argb8888.h"
#include "pixmap/xrgb8888.h"
#include "pixmap/rgba8888.h"
#include "pixmap/rgbx8888.h"
#include "../core/painter.h"

/* ////////////////////////////////////////////////////////////////////////
 * globals 
 */

// the pixmaps for opaque
static g2_pixmap_t g_pixmaps_opaque[] =
{
	{ 	"pal8"
	, 	8
	, 	1
	, 	G2_PIXFMT_PAL8
	, 	g2_pixmap_pal8_pixel
	, 	g2_pixmap_pal8_color
	,	g2_pixmap_pal8_pixel_get
	,	g2_pixmap_pal8_pixel_set_o
	, 	g2_pixmap_pal8_pixel_cpy_o
	,	g2_pixmap_pal8_color_get
	,	g2_pixmap_pal8_color_set_o
	, 	g2_pixmap_pal8_pixels_set_o
	}

, 	{ 	"rgb565"
	, 	16
	, 	2
	, 	G2_PIXFMT_RGB565
	, 	g2_pixmap_rgb565_pixel
	, 	g2_pixmap_rgb565_color
	,	g2_pixmap_rgb565_pixel_get
	,	g2_pixmap_rgb565_pixel_set_o
	, 	g2_pixmap_rgb565_pixel_cpy_o
	,	g2_pixmap_rgb565_color_get
	,	g2_pixmap_rgb565_color_set_o
	, 	g2_pixmap_rgb565_pixels_set_o
	}

, 	{ 	"rgb888"
	, 	24
	, 	3
	, 	G2_PIXFMT_RGB888
	, 	g2_pixmap_rgb888_pixel
	, 	g2_pixmap_rgb888_color
	,	g2_pixmap_rgb888_pixel_get
	,	g2_pixmap_rgb888_pixel_set_o
	, 	g2_pixmap_rgb888_pixel_cpy_o
	,	g2_pixmap_rgb888_color_get
	,	g2_pixmap_rgb888_color_set_o
	, 	g2_pixmap_rgb888_pixels_set_o
	}

, 	{ 	"argb1555"
	, 	16
	, 	2
	, 	G2_PIXFMT_ARGB1555
	, 	g2_pixmap_argb1555_pixel
	, 	g2_pixmap_argb1555_color
	,	g2_pixmap_argb1555_pixel_get
	,	g2_pixmap_argb1555_pixel_set_o
	, 	g2_pixmap_argb1555_pixel_cpy_o
	,	g2_pixmap_argb1555_color_get
	,	g2_pixmap_argb1555_color_set_o
	, 	g2_pixmap_argb1555_pixels_set_o
	}

, 	{ 	"xrgb1555"
	, 	16
	, 	2
	, 	G2_PIXFMT_XRGB1555
	, 	g2_pixmap_xrgb1555_pixel
	, 	g2_pixmap_xrgb1555_color
	,	g2_pixmap_xrgb1555_pixel_get
	,	g2_pixmap_xrgb1555_pixel_set_o
	, 	g2_pixmap_xrgb1555_pixel_cpy_o
	,	g2_pixmap_xrgb1555_color_get
	,	g2_pixmap_xrgb1555_color_set_o
	, 	g2_pixmap_xrgb1555_pixels_set_o
	}

, 	{ 	"argb8888"
	, 	32
	, 	4
	, 	G2_PIXFMT_ARGB8888
	, 	g2_pixmap_argb8888_pixel
	, 	g2_pixmap_argb8888_color
	,	g2_pixmap_argb8888_pixel_get
	,	g2_pixmap_argb8888_pixel_set_o
	, 	g2_pixmap_argb8888_pixel_cpy_o
	,	g2_pixmap_argb8888_color_get
	,	g2_pixmap_argb8888_color_set_o
	, 	g2_pixmap_argb8888_pixels_set_o
	}

, 	{ 	"xrgb8888"
	, 	32
	, 	4
	, 	G2_PIXFMT_XRGB8888
	, 	g2_pixmap_xrgb8888_pixel
	, 	g2_pixmap_xrgb8888_color
	,	g2_pixmap_xrgb8888_pixel_get
	,	g2_pixmap_xrgb8888_pixel_set_o
	, 	g2_pixmap_xrgb8888_pixel_cpy_o
	,	g2_pixmap_xrgb8888_color_get
	,	g2_pixmap_xrgb8888_color_set_o
	, 	g2_pixmap_xrgb8888_pixels_set_o
	}

, 	{ 	"argb4444"
	, 	16
	, 	2
	, 	G2_PIXFMT_ARGB4444
	, 	TB_NULL
	, 	TB_NULL
	,	TB_NULL
	,	TB_NULL
	, 	TB_NULL
	,	TB_NULL
	,	TB_NULL
	, 	TB_NULL
	}

, 	{ 	"xrgb4444"
	, 	16
	, 	2
	, 	G2_PIXFMT_XRGB4444
	, 	TB_NULL
	, 	TB_NULL
	,	TB_NULL
	,	TB_NULL
	, 	TB_NULL
	,	TB_NULL
	,	TB_NULL
	, 	TB_NULL
	}

, 	{ 	"rgba8888"
	, 	32
	, 	4
	, 	G2_PIXFMT_RGBA8888
	, 	g2_pixmap_rgba8888_pixel
	, 	g2_pixmap_rgba8888_color
	,	g2_pixmap_rgba8888_pixel_get
	,	g2_pixmap_rgba8888_pixel_set_o
	, 	g2_pixmap_rgba8888_pixel_cpy_o
	,	g2_pixmap_rgba8888_color_get
	,	g2_pixmap_rgba8888_color_set_o
	, 	g2_pixmap_rgba8888_pixels_set_o
	}

, 	{ 	"rgbx8888"
	, 	32
	, 	4
	, 	G2_PIXFMT_RGBX8888
	, 	g2_pixmap_rgbx8888_pixel
	, 	g2_pixmap_rgbx8888_color
	,	g2_pixmap_rgbx8888_pixel_get
	,	g2_pixmap_rgbx8888_pixel_set_o
	, 	g2_pixmap_rgbx8888_pixel_cpy_o
	,	g2_pixmap_rgbx8888_color_get
	,	g2_pixmap_rgbx8888_color_set_o
	, 	g2_pixmap_rgbx8888_pixels_set_o
	}

, 	{ 	"rgba4444"
	, 	16
	, 	2
	, 	G2_PIXFMT_RGBA4444
	, 	TB_NULL
	, 	TB_NULL
	,	TB_NULL
	,	TB_NULL
	, 	TB_NULL
	,	TB_NULL
	,	TB_NULL
	, 	TB_NULL
	}

, 	{ 	"rgbx4444"
	, 	16
	, 	2
	, 	G2_PIXFMT_RGBX4444
	, 	TB_NULL
	, 	TB_NULL
	,	TB_NULL
	,	TB_NULL
	, 	TB_NULL
	,	TB_NULL
	,	TB_NULL
	, 	TB_NULL
	}

, 	{ 	"bgr565"
	, 	16
	, 	2
	, 	G2_PIXFMT_BGR565
	, 	TB_NULL
	, 	TB_NULL
	,	TB_NULL
	,	TB_NULL
	, 	TB_NULL
	,	TB_NULL
	,	TB_NULL
	, 	TB_NULL
	}

, 	{ 	"bgr888"
	, 	24
	, 	3
	, 	G2_PIXFMT_BGR888
	, 	TB_NULL
	, 	TB_NULL
	,	TB_NULL
	,	TB_NULL
	, 	TB_NULL
	,	TB_NULL
	,	TB_NULL
	, 	TB_NULL
	}
, 	{ 	"abgr1555"
	, 	16
	, 	2
	, 	G2_PIXFMT_ABGR1555
	, 	TB_NULL
	, 	TB_NULL
	,	TB_NULL
	,	TB_NULL
	, 	TB_NULL
	,	TB_NULL
	,	TB_NULL
	, 	TB_NULL
	}

, 	{ 	"xbgr1555"
	, 	16
	, 	2
	, 	G2_PIXFMT_XBGR1555
	, 	TB_NULL
	, 	TB_NULL
	,	TB_NULL
	,	TB_NULL
	, 	TB_NULL
	,	TB_NULL
	,	TB_NULL
	, 	TB_NULL
	}

, 	{ 	"abgr8888"
	, 	32
	, 	4
	, 	G2_PIXFMT_ABGR8888
	, 	TB_NULL
	, 	TB_NULL
	,	TB_NULL
	,	TB_NULL
	, 	TB_NULL
	,	TB_NULL
	,	TB_NULL
	, 	TB_NULL
	}

, 	{ 	"xbgr8888"
	, 	32
	, 	4
	, 	G2_PIXFMT_XBGR8888
	, 	TB_NULL
	, 	TB_NULL
	,	TB_NULL
	,	TB_NULL
	, 	TB_NULL
	,	TB_NULL
	,	TB_NULL
	, 	TB_NULL
	}

, 	{ 	"abgr4444"
	, 	16
	, 	2
	, 	G2_PIXFMT_ABGR4444
	, 	TB_NULL
	, 	TB_NULL
	,	TB_NULL
	,	TB_NULL
	, 	TB_NULL
	,	TB_NULL
	,	TB_NULL
	, 	TB_NULL
	}

, 	{ 	"xbgr4444"
	, 	16
	, 	2
	, 	G2_PIXFMT_XBGR4444
	, 	TB_NULL
	, 	TB_NULL
	,	TB_NULL
	,	TB_NULL
	, 	TB_NULL
	,	TB_NULL
	,	TB_NULL
	, 	TB_NULL
	}

, 	{ 	"bgra8888"
	, 	32
	, 	4
	, 	G2_PIXFMT_BGRA8888
	, 	TB_NULL
	, 	TB_NULL
	,	TB_NULL
	,	TB_NULL
	, 	TB_NULL
	,	TB_NULL
	,	TB_NULL
	, 	TB_NULL
	}

, 	{ 	"bgrx8888"
	, 	32
	, 	4
	, 	G2_PIXFMT_BGRX8888
	, 	TB_NULL
	, 	TB_NULL
	,	TB_NULL
	,	TB_NULL
	, 	TB_NULL
	,	TB_NULL
	,	TB_NULL
	, 	TB_NULL
	}

, 	{ 	"bgra4444"
	, 	16
	, 	2
	, 	G2_PIXFMT_BGRA4444
	, 	TB_NULL
	, 	TB_NULL
	,	TB_NULL
	,	TB_NULL
	, 	TB_NULL
	,	TB_NULL
	,	TB_NULL
	, 	TB_NULL
	}

, 	{ 	"bgrx4444"
	, 	16
	, 	2
	, 	G2_PIXFMT_BGRX4444
	, 	TB_NULL
	, 	TB_NULL
	,	TB_NULL
	,	TB_NULL
	, 	TB_NULL
	,	TB_NULL
	,	TB_NULL
	, 	TB_NULL
	}
};

// the pixmaps for alpha
static g2_pixmap_t g_pixmaps_alpha[] =
{
	{ 	"pal8"
	, 	8
	, 	1
	, 	G2_PIXFMT_PAL8
	, 	g2_pixmap_pal8_pixel
	, 	g2_pixmap_pal8_color
	,	g2_pixmap_pal8_pixel_get
	,	g2_pixmap_pal8_pixel_set_a
	, 	g2_pixmap_pal8_pixel_cpy_a
	,	g2_pixmap_pal8_color_get
	,	g2_pixmap_pal8_color_set_a
	, 	g2_pixmap_pal8_pixels_set_a
	}

, 	{ 	"rgb565"
	, 	16
	, 	2
	, 	G2_PIXFMT_RGB565
	, 	g2_pixmap_rgb565_pixel
	, 	g2_pixmap_rgb565_color
	,	g2_pixmap_rgb565_pixel_get
	,	g2_pixmap_rgb565_pixel_set_a
	, 	g2_pixmap_rgb565_pixel_cpy_a
	,	g2_pixmap_rgb565_color_get
	,	g2_pixmap_rgb565_color_set_a
	, 	g2_pixmap_rgb565_pixels_set_a
	}

, 	{ 	"rgb888"
	, 	24
	, 	3
	, 	G2_PIXFMT_RGB888
	, 	g2_pixmap_rgb888_pixel
	, 	g2_pixmap_rgb888_color
	,	g2_pixmap_rgb888_pixel_get
	,	g2_pixmap_rgb888_pixel_set_a
	, 	g2_pixmap_rgb888_pixel_cpy_a
	,	g2_pixmap_rgb888_color_get
	,	g2_pixmap_rgb888_color_set_a
	, 	g2_pixmap_rgb888_pixels_set_a
	}

, 	{ 	"argb1555"
	, 	16
	, 	2
	, 	G2_PIXFMT_ARGB1555
	, 	g2_pixmap_argb1555_pixel
	, 	g2_pixmap_argb1555_color
	,	g2_pixmap_argb1555_pixel_get
	,	g2_pixmap_argb1555_pixel_set_a
	, 	g2_pixmap_argb1555_pixel_cpy_a
	,	g2_pixmap_argb1555_color_get
	,	g2_pixmap_argb1555_color_set_a
	, 	g2_pixmap_argb1555_pixels_set_a
	}

, 	{ 	"xrgb1555"
	, 	16
	, 	2
	, 	G2_PIXFMT_XRGB1555
	, 	g2_pixmap_xrgb1555_pixel
	, 	g2_pixmap_xrgb1555_color
	,	g2_pixmap_xrgb1555_pixel_get
	,	g2_pixmap_xrgb1555_pixel_set_a
	, 	g2_pixmap_xrgb1555_pixel_cpy_a
	,	g2_pixmap_xrgb1555_color_get
	,	g2_pixmap_xrgb1555_color_set_a
	, 	g2_pixmap_xrgb1555_pixels_set_a
	}

, 	{ 	"argb8888"
	, 	32
	, 	4
	, 	G2_PIXFMT_ARGB8888
	, 	g2_pixmap_argb8888_pixel
	, 	g2_pixmap_argb8888_color
	,	g2_pixmap_argb8888_pixel_get
	,	g2_pixmap_argb8888_pixel_set_a
	, 	g2_pixmap_argb8888_pixel_cpy_a
	,	g2_pixmap_argb8888_color_get
	,	g2_pixmap_argb8888_color_set_a
	, 	g2_pixmap_argb8888_pixels_set_a
	}

, 	{ 	"xrgb8888"
	, 	32
	, 	4
	, 	G2_PIXFMT_XRGB8888
	, 	g2_pixmap_xrgb8888_pixel
	, 	g2_pixmap_xrgb8888_color
	,	g2_pixmap_xrgb8888_pixel_get
	,	g2_pixmap_xrgb8888_pixel_set_a
	, 	g2_pixmap_xrgb8888_pixel_cpy_a
	,	g2_pixmap_xrgb8888_color_get
	,	g2_pixmap_xrgb8888_color_set_a
	, 	g2_pixmap_xrgb8888_pixels_set_a
	}

, 	{ 	"argb4444"
	, 	16
	, 	2
	, 	G2_PIXFMT_ARGB4444
	, 	TB_NULL
	, 	TB_NULL
	,	TB_NULL
	,	TB_NULL
	, 	TB_NULL
	,	TB_NULL
	,	TB_NULL
	, 	TB_NULL
	}

, 	{ 	"xrgb4444"
	, 	16
	, 	2
	, 	G2_PIXFMT_XRGB4444
	, 	TB_NULL
	, 	TB_NULL
	,	TB_NULL
	,	TB_NULL
	, 	TB_NULL
	,	TB_NULL
	,	TB_NULL
	, 	TB_NULL
	}

, 	{ 	"rgba8888"
	, 	32
	, 	4
	, 	G2_PIXFMT_RGBA8888
	, 	g2_pixmap_rgba8888_pixel
	, 	g2_pixmap_rgba8888_color
	,	g2_pixmap_rgba8888_pixel_get
	,	g2_pixmap_rgba8888_pixel_set_a
	, 	g2_pixmap_rgba8888_pixel_cpy_a
	,	g2_pixmap_rgba8888_color_get
	,	g2_pixmap_rgba8888_color_set_a
	, 	g2_pixmap_rgba8888_pixels_set_a
	}

, 	{ 	"rgbx8888"
	, 	32
	, 	4
	, 	G2_PIXFMT_RGBX8888
	, 	g2_pixmap_rgbx8888_pixel
	, 	g2_pixmap_rgbx8888_color
	,	g2_pixmap_rgbx8888_pixel_get
	,	g2_pixmap_rgbx8888_pixel_set_a
	, 	g2_pixmap_rgbx8888_pixel_cpy_a
	,	g2_pixmap_rgbx8888_color_get
	,	g2_pixmap_rgbx8888_color_set_a
	, 	g2_pixmap_rgbx8888_pixels_set_a
	}

, 	{ 	"rgba4444"
	, 	16
	, 	2
	, 	G2_PIXFMT_RGBA4444
	, 	TB_NULL
	, 	TB_NULL
	,	TB_NULL
	,	TB_NULL
	, 	TB_NULL
	,	TB_NULL
	,	TB_NULL
	, 	TB_NULL
	}

, 	{ 	"rgbx4444"
	, 	16
	, 	2
	, 	G2_PIXFMT_RGBX4444
	, 	TB_NULL
	, 	TB_NULL
	,	TB_NULL
	,	TB_NULL
	, 	TB_NULL
	,	TB_NULL
	,	TB_NULL
	, 	TB_NULL
	}

, 	{ 	"bgr565"
	, 	16
	, 	2
	, 	G2_PIXFMT_BGR565
	, 	TB_NULL
	, 	TB_NULL
	,	TB_NULL
	,	TB_NULL
	, 	TB_NULL
	,	TB_NULL
	,	TB_NULL
	, 	TB_NULL
	}

, 	{ 	"bgr888"
	, 	24
	, 	3
	, 	G2_PIXFMT_BGR888
	, 	TB_NULL
	, 	TB_NULL
	,	TB_NULL
	,	TB_NULL
	, 	TB_NULL
	,	TB_NULL
	,	TB_NULL
	, 	TB_NULL
	}
, 	{ 	"abgr1555"
	, 	16
	, 	2
	, 	G2_PIXFMT_ABGR1555
	, 	TB_NULL
	, 	TB_NULL
	,	TB_NULL
	,	TB_NULL
	, 	TB_NULL
	,	TB_NULL
	,	TB_NULL
	, 	TB_NULL
	}

, 	{ 	"xbgr1555"
	, 	16
	, 	2
	, 	G2_PIXFMT_XBGR1555
	, 	TB_NULL
	, 	TB_NULL
	,	TB_NULL
	,	TB_NULL
	, 	TB_NULL
	,	TB_NULL
	,	TB_NULL
	, 	TB_NULL
	}

, 	{ 	"abgr8888"
	, 	32
	, 	4
	, 	G2_PIXFMT_ABGR8888
	, 	TB_NULL
	, 	TB_NULL
	,	TB_NULL
	,	TB_NULL
	, 	TB_NULL
	,	TB_NULL
	,	TB_NULL
	, 	TB_NULL
	}

, 	{ 	"xbgr8888"
	, 	32
	, 	4
	, 	G2_PIXFMT_XBGR8888
	, 	TB_NULL
	, 	TB_NULL
	,	TB_NULL
	,	TB_NULL
	, 	TB_NULL
	,	TB_NULL
	,	TB_NULL
	, 	TB_NULL
	}

, 	{ 	"abgr4444"
	, 	16
	, 	2
	, 	G2_PIXFMT_ABGR4444
	, 	TB_NULL
	, 	TB_NULL
	,	TB_NULL
	,	TB_NULL
	, 	TB_NULL
	,	TB_NULL
	,	TB_NULL
	, 	TB_NULL
	}

, 	{ 	"xbgr4444"
	, 	16
	, 	2
	, 	G2_PIXFMT_XBGR4444
	, 	TB_NULL
	, 	TB_NULL
	,	TB_NULL
	,	TB_NULL
	, 	TB_NULL
	,	TB_NULL
	,	TB_NULL
	, 	TB_NULL
	}

, 	{ 	"bgra8888"
	, 	32
	, 	4
	, 	G2_PIXFMT_BGRA8888
	, 	TB_NULL
	, 	TB_NULL
	,	TB_NULL
	,	TB_NULL
	, 	TB_NULL
	,	TB_NULL
	,	TB_NULL
	, 	TB_NULL
	}

, 	{ 	"bgrx8888"
	, 	32
	, 	4
	, 	G2_PIXFMT_BGRX8888
	, 	TB_NULL
	, 	TB_NULL
	,	TB_NULL
	,	TB_NULL
	, 	TB_NULL
	,	TB_NULL
	,	TB_NULL
	, 	TB_NULL
	}

, 	{ 	"bgra4444"
	, 	16
	, 	2
	, 	G2_PIXFMT_BGRA4444
	, 	TB_NULL
	, 	TB_NULL
	,	TB_NULL
	,	TB_NULL
	, 	TB_NULL
	,	TB_NULL
	,	TB_NULL
	, 	TB_NULL
	}

, 	{ 	"bgrx4444"
	, 	16
	, 	2
	, 	G2_PIXFMT_BGRX4444
	, 	TB_NULL
	, 	TB_NULL
	,	TB_NULL
	,	TB_NULL
	, 	TB_NULL
	,	TB_NULL
	,	TB_NULL
	, 	TB_NULL
	}
};

/* ////////////////////////////////////////////////////////////////////////
 * implementions
 */
g2_pixmap_t* g2_pixmap(tb_handle_t painter, tb_size_t pixfmt, tb_byte_t alpha)
{
	tb_byte_t a = painter? (G2_QUALITY_TOP - g2_quality(painter)) << 3 : 0;
	if (alpha >= (0xff - a))
	{
		// opaque
		tb_assert_and_check_return_val(pixfmt != G2_PIXFMT_NONE && (pixfmt - 1) < tb_arrayn(g_pixmaps_opaque), TB_NULL);
		return (g2_pixmap_t*)&(g_pixmaps_opaque[pixfmt - 1]);
	}
	else if (alpha > a)
	{
		// alpha
		tb_assert_and_check_return_val(pixfmt != G2_PIXFMT_NONE && (pixfmt - 1) < tb_arrayn(g_pixmaps_alpha), TB_NULL);
		return (g2_pixmap_t*)&(g_pixmaps_alpha[pixfmt - 1]);
	}

	// transparent
	return TB_NULL;
}

