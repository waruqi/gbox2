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
 * @file		style.h
 *
 */
#ifndef G2_SVG_PARSER_STYLE_H
#define G2_SVG_PARSER_STYLE_H

/* ///////////////////////////////////////////////////////////////////////
 * includes
 */
#include "prefix.h"
#include "float.h"
#include "separator.h"

/* ///////////////////////////////////////////////////////////////////////
 * inlines
 */
static __tb_inline__ tb_char_t const* g2_svg_parser_style_color_value(tb_char_t const* p, g2_color_t* color)
{
	// pixel: argb
	g2_pixel_t pixel = tb_s16tou32(p);

	// skip pixel
	tb_size_t n = 0;
	for (; tb_isdigit16(*p); p++, n++) ;

	// only three digits? expand it. e.g. #123 => #112233
	if (n == 3) pixel = (((pixel >> 8) & 0x0f) << 20) | (((pixel >> 8) & 0x0f) << 16) | (((pixel >> 4) & 0x0f) << 12) | (((pixel >> 4) & 0x0f) << 8) | ((pixel & 0x0f) << 4) | (pixel & 0x0f);

	// no alpha? opaque it
	if (!(pixel & 0xff000000)) pixel |= 0xff000000;

	// color
	*color = g2_pixel_color(pixel);

	// ok
	return p;
}
static __tb_inline__ tb_char_t const* g2_svg_parser_style_color_rgb(tb_char_t const* p, g2_color_t* color)
{
	// skip '('
	while (*p && *p != '(') p++; p++;

	// a
	color->a = 0xff;

	// r
	color->r = tb_stou32(p);
	while (*p && tb_isdigit(*p)) p++; p = g2_svg_parser_separator_skip(p);

	// g
	color->g = tb_stou32(p);
	while (*p && tb_isdigit(*p)) p++; p = g2_svg_parser_separator_skip(p);

	// b
	color->b = tb_stou32(p);
	while (*p && tb_isdigit(*p)) p++; p = g2_svg_parser_separator_skip(p);

	// skip ')'
	while (*p && *p != ')') p++; p++;

	// ok
	return p;
}
static __tb_inline__ tb_char_t const* g2_svg_parser_style_color(tb_char_t const* p, g2_color_t* color)
{
	// skip space
	while (tb_isspace(*p)) p++;

	// color
	g2_named_color_t* ncolor = tb_null;
	if (*p == '#') p = g2_svg_parser_style_color_value(p + 1, color);
	else if (!tb_strnicmp(p, "rgb", 3)) p = g2_svg_parser_style_color_rgb(p + 3, color);
	else if (ncolor = g2_color_from_name(p)) 
	{
		*color = ncolor->color;
		p += tb_strlen(ncolor->name);
	}

	// ok
	return p;
}
static __tb_inline__ tb_char_t const* g2_svg_parser_style_paint(tb_char_t const* p, g2_svg_style_paint_t* paint)
{
	g2_named_color_t* ncolor = tb_null;
	if (*p == '#')
	{
		paint->mode = G2_SVG_STYLE_PAINT_MODE_VALUE;
		p = g2_svg_parser_style_color_value(p + 1, &paint->color);
	}
	else if (!tb_strnicmp(p, "rgb", 3)) 
	{
		paint->mode = G2_SVG_STYLE_PAINT_MODE_VALUE;
		p = g2_svg_parser_style_color_rgb(p + 3, &paint->color);
	}
	else if (!tb_strnicmp(p, "url", 3)) 
	{
		// skip "url"
		p += 3;

		// skip '('
		while (*p && *p != '(') p++; p++;

		// url
		paint->mode = G2_SVG_STYLE_PAINT_MODE_URL;
		tb_pstring_clear(&paint->url);
		while (*p && *p != ')') tb_pstring_chrcat(&paint->url, *p++); 
		
		// skip ')'
		p++;
	}
	else if (ncolor = g2_color_from_name(p)) 
	{
		paint->mode = G2_SVG_STYLE_PAINT_MODE_VALUE;
		paint->color = ncolor->color;
		p += tb_strlen(ncolor->name);
	}
	else if (!tb_strnicmp(p, "none", 4)) 
	{
		paint->mode = G2_SVG_STYLE_PAINT_MODE_NONE;
		p += 4;
	}

	// ok
	return p;
}
static __tb_inline__ tb_char_t const* g2_svg_parser_style_fill_opacity(tb_char_t const* p, g2_svg_style_t* style)
{
	// skip space
	while (tb_isspace(*p)) p++;

	// mode
	style->mode |= G2_SVG_STYLE_MODE_FILL;

	// flag
	style->fill.flag |= G2_SVG_STYLE_PAINT_FLAG_HAS_OPACITY;

	// width
	return g2_svg_parser_float(p, &style->fill.opacity);
}
static __tb_inline__ tb_char_t const* g2_svg_parser_style_fill(tb_char_t const* p, g2_svg_style_t* style)
{
	// skip space
	while (tb_isspace(*p)) p++;

	// mode
	style->mode |= G2_SVG_STYLE_MODE_FILL;

	// fill
	return g2_svg_parser_style_paint(p, &style->fill);
}
static __tb_inline__ tb_char_t const* g2_svg_parser_style_stok(tb_char_t const* p, g2_svg_style_t* style)
{
	// skip space
	while (tb_isspace(*p)) p++;

	// mode
	style->mode |= G2_SVG_STYLE_MODE_STOK;

	// stroke
	return g2_svg_parser_style_paint(p, &style->stok);
}
static __tb_inline__ tb_char_t const* g2_svg_parser_style_stok_width(tb_char_t const* p, g2_svg_style_t* style)
{
	// skip space
	while (tb_isspace(*p)) p++;

	// mode
	style->mode |= G2_SVG_STYLE_MODE_STOK;

	// width
	return g2_svg_parser_float(p, &style->width);
}
static __tb_inline__ tb_char_t const* g2_svg_parser_style_stok_linejoin(tb_char_t const* p, g2_svg_style_t* style)
{
	// skip space
	while (tb_isspace(*p)) p++;

	// mode
	style->mode |= G2_SVG_STYLE_MODE_STOK;

	// join
	if (!tb_strnicmp(p, "miter", 5)) style->join = G2_SVG_STYLE_JOIN_MITER;
	else if (!tb_strnicmp(p, "round", 5)) style->join = G2_SVG_STYLE_JOIN_ROUND;
	else if (!tb_strnicmp(p, "bevel", 5)) style->join = G2_SVG_STYLE_JOIN_BEVEL;
	
	// skip join
	if (style->join) p += 5;

	// ok
	return p;
}
static __tb_inline__ tb_char_t const* g2_svg_parser_style_stok_linecap(tb_char_t const* p, g2_svg_style_t* style)
{
	// skip space
	while (tb_isspace(*p)) p++;

	// mode
	style->mode |= G2_SVG_STYLE_MODE_STOK;

	// join
	if (!tb_strnicmp(p, "butt", 4)) 
	{
		style->cap = G2_SVG_STYLE_CAP_BUTT;
		p += 4;
	}
	else if (!tb_strnicmp(p, "round", 5)) 
	{
		style->cap = G2_SVG_STYLE_CAP_ROUND;
		p += 5;
	}
	else if (!tb_strnicmp(p, "square", 6)) 
	{
		style->cap = G2_SVG_STYLE_CAP_SQUARE;
		p += 6;
	}
	
	// ok
	return p;
}
static __tb_inline__ tb_char_t const* g2_svg_parser_style_stok_opacity(tb_char_t const* p, g2_svg_style_t* style)
{
	// skip space
	while (tb_isspace(*p)) p++;

	// mode
	style->mode |= G2_SVG_STYLE_MODE_STOK;

	// flag
	style->stok.flag |= G2_SVG_STYLE_PAINT_FLAG_HAS_OPACITY;

	// opacity
	return g2_svg_parser_float(p, &style->stok.opacity);
}
static __tb_inline__ tb_char_t const* g2_svg_parser_style_opacity(tb_char_t const* p, g2_svg_style_t* style)
{
	// skip space
	while (tb_isspace(*p)) p++;

	// mode
	style->mode |= G2_SVG_STYLE_MODE_OPACITY;

	// opacity
	return g2_svg_parser_float(p, &style->opacity);
}
static __tb_inline__ tb_char_t const* g2_svg_parser_style_gradient_spread(tb_char_t const* p, tb_size_t* spread)
{
	// skip space
	while (tb_isspace(*p)) p++;

	// spread
	if (!tb_strnicmp(p, "pad", 3)) 
	{
		*spread = G2_SVG_STYLE_GRADIENT_SPREAD_PAD;
		p += 3;
	}
	else if (!tb_strnicmp(p, "reflect", 7)) 
	{
		*spread = G2_SVG_STYLE_GRADIENT_SPREAD_REFLECT;
		p += 7;
	}
	else if (!tb_strnicmp(p, "repeat", 6)) 
	{
		*spread = G2_SVG_STYLE_GRADIENT_SPREAD_REPEAT;
		p += 6;
	}
	else *spread = G2_SVG_STYLE_GRADIENT_SPREAD_NONE;
	
	// ok
	return p;
}
static __tb_inline__ tb_char_t const* g2_svg_parser_style_units(tb_char_t const* p, tb_size_t* units)
{
	// skip space
	while (tb_isspace(*p)) p++;

	// units
	if (!tb_strnicmp(p, "userSpaceOnUse", 14)) 
	{
		*units = G2_SVG_STYLE_UNITS_USER;
		p += 14;
	}
	else if (!tb_strnicmp(p, "objectBoundingBox", 17)) 
	{
		*units = G2_SVG_STYLE_UNITS_OBJB;
		p += 17;
	}
	else *units = G2_SVG_STYLE_UNITS_NONE;

	// ok
	return p;
}
static __tb_inline__ tb_char_t const* g2_svg_parser_style_clippath(tb_char_t const* p, g2_svg_style_t* style)
{
	// skip space
	while (tb_isspace(*p)) p++;

	// mode
	style->mode |= G2_SVG_STYLE_MODE_CLIPPATH;

	// clip-path: url()
	if (!tb_strnicmp(p, "url", 3)) 
	{
		// skip "url"
		p += 3;

		// skip '('
		while (*p && *p != '(') p++; p++;

		// url
		style->clippath.mode = G2_SVG_STYLE_CLIPPATH_MODE_URL;
		tb_pstring_clear(&style->clippath.url);
		while (*p && *p != ')') tb_pstring_chrcat(&style->clippath.url, *p++); 
		
		// skip ')'
		p++;
	}
	// clip-path: inherit
	else if (!tb_strnicmp(p, "inherit", 7)) 
	{
		style->clippath.mode = G2_SVG_STYLE_CLIPPATH_MODE_INHERIT;
		p += 7;
	}
	// clip-path: none
	else if (!tb_strnicmp(p, "none", 4)) 
	{
		style->clippath.mode = G2_SVG_STYLE_CLIPPATH_MODE_NONE;
		p += 4;
	}

	// ok
	return p;
}
static __tb_inline__ tb_char_t const* g2_svg_parser_style_stop_color(tb_char_t const* p, g2_color_t* color)
{
	return g2_svg_parser_style_color(p, color);
}
static __tb_inline__ tb_char_t const* g2_svg_parser_style_stop_opacity(tb_char_t const* p, g2_color_t* color)
{
	g2_float_t opacity;
	p = g2_svg_parser_float(p, &opacity);
	color->a = g2_float_to_long(opacity * color->a);
	return p;
}
static __tb_inline__ tb_char_t const* g2_svg_parser_style_stop(tb_char_t const* p, g2_color_t* color)
{
	// check
	tb_assert(color);

	// done
	while (*p)
	{
		if (!tb_isspace(*p))
		{
			if (!tb_strnicmp(p, "stop-color:", 11))
				p = g2_svg_parser_style_stop_color(p + 11, color);
			else if (!tb_strnicmp(p, "stop-opacity:", 13))
				p = g2_svg_parser_style_stop_opacity(p + 13, color);
			else p++;
		}
		else p++;
	}
	return p;
}
static __tb_inline__ tb_char_t const* g2_svg_parser_style_font_size(tb_char_t const* p, g2_svg_style_t* style)
{
	// mode
	style->mode |= G2_SVG_STYLE_MODE_FONT;

	// size
	return g2_svg_parser_float(p, &style->font.size);
}
static __tb_inline__ tb_char_t const* g2_svg_parser_style_font_family(tb_char_t const* p, g2_svg_style_t* style)
{
	// skip space
	while (tb_isspace(*p)) p++;

	// mode
	style->mode |= G2_SVG_STYLE_MODE_FONT;

	// family
	tb_pstring_clear(&style->font.family);
	while (*p && *p != ';') tb_pstring_chrcat(&style->font.family, *p++); 
	
	// skip ';'
	if (*p == ';') p++;

	// ok
	return p;
}
static __tb_inline__ tb_char_t const* g2_svg_parser_style_font_weight(tb_char_t const* p, g2_svg_style_t* style)
{
	// skip space
	while (tb_isspace(*p)) p++;

	// mode
	style->mode |= G2_SVG_STYLE_MODE_FONT;

	// weight
	if (!tb_strnicmp(p, "normal", 6)) 
	{
		style->font.weight = G2_SVG_STYLE_FONT_WEIGHT_NORMAL;
		p += 6;
	}
	else if (!tb_strnicmp(p, "bold", 4)) 
	{
		style->font.weight = G2_SVG_STYLE_FONT_WEIGHT_BORD;
		p += 4;
	}
	else if (!tb_strnicmp(p, "bolder", 6)) 
	{
		style->font.weight = G2_SVG_STYLE_FONT_WEIGHT_BOLDER;
		p += 6;
	}
	else if (!tb_strnicmp(p, "lighter", 7)) 
	{
		style->font.weight = G2_SVG_STYLE_FONT_WEIGHT_LIGHTER;
		p += 7;
	}
	else 
	{
		// 100 - 900 or 0
		style->font.weight = tb_stou32(p);
		if (style->font.weight < 100 || style->font.weight > 900) style->font.weight = G2_SVG_STYLE_FONT_WEIGHT_INHERIT;

		// skip
		while (*p && *p != ';') p++; if (*p == ';') p++;
	}
	
	// ok
	return p;
}
static __tb_inline__ tb_char_t const* g2_svg_parser_style_font_style(tb_char_t const* p, g2_svg_style_t* style)
{
	// skip space
	while (tb_isspace(*p)) p++;

	// mode
	style->mode |= G2_SVG_STYLE_MODE_FONT;

	// style
	if (!tb_strnicmp(p, "normal", 6)) 
	{
		style->font.style = G2_SVG_STYLE_FONT_STYLE_NORMAL;
		p += 6;
	}
	else if (!tb_strnicmp(p, "italic", 6)) 
	{
		style->font.style = G2_SVG_STYLE_FONT_STYLE_ITALIC;
		p += 6;
	}
	else if (!tb_strnicmp(p, "oblique", 7)) 
	{
		style->font.style = G2_SVG_STYLE_FONT_STYLE_OBLIQUE;
		p += 7;
	}
	else style->font.style = G2_SVG_STYLE_FONT_STYLE_INHERIT;

	// ok
	return p;
}
static __tb_inline__ tb_char_t const* g2_svg_parser_style_text_anchor(tb_char_t const* p, g2_svg_style_t* style)
{
	// skip space
	while (tb_isspace(*p)) p++;

	// mode
	style->mode |= G2_SVG_STYLE_MODE_TEXT;

	// anchor
	if (!tb_strnicmp(p, "start", 5)) 
	{
		style->text.anchor = G2_SVG_STYLE_TEXT_ANCHOR_START;
		p += 5;
	}
	else if (!tb_strnicmp(p, "middle", 6)) 
	{
		style->text.anchor = G2_SVG_STYLE_TEXT_ANCHOR_MIDDLE;
		p += 6;
	}
	else if (!tb_strnicmp(p, "end", 3)) 
	{
		style->text.anchor = G2_SVG_STYLE_TEXT_ANCHOR_END;
		p += 3;
	}
	else style->text.anchor = G2_SVG_STYLE_TEXT_ANCHOR_INHERIT;

	// ok
	return p;
}
static __tb_inline__ tb_char_t const* g2_svg_parser_style(tb_char_t const* p, g2_svg_style_t* style)
{
	// check
	tb_assert(style);

	// done
	while (*p)
	{
		if (!tb_isspace(*p))
		{
			if (!tb_strnicmp(p, "fill:", 5))
				p = g2_svg_parser_style_fill(p + 5, style);
			else if (!tb_strnicmp(p, "fill-opacity:", 13))
				p = g2_svg_parser_style_fill_opacity(p + 13, style);
			else if (!tb_strnicmp(p, "stroke:", 7))
				p = g2_svg_parser_style_stok(p + 7, style);
			else if (!tb_strnicmp(p, "stroke-width:", 13))
				p = g2_svg_parser_style_stok_width(p + 13, style);
			else if (!tb_strnicmp(p, "stroke-linecap:", 15))
				p = g2_svg_parser_style_stok_linecap(p + 15, style);
			else if (!tb_strnicmp(p, "stroke-linejoin:", 16))
				p = g2_svg_parser_style_stok_linejoin(p + 16, style);
			else if (!tb_strnicmp(p, "stroke-opacity:", 15))
				p = g2_svg_parser_style_stok_opacity(p + 15, style);
			else if (!tb_strnicmp(p, "opacity:", 8))
				p = g2_svg_parser_style_opacity(p + 8, style);
			else if (!tb_strnicmp(p, "clip-path:", 10))
				p = g2_svg_parser_style_clippath(p + 10, style);
			else if (!tb_strnicmp(p, "font-size:", 10))
				p = g2_svg_parser_style_font_size(p + 10, style);
			else if (!tb_strnicmp(p, "line-height:", 12))
				p = g2_svg_parser_style_font_size(p + 12, style);
			else if (!tb_strnicmp(p, "font-family:", 12))
				p = g2_svg_parser_style_font_family(p + 12, style);
			else if (!tb_strnicmp(p, "font-weight:", 12))
				p = g2_svg_parser_style_font_weight(p + 12, style);
			else if (!tb_strnicmp(p, "font-style:", 11))
				p = g2_svg_parser_style_font_style(p + 11, style);
			else if (!tb_strnicmp(p, "text-anchor:", 12))
				p = g2_svg_parser_style_text_anchor(p + 12, style);
			else p++;
		}
		else p++;
	}
	return p;
}
#endif


