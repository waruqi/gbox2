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
 * trace
 */
#define TB_TRACE_IMPL_TAG 		"svg"

/* ///////////////////////////////////////////////////////////////////////
 * includes
 */
#include "reader.h"

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
	tb_assert_and_check_return_val(reader, tb_null);

	// parent
	g2_svg_element_t* 	parent = tb_null;

	// ignore?
	tb_bool_t 			ignore = tb_false;
	
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
				if (!ignore)
				{
					// init
					g2_svg_element_t* element = g2_svg_element_init(reader);
					tb_assert_and_check_goto(element, fail);

					// trace
					if (!element->type)
						tb_trace_impl("not_impl: <%s>", tb_xml_reader_element(reader));

					// append
					g2_svg_element_append_tail(parent, element); 
					tb_assert_and_check_goto(element->parent, fail);
				}
			}
			break;
		case TB_XML_READER_EVENT_ELEMENT_BEG: 
			{
				// init
				g2_svg_element_t* element = g2_svg_element_init(reader);
				tb_assert_and_check_goto(element, fail);

				// trace
				if (!element->type)
					tb_trace_impl("not_impl: <%s>", tb_xml_reader_element(reader));

				// metadata? ignore it
				if (element->type == G2_SVG_ELEMENT_TYPE_METADATA) 
				{
					ignore = tb_true;
					tb_trace_impl("ignore: <metadata>...</metadata>");
				}

				// is svg?
				if (!parent)
				{
					if (element->type == G2_SVG_ELEMENT_TYPE_SVG)
						parent = element;
					else
					{
						g2_svg_element_exit(element);
						goto fail;
					}
				}
				else if (!ignore)
				{
					// append
					g2_svg_element_append_tail(parent, element); 
					tb_assert_and_check_goto(element->parent, fail);

					// enter
					parent = element;
				}
				else g2_svg_element_exit(element);
			}
			break;
		case TB_XML_READER_EVENT_ELEMENT_END: 
			{
				tb_assert_and_check_goto(parent, fail);

				if (ignore)
				{
					tb_char_t const* name = tb_xml_reader_element(reader);
					if (name && !tb_stricmp(name, "metadata")) ignore = tb_false;
				}
				else
				{
					// leave
					if (parent->type != G2_SVG_ELEMENT_TYPE_SVG) 
						parent = parent->parent;
				}
			}
			break;
		case TB_XML_READER_EVENT_TEXT: 
			{
				tb_char_t const* text = tb_xml_reader_text(reader);
				if (parent && text && !ignore)
				{
					// is spaces?
					tb_char_t const* p = text;
					while (*p && tb_isspace(*p)) p++;
					tb_check_break(*p);
					
					// init
					g2_svg_element_t* element = g2_svg_element_init_data(reader);
					tb_assert_and_check_goto(element, fail);

					// data
					tb_pstring_cstrcpy(&((g2_svg_element_data_t*)element)->data, text);

					// append
					g2_svg_element_append_tail(parent, element); 
					tb_assert_and_check_goto(element->parent, fail);
				}
			}
			break;
		case TB_XML_READER_EVENT_CDATA: 
			{
				tb_char_t const* cdata = tb_xml_reader_cdata(reader);
				if (parent && cdata && !ignore)
				{
					// init
					g2_svg_element_t* element = g2_svg_element_init_data(reader);
					tb_assert_and_check_goto(element, fail);

					// data
					tb_pstring_cstrcpy(&((g2_svg_element_data_t*)element)->data, cdata);

					// append
					g2_svg_element_append_tail(parent, element); 
					tb_assert_and_check_goto(element->parent, fail);
				}
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
	return tb_null;
}
