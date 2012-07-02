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

/* ///////////////////////////////////////////////////////////////////////
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

/* ///////////////////////////////////////////////////////////////////////
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
static tb_handle_t g2_bmp_decoder_done(g2_image_decoder_t* decoder)
{
	tb_assert_and_check_return_val(decoder && decoder->type == G2_IMAGE_TYPE_BMP, TB_NULL);

	// the pixfmt
	tb_size_t pixfmt 	= decoder->pixfmt;
	tb_assert_and_check_return_val(G2_PIXFMT_OK(pixfmt), TB_NULL);

	// the width & height
	tb_size_t width 	= decoder->width;
	tb_size_t height 	= decoder->height;
	tb_assert_and_check_return_val(width & height, TB_NULL);

	// the stream
	tb_gstream_t* gst 	= decoder->gst;
	tb_assert_and_check_return_val(gst, TB_NULL);

	// the file size
	tb_hize_t filesize 	= tb_gstream_size(gst);
	tb_assert_and_check_return_val(filesize, TB_NULL);

	// bpp
	if (!tb_gstream_bskip(gst, 2)) return TB_NULL;
	tb_size_t bpp = tb_gstream_bread_u16_le(gst);
	tb_assert_and_check_return_val(bpp, TB_NULL);
	tb_trace_impl("size: %lux%lu, bpp: %lu", width, height, bpp);

	// compression? not support 
	tb_size_t bc = tb_gstream_bread_u32_le(gst);
	tb_assert_and_check_return_val(bc != G2_BMP_RLE4 && bc != G2_BMP_RLE8, TB_NULL);

	// linesize & datasize
	tb_size_t linesize = (width * bpp) >> 3;
	tb_size_t datasize = tb_gstream_bread_u32_le(gst);
	if (!datasize) datasize = tb_align4(linesize) * height;
	tb_trace_impl("data: %lu bytes", datasize);
	tb_assert_and_check_return_val(datasize && datasize < filesize, TB_NULL);

	// has pal?
	g2_color_t 	pals[256];
	tb_size_t 	paln = 1 << bpp;
	if (bpp <= 8)
	{
#if 0
		// the palette count
		if (!tb_gstream_bskip(gst, 8)) return TB_NULL;
		paln = tb_gstream_bread_u32_le(gst);
		if (!tb_gstream_bskip(gst, 4)) return TB_NULL;
#else
		if (!tb_gstream_bskip(gst, 16)) return TB_NULL;
#endif
		tb_trace_impl("pal: %lu", paln);

		// the palette entries
		tb_size_t i = 0;
		for (i = 0; i < paln; i++)
		{
			pals[i].b = tb_gstream_bread_u8(gst);
			pals[i].g = tb_gstream_bread_u8(gst);
			pals[i].r = tb_gstream_bread_u8(gst);
			if (!tb_gstream_bskip(gst, 1)) return TB_NULL;
			pals[i].a = 0xff;
		}
	}

	// the pixfmt
	g2_pixmap_t* sp = TB_NULL;
	g2_pixmap_t* dp = g2_pixmap(pixfmt, 0xff);
	if (bc == G2_BMP_BITFIELDS)
	{
		// the color mask
		if (!tb_gstream_bskip(gst, 16)) return TB_NULL;
		tb_size_t rm = tb_gstream_bread_u32_le(gst);
		tb_size_t gm = tb_gstream_bread_u32_le(gst);
		tb_size_t bm = tb_gstream_bread_u32_le(gst);

		if (bpp == 16)
		{
			if (rm == 0xf800 && gm == 0x07e0 && bm == 0x001f)
				sp = g2_pixmap(G2_PIXFMT_RGB565 | G2_PIXFMT_LENDIAN, 0xff);
			else if (rm == 0x7c00 && gm == 0x03e0 && bm == 0x001f)
				sp = g2_pixmap(G2_PIXFMT_XRGB1555 | G2_PIXFMT_LENDIAN, 0xff);
		}
		else if (bpp == 32)
		{
			if (rm == 0xff000000 && gm == 0xff0000 && bm == 0xff00)
				sp = g2_pixmap(G2_PIXFMT_RGBX8888 | G2_PIXFMT_LENDIAN, 0xff);
		}
	}
	else if (bc == G2_BMP_RGB)
	{
		switch (bpp)
		{
		case 32:
			sp = g2_pixmap(G2_PIXFMT_ARGB8888 | G2_PIXFMT_LENDIAN, 0xff);
			break;
		case 24:
			sp = g2_pixmap(G2_PIXFMT_RGB888 | G2_PIXFMT_LENDIAN, 0xff);
			break;
		case 16:
			sp = g2_pixmap(G2_PIXFMT_XRGB1555 | G2_PIXFMT_LENDIAN, 0xff);
			break;
		case 8:
		case 4:
		case 1:
			sp = g2_pixmap(G2_PIXFMT_PAL8 | G2_PIXFMT_LENDIAN, 0xff);
			break;
		default:
			tb_trace_impl("the bpp: %lu is not supported", bpp);
			return TB_NULL;
		}
	}
	tb_assert_and_check_return_val(sp && dp, TB_NULL);
	tb_trace_impl("pixfmt: %s => %s", sp->name, dp->name);

	// goto the bmp data 
	if (!tb_gstream_bseek(gst, filesize - datasize)) return TB_NULL;

	// init bitmap
	tb_handle_t bitmap = g2_bitmap_init(pixfmt, width, height);
	tb_assert_and_check_return_val(bitmap, TB_NULL);

	// make bitmap
	tb_byte_t* data = g2_bitmap_make(bitmap);
	tb_assert_and_check_goto(data, fail);

	// init
	tb_size_t 	b = dp->btp;
	tb_size_t 	t = sp->btp;
	tb_size_t 	r = tb_align4(linesize);
	tb_size_t 	n = g2_bitmap_line(bitmap);
	tb_byte_t* 	p = data + (height - 1) * n;
	tb_byte_t 	l[8192];
	tb_assert_and_check_goto(r <= 8192, fail);

	// the bitmap data
	if (bpp > 8)
	{
		// walk
		while (height--)
		{
			// read line
			if (!tb_gstream_bread(gst, l, r)) goto fail;
			
			// save image data
			tb_byte_t* 	d = p;
			tb_size_t 	i = 0;
			if (sp == dp)
			{
				for (i = 0; i < linesize; i += t, d += b)
					dp->pixel_cpy(d, l + i, 0xff);
			}
			else
			{
				for (i = 0; i < linesize; i += t, d += b)
					dp->color_set(d, sp->color_get(l + i));
			}

			// next line
			p -= n;
		}
	}
	else if (bpp == 8)
	{
		// walk
		while (height--)
		{
			// read line
			if (!tb_gstream_bread(gst, l, r)) goto fail;
			
			// save image data
			tb_byte_t* 	d = p;
			tb_size_t 	i = 0;
			for (i = 0; i < linesize; i++, d += b)
				dp->color_set(d, pals[l[i]]);

			// next line
			p -= n;
		}
	}	
	else
	{
		// walk
		while (height--)
		{
			// read line
			if (!tb_gstream_bread(gst, l, r)) goto fail;
			
			// save image data
			tb_byte_t* 	d = p;
			tb_size_t 	i = 0;
			tb_size_t 	m = (linesize << 3) / bpp;
			for (i = 0; i < m; i += bpp, d += b)
				dp->color_set(d, pals[tb_bits_get_ubits32(&l[i / 8], i & 7, bpp)]);

			// next line
			p -= n;
		}
	}

	// ok
	return bitmap;

fail:
	if (bitmap) g2_bitmap_exit(bitmap);
	return TB_NULL;
}
/* ///////////////////////////////////////////////////////////////////////
 * interfaces
 */
g2_image_decoder_t* g2_bmp_decoder_init(tb_size_t pixfmt, tb_gstream_t* gst)
{
	tb_assert_and_check_return_val(G2_PIXFMT_OK(pixfmt) && gst, TB_NULL);

	// probe it
	if (!g2_bmp_decoder_probe(gst)) return TB_NULL;

	// width & height
	if (!tb_gstream_bskip(gst, 18)) return TB_NULL;
	tb_size_t width = tb_gstream_bread_u32_le(gst);
	tb_size_t height = tb_gstream_bread_u32_le(gst);
	tb_assert_and_check_return_val(width && height, TB_NULL);

	// alloc decoder
	g2_bmp_decoder_t* decoder = tb_malloc0(sizeof(g2_bmp_decoder_t));
	tb_assert_and_check_return_val(decoder, TB_NULL);

	// init decoder
	decoder->base.type 		= G2_IMAGE_TYPE_BMP;
	decoder->base.gst 		= gst;
	decoder->base.pixfmt 	= pixfmt;
	decoder->base.width 	= width;
	decoder->base.height 	= height;
	decoder->base.done 		= g2_bmp_decoder_done;

	// ok
	return (g2_image_decoder_t*)decoder;
}
