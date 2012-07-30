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
// the svg element entry type
typedef struct __g2_svg_element_entry_t
{
	// the element type
	tb_size_t 				type;

	// the element name
	tb_char_t const* 		name;

	// the initialiser
	g2_svg_element_t* 		(*init)(tb_handle_t reader);

}g2_svg_element_entry_t;

/* ///////////////////////////////////////////////////////////////////////
 * globals
 */

// the entries
static g2_svg_element_entry_t 	g_element_entries[] = 
{
	{G2_SVG_ELEMENT_TYPE_NONE, 					"none", 				g2_svg_element_init_none 				}
,	{G2_SVG_ELEMENT_TYPE_A, 					"a", 					g2_svg_element_init_none 				}
,	{G2_SVG_ELEMENT_TYPE_ANIMATE, 				"animate", 				g2_svg_element_init_none 				}
,	{G2_SVG_ELEMENT_TYPE_ANIMATECOLOR, 			"animateColor", 		g2_svg_element_init_none 				}
,	{G2_SVG_ELEMENT_TYPE_ANIMATEMOTION, 		"animateMotion", 		g2_svg_element_init_none 				}
,	{G2_SVG_ELEMENT_TYPE_ANIMATETRANSFORM, 		"animateTransform", 	g2_svg_element_init_none 				}
,	{G2_SVG_ELEMENT_TYPE_CIRCLE, 				"circle", 				g2_svg_element_init_circle 				}
,	{G2_SVG_ELEMENT_TYPE_CLIPPATH, 				"clipPath", 			g2_svg_element_init_none 				}
,	{G2_SVG_ELEMENT_TYPE_CURSOR, 				"cursor", 				g2_svg_element_init_none 				}
,	{G2_SVG_ELEMENT_TYPE_DEFS, 					"defs", 				g2_svg_element_init_none 				}
,	{G2_SVG_ELEMENT_TYPE_DESC, 					"desc", 				g2_svg_element_init_none 				}
,	{G2_SVG_ELEMENT_TYPE_ELLIPSE, 				"ellipse", 				g2_svg_element_init_ellipse 			}
,	{G2_SVG_ELEMENT_TYPE_FEBLEND, 				"feBlend", 				g2_svg_element_init_none 				}
,	{G2_SVG_ELEMENT_TYPE_FECOLORMATRIX, 		"feColorMatrix", 		g2_svg_element_init_none 				}
,	{G2_SVG_ELEMENT_TYPE_FECOMPONENTTRANSFER, 	"feComponentTransfer", 	g2_svg_element_init_none 				}
,	{G2_SVG_ELEMENT_TYPE_FECOMPOSITE, 			"feComposite", 			g2_svg_element_init_none 				}
,	{G2_SVG_ELEMENT_TYPE_FECONVOLVEMATRIX, 		"feConvolveMatrix", 	g2_svg_element_init_none 				}
,	{G2_SVG_ELEMENT_TYPE_FEDIFFUSELIGHTING, 	"feDiffuseLighting", 	g2_svg_element_init_none 				}
,	{G2_SVG_ELEMENT_TYPE_FEDISPLACEMENTMAP, 	"feDisplacementMap", 	g2_svg_element_init_none 				}
,	{G2_SVG_ELEMENT_TYPE_FEFLOOD, 				"feFlood", 				g2_svg_element_init_none 				}
,	{G2_SVG_ELEMENT_TYPE_FEGAUSSIANBLUR, 		"feGaussianBlur", 		g2_svg_element_init_none 				}
,	{G2_SVG_ELEMENT_TYPE_FEIMAGE, 				"feImage", 				g2_svg_element_init_none 				}
,	{G2_SVG_ELEMENT_TYPE_FEMERGE, 				"feMerge", 				g2_svg_element_init_none 				}
,	{G2_SVG_ELEMENT_TYPE_FEMERGENODE, 			"feMergeNode", 			g2_svg_element_init_none 				}
,	{G2_SVG_ELEMENT_TYPE_FEMORPHOLOGY, 			"feMorphology", 		g2_svg_element_init_none 				}
,	{G2_SVG_ELEMENT_TYPE_FEOFFSET, 				"feOffset", 			g2_svg_element_init_none 				}
,	{G2_SVG_ELEMENT_TYPE_FESPECULARLIGHTING, 	"feSpecularLighting", 	g2_svg_element_init_none 				}
,	{G2_SVG_ELEMENT_TYPE_FETILE, 				"feTile", 				g2_svg_element_init_none 				}
,	{G2_SVG_ELEMENT_TYPE_FETURBULENCE, 			"feTurbulence", 		g2_svg_element_init_none 				}
,	{G2_SVG_ELEMENT_TYPE_FILTER, 				"filter", 				g2_svg_element_init_none 				}
,	{G2_SVG_ELEMENT_TYPE_FONT, 					"font", 				g2_svg_element_init_none 				}
,	{G2_SVG_ELEMENT_TYPE_FONTFACE, 				"font-face", 			g2_svg_element_init_none 				}
,	{G2_SVG_ELEMENT_TYPE_FONTFACEFORMAT, 		"font-face-format", 	g2_svg_element_init_none 				}
,	{G2_SVG_ELEMENT_TYPE_FONTFACENAME, 			"font-face-name", 		g2_svg_element_init_none 				}
,	{G2_SVG_ELEMENT_TYPE_FONTFACESRC, 			"font-face-src", 		g2_svg_element_init_none 				}
,	{G2_SVG_ELEMENT_TYPE_FONTFACEURI, 			"font-face-uri", 		g2_svg_element_init_none 				}
,	{G2_SVG_ELEMENT_TYPE_FOREIGNOBJECT, 		"foreignObject", 		g2_svg_element_init_none 				}
,	{G2_SVG_ELEMENT_TYPE_G, 					"g", 					g2_svg_element_init_g 					}
,	{G2_SVG_ELEMENT_TYPE_GLYPH, 				"glyph", 				g2_svg_element_init_none 				}
,	{G2_SVG_ELEMENT_TYPE_HKERN, 				"hkern", 				g2_svg_element_init_none 				}
,	{G2_SVG_ELEMENT_TYPE_IMAGE, 				"image", 				g2_svg_element_init_none 				}
,	{G2_SVG_ELEMENT_TYPE_LINE, 					"line", 				g2_svg_element_init_line 				}
,	{G2_SVG_ELEMENT_TYPE_LINEARGRADIENT, 		"linearGradient", 		g2_svg_element_init_linear_gradient 	}
,	{G2_SVG_ELEMENT_TYPE_MASK, 					"mask", 				g2_svg_element_init_none 				}
,	{G2_SVG_ELEMENT_TYPE_METADATA, 				"metadata", 			g2_svg_element_init_none 				}
,	{G2_SVG_ELEMENT_TYPE_MISSINGGLYPH, 			"missing-glyph", 		g2_svg_element_init_none 				}
,	{G2_SVG_ELEMENT_TYPE_OPERATORSCRIPT, 		"OperatorScript", 		g2_svg_element_init_none 				}
,	{G2_SVG_ELEMENT_TYPE_PARAGRAPH, 			"Paragraph", 			g2_svg_element_init_none 				}
,	{G2_SVG_ELEMENT_TYPE_PATH, 					"path", 				g2_svg_element_init_path 				}
,	{G2_SVG_ELEMENT_TYPE_PATTERN, 				"pattern", 				g2_svg_element_init_none 				}
,	{G2_SVG_ELEMENT_TYPE_POLYGON, 				"polygon", 				g2_svg_element_init_polygon 			}
,	{G2_SVG_ELEMENT_TYPE_POLYLINE, 				"polyline", 			g2_svg_element_init_polyline 			}
,	{G2_SVG_ELEMENT_TYPE_RADIALGRADIENT, 		"radialGradient", 		g2_svg_element_init_radial_gradient		}
,	{G2_SVG_ELEMENT_TYPE_RECT, 					"rect", 				g2_svg_element_init_rect 				}
,	{G2_SVG_ELEMENT_TYPE_SCRIPT, 				"script", 				g2_svg_element_init_none 				}
,	{G2_SVG_ELEMENT_TYPE_STOP, 					"stop", 				g2_svg_element_init_stop 				}
,	{G2_SVG_ELEMENT_TYPE_SVG, 					"svg", 					g2_svg_element_init_svg 				}
,	{G2_SVG_ELEMENT_TYPE_SVGTESTCASE, 			"SVGTestCase", 			g2_svg_element_init_none 				}
,	{G2_SVG_ELEMENT_TYPE_SWITCH, 				"switch", 				g2_svg_element_init_none 				}
,	{G2_SVG_ELEMENT_TYPE_SYMBOL, 				"symbol", 				g2_svg_element_init_none 				}
,	{G2_SVG_ELEMENT_TYPE_TEXT, 					"text", 				g2_svg_element_init_none 				}
,	{G2_SVG_ELEMENT_TYPE_TEXTPATH, 				"textPath", 			g2_svg_element_init_none 				}
,	{G2_SVG_ELEMENT_TYPE_TITLE, 				"title", 				g2_svg_element_init_none 				}
,	{G2_SVG_ELEMENT_TYPE_TSPAN, 				"tspan", 				g2_svg_element_init_none 				}
,	{G2_SVG_ELEMENT_TYPE_USE, 					"use", 					g2_svg_element_init_use 				}
,	{G2_SVG_ELEMENT_TYPE_VIDEO, 				"video", 				g2_svg_element_init_none 				}
,	{G2_SVG_ELEMENT_TYPE_VIEW, 					"view", 				g2_svg_element_init_none 				}
,	{G2_SVG_ELEMENT_TYPE_VKERN, 				"vkern", 				g2_svg_element_init_none 				}
};

