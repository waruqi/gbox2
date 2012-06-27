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
 * @file		shader.cpp
 *
 */

/* ///////////////////////////////////////////////////////////////////////
 * includes
 */
#include "prefix.h"
#include "../shader.h"

/* ///////////////////////////////////////////////////////////////////////
 * implementation
 */
static tb_handle_t g2_skia_shader_init_linear(g2_point_t const* pb, g2_point_t const* pe, g2_gradient_t const* gradient, tb_size_t mode)
{
	return TB_NULL;
}
static tb_handle_t g2_skia_shader_init_radial(g2_circle_t const* cp, g2_gradient_t const* gradient, tb_size_t mode)
{
	return TB_NULL;
}
static tb_handle_t g2_skia_shader_init_radial2(g2_circle_t const* cb, g2_circle_t const* ce, g2_gradient_t const* gradient, tb_size_t mode)
{
	return TB_NULL;
}
/* ///////////////////////////////////////////////////////////////////////
 * interfaces
 */
extern "C"
{
	tb_handle_t g2_shader_init_linear(g2_point_t const* pb, g2_point_t const* pe, g2_gradient_t const* gradient, tb_size_t mode)
	{
		return g2_skia_shader_init_linear(pb, pe, gradient, mode);
	}
	tb_handle_t g2_shader_init_radial(g2_circle_t const* cp, g2_gradient_t const* gradient, tb_size_t mode)
	{
		return g2_skia_shader_init_radial(cp, gradient, mode);
	}
	tb_handle_t g2_shader_init_radial2(g2_circle_t const* cb, g2_circle_t const* ce, g2_gradient_t const* gradient, tb_size_t mode)
	{
		return g2_skia_shader_init_radial2(cb, ce, gradient, mode);
	}
}
