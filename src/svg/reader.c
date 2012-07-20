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
 * @file		reader.c
 *
 */

/* ///////////////////////////////////////////////////////////////////////
 * includes
 */
#include "reader.h"
#include "element.h"

/* ///////////////////////////////////////////////////////////////////////
 * implementation
 */

tb_handle_t g2_svg_reader_init(tb_gstream_t* gst)
{
	return tb_xml_reader_init(gst);
}
tb_void_t g2_svg_reader_exit(tb_handle_t reader)
{
	tb_xml_reader_exit(reader);
}
g2_svg_element_t* g2_svg_reader_load(tb_handle_t reader)
{
	tb_assert_and_check_return_val(reader, TB_NULL);

	// parent
	g2_svg_element_t* parent = TB_NULL;
	
	// walk
	tb_size_t e = TB_XML_READER_EVENT_NONE;
	while (e = tb_xml_reader_next(reader))
	{
		switch (e)
		{
		case TB_XML_READER_EVENT_DOCUMENT:
		case TB_XML_READER_EVENT_DOCUMENT_TYPE:
			break;
		case TB_XML_READER_EVENT_ELEMENT_EMPTY: 
			{
				// init
				g2_svg_element_t* element = g2_svg_element_init(reader);
				tb_assert_and_check_goto(element, fail);
				
				// append
				g2_svg_element_append_tail(parent, element); 
				tb_assert_and_check_goto(element->parent, fail);
			}
			break;
		case TB_XML_READER_EVENT_ELEMENT_BEG: 
			{
				// init
				g2_svg_element_t* element = g2_svg_element_init(reader);
				tb_assert_and_check_goto(element, fail);

				// append
				g2_svg_element_append_tail(parent, element); 
				tb_assert_and_check_goto(element->parent, fail);

				// enter
				parent = element;
			}
			break;
		case TB_XML_READER_EVENT_ELEMENT_END: 
			{
				tb_assert_and_check_goto(parent, fail);
				parent = parent->parent;
			}
			break;
		case TB_XML_READER_EVENT_TEXT: 
			{
			}
			break;
		case TB_XML_READER_EVENT_CDATA: 
			{
			}
			break;
		case TB_XML_READER_EVENT_COMMENT: 
			{
			}
			break;
		default:
			break;
		}
	}

	// ok
	return parent;

fail:
	if (parent) g2_svg_element_exit(parent);
	return TB_NULL;
}
