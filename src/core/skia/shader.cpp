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
 * @file		shader.cpp
 *
 */

/* ///////////////////////////////////////////////////////////////////////
 * includes
 */
#include "prefix.h"
#include "../shader.h"

/* ///////////////////////////////////////////////////////////////////////
 * macros
 */
#ifdef SK_SCALAR_IS_FLOAT
# 	define kMatrix22Elem 	SK_Scalar1
#else
# 	define kMatrix22Elem 	SK_Fract1
#endif

/* ///////////////////////////////////////////////////////////////////////
 * implementation
 */
static tb_handle_t g2_skia_shader_init_linear(tb_handle_t context, g2_point_t const* pb, g2_point_t const* pe, g2_gradient_t const* gradient, tb_size_t wrap)
{
	// check
	tb_assert_and_check_return_val(pb && pe && gradient && gradient->color && gradient->count, TB_NULL);

	// the border wrap is not supported for skia
	if (wrap == G2_SHADER_WRAP_BORDER) wrap = G2_SHADER_WRAP_CLAMP;
	tb_assert_and_check_return_val(wrap > 1, TB_NULL);

	// init shader
	SkPoint pts[2];
	pts[0] = SkPoint::Make(pb->x, pb->y);
	pts[1] = SkPoint::Make(pe->x, pe->y);
	return SkGradientShader::CreateLinear(pts, reinterpret_cast<SkColor*>(gradient->color), gradient->radio, gradient->count, static_cast<SkShader::TileMode>(wrap - 2));
}
static tb_handle_t g2_skia_shader_init_radial(tb_handle_t context, g2_circle_t const* cp, g2_gradient_t const* gradient, tb_size_t wrap)
{
	// check
	tb_assert_and_check_return_val(cp && gradient && gradient->color && gradient->count, TB_NULL);

	// the border wrap is not supported for skia
	if (wrap == G2_SHADER_WRAP_BORDER) wrap = G2_SHADER_WRAP_CLAMP;
	tb_assert_and_check_return_val(wrap > 1, TB_NULL);

	// init shader
	SkPoint pt = SkPoint::Make(cp->c.x, cp->c.y);
	return SkGradientShader::CreateRadial(pt, cp->r, reinterpret_cast<SkColor*>(gradient->color), gradient->radio, gradient->count, static_cast<SkShader::TileMode>(wrap - 2));
}
static tb_handle_t g2_skia_shader_init_radial2(tb_handle_t context, g2_circle_t const* cb, g2_circle_t const* ce, g2_gradient_t const* gradient, tb_size_t wrap)
{
	// check
	tb_assert_and_check_return_val(cb && ce && gradient && gradient->color && gradient->count, TB_NULL);

	// the border wrap is not supported for skia
	if (wrap == G2_SHADER_WRAP_BORDER) wrap = G2_SHADER_WRAP_CLAMP;
	tb_assert_and_check_return_val(wrap > 1, TB_NULL);

	// init shader
	SkPoint p1 = SkPoint::Make(cb->c.x, cb->c.y);
	SkPoint p2 = SkPoint::Make(ce->c.x, ce->c.y);
	return SkGradientShader::CreateTwoPointRadial(p1, cb->r, p2, ce->r, reinterpret_cast<SkColor*>(gradient->color), gradient->radio, gradient->count, static_cast<SkShader::TileMode>(wrap - 2));
}
static tb_handle_t g2_skia_shader_init_bitmap(tb_handle_t context, tb_handle_t bitmap, tb_size_t wrap)
{
	// check
	tb_assert_and_check_return_val(bitmap, TB_NULL);

	// the border wrap is not supported for skia
	if (wrap == G2_SHADER_WRAP_BORDER) wrap = G2_SHADER_WRAP_CLAMP;
	tb_assert_and_check_return_val(wrap > 1, TB_NULL);

	// init shader
	return SkShader::CreateBitmapShader(*static_cast<SkBitmap const*>(bitmap), static_cast<SkShader::TileMode>(wrap - 2), static_cast<SkShader::TileMode>(wrap - 2));
}
static tb_void_t g2_skia_shader_exit(tb_handle_t shader)
{
	SkShader* sshader = static_cast<SkShader*>(shader);
	tb_assert_and_check_return(sshader);

	sshader->unref();
}
static g2_matrix_t const* g2_skia_shader_matrix(tb_handle_t shader)
{
	SkShader* sshader = static_cast<SkShader*>(shader);
	tb_assert_and_check_return_val(sshader, TB_NULL);

	SkMatrix mx;
	if (!sshader->getLocalMatrix(&mx)) return TB_NULL;

	g2_matrix_init(&sshader->matrix, mx.getScaleX(), mx.getScaleY(), mx.getSkewX(), mx.getSkewY(), mx.getTranslateX(), mx.getTranslateY());
	return &sshader->matrix;
}
static tb_void_t g2_skia_shader_matrix_set(tb_handle_t shader, g2_matrix_t const* matrix)
{
	SkShader* sshader = static_cast<SkShader*>(shader);
	tb_assert_and_check_return(sshader);

	if (matrix)
	{
		SkMatrix mx;
		mx.setAll( 	matrix->sx, matrix->kx, matrix->tx
				, 	matrix->ky, matrix->sy, matrix->ty
				, 	0, 0, kMatrix22Elem);
		sshader->setLocalMatrix(mx);
	}
	else sshader->resetLocalMatrix();
}
static tb_size_t g2_skia_shader_ref(tb_handle_t shader)
{
	SkShader* sshader = static_cast<SkShader*>(shader);
	tb_assert_and_check_return_val(sshader, 0);

	return sshader->getRefCnt();
}
static tb_void_t g2_skia_shader_inc(tb_handle_t shader)
{
	SkShader* sshader = static_cast<SkShader*>(shader);
	tb_assert_and_check_return(sshader);

	sshader->ref();
}
static tb_void_t g2_skia_shader_dec(tb_handle_t shader)
{
	SkShader* sshader = static_cast<SkShader*>(shader);
	tb_assert_and_check_return(sshader);

	sshader->unref();
}

