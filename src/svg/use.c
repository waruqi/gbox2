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
 * @file		use.c
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
#include "writer/writer.h"

/* ///////////////////////////////////////////////////////////////////////
 * implementation
 */
static tb_void_t g2_svg_element_use_writ(g2_svg_element_t const* element, tb_gstream_t* gst)
{
	g2_svg_element_use_t const* use = (g2_svg_element_use_t const*)element;
	tb_assert_and_check_return(use);

	// id
	if (tb_pstring_size(&use->base.id))
		tb_gstream_printf(gst, " id=\"%s\"", tb_pstring_cstr(&use->base.id));

	// xhref
	if (tb_pstring_size(&use->xhref))
		tb_gstream_printf(gst, " xlink:href=\"%s\"", tb_pstring_cstr(&use->xhref));

	// x & y
	if (g2_nz(use->rect.x) || g2_nz(use->rect.y)) 
		tb_gstream_printf(gst, " x=\"%f\" y=\"%f\"", g2_float_to_tb(use->rect.x), g2_float_to_tb(use->rect.y));

	// width & height
	if (g2_nz(use->rect.w) || g2_nz(use->rect.h)) 
		tb_gstream_printf(gst, " width=\"%f\" height=\"%f\"", g2_float_to_tb(use->rect.w), g2_float_to_tb(use->rect.h));

	// style 
	g2_svg_writer_style(gst, &use->style); 

	// transform 
	g2_svg_writer_transform(gst, &use->matrix); 
}
static tb_void_t g2_svg_element_use_exit(g2_svg_element_t* element)
{
	g2_svg_element_use_t* use = (g2_svg_element_use_t*)element;
	if (use)
	{
		// exit style
		g2_svg_style_exit(&use->style);
	}
}
/* ///////////////////////////////////////////////////////////////////////
 * initializer
 */
g2_svg_element_t* g2_svg_element_init_use(tb_handle_t reader)
{
	// alloc 
	g2_svg_element_use_t* element = tb_malloc0(sizeof(g2_svg_element_use_t));
	tb_assert_and_check_return_val(element, TB_NULL);

	// init
	element->base.exit = g2_svg_element_use_exit;
	element->base.writ = g2_svg_element_use_writ;

	// init style
	g2_svg_style_init(&element->style);

	// init matrix
	g2_matrix_clear(&element->matrix);

	// attributes
	tb_xml_node_t const* attr = tb_xml_reader_attributes(reader);
	for (; attr; attr = attr->next)
	{
		tb_char_t const* p = tb_pstring_cstr(&attr->data);
		if (!tb_pstring_cstricmp(&attr->name, "id"))
			tb_pstring_strcpy(&element->base.id, &attr->data);
		else if (!tb_pstring_cstricmp(&attr->name, "xlink:href"))
			tb_pstring_strcpy(&element->xhref, &attr->data);
		else if (!tb_pstring_cstricmp(&attr->name, "x"))
			g2_svg_parser_float(p, &element->rect.x);
		else if (!tb_pstring_cstricmp(&attr->name, "y"))
			g2_svg_parser_float(p, &element->rect.y);
		else if (!tb_pstring_cstricmp(&attr->name, "width"))
			g2_svg_parser_float(p, &element->rect.w);
		else if (!tb_pstring_cstricmp(&attr->name, "height"))
			g2_svg_parser_float(p, &element->rect.h);
		else if (!tb_pstring_cstricmp(&attr->name, "fill"))
			g2_svg_parser_style_fill(p, &element->style);
		else if (!tb_pstring_cstricmp(&attr->name, "stroke"))
			g2_svg_parser_style_stroke(p, &element->style);
		else if (!tb_pstring_cstricmp(&attr->name, "stroke-width"))
			g2_svg_parser_style_stroke_width(p, &element->style);
		else if (!tb_pstring_cstricmp(&attr->name, "stroke-linecap"))
			g2_svg_parser_style_stroke_linecap(p, &element->style);
		else if (!tb_pstring_cstricmp(&attr->name, "stroke-linejoin"))
			g2_svg_parser_style_stroke_linejoin(p, &element->style);
		else if (!tb_pstring_cstricmp(&attr->name, "style"))
			g2_svg_parser_style(p, &element->style);
		else if (!tb_pstring_cstricmp(&attr->name, "transform"))
			g2_svg_parser_transform(p, &element->matrix);
	}

	// ok
	return element;
}

