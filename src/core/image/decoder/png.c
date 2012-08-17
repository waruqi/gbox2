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
 * @file		png.c
 *
 */

/* ///////////////////////////////////////////////////////////////////////
 * trace
 */
#define TB_TRACE_IMPL_TAG 				"png"

/* ///////////////////////////////////////////////////////////////////////
 * includes
 */
#include "png.h"
#include "decoder.h"
#include "../../../gbox2.h"
#include "../../../third/png/png.h"

/* ///////////////////////////////////////////////////////////////////////
 * types
 */
// the png decoder type
typedef struct __g2_png_decoder_t
{
	// the base
	g2_image_decoder_t 				base;

	// the png 
	png_structp 					png;

	// the info
	png_infop 						info;
	
	// the bit depth
	tb_int_t 						bit_depth;

	// the color type
	tb_int_t 						color_type;

	// the interlace type
	tb_int_t 						interlace_type;

}g2_png_decoder_t;

/* ///////////////////////////////////////////////////////////////////////
 * implementation
 */
static tb_void_t g2_png_decoder_error(png_structp png, png_const_charp msg)
{
	tb_trace_impl("error: %s", msg);
	longjmp(png_jmpbuf(png), 1);
}
static tb_void_t g2_png_decoder_reader(png_structp png, png_bytep data, png_size_t size)
{
	tb_gstream_t* gst = (tb_gstream_t*)png_get_io_ptr(png);
	tb_assert_and_check_return(gst && size <= tb_gstream_left(gst));
	
	// read it
	tb_bool_t ok = tb_gstream_bread(gst, data, size);
	tb_assert(ok);
}
static tb_bool_t g2_png_decoder_probe(tb_gstream_t* gst)
{
	// need
	tb_byte_t* p = TB_NULL;
	if (!tb_gstream_bneed(gst, &p, 8)) return TB_FALSE;
	tb_assert_and_check_return_val(p, TB_FALSE);

	// ok?
	return ( 	p[0] == 0x89 
			&& 	p[1] == 'P'
			&& 	p[2] == 'N' 
			&& 	p[3] == 'G'
			&& 	p[4] == 0x0d
			&& 	p[5] == 0x0a
			&& 	p[6] == 0x1a
			&& 	p[7] == 0x0a)? TB_TRUE : TB_FALSE;
}
static tb_handle_t g2_png_decoder_done(g2_image_decoder_t* decoder)
{
	// check
	tb_assert_and_check_return_val(decoder && decoder->type == G2_IMAGE_TYPE_PNG, TB_NULL);

	// decoder
	g2_png_decoder_t* pdecoder = (g2_png_decoder_t*)decoder;

	// the pixfmt
	tb_size_t pixfmt 	= decoder->pixfmt;
	tb_assert_and_check_return_val(G2_PIXFMT_OK(pixfmt), TB_NULL);

	// the pixmap
	g2_pixmap_t* dpixmap = g2_pixmap(pixfmt, 0xff);
	g2_pixmap_t* spixmap = g2_pixmap(G2_PIXFMT_ARGB8888 | G2_PIXFMT_LENDIAN, 0xff);
	tb_assert_and_check_return_val(dpixmap && spixmap, TB_NULL);

	// the width & height
	tb_size_t width 	= decoder->width;
	tb_size_t height 	= decoder->height;
	tb_assert_and_check_return_val(width & height, TB_NULL);

	// init bitmap
	tb_handle_t bitmap = g2_bitmap_init(pixfmt, width, height, 0);
	tb_assert_and_check_return_val(bitmap, TB_NULL);

	// make bitmap
	tb_byte_t* data = g2_bitmap_make(bitmap);
	tb_assert_and_check_goto(data, fail);

	// set error handling if you are using the setjmp/longjmp method (this is
	// the normal method of doing things with libpng).  required unless you
	// set up your own error handlers in the png_create_read_struct() earlier.
	if (setjmp(png_jmpbuf(pdecoder->png))) goto fail;
	
	// tell libpng to strip 16 bit/color files down to 8 bits/color 
	if (pdecoder->bit_depth == 16) png_set_strip_16(pdecoder->png);

	// extract multiple pixels with bit depths of 1, 2, and 4 from a single
	// byte into separate bytes (useful for paletted and grayscale images)
	if (pdecoder->bit_depth < 8) png_set_packing(pdecoder->png);

	// expand grayscale images to the full 8 bits from 1, 2, or 4 bits/pixel
	if (pdecoder->color_type == PNG_COLOR_TYPE_GRAY && pdecoder->bit_depth < 8)
		png_set_expand_gray_1_2_4_to_8(pdecoder->png);

    // make a grayscale image into rgb. 
    if (pdecoder->color_type == PNG_COLOR_TYPE_GRAY || pdecoder->color_type == PNG_COLOR_TYPE_GRAY_ALPHA)
        png_set_gray_to_rgb(pdecoder->png);

	// expand paletted or rgb images with transparency to full alpha channels
	// so the data will be available as RGBA quartets.
	if (png_get_valid(pdecoder->png, pdecoder->info, PNG_INFO_tRNS))
		png_set_tRNS_to_alpha(pdecoder->png);

	// flip the rgb pixels to bgr (or rgba to bgra)
	if (pdecoder->color_type & PNG_COLOR_MASK_COLOR)
 		png_set_bgr(pdecoder->png);

	// swap the rgba or ga data to argb or ag (or bgra to abgr) 
//	png_set_swap_alpha(pdecoder->png);
   
	// add filler (or alpha) byte (before/after each rgb triplet)
	if (pdecoder->color_type == PNG_COLOR_TYPE_RGB || pdecoder->color_type == PNG_COLOR_TYPE_GRAY)
		png_set_filler(pdecoder->png, 0xff, PNG_FILLER_AFTER);

	// turn on interlace handling. required if you are not using
	// png_read_image(). to see how to handle interlacing passes,
	// see the png_read_row() method below:
	tb_long_t number_passes = pdecoder->interlace_type != PNG_INTERLACE_NONE ? png_set_interlace_handling(pdecoder->png) : 1;
	tb_trace_impl("number_passes: %ld", number_passes);

	// optional call to gamma correct and add the background to the palette
	// and update info structure.  required if you are expecting libpng to
	// update the palette for you (ie you selected such a transform above).
 	png_read_update_info(pdecoder->png, pdecoder->info);

	// init line
	tb_size_t 	lsize = png_get_rowbytes(pdecoder->png, pdecoder->info);
	tb_byte_t* 	ldata = tb_malloc0(lsize);
	tb_assert_and_check_goto(ldata && lsize, fail);
	
	// init flag
	tb_size_t 	flag = g2_bitmap_flag(bitmap) & ~G2_BITMAP_FLAG_ALPHA;
	tb_byte_t 	balpha = 0xff - ((G2_QUALITY_TOP - g2_quality()) << 3);

	// walk passes
	tb_size_t 	k = 0;
	for (k = 0; k < number_passes; k++)
	{
		// walk line
		tb_size_t 	j;
		tb_size_t 	b = dpixmap->btp;
		tb_size_t 	n = g2_bitmap_lpitch(bitmap);
		tb_byte_t* 	p = data;
		for (j = 0; j < height; j++)
		{
			// read line
			png_read_rows(pdecoder->png, &ldata, TB_NULL, 1);

			// last data
			if (k == number_passes - 1)
			{
				// save data
				tb_size_t 	i = 0;
				tb_byte_t* 	d = p;
				tb_byte_t* 	e = p + n;
				if (dpixmap == spixmap)
				{
					for (i = 0; i < lsize && d < e; i += 4, d += b)
					{
						// copy
						dpixmap->pixel_cpy(d, &ldata[i], 0xff);

						// alpha?
						if (ldata[i + 3] < balpha) flag |= G2_BITMAP_FLAG_ALPHA;
					}
				}
				else
				{
					for (i = 0; i < lsize && d < e; i += 4, d += b)
					{
						// copy
						dpixmap->color_set(d, spixmap->color_get(&ldata[i]));

						// alpha?
						if (ldata[i + 3] < balpha) flag |= G2_BITMAP_FLAG_ALPHA;
					}
				}

				// next line
				p += n;
			}
		}
	}

	// has alpha?
	g2_bitmap_flag_set(bitmap, flag);

	// exit line
	tb_free(ldata);

	// exit reader
	png_read_end(pdecoder->png, pdecoder->info);

	// ok
	return bitmap;

fail:
	if (bitmap) g2_bitmap_exit(bitmap);
	return TB_NULL;
}
static tb_void_t g2_png_decoder_free(g2_image_decoder_t* decoder)
{
	tb_assert_and_check_return(decoder && decoder->type == G2_IMAGE_TYPE_PNG);
	
	// decoder
	g2_png_decoder_t* pdecoder = (g2_png_decoder_t*)decoder;

	// exit png
	png_destroy_read_struct(&pdecoder->png, &pdecoder->info, TB_NULL);
}
/* ///////////////////////////////////////////////////////////////////////
 * interfaces
 */
