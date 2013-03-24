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
 * @file		data.c
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

static tb_void_t g2_svg_element_data_exit(g2_svg_element_t* element)
{
	g2_svg_element_data_t* data = (g2_svg_element_data_t*)element;
	if (data)
	{
		// exit id
		tb_pstring_exit(&data->base.id);

		// exit data
		tb_pstring_exit(&data->data);
	}
}
/* ///////////////////////////////////////////////////////////////////////
 * initializer
 */
g2_svg_element_t* g2_svg_element_init_data(tb_handle_t reader)
{
	// alloc 
	g2_svg_element_data_t* element = tb_malloc0(sizeof(g2_svg_element_data_t));
	tb_assert_and_check_return_val(element, tb_null);

	// init
	element->base.exit = g2_svg_element_data_exit;
	element->base.type = G2_SVG_ELEMENT_TYPE_DATA;

	// init id
	tb_pstring_init(&element->base.id);

	// init data
	tb_pstring_init(&element->data);

	// ok
	return element;
}

