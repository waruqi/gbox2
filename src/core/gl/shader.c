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
 * @file		shader.c
 *
 */
/* ///////////////////////////////////////////////////////////////////////
 * includes
 */
#include "shader.h"
#include "context.h"

/* ///////////////////////////////////////////////////////////////////////
 * macros
 */

// the gradient texcoord size
#define G2_GL_SHADER_GRAD_TEXCOORD_SIZE 			(1024)

// the gradient stop maxn
#define G2_GL_SHADER_GRAD_STOP_MAXN 				(1024)

/* ///////////////////////////////////////////////////////////////////////
 * gl interfaces
 */

static __tb_inline__ g2_gl_shader_t* g2_gl_shader_init(tb_handle_t context, tb_size_t type, tb_size_t wrap)
{
	// check
	g2_gl_context_t* gcontext = (g2_gl_context_t*)context;
	tb_assert_and_check_return_val(gcontext && type, TB_NULL);

	// make texture
	GLuint* texture = g2_gl_context_texture_alc(context);
	tb_assert_and_check_return_val(texture, TB_NULL);

	// make shader
	g2_gl_shader_t* shader = g2_gl_context_shader_alc(context);
	tb_assert_and_check_return_val(shader, TB_NULL);

	// init shader
	shader->type 		= type;
	shader->wrap 		= wrap;
	shader->refn 		= 1;
	shader->texture 	= texture;
	shader->context 	= context;
	shader->flag 		= G2_GL_SHADER_FLAG_NONE;

	// init matrix
	g2_matrix_clear(&shader->matrix);

	// ok
	return shader;
}
static __tb_inline__ tb_void_t g2_gl_shader_exit(g2_gl_shader_t* shader)
{
	if (shader && shader->context)
	{
		// exit texture
		if (shader->texture) 
			g2_gl_context_texture_del(shader->context, shader->texture);

		// exit shader
		g2_gl_context_shader_del(shader->context, shader);
	}
}
static __tb_inline__ tb_size_t g2_shader_make_stops(g2_gradient_t const* gradient, g2_gl_stop_t* stops, tb_size_t maxn, tb_bool_t* alpha)
{
	// init
	tb_size_t 		stopn = 0;
	g2_float_t* 	radio = gradient->radio;
	g2_color_t* 	color = gradient->color;
	tb_size_t 		count = gradient->count;
	tb_assert(count < maxn);

	// no radio? make the average stops
	if (!radio)
	{
		tb_size_t i = 0;
		tb_bool_t a = TB_FALSE;
		tb_size_t n = tb_min(count, maxn - 1);
		for (i = 0; i < n; i++)
		{
			// add stop
			stops[i].radio = (i * G2_ONE) / n;
			stops[i].color = color[i];

			// has alpha?
			if (!a && color[i].a != 0xff) a = TB_TRUE;
		}

		// patch radio 1.0
		stops[i].radio = G2_ONE;
		stops[i].color = stops[n - 1].color;
		stopn = i + 1;

		// alpha?
		*alpha = a;
	}
	// check and patch radio
	else
	{
		tb_size_t 	i = 0;
		g2_float_t 	last = 0;
		tb_bool_t 	a = TB_FALSE;
		for (i = 0; i < count && stopn < maxn; i++)
		{
			// check range, must be [0, 1], skip it if out of range
			if (g2_lz(radio[i]) || g2_b1(radio[i])) continue ;

			// check repeat, skip it if repeat
			if (i && radio[i] == last) continue ;

			// check order, discard whole sequence if not in ascending order
			if (radio[i] < last) 
			{
				stopn = 0;
				break ;
			}

			// add stop at offset 0 with same color if first not at 0
			if (!i && g2_nz(radio[0]))
			{
				stops[stopn].radio = 0;
				stops[stopn].color = color[0];
				stopn++;
			}

			// add stop
			stops[stopn].radio = radio[i];
			stops[stopn].color = color[i];
			stopn++;

			// has alpha?
			if (!a && color[i].a != 0xff) a = TB_TRUE;

			// save the last radio
			last = radio[i];
		}

		// add stop at offset 1 with same color if last not at 1
		if (stopn && stopn < maxn && g2_n1(last))
		{
			stops[stopn].radio = G2_ONE;
			stops[stopn].color = color[count - 1];
			stopn++;
		}

		// alpha?
		*alpha = a;
	}


	// ok?
	return stopn;
}
static __tb_inline__ tb_void_t g2_shader_make_color_interpolation(tb_byte_t* pb, tb_byte_t* pe, g2_color_t cb, g2_color_t ce)
{
	// init width
	tb_long_t pw = (pe - pb) >> 2;
	tb_long_t rw = (ce.r - cb.r);
	tb_long_t gw = (ce.g - cb.g);
	tb_long_t bw = (ce.b - cb.b);
	tb_long_t aw = (ce.a - cb.a);
	
	// init scale
	tb_long_t rs = 1;
	tb_long_t gs = 1;
	tb_long_t bs = 1;
	tb_long_t as = 1;

	// adjust width & scale
	if (!pw) pw = 1;
	if (rw < 0)
	{
		rw = -rw;
		rs = -rs;
	}
	if (gw < 0) 
	{
		gw = -gw;
		gs = -gs;
	}
	if (bw < 0) 
	{
		bw = -bw;
		bs = -bs;
	}
	if (aw < 0) 
	{
		aw = -aw;
		as = -as;
	}

	// init step
	tb_long_t rn = 1;
	tb_long_t gn = 1;
	tb_long_t bn = 1;
	tb_long_t an = 1;
	if (rw > pw) rn = rw / pw + 1;
	if (gw > pw) gn = gw / pw + 1;
	if (bw > pw) bn = bw / pw + 1;
	if (aw > pw) bn = aw / pw + 1;

	// walk
	tb_long_t pi = 0;
	tb_long_t ri = 0;
	tb_long_t gi = 0;
	tb_long_t bi = 0;
	tb_long_t ai = 0;
	for (; pb < pe; pb += 4, pi++)
	{
		// do interpolation
		pb[0] = cb.r + rs * ri;
		pb[1] = cb.g + gs * gi;
		pb[2] = cb.b + bs * bi;
		pb[3] = cb.a + as * ai;

		// next
		if (rw * pi > ri * pw) ri += rn;
		if (gw * pi > gi * pw) gi += gn;
		if (bw * pi > bi * pw) bi += bn;
		if (aw * pi > ai * pw) ai += an;
	}
}
static __tb_inline__ tb_bool_t g2_shader_make_color(tb_byte_t* data, tb_size_t size, g2_gl_stop_t const* stops, tb_size_t stopn)
{
	// check
	tb_assert_and_check_return_val(data && size && stops && stopn, TB_FALSE);

	// init
	tb_size_t 	i = 0;
	tb_byte_t* 	pb = data;
	tb_byte_t* 	pe = data;
	g2_color_t 	cb = stops[0].color;
	g2_color_t 	ce = cb;
	for (i = 1; i < stopn; ++i, cb = ce, pb = pe)
	{
		// [pb, pe)
		pe = data + tb_align4(g2_float_to_long(stops[i].radio * size));
		tb_assert(pb < pe && pe <= data + size);

		// [cb, ce)
		ce = stops[i].color;

		// do interpolation
		g2_shader_make_color_interpolation(pb, pe, cb, ce);
	}

	// ok
	return TB_TRUE;
}
static __tb_inline__ tb_bool_t g2_shader_make_gradient(g2_gl_shader_t* shader, g2_gradient_t const* gradient, tb_byte_t* data, tb_size_t size, tb_bool_t* alpha)
{
	// make stops
	g2_gl_stop_t 	stops[G2_GL_SHADER_GRAD_STOP_MAXN];
	tb_size_t 		stopn = g2_shader_make_stops(gradient, stops, G2_GL_SHADER_GRAD_STOP_MAXN, alpha);
	tb_assert_and_check_return_val(stopn, TB_FALSE);

	// make color
	return g2_shader_make_color(data, size, stops, stopn);
}

