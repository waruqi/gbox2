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
#include "../../../third/png/png.h"

/* ///////////////////////////////////////////////////////////////////////
 * types
 */
// the png decoder type
typedef struct __g2_png_decoder_t
{
	// the base
	g2_image_decoder_t 				base;

}g2_png_decoder_t;

/* ///////////////////////////////////////////////////////////////////////
 * implementation
 */
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
	g2_png_decoder_t* jdecoder = (g2_png_decoder_t*)decoder;

	// the pixfmt
	tb_size_t pixfmt 	= decoder->pixfmt;
	tb_assert_and_check_return_val(G2_PIXFMT_OK(pixfmt), TB_NULL);

	// the pixmap
	g2_pixmap_t* pixmap = g2_pixmap(pixfmt, 0xff);
	tb_assert_and_check_return_val(pixmap, TB_NULL);

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

	// ok
	return bitmap;

fail:
	if (bitmap) g2_bitmap_exit(bitmap);
	return TB_NULL;
}
static tb_void_t g2_png_decoder_free(g2_image_decoder_t* decoder)
{
	tb_assert_and_check_return(decoder && decoder->type == G2_IMAGE_TYPE_PNG);

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

	// init width & height
//	decoder->base.width 	= decoder->jdec.image_width;
//	decoder->base.height 	= decoder->jdec.image_height;
	tb_trace_impl("size: %lux%lu", decoder->base.width, decoder->base.height);

	// ok
	return (g2_image_decoder_t*)decoder;

fail:
	if (decoder) g2_image_decoder_exit(decoder);
	return TB_NULL;
}
