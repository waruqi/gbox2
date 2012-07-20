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
 * @file		element.c
 *
 */
/* ///////////////////////////////////////////////////////////////////////
 * includes
 */
#include "element.h"

/* ///////////////////////////////////////////////////////////////////////
 * types
 */
// the svg reader entry type
typedef struct __g2_svg_reader_entry_t
{
	// the element type
	tb_size_t 				type;

	// the element name
	tb_char_t const* 		name;

}g2_svg_reader_entry_t;

/* ///////////////////////////////////////////////////////////////////////
 * globals
 */

// the entries
static g2_svg_reader_entry_t* 	g_reader_entries[] = 
{
	{G2_SVG_ELEMENT_TYPE_NONE, 				TB_NULL 			}
,	{G2_SVG_ELEMENT_TYPE_CIRClE, 			"circle" 			}
,	{G2_SVG_ELEMENT_TYPE_CLIPPATH, 			"clipPath" 			}
,	{G2_SVG_ELEMENT_TYPE_DEFS, 				"defs" 				}
,	{G2_SVG_ELEMENT_TYPE_ELLIPSE, 			"ellipse" 			}
,	{G2_SVG_ELEMENT_TYPE_FECOLORMATRIX, 	"feColorMatrix" 	}
,	{G2_SVG_ELEMENT_TYPE_FILTER, 			"filter" 			}
,	{G2_SVG_ELEMENT_TYPE_G, 				"g" 				}
,	{G2_SVG_ELEMENT_TYPE_IMAGE, 			"image" 			}
,	{G2_SVG_ELEMENT_TYPE_LINE, 				"line" 				}
,	{G2_SVG_ELEMENT_TYPE_LINEARGRADIENT, 	"linearGradient" 	}
,	{G2_SVG_ELEMENT_TYPE_MASK, 				"mask" 				}
,	{G2_SVG_ELEMENT_TYPE_METADATA, 			"metadata" 			}
,	{G2_SVG_ELEMENT_TYPE_PATH, 				"path" 				}
,	{G2_SVG_ELEMENT_TYPE_POLYGON, 			"polygon" 			}
,	{G2_SVG_ELEMENT_TYPE_POLYLINE, 			"polyline" 			}
,	{G2_SVG_ELEMENT_TYPE_RADIALGRADIENT, 	"radialGradient" 	}
,	{G2_SVG_ELEMENT_TYPE_RECT, 				"rect" 				}
,	{G2_SVG_ELEMENT_TYPE_SVG, 				"svg" 				}
,	{G2_SVG_ELEMENT_TYPE_STOP, 				"stop" 				}
,	{G2_SVG_ELEMENT_TYPE_SYMBOL, 			"symbol" 			}
,	{G2_SVG_ELEMENT_TYPE_TEXT, 				"text" 				}
,	{G2_SVG_ELEMENT_TYPE_TSPAN, 			"tspan" 			}
,	{G2_SVG_ELEMENT_TYPE_USE, 				"use" 				}
};

/* ///////////////////////////////////////////////////////////////////////
 * implementation
 */
g2_svg_element_t* g2_svg_element_init(tb_handle_t reader)
{
#if 0

static tb_size_t g2_svg_reader_type(tb_char_t const* name)
{
	// FIXME: use binary search
	tb_size_t i = 0;
	tb_size_t n = tb_arraryn(g_reader_entries);
	for (i = 1; i < n; i++)
		if (!tb_stricmp(g_reader_entries[i].name, name)) return g_reader_entries[i].type;

	return G2_SVG_ELEMENT_TYPE_NONE;
}
#endif
	return TB_NULL;
}
tb_void_t g2_svg_element_exit(g2_svg_element_t* element)
{
	if (element)
	{
		// free childs
		if (element->head)
		{
			g2_svg_element_t* save = TB_NULL;
			g2_svg_element_t* next = element->head;
			while (next)
			{
				// save
				save = next->next;
				
				// exit
				g2_svg_element_exit(element);

				// next
				next = save;
			}
		}

		// exit it
		if (element->exit) element->exit(element);
	
		// free it
		tb_free(element);
	}
}
tb_void_t g2_svg_element_insert_next(g2_svg_element_t* element, g2_svg_element_t* next)
{
	// check
	tb_assert_and_check_return(element && next);

	// init
	next->parent = element->parent;
	next->next = element->next;

	// next
	element->next = next;
}
tb_void_t g2_svg_element_remove_next(g2_svg_element_t* element)
{
	// check
	tb_assert_and_check_return(element);

	// next
	g2_svg_element_t* next = element->next;

	// save
	g2_svg_element_t* save = next? next->next : TB_NULL;

	// exit
	if (next) g2_svg_element_exit(next);

	// next
	element->next = save;
}
tb_void_t g2_svg_element_append_head(g2_svg_element_t* element, g2_svg_element_t* child)
{
	// check
	tb_assert_and_check_return(element && child);

	// init
	child->parent = element;

	// append
	if (element->head) 
	{
		child->next = element->head;
		element->head = child;
	}
	else
	{
		tb_assert(!element->tail);
		element->tail = element->head = child;
	}
}
tb_void_t g2_svg_element_append_tail(g2_svg_element_t* element, g2_svg_element_t* child)
{
	// check
	tb_assert_and_check_return(element && child);

	// init
	child->parent = element;
	child->next = TB_NULL;

	// append
	if (element->tail) 
	{
		element->tail->next = child;
		element->tail = child;
	}
	else
	{
		tb_assert(!element->head);
		element->tail = element->head = child;
	}
}
