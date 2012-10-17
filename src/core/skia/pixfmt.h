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

/* ///////////////////////////////////////////////////////////////////////
 * includes
 */
#include "prefix.h"

/* ///////////////////////////////////////////////////////////////////////
 * inlines
 */

// g2 pixfmt => skia pixfmt
static __tb_inline__ SkBitmap::Config g2_pixfmt_to_skia(tb_size_t pixfmt)
{
#if 0
	typedef enum __g2_pixfmt_t
	{
		G2_PIXFMT_NONE 			= 0		
	, 	G2_PIXFMT_PAL8 			= 1		//!< 8-bit palette
	, 	G2_PIXFMT_RGB565		= 2		//!< 16-bit r g b: 5 6 5 r: 11111000 g: 11111100 b: 11111000
	, 	G2_PIXFMT_RGB888		= 3		//!< 24-bit r g b: 8 8 8
	, 	G2_PIXFMT_ARGB1555		= 4		//!< 16-bit a r g b: 1 5 5 5 a: 10000000 r: 11111000 g: 11111000 b: 11111000
	, 	G2_PIXFMT_XRGB1555		= 5		//!< 16-bit x r g b: 1 5 5 5 x: 10000000 r: 11111000 g: 11111000 b: 11111000
	, 	G2_PIXFMT_ARGB4444		= 6		//!< 16-bit a r g b: 4 4 4 4
	, 	G2_PIXFMT_XRGB4444		= 7		//!< 16-bit x r g b: 4 4 4 4
	, 	G2_PIXFMT_ARGB8888		= 8		//!< 32-bit a r g b: 8 8 8 8
	, 	G2_PIXFMT_XRGB8888		= 9		//!< 32-bit x r g b: 8 8 8 8
	, 	G2_PIXFMT_RGBA5551		= 10	//!< 16-bit r g b a: 5 5 5 1 r: 11111000 g: 11111000 b: 11111000 a: 10000000
	, 	G2_PIXFMT_RGBX5551		= 11	//!< 16-bit r g b x: 5 5 5 1 r: 11111000 g: 11111000 b: 11111000 x: 10000000
	, 	G2_PIXFMT_RGBA4444		= 12	//!< 16-bit r g b a: 4 4 4 4
	, 	G2_PIXFMT_RGBX4444		= 13	//!< 16-bit r g b x: 4 4 4 4
	, 	G2_PIXFMT_RGBA8888		= 14	//!< 32-bit r g b a: 8 8 8 8
	, 	G2_PIXFMT_RGBX8888		= 15	//!< 32-bit r g b x: 8 8 8 8

	, 	G2_PIXFMT_BGR565		= 16	//!< 16-bit b g r: 5 6 5 b: 11111000 g: 11111100 r: 11111000
	, 	G2_PIXFMT_BGR888		= 17	//!< 24-bit b g r: 8 8 8
	, 	G2_PIXFMT_ABGR1555		= 18	//!< 16-bit a b g r: 1 5 5 5 a: 10000000 b: 11111000 g: 11111000 r: 11111000
	, 	G2_PIXFMT_XBGR1555		= 19	//!< 16-bit x b g r: 1 5 5 5 x: 10000000 b: 11111000 g: 11111000 r: 11111000
	, 	G2_PIXFMT_ABGR4444		= 20	//!< 16-bit a b g r: 4 4 4 4
	, 	G2_PIXFMT_XBGR4444		= 21 	//!< 16-bit x b g r: 4 4 4 4
	, 	G2_PIXFMT_ABGR8888		= 22	//!< 32-bit a b g r: 8 8 8 8
	, 	G2_PIXFMT_XBGR8888		= 23	//!< 32-bit x b g r: 8 8 8 8
	, 	G2_PIXFMT_BGRA5551		= 24	//!< 16-bit b g r a: 5 5 5 1 b: 11111000 g: 11111000 r: 11111000 a: 10000000 
	, 	G2_PIXFMT_BGRX5551		= 25	//!< 16-bit b g r x: 5 5 5 1 b: 11111000 g: 11111000 r: 11111000 x: 10000000
	, 	G2_PIXFMT_BGRA4444		= 26	//!< 16-bit b g r a: 4 4 4 4
	, 	G2_PIXFMT_BGRX4444		= 27	//!< 16-bit b g r x: 4 4 4 4
	, 	G2_PIXFMT_BGRA8888		= 28	//!< 32-bit b g r a: 8 8 8 8
	, 	G2_PIXFMT_BGRX8888		= 29	//!< 32-bit b g r x: 8 8 8 8

	}g2_pixfmt_t;
#endif

	static SkBitmap::Config const spixfmts[] =
	{
		SkBitmap::kNo_Config
	, 	SkBitmap::kNo_Config

	, 	SkBitmap::kRGB_565_Config
	, 	SkBitmap::kNo_Config
	, 	SkBitmap::kNo_Config
	, 	SkBitmap::kNo_Config
	, 	SkBitmap::kARGB_4444_Config
	, 	SkBitmap::kARGB_4444_Config
	, 	SkBitmap::kARGB_8888_Config
	, 	SkBitmap::kARGB_8888_Config
	, 	SkBitmap::kNo_Config
	, 	SkBitmap::kNo_Config
	, 	SkBitmap::kNo_Config
	, 	SkBitmap::kNo_Config
	, 	SkBitmap::kNo_Config
	, 	SkBitmap::kNo_Config

	, 	SkBitmap::kNo_Config
	, 	SkBitmap::kNo_Config
	, 	SkBitmap::kNo_Config
	, 	SkBitmap::kNo_Config
	, 	SkBitmap::kNo_Config
	, 	SkBitmap::kNo_Config
	, 	SkBitmap::kNo_Config
	, 	SkBitmap::kNo_Config
	, 	SkBitmap::kNo_Config
	, 	SkBitmap::kNo_Config
	, 	SkBitmap::kNo_Config
	, 	SkBitmap::kNo_Config
	, 	SkBitmap::kNo_Config
	, 	SkBitmap::kNo_Config

	};

	pixfmt &= ~G2_PIXFMT_MENDIAN;
	tb_assert_and_check_return_val(pixfmt < tb_arrayn(spixfmts), SkBitmap::kNo_Config);
	return spixfmts[pixfmt];
}

