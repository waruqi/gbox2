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
 * @file		gradient.c
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
 * linear_gradient
 */
static tb_void_t g2_svg_element_linear_gradient_writ(g2_svg_element_t const* element, tb_gstream_t* gst)
{
	g2_svg_element_linear_gradient_t const* linear_gradient = (g2_svg_element_linear_gradient_t const*)element;
	tb_assert_and_check_return(linear_gradient);

	// id
	if (tb_pstring_size(&linear_gradient->base.id))
		tb_gstream_printf(gst, " id=\"%s\"", tb_pstring_cstr(&linear_gradient->base.id));

	// xhref
	if (tb_pstring_size(&linear_gradient->xhref))
		tb_gstream_printf(gst, " xlink:href=\"%s\"", tb_pstring_cstr(&linear_gradient->xhref));

	// linear_gradient
	tb_gstream_printf(gst, " x1=\"%f\" y1=\"%f\" x2=\"%f\" y2=\"%f\""
		, g2_float_to_tb(linear_gradient->pb.x)
		, g2_float_to_tb(linear_gradient->pb.y)
		, g2_float_to_tb(linear_gradient->pe.x)
		, g2_float_to_tb(linear_gradient->pe.y));

	// units
	if (linear_gradient->units)
	{
		static tb_char_t const* units[] =
		{
			"userSpaceOnUse"
		, 	"objectBoundingBox"
		};
		if (linear_gradient->units && linear_gradient->units - 1 < tb_arrayn(units)) 
			tb_gstream_printf(gst, " gradientUnits=\"%s\"", units[linear_gradient->units - 1]);
	}

	// spread
	if (linear_gradient->spread)
	{
		static tb_char_t const* spreads[] =
		{
			"pad"
		, 	"reflect"
		, 	"repeat"
		};
		if (linear_gradient->spread && linear_gradient->spread - 1 < tb_arrayn(spreads)) 
			tb_gstream_printf(gst, " spreadMethod=\"%s\"", spreads[linear_gradient->spread - 1]);
	}

	// transform 
	if (!g2_matrix_identity(&linear_gradient->matrix))
	{
		tb_gstream_printf(gst, " gradientTransform=\"matrix(%f,%f,%f,%f,%f,%f)\"" 	, g2_float_to_tb(linear_gradient->matrix.sx)
																					, g2_float_to_tb(linear_gradient->matrix.ky)
																					, g2_float_to_tb(linear_gradient->matrix.kx)
																					, g2_float_to_tb(linear_gradient->matrix.sy)
																					, g2_float_to_tb(linear_gradient->matrix.tx)
																					, g2_float_to_tb(linear_gradient->matrix.ty));
	}

}
static tb_void_t g2_svg_element_linear_gradient_exit(g2_svg_element_t* element)
{
	g2_svg_element_linear_gradient_t* linear_gradient = (g2_svg_element_linear_gradient_t*)element;
	if (linear_gradient)
	{
		// exit xhref
		tb_pstring_exit(&linear_gradient->xhref);
	}
}


/* ///////////////////////////////////////////////////////////////////////
 * radial_gradient
 */
static tb_void_t g2_svg_element_radial_gradient_writ(g2_svg_element_t const* element, tb_gstream_t* gst)
{
	g2_svg_element_radial_gradient_t const* radial_gradient = (g2_svg_element_radial_gradient_t const*)element;
	tb_assert_and_check_return(radial_gradient);

	// id
	if (tb_pstring_size(&radial_gradient->base.id))
		tb_gstream_printf(gst, " id=\"%s\"", tb_pstring_cstr(&radial_gradient->base.id));

	// xhref
	if (tb_pstring_size(&radial_gradient->xhref))
		tb_gstream_printf(gst, " xlink:href=\"%s\"", tb_pstring_cstr(&radial_gradient->xhref));

	// radial_gradient
	tb_gstream_printf(gst, " cx=\"%f\" cy=\"%f\" r=\"%f\""
		, g2_float_to_tb(radial_gradient->cp.c.x)
		, g2_float_to_tb(radial_gradient->cp.c.y)
		, g2_float_to_tb(radial_gradient->cp.r));

	tb_gstream_printf(gst, " fx=\"%f\" fy=\"%f\""
		, g2_float_to_tb(radial_gradient->fp.x)
		, g2_float_to_tb(radial_gradient->fp.y));

	// units
	if (radial_gradient->units)
	{
		static tb_char_t const* units[] =
		{
			"userSpaceOnUse"
		, 	"objectBoundingBox"
		};
		if (radial_gradient->units && radial_gradient->units - 1 < tb_arrayn(units)) 
			tb_gstream_printf(gst, " gradientUnits=\"%s\"", units[radial_gradient->units - 1]);
	}

	// spread
	if (radial_gradient->spread)
	{
		static tb_char_t const* spreads[] =
		{
			"pad"
		, 	"reflect"
		, 	"repeat"
		};
		if (radial_gradient->spread && radial_gradient->spread - 1 < tb_arrayn(spreads)) 
			tb_gstream_printf(gst, " spreadMethod=\"%s\"", spreads[radial_gradient->spread - 1]);
	}

	// transform 
	if (!g2_matrix_identity(&radial_gradient->matrix))
	{
		tb_gstream_printf(gst, " gradientTransform=\"matrix(%f,%f,%f,%f,%f,%f)\"" 	, g2_float_to_tb(radial_gradient->matrix.sx)
																					, g2_float_to_tb(radial_gradient->matrix.ky)
																					, g2_float_to_tb(radial_gradient->matrix.kx)
																					, g2_float_to_tb(radial_gradient->matrix.sy)
																					, g2_float_to_tb(radial_gradient->matrix.tx)
																					, g2_float_to_tb(radial_gradient->matrix.ty));
	}

}
static tb_void_t g2_svg_element_radial_gradient_exit(g2_svg_element_t* element)
{
	g2_svg_element_radial_gradient_t* radial_gradient = (g2_svg_element_radial_gradient_t*)element;
	if (radial_gradient)
	{
		// exit xhref
		tb_pstring_exit(&radial_gradient->xhref);
	}
}
/* ///////////////////////////////////////////////////////////////////////
 * initializer
 */
