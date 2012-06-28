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
	
tb_handle_t g2_shader_init2_linear(g2_float_t xb, g2_float_t yb, g2_float_t xe, g2_float_t ye, g2_gradient_t const* gradient, tb_size_t mode)
{
	g2_point_t pb, pe;

	pb.x = xb;
	pb.y = yb;
	pe.x = xe;
	pe.y = ye;

	return g2_shader_init_linear(&pb, &pe, gradient, mode);
}
tb_handle_t g2_shader_initi_linear(g2_ipoint_t const* pb, g2_ipoint_t const* pe, g2_gradient_t const* gradient, tb_size_t mode)
{
	g2_point_t p1 = g2_ipoint_to_point(pb);
	g2_point_t p2 = g2_ipoint_to_point(pe);

	return g2_shader_init_linear(&p1, &p2, gradient, mode);
}
tb_handle_t g2_shader_init2i_linear(tb_long_t xb, tb_long_t yb, tb_long_t xe, tb_long_t ye, g2_gradient_t const* gradient, tb_size_t mode)
{
	g2_point_t pb, pe;

	pb.x = g2_long_to_float(xb);
	pb.y = g2_long_to_float(yb);
	pe.x = g2_long_to_float(xe);
	pe.y = g2_long_to_float(ye);

	return g2_shader_init_linear(&pb, &pe, gradient, mode);
}
tb_handle_t g2_shader_init2_radial(g2_float_t x0, g2_float_t y0, g2_float_t r, g2_gradient_t const* gradient, tb_size_t mode)
{
	g2_circle_t c;

	c.c.x 	= x0;
	c.c.y 	= y0;
	c.r 	= r;

	return g2_shader_init_radial(&c, gradient, mode);
}
tb_handle_t g2_shader_initi_radial(g2_icircle_t const* cp, g2_gradient_t const* gradient, tb_size_t mode)
{
	g2_circle_t c;

	c.c 	= g2_ipoint_to_point(&cp->c);
	c.r 	= g2_long_to_float(cp->r);

	return g2_shader_init_radial(&c, gradient, mode);
}
tb_handle_t g2_shader_init2i_radial(tb_long_t x0, tb_long_t y0, tb_size_t r, g2_gradient_t const* gradient, tb_size_t mode)
{
	g2_circle_t c;

	c.c.x 	= g2_long_to_float(x0);
	c.c.y 	= g2_long_to_float(y0);
	c.r 	= g2_long_to_float(r);

	return g2_shader_init_radial(&c, gradient, mode);
}
tb_handle_t g2_shader_init2_radial2(g2_float_t xb, g2_float_t yb, g2_float_t rb, g2_float_t xe, g2_float_t ye, g2_float_t re, g2_gradient_t const* gradient, tb_size_t mode)
{
	g2_circle_t c1, c2;

	c1.c.x 	= xb;
	c1.c.y 	= yb;
	c1.r 	= rb;

	c2.c.x 	= xe;
	c2.c.y 	= ye;
	c2.r 	= re;

	return g2_shader_init_radial2(&c1, &c2, gradient, mode);
}
tb_handle_t g2_shader_initi_radial2(g2_icircle_t const* cb, g2_icircle_t const* ce, g2_gradient_t const* gradient, tb_size_t mode)
{
	g2_circle_t c1, c2;

	c1.c 	= g2_ipoint_to_point(&cb->c);
	c1.r 	= g2_long_to_float(cb->r);

	c2.c 	= g2_ipoint_to_point(&ce->c);
	c2.r 	= g2_long_to_float(ce->r);

	return g2_shader_init_radial2(&c1, &c2, gradient, mode);
}
tb_handle_t g2_shader_init2i_radial2(tb_long_t xb, tb_long_t yb, tb_size_t rb, tb_long_t xe, tb_long_t ye, tb_size_t re, g2_gradient_t const* gradient, tb_size_t mode)
{
	g2_circle_t c1, c2;

	c1.c.x 	= g2_long_to_float(xb);
	c1.c.y 	= g2_long_to_float(yb);
	c1.r 	= g2_long_to_float(rb);

	c2.c.x 	= g2_long_to_float(xe);
	c2.c.y 	= g2_long_to_float(ye);
	c2.r 	= g2_long_to_float(re);

	return g2_shader_init_radial2(&c1, &c2, gradient, mode);
}
tb_handle_t g2_shader_init2_conical(g2_float_t xb, g2_float_t yb, g2_float_t rb, g2_float_t xe, g2_float_t ye, g2_float_t re, g2_gradient_t const* gradient, tb_size_t mode)
{
	g2_circle_t c1, c2;

	c1.c.x 	= xb;
	c1.c.y 	= yb;
	c1.r 	= rb;

	c2.c.x 	= xe;
	c2.c.y 	= ye;
	c2.r 	= re;

	return g2_shader_init_conical(&c1, &c2, gradient, mode);
}
tb_handle_t g2_shader_initi_conical(g2_icircle_t const* cb, g2_icircle_t const* ce, g2_gradient_t const* gradient, tb_size_t mode)
{
	g2_circle_t c1, c2;

	c1.c 	= g2_ipoint_to_point(&cb->c);
	c1.r 	= g2_long_to_float(cb->r);

	c2.c 	= g2_ipoint_to_point(&ce->c);
	c2.r 	= g2_long_to_float(ce->r);

	return g2_shader_init_conical(&c1, &c2, gradient, mode);
}
tb_handle_t g2_shader_init2i_conical(tb_long_t xb, tb_long_t yb, tb_size_t rb, tb_long_t xe, tb_long_t ye, tb_size_t re, g2_gradient_t const* gradient, tb_size_t mode)
{
	g2_circle_t c1, c2;

	c1.c.x 	= g2_long_to_float(xb);
	c1.c.y 	= g2_long_to_float(yb);
	c1.r 	= g2_long_to_float(rb);

	c2.c.x 	= g2_long_to_float(xe);
	c2.c.y 	= g2_long_to_float(ye);
	c2.r 	= g2_long_to_float(re);

	return g2_shader_init_conical(&c1, &c2, gradient, mode);
}
tb_handle_t g2_shader_init2_sweep(g2_float_t x0, g2_float_t y0, g2_gradient_t const* gradient)
{	
	g2_point_t pt;

	pt.x = x0;
	pt.y = y0;

	return g2_shader_init_sweep(&pt, gradient);
}
tb_handle_t g2_shader_initi_sweep(g2_ipoint_t const* c0, g2_gradient_t const* gradient)
{
	g2_point_t pt = g2_ipoint_to_point(c0);
	return g2_shader_init_sweep(&pt, gradient);
}
tb_handle_t g2_shader_init2i_sweep(tb_long_t x0, tb_long_t y0, g2_gradient_t const* gradient)
{
	g2_point_t pt;

	pt.x = g2_long_to_float(x0);
	pt.y = g2_long_to_float(y0);

	return g2_shader_init_sweep(&pt, gradient);
}
