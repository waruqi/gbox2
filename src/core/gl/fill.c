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
 * @file		fill.c
 *
 */

/* ///////////////////////////////////////////////////////////////////////
 * trace
 */
#define TB_TRACE_IMPL_TAG 		"fill"

/* ///////////////////////////////////////////////////////////////////////
 * includes
 */
#include "fill.h"
#include "shader.h"
#include "../soft/split/split.h"

/* ///////////////////////////////////////////////////////////////////////
 * types
 */

// the gl fill flag type
typedef enum __g2_gl_fill_flag_t
{
	G2_GL_FILL_FLAG_NONE 		= 0
,	G2_GL_FILL_FLAG_RECT 		= 1
,	G2_GL_FILL_FLAG_STENCIL 	= 2
,	G2_GL_FILL_FLAG_CONVEX 		= 4

}g2_gl_fill_flag_t;

// the gl fill type
typedef struct __g2_gl_fill_t
{
	// the painter
	g2_gl_painter_t* 	painter;

	// the context
	g2_gl_context_t* 	context;

	// the program for gl >= 2.0
	tb_handle_t 		program;

	// the style 
	tb_handle_t 		style;

	// the shader
	g2_gl_shader_t* 	shader;

	// the flag
	tb_size_t 			flag;

	// the vertices, 4[points] x 2[xy]
	tb_float_t 			vertices[8];

	// the texcoords, 4[points] x 2[xy]
	tb_float_t 			texcoords[8];

	// the colors, 4[points] x 4[rgba]
	tb_float_t 			colors[16];

	// the matrix
	tb_float_t 			matrix[16];

}g2_gl_fill_t;

/* ///////////////////////////////////////////////////////////////////////
 * implementation
 */
