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

	// the flag
	tb_size_t 			flag;

	// the texcoords
	tb_float_t 			texcoords[8];

	// the matrix
	tb_float_t 			matrix[16];

}g2_gl_fill_t;

/* ///////////////////////////////////////////////////////////////////////
 * implementation
 */
static __tb_inline__ tb_void_t g2_gl_fill_matrix_enter(g2_gl_fill_t* fill)
{
	g2_gl_matrix_from(fill->matrix, &fill->painter->matrix);
	if (fill->context->version < 0x20)
	{
		glMatrixMode(GL_MODELVIEW);
		glPushMatrix();
		glMultMatrixf(fill->matrix);
	}
	else glUniformMatrix4fv(g2_gl_program_location(fill->program, G2_GL_PROGRAM_LOCATION_MATRIX_MODEL), 1, GL_FALSE, fill->matrix);
}
static __tb_inline__ tb_void_t g2_gl_fill_matrix_leave(g2_gl_fill_t* fill)
{
	if (fill->context->version < 0x20)
		glPopMatrix();
}
static __tb_inline__ tb_void_t g2_gl_fill_stencil_init(g2_gl_fill_t* fill)
{
    glDisable(GL_BLEND);
    glDisable(GL_TEXTURE_1D);
    glDisable(GL_TEXTURE_2D);
	glEnable(GL_STENCIL_TEST);
}
static __tb_inline__ tb_void_t g2_gl_fill_stencil_exit(g2_gl_fill_t* fill)
{
	glColorMask(GL_TRUE, GL_TRUE, GL_TRUE, GL_TRUE);
	glDisable(GL_STENCIL_TEST);
}
static __tb_inline__ tb_void_t g2_gl_fill_stencil_enter(g2_gl_fill_t* fill)
{
	glStencilFunc(GL_ALWAYS, 0, 0);
	glStencilOp(GL_INVERT, GL_INVERT, GL_INVERT);
	glColorMask(GL_FALSE, GL_FALSE, GL_FALSE, GL_FALSE);
}
static __tb_inline__ tb_void_t g2_gl_fill_stencil_leave(g2_gl_fill_t* fill)
{
	glStencilFunc(GL_EQUAL, 1, 1);
	glStencilOp(GL_ZERO, GL_ZERO, GL_ZERO);
	glColorMask(GL_TRUE, GL_TRUE, GL_TRUE, GL_TRUE);
}
static __tb_inline__ tb_bool_t g2_gl_fill_context_init(g2_gl_fill_t* fill)
{
	// style
	tb_handle_t 	style = fill->style;

	// mode
	tb_size_t 		mode = g2_style_mode(style);

	// flag
	tb_size_t 		flag = g2_style_flag(style);

	// shader
	tb_handle_t 	shader = g2_style_shader(style);

	// has fill?
	tb_check_return_val(mode & G2_STYLE_MODE_FILL, TB_FALSE);

	// enable antialiasing?
	if (flag & G2_STYLE_FLAG_ANTI_ALIAS) glEnable(GL_MULTISAMPLE);
	else glDisable(GL_MULTISAMPLE);

	// init color
	if (!shader)
	{
		tb_byte_t 	alpha = g2_style_alpha(style);
		g2_color_t 	color = g2_style_color(style);

		// enable blend?
		if (alpha != 0xff) 
		{
			glEnable(GL_BLEND);
			glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
		}
		else glDisable(GL_BLEND);
	
		if (fill->context->version < 0x20)
		{
			// init color
			glColor4f((tb_float_t)color.r / 0xff, (tb_float_t)color.g / 0xff, (tb_float_t)color.b / 0xff, (tb_float_t)color.a / 0xff);
		}
		else
		{	
			// init program
			fill->program = fill->context->programs[G2_GL_PROGRAM_TYPE_COLOR];
			tb_assert_and_check_return_val(fill->program, TB_FALSE);
			g2_gl_program_uses(fill->program);
		
			// init color
			glVertexAttrib4f(g2_gl_program_location(fill->program, G2_GL_PROGRAM_LOCATION_COLOR), (tb_float_t)color.r / 0xff, (tb_float_t)color.g / 0xff, (tb_float_t)color.b / 0xff, (tb_float_t)color.a / 0xff);

		}
	}
	else if (fill->context->version >= 0x20)
	{
		// init program
		fill->program = fill->context->programs[G2_GL_PROGRAM_TYPE_IMAGE];
		tb_assert_and_check_return_val(fill->program, TB_FALSE);
		g2_gl_program_uses(fill->program);
		
	}
	
	if (fill->context->version < 0x20)
	{
		// enable vertices
		glEnableClientState(GL_VERTEX_ARRAY);
	}
	else
	{
		// init vertices
		glEnableVertexAttribArray(g2_gl_program_location(fill->program, G2_GL_PROGRAM_LOCATION_VERTICES));

		// init project matrix
		glUniformMatrix4fv(g2_gl_program_location(fill->program, G2_GL_PROGRAM_LOCATION_MATRIX_PROJECT), 1, GL_FALSE, fill->context->matrix);
	}

	// ok
	return TB_TRUE;
}
static __tb_inline__ tb_void_t g2_gl_fill_context_exit(g2_gl_fill_t* fill)
{
	if (fill->context->version < 0x20)
	{
		// disable vertices
		glDisableClientState(GL_VERTEX_ARRAY);

		// disable texcoords
		glDisableClientState(GL_TEXTURE_COORD_ARRAY);
	}
	else
	{	
		// disable vertices
		glDisableVertexAttribArray(g2_gl_program_location(fill->program, G2_GL_PROGRAM_LOCATION_VERTICES));

		// disable texcoords
		glDisableVertexAttribArray(g2_gl_program_location(fill->program, G2_GL_PROGRAM_LOCATION_TEXCOORDS));
	}

	// disable antialiasing
	glDisable(GL_MULTISAMPLE);

	// disable blend
	glDisable(GL_BLEND);

	// disable texture
	glDisable(GL_TEXTURE_1D);
	glDisable(GL_TEXTURE_2D);
}
static __tb_inline__ tb_void_t g2_gl_fill_style_draw_color(g2_gl_fill_t* fill, g2_color_t color)
{
	// enable blend?
	tb_byte_t alpha = g2_style_alpha(fill->style);
	if (alpha != 0xff) 
	{
		glEnable(GL_BLEND);
		glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	}
	else glDisable(GL_BLEND);

	// init color
	if (fill->context->version < 0x20)
		glColor4f((tb_float_t)color.r / 0xff, (tb_float_t)color.g / 0xff, (tb_float_t)color.b / 0xff, (tb_float_t)color.a / 0xff);
	else glVertexAttrib4f(g2_gl_program_location(fill->program, G2_GL_PROGRAM_LOCATION_COLOR), (tb_float_t)color.r / 0xff, (tb_float_t)color.g / 0xff, (tb_float_t)color.b / 0xff, (tb_float_t)color.a / 0xff);

	// draw
	glDrawArrays(GL_TRIANGLE_STRIP, 0, 4);
}
static __tb_inline__ tb_void_t g2_gl_fill_style_draw_shader_image(g2_gl_fill_t* fill, g2_gl_shader_t const* shader, g2_gl_rect_t const* bounds)
{
	// init texture
	glEnable(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D, *shader->texture);

	/* the global image matrix => the camera viewport matrix
	 *
	 * glScalef(bw / sw, bh / sh, 1.0f); 			//< disable auto scale in the bounds
	 * glTranslatef(bx / bw, by / bh, 0.0f); 		//< move viewport to global
	 *
	 */
	g2_gl_matrix_from(fill->matrix, &shader->matrix);
	tb_float_t bx = bounds->x1;
	tb_float_t by = bounds->y1;
	tb_float_t bw = bounds->x2 - bounds->x1 + 1;
	tb_float_t bh = bounds->y2 - bounds->y1 + 1;
	tb_float_t sw = shader->u.image.width;
	tb_float_t sh = shader->u.image.height;
	tb_float_t sx = fill->matrix[0];
	tb_float_t sy = fill->matrix[5];

	/* adjust scale 
	 *
	 * global => camera: (1 / sx)
	 * disable auto scale in the bounds: (bw / sw)
	 *
	 * => sx = (bw / sw) * (1 / sx) => bw / (sx * sw)
	 *
	 */
	fill->matrix[0] 	= bw / (sx * sw);
	fill->matrix[5] 	= bh / (sy * sh);

	// adjust skew
	fill->matrix[1] 	*= fill->matrix[5] / sy;
	fill->matrix[4] 	*= fill->matrix[0] / sx;

	/* adjust translate
	 *
	 * scale: sx
	 * global => camera: -tx / bw
	 * move viewport to global: bx / bw
	 *
	 * => tx = sx * ((bx / bw) + (-tx / bw)) => sx * (bx - tx) / bw
	 * => tx = (bx - tx) / (sx * sw)
	 *
	 */
	fill->matrix[12] 	= (bx - fill->matrix[12]) / (sx * sw);
	fill->matrix[13] 	= (by - fill->matrix[13]) / (sy * sh);

	// enter matrix
	if (fill->context->version < 0x20)
	{
		glMatrixMode(GL_TEXTURE);
		glPushMatrix();
		glMultMatrixf(fill->matrix);
	}
	else glUniformMatrix4fv(g2_gl_program_location(fill->program, G2_GL_PROGRAM_LOCATION_MATRIX_TEXCOORD), 1, GL_FALSE, fill->matrix);

	// blend?
	tb_byte_t alpha = g2_style_alpha(fill->style);
	if (shader->flag & G2_GL_SHADER_FLAG_ALPHA
		|| shader->wrap == G2_SHADER_WRAP_BORDER
		|| alpha != 0xff
		)
	{
		glEnable(GL_BLEND);
		glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

		if (fill->context->version < 0x20)
			glColor4f(1.0f, 1.0f, 1.0f, (tb_float_t)alpha / 0xff);
		else glVertexAttrib4f(g2_gl_program_location(fill->program, G2_GL_PROGRAM_LOCATION_COLOR), 1.0f, 1.0f, 1.0f, (tb_float_t)alpha / 0xff);
	}
	else 
	{
		glDisable(GL_BLEND);
		if (fill->context->version < 0x20)
			glColor4f(1.0f, 1.0f, 1.0f, 1.0f);	
		else glVertexAttrib4f(g2_gl_program_location(fill->program, G2_GL_PROGRAM_LOCATION_COLOR), 1.0f, 1.0f, 1.0f, 1.0f);
	}

	// mode
	glTexEnvi(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);

	// wrap
	static GLuint wrap[] = 
	{
		GL_CLAMP_TO_BORDER
	,	GL_CLAMP_TO_BORDER
	,	GL_CLAMP_TO_EDGE
	,	GL_REPEAT
	,	GL_MIRRORED_REPEAT
	};
	tb_assert(shader->wrap < tb_arrayn(wrap));
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, wrap[shader->wrap]);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, wrap[shader->wrap]);

	// filter?
	if (g2_style_flag(fill->style) & G2_STYLE_FLAG_BITMAP_FILTER)
	{
		// init filter
		tb_size_t filter = g2_quality() > G2_QUALITY_LOW? GL_LINEAR : GL_NEAREST;
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, filter);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, filter);
	}
	else
	{
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	}

	// texcoords
	if (fill->context->version < 0x20)
	{
		glEnableClientState(GL_TEXTURE_COORD_ARRAY);
		glTexCoordPointer(2, GL_FLOAT, 0, fill->texcoords);
	}
	else 
	{
		glEnableVertexAttribArray(g2_gl_program_location(fill->program, G2_GL_PROGRAM_LOCATION_TEXCOORDS));
		glVertexAttribPointer(g2_gl_program_location(fill->program, G2_GL_PROGRAM_LOCATION_TEXCOORDS), 2, GL_FLOAT, GL_FALSE, 0, fill->texcoords);
	}

	// draw
	glDrawArrays(GL_TRIANGLE_STRIP, 0, 4);

	// leave matrix
	if (fill->context->version < 0x20)
	{
		glPopMatrix();
		glMatrixMode(GL_MODELVIEW);
		glDisableClientState(GL_TEXTURE_COORD_ARRAY);
	}
	else
	{
		// disable texcoords
		glDisableVertexAttribArray(g2_gl_program_location(fill->program, G2_GL_PROGRAM_LOCATION_TEXCOORDS));
	}

	// exit texture
	glDisable(GL_TEXTURE_2D);
}
static __tb_inline__ tb_void_t g2_gl_fill_style_draw_shader_linear(g2_gl_fill_t* fill, g2_gl_shader_t const* shader, g2_gl_rect_t const* bounds)
{
	// init texture
	glEnable(GL_TEXTURE_1D);
	glBindTexture(GL_TEXTURE_1D, *shader->texture);

	// init matrix
	g2_matrix_t matrix = *g2_matrix(fill->painter);

	// init vector
	g2_point_t pb = shader->u.linear.pb;
	g2_point_t pe = shader->u.linear.pe;
	g2_matrix_apply_point(&matrix, &pb);
	g2_matrix_apply_point(&matrix, &pe);

	/* init texcoords
	 *                 pe (01)
	 *                 *
	 *             *   | *
	 *          *      |  *
	 * (00)  *         |   *
	 * pb 0*****|******|*****1 (11)  => texture 1d
	 *      *   |      |   *
	 *       *  |      *
	 *        * |  *
	 *         * (10)
	 */
	fill->texcoords[0] = 0.0f;
	fill->texcoords[1] = 0.6f;
	fill->texcoords[2] = 0.3f;
	fill->texcoords[3] = 1.0f;

	/* the global image matrix => the camera viewport matrix
	 *
	 * glScalef(bw / sw, bh / sh, 1.0f); 			//< disable auto scale in the bounds
	 * glTranslatef(bx / bw, by / bh, 0.0f); 		//< move viewport to global
	 *
	 */
	g2_gl_matrix_from(fill->matrix, &shader->matrix);
	tb_float_t bx = bounds->x1;
	tb_float_t by = bounds->y1;
	tb_float_t bw = bounds->x2 - bounds->x1 + 1;
	tb_float_t bh = bounds->y2 - bounds->y1 + 1;
	tb_float_t sw = shader->u.image.width;
	tb_float_t sh = shader->u.image.height;
	tb_float_t sx = fill->matrix[0];
	tb_float_t sy = fill->matrix[5];

	/* adjust scale 
	 *
	 * global => camera: (1 / sx)
	 * disable auto scale in the bounds: (bw / sw)
	 *
	 * => sx = (bw / sw) * (1 / sx) => bw / (sx * sw)
	 *
	 */
	fill->matrix[0] 	= bw / (sx * sw);
	fill->matrix[5] 	= bh / (sy * sh);

	// adjust skew
	fill->matrix[1] 	*= fill->matrix[5] / sy;
	fill->matrix[4] 	*= fill->matrix[0] / sx;

	/* adjust translate
	 *
	 * scale: sx
	 * global => camera: -tx / bw
	 * move viewport to global: bx / bw
	 *
	 * => tx = sx * ((bx / bw) + (-tx / bw)) => sx * (bx - tx) / bw
	 * => tx = (bx - tx) / (sx * sw)
	 *
	 */
	fill->matrix[12] 	= (bx - fill->matrix[12]) / (sx * sw);
	fill->matrix[13] 	= (by - fill->matrix[13]) / (sy * sh);

	// enter matrix
	if (fill->context->version < 0x20)
	{
		glMatrixMode(GL_TEXTURE);
		glPushMatrix();
//		glMultMatrixf(fill->matrix);
	}
	else glUniformMatrix4fv(g2_gl_program_location(fill->program, G2_GL_PROGRAM_LOCATION_MATRIX_TEXCOORD), 1, GL_FALSE, fill->matrix);

	// blend?
	tb_byte_t alpha = g2_style_alpha(fill->style);
	if (shader->flag & G2_GL_SHADER_FLAG_ALPHA
		|| shader->wrap == G2_SHADER_WRAP_BORDER
		|| alpha != 0xff
		)
	{
		glEnable(GL_BLEND);
		glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

		if (fill->context->version < 0x20)
			glColor4f(1.0f, 1.0f, 1.0f, (tb_float_t)alpha / 0xff);
		else glVertexAttrib4f(g2_gl_program_location(fill->program, G2_GL_PROGRAM_LOCATION_COLOR), 1.0f, 1.0f, 1.0f, (tb_float_t)alpha / 0xff);
	}
	else 
	{
		glDisable(GL_BLEND);
		if (fill->context->version < 0x20)
			glColor4f(1.0f, 1.0f, 1.0f, 1.0f);	
		else glVertexAttrib4f(g2_gl_program_location(fill->program, G2_GL_PROGRAM_LOCATION_COLOR), 1.0f, 1.0f, 1.0f, 1.0f);
	}

	// mode
	glTexEnvi(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);

	// wrap
	static GLuint wrap[] = 
	{
		GL_CLAMP_TO_BORDER
	,	GL_CLAMP_TO_BORDER
	,	GL_CLAMP_TO_EDGE
	,	GL_REPEAT
	,	GL_MIRRORED_REPEAT
	};
	tb_assert(shader->wrap < tb_arrayn(wrap));
	glTexParameteri(GL_TEXTURE_1D, GL_TEXTURE_WRAP_S, wrap[shader->wrap]);
	glTexParameteri(GL_TEXTURE_1D, GL_TEXTURE_WRAP_T, wrap[shader->wrap]);

	// filter?
	if (g2_style_flag(fill->style) & G2_STYLE_FLAG_BITMAP_FILTER)
	{
		// init filter
		tb_size_t filter = g2_quality() > G2_QUALITY_LOW? GL_LINEAR : GL_NEAREST;
		glTexParameteri(GL_TEXTURE_1D, GL_TEXTURE_MAG_FILTER, filter);
		glTexParameteri(GL_TEXTURE_1D, GL_TEXTURE_MIN_FILTER, filter);
	}
	else
	{
		glTexParameteri(GL_TEXTURE_1D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
		glTexParameteri(GL_TEXTURE_1D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	}

	// texcoords
	if (fill->context->version < 0x20)
	{
		glEnableClientState(GL_TEXTURE_COORD_ARRAY);
		glTexCoordPointer(1, GL_FLOAT, 0, fill->texcoords);
	}
	else 
	{
		glEnableVertexAttribArray(g2_gl_program_location(fill->program, G2_GL_PROGRAM_LOCATION_TEXCOORDS));
		glVertexAttribPointer(g2_gl_program_location(fill->program, G2_GL_PROGRAM_LOCATION_TEXCOORDS), 2, GL_FLOAT, GL_FALSE, 0, fill->texcoords);
	}

	// draw
	glDrawArrays(GL_TRIANGLE_STRIP, 0, 4);

	// leave matrix
	if (fill->context->version < 0x20)
	{
		glPopMatrix();
		glMatrixMode(GL_MODELVIEW);
		glDisableClientState(GL_TEXTURE_COORD_ARRAY);
	}
	else
	{
		// disable texcoords
		glDisableVertexAttribArray(g2_gl_program_location(fill->program, G2_GL_PROGRAM_LOCATION_TEXCOORDS));
	}

	// exit texture
	glDisable(GL_TEXTURE_1D);
}
static __tb_inline__ tb_void_t g2_gl_fill_style_draw_shader_radial(g2_gl_fill_t* fill, g2_gl_shader_t const* shader, g2_gl_rect_t const* bounds)
{
}
static __tb_inline__ tb_void_t g2_gl_fill_style_draw_shader_radial2(g2_gl_fill_t* fill, g2_gl_shader_t const* shader, g2_gl_rect_t const* bounds)
{
}
static __tb_inline__ tb_void_t g2_gl_fill_style_draw_shader(g2_gl_fill_t* fill, g2_gl_shader_t const* shader, g2_gl_rect_t const* bounds)
{
	// check
	tb_assert_and_check_return(fill && shader && shader->texture);

	// draw shader
	switch (shader->type)
	{
	case G2_GL_SHADER_TYPE_BITMAP:
		g2_gl_fill_style_draw_shader_image(fill, shader, bounds);
		break;
	case G2_GL_SHADER_TYPE_LINEAR:
		g2_gl_fill_style_draw_shader_linear(fill, shader, bounds);
		break;
	case G2_GL_SHADER_TYPE_RADIAL:
		g2_gl_fill_style_draw_shader_radial(fill, shader, bounds);
		break;
	case G2_GL_SHADER_TYPE_RADIAL2:
		g2_gl_fill_style_draw_shader_radial2(fill, shader, bounds);
		break;
	default:
		break;
	}
}
static __tb_inline__ tb_void_t g2_gl_fill_style_draw(g2_gl_fill_t* fill, g2_gl_rect_t const* bounds)
{
	// style
	tb_handle_t 	style = fill->style;

	// mode
	tb_size_t 		mode = g2_style_mode(style);

	// flag
	tb_size_t 		flag = g2_style_flag(style);

	// rect or stencil?
	tb_check_return(fill->flag & (G2_GL_FILL_FLAG_RECT | G2_GL_FILL_FLAG_STENCIL));

	// init vertices
	tb_float_t vertices[8];
	vertices[0] = bounds->x1;
	vertices[1] = bounds->y1;
	vertices[2] = bounds->x2;
	vertices[3] = bounds->y1;
	vertices[4] = bounds->x1;
	vertices[5] = bounds->y2;
	vertices[6] = bounds->x2;
	vertices[7] = bounds->y2;
	if (fill->context->version < 0x20)
		glVertexPointer(2, GL_FLOAT, 0, vertices);
	else glVertexAttribPointer(g2_gl_program_location(fill->program, G2_GL_PROGRAM_LOCATION_VERTICES), 2, GL_FLOAT, GL_FALSE, 0, vertices);

	// draw
	if (g2_style_shader(style)) g2_gl_fill_style_draw_shader(fill, g2_style_shader(style), bounds);
	else g2_gl_fill_style_draw_color(fill, g2_style_color(style));
}
static __tb_inline__ tb_bool_t g2_gl_fill_init(g2_gl_fill_t* fill, g2_gl_painter_t* painter, tb_size_t flag)
{
	// init fill
	fill->painter 	= painter;
	fill->context 	= painter->context;
	fill->style 	= painter->style_usr;
	fill->flag 		= flag;
	fill->flag 		= (!(flag & G2_GL_FILL_FLAG_CONVEX) || (g2_style_shader(fill->style) && !(flag & G2_GL_FILL_FLAG_RECT)))? (flag | G2_GL_FILL_FLAG_STENCIL) : flag;
	tb_assert_and_check_return_val(fill->painter && fill->context && fill->style, TB_FALSE);

	// init texcoords
	fill->texcoords[0] = 0.0f;
	fill->texcoords[1] = 0.0f;
	fill->texcoords[2] = 1.0f;
	fill->texcoords[3] = 0.0f;
	fill->texcoords[4] = 0.0f;
	fill->texcoords[5] = 1.0f;
	fill->texcoords[6] = 1.0f;
	fill->texcoords[7] = 1.0f;

	// init matrix
	g2_gl_matrix_init(fill->matrix);

	// init context
	if (!g2_gl_fill_context_init(fill)) return TB_FALSE;
	
	// enter matrix
	g2_gl_fill_matrix_enter(fill);

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
		glVertexPointer(2, GL_FLOAT, 0, tb_vector_data(path->fill.data));
	else glVertexAttribPointer(g2_gl_program_location(fill.program, G2_GL_PROGRAM_LOCATION_VERTICES), 2, GL_FLOAT, GL_FALSE, 0, tb_vector_data(path->fill.data));

	// draw path
	tb_size_t 	head = 0;
	tb_size_t 	size = 0;
	tb_size_t 	itor = tb_iterator_head(path->fill.size);
	tb_size_t 	tail = tb_iterator_tail(path->fill.size);
	for (; itor != tail; itor++)
	{
		size = tb_iterator_item(path->fill.size, itor);
		glDrawArrays(GL_TRIANGLE_FAN, (GLint)head, (GLint)size);
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
	if (fill.context->version < 0x20) glVertexPointer(2, GL_FLOAT, 0, data);
	else glVertexAttribPointer(g2_gl_program_location(fill.program, G2_GL_PROGRAM_LOCATION_VERTICES), 2, GL_FLOAT, GL_FALSE, 0, data);
	glDrawArrays(GL_TRIANGLE_FAN, 0, (GLint)size);

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
	if (fill.context->version < 0x20) glVertexPointer(2, GL_FLOAT, 0, data);
	else glVertexAttribPointer(g2_gl_program_location(fill.program, G2_GL_PROGRAM_LOCATION_VERTICES), 2, GL_FLOAT, GL_FALSE, 0, data);
	glDrawArrays(GL_TRIANGLE_FAN, 0, (GLint)size);

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
	if (fill.context->version < 0x20) glVertexPointer(2, GL_FLOAT, 0, vertices);
	else glVertexAttribPointer(g2_gl_program_location(fill.program, G2_GL_PROGRAM_LOCATION_VERTICES), 2, GL_FLOAT, GL_FALSE, 0, vertices);
	glDrawArrays(GL_TRIANGLE_STRIP, 0, 3);

	// draw fill
	g2_gl_fill_draw(&fill, &bounds);

	// exit fill
	g2_gl_fill_exit(&fill);
}