// skia pixfmt => g2 pixfmt
static __tb_inline__ tb_size_t g2_pixfmt_from_skia(SkBitmap::Config pixfmt)
{
#if 0
	enum Config 
	{
		kNo_Config 			//!< bitmap has not been configured
	,	kA1_Config
	,	kA8_Config 			//!< 8-bits per pixel, with only alpha specified (0 is transparent, 0xFF is opaque)
	,	kIndex8_Config 		//!< 8-bits per pixel, using SkColorTable to specify the colors
	,	kRGB_565_Config 	//!< 16-bits per pixel, (see SkColorPriv.h for packing)
	,	kARGB_4444_Config 	//!< 16-bits per pixel, (see SkColorPriv.h for packing)
	,	kARGB_8888_Config 	//!< 32-bits per pixel, (see SkColorPriv.h for packing)
	,	kRLE_Index8_Config
	,	kConfigCount
	};
#endif

	static tb_size_t const spixfmts[] =
	{
		G2_PIXFMT_NONE
	, 	G2_PIXFMT_NONE
	, 	G2_PIXFMT_NONE
	, 	G2_PIXFMT_PAL8
	, 	G2_PIXFMT_RGB565
	, 	G2_PIXFMT_ARGB4444
	, 	G2_PIXFMT_ARGB8888
	, 	G2_PIXFMT_NONE
	};
	tb_assert_and_check_return_val(static_cast<tb_size_t>(pixfmt) < tb_arrayn(spixfmts), G2_PIXFMT_NONE);
	return spixfmts[static_cast<tb_size_t>(pixfmt)] | G2_PIXFMT_NENDIAN;
}

#endif


