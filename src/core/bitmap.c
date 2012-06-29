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
 * @file		bitmap.c
 *
 */
/* ///////////////////////////////////////////////////////////////////////
 * includes
 */
#include "bitmap.h"
#include "image/image.h"

/* ///////////////////////////////////////////////////////////////////////
 * types
 */


/* ///////////////////////////////////////////////////////////////////////
 * globals
 */

/* ///////////////////////////////////////////////////////////////////////
 * interfaces
 */
tb_handle_t g2_bitmap_init_url(tb_size_t pixfmt, tb_char_t const* url)
{
	tb_assert_and_check_return_val(pixfmt != G2_PIXFMT_NONE && url, TB_NULL);
	
	// init stream
	tb_gstream_t* gst = tb_gstream_init_from_url(url);
	tb_assert_and_check_return_val(gst, TB_NULL);

	// open stream
	tb_handle_t bitmap = TB_NULL;
	if (tb_gstream_bopen(gst))
	{
		// init bitmap
		bitmap = g2_bitmap_init_gst(pixfmt, gst);

		// close stream
		tb_gstream_bclose(gst);
	}

	// exit gstream
	tb_gstream_exit(gst);

	// ok?
	return bitmap;
}

tb_handle_t g2_bitmap_init_gst(tb_size_t pixfmt, tb_gstream_t* gst)
{
	tb_assert_and_check_return_val(pixfmt != G2_PIXFMT_NONE && gst, TB_NULL);

	// init image decoder
	g2_image_decoder_t* decoder = g2_image_decoder_init(pixfmt, gst);
	tb_assert_and_check_return_val(decoder, TB_NULL);

	// done image decoder
	tb_handle_t bitmap = g2_image_decoder_done(decoder);
	tb_assert(bitmap);

	// exit image decoder
	g2_image_decoder_exit(decoder);

	// ok?
	return bitmap;
}