static __tb_inline__ tb_void_t g2_gl_fill_matrix_enter(g2_gl_fill_t* fill, tb_float_t const* matrix)
{
	if (fill->context->version < 0x20)
	{
		g2_glMatrixMode(G2_GL_MODELVIEW);
		g2_glPushMatrix();
		g2_glMultMatrixf(matrix);
	}
	else g2_glUniformMatrix4fv(g2_gl_program_location(fill->program, G2_GL_PROGRAM_LOCATION_MATRIX_MODEL), 1, G2_GL_FALSE, matrix);
}
static __tb_inline__ tb_void_t g2_gl_fill_matrix_leave(g2_gl_fill_t* fill)
{
	if (fill->context->version < 0x20)
	{
		g2_glPopMatrix();
	}
}
static __tb_inline__ tb_void_t g2_gl_fill_stencil_init(g2_gl_fill_t* fill)
{
    g2_glDisable(G2_GL_BLEND);
    g2_glDisable(G2_GL_TEXTURE_2D);
	g2_glEnable(G2_GL_STENCIL_TEST);
}
static __tb_inline__ tb_void_t g2_gl_fill_stencil_exit(g2_gl_fill_t* fill)
{
	g2_glColorMask(G2_GL_TRUE, G2_GL_TRUE, G2_GL_TRUE, G2_GL_TRUE);
	g2_glDisable(G2_GL_STENCIL_TEST);
}
static __tb_inline__ tb_void_t g2_gl_fill_stencil_enter(g2_gl_fill_t* fill)
{
	g2_glStencilFunc(G2_GL_ALWAYS, 0, 0);
	g2_glStencilOp(G2_GL_INVERT, G2_GL_INVERT, G2_GL_INVERT);
	g2_glColorMask(G2_GL_FALSE, G2_GL_FALSE, G2_GL_FALSE, G2_GL_FALSE);
}
static __tb_inline__ tb_void_t g2_gl_fill_stencil_leave(g2_gl_fill_t* fill)
{
	g2_glStencilFunc(G2_GL_EQUAL, 1, 1);
	g2_glStencilOp(G2_GL_ZERO, G2_GL_ZERO, G2_GL_ZERO);
	g2_glColorMask(G2_GL_TRUE, G2_GL_TRUE, G2_GL_TRUE, G2_GL_TRUE);
}
static __tb_inline__ tb_void_t g2_gl_fill_apply_antialiasing(g2_gl_fill_t* fill)
{
	if (g2_style_flag(fill->style) & G2_STYLE_FLAG_ANTI_ALIAS) g2_glEnable(G2_GL_MULTISAMPLE);
	else g2_glDisable(G2_GL_MULTISAMPLE);
}
static __tb_inline__ tb_void_t g2_gl_fill_apply_color(g2_gl_fill_t* fill, g2_color_t color)
{
	if (fill->context->version < 0x20)
		g2_glColor4f((tb_float_t)color.r / 0xff, (tb_float_t)color.g / 0xff, (tb_float_t)color.b / 0xff, (tb_float_t)color.a / 0xff);
	else g2_glVertexAttrib4f(g2_gl_program_location(fill->program, G2_GL_PROGRAM_LOCATION_COLORS), (tb_float_t)color.r / 0xff, (tb_float_t)color.g / 0xff, (tb_float_t)color.b / 0xff, (tb_float_t)color.a / 0xff);
}
static __tb_inline__ tb_void_t g2_gl_fill_apply_blend(g2_gl_fill_t* fill, tb_bool_t enable)
{
	if (enable) 
	{
		g2_glEnable(G2_GL_BLEND);
		g2_glBlendFunc(G2_GL_SRC_ALPHA, G2_GL_ONE_MINUS_SRC_ALPHA);
	}
	else g2_glDisable(G2_GL_BLEND);
}
static __tb_inline__ tb_void_t g2_gl_fill_apply_solid(g2_gl_fill_t* fill)
{
	// apply blend
	g2_gl_fill_apply_blend(fill, g2_style_alpha(fill->style) != 0xff);

	// apply color
	g2_gl_fill_apply_color(fill, g2_style_color(fill->style));
}
static __tb_inline__ tb_void_t g2_gl_fill_apply_wrap(g2_gl_fill_t* fill)
{
	// wrap
	static g2_GLuint_t wrap[] = 
	{
		G2_GL_CLAMP_TO_BORDER
	,	G2_GL_CLAMP_TO_BORDER
	,	G2_GL_CLAMP_TO_EDGE
	,	G2_GL_REPEAT
	,	G2_GL_MIRRORED_REPEAT
	};
	tb_assert(fill->shader->wrap < tb_arrayn(wrap));

	// wrap
	switch (fill->shader->type)
	{
	case G2_GL_SHADER_TYPE_BITMAP:
		g2_glTexParameteri(G2_GL_TEXTURE_2D, G2_GL_TEXTURE_WRAP_S, wrap[fill->shader->wrap]);
		g2_glTexParameteri(G2_GL_TEXTURE_2D, G2_GL_TEXTURE_WRAP_T, wrap[fill->shader->wrap]);
		break;
	case G2_GL_SHADER_TYPE_LINEAR:
	case G2_GL_SHADER_TYPE_RADIAL:
		g2_glTexParameteri(G2_GL_TEXTURE_2D, G2_GL_TEXTURE_WRAP_S, wrap[fill->shader->wrap]);
		g2_glTexParameteri(G2_GL_TEXTURE_2D, G2_GL_TEXTURE_WRAP_T, G2_GL_CLAMP_TO_EDGE);
		break;
	default:
		break;
	}
}
static __tb_inline__ tb_void_t g2_gl_fill_apply_filter(g2_gl_fill_t* fill)
{
	// filter?
	if (g2_style_flag(fill->style) & G2_STYLE_FLAG_BITMAP_FILTER)
	{
		// init filter
		tb_size_t filter = g2_quality() > G2_QUALITY_LOW? G2_GL_LINEAR : G2_GL_NEAREST;
		g2_glTexParameteri(G2_GL_TEXTURE_2D, G2_GL_TEXTURE_MAG_FILTER, filter);
		g2_glTexParameteri(G2_GL_TEXTURE_2D, G2_GL_TEXTURE_MIN_FILTER, filter);
	}
	else
	{
		g2_glTexParameteri(G2_GL_TEXTURE_2D, G2_GL_TEXTURE_MAG_FILTER, G2_GL_NEAREST);
		g2_glTexParameteri(G2_GL_TEXTURE_2D, G2_GL_TEXTURE_MIN_FILTER, G2_GL_NEAREST);
	}
}
static __tb_inline__ tb_void_t g2_gl_fill_apply_vertices(g2_gl_fill_t* fill)
{
	if (fill->context->version < 0x20) g2_glVertexPointer(2, G2_GL_FLOAT, 0, fill->vertices);
	else g2_glVertexAttribPointer(g2_gl_program_location(fill->program, G2_GL_PROGRAM_LOCATION_VERTICES), 2, G2_GL_FLOAT, G2_GL_FALSE, 0, fill->vertices);
}
static __tb_inline__ tb_void_t g2_gl_fill_apply_colors(g2_gl_fill_t* fill)
{
	if (fill->context->version < 0x20) g2_glColorPointer(4, G2_GL_FLOAT, 0, fill->colors);
	else g2_glVertexAttribPointer(g2_gl_program_location(fill->program, G2_GL_PROGRAM_LOCATION_COLORS), 4, G2_GL_FLOAT, G2_GL_FALSE, 0, fill->colors);
}
static __tb_inline__ tb_void_t g2_gl_fill_apply_texcoords(g2_gl_fill_t* fill)
{
	// texcoords
	if (fill->context->version < 0x20) g2_glTexCoordPointer(2, G2_GL_FLOAT, 0, fill->texcoords);
	else g2_glVertexAttribPointer(g2_gl_program_location(fill->program, G2_GL_PROGRAM_LOCATION_TEXCOORDS), 2, G2_GL_FLOAT, G2_GL_FALSE, 0, fill->texcoords);
}
static __tb_inline__ tb_bool_t g2_gl_fill_apply_program(g2_gl_fill_t* fill)
{
	if (fill->context->version >= 0x20)
	{	
		// type
		tb_size_t type = G2_GL_PROGRAM_TYPE_COLOR;
		if (fill->shader)
		{
			switch (fill->shader->type)
			{
			case G2_GL_SHADER_TYPE_BITMAP:
				type = G2_GL_PROGRAM_TYPE_BITMAP;
				break;
			case G2_GL_SHADER_TYPE_LINEAR:
			case G2_GL_SHADER_TYPE_RADIAL:
				type = G2_GL_PROGRAM_TYPE_BITMAP;
				break;
			default:
				tb_assert_and_check_return_val(0, TB_FALSE);
				break;
			}
		}

		// program
		fill->program = fill->context->programs[type];
		tb_assert_and_check_return_val(fill->program, TB_FALSE);
		g2_gl_program_uses(fill->program);
	}

	// ok
	return TB_TRUE;
}
static __tb_inline__ tb_void_t g2_gl_fill_enter_vertex_state(g2_gl_fill_t* fill)
{
	// apply antialiasing?
	g2_gl_fill_apply_antialiasing(fill);

	// apply vertices & texcoords
	if (fill->context->version < 0x20)
	{
		// enable vertices
		g2_glEnableClientState(G2_GL_VERTEX_ARRAY);
	}
	else
	{
		// enable vertices
		g2_glEnableVertexAttribArray(g2_gl_program_location(fill->program, G2_GL_PROGRAM_LOCATION_VERTICES));

		// apply project matrix
		g2_glUniformMatrix4fv(g2_gl_program_location(fill->program, G2_GL_PROGRAM_LOCATION_MATRIX_PROJECT), 1, G2_GL_FALSE, fill->context->matrix);
	}
}
static __tb_inline__ tb_void_t g2_gl_fill_leave_vertex_state(g2_gl_fill_t* fill)
{
	// disable antialiasing
	g2_glDisable(G2_GL_MULTISAMPLE);

	// apply vertices & texcoords
	if (fill->context->version < 0x20)
	{
		// disable vertices
		g2_glDisableClientState(G2_GL_VERTEX_ARRAY);
	}
	else
	{
		// disable vertices
		g2_glDisableVertexAttribArray(g2_gl_program_location(fill->program, G2_GL_PROGRAM_LOCATION_VERTICES));
	}
}
static __tb_inline__ tb_void_t g2_gl_fill_enter_texture_state(g2_gl_fill_t* fill)
{
	// enable texture
	g2_glEnable(G2_GL_TEXTURE_2D);

	// bind texture
	g2_glBindTexture(G2_GL_TEXTURE_2D, *fill->shader->texture);

	// apply vertices & texcoords
	if (fill->context->version < 0x20)
	{
		// enable texcoords
		g2_glEnableClientState(G2_GL_TEXTURE_COORD_ARRAY);

		// apply mode
		g2_glTexEnvi(G2_GL_TEXTURE_ENV, G2_GL_TEXTURE_ENV_MODE, G2_GL_MODULATE);
	}
	else
	{
		// enable texcoords
		g2_glEnableVertexAttribArray(g2_gl_program_location(fill->program, G2_GL_PROGRAM_LOCATION_TEXCOORDS));
	}

	// apply blend
	tb_byte_t 	alpha = g2_style_alpha(fill->style);
	g2_gl_fill_apply_blend(fill, fill->shader->flag & G2_GL_SHADER_FLAG_ALPHA || fill->shader->wrap == G2_SHADER_WRAP_BORDER || alpha != 0xff);

	// apply color
	g2_gl_fill_apply_color(fill, g2_color_make(alpha, 0xff, 0xff, 0xff));

	// apply wrap
	g2_gl_fill_apply_wrap(fill);

	// apply filter
	g2_gl_fill_apply_filter(fill);
}
static __tb_inline__ tb_void_t g2_gl_fill_leave_texture_state(g2_gl_fill_t* fill)
{
	// apply vertices & texcoords
	if (fill->context->version < 0x20)
	{
		// disable texcoords
		g2_glDisableClientState(G2_GL_TEXTURE_COORD_ARRAY);
	}
	else
	{
		// disable texcoords
		g2_glDisableVertexAttribArray(g2_gl_program_location(fill->program, G2_GL_PROGRAM_LOCATION_TEXCOORDS));
	}

	// disable texture
	g2_glDisable(G2_GL_TEXTURE_2D);
}
static __tb_inline__ tb_void_t g2_gl_fill_enter_texture_matrix(g2_gl_fill_t* fill)
{
	// apply matrix
	if (fill->context->version < 0x20)
	{
		// enter the texture matrix mode
		g2_glMatrixMode(G2_GL_TEXTURE);
		g2_glPushMatrix();
	}
}
static __tb_inline__ tb_void_t g2_gl_fill_apply_texture_matrix(g2_gl_fill_t* fill, g2_gl_rect_t const* bounds)
{
	// check
	tb_assert_and_check_return(fill->shader);

	// init
	tb_float_t bx = bounds->x1;
	tb_float_t by = bounds->y1;
	tb_float_t bw = bounds->x2 - bounds->x1 + 1;
	tb_float_t bh = bounds->y2 - bounds->y1 + 1;
	tb_float_t sw = fill->shader->width;
	tb_float_t sh = fill->shader->height;

	// apply matrix
	if (fill->context->version < 0x20)
	{
		// apply the texture matrix
		g2_glMultMatrixf(fill->shader->matrix_gl);

		// disable auto scale in the bounds
		g2_glScalef(bw / sw, bh / sh, 1.0f);

		// move viewport to global
		g2_glTranslatef(bx / bw, by / bh, 0.0f);
	}
	else 
	{
		// init matrix
		g2_gl_matrix_copy(fill->matrix, fill->shader->matrix_gl);

		// disable auto scale in the bounds
		g2_gl_matrix_scale(fill->matrix, bw / sw, bh / sh);

		// move viewport to global
		g2_gl_matrix_translate(fill->matrix, bx / bw, by / bh);

		// apply the texture matrix
		g2_glUniformMatrix4fv(g2_gl_program_location(fill->program, G2_GL_PROGRAM_LOCATION_MATRIX_TEXCOORD), 1, G2_GL_FALSE, fill->matrix);
	}
}
static __tb_inline__ tb_void_t g2_gl_fill_leave_texture_matrix(g2_gl_fill_t* fill)
{
	if (fill->context->version < 0x20)
	{
		// leave the texture matrix mode
		g2_glPopMatrix();
		g2_glMatrixMode(G2_GL_MODELVIEW);
	}
}
static __tb_inline__ tb_bool_t g2_gl_fill_context_init(g2_gl_fill_t* fill)
{
	// has fill?
	tb_check_return_val(g2_style_mode(fill->style) & G2_STYLE_MODE_FILL, TB_FALSE);

	// apply program first
	if (!g2_gl_fill_apply_program(fill)) return TB_FALSE;

	// enter vertex state
	g2_gl_fill_enter_vertex_state(fill);

	// apply solid if no shader
	if (!fill->shader) g2_gl_fill_apply_solid(fill);
	
	// ok
	return TB_TRUE;
}
static __tb_inline__ tb_void_t g2_gl_fill_context_exit(g2_gl_fill_t* fill)
{
	// leave vertex state
	g2_gl_fill_leave_vertex_state(fill);

	// leave texture state
	g2_gl_fill_leave_texture_state(fill);

	// disable blend
	g2_glDisable(G2_GL_BLEND);
}
static __tb_inline__ tb_void_t g2_gl_fill_style_draw_color(g2_gl_fill_t* fill, g2_gl_rect_t const* bounds)
{
	// apply solid
	g2_gl_fill_apply_solid(fill);

	// init vertices
	fill->vertices[0] = bounds->x1;
	fill->vertices[1] = bounds->y1;
	fill->vertices[2] = bounds->x2;
	fill->vertices[3] = bounds->y1;
	fill->vertices[4] = bounds->x1;
	fill->vertices[5] = bounds->y2;
	fill->vertices[6] = bounds->x2;
	fill->vertices[7] = bounds->y2;
	
	// apply vertices
	g2_gl_fill_apply_vertices(fill);

	// draw
	g2_glDrawArrays(G2_GL_TRIANGLE_STRIP, 0, 4);
}
static __tb_inline__ tb_void_t g2_gl_fill_style_draw_shader_bitmap(g2_gl_fill_t* fill, g2_gl_rect_t const* bounds)
{
	// enter texture state
	g2_gl_fill_enter_texture_state(fill);

	// enter texture matrix
	g2_gl_fill_enter_texture_matrix(fill);

	// init texcoords
	fill->texcoords[0] = 0.0f;
	fill->texcoords[1] = 0.0f;
	fill->texcoords[2] = 1.0f;
	fill->texcoords[3] = 0.0f;
	fill->texcoords[4] = 0.0f;
	fill->texcoords[5] = 1.0f;
	fill->texcoords[6] = 1.0f;
	fill->texcoords[7] = 1.0f;

	// apply texcoords
	g2_gl_fill_apply_texcoords(fill);

	// init vertices
	fill->vertices[0] = bounds->x1;
	fill->vertices[1] = bounds->y1;
	fill->vertices[2] = bounds->x2;
	fill->vertices[3] = bounds->y1;
	fill->vertices[4] = bounds->x1;
	fill->vertices[5] = bounds->y2;
	fill->vertices[6] = bounds->x2;
	fill->vertices[7] = bounds->y2;
	
	// apply vertices
	g2_gl_fill_apply_vertices(fill);

	// apply texture matrix
	g2_gl_fill_apply_texture_matrix(fill, bounds);

	// draw
	g2_glDrawArrays(G2_GL_TRIANGLE_STRIP, 0, 4);

	// leave texture matrix
	g2_gl_fill_leave_texture_matrix(fill);

	// leave texture state
	g2_gl_fill_leave_texture_state(fill);
}
static __tb_inline__ tb_void_t g2_gl_fill_style_draw_shader_linear(g2_gl_fill_t* fill, g2_gl_rect_t const* bounds)
{
	// enter texture state
	g2_gl_fill_enter_texture_state(fill);

	// enter texture matrix
	g2_gl_fill_enter_texture_matrix(fill);

	// init texcoords
	fill->texcoords[0] = 0.0f;
	fill->texcoords[1] = 0.0f;
	fill->texcoords[2] = 1.0f;
	fill->texcoords[3] = 0.0f;
	fill->texcoords[4] = 0.0f;
	fill->texcoords[5] = 1.0f;
	fill->texcoords[6] = 1.0f;
	fill->texcoords[7] = 1.0f;

	// apply texcoords
	g2_gl_fill_apply_texcoords(fill);

	// init vertices
	fill->vertices[0] = bounds->x1;
	fill->vertices[1] = bounds->y1;
	fill->vertices[2] = bounds->x2;
	fill->vertices[3] = bounds->y1;
	fill->vertices[4] = bounds->x1;
	fill->vertices[5] = bounds->y2;
	fill->vertices[6] = bounds->x2;
	fill->vertices[7] = bounds->y2;
	
	// apply vertices
	g2_gl_fill_apply_vertices(fill);

	// apply texture matrix
	g2_gl_fill_apply_texture_matrix(fill, bounds);

	// draw
	g2_glDrawArrays(G2_GL_TRIANGLE_STRIP, 0, 4);

	// leave texture matrix
	g2_gl_fill_leave_texture_matrix(fill);

	// leave texture state
	g2_gl_fill_leave_texture_state(fill);
}
static __tb_inline__ tb_void_t g2_gl_fill_style_draw_shader_radial(g2_gl_fill_t* fill, g2_gl_rect_t const* bounds)
{
	// enter texture state
	g2_gl_fill_enter_texture_state(fill);

	// enter texture matrix
	g2_gl_fill_enter_texture_matrix(fill);

	// init texcoords
	fill->texcoords[0] = 0.0f;
	fill->texcoords[1] = 0.0f;
	fill->texcoords[2] = 1.0f;
	fill->texcoords[3] = 0.0f;
	fill->texcoords[4] = 0.0f;
	fill->texcoords[5] = 1.0f;
	fill->texcoords[6] = 1.0f;
	fill->texcoords[7] = 1.0f;

	// apply texcoords
	g2_gl_fill_apply_texcoords(fill);

#if 1
	// init fragment vertices
	tb_float_t x = g2_float_to_tb(fill->shader->u.radial.cp.c.x);
	tb_float_t y = g2_float_to_tb(fill->shader->u.radial.cp.c.y);
	tb_float_t r = g2_float_to_tb(fill->shader->u.radial.cp.r);
	fill->vertices[0] = x;
	fill->vertices[1] = y;
	fill->vertices[2] = x + r;
	fill->vertices[3] = y + 10.0;
	fill->vertices[4] = x + r;
	fill->vertices[5] = y - 10.0;
	fill->vertices[6] = x;
	fill->vertices[7] = y;

	// init fragment bounds
	g2_gl_rect_t fbounds;
	g2_gl_rect_init(&fbounds, fill->vertices[0], fill->vertices[1]);
	g2_gl_rect_done(&fbounds, fill->vertices[2], fill->vertices[3]);
	g2_gl_rect_done(&fbounds, fill->vertices[4], fill->vertices[5]);
	
	// apply vertices
	g2_gl_fill_apply_vertices(fill);

	// apply texture matrix
	g2_gl_fill_apply_texture_matrix(fill, &fbounds);

	// draw
	g2_glDrawArrays(G2_GL_TRIANGLE_STRIP, 0, 4);
#else
	// init vertices
	fill->vertices[0] = bounds->x1;
	fill->vertices[1] = bounds->y1;
	fill->vertices[2] = bounds->x2;
	fill->vertices[3] = bounds->y1;
	fill->vertices[4] = bounds->x1;
	fill->vertices[5] = bounds->y2;
	fill->vertices[6] = bounds->x2;
	fill->vertices[7] = bounds->y2;
	
	// apply vertices
	g2_gl_fill_apply_vertices(fill);

	// apply texture matrix
	g2_gl_fill_apply_texture_matrix(fill, bounds);

	// draw
	g2_glDrawArrays(G2_GL_TRIANGLE_STRIP, 0, 4);

#endif

	// leave texture matrix
	g2_gl_fill_leave_texture_matrix(fill);

	// leave texture state
	g2_gl_fill_leave_texture_state(fill);
}
static __tb_inline__ tb_void_t g2_gl_fill_style_draw_shader(g2_gl_fill_t* fill, g2_gl_rect_t const* bounds)
{
	// draw shader
	switch (fill->shader->type)
	{
	case G2_GL_SHADER_TYPE_BITMAP:
		g2_gl_fill_style_draw_shader_bitmap(fill, bounds);
		break;
	case G2_GL_SHADER_TYPE_LINEAR:
		g2_gl_fill_style_draw_shader_linear(fill, bounds);
		break;
	case G2_GL_SHADER_TYPE_RADIAL:
		g2_gl_fill_style_draw_shader_radial(fill, bounds);
		break;
		break;
	default:
		break;
	}
}
static __tb_inline__ tb_void_t g2_gl_fill_style_draw(g2_gl_fill_t* fill, g2_gl_rect_t const* bounds)
{
	// rect or stencil?
	tb_check_return(fill->flag & (G2_GL_FILL_FLAG_RECT | G2_GL_FILL_FLAG_STENCIL));

	// draw
	if (g2_style_shader(fill->style)) g2_gl_fill_style_draw_shader(fill, bounds);
	else g2_gl_fill_style_draw_color(fill, bounds);
}
static __tb_inline__ tb_bool_t g2_gl_fill_init(g2_gl_fill_t* fill, g2_gl_painter_t* painter, tb_size_t flag)
{
	// init fill
	fill->painter 	= painter;
	fill->context 	= painter->context;
	fill->style 	= painter->style_usr;
	fill->shader 	= g2_style_shader(fill->style);
	fill->flag 		= flag;
	fill->flag 		= (!(flag & G2_GL_FILL_FLAG_CONVEX) || (g2_style_shader(fill->style) && !(flag & G2_GL_FILL_FLAG_RECT)))? (flag | G2_GL_FILL_FLAG_STENCIL) : flag;
	tb_assert_and_check_return_val(fill->painter && fill->context && fill->style, TB_FALSE);

	// init context
	if (!g2_gl_fill_context_init(fill)) return TB_FALSE;
	
	// enter matrix
	g2_gl_matrix_from(fill->matrix, &fill->painter->matrix);
	g2_gl_fill_matrix_enter(fill, fill->matrix);

	// use stencil?
	if (fill->flag & G2_GL_FILL_FLAG_STENCIL)
	{
		// init stencil
		g2_gl_fill_stencil_init(fill);

		// enter stencil
		g2_gl_fill_stencil_enter(fill);
	}

	// ok
	return TB_TRUE;
}
static __tb_inline__ tb_void_t g2_gl_fill_draw(g2_gl_fill_t* fill, g2_gl_rect_t* bounds)
{
	// leave stencil
	if (fill->flag & G2_GL_FILL_FLAG_STENCIL)
		g2_gl_fill_stencil_leave(fill);

	// draw style
	g2_gl_fill_style_draw(fill, bounds);
}
static __tb_inline__ tb_void_t g2_gl_fill_exit(g2_gl_fill_t* fill)
{
	// leave matrix
	g2_gl_fill_matrix_leave(fill);

	// exit stencil
	if (fill->flag & G2_GL_FILL_FLAG_STENCIL) 
		g2_gl_fill_stencil_exit(fill);

	// exit fill style
	g2_gl_fill_context_exit(fill);
}
static tb_void_t g2_gl_fill_split_circle_func(g2_soft_split_circle_t* split, g2_point_t const* pt)
{
	// vertices
	tb_vector_t* vertices = (tb_vector_t*)split->data;
	tb_assert_return(vertices);

	// data
	tb_float_t data[2];
	data[0] = g2_float_to_tb(pt->x);
	data[1] = g2_float_to_tb(pt->y);

	// add
	tb_vector_insert_tail(vertices, data);
}
static tb_void_t g2_gl_fill_split_ellipse_func(g2_soft_split_ellipse_t* split, g2_point_t const* pt)
{
	// vertices
	tb_vector_t* vertices = (tb_vector_t*)split->data;
	tb_assert_return(vertices);

	// data
	tb_float_t data[2];
	data[0] = g2_float_to_tb(pt->x);
	data[1] = g2_float_to_tb(pt->y);

	// add
	tb_vector_insert_tail(vertices, data);
}
/* ///////////////////////////////////////////////////////////////////////
 * interfaces
 */
