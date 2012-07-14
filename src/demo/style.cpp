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
 * @file		style.cpp
 *
 */

/* ///////////////////////////////////////////////////////////////////////
 * includes
 */
#include "prefix.h"
#include "../style.h"

/* ///////////////////////////////////////////////////////////////////////
 * implementation
 */
static tb_handle_t g2_skia_style_init()
{
	// alloc
	SkPaint* sstyle = new SkPaint();
	tb_assert_and_check_return_val(sstyle, TB_NULL);
	
	// init style
	tb_size_t flag = SkPaint::kAntiAlias_Flag | SkPaint::kFilterBitmap_Flag;
	if (g2_quality() > G2_QUALITY_LOW) sstyle->setFlags(sstyle->getFlags() | flag);
	else sstyle->setFlags(sstyle->getFlags() & ~flag);

	// ok
	return sstyle;
}
static tb_void_t g2_skia_style_exit(tb_handle_t style)
{
	SkPaint* sstyle = static_cast<SkPaint*>(style);
	tb_assert_and_check_return(sstyle);
 
	// free it
 	delete sstyle;
}
static tb_void_t g2_skia_style_clear(tb_handle_t style)
{
	SkPaint* sstyle = static_cast<SkPaint*>(style);
	tb_assert_and_check_return(sstyle);

	// shader
	SkShader* shader = sstyle->getShader();

	// reset
	sstyle->reset();
	tb_size_t flag = SkPaint::kAntiAlias_Flag | SkPaint::kFilterBitmap_Flag;
	if (g2_quality() > G2_QUALITY_LOW) sstyle->setFlags(sstyle->getFlags() | flag);
	else sstyle->setFlags(sstyle->getFlags() & ~flag);

	// ref--
	if (shader) SkSafeUnref(shader);
}
static tb_size_t g2_skia_style_mode(tb_handle_t style)
{
	SkPaint* sstyle = static_cast<SkPaint*>(style);
	tb_assert_and_check_return_val(sstyle, G2_STYLE_MODE_NONE);

	tb_size_t mode = G2_STYLE_MODE_NONE;
	switch (sstyle->getStyle())
	{
	case SkPaint::kFill_Style: mode |= G2_STYLE_MODE_FILL; break;
	case SkPaint::kStroke_Style: mode |= G2_STYLE_MODE_STROKE; break;
	case SkPaint::kStrokeAndFill_Style: mode |= G2_STYLE_MODE_FILL | G2_STYLE_MODE_STROKE; break;
	default: break;
	}
	return mode;
}
static tb_void_t g2_skia_style_mode_set(tb_handle_t style, tb_size_t mode)
{
	SkPaint* sstyle = static_cast<SkPaint*>(style);
	tb_assert_and_check_return(sstyle && mode);

	if (mode & G2_STYLE_MODE_FILL && mode & G2_STYLE_MODE_STROKE) sstyle->setStyle(SkPaint::kStrokeAndFill_Style);
	else if (mode & G2_STYLE_MODE_FILL) sstyle->setStyle(SkPaint::kFill_Style);
	else if (mode & G2_STYLE_MODE_STROKE) sstyle->setStyle(SkPaint::kStroke_Style);
}
static tb_size_t g2_skia_style_flag(tb_handle_t style)
{
	SkPaint* sstyle = static_cast<SkPaint*>(style);
	tb_assert_and_check_return_val(sstyle, G2_STYLE_FLAG_NONE);

	return sstyle->getFlags() & SkPaint::kAntiAlias_Flag? G2_STYLE_FLAG_ANTI_ALIAS : G2_STYLE_FLAG_NONE;
}
static tb_void_t g2_skia_style_flag_set(tb_handle_t style, tb_size_t flag)
{
	SkPaint* sstyle = static_cast<SkPaint*>(style);
	tb_assert_and_check_return(sstyle);

	if (flag & G2_STYLE_FLAG_ANTI_ALIAS) sstyle->setFlags(sstyle->getFlags() | SkPaint::kAntiAlias_Flag);
	else sstyle->setFlags(sstyle->getFlags() & ~SkPaint::kAntiAlias_Flag);
}
static g2_color_t g2_skia_style_color(tb_handle_t style)
{
	SkPaint* sstyle = static_cast<SkPaint*>(style);
	tb_assert_and_check_return_val(sstyle, G2_COLOR_DEFAULT);

	return g2_skia_color_to_g2(sstyle->getColor());
}
static tb_void_t g2_skia_style_color_set(tb_handle_t style, g2_color_t color)
{	
	SkPaint* sstyle = static_cast<SkPaint*>(style);
	tb_assert_and_check_return(sstyle);

	sstyle->setColor(g2_skia_color_to_sk(color));
}
static tb_byte_t g2_skia_style_alpha(tb_handle_t style)
{
	SkPaint* sstyle = static_cast<SkPaint*>(style);
	tb_assert_and_check_return_val(sstyle, 0xff);

	return sstyle->getAlpha();
}
static tb_void_t g2_skia_style_alpha_set(tb_handle_t style, tb_byte_t alpha)
{
	SkPaint* sstyle = static_cast<SkPaint*>(style);
	tb_assert_and_check_return(sstyle);

	sstyle->setAlpha(alpha);
}
static g2_float_t g2_skia_style_width(tb_handle_t style)
{
	SkPaint* sstyle = static_cast<SkPaint*>(style);
	tb_assert_and_check_return_val(sstyle, G2_ONE);

	return sstyle->getStrokeWidth();
}
static tb_void_t g2_skia_style_width_set(tb_handle_t style, g2_float_t width)
{
	SkPaint* sstyle = static_cast<SkPaint*>(style);
	tb_assert_and_check_return(sstyle);

	sstyle->setStrokeWidth(width);
}
static tb_size_t g2_skia_style_cap(tb_handle_t style)
{
	SkPaint* sstyle = static_cast<SkPaint*>(style);
	tb_assert_and_check_return_val(sstyle, G2_STYLE_CAP_NONE);

	return sstyle->getStrokeCap() + 1;
}
static tb_void_t g2_skia_style_cap_set(tb_handle_t style, tb_size_t cap)
{
	SkPaint* sstyle = static_cast<SkPaint*>(style);
	tb_assert_and_check_return(sstyle && cap != G2_STYLE_CAP_NONE);

	sstyle->setStrokeCap(static_cast<SkPaint::Cap>(cap - 1));
}
static tb_size_t g2_skia_style_join(tb_handle_t style)
{
	SkPaint* sstyle = static_cast<SkPaint*>(style);
	tb_assert_and_check_return_val(sstyle, G2_STYLE_JOIN_NONE);

	return sstyle->getStrokeJoin() + 1;
}
static tb_void_t g2_skia_style_join_set(tb_handle_t style, tb_size_t join)
{
	SkPaint* sstyle = static_cast<SkPaint*>(style);
	tb_assert_and_check_return(sstyle && join != G2_STYLE_JOIN_NONE);

	sstyle->setStrokeJoin(static_cast<SkPaint::Join>(join - 1));
}
static tb_handle_t g2_skia_style_shader(tb_handle_t style)
{
	SkPaint* sstyle = static_cast<SkPaint*>(style);
	tb_assert_and_check_return_val(sstyle, TB_NULL);

	return static_cast<tb_handle_t>(sstyle->getShader());
}
static tb_void_t g2_skia_style_shader_set(tb_handle_t style, tb_handle_t shader)
{
	SkPaint* sstyle = static_cast<SkPaint*>(style);
	tb_assert_and_check_return(sstyle);

	// set shader
	sstyle->setShader(static_cast<SkShader*>(shader));
}

