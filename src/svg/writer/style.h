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
#ifndef G2_SVG_WRITER_STYLE_H
#define G2_SVG_WRITER_STYLE_H

/* ///////////////////////////////////////////////////////////////////////
 * includes
 */
#include "prefix.h"

/* ///////////////////////////////////////////////////////////////////////
 * inlines
 */

static __tb_inline__ tb_void_t g2_svg_writer_style(tb_gstream_t* gst, tb_handle_t style)
{
	// check
	tb_assert(gst && style);

	// mode
	tb_size_t mode = g2_style_mode(style);

	// color
	union __g2_c2p_t
	{
		g2_color_t c;
		g2_pixel_t p;

	}c2p;
	c2p.c = g2_style_color(style);

	// fill?
	if (mode & G2_STYLE_MODE_FILL)
	{
		// is not black? fill it
		if (c2p.p != 0xff000000)
			tb_gstream_printf(gst, " fill=\"#%06x\"", c2p.c.a != 0xff? c2p.p : (c2p.p & 0x00ffffff));
	}

	// stroke?
	if (mode & G2_STYLE_MODE_STROKE)
	{
		// is not black? fill it
		if (c2p.p != 0xff000000)
			tb_gstream_printf(gst, " stroke=\"#%06x\"", c2p.c.a != 0xff? c2p.p : (c2p.p & 0x00ffffff));
	}
}

#endif


