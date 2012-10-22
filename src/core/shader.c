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
 * @file		shader.c
 *
 */
/* ///////////////////////////////////////////////////////////////////////
 * includes
 */
#include "shader.h"

/* ///////////////////////////////////////////////////////////////////////
 * implementation
 */
	
tb_handle_t g2_shader_init2_linear(tb_handle_t context, g2_float_t xb, g2_float_t yb, g2_float_t xe, g2_float_t ye, g2_gradient_t const* gradient, tb_size_t mode)
{
	g2_point_t pb, pe;

	pb.x = xb;
	pb.y = yb;
	pe.x = xe;
	pe.y = ye;

	return g2_shader_init_linear(context, &pb, &pe, gradient, mode);
}
tb_handle_t g2_shader_initi_linear(tb_handle_t context, g2_ipoint_t const* pb, g2_ipoint_t const* pe, g2_gradient_t const* gradient, tb_size_t mode)
{
	g2_point_t p1 = g2_ipoint_to_point(pb);
	g2_point_t p2 = g2_ipoint_to_point(pe);

	return g2_shader_init_linear(context, &p1, &p2, gradient, mode);
}
tb_handle_t g2_shader_init2i_linear(tb_handle_t context, tb_long_t xb, tb_long_t yb, tb_long_t xe, tb_long_t ye, g2_gradient_t const* gradient, tb_size_t mode)
{
	g2_point_t pb, pe;

	pb.x = g2_long_to_float(xb);
	pb.y = g2_long_to_float(yb);
	pe.x = g2_long_to_float(xe);
	pe.y = g2_long_to_float(ye);

	return g2_shader_init_linear(context, &pb, &pe, gradient, mode);
}
tb_handle_t g2_shader_init2_radial(tb_handle_t context, g2_float_t x0, g2_float_t y0, g2_float_t r, g2_gradient_t const* gradient, tb_size_t mode)
{
	g2_circle_t c;

	c.c.x 	= x0;
	c.c.y 	= y0;
	c.r 	= r;

	return g2_shader_init_radial(context, &c, gradient, mode);
}
tb_handle_t g2_shader_initi_radial(tb_handle_t context, g2_icircle_t const* cp, g2_gradient_t const* gradient, tb_size_t mode)
{
	g2_circle_t c;

	c.c 	= g2_ipoint_to_point(&cp->c);
	c.r 	= g2_long_to_float(cp->r);

	return g2_shader_init_radial(context, &c, gradient, mode);
}
tb_handle_t g2_shader_init2i_radial(tb_handle_t context, tb_long_t x0, tb_long_t y0, tb_size_t r, g2_gradient_t const* gradient, tb_size_t mode)
{
	g2_circle_t c;

	c.c.x 	= g2_long_to_float(x0);
	c.c.y 	= g2_long_to_float(y0);
	c.r 	= g2_long_to_float(r);

	return g2_shader_init_radial(context, &c, gradient, mode);
}