g2_svg_element_t* g2_svg_element_init_linear_gradient(tb_handle_t reader)
{
	// alloc 
	g2_svg_element_linear_gradient_t* element = tb_malloc0(sizeof(g2_svg_element_linear_gradient_t));
	tb_assert_and_check_return_val(element, TB_NULL);

	// init
	element->base.exit = g2_svg_element_linear_gradient_exit;
	element->base.writ = g2_svg_element_linear_gradient_writ;

	// init xhref
	tb_pstring_init(&element->xhref);

	// init matrix
	g2_matrix_clear(&element->matrix);

	// attributes
	tb_xml_node_t const* attr = tb_xml_reader_attributes(reader);
	for (; attr; attr = attr->next)
	{
		tb_char_t const* p = tb_pstring_cstr(&attr->data);
		if (!tb_pstring_cstricmp(&attr->name, "id"))
			tb_pstring_strcpy(&element->base.id, &attr->data);
		else if (!tb_pstring_cstricmp(&attr->name, "x1"))
			g2_svg_parser_float(p, &element->pb.x);
		else if (!tb_pstring_cstricmp(&attr->name, "y1"))
			g2_svg_parser_float(p, &element->pb.y);
		else if (!tb_pstring_cstricmp(&attr->name, "x2") || !tb_pstring_cstricmp(&attr->name, "x3"))
			g2_svg_parser_float(p, &element->pe.x);
		else if (!tb_pstring_cstricmp(&attr->name, "y2") || !tb_pstring_cstricmp(&attr->name, "y3"))
			g2_svg_parser_float(p, &element->pe.y);
		else if (!tb_pstring_cstricmp(&attr->name, "gradientTransform"))
			g2_svg_parser_transform(p, &element->matrix);
		else if (!tb_pstring_cstricmp(&attr->name, "spreadMethod"))
			g2_svg_parser_style_gradient_spread(p, &element->spread);
		else if (!tb_pstring_cstricmp(&attr->name, "gradientUnits"))
			g2_svg_parser_style_units(p, &element->units);
		else if (!tb_pstring_cstricmp(&attr->name, "xlink:href"))
			tb_pstring_strcpy(&element->xhref, &attr->data);
	}

	// ok
	return element;
}
g2_svg_element_t* g2_svg_element_init_radial_gradient(tb_handle_t reader)
{
	// alloc 
	g2_svg_element_radial_gradient_t* element = tb_malloc0(sizeof(g2_svg_element_radial_gradient_t));
	tb_assert_and_check_return_val(element, TB_NULL);

	// init
	element->base.exit = g2_svg_element_radial_gradient_exit;
	element->base.writ = g2_svg_element_radial_gradient_writ;

	// init xhref
	tb_pstring_init(&element->xhref);

	// init matrix
	g2_matrix_clear(&element->matrix);

	// attributes
	tb_xml_node_t const* attr = tb_xml_reader_attributes(reader);
	for (; attr; attr = attr->next)
	{
		tb_char_t const* p = tb_pstring_cstr(&attr->data);
		if (!tb_pstring_cstricmp(&attr->name, "id"))
			tb_pstring_strcpy(&element->base.id, &attr->data);
		else if (!tb_pstring_cstricmp(&attr->name, "cx"))
			g2_svg_parser_float(p, &element->cp.c.x);
		else if (!tb_pstring_cstricmp(&attr->name, "cy"))
			g2_svg_parser_float(p, &element->cp.c.y);
		else if (!tb_pstring_cstricmp(&attr->name, "r"))
			g2_svg_parser_float(p, &element->cp.r);
		else if (!tb_pstring_cstricmp(&attr->name, "fx"))
			g2_svg_parser_float(p, &element->fp.x);
		else if (!tb_pstring_cstricmp(&attr->name, "fy"))
			g2_svg_parser_float(p, &element->fp.y);
		else if (!tb_pstring_cstricmp(&attr->name, "gradientTransform"))
			g2_svg_parser_transform(p, &element->matrix);
		else if (!tb_pstring_cstricmp(&attr->name, "spreadMethod"))
			g2_svg_parser_style_gradient_spread(p, &element->spread);
		else if (!tb_pstring_cstricmp(&attr->name, "gradientUnits"))
			g2_svg_parser_style_units(p, &element->units);
		else if (!tb_pstring_cstricmp(&attr->name, "xlink:href"))
			tb_pstring_strcpy(&element->xhref, &attr->data);
	}

	// ok
	return element;
}

