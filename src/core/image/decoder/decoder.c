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
 * @file		decoder.c
 *
 */

/* ///////////////////////////////////////////////////////////////////////
 * includes
 */
#include "decoder.h"
#include "bmp.h"
#include "jpg.h"
#include "png.h"
#include "gif.h"

/* ///////////////////////////////////////////////////////////////////////
 * implementation
 */
g2_image_decoder_t* g2_image_decoder_init(tb_size_t pixfmt, tb_gstream_t* gst)
{
	// init the image decoder list
	static g2_image_decoder_t* (*init[])(tb_size_t , tb_gstream_t* ) =
	{
		tb_null
#ifdef TB_CONFIG_JPG
	,	g2_jpg_decoder_init
#endif
#ifdef TB_CONFIG_PNG
	,	g2_png_decoder_init
#endif
	,	g2_bmp_decoder_init
	,	g2_gif_decoder_init
	};

	// try initing it
	tb_size_t i = 1;
	tb_size_t n = tb_arrayn(init);
	g2_image_decoder_t* decoder = tb_null;
	for (i = 0; i < n; i++)
	{
		if (init[i] && (decoder = init[i](pixfmt, gst))) return decoder;
	}

	return tb_null;
}
tb_void_t g2_image_decoder_exit(g2_image_decoder_t* decoder)
{
	if (decoder)
	{
		if (decoder->free) decoder->free(decoder);
		tb_free(decoder);
	}
}
tb_handle_t g2_image_decoder_done(g2_image_decoder_t* decoder)
{
	// check
	tb_assert_and_check_return_val(decoder && decoder->done, tb_null);

	// done
	return decoder->done(decoder);
}
