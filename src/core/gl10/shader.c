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
#include "matrix.h"

/* ///////////////////////////////////////////////////////////////////////
 * gl10 interfaces
 */

g2_gl10_shader_t* g2_gl10_shader_init(tb_size_t type, tb_size_t mode)
{
	// check
	tb_assert_and_check_return_val(type, TB_NULL);

	// make texture
	tb_uint_t texture = 0;
 	glGenTextures(1, &texture);
	glBindTexture(GL_TEXTURE_2D, texture);
	tb_assert_and_check_return_val(glIsTexture(texture), TB_NULL);

	// make shader
	g2_gl10_shader_t* shader = tb_malloc0(sizeof(g2_gl10_shader_t));
	tb_assert_and_check_return_val(shader, TB_NULL);

	// init shader
	shader->type = type;
	shader->mode = mode;
	shader->refn = 1;
	shader->texture = texture;

	// init matrix
	g2_matrix_clear(&shader->matrix);
	g2_gl10_matrix_init(shader->matrix_gl);

	// ok
	return shader;
}
tb_void_t g2_gl10_shader_exit(g2_gl10_shader_t* shader)
{
	if (shader)
	{
		// exit texture
		tb_uint_t texture = shader->texture;
 		if (glIsTexture(texture))
 			glDeleteTextures(1, &texture);

		// exit it
		tb_free(shader);
	}
}

/* ///////////////////////////////////////////////////////////////////////
 * interfaces
 */
tb_handle_t g2_shader_init_linear(g2_point_t const* pb, g2_point_t const* pe, g2_gradient_t const* gradient, tb_size_t mode)
{
	tb_trace_noimpl();
	return TB_NULL;
}
tb_handle_t g2_shader_init_radial(g2_circle_t const* cp, g2_gradient_t const* gradient, tb_size_t mode)
{
	tb_trace_noimpl();
	return TB_NULL;
}
tb_handle_t g2_shader_init_radial2(g2_circle_t const* cb, g2_circle_t const* ce, g2_gradient_t const* gradient, tb_size_t mode)
{
	tb_trace_noimpl();
	return TB_NULL;
}
tb_handle_t g2_shader_init_bitmap(tb_handle_t bitmap, tb_size_t mode)
{
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
	tb_assert_and_check_return_val(G2_PIXFMT(pixfmt) == G2_PIXFMT_ARGB8888, TB_NULL);

	// init
	g2_gl10_shader_t* shader = g2_gl10_shader_init(G2_GL10_SHADER_TYPE_BITMAP, mode);
	tb_assert_and_check_return_val(shader, TB_NULL);

	// make texture
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, G2_PIXFMT_BE(pixfmt)? GL_BGRA : GL_BGRA, GL_UNSIGNED_BYTE, data);

	// ok
	return shader;
}
tb_void_t g2_shader_exit(tb_handle_t shader)
{
	// shader
	g2_gl10_shader_t* gshader = (g2_gl10_shader_t*)shader;
	tb_assert_and_check_return(gshader);

}
g2_matrix_t const* g2_shader_matrix(tb_handle_t shader)
{
	// shader
	g2_gl10_shader_t* gshader = (g2_gl10_shader_t*)shader;
	tb_assert_and_check_return_val(gshader, TB_NULL);

	return &gshader->matrix;
}
tb_void_t g2_shader_matrix_set(tb_handle_t shader, g2_matrix_t const* matrix)
{
	// shader
	g2_gl10_shader_t* gshader = (g2_gl10_shader_t*)shader;
	tb_assert_and_check_return(gshader);

	if (matrix) gshader->matrix = *matrix;
	else g2_matrix_clear(&gshader->matrix);
}
