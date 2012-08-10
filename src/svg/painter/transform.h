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
#ifndef G2_SVG_PAINTER_TRANSFORM_H
#define G2_SVG_PAINTER_TRANSFORM_H

/* ///////////////////////////////////////////////////////////////////////
 * includes
 */
#include "prefix.h"

/* ///////////////////////////////////////////////////////////////////////
 * inlines
 */
static __tb_inline__ tb_bool_t g2_svg_painter_transform_enter(g2_svg_painter_t* painter, g2_matrix_t const* matrix)
{
	// check
	tb_assert_and_check_return_val(painter && painter->painter && matrix, TB_FALSE);

	// transform 
	if (!g2_matrix_identity(matrix)) 
	{
		// save
		g2_save(painter->painter, G2_SAVE_MODE_MATRIX);

		// apply
		g2_multiply(painter->painter, matrix);

		// ok
		return TB_TRUE;
	}

	// no
	return TB_FALSE;
}
static __tb_inline__ tb_void_t g2_svg_painter_transform_leave(g2_svg_painter_t* painter)
{
	// check
	tb_assert_and_check_return(painter && painter->painter);

	// load
	g2_load(painter->painter);
}
#endif


