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
#ifndef G2_SVG_PAINTER_STYLE_H
#define G2_SVG_PAINTER_STYLE_H

/* ///////////////////////////////////////////////////////////////////////
 * includes
 */
#include "prefix.h"

/* ///////////////////////////////////////////////////////////////////////
 * macros
 */
#ifdef TB_CONFIG_MEMORY_MODE_SMALL
# 	define G2_SVG_ELEMENT_SHADERS_MAXN 			(32)
#else
# 	define G2_SVG_ELEMENT_SHADERS_MAXN 			(64)
#endif

/* ///////////////////////////////////////////////////////////////////////
 * inlines
 */
static tb_void_t g2_svg_painter_style_shader_free(tb_item_func_t* func, tb_pointer_t item)
{
	// check
	tb_assert_and_check_return(item);

	// shader
	tb_handle_t shader = (tb_handle_t)*((tb_pointer_t*)item);
	if (shader) g2_shader_dec(shader);
}
static __tb_inline__ tb_bool_t g2_svg_painter_style_gradient_linear_build(g2_svg_painter_t* painter, g2_svg_element_linear_gradient_t const* element, g2_gradient_t* gradient, g2_point_t* pb, g2_point_t* pe)
{
	if (element->base.head)
	{
		g2_svg_element_t* next = element->base.head;
		while (next)
		{
			// add stop
			if (next->type == G2_SVG_ELEMENT_TYPE_STOP && gradient->count < 256)
			{
				g2_svg_element_stop_t const* stop = (g2_svg_element_stop_t const*)next;
				gradient->color[gradient->count] = stop->color;
				gradient->radio[gradient->count] = stop->offset;
				gradient->count++;
			}

			// next
			next = next->next;
		}
	}

	// pb & pe
	tb_bool_t b = tb_false;
	if (pb && (g2_nz(element->pb.x) || g2_nz(element->pb.y))) { *pb = element->pb; b = tb_true; }
	if (pe && (g2_nz(element->pe.x) || g2_nz(element->pe.y))) { *pe = element->pe; b = tb_true; }

	// href?
	if (!gradient->count || !b)
	{
		tb_char_t const* url = tb_pstring_cstr(&element->href);
		if (url && url[0] == '#') 
		{
			g2_svg_element_linear_gradient_t const* e = tb_hash_get(painter->hash, &url[1]);
			if (e && e->base.type == G2_SVG_ELEMENT_TYPE_LINEARGRADIENT)
				return g2_svg_painter_style_gradient_linear_build(painter, e, gradient, b? tb_null : pb, b? tb_null : pe);
		}
	}

	// ok?
	return gradient->count? tb_true : tb_false;
}
static __tb_inline__ tb_bool_t g2_svg_painter_style_gradient_radial_build(g2_svg_painter_t* painter, g2_svg_element_radial_gradient_t const* element, g2_gradient_t* gradient, g2_circle_t* cp)
{
	if (element->base.head)
	{
		g2_svg_element_t* next = element->base.head;
		while (next)
		{
			// add stop
			if (next->type == G2_SVG_ELEMENT_TYPE_STOP && gradient->count < 256)
			{
				g2_svg_element_stop_t const* stop = (g2_svg_element_stop_t const*)next;
				gradient->color[gradient->count] = stop->color;
				gradient->radio[gradient->count] = stop->offset;
				gradient->count++;
			}

			// next
			next = next->next;
		}
	}

	// cp
	tb_bool_t b = tb_false;
	if (cp && (g2_nz(element->cp.c.x) || g2_nz(element->cp.c.y) || g2_nz(element->cp.r))) { *cp = element->cp; b = tb_true; }

	// href?
	if (!gradient->count || !b)
	{
		tb_char_t const* url = tb_pstring_cstr(&element->href);
		if (url && url[0] == '#') 
		{
			g2_svg_element_radial_gradient_t const* e = tb_hash_get(painter->hash, &url[1]);
			if (e && e->base.type == G2_SVG_ELEMENT_TYPE_RADIALGRADIENT)
				return g2_svg_painter_style_gradient_radial_build(painter, e, gradient, b? tb_null : cp);
		}
	}

	// ok?
	return gradient->count? tb_true : tb_false;
}
static __tb_inline__ tb_bool_t g2_svg_painter_style_gradient_linear(g2_svg_painter_t* painter, g2_svg_element_linear_gradient_t const* element)
{
	// init gradient
	g2_point_t 			pb = {0};
	g2_point_t 			pe = {0};
	g2_color_t 			color[256];
	g2_float_t 			radio[256];
	g2_gradient_t 		gradient = {color, radio};
	if (!g2_svg_painter_style_gradient_linear_build(painter, element, &gradient, &pb, &pe)) return tb_false;

	// init mode
	tb_size_t mode = G2_SHADER_WRAP_CLAMP;
	if (element->spread == G2_SVG_STYLE_GRADIENT_SPREAD_REFLECT) mode = G2_SHADER_WRAP_MIRROR;
	else if (element->spread == G2_SVG_STYLE_GRADIENT_SPREAD_REPEAT) mode = G2_SHADER_WRAP_REPEAT;

	// shader?
	tb_handle_t shader = painter->shaders? tb_hash_get(painter->shaders, element) : tb_null;
	if (!shader)
	{
		// init shader
		shader = g2_shader_init_linear(g2_context(painter->painter), &pb, &pe, &gradient, mode);
		tb_assert_and_check_return_val(shader, tb_false);

		// init shaders
		if (!painter->shaders) 
		{
			tb_item_func_t func = tb_item_func_ptr();
			func.free = g2_svg_painter_style_shader_free;
			painter->shaders = tb_hash_init(G2_SVG_ELEMENT_SHADERS_MAXN, tb_item_func_ptr(), func);
		}

		// set element => shader
		if (painter->shaders) tb_hash_set(painter->shaders, element, shader);
	}

	// set shader
	g2_shader(painter->painter, shader);

	// ok
	return tb_true;
}
static __tb_inline__ tb_bool_t g2_svg_painter_style_gradient_radial(g2_svg_painter_t* painter, g2_svg_element_radial_gradient_t const* element)
{	
	// init gradient
	g2_circle_t 		cp = {0};
	g2_color_t 			color[256];
	g2_float_t 			radio[256];
	g2_gradient_t 		gradient = {color, radio};
	if (!g2_svg_painter_style_gradient_radial_build(painter, element, &gradient, &cp)) return tb_false;

	// init mode
	tb_size_t mode = G2_SHADER_WRAP_CLAMP;
	if (element->spread == G2_SVG_STYLE_GRADIENT_SPREAD_REFLECT) mode = G2_SHADER_WRAP_MIRROR;
	else if (element->spread == G2_SVG_STYLE_GRADIENT_SPREAD_REPEAT) mode = G2_SHADER_WRAP_REPEAT;

	// shader?
	tb_handle_t shader = painter->shaders? tb_hash_get(painter->shaders, element) : tb_null;
	if (!shader)
	{
		// init shader
		shader = g2_shader_init_radial(g2_context(painter->painter), &cp, &gradient, mode);
		tb_assert_and_check_return_val(shader, tb_false);

		// init shaders
		if (!painter->shaders) 
		{
			tb_item_func_t func = tb_item_func_ptr();
			func.free = g2_svg_painter_style_shader_free;
			painter->shaders = tb_hash_init(G2_SVG_ELEMENT_SHADERS_MAXN, tb_item_func_ptr(), func);
		}

		// set element => shader
		if (painter->shaders) tb_hash_set(painter->shaders, element, shader);
	}

	// set shader
	g2_shader(painter->painter, shader);

	// ok
	return tb_true;
}
static __tb_inline__ tb_bool_t g2_svg_painter_style_url(g2_svg_painter_t* painter, tb_char_t const* url)
{
	// id?
	if (url[0] == '#')
	{
		// id => element
		g2_svg_element_t const* element = tb_hash_get(painter->hash, &url[1]);
		tb_assert_and_check_return_val(element, tb_false);

		// done
		switch (element->type)
		{
		case G2_SVG_ELEMENT_TYPE_LINEARGRADIENT:
			return g2_svg_painter_style_gradient_linear(painter, (g2_svg_element_linear_gradient_t const*)element);
		case G2_SVG_ELEMENT_TYPE_RADIALGRADIENT:
			return g2_svg_painter_style_gradient_radial(painter, (g2_svg_element_radial_gradient_t const*)element);
		default:
			break;
		}
	}

	return tb_false;
}
static __tb_inline__ tb_bool_t g2_svg_painter_style_fill(g2_svg_painter_t* painter, g2_svg_style_t const* style)
{
	// no fill? next it
	tb_check_return_val(style->mode & G2_SVG_STYLE_MODE_FILL, tb_false);

	// fill
	g2_clear_style(painter->painter);
	g2_mode(painter->painter, G2_STYLE_MODE_FILL);

	// fill it
	switch (style->fill.mode)
	{
	case G2_SVG_STYLE_PAINT_MODE_VALUE:
		g2_color(painter->painter, style->fill.color);
		break;
	case G2_SVG_STYLE_PAINT_MODE_URL:
		if (!g2_svg_painter_style_url(painter, tb_pstring_cstr(&style->fill.url))) return tb_false;
		break;
	default:
		return tb_false;
	}

	// opacity
	if (style->fill.flag & G2_SVG_STYLE_PAINT_FLAG_HAS_OPACITY)
		g2_alpha(painter->painter, (tb_byte_t)g2_float_to_long(style->fill.opacity * 0xff));
	else if (style->mode & G2_SVG_STYLE_MODE_OPACITY)
		g2_alpha(painter->painter, (tb_byte_t)g2_float_to_long(style->opacity * 0xff));

	// ok
	return tb_true;
}
static __tb_inline__ tb_bool_t g2_svg_painter_style_stok(g2_svg_painter_t* painter, g2_svg_style_t const* style)
{
	// no stroke? next it
	tb_check_return_val(style->mode & G2_SVG_STYLE_MODE_STOK, tb_false);

	// stroke
	g2_clear_style(painter->painter);
	g2_mode(painter->painter, G2_STYLE_MODE_STOK);

	// stroke it
	switch (style->stok.mode)
	{
	case G2_SVG_STYLE_PAINT_MODE_VALUE:
		g2_color(painter->painter, style->stok.color);
		break;
	case G2_SVG_STYLE_PAINT_MODE_URL:
		if (!g2_svg_painter_style_url(painter, tb_pstring_cstr(&style->stok.url))) return tb_false;
		break;
	default:
		return tb_false;
	}

	// width
	if (g2_nz(style->width)) g2_width(painter->painter, style->width);
	
	// join
	if (style->join) g2_join(painter->painter, style->join);

	// join
	if (style->cap) g2_cap(painter->painter, style->cap);

	// opacity
	if (style->stok.flag & G2_SVG_STYLE_PAINT_FLAG_HAS_OPACITY)
		g2_alpha(painter->painter, (tb_byte_t)g2_float_to_long(style->stok.opacity * 0xff));
	else if (style->mode & G2_SVG_STYLE_MODE_OPACITY)
		g2_alpha(painter->painter, (tb_byte_t)g2_float_to_long(style->opacity * 0xff));

	// ok
	return tb_true;
}
static __tb_inline__ tb_void_t g2_svg_painter_style_clip(g2_svg_painter_t* painter, g2_svg_style_t const* style)
{
	// no fill? next it
	tb_check_return(style->mode & G2_SVG_STYLE_MODE_CLIPPATH);

	// clear clipper
	g2_clear_clipper(painter->painter);

	tb_print("ffffffffffffffff: %d", style->clippath.mode);
	// has url?
	tb_check_return(style->clippath.mode == G2_SVG_STYLE_PAINT_MODE_URL);

	tb_print("2");
	// url
	tb_char_t const* url = tb_pstring_cstr(&style->clippath.url);
	tb_assert_and_check_return(url);

	tb_print("3");
	// id?
	if (url[0] == '#')
	{
	tb_print("4");
		// the clippath
		g2_svg_element_t* clippath = tb_hash_get(painter->hash, &url[1]);
		tb_assert_and_check_return(clippath && clippath->type == G2_SVG_ELEMENT_TYPE_CLIPPATH);

	tb_print("5");
		// clip it
		if (clippath->clip) clippath->clip(clippath, painter);
	}
}
static __tb_inline__ tb_bool_t g2_svg_painter_style_image(g2_svg_painter_t* painter, g2_svg_style_t const* style)
{
	// no fill? next it
	tb_check_return_val(style->mode & G2_SVG_STYLE_MODE_IMAGE && style->image.bitmap, tb_false);

	// image
	g2_clear_style(painter->painter);
	g2_mode(painter->painter, G2_STYLE_MODE_FILL);

	// opacity
	if (style->mode & G2_SVG_STYLE_MODE_OPACITY)
		g2_alpha(painter->painter, (tb_byte_t)g2_float_to_long(style->opacity * 0xff));

	// shader?
	tb_handle_t shader = painter->shaders? tb_hash_get(painter->shaders, style->image.bitmap) : tb_null;
	if (!shader)
	{
		// init shader
		shader = g2_shader_init_bitmap(g2_context(painter->painter), style->image.bitmap, G2_SHADER_WRAP_BORDER);
		tb_assert_and_check_return_val(shader, tb_false);

		// init shaders
		if (!painter->shaders) 
		{
			tb_item_func_t func = tb_item_func_ptr();
			func.free = g2_svg_painter_style_shader_free;
			painter->shaders = tb_hash_init(G2_SVG_ELEMENT_SHADERS_MAXN, tb_item_func_ptr(), func);
		}

		// set bitmap => shader
		if (painter->shaders) tb_hash_set(painter->shaders, style->image.bitmap, shader);
	}

	// bounds
	g2_rect_t const* bounds = style->image.bounds;
	
	// matrix
	if (bounds)
	{
		// init size
		tb_size_t 	rw = g2_bitmap_width(style->image.bitmap);
		tb_size_t 	rh = g2_bitmap_height(style->image.bitmap);
		g2_float_t 	bx = bounds->x;
		g2_float_t 	by = bounds->y;
		g2_float_t 	bw = bounds->w;
		g2_float_t 	bh = bounds->h;
		g2_float_t 	cw = bw;
		g2_float_t 	ch = bh;
		g2_float_t 	fw = g2_long_to_float((g2_float_to_long(ch) * rw) / rh);
		g2_float_t 	fh = g2_long_to_float((g2_float_to_long(cw) * rh) / rw);
		if (fw < cw) cw = fw;
		if (fh < ch) ch = fh;

		// init matrix
		g2_matrix_t matrix;
		g2_matrix_init_translate(&matrix, bx + g2_rsh((bw - cw), 1), by + g2_rsh((bh - ch), 1));
		g2_matrix_scale(&matrix, cw / rw, ch / rh);

		// set matrix
		g2_shader_matrix_set(shader, &matrix);
	}

	// set shader
	g2_shader(painter->painter, shader);

	// ok
	return tb_true;
}
static __tb_inline__ tb_void_t g2_svg_painter_style_walk(g2_svg_style_t* applied, g2_svg_style_t const* style)
{
	// check
	tb_assert_and_check_return(applied && style);

	// has fill?
	if (style->mode & G2_SVG_STYLE_MODE_FILL)
	{
		// no inherit? fill it
		applied->mode |= G2_SVG_STYLE_MODE_FILL;
		if (!applied->fill.mode)
		{
			applied->fill.mode = style->fill.mode;
			switch (style->fill.mode)
			{
			case G2_SVG_STYLE_PAINT_MODE_VALUE:
				applied->fill.color = style->fill.color;
				break;
			case G2_SVG_STYLE_PAINT_MODE_URL:
				tb_pstring_strcpy(&applied->fill.url, &style->fill.url);
				break;
			default:
				break;
			}
		}

		// has opacity?
		if (!(applied->fill.flag & G2_SVG_STYLE_PAINT_FLAG_HAS_OPACITY) 
			&& style->fill.flag & G2_SVG_STYLE_PAINT_FLAG_HAS_OPACITY)
		{
			applied->fill.flag |= G2_SVG_STYLE_PAINT_FLAG_HAS_OPACITY;
			applied->fill.opacity = style->fill.opacity;
		}
	}

	// has stroke?
	if (style->mode & G2_SVG_STYLE_MODE_STOK)
	{
		// no inherit? stroke it
		applied->mode |= G2_SVG_STYLE_MODE_STOK;
		if (!applied->stok.mode)
		{
			applied->stok.mode = style->stok.mode;
			switch (style->stok.mode)
			{
			case G2_SVG_STYLE_PAINT_MODE_VALUE:
				applied->stok.color = style->stok.color;
				break;
			case G2_SVG_STYLE_PAINT_MODE_URL:
				tb_pstring_strcpy(&applied->stok.url, &style->stok.url);
				break;
			default:
				break;
			}
		}

		// cap
		if (!applied->cap) applied->cap = style->cap;

		// join
		if (!applied->join) applied->join = style->join;

		// width
		if (g2_ez(applied->width)) applied->width = style->width;

		// has opacity?
		if (!(applied->stok.flag & G2_SVG_STYLE_PAINT_FLAG_HAS_OPACITY) 
			&& style->stok.flag & G2_SVG_STYLE_PAINT_FLAG_HAS_OPACITY)
		{
			applied->stok.flag |= G2_SVG_STYLE_PAINT_FLAG_HAS_OPACITY;
			applied->stok.opacity = style->stok.opacity;
		}
	}

	// has opacity?
	if (!(applied->mode & G2_SVG_STYLE_MODE_OPACITY) 
		&& style->mode & G2_SVG_STYLE_MODE_OPACITY)
	{
		applied->mode |= G2_SVG_STYLE_MODE_OPACITY;
		applied->opacity = style->opacity;
	}

	// has image?
	if (!(applied->mode & G2_SVG_STYLE_MODE_IMAGE) 
		&& style->mode & G2_SVG_STYLE_MODE_IMAGE)
	{
		applied->mode |= G2_SVG_STYLE_MODE_IMAGE;
		applied->image.bitmap = style->image.bitmap;
		applied->image.bounds = style->image.bounds;
	}

	// has clippath?
	if (style->mode & G2_SVG_STYLE_MODE_CLIPPATH)
	{
		// no inherit? stroke it
		applied->mode |= G2_SVG_STYLE_MODE_CLIPPATH;
		if (!applied->clippath.mode)
		{
			applied->clippath.mode = style->clippath.mode;
			if (style->clippath.mode == G2_SVG_STYLE_CLIPPATH_MODE_URL)
				tb_pstring_strcpy(&applied->clippath.url, &style->clippath.url);
		}
#error
	tb_print("applied: %d", applied->clippath.mode);
	}
}


#endif


