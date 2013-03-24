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
 * @file		gif.c
 *
 */

/* ///////////////////////////////////////////////////////////////////////
 * trace
 */
#define TB_TRACE_IMPL_TAG 				"gif"

/* ///////////////////////////////////////////////////////////////////////
 * includes
 */
#include "gif.h"
#include "decoder.h"

/* ///////////////////////////////////////////////////////////////////////
 * types
 */
// the gif decoder type
typedef struct __g2_gif_decoder_t
{
	// the base
	g2_image_decoder_t 				base;

}g2_gif_decoder_t;

/* ///////////////////////////////////////////////////////////////////////
 * implementation
 */
static tb_bool_t g2_gif_decoder_probe(tb_gstream_t* gst)
{
	// need
	tb_byte_t* p = tb_null;
	if (!tb_gstream_bneed(gst, &p, 6)) return tb_false;
	tb_assert_and_check_return_val(p, tb_false);

	// ok?
	return ( 	p[0] == 'G'
			&& 	p[1] == 'I' 
			&& 	p[2] == 'F' 
			&& 	p[3] == '8' 
			&& ( 	p[4] == '7'
				|| 	p[4] == '9') 
			&& 	p[5] == 'a')? tb_true : tb_false;
}
static tb_handle_t g2_gif_decoder_done(g2_image_decoder_t* decoder)
{
	// check
	tb_assert_and_check_return_val(decoder && decoder->type == G2_IMAGE_TYPE_GIF, tb_null);

	// decoder
	g2_gif_decoder_t* gdecoder = (g2_gif_decoder_t*)decoder;

	// the pixfmt
	tb_size_t pixfmt 	= decoder->pixfmt;
	tb_assert_and_check_return_val(G2_PIXFMT_OK(pixfmt), tb_null);

	// the pixmap
	g2_pixmap_t* pixmap = g2_pixmap(pixfmt, 0xff);
	tb_assert_and_check_return_val(pixmap, tb_null);

	// the width & height
	tb_size_t width 	= decoder->width;
	tb_size_t height 	= decoder->height;
	tb_assert_and_check_return_val(width & height, tb_null);

	// init bitmap
	tb_handle_t bitmap = g2_bitmap_init(pixfmt, width, height, 0);
	tb_assert_and_check_return_val(bitmap, tb_null);

	// make bitmap
	tb_byte_t* data = g2_bitmap_make(bitmap);
	tb_assert_and_check_goto(data, fail);

	// ok
	return bitmap;

fail:
	if (bitmap) g2_bitmap_exit(bitmap);
	return tb_null;
}
static tb_void_t g2_gif_decoder_free(g2_image_decoder_t* decoder)
{
	tb_assert_and_check_return(decoder && decoder->type == G2_IMAGE_TYPE_GIF);

}
/* ///////////////////////////////////////////////////////////////////////
 * interfaces
 */
g2_image_decoder_t* g2_gif_decoder_init(tb_size_t pixfmt, tb_gstream_t* gst)
{
	tb_assert_and_check_return_val(G2_PIXFMT_OK(pixfmt) && gst, tb_null);

	// probe it
	if (!g2_gif_decoder_probe(gst)) return tb_null;

	// alloc decoder
	g2_gif_decoder_t* decoder = tb_malloc0(sizeof(g2_gif_decoder_t));
	tb_assert_and_check_return_val(decoder, tb_null);

	// init decoder
	decoder->base.type 		= G2_IMAGE_TYPE_GIF;
	decoder->base.gst 		= gst;
	decoder->base.pixfmt 	= pixfmt;
	decoder->base.done 		= g2_gif_decoder_done;
	decoder->base.free 		= g2_gif_decoder_free;

	// init width & height
//	decoder->base.width 	= decoder->jdec.image_width;
//	decoder->base.height 	= decoder->jdec.image_height;
	tb_trace_impl("size: %lux%lu", decoder->base.width, decoder->base.height);

	// ok
	return (g2_image_decoder_t*)decoder;

fail:
	if (decoder) g2_image_decoder_exit(decoder);
	return tb_null;
}
