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
 * @file		circle.c
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
#include "parser/parser.h"

/* ///////////////////////////////////////////////////////////////////////
 * implementation
 */
#ifdef G2_DEBUG
static tb_void_t g2_svg_element_circle_dump(g2_svg_element_t const* element, tb_pstring_t* attr)
{
	g2_svg_element_circle_t const* circle = (g2_svg_element_circle_t const*)element;
	tb_assert_and_check_return(circle);

	// clear
	tb_pstring_clear(attr);

	// circle
	tb_pstring_cstrfcat(attr, " cx=\"%f\" cy=\"%f\" r=\"%f\"", g2_float_to_tb(circle->circle.c.x), g2_float_to_tb(circle->circle.c.y), g2_float_to_tb(circle->circle.r));

	// transform 
	if (!g2_matrix_identity(&circle->matrix)) 
	{
		tb_pstring_cstrfcat(attr, " transform=\"matrix(%f,%f,%f,%f,%f,%f)\"" 	, g2_float_to_tb(circle->matrix.sx)
																				, g2_float_to_tb(circle->matrix.ky)
																				, g2_float_to_tb(circle->matrix.kx)
																				, g2_float_to_tb(circle->matrix.sy)
																				, g2_float_to_tb(circle->matrix.tx)
																				, g2_float_to_tb(circle->matrix.ty));
	}
}
#endif

static tb_void_t g2_svg_element_circle_exit(g2_svg_element_t* element)
{
	g2_svg_element_circle_t* circle = (g2_svg_element_circle_t*)element;
	if (circle)
	{
		// exit style
		if (circle->style) g2_style_exit(circle->style);
		circle->style = TB_NULL;
	}
}
/* ///////////////////////////////////////////////////////////////////////
 * initializer
 */
g2_svg_element_t* g2_svg_element_init_circle(tb_handle_t reader)
{
	// alloc 
	g2_svg_element_circle_t* element = tb_malloc0(sizeof(g2_svg_element_circle_t));
	tb_assert_and_check_return_val(element, TB_NULL);

	// init
	element->base.exit = g2_svg_element_circle_exit;
#ifdef G2_DEBUG
	element->base.dump = g2_svg_element_circle_dump;
#endif

	// init style
	element->style = g2_style_init();

	// init matrix
	g2_matrix_clear(&element->matrix);

	// attributes
	tb_xml_node_t const* attr = tb_xml_reader_attributes(reader);
	for (; attr; attr = attr->next)
	{
		tb_char_t const* p = tb_pstring_cstr(&attr->data);
		if (!tb_pstring_cstricmp(&attr->name, "cx"))
			g2_svg_parser_float(p, &element->circle.c.x);
		else if (!tb_pstring_cstricmp(&attr->name, "cy"))
			g2_svg_parser_float(p, &element->circle.c.y);
		else if (!tb_pstring_cstricmp(&attr->name, "r"))
			g2_svg_parser_float(p, &element->circle.r);
		else if (!tb_pstring_cstricmp(&attr->name, "fill"))
			g2_svg_parser_paint_fill(p, element->style);
		else if (!tb_pstring_cstricmp(&attr->name, "transform"))
			g2_svg_parser_transform(p, &element->matrix);

	}

	// ok
	return element;
}

