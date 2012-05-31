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
#ifndef G2_CORE_SKIA_PIXFMT_H
#define G2_CORE_SKIA_PIXFMT_H

/* /////////////////////////////////////////////////////////
 * includes
 */
#include "prefix.h"

/* /////////////////////////////////////////////////////////
 * inlines
 */
static __tb_inline__ SkBitmap::Config g2_skia_pixfmt(tb_size_t pixfmt)
{
#if 0
	typedef enum __g2_pixfmt_t
	{
		G2_PIXFMT_NONE 			= 0		
	, 	G2_PIXFMT_PAL8 			= 1		//!< 8-bit palette
	, 	G2_PIXFMT_ARGB1555		= 2		//!< 16-bit a r g b: 1 5 5 5 a: 10000000 r: 11111000 g: 11111000 b: 11111000
	, 	G2_PIXFMT_XRGB1555		= 3		//!< 16-bit x r g b: 1 5 5 5 x: 10000000 r: 11111000 g: 11111000 b: 11111000
	, 	G2_PIXFMT_RGB565		= 4		//!< 16-bit r g b: 5 6 5 r: 11111000 g: 11111100 b: 11111000
	, 	G2_PIXFMT_RGB888		= 5		//!< 24-bit r g b: 8 8 8
	, 	G2_PIXFMT_ARGB8888		= 6		//!< 32-bit a r g b: 8 8 8 8
	, 	G2_PIXFMT_XRGB8888		= 7		//!< 32-bit x r g b: 8 8 8 8
	, 	G2_PIXFMT_ARGB4444		= 8		//!< 32-bit a r g b: 4 4 4 4
	, 	G2_PIXFMT_XRGB4444		= 9		//!< 32-bit x r g b: 4 4 4 4

	, 	G2_PIXFMT_ABGR1555		= 10	//!< 16-bit a b g r: 1 5 5 5 a: 10000000 b: 11111000 g: 11111000 r: 11111000
	, 	G2_PIXFMT_XBGR1555		= 11	//!< 16-bit x b g r: 1 5 5 5 x: 10000000 b: 11111000 g: 11111000 r: 11111000
	, 	G2_PIXFMT_BGR565		= 12	//!< 16-bit b g r: 5 6 5 b: 11111000 g: 11111100 r: 11111000
	, 	G2_PIXFMT_BGR888		= 13	//!< 24-bit b g r: 8 8 8
	, 	G2_PIXFMT_ABGR8888		= 14	//!< 32-bit a b g r: 8 8 8 8
	, 	G2_PIXFMT_XBGR8888		= 15	//!< 32-bit x b g r: 8 8 8 8
	, 	G2_PIXFMT_ABGR4444		= 16	//!< 32-bit a b g r: 4 4 4 4
	, 	G2_PIXFMT_XBGR4444		= 17	//!< 32-bit x b g r: 4 4 4 4

	}g2_pixfmt_t;
#endif

	static SkBitmap::Config const spixfmts[] =
	{
		SkBitmap::kNo_Config
	, 	SkBitmap::kNo_Config
	, 	SkBitmap::kNo_Config
	, 	SkBitmap::kNo_Config
	, 	SkBitmap::kRGB_565_Config
	, 	SkBitmap::kNo_Config
	, 	SkBitmap::kARGB_8888_Config
	, 	SkBitmap::kARGB_8888_Config
	, 	SkBitmap::kARGB_4444_Config
	, 	SkBitmap::kARGB_4444_Config

	, 	SkBitmap::kNo_Config
	, 	SkBitmap::kNo_Config
	, 	SkBitmap::kNo_Config
	, 	SkBitmap::kNo_Config
	, 	SkBitmap::kNo_Config
	, 	SkBitmap::kNo_Config
	, 	SkBitmap::kNo_Config
	, 	SkBitmap::kNo_Config
	};
	return spixfmts[pixfmt];
}

#endif


