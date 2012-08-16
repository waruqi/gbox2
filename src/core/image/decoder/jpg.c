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
 * @file		jpg.c
 *
 */

/* ///////////////////////////////////////////////////////////////////////
 * trace
 */
#define TB_TRACE_IMPL_TAG 				"jpeg"

/* ///////////////////////////////////////////////////////////////////////
 * includes
 */
#include "jpg.h"
#include "decoder.h"
#include "../../../third/jpeg/jinclude.h"
#include "../../../third/jpeg/jpeglib.h"

/* ///////////////////////////////////////////////////////////////////////
 * types
 */

// the jpeg source manger type
typedef struct __g2_jpg_decoder_jsrc_manger_t 
{
	// the ipeg source
	struct jpeg_source_mgr 			jsrc;

	// the stream
	tb_gstream_t* 					jgst;

	// the data & size
	tb_byte_t 						data[TB_GSTREAM_BLOCK_MAXN];

}g2_jpg_decoder_jsrc_manager_t;

// the jpeg error manager type
typedef struct __g2_jpg_decoder_jerr_manager_t 
{
	// the jpeg error
	struct jpeg_error_mgr 			jerr;

	// is error?
	tb_bool_t 						berr;

}g2_jpg_decoder_jerr_manager_t;

// the jpeg decoder type
typedef struct __g2_jpg_decoder_t
{
	// the base
	g2_image_decoder_t 				base;

	// the jpeg error manager
	g2_jpg_decoder_jerr_manager_t 	jerr;

	// the jpeg decompress
	struct jpeg_decompress_struct 	jdec;

}g2_jpg_decoder_t;

/* ///////////////////////////////////////////////////////////////////////
 * implementation
 */
static tb_void_t g2_jpg_decoder_jsrc_init_source(j_decompress_ptr jdec)
{
	// g2_jpg_decoder_jsrc_manager_t* jsm = (g2_jpg_decoder_jsrc_manager_t*)jdec->src;
}
static boolean g2_jpg_decoder_jsrc_fill_input_buffer(j_decompress_ptr jdec)
{
	g2_jpg_decoder_jsrc_manager_t* jsm = (g2_jpg_decoder_jsrc_manager_t*)jdec->src;
	tb_assert_and_check_return_val(jsm && jsm->jgst, TB_FALSE);

	// read 
	tb_hize_t left = tb_gstream_left(jsm->jgst);
	tb_size_t need = (tb_size_t)tb_min(left, TB_GSTREAM_BLOCK_MAXN);
	if (!tb_gstream_bread(jsm->jgst, jsm->data, need)) return TB_FALSE;

	// fill
	jsm->jsrc.next_input_byte       = jsm->data;
	jsm->jsrc.bytes_in_buffer       = need;

	// ok
	return TB_TRUE;
}
static tb_void_t g2_jpg_decoder_jsrc_skip_input_data(j_decompress_ptr jdec, tb_long_t num_bytes)
{
	g2_jpg_decoder_jsrc_manager_t* jsm = (g2_jpg_decoder_jsrc_manager_t*)jdec->src;
	if (jsm && num_bytes > 0 && jsm->jsrc.next_input_byte && jsm->jsrc.bytes_in_buffer >= num_bytes)
	{
		jsm->jsrc.next_input_byte += num_bytes;
		jsm->jsrc.bytes_in_buffer -= num_bytes;
	}
}
static tb_void_t g2_jpg_decoder_jsrc_term_source(j_decompress_ptr jdec)
{
	//g2_jpg_decoder_jsrc_manager_t* jsm = (g2_jpg_decoder_jsrc_manager_t*)jdec->src;
}
static tb_void_t g2_jpg_decoder_jerr_exit(j_common_ptr jerr)
{
	if (jerr)
	{
		g2_jpg_decoder_jerr_manager_t* jem = (g2_jpg_decoder_jerr_manager_t*)jerr->err;
		if (jem) jem->berr = TB_TRUE;
	}
}
static tb_void_t g2_jpg_decoder_jsrc_init(j_decompress_ptr jdec, tb_gstream_t* jgst)
{
	// create source
	if (!jdec->src) jdec->src = (struct jpeg_source_mgr*)(*jdec->mem->alloc_small)((j_common_ptr)jdec, JPOOL_PERMANENT, sizeof(g2_jpg_decoder_jsrc_manager_t));

	// attach source funcs
	g2_jpg_decoder_jsrc_manager_t* jsm 		= (g2_jpg_decoder_jsrc_manager_t*)jdec->src;
	jsm->jsrc.init_source 					= g2_jpg_decoder_jsrc_init_source;
	jsm->jsrc.fill_input_buffer 			= g2_jpg_decoder_jsrc_fill_input_buffer;
	jsm->jsrc.skip_input_data 				= g2_jpg_decoder_jsrc_skip_input_data;
	jsm->jsrc.resync_to_restart 			= jpeg_resync_to_restart;
	jsm->jsrc.term_source 					= g2_jpg_decoder_jsrc_term_source;

	// init stream
	jsm->jsrc.next_input_byte 				= TB_NULL;
	jsm->jsrc.bytes_in_buffer 				= 0;
	jsm->jgst 								= jgst;
}
static tb_bool_t g2_jpg_decoder_probe(tb_gstream_t* gst)
{
	// need
	tb_byte_t* p = TB_NULL;
	if (!tb_gstream_bneed(gst, &p, 4)) return TB_FALSE;
	tb_assert_and_check_return_val(p, TB_FALSE);

	// ok?
	return ( 	p[0] == 0xff 
			&& 	p[1] == 0xd8 
			&& 	p[2] == 0xff 
			&& (p[3] >= 0xe0 && p[3] <= 0xef))? TB_TRUE : TB_FALSE;
}
static tb_handle_t g2_jpg_decoder_done(g2_image_decoder_t* decoder)
{
	// check
	tb_assert_and_check_return_val(decoder && decoder->type == G2_IMAGE_TYPE_JPG, TB_NULL);

	// decoder
	g2_jpg_decoder_t* jdecoder = (g2_jpg_decoder_t*)decoder;

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

	// init pixfmt: rgb
	jdecoder->jdec.out_color_space = JCS_RGB;

	// decode it
	jpeg_start_decompress(&jdecoder->jdec);

	// init line
	tb_size_t 	lsize = jdecoder->jdec.output_components * jdecoder->jdec.output_width;
	JSAMPROW 	ldata = jdecoder->jdec.mem->alloc_small((j_common_ptr)&jdecoder->jdec, JPOOL_IMAGE, lsize);
	tb_assert_and_check_goto(ldata && lsize, fail);

	// read lines
	g2_color_t 	c;
	tb_size_t 	b = pixmap->btp;
	tb_size_t 	n = g2_bitmap_lpitch(bitmap);
	tb_byte_t* 	p = data;
	while (jdecoder->jdec.output_scanline < jdecoder->jdec.output_height)
	{
		// read line
		jpeg_read_scanlines(&jdecoder->jdec, &ldata, 1);

		// save data
		tb_size_t 	i = 0;
		tb_byte_t* 	d = p;
		for (i = 0; i < lsize; i += 3, d += b)
		{
			c.r = GETJSAMPLE(ldata[i + 0]);
			c.g = GETJSAMPLE(ldata[i + 1]);
			c.b = GETJSAMPLE(ldata[i + 2]);
			c.a = 0xff;
			pixmap->color_set(d, c);
		}

		// next line
		p += n;
	}

	// finish it
	jpeg_finish_decompress(&jdecoder->jdec);

	// ok
	return bitmap;

fail:
	if (bitmap) g2_bitmap_exit(bitmap);
	return TB_NULL;
}
static tb_void_t g2_jpg_decoder_free(g2_image_decoder_t* decoder)
{
	tb_assert_and_check_return(decoder && decoder->type == G2_IMAGE_TYPE_JPG);

	// exit jpeg decoder
	jpeg_destroy_decompress(&((g2_jpg_decoder_t*)decoder)->jdec);
}
/* ///////////////////////////////////////////////////////////////////////
 * interfaces
 */
