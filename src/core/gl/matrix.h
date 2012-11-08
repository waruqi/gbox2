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
 * @file		matrix.h
 *
 */
#ifndef G2_CORE_GL_MATRIX_H
#define G2_CORE_GL_MATRIX_H

/* ///////////////////////////////////////////////////////////////////////
 * includes
 */
#include "prefix.h"

/* ///////////////////////////////////////////////////////////////////////
 * inlines
 */
static __tb_inline__ tb_void_t g2_gl_matrix_init(tb_float_t* gmatrix, tb_float_t sx, tb_float_t kx, tb_float_t ky, tb_float_t sy, tb_float_t tx, tb_float_t ty)
{
	gmatrix[0] 	= sx;
	gmatrix[1] 	= ky;
	gmatrix[2] 	= 0.0f;
	gmatrix[3] 	= 0.0f;
	gmatrix[4] 	= kx;
	gmatrix[5] 	= sy;
	gmatrix[6] 	= 0.0f; 
	gmatrix[7] 	= 0.0f;       
	gmatrix[8] 	= 0.0f;
	gmatrix[9] 	= 0.0f; 
	gmatrix[10] = 1.0f; 
	gmatrix[11] = 0.0f; 
	gmatrix[12] = tx; 
	gmatrix[13] = ty; 
	gmatrix[14] = 0.0f;
	gmatrix[15] = 1.0f;
}
static __tb_inline__ tb_void_t g2_gl_matrix_init_sincos(tb_float_t* gmatrix, tb_float_t sin, tb_float_t cos)
{
	g2_gl_matrix_init(gmatrix, cos, -sin, sin, cos, 0.0f, 0.0f);	
}
static __tb_inline__ tb_void_t g2_gl_matrix_init_sincosp(tb_float_t* gmatrix, tb_float_t sin, tb_float_t cos, tb_float_t px, tb_float_t py)
{
    tb_float_t const one_cos = 1.0f - cos;
	g2_gl_matrix_init(gmatrix, cos, -sin, sin, cos, sin * py + one_cos * px, -sin * px + one_cos * py);	
}
static __tb_inline__ tb_void_t g2_gl_matrix_init_rotate(tb_float_t* gmatrix, tb_float_t degrees)
{
	tb_float_t s;
	tb_float_t c;
	tb_sincosf((degrees * TB_PI) / 180., &s, &c);
	g2_gl_matrix_init_sincos(gmatrix, s, c);
}
static __tb_inline__ tb_void_t g2_gl_matrix_init_rotatep(tb_float_t* gmatrix, tb_float_t degrees, tb_float_t px, tb_float_t py)
{
	tb_float_t s;
	tb_float_t c;
	tb_sincosf((degrees * TB_PI) / 180., &s, &c);
	g2_gl_matrix_init_sincosp(gmatrix, s, c, px, py);
}
static __tb_inline__ tb_void_t g2_gl_matrix_init_skew(tb_float_t* gmatrix, tb_float_t kx, tb_float_t ky)
{
	g2_gl_matrix_init(gmatrix, 1.0f, kx, ky, 1.0f, 0.0f, 0.0f);
}
static __tb_inline__ tb_void_t g2_gl_matrix_init_skewp(tb_float_t* gmatrix, tb_float_t kx, tb_float_t ky, tb_float_t px, tb_float_t py)
{
	g2_gl_matrix_init(gmatrix, 1.0f, kx, ky, 1.0f, -kx * py, -ky * px);
}
static __tb_inline__ tb_void_t g2_gl_matrix_init_scale(tb_float_t* gmatrix, tb_float_t sx, tb_float_t sy)
{
	g2_gl_matrix_init(gmatrix, sx, 0.0f, 0.0f, sy, 0.0f, 0.0f);
}
static __tb_inline__ tb_void_t g2_gl_matrix_init_scalep(tb_float_t* gmatrix, tb_float_t sx, tb_float_t sy, tb_float_t px, tb_float_t py)
{
	g2_gl_matrix_init(gmatrix, sx, 0.0f, 0.0f, sy, px - sx * px, py - sy * py);
}
static __tb_inline__ tb_void_t g2_gl_matrix_init_translate(tb_float_t* gmatrix, tb_float_t tx, tb_float_t ty)
{
	g2_gl_matrix_init(gmatrix, 1.0f, 0.0f, 0.0f, 1.0f, tx, ty);
}
static __tb_inline__ tb_void_t g2_gl_matrix_clear(tb_float_t* gmatrix)
{
	g2_gl_matrix_init(gmatrix, 1.0f, 0.0f, 0.0f, 1.0f, 0.0f, 0.0f);
}
static __tb_inline__ tb_void_t g2_gl_matrix_copy(tb_float_t* gmatrix, tb_float_t const* gmatrix2)
{
	tb_memcpy(gmatrix, gmatrix2, sizeof(tb_float_t) << 4);
}
static __tb_inline__ tb_void_t g2_gl_matrix_from(tb_float_t* gmatrix, g2_matrix_t const* matrix)
{
	g2_gl_matrix_init(gmatrix, g2_float_to_tb(matrix->sx), g2_float_to_tb(matrix->kx), g2_float_to_tb(matrix->ky), g2_float_to_tb(matrix->sy), g2_float_to_tb(matrix->tx), g2_float_to_tb(matrix->ty));
}
static __tb_inline__ tb_void_t g2_gl_matrix_ortho(tb_float_t* gmatrix, tb_float_t left, tb_float_t right, tb_float_t bottom, tb_float_t top, tb_float_t nearp, tb_float_t farp)
{
	g2_gl_matrix_clear(gmatrix);
	gmatrix[0] 	= 2.0f / (right - left);
	gmatrix[5] 	= 2.0f / (top - bottom);
    gmatrix[10] = -2.0f / (farp - nearp);  
    gmatrix[12] = -(right + left) / (right - left);  
    gmatrix[13] = -(top + bottom) / (top - bottom);  
    gmatrix[14] = -(farp + nearp) / (farp - nearp); 
}
static __tb_inline__ tb_void_t g2_gl_matrix_multiply(tb_float_t* gmatrix, tb_float_t const* gmatrix2)
{
	tb_float_t sx = gmatrix[0] * gmatrix2[0] + gmatrix[4] * gmatrix2[1];
	tb_float_t ky = gmatrix[1] * gmatrix2[0] + gmatrix[5] * gmatrix2[1];

	tb_float_t kx = gmatrix[0] * gmatrix2[4] + gmatrix[4] * gmatrix2[5];
	tb_float_t sy = gmatrix[1] * gmatrix2[4] + gmatrix[5] * gmatrix2[5];

	tb_float_t tx = gmatrix[0] * gmatrix2[12] + gmatrix[4] * gmatrix2[13] + gmatrix[12];
	tb_float_t ty = gmatrix[1] * gmatrix2[12] + gmatrix[5] * gmatrix2[13] + gmatrix[13];

	g2_gl_matrix_init(gmatrix, sx, kx, ky, sy, tx, ty);
}
static __tb_inline__ tb_void_t g2_gl_matrix_scale(tb_float_t* gmatrix, tb_float_t sx, tb_float_t sy)
{
	gmatrix[0] *= sx;
	gmatrix[1] *= sx;
	gmatrix[4] *= sy;
	gmatrix[5] *= sy;
}
static __tb_inline__ tb_void_t g2_gl_matrix_translate(tb_float_t* gmatrix, tb_float_t dx, tb_float_t dy)
{
	gmatrix[12] += gmatrix[0] * dx + gmatrix[4] * dy;
	gmatrix[13] += gmatrix[1] * dx + gmatrix[5] * dy;
}
static __tb_inline__ tb_void_t g2_gl_matrix_rotate(tb_float_t* gmatrix, tb_float_t degrees)
{
	// rotate
	tb_float_t mx[16];
	g2_gl_matrix_init_rotate(mx, degrees);
	g2_gl_matrix_multiply(gmatrix, mx);
}
static __tb_inline__ tb_void_t g2_gl_matrix_rotatep(tb_float_t* gmatrix, tb_float_t degrees, tb_float_t px, tb_float_t py)
{
	// rotate
	tb_float_t mx[16];
	g2_gl_matrix_init_rotatep(mx, degrees, px, py);
	g2_gl_matrix_multiply(gmatrix, mx);
}
#endif
