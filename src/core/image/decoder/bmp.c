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
 * @file		bmp.c
 *
 */

/* ///////////////////////////////////////////////////////////////////////
 * trace
 */
#define TB_TRACE_IMPL_TAG 				"bmp"

/* /////////////////////////////////////////////////////////
 * includes
 */
#include "bmp.h"

/* ////////////////////////////////////////////////////////////////////////
 * macros
 */

#define G2_BMP_OFFSET_BPP 	 			(28) 	// bpp
#define G2_BMP_OFFSET_IMAGE_SIZE 		(34) 	// bmp size
#define G2_BMP_OFFSET_PALETTE 	 		(54) 	// palette

// bmp compression flag
#define G2_BMP_RGB 						(0)
#define G2_BMP_RLE8 					(1)
#define G2_BMP_RLE4 					(2)
#define G2_BMP_BITFIELDS 				(3)

/*!the bmp format
 *
 * @code
 *
 * typedef struct __g2_bmp_t
 * {
 * 		g2_bmp_file_header_t 	header;
 * 		g2_bmp_info_t 			info;
 *	
 * }g2_image_t;
 *
 * typedef struct __g2_bmp_file_header_t
 * {
 * 		tb_uint16_t 			type; 				//!< bmp_id == 0x4D42("BM")
 * 		tb_uint32_t 			size; 
 * 		tb_uint16_t 			reserved1; 
 * 		tb_uint16_t 			reserved2; 
 * 		tb_uint32_t 			offset_bits; 
 *
 * }g2_bmp_file_header_t;
 *	
 * typedef struct __g2_bmp_info_t
 * {
 * 		g2_bmp_info_header_t    header;
 * 		g2_bmp_rgb_t 			colors[1];
 *
 * }g2_bmp_info_t;
 *
 * typedef struct __g2_bmp_info_header_t
 * {
 * 		tb_uint32_t 			size; 				//!< sizeof(g2_bmp_info_header_t) 
 * 		tb_int32_t 				w; 					// width 
 * 		tb_int32_t 				h; 					// height
 * 		tb_uint16_t 			planes; 
 * 		tb_uint16_t 			bpp; 				// bst per pixels
 * 		tb_uint32_t 			compression; 		// G2_BMP_RGB, G2_BMP_RLE4, G2_BMP_RLE8, G2_BMP_BITFIELDS 
 * 		tb_uint32_t 			image_size; 		// image size for G2_BMP_RGB 
 * 		tb_int32_t 				x_pels_per_meter; 
 * 		tb_int32_t 				y_pels_per_meter; 
 * 		tb_uint32_t 			clr_used; 
 * 		tb_uint32_t 			clr_important; 
 *
 * }g2_bmp_info_header_t; 
 * 
 * typedef struct __g2_bmp_rgb_t 
 * {
 * 		tb_byte_t   			 b;
 * 		tb_byte_t   			 g;
 * 		tb_byte_t   			 r;
 * 		tb_byte_t   			 reserved;
 *
 * }g2_bmp_rgb_t;
 *
 * @endcode
 */

/* /////////////////////////////////////////////////////////
 * implementation
 */
static tb_bool_t g2_bmp_decoder_probe(tb_gstream_t* gst)
{
	// need
	tb_byte_t* p = TB_NULL;
	if (!tb_gstream_bneed(gst, &p, 2)) return TB_FALSE;
	tb_assert_and_check_return_val(p, TB_FALSE);

	// ok?
	return (p[0] == 'B' && p[1] == 'M')? TB_TRUE : TB_FALSE;
}

/* /////////////////////////////////////////////////////////
 * interfaces
 */
g2_image_decoder_t* g2_bmp_decoder_init(tb_size_t pixfmt, tb_gstream_t* gst)
{
	tb_assert_and_check_return_val(pixfmt != G2_PIXFMT_NONE && gst, TB_NULL);

	// probe it
	if (!g2_bmp_decoder_probe(gst)) return TB_NULL;

	// width & height
	tb_gstream_bskip(gst, 18);
	tb_size_t width = tb_gstream_bread_u32_le(gst);
	tb_size_t height = tb_gstream_bread_u32_le(gst);
	tb_assert_and_check_return_val(width && height, TB_NULL);

	// bpp
	tb_gstream_bskip(gst, 2);
	tb_size_t bpp = tb_gstream_bread_u16_le(gst);
	tb_assert_and_check_return_val(bpp, TB_NULL);
	tb_trace_impl("size: %lux%lu, bpp: %lu", width, height, bpp);

	// compression? not support 
	tb_size_t bc = tb_gstream_bread_u32_le(gst);
	tb_assert_and_check_return_val(bc != G2_BMP_RLE4 && bc != G2_BMP_RLE8);

	return TB_NULL;
}