/* ///////////////////////////////////////////////////////////////////////
 * interfaces
 */
extern "C"
{
	tb_handle_t g2_shader_init_linear(tb_handle_t context, g2_point_t const* pb, g2_point_t const* pe, g2_gradient_t const* gradient, tb_size_t wrap)
	{
		return g2_skia_shader_init_linear(context, pb, pe, gradient, wrap);
	}
	tb_handle_t g2_shader_init_radial(tb_handle_t context, g2_circle_t const* cp, g2_gradient_t const* gradient, tb_size_t wrap)
	{
		return g2_skia_shader_init_radial(context, cp, gradient, wrap);
	}
	tb_handle_t g2_shader_init_radial2(tb_handle_t context, g2_circle_t const* cb, g2_circle_t const* ce, g2_gradient_t const* gradient, tb_size_t wrap)
	{
		return g2_skia_shader_init_radial2(context, cb, ce, gradient, wrap);
	}
	tb_handle_t g2_shader_init_bitmap(tb_handle_t context, tb_handle_t bitmap, tb_size_t wrap)
	{
		return g2_skia_shader_init_bitmap(context, bitmap, wrap);
	}
	tb_void_t g2_shader_exit(tb_handle_t shader)
	{
		g2_skia_shader_exit(shader);
	}
	g2_matrix_t const* g2_shader_matrix(tb_handle_t shader)
	{
		return g2_skia_shader_matrix(shader);
	}
	tb_void_t g2_shader_matrix_set(tb_handle_t shader, g2_matrix_t const* matrix)
	{
		g2_skia_shader_matrix_set(shader, matrix);
	}
	tb_size_t g2_shader_ref(tb_handle_t shader)
	{
		return g2_skia_shader_ref(shader);
	}
	tb_void_t g2_shader_inc(tb_handle_t shader)
	{
		g2_skia_shader_inc(shader);
	}
	tb_void_t g2_shader_dec(tb_handle_t shader)
	{
		g2_skia_shader_dec(shader);
	}
}