/* ///////////////////////////////////////////////////////////////////////
 * comparator
 */
static tb_long_t g2_svg_element_entry_comp(tb_iterator_t* iterator, tb_cpointer_t item, tb_cpointer_t name)
{
	// check
	tb_assert_return_val(item && name, 0);

	// comp
	return tb_stricmp(((g2_svg_element_entry_t const*)item)->name, name);
}

/* ///////////////////////////////////////////////////////////////////////
 * implementation
 */
g2_svg_element_t* g2_svg_element_init(tb_handle_t reader)
{
	// the element name
	tb_char_t const* name = tb_xml_reader_element(reader);
	tb_assert_and_check_return_val(name, TB_NULL);

	// init iterator
	tb_iterator_t 	iterator = tb_iterator_mem(g_element_entries, tb_arrayn(g_element_entries), sizeof(g2_svg_element_entry_t));
	iterator.comp = g2_svg_element_entry_comp;

	// find it by the binary search
	tb_size_t 		itor = tb_binary_find_all(&iterator, name);

	// ok?
	if (itor != tb_iterator_tail(&iterator))
	{
		// entry
		g2_svg_element_entry_t const* entry = (g2_svg_element_entry_t const*)tb_iterator_item(&iterator, itor);
		if (entry && entry->init)
		{
			// init
			g2_svg_element_t* element = entry->init(reader);
			if (element) element->type = entry->type;
			return element;
		}
	}

	// none
	return g2_svg_element_init_none(reader);
}
g2_svg_element_t* g2_svg_element_init_none(tb_handle_t reader)
{
	// alloc 
	g2_svg_element_t* element = tb_malloc0(sizeof(g2_svg_element_t));
	tb_assert_and_check_return_val(element, TB_NULL);

	// init
	element->type = G2_SVG_ELEMENT_TYPE_NONE;

	// init id
	tb_pstring_init(&element->id);

	// ok
	return element;
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

		// exit id
		tb_pstring_exit(&element->id);

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
tb_char_t const* g2_svg_element_name(g2_svg_element_t const* element)
{
	tb_assert_and_check_return_val(element, TB_NULL);
	return element->type < tb_arrayn(g_element_entries)? g_element_entries[element->type].name : TB_NULL;
}

