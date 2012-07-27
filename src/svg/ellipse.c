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
 * @file		ellipse.c
 *
 */

/* ///////////////////////////////////////////////////////////////////////
 * trace
 */
#define TB_TRACE_IMPL_TAG 		"svg"

/* ///////////////////////////////////////////////////////////////////////
 * includes
 */
#include "element.h"

/* ///////////////////////////////////////////////////////////////////////
 * implementation
 */
#ifdef G2_DEBUG
static tb_void_t g2_svg_element_ellipse_dump(g2_svg_element_t const* element, tb_pstring_t* attr)
{
	g2_svg_element_ellipse_t const* ellipse = (g2_svg_element_ellipse_t const*)element;
	tb_assert_and_check_return(ellipse);

	// clear
	tb_pstring_clear(attr);

	// ellipse
	tb_pstring_cstrfcat(attr, " cx=\"%f\" cy=\"%f\" rx=\"%f\" ry=\"%f\"", g2_float_to_tb(ellipse->ellipse.c0.x), g2_float_to_tb(ellipse->ellipse.c0.y), g2_float_to_tb(ellipse->ellipse.rx), g2_float_to_tb(ellipse->ellipse.ry));
}
#endif

/* ///////////////////////////////////////////////////////////////////////
 * initializer
 */
g2_svg_element_t* g2_svg_element_init_ellipse(tb_handle_t reader)
{
	// alloc 
	g2_svg_element_ellipse_t* element = tb_malloc0(sizeof(g2_svg_element_ellipse_t));
	tb_assert_and_check_return_val(element, TB_NULL);

	// init
#ifdef G2_DEBUG
	element->base.dump = g2_svg_element_ellipse_dump;
#endif

	// attributes
	tb_xml_node_t const* attr = tb_xml_reader_attributes(reader);
	for (; attr; attr = attr->next)
	{
		tb_char_t const* p = tb_pstring_cstr(&attr->data);
		if (!tb_pstring_cstricmp(&attr->name, "cx"))
			element->ellipse.c0.x = tb_float_to_g2(tb_stof(p));
		else if (!tb_pstring_cstricmp(&attr->name, "cy"))
			element->ellipse.c0.y = tb_float_to_g2(tb_stof(p));
		else if (!tb_pstring_cstricmp(&attr->name, "rx"))
			element->ellipse.rx = tb_float_to_g2(tb_stof(p));
		else if (!tb_pstring_cstricmp(&attr->name, "ry"))
			element->ellipse.ry = tb_float_to_g2(tb_stof(p));
	}

	// ok
	return element;
}

