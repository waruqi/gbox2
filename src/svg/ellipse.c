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
#include "parser/parser.h"

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

	// transform 
	if (!g2_matrix_identity(&ellipse->matrix)) 
	{
		tb_pstring_cstrfcat(attr, " transform=\"matrix(%f,%f,%f,%f,%f,%f)\"" 	, g2_float_to_tb(ellipse->matrix.sx)
																				, g2_float_to_tb(ellipse->matrix.ky)
																				, g2_float_to_tb(ellipse->matrix.kx)
																				, g2_float_to_tb(ellipse->matrix.sy)
																				, g2_float_to_tb(ellipse->matrix.tx)
																				, g2_float_to_tb(ellipse->matrix.ty));
	}
}
#endif

static tb_void_t g2_svg_element_ellipse_exit(g2_svg_element_t* element)
{
	g2_svg_element_ellipse_t* ellipse = (g2_svg_element_ellipse_t*)element;
	if (ellipse)
	{
		// exit style
		if (ellipse->style) g2_style_exit(ellipse->style);
		ellipse->style = TB_NULL;
	}
}
/* ///////////////////////////////////////////////////////////////////////
 * initializer
 */
g2_svg_element_t* g2_svg_element_init_ellipse(tb_handle_t reader)
{
	// alloc 
	g2_svg_element_ellipse_t* element = tb_malloc0(sizeof(g2_svg_element_ellipse_t));
	tb_assert_and_check_return_val(element, TB_NULL);

	// init
	element->base.exit = g2_svg_element_ellipse_exit;
#ifdef G2_DEBUG
	element->base.dump = g2_svg_element_ellipse_dump;
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
			g2_svg_parser_float(p, &element->ellipse.c0.x);
		else if (!tb_pstring_cstricmp(&attr->name, "cy"))
			g2_svg_parser_float(p, &element->ellipse.c0.y);
		else if (!tb_pstring_cstricmp(&attr->name, "rx"))
			g2_svg_parser_float(p, &element->ellipse.rx);
		else if (!tb_pstring_cstricmp(&attr->name, "ry"))
			g2_svg_parser_float(p, &element->ellipse.ry);
		else if (!tb_pstring_cstricmp(&attr->name, "fill"))
			g2_svg_parser_paint_fill(p, element->style);
		else if (!tb_pstring_cstricmp(&attr->name, "transform"))
			g2_svg_parser_transform(p, &element->matrix);
	}

	// ok
	return element;
}

