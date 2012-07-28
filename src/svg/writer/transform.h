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
 * @file		transform.h
 *
 */
#ifndef G2_SVG_WRITER_TRANSFORM_H
#define G2_SVG_WRITER_TRANSFORM_H

/* ///////////////////////////////////////////////////////////////////////
 * includes
 */
#include "prefix.h"

/* ///////////////////////////////////////////////////////////////////////
 * inlines
 */

static __tb_inline__ tb_void_t g2_svg_writer_transform(tb_gstream_t* gst, g2_matrix_t* matrix)
{
	// check
	tb_assert(gst && matrix);

	// transform 
	if (!g2_matrix_identity(matrix)) 
	{
		tb_gstream_printf(gst, " transform=\"matrix(%f,%f,%f,%f,%f,%f)\"" 	, g2_float_to_tb(matrix->sx)
																			, g2_float_to_tb(matrix->ky)
																			, g2_float_to_tb(matrix->kx)
																			, g2_float_to_tb(matrix->sy)
																			, g2_float_to_tb(matrix->tx)
																			, g2_float_to_tb(matrix->ty));
	}
}

#endif


