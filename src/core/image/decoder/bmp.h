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
 * @file		bmp.h
 *
 */
#ifndef G2_CORE_IMAGE_DECODER_BMP_H
#define G2_CORE_IMAGE_DECODER_BMP_H

/* ///////////////////////////////////////////////////////////////////////
 * includes
 */
#include "prefix.h"

/* ///////////////////////////////////////////////////////////////////////
 * types
 */
// the bmp decoder type
typedef struct __g2_bmp_decoder_t
{
	// the base
	g2_image_decoder_t base;

}g2_bmp_decoder_t;

/* ///////////////////////////////////////////////////////////////////////
 * interfaces
 */
g2_image_decoder_t* g2_bmp_decoder_init(tb_size_t pixfmt, tb_gstream_t* gst);

#endif


