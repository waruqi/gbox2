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
 * @file		transform.h
 *
 */
#ifndef G2_SVG_PARSER_TRANSFORM_H
#define G2_SVG_PARSER_TRANSFORM_H

/* ///////////////////////////////////////////////////////////////////////
 * includes
 */
#include "prefix.h"
#include "float.h"
#include "separator.h"

/* ///////////////////////////////////////////////////////////////////////
 * inlines
 */

// translate(<tx> [<ty>])
static __tb_inline__ tb_char_t const* g2_svg_parser_transform_translate(tb_char_t const* p, g2_matrix_t* matrix)
{
	// init
	g2_float_t tx = 0; 
	g2_float_t ty = 0; 

	// skip name
	p += 9;

	// skip '('
	while (*p && *p != '(') p++; p++;

	// tx
	p = g2_svg_parser_float(p, &tx); p = g2_svg_parser_separator_skip(p);

	// ty
	if (*p != ')') { p = g2_svg_parser_float(p, &ty); p = g2_svg_parser_separator_skip(p); }

	// skip ')'
	while (*p && *p != ')') p++; p++;

	// translate
	g2_matrix_translate(matrix, tx, ty);

	// trace
	tb_trace_impl("transform: translate: %f, %f", g2_float_to_tb(tx), g2_float_to_tb(ty));

	// ok
	return p;
}
// scale(<sx> [<sy>])
static __tb_inline__ tb_char_t const* g2_svg_parser_transform_scale(tb_char_t const* p, g2_matrix_t* matrix)
{
	// init
	g2_float_t sx = 0; 
	g2_float_t sy = 0; 

	// skip name
	p += 5;

	// skip '('
	while (*p && *p != '(') p++; p++;

	// sx
	p = g2_svg_parser_float(p, &sx); p = g2_svg_parser_separator_skip(p);

	// sy
	if (*p != ')') { p = g2_svg_parser_float(p, &sy); p = g2_svg_parser_separator_skip(p); }
	else sy = sx;

	// skip ')'
	while (*p && *p != ')') p++; p++;

	// scale
	g2_matrix_scale(matrix, sx, sy);

	// trace
	tb_trace_impl("transform: scale: %f, %f", g2_float_to_tb(sx), g2_float_to_tb(sy));

	// ok
	return p;
}
// rotate(<rotate-angle> [<cx> <cy>])
static __tb_inline__ tb_char_t const* g2_svg_parser_transform_rotate(tb_char_t const* p, g2_matrix_t* matrix)
{
	// init
	g2_float_t 	ra = 0; 
	g2_float_t 	cx = 0; 
	g2_float_t 	cy = 0; 
	tb_size_t 	bc = 0;

	// skip name
	p += 6;

	// skip '('
	while (*p && *p != '(') p++; p++;

	// ra
	p = g2_svg_parser_float(p, &ra); p = g2_svg_parser_separator_skip(p);

	// cx
	if (*p != ')') { p = g2_svg_parser_float(p, &cx); p = g2_svg_parser_separator_skip(p); bc = 1; }

	// cy
	if (*p != ')') { p = g2_svg_parser_float(p, &cy); p = g2_svg_parser_separator_skip(p); bc = 1; }

	// skip ')'
	while (*p && *p != ')') p++; p++;

	// rotate
	if (bc) g2_matrix_translate(matrix, cx, cy);
	g2_matrix_rotate(matrix, ra);
	if (bc) g2_matrix_translate(matrix, -cx, -cy);

	// trace
	tb_trace_impl("transform: rotate: %f, %f, %f", g2_float_to_tb(ra), g2_float_to_tb(cx), g2_float_to_tb(cy));

	// ok
	return p;
}
// skewX(<skew-angle>)
static __tb_inline__ tb_char_t const* g2_svg_parser_transform_skew_x(tb_char_t const* p, g2_matrix_t* matrix)
{
	// init
	g2_float_t kx = 0; 

	// skip name
	p += 5;

	// skip '('
	while (*p && *p != '(') p++; p++;

	// kx
	p = g2_svg_parser_float(p, &kx); p = g2_svg_parser_separator_skip(p);

	// skip ')'
	while (*p && *p != ')') p++; p++;

	// skew
	g2_matrix_skew(matrix, kx, 0);

	// trace
	tb_trace_impl("transform: skew_x: %f", g2_float_to_tb(kx));

	// ok
	return p;
}
// skewY(<skew-angle>)
static __tb_inline__ tb_char_t const* g2_svg_parser_transform_skew_y(tb_char_t const* p, g2_matrix_t* matrix)
{
	// init
	g2_float_t ky = 0; 

	// skip name
	p += 5;

	// skip '('
	while (*p && *p != '(') p++; p++;

	// ky
	p = g2_svg_parser_float(p, &ky); p = g2_svg_parser_separator_skip(p);

	// skip ')'
	while (*p && *p != ')') p++; p++;

	// skew
	g2_matrix_skew(matrix, 0, ky);

	// trace
	tb_trace_impl("transform: skew_y: %f", g2_float_to_tb(ky));

	// ok
	return p;
}
// matrix(<a> <b> <c> <d> <e> <f>)
static __tb_inline__ tb_char_t const* g2_svg_parser_transform_matrix(tb_char_t const* p, g2_matrix_t* matrix)
{
	// init
	g2_float_t sx = 0; 
	g2_float_t ky = 0; 
	g2_float_t kx = 0; 
	g2_float_t sy = 0; 
	g2_float_t tx = 0; 
	g2_float_t ty = 0; 

	// skip name
	p += 6;

	// skip '('
	while (*p && *p != '(') p++; p++;

	// sx
	p = g2_svg_parser_float(p, &sx); p = g2_svg_parser_separator_skip(p);

	// ky
	if (*p != ')') { p = g2_svg_parser_float(p, &ky); p = g2_svg_parser_separator_skip(p); }

	// kx
	if (*p != ')') { p = g2_svg_parser_float(p, &kx); p = g2_svg_parser_separator_skip(p); }

	// sy
	if (*p != ')') { p = g2_svg_parser_float(p, &sy); p = g2_svg_parser_separator_skip(p); }

	// tx
	if (*p != ')') { p = g2_svg_parser_float(p, &tx); p = g2_svg_parser_separator_skip(p); }

	// ty
	if (*p != ')') { p = g2_svg_parser_float(p, &ty); p = g2_svg_parser_separator_skip(p); }

	// skip ')'
	while (*p && *p != ')') p++; p++;

	// matrix
	g2_matrix_t mx;
	g2_matrix_init(&mx, sx, kx, ky, sy, tx, ty);
	g2_matrix_multiply(matrix, &mx);

	// trace
	tb_trace_impl("transform: matrix: %f, %f, %f, %f, %f, %f", g2_float_to_tb(sx), g2_float_to_tb(ky), g2_float_to_tb(kx), g2_float_to_tb(sy), g2_float_to_tb(tx), g2_float_to_tb(ty));

	// ok
	return p;
}
// e.g. <g transform="translate(-10,-20) scale(2) rotate(45) translate(5,10)">
static __tb_inline__ tb_char_t const* g2_svg_parser_transform(tb_char_t const* p, g2_matrix_t* matrix)
{
	// check
	tb_assert(matrix);

	// done
	while (*p)
	{
		if (!tb_isspace(*p))
		{
			if (!tb_strnicmp(p, "translate", 9))
				p = g2_svg_parser_transform_translate(p, matrix);
			else if (!tb_strnicmp(p, "scale", 5))
				p = g2_svg_parser_transform_scale(p, matrix);
			else if (!tb_strnicmp(p, "skewX", 5))
				p = g2_svg_parser_transform_skew_x(p, matrix);
			else if (!tb_strnicmp(p, "skewY", 5))
				p = g2_svg_parser_transform_skew_y(p, matrix);
			else if (!tb_strnicmp(p, "rotate", 6))
				p = g2_svg_parser_transform_rotate(p, matrix);
			else if (!tb_strnicmp(p, "matrix", 6))
				p = g2_svg_parser_transform_matrix(p, matrix);
			else p++;
		}
		else p++;
	}
	return p;
}

#endif


