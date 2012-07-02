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
 * @file		pixfmt.h
 *
 */
#ifndef G2_PREFIX_PIXFMT_H
#define G2_PREFIX_PIXFMT_H

/* ///////////////////////////////////////////////////////////////////////
 * includes
 */
#include "config.h"

/* ///////////////////////////////////////////////////////////////////////
 * macros
 */

// argb => pixel
#define G2_ARGB_1555(a, r, g, b) 	((((a) << 8) & 0x8000) | (((r) << 7) & 0x7c00) | (((g) << 2) & 0x3e0) | (((b) >> 3)))
#define G2_XRGB_1555(r, g, b) 		((0x8000) | (((r) << 7) & 0x7c00) | (((g) << 2) & 0x3e0) | (((b) >> 3)))
#define G2_RGB_565(r, g, b) 		((((r) << 8) & 0xf800) | (((g) << 3) & 0x7e0) | (((b) >> 3)))
#define G2_RGB_888(r, g, b) 		((b) | ((g) << 8) | ((r) << 16))
#define G2_ARGB_8888(a, r, g, b) 	((b) | ((g) << 8) | ((r) << 16) | ((a) << 24))
#define G2_XRGB_8888(r, g, b) 		((b) | ((g) << 8) | ((r) << 16) | ((0xff) << 24))
#define G2_RGBA_8888(r, g, b, a) 	((a) | ((b) << 8) | ((g) << 16) | ((r) << 24))
#define G2_RGBX_8888(r, g, b) 		(0xff | ((b) << 8) | ((g) << 16) | ((r) << 24))

// pixel => a r g b
#define G2_RGB_565_R(c) 			(((c) >> 8) & 0x00f8)
#define G2_RGB_565_G(c) 			(((c) >> 3) & 0x00fc)
#define G2_RGB_565_B(c) 			(((c) << 3) & 0x00f8)
	
#define G2_RGB_888_R(c) 			(((c) >> 16) & 0xff)
#define G2_RGB_888_G(c) 			(((c) >> 8) & 0xff)
#define G2_RGB_888_B(c) 			((c) & 0xff)

#define G2_ARGB_1555_R(c) 			(((c) >> 7) & 0x00f8)
#define G2_ARGB_1555_G(c) 			(((c) >> 2) & 0x00f8)
#define G2_ARGB_1555_B(c) 			(((c) << 3) & 0x00f8)
#define G2_ARGB_1555_A(c) 			(((c) >> 8) & 0x0001)

#define G2_XRGB_1555_R(c) 			(((c) >> 7) & 0x00f8)
#define G2_XRGB_1555_G(c) 			(((c) >> 2) & 0x00f8)
#define G2_XRGB_1555_B(c) 			(((c) << 3) & 0x00f8)

#define G2_ARGB_8888_R(c) 			(((c) >> 16) & 0xff)
#define G2_ARGB_8888_G(c) 			(((c) >> 8) & 0xff)
#define G2_ARGB_8888_B(c) 			((c) & 0xff)
#define G2_ARGB_8888_A(c) 			(((c) >> 24) & 0xff)

#define G2_RGBA_8888_R(c) 			(((c) >> 24) & 0xff)
#define G2_RGBA_8888_G(c) 			(((c) >> 16) & 0xff)
#define G2_RGBA_8888_B(c) 			(((c) >> 8) & 0xff)
#define G2_RGBA_8888_A(c) 			((c) & 0xff)

#define G2_XRGB_8888_R(c) 			(((c) >> 16) & 0xff)
#define G2_XRGB_8888_G(c) 			(((c) >> 8) & 0xff)
#define G2_XRGB_8888_B(c) 			((c) & 0xff)

#define G2_RGBX_8888_R(c) 			(((c) >> 24) & 0xff)
#define G2_RGBX_8888_G(c) 			(((c) >> 16) & 0xff)
#define G2_RGBX_8888_B(c) 			(((c) >> 8) & 0xff)

/* ///////////////////////////////////////////////////////////////////////
 * types
 */

/// the pixel format type
typedef enum __g2_pixfmt_t
{
 	G2_PIXFMT_NONE 			= 0		
, 	G2_PIXFMT_PAL8 			= 1		//!< 8-bit palette
, 	G2_PIXFMT_RGB565		= 2		//!< 16-bit r g b: 5 6 5 r: 11111000 g: 11111100 b: 11111000
, 	G2_PIXFMT_RGB888		= 3		//!< 24-bit r g b: 8 8 8
, 	G2_PIXFMT_ARGB1555		= 4		//!< 16-bit a r g b: 1 5 5 5 a: 10000000 r: 11111000 g: 11111000 b: 11111000
, 	G2_PIXFMT_XRGB1555		= 5		//!< 16-bit x r g b: 1 5 5 5 x: 10000000 r: 11111000 g: 11111000 b: 11111000
, 	G2_PIXFMT_ARGB8888		= 6		//!< 32-bit a r g b: 8 8 8 8
, 	G2_PIXFMT_XRGB8888		= 7		//!< 32-bit x r g b: 8 8 8 8
, 	G2_PIXFMT_ARGB4444		= 8		//!< 32-bit a r g b: 4 4 4 4
, 	G2_PIXFMT_XRGB4444		= 9		//!< 32-bit x r g b: 4 4 4 4
, 	G2_PIXFMT_RGBA8888		= 10	//!< 32-bit r g b a: 8 8 8 8
, 	G2_PIXFMT_RGBX8888		= 11	//!< 32-bit r g b x: 8 8 8 8
, 	G2_PIXFMT_RGBA4444		= 12	//!< 32-bit r g b a: 4 4 4 4
, 	G2_PIXFMT_RGBX4444		= 13	//!< 32-bit r g b x: 4 4 4 4

, 	G2_PIXFMT_BGR565		= 14	//!< 16-bit b g r: 5 6 5 b: 11111000 g: 11111100 r: 11111000
, 	G2_PIXFMT_BGR888		= 15	//!< 24-bit b g r: 8 8 8
, 	G2_PIXFMT_ABGR1555		= 16	//!< 16-bit a b g r: 1 5 5 5 a: 10000000 b: 11111000 g: 11111000 r: 11111000
, 	G2_PIXFMT_XBGR1555		= 17	//!< 16-bit x b g r: 1 5 5 5 x: 10000000 b: 11111000 g: 11111000 r: 11111000
, 	G2_PIXFMT_ABGR8888		= 18	//!< 32-bit a b g r: 8 8 8 8
, 	G2_PIXFMT_XBGR8888		= 19	//!< 32-bit x b g r: 8 8 8 8
, 	G2_PIXFMT_ABGR4444		= 20	//!< 32-bit a b g r: 4 4 4 4
, 	G2_PIXFMT_XBGR4444		= 21	//!< 32-bit x b g r: 4 4 4 4
, 	G2_PIXFMT_BGRA8888		= 22	//!< 32-bit b g r a: 8 8 8 8
, 	G2_PIXFMT_BGRX8888		= 23	//!< 32-bit b g r x: 8 8 8 8
, 	G2_PIXFMT_BGRA4444		= 24	//!< 32-bit b g r a: 4 4 4 4
, 	G2_PIXFMT_BGRX4444		= 25	//!< 32-bit b g r x: 4 4 4 4

	// big endian or little endian for storing the data
, 	G2_PIXFMT_LE 			= 0x0100
, 	G2_PIXFMT_BE 			= 0x0200
, 	G2_PIXFMT_NE 			= 0x0300
, 	G2_PIXFMT_MK 			= 0xFF00

}g2_pixfmt_t;


#endif