g2_image_decoder_t* g2_png_decoder_init(tb_size_t pixfmt, tb_gstream_t* gst)
{
	tb_assert_and_check_return_val(G2_PIXFMT_OK(pixfmt) && gst, TB_NULL);

	// probe it
	if (!g2_png_decoder_probe(gst)) return TB_NULL;

	// alloc decoder
	g2_png_decoder_t* decoder = tb_malloc0(sizeof(g2_png_decoder_t));
	tb_assert_and_check_return_val(decoder, TB_NULL);

	// init decoder
	decoder->base.type 		= G2_IMAGE_TYPE_PNG;
	decoder->base.gst 		= gst;
	decoder->base.pixfmt 	= pixfmt;
	decoder->base.done 		= g2_png_decoder_done;
	decoder->base.free 		= g2_png_decoder_free;

	// init png
	decoder->png = png_create_read_struct(PNG_LIBPNG_VER_STRING, TB_NULL, g2_png_decoder_error, TB_NULL);
	tb_assert_and_check_goto(decoder->png, fail);

	// init info
	decoder->info = png_create_info_struct(decoder->png);
	tb_assert_and_check_goto(decoder->info, fail);

	// init reader
 	png_set_read_fn(decoder->png, (tb_pointer_t)gst, g2_png_decoder_reader);

	// read info
	png_read_info(decoder->png, decoder->info);

	// the header info
	png_uint_32 width = 0;
	png_uint_32 height = 0;
	png_get_IHDR(decoder->png, decoder->info, &width, &height, &decoder->bit_depth, &decoder->color_type, &decoder->interlace_type, TB_NULL, TB_NULL);
	tb_assert_and_check_goto(width && height, fail);

	// FIXME: not support now.
	tb_assert_and_check_goto(decoder->color_type != PNG_COLOR_TYPE_PALETTE, fail);

	// init width & height
	decoder->base.width 	= width;
	decoder->base.height 	= height;
	tb_trace_impl("size: %lux%lu", decoder->base.width, decoder->base.height);

	// ok
	return (g2_image_decoder_t*)decoder;

fail:
	if (decoder) g2_image_decoder_exit(decoder);
	return TB_NULL;
}