g2_image_decoder_t* g2_jpg_decoder_init(tb_size_t pixfmt, tb_gstream_t* gst)
{
	tb_assert_and_check_return_val(G2_PIXFMT_OK(pixfmt) && gst, TB_NULL);

	// probe it
	if (!g2_jpg_decoder_probe(gst)) return TB_NULL;

	// alloc decoder
	g2_jpg_decoder_t* decoder = tb_malloc0(sizeof(g2_jpg_decoder_t));
	tb_assert_and_check_return_val(decoder, TB_NULL);

	// init decoder
	decoder->base.type 		= G2_IMAGE_TYPE_JPG;
	decoder->base.gst 		= gst;
	decoder->base.pixfmt 	= pixfmt;
	decoder->base.done 		= g2_jpg_decoder_done;
	decoder->base.free 		= g2_jpg_decoder_free;

	// init jpeg manager
	decoder->jdec.err = jpeg_std_error((struct jpeg_error_mgr *)&decoder->jerr);
	decoder->jerr.jerr.error_exit = g2_jpg_decoder_jerr_exit;
	decoder->jerr.berr = TB_FALSE;

	// init jpeg decoder
	jpeg_create_decompress(&decoder->jdec);

	// init jpeg source
	g2_jpg_decoder_jsrc_init(&decoder->jdec, gst);

	// read jpeg header
	jpeg_read_header(&decoder->jdec, TB_TRUE);
	tb_assert_and_check_goto(!decoder->jerr.berr, fail);

	// init width & height
	decoder->base.width 	= decoder->jdec.image_width;
	decoder->base.height 	= decoder->jdec.image_height;
	tb_trace_impl("size: %lux%lu", decoder->base.width, decoder->base.height);

	// ok
	return (g2_image_decoder_t*)decoder;

fail:
	if (decoder) g2_image_decoder_exit(decoder);
	return TB_NULL;
}