/* ///////////////////////////////////////////////////////////////////////
 * interfaces
 */
extern "C"
{
	tb_handle_t g2_style_init()
	{
		return g2_skia_style_init();
	}
	tb_void_t g2_style_exit(tb_handle_t style)
	{
		g2_skia_style_exit(style);
	}
	tb_void_t g2_style_clear(tb_handle_t style)
	{
		g2_skia_style_clear(style);
	}
	tb_size_t g2_style_mode(tb_handle_t style)
	{
		return g2_skia_style_mode(style);
	}
	tb_void_t g2_style_mode_set(tb_handle_t style, tb_size_t mode)
	{
		g2_skia_style_mode_set(style, mode);
	}
	tb_size_t g2_style_flag(tb_handle_t style)
	{
		return g2_skia_style_flag(style);
	}
	tb_void_t g2_style_flag_set(tb_handle_t style, tb_size_t flag)
	{
		g2_skia_style_flag_set(style, flag);
	}
	g2_color_t g2_style_color(tb_handle_t style)
	{
		return g2_skia_style_color(style);
	}
	tb_void_t g2_style_color_set(tb_handle_t style, g2_color_t color)
	{
		g2_skia_style_color_set(style, color);
	}
	tb_byte_t g2_style_alpha(tb_handle_t style)
	{
		return g2_skia_style_alpha(style);
	}
	tb_void_t g2_style_alpha_set(tb_handle_t style, tb_byte_t alpha)
	{
		g2_skia_style_alpha_set(style, alpha);
	}
	g2_float_t g2_style_width(tb_handle_t style)
	{
		return g2_skia_style_width(style);
	}
	tb_void_t g2_style_width_set(tb_handle_t style, g2_float_t width)
	{
		g2_skia_style_width_set(style, width);
	}
	tb_size_t g2_style_cap(tb_handle_t style)
	{
		return g2_skia_style_cap(style);
	}
	tb_void_t g2_style_cap_set(tb_handle_t style, tb_size_t cap)
	{
		g2_skia_style_cap_set(style, cap);
	}
	tb_size_t g2_style_join(tb_handle_t style)
	{
		return g2_skia_style_join(style);
	}
	tb_void_t g2_style_join_set(tb_handle_t style, tb_size_t join)
	{
		g2_skia_style_join_set(style, join);
	}
	tb_handle_t g2_style_shader(tb_handle_t style)
	{
		return g2_skia_style_shader(style);
	}
	tb_void_t g2_style_shader_set(tb_handle_t style, tb_handle_t shader)
	{
		g2_skia_style_shader_set(style, shader);
	}
}
