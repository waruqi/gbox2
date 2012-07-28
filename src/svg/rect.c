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
 * @file		rect.c
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
static tb_void_t g2_svg_element_rect_dump(g2_svg_element_t const* element, tb_pstring_t* attr)
{
	g2_svg_element_rect_t const* rect = (g2_svg_element_rect_t const*)element;
	tb_assert_and_check_return(rect);

	// clear
	tb_pstring_clear(attr);

	// rect
	tb_pstring_cstrfcat(attr, " x=\"%f\" y=\"%f\" width=\"%f\" height=\"%f\"", g2_float_to_tb(rect->rect.x), g2_float_to_tb(rect->rect.y), g2_float_to_tb(rect->rect.w), g2_float_to_tb(rect->rect.h));

	// style
	if (rect->style)
	{
		union __g2_c2p_t
		{
			g2_color_t c;
			g2_pixel_t p;

		}c2p;
		c2p.c = g2_style_color(rect->style);
		tb_pstring_cstrfcat(attr, " fill=\"#%x\"", c2p.p);
	}

	// transform 
	if (!g2_matrix_identity(&rect->matrix)) 
	{
		tb_pstring_cstrfcat(attr, " transform=\"matrix(%f,%f,%f,%f,%f,%f)\"" 	, g2_float_to_tb(rect->matrix.sx)
																				, g2_float_to_tb(rect->matrix.ky)
																				, g2_float_to_tb(rect->matrix.kx)
																				, g2_float_to_tb(rect->matrix.sy)
																				, g2_float_to_tb(rect->matrix.tx)
																				, g2_float_to_tb(rect->matrix.ty));
	}
}
#endif

static tb_void_t g2_svg_element_rect_exit(g2_svg_element_t* element)
{
	g2_svg_element_rect_t* rect = (g2_svg_element_rect_t*)element;
	if (rect)
	{
		// exit style
		if (rect->style) g2_style_exit(rect->style);
		rect->style = TB_NULL;
	}
}
/* ///////////////////////////////////////////////////////////////////////
 * initializer
 */
g2_svg_element_t* g2_svg_element_init_rect(tb_handle_t reader)
{
	// alloc 
	g2_svg_element_rect_t* element = tb_malloc0(sizeof(g2_svg_element_rect_t));
	tb_assert_and_check_return_val(element, TB_NULL);

	// init
	element->base.exit = g2_svg_element_rect_exit;
#ifdef G2_DEBUG
	element->base.dump = g2_svg_element_rect_dump;
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
		if (!tb_pstring_cstricmp(&attr->name, "x"))
			g2_svg_parser_float(p, &element->rect.x);
		else if (!tb_pstring_cstricmp(&attr->name, "y"))
			g2_svg_parser_float(p, &element->rect.y);
		else if (!tb_pstring_cstricmp(&attr->name, "width"))
			g2_svg_parser_float(p, &element->rect.w);
		else if (!tb_pstring_cstricmp(&attr->name, "height"))
			g2_svg_parser_float(p, &element->rect.h);
		else if (!tb_pstring_cstricmp(&attr->name, "fill"))
			g2_svg_parser_paint_fill(p, element->style);
		else if (!tb_pstring_cstricmp(&attr->name, "transform"))
			g2_svg_parser_transform(p, &element->matrix);
	}

	// ok
	return element;
}

