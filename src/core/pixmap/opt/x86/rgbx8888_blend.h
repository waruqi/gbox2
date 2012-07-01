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
 * @file		rgbx8888_blend.h
 *
 */
#ifndef G2_CORE_PIXMAP_OPT_x86_RGBX8888_BLEND_H
#define G2_CORE_PIXMAP_OPT_x86_RGBX8888_BLEND_H

/* ///////////////////////////////////////////////////////////////////////
 * includes
 */
#include "prefix.h"
#include "xrgb8888_blend.h"

/* ///////////////////////////////////////////////////////////////////////
 * macros
 */

#if defined(TB_CONFIG_ASSEMBLER_GAS)
//# 	define g2_pixmap_rgbx8888_blend(d, s, a) 		g2_pixmap_xrgb8888_blend_asm(d, s, a)
//# 	define g2_pixmap_rgbx8888_blend2(d, hs, ls, a) 	g2_pixmap_xrgb8888_blend2_asm(d, hs, ls, a)
#endif

/* ///////////////////////////////////////////////////////////////////////
 * implementation
 */


#endif