/* ///////////////////////////////////////////////////////////////////////
 * interfaces
 */
tb_handle_t g2_shader_init_linear(tb_handle_t context, g2_point_t const* pb, g2_point_t const* pe, g2_gradient_t const* gradient, tb_size_t wrap)
{
	// check
	tb_assert_and_check_return_val(context && pb && pe && gradient && gradient->color && gradient->count && wrap, TB_NULL);

	// init shader
	g2_gl_shader_t* shader = g2_gl_shader_init(context, G2_GL_SHADER_TYPE_GRADIENT_LINEAR, wrap);
	tb_assert_and_check_return_val(shader && shader->texture, TB_NULL);

	// init linear
	shader->u.linear.pb = *pb;
	shader->u.linear.pe = *pe;
	
	// make gradient
	tb_bool_t 		alpha = TB_FALSE;
	tb_byte_t 		data[G2_GL_SHADER_GRAD_TEXCOORD_SIZE << 2];
	if (!g2_shader_make_gradient(shader, gradient, data, tb_arrayn(data), &alpha)) goto fail;

	// alpha?
	if (alpha) shader->flag |= G2_GL_SHADER_FLAG_ALPHA;

	// make texture
	glBindTexture(GL_TEXTURE_1D, *shader->texture);
 	glPixelStorei(GL_UNPACK_ALIGNMENT, 1);
	glTexImage1D(GL_TEXTURE_1D, 0, GL_RGBA, G2_GL_SHADER_GRAD_TEXCOORD_SIZE, 0, GL_RGBA, GL_UNSIGNED_BYTE, data);

	// ok
	return shader;

fail:
	if (shader) g2_gl_shader_exit(shader);
	return TB_NULL;
}
tb_handle_t g2_shader_init_radial(tb_handle_t context, g2_circle_t const* cp, g2_gradient_t const* gradient, tb_size_t wrap)
{
	// check
	tb_assert_and_check_return_val(context && cp && gradient && gradient->color && gradient->count && wrap, TB_NULL);

	// init shader
	g2_gl_shader_t* shader = g2_gl_shader_init(context, G2_GL_SHADER_TYPE_GRADIENT_RADIAL, wrap);
	tb_assert_and_check_return_val(shader && shader->texture, TB_NULL);

	// init radial
	shader->u.radial.cp = *cp;
	
	// make gradient
	tb_bool_t 		alpha = TB_FALSE;
	tb_byte_t 		data[G2_GL_SHADER_GRAD_TEXCOORD_SIZE << 2];
	if (!g2_shader_make_gradient(shader, gradient, data, tb_arrayn(data), &alpha)) goto fail;

	// alpha?
	if (alpha) shader->flag |= G2_GL_SHADER_FLAG_ALPHA;

	// make texture
	glBindTexture(GL_TEXTURE_1D, *shader->texture);
 	glPixelStorei(GL_UNPACK_ALIGNMENT, 1);
	glTexImage1D(GL_TEXTURE_1D, 0, GL_RGBA, G2_GL_SHADER_GRAD_TEXCOORD_SIZE, 0, GL_RGBA, GL_UNSIGNED_BYTE, data);

	// ok
	return shader;

fail:
	if (shader) g2_gl_shader_exit(shader);
	return TB_NULL;
}
tb_handle_t g2_shader_init_radial2(tb_handle_t context, g2_circle_t const* cb, g2_circle_t const* ce, g2_gradient_t const* gradient, tb_size_t wrap)
{
	// check
	tb_assert_and_check_return_val(context && cb && ce && gradient && gradient->color && gradient->count && wrap, TB_NULL);

	// init shader
	g2_gl_shader_t* shader = g2_gl_shader_init(context, G2_GL_SHADER_TYPE_GRADIENT_RADIAL2, wrap);
	tb_assert_and_check_return_val(shader && shader->texture, TB_NULL);

	// init radial2
	shader->u.radial2.cb = *cb;
	shader->u.radial2.ce = *ce;

	// make gradient
	tb_bool_t 		alpha = TB_FALSE;
	tb_byte_t 		data[G2_GL_SHADER_GRAD_TEXCOORD_SIZE << 2];
	if (!g2_shader_make_gradient(shader, gradient, data, tb_arrayn(data), &alpha)) goto fail;

	// alpha?
	if (alpha) shader->flag |= G2_GL_SHADER_FLAG_ALPHA;

	// make texture
	glBindTexture(GL_TEXTURE_1D, *shader->texture);
 	glPixelStorei(GL_UNPACK_ALIGNMENT, 1);
	glTexImage1D(GL_TEXTURE_1D, 0, GL_RGBA, G2_GL_SHADER_GRAD_TEXCOORD_SIZE, 0, GL_RGBA, GL_UNSIGNED_BYTE, data);

	// ok
	return shader;

fail:
	if (shader) g2_gl_shader_exit(shader);
	return TB_NULL;
}
tb_handle_t g2_shader_init_bitmap(tb_handle_t context, tb_handle_t bitmap, tb_size_t wrap)
{
	// check
	tb_assert_and_check_return_val(context && bitmap && wrap, TB_NULL);

	// data & size
	tb_pointer_t 	data = g2_bitmap_data(bitmap);
	tb_size_t 		size = g2_bitmap_size(bitmap);
	tb_assert_and_check_return_val(data && size, TB_NULL);

	// width & height 
	tb_size_t 		width = g2_bitmap_width(bitmap);
	tb_size_t 		height = g2_bitmap_height(bitmap);
	tb_assert_and_check_return_val(width && height, TB_NULL);

	// pixfmt
	tb_size_t 		pixfmt = g2_bitmap_pixfmt(bitmap);
	tb_assert_and_check_return_val( 	(G2_PIXFMT(pixfmt) == G2_PIXFMT_ARGB8888 && !G2_PIXFMT_BE(pixfmt))
									|| 	(G2_PIXFMT(pixfmt) == G2_PIXFMT_RGBA8888 && G2_PIXFMT_BE(pixfmt)), TB_NULL);

	// init shader
	g2_gl_shader_t* shader = g2_gl_shader_init(context, G2_GL_SHADER_TYPE_BITMAP, wrap);
	tb_assert_and_check_return_val(shader && shader->texture, TB_NULL);

	// init width & height
	shader->u.image.width 		= width;
	shader->u.image.height 		= height;

	// alpha?
	if (g2_bitmap_flag(bitmap) & G2_BITMAP_FLAG_ALPHA)
		shader->flag |= G2_GL_SHADER_FLAG_ALPHA;

	// make texture
	glBindTexture(GL_TEXTURE_2D, *shader->texture);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, G2_PIXFMT_BE(pixfmt)? GL_RGBA : GL_BGRA, GL_UNSIGNED_BYTE, data);

	// ok
	return shader;
}
tb_void_t g2_shader_exit(tb_handle_t shader)
{
	// shader
	g2_gl_shader_t* gshader = (g2_gl_shader_t*)shader;
	tb_assert_and_check_return(gshader);

	// refn--
	g2_shader_dec(shader);
}
g2_matrix_t const* g2_shader_matrix(tb_handle_t shader)
{
	// shader
	g2_gl_shader_t* gshader = (g2_gl_shader_t*)shader;
	tb_assert_and_check_return_val(gshader, TB_NULL);

	return &gshader->matrix;
}
tb_void_t g2_shader_matrix_set(tb_handle_t shader, g2_matrix_t const* matrix)
{
	// shader
	g2_gl_shader_t* gshader = (g2_gl_shader_t*)shader;
	tb_assert_and_check_return(gshader);

	if (matrix) gshader->matrix = *matrix;
	else g2_matrix_clear(&gshader->matrix);
}
tb_size_t g2_shader_ref(tb_handle_t shader)
{
	// shader
	g2_gl_shader_t* gshader = (g2_gl_shader_t*)shader;
	tb_assert_and_check_return_val(gshader, 0);

	// refn
	return gshader->refn;
}
tb_void_t g2_shader_inc(tb_handle_t shader)
{
	// shader
	g2_gl_shader_t* gshader = (g2_gl_shader_t*)shader;
	tb_assert_and_check_return(gshader && gshader->refn);

	// refn++
	gshader->refn++;
}
tb_void_t g2_shader_dec(tb_handle_t shader)
{
	// shader
	g2_gl_shader_t* gshader = (g2_gl_shader_t*)shader;
	tb_assert_and_check_return(gshader && gshader->refn);

	// refn--
	if (gshader->refn > 1) gshader->refn--;
	else g2_gl_shader_exit(gshader);
}
