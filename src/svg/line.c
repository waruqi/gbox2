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
 * @file		line.c
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
static tb_void_t g2_svg_element_line_dump(g2_svg_element_t const* element, tb_pstring_t* attr)
{
	g2_svg_element_line_t const* line = (g2_svg_element_line_t const*)element;
	tb_assert_and_check_return(line);

	// clear
	tb_pstring_clear(attr);

	// line
	tb_pstring_cstrfcat(attr, " x1=\"%f\" y1=\"%f\" x2=\"%f\" y2=\"%f\"", g2_float_to_tb(line->line.p0.x), g2_float_to_tb(line->line.p0.y), g2_float_to_tb(line->line.p1.x), g2_float_to_tb(line->line.p1.y));

	// transform 
	if (!g2_matrix_identity(&line->matrix)) 
	{
		tb_pstring_cstrfcat(attr, " transform=\"matrix(%f,%f,%f,%f,%f,%f)\"" 	, g2_float_to_tb(line->matrix.sx)
																				, g2_float_to_tb(line->matrix.ky)
																				, g2_float_to_tb(line->matrix.kx)
																				, g2_float_to_tb(line->matrix.sy)
																				, g2_float_to_tb(line->matrix.tx)
																				, g2_float_to_tb(line->matrix.ty));
	}
}
#endif

static tb_void_t g2_svg_element_line_exit(g2_svg_element_t* element)
{
	g2_svg_element_line_t* line = (g2_svg_element_line_t*)element;
	if (line)
	{
		// exit style
		if (line->style) g2_style_exit(line->style);
		line->style = TB_NULL;
	}
}
/* ///////////////////////////////////////////////////////////////////////
 * initializer
 */
g2_svg_element_t* g2_svg_element_init_line(tb_handle_t reader)
{
	// alloc 
	g2_svg_element_line_t* element = tb_malloc0(sizeof(g2_svg_element_line_t));
	tb_assert_and_check_return_val(element, TB_NULL);

	// init
	element->base.exit = g2_svg_element_line_exit;
#ifdef G2_DEBUG
	element->base.dump = g2_svg_element_line_dump;
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
		if (!tb_pstring_cstricmp(&attr->name, "x1"))
			g2_svg_parser_float(p, &element->line.p0.x);
		else if (!tb_pstring_cstricmp(&attr->name, "y1"))
			g2_svg_parser_float(p, &element->line.p0.y);
		else if (!tb_pstring_cstricmp(&attr->name, "x2"))
			g2_svg_parser_float(p, &element->line.p1.x);
		else if (!tb_pstring_cstricmp(&attr->name, "y2"))
			g2_svg_parser_float(p, &element->line.p1.y);
		else if (!tb_pstring_cstricmp(&attr->name, "transform"))
			g2_svg_parser_transform(p, &element->matrix);

	}

	// ok
	return element;
}

