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
static g2_pixmap_t const* g_pixmaps_opaque[] =
{
	&g_pixmap_opaque_pal8
,	&g_pixmap_opaque_rgb565
,	&g_pixmap_opaque_rgb888
,	&g_pixmap_opaque_argb1555
,	&g_pixmap_opaque_xrgb1555
,	&g_pixmap_opaque_argb8888
,	&g_pixmap_opaque_xrgb8888
,	TB_NULL
,	TB_NULL
,	&g_pixmap_opaque_rgba8888
,	&g_pixmap_opaque_rgbx8888
,	TB_NULL
,	TB_NULL

,	TB_NULL
,	TB_NULL
,	TB_NULL
,	TB_NULL
,	TB_NULL
,	TB_NULL
,	TB_NULL
,	TB_NULL
,	TB_NULL
,	TB_NULL
,	TB_NULL
,	TB_NULL

};

// the pixmaps for alpha
static g2_pixmap_t const* g_pixmaps_alpha[] =
{
	&g_pixmap_alpha_pal8
,	&g_pixmap_alpha_rgb565
,	&g_pixmap_alpha_rgb888
,	&g_pixmap_alpha_argb1555
,	&g_pixmap_alpha_xrgb1555
,	&g_pixmap_alpha_argb8888
,	&g_pixmap_alpha_xrgb8888
,	TB_NULL
,	TB_NULL
,	&g_pixmap_alpha_rgba8888
,	&g_pixmap_alpha_rgbx8888
,	TB_NULL
,	TB_NULL

,	TB_NULL
,	TB_NULL
,	TB_NULL
,	TB_NULL
,	TB_NULL
,	TB_NULL
,	TB_NULL
,	TB_NULL
,	TB_NULL
,	TB_NULL
,	TB_NULL
,	TB_NULL

};

/* ////////////////////////////////////////////////////////////////////////
 * implementions
 */
g2_pixmap_t const* g2_pixmap(tb_handle_t painter, tb_size_t pixfmt, tb_byte_t alpha)
{
	tb_byte_t a = painter? (G2_QUALITY_TOP - g2_quality(painter)) << 3 : 0;
	if (alpha >= (0xff - a))
	{
		// opaque
		tb_assert_and_check_return_val(pixfmt != G2_PIXFMT_NONE && (pixfmt - 1) < tb_arrayn(g_pixmaps_opaque), TB_NULL);
		return g_pixmaps_opaque[pixfmt - 1];
	}
	else if (alpha > a)
	{
		// alpha
		tb_assert_and_check_return_val(pixfmt != G2_PIXFMT_NONE && (pixfmt - 1) < tb_arrayn(g_pixmaps_alpha), TB_NULL);
		return g_pixmaps_alpha[pixfmt - 1];
	}

	// transparent
	return TB_NULL;
}

