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
 * @file		animate.c
 *
 */
/* ///////////////////////////////////////////////////////////////////////
 * includes
 */
#include "element.h"

/* ///////////////////////////////////////////////////////////////////////
 * implementation
 */
g2_svg_element_t* g2_svg_element_init_animate(tb_handle_t reader)
{
	// alloc 
	g2_svg_element_svg_t* element = tb_malloc0(sizeof(g2_svg_element_animate_t));
	tb_assert_and_check_return_val(element, TB_NULL);

	// init
	element->base.type = G2_SVG_ELEMENT_TYPE_ANIMATE;

	// ok
	return element;
}
g2_svg_element_t* g2_svg_element_init_animate_color(tb_handle_t reader)
{
	// alloc 
	g2_svg_element_svg_t* element = tb_malloc0(sizeof(g2_svg_element_animate_color_t));
	tb_assert_and_check_return_val(element, TB_NULL);

	// init
	element->base.type = G2_SVG_ELEMENT_TYPE_ANIMATECOLOR;

	// ok
	return element;
}
g2_svg_element_t* g2_svg_element_init_animate_motion(tb_handle_t reader)
{
	// alloc 
	g2_svg_element_svg_t* element = tb_malloc0(sizeof(g2_svg_element_animate_motion_t));
	tb_assert_and_check_return_val(element, TB_NULL);

	// init
	element->base.type = G2_SVG_ELEMENT_TYPE_ANIMATEMOTION;

	// ok
	return element;
}
g2_svg_element_t* g2_svg_element_init_animate_transform(tb_handle_t reader)
{
	// alloc 
	g2_svg_element_svg_t* element = tb_malloc0(sizeof(g2_svg_element_animate_transform_t));
	tb_assert_and_check_return_val(element, TB_NULL);

	// init
	element->base.type = G2_SVG_ELEMENT_TYPE_ANIMATETRANSFORM;

	// ok
	return element;
}