tb_void_t g2_gl_fill_rect(g2_gl_painter_t* painter, g2_rect_t const* rect)
{
	// init bounds
	g2_gl_rect_t bounds;
	bounds.x1 = g2_float_to_tb(rect->x);
	bounds.y1 = g2_float_to_tb(rect->y);
	bounds.x2 = g2_float_to_tb(rect->x + rect->w - 1);
	bounds.y2 = g2_float_to_tb(rect->y + rect->h - 1);
	tb_check_return(bounds.x1 < bounds.x2 && bounds.y1 < bounds.y2);

	// init fill
	g2_gl_fill_t fill = {0};
	if (!g2_gl_fill_init(&fill, painter, G2_GL_FILL_FLAG_RECT | G2_GL_FILL_FLAG_CONVEX)) return ;

	// draw fill
	g2_gl_fill_draw(&fill, &bounds);

	// exit fill
	g2_gl_fill_exit(&fill);
}
tb_void_t g2_gl_fill_path(g2_gl_painter_t* painter, g2_gl_path_t const* path)
{
	// check
	tb_assert(path->fill.data && tb_vector_size(path->fill.data));
	tb_assert(path->fill.size && tb_vector_size(path->fill.size));
	tb_check_return(path->fill.rect.x1 < path->fill.rect.x2 && path->fill.rect.y1 < path->fill.rect.y2);
	
	// fill
	g2_gl_fill_t fill = {0};

	// like rect?
	if (path->like == G2_GL_PATH_LIKE_RECT)
	{
		// init fill
		if (!g2_gl_fill_init(&fill, painter, G2_GL_FILL_FLAG_RECT | G2_GL_FILL_FLAG_CONVEX)) return ;

		// draw fill
		g2_gl_fill_draw(&fill, &path->rect);

		// exit fill
		g2_gl_fill_exit(&fill);

		// ok
		return ;
	}
	// like triangle?
	else if (path->like == G2_GL_PATH_LIKE_TRIG)
	{
		// fill triangle
		g2_gl_fill_triangle(painter, &path->trig);

		// ok
		return ;
	}

	// init fill
	if (!g2_gl_fill_init(&fill, painter, path->like == G2_GL_PATH_LIKE_CONX? G2_GL_FILL_FLAG_CONVEX : G2_GL_FILL_FLAG_NONE)) return ;

	// init vertices
	if (fill.context->version < 0x20)
		g2_glVertexPointer(2, G2_GL_FLOAT, 0, tb_vector_data(path->fill.data));
	else g2_glVertexAttribPointer(g2_gl_program_location(fill.program, G2_GL_PROGRAM_LOCATION_VERTICES), 2, G2_GL_FLOAT, G2_GL_FALSE, 0, tb_vector_data(path->fill.data));

	// draw path
	tb_size_t 	head = 0;
	tb_size_t 	size = 0;
	tb_size_t 	itor = tb_iterator_head(path->fill.size);
	tb_size_t 	tail = tb_iterator_tail(path->fill.size);
	for (; itor != tail; itor++)
	{
		size = tb_iterator_item(path->fill.size, itor);
		g2_glDrawArrays(G2_GL_TRIANGLE_FAN, (g2_GLint_t)head, (g2_GLint_t)size);
		head += size;
	}

	// draw fill
	g2_gl_fill_draw(&fill, &path->fill.rect);

	// exit fill
	g2_gl_fill_exit(&fill);
}
tb_void_t g2_gl_fill_circle(g2_gl_painter_t* painter, g2_circle_t const* circle)
{
	// init bounds
	g2_gl_rect_t bounds;
	bounds.x1 = g2_float_to_tb(circle->c.x - circle->r);
	bounds.y1 = g2_float_to_tb(circle->c.y - circle->r);
	bounds.x2 = g2_float_to_tb(circle->c.x + circle->r - G2_ONE);
	bounds.y2 = g2_float_to_tb(circle->c.y + circle->r - G2_ONE);
	tb_check_return(bounds.x1 < bounds.x2 && bounds.y1 < bounds.y2);
	
	// init vertices
	tb_assert_and_check_return(painter->vertices);
	tb_vector_clear(painter->vertices);

	// split circle, FIXME: cache it
	g2_soft_split_circle_t split;
	g2_soft_split_circle_init(&split, g2_gl_fill_split_circle_func, painter->vertices);
	g2_soft_split_circle_done(&split, circle);

	// data & size
	tb_float_t* data = tb_vector_data(painter->vertices);
	tb_size_t 	size = tb_vector_size(painter->vertices);
	tb_assert_and_check_return(data && size > 2);

	// init fill
	g2_gl_fill_t fill = {0};
	if (!g2_gl_fill_init(&fill, painter, G2_GL_FILL_FLAG_CONVEX)) return ;

	// draw vertices
	if (fill.context->version < 0x20) g2_glVertexPointer(2, G2_GL_FLOAT, 0, data);
	else g2_glVertexAttribPointer(g2_gl_program_location(fill.program, G2_GL_PROGRAM_LOCATION_VERTICES), 2, G2_GL_FLOAT, G2_GL_FALSE, 0, data);
	g2_glDrawArrays(G2_GL_TRIANGLE_FAN, 0, (g2_GLint_t)size);

	// draw fill
	g2_gl_fill_draw(&fill, &bounds);

	// exit fill
	g2_gl_fill_exit(&fill);
}
tb_void_t g2_gl_fill_ellipse(g2_gl_painter_t* painter, g2_ellipse_t const* ellipse)
{
	// init bounds
	g2_gl_rect_t bounds;
	bounds.x1 = g2_float_to_tb(ellipse->c0.x - ellipse->rx);
	bounds.y1 = g2_float_to_tb(ellipse->c0.y - ellipse->ry);
	bounds.x2 = g2_float_to_tb(ellipse->c0.x + ellipse->rx - G2_ONE);
	bounds.y2 = g2_float_to_tb(ellipse->c0.y + ellipse->ry - G2_ONE);
	tb_check_return(bounds.x1 < bounds.x2 && bounds.y1 < bounds.y2);
	
	// init vertices
	tb_assert_and_check_return(painter->vertices);
	tb_vector_clear(painter->vertices);

	// split ellipse, FIXME: cache it
	g2_soft_split_ellipse_t split;
	g2_soft_split_ellipse_init(&split, g2_gl_fill_split_ellipse_func, painter->vertices);
	g2_soft_split_ellipse_done(&split, ellipse);

	// data & size
	tb_float_t* data = tb_vector_data(painter->vertices);
	tb_size_t 	size = tb_vector_size(painter->vertices);
	tb_assert_and_check_return(data && size > 2);

	// init fill
	g2_gl_fill_t fill = {0};
	if (!g2_gl_fill_init(&fill, painter, G2_GL_FILL_FLAG_CONVEX)) return ;

	// draw vertices
	if (fill.context->version < 0x20) g2_glVertexPointer(2, G2_GL_FLOAT, 0, data);
	else g2_glVertexAttribPointer(g2_gl_program_location(fill.program, G2_GL_PROGRAM_LOCATION_VERTICES), 2, G2_GL_FLOAT, G2_GL_FALSE, 0, data);
	g2_glDrawArrays(G2_GL_TRIANGLE_FAN, 0, (g2_GLint_t)size);

	// draw fill
	g2_gl_fill_draw(&fill, &bounds);

	// exit fill
	g2_gl_fill_exit(&fill);
}
tb_void_t g2_gl_fill_triangle(g2_gl_painter_t* painter, g2_triangle_t const* triangle)
{
	// init vertices
	tb_float_t vertices[6];
	vertices[0] = g2_float_to_tb(triangle->p0.x);
	vertices[1] = g2_float_to_tb(triangle->p0.y);
	vertices[2] = g2_float_to_tb(triangle->p1.x);
	vertices[3] = g2_float_to_tb(triangle->p1.y);
	vertices[4] = g2_float_to_tb(triangle->p2.x);
	vertices[5] = g2_float_to_tb(triangle->p2.y);

	// init bounds
	g2_gl_rect_t bounds;
	g2_gl_rect_init(&bounds, vertices[0], vertices[1]);
	g2_gl_rect_done(&bounds, vertices[2], vertices[3]);
	g2_gl_rect_done(&bounds, vertices[4], vertices[5]);
	tb_check_return(bounds.x1 < bounds.x2 && bounds.y1 < bounds.y2);

	// init fill
	g2_gl_fill_t fill = {0};
	if (!g2_gl_fill_init(&fill, painter, G2_GL_FILL_FLAG_CONVEX)) return ;

	// draw vertices
	if (fill.context->version < 0x20) g2_glVertexPointer(2, G2_GL_FLOAT, 0, vertices);
	else g2_glVertexAttribPointer(g2_gl_program_location(fill.program, G2_GL_PROGRAM_LOCATION_VERTICES), 2, G2_GL_FLOAT, G2_GL_FALSE, 0, vertices);
	g2_glDrawArrays(G2_GL_TRIANGLE_STRIP, 0, 3);

	// draw fill
	g2_gl_fill_draw(&fill, &bounds);

	// exit fill
	g2_gl_fill_exit(&fill);
}

