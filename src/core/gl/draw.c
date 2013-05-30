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
 * @file		draw.c
 *
 */

/* ///////////////////////////////////////////////////////////////////////
 * trace
 */
#define TB_TRACE_IMPL_TAG 		"draw"

/* ///////////////////////////////////////////////////////////////////////
 * includes
 */
#include "draw.h"
#include "shader.h"

/* ///////////////////////////////////////////////////////////////////////
 * types
 */

// the gl draw flag type
typedef enum __g2_gl_draw_flag_t
{
	G2_GL_DRAW_FLAG_NONE 		= 0
,	G2_GL_DRAW_FLAG_RECT 		= 1
,	G2_GL_DRAW_FLAG_STENCIL 	= 2
,	G2_GL_DRAW_FLAG_CONVEX 		= 4
,	G2_GL_DRAW_FLAG_SCISSOR 	= 8

}g2_gl_draw_flag_t;

// the gl draw radial factor type
typedef struct __g2_gl_draw_radial_factor_t
{
	// the factor
	tb_float_t 			factor;

	// the rotate
	tb_float_t 			rotation;

	// the count
	tb_size_t 			count;
	
}g2_gl_draw_radial_factor_t;

// the gl draw type
typedef struct __g2_gl_draw_t
{
	// the painter
	g2_gl_painter_t* 	painter;

	// the context
	g2_gl_context_t* 	context;

	// the clipper 
	tb_handle_t 		clipper;

	// the program for gl >= 2.0
	tb_handle_t 		program;

	// the style 
	tb_handle_t 		style;

	// the shader
	g2_gl_shader_t* 	shader;

	// the mode
	tb_size_t 			mode;

	// the flag
	tb_size_t 			flag;

	// the stencil pass value
	tb_byte_t 			pass;

	// the vertices, 4[points] x 2[xy]
	tb_float_t 			vertices[8];

	// the texcoords, 4[points] x 2[xy]
	tb_float_t 			texcoords[8];

	// the vertex matrix
	tb_float_t 			vmatrix[16];

	// the texture matrix
	tb_float_t 			tmatrix[16];

}g2_gl_draw_t;

/* ///////////////////////////////////////////////////////////////////////
 * implementation
 */
static __tb_inline__ tb_void_t g2_gl_draw_apply_antialiasing(g2_gl_draw_t* draw)
{
	if (g2_style_flag(draw->style) & G2_STYLE_FLAG_ANTI_ALIAS) 
	{
		g2_glEnable(G2_GL_MULTISAMPLE);
//		g2_glEnable(G2_GL_LINE_SMOOTH);
//		g2_glHint(G2_GL_LINE_SMOOTH_HINT, G2_GL_NICEST);
	}
	else g2_glDisable(G2_GL_MULTISAMPLE);
}
static __tb_inline__ tb_void_t g2_gl_draw_apply_color(g2_gl_draw_t* draw, g2_color_t color)
{
	if (draw->context->version < 0x20)
		g2_glColor4f((tb_float_t)color.r / 0xff, (tb_float_t)color.g / 0xff, (tb_float_t)color.b / 0xff, (tb_float_t)color.a / 0xff);
	else g2_glVertexAttrib4f(g2_gl_program_location(draw->program, G2_GL_PROGRAM_LOCATION_COLORS), (tb_float_t)color.r / 0xff, (tb_float_t)color.g / 0xff, (tb_float_t)color.b / 0xff, (tb_float_t)color.a / 0xff);
}
static __tb_inline__ tb_void_t g2_gl_draw_apply_blend(g2_gl_draw_t* draw, tb_bool_t enable)
{
	if (enable) 
	{
		g2_glEnable(G2_GL_BLEND);
		g2_glBlendFunc(G2_GL_SRC_ALPHA, G2_GL_ONE_MINUS_SRC_ALPHA);
	}
	else g2_glDisable(G2_GL_BLEND);
}
static __tb_inline__ tb_void_t g2_gl_draw_apply_solid(g2_gl_draw_t* draw)
{
	// apply blend
	g2_gl_draw_apply_blend(draw, g2_style_alpha(draw->style) != 0xff);

	// apply color
	g2_gl_draw_apply_color(draw, g2_style_color(draw->style));
}
static __tb_inline__ tb_void_t g2_gl_draw_apply_wrap(g2_gl_draw_t* draw)
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
	tb_assert(draw->shader->wrap < tb_arrayn(wrap));

	// wrap
	switch (draw->shader->type)
	{
	case G2_GL_SHADER_TYPE_BITMAP:
		g2_glTexParameteri(G2_GL_TEXTURE_2D, G2_GL_TEXTURE_WRAP_S, wrap[draw->shader->wrap]);
		g2_glTexParameteri(G2_GL_TEXTURE_2D, G2_GL_TEXTURE_WRAP_T, wrap[draw->shader->wrap]);
		break;
	case G2_GL_SHADER_TYPE_LINEAR:
	case G2_GL_SHADER_TYPE_RADIAL:
		g2_glTexParameteri(G2_GL_TEXTURE_2D, G2_GL_TEXTURE_WRAP_S, wrap[draw->shader->wrap]);
		g2_glTexParameteri(G2_GL_TEXTURE_2D, G2_GL_TEXTURE_WRAP_T, G2_GL_CLAMP_TO_EDGE);
		break;
	default:
		break;
	}
}
static __tb_inline__ tb_void_t g2_gl_draw_apply_filter(g2_gl_draw_t* draw)
{
	// filter?
	if (g2_style_flag(draw->style) & G2_STYLE_FLAG_BITMAP_FILTER)
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
static __tb_inline__ tb_void_t g2_gl_draw_apply_vertices(g2_gl_draw_t* draw)
{
	if (draw->context->version < 0x20) g2_glVertexPointer(2, G2_GL_FLOAT, 0, draw->vertices);
	else g2_glVertexAttribPointer(g2_gl_program_location(draw->program, G2_GL_PROGRAM_LOCATION_VERTICES), 2, G2_GL_FLOAT, G2_GL_FALSE, 0, draw->vertices);
}
static __tb_inline__ tb_void_t g2_gl_draw_apply_texcoords(g2_gl_draw_t* draw)
{
	// texcoords
	if (draw->context->version < 0x20) g2_glTexCoordPointer(2, G2_GL_FLOAT, 0, draw->texcoords);
	else g2_glVertexAttribPointer(g2_gl_program_location(draw->program, G2_GL_PROGRAM_LOCATION_TEXCOORDS), 2, G2_GL_FLOAT, G2_GL_FALSE, 0, draw->texcoords);
}
static __tb_inline__ tb_bool_t g2_gl_draw_apply_program(g2_gl_draw_t* draw)
{
	if (draw->context->version >= 0x20)
	{	
		// type
		tb_size_t type = G2_GL_PROGRAM_TYPE_COLOR;
		if (draw->shader)
		{
			switch (draw->shader->type)
			{
			case G2_GL_SHADER_TYPE_BITMAP:
				type = G2_GL_PROGRAM_TYPE_BITMAP;
				break;
			case G2_GL_SHADER_TYPE_LINEAR:
			case G2_GL_SHADER_TYPE_RADIAL:
				type = G2_GL_PROGRAM_TYPE_BITMAP;
				break;
			default:
				tb_assert_and_check_return_val(0, tb_false);
				break;
			}
		}

		// program
		draw->program = draw->context->programs[type];
		tb_assert_and_check_return_val(draw->program, tb_false);
		g2_gl_program_uses(draw->program);
	}

	// ok
	return tb_true;
}
static __tb_inline__ tb_void_t g2_gl_draw_enter_vertex_state(g2_gl_draw_t* draw)
{
	// apply antialiasing?
	g2_gl_draw_apply_antialiasing(draw);

	// apply vertices & texcoords
	if (draw->context->version < 0x20)
	{
		// enable vertices
		g2_glEnableClientState(G2_GL_VERTEX_ARRAY);
	}
	else
	{
		// enable vertices
		g2_glEnableVertexAttribArray(g2_gl_program_location(draw->program, G2_GL_PROGRAM_LOCATION_VERTICES));

		// apply project matrix
		g2_glUniformMatrix4fv(g2_gl_program_location(draw->program, G2_GL_PROGRAM_LOCATION_MATRIX_PROJECT), 1, G2_GL_FALSE, draw->context->matrix);
	}
}
static __tb_inline__ tb_void_t g2_gl_draw_leave_vertex_state(g2_gl_draw_t* draw)
{
	// disable antialiasing
	g2_glDisable(G2_GL_MULTISAMPLE);

	// apply vertices & texcoords
	if (draw->context->version < 0x20)
	{
		// disable vertices
		g2_glDisableClientState(G2_GL_VERTEX_ARRAY);
	}
	else
	{
		// disable vertices
		g2_glDisableVertexAttribArray(g2_gl_program_location(draw->program, G2_GL_PROGRAM_LOCATION_VERTICES));
	}
}
static __tb_inline__ tb_void_t g2_gl_draw_enter_texture_state(g2_gl_draw_t* draw)
{
	// enable texture
	g2_glEnable(G2_GL_TEXTURE_2D);

	// bind texture
	g2_glBindTexture(G2_GL_TEXTURE_2D, *draw->shader->texture);

	// apply vertices & texcoords
	if (draw->context->version < 0x20)
	{
		// enable texcoords
		g2_glEnableClientState(G2_GL_TEXTURE_COORD_ARRAY);

		// apply mode
		g2_glTexEnvi(G2_GL_TEXTURE_ENV, G2_GL_TEXTURE_ENV_MODE, G2_GL_MODULATE);
	}
	else
	{
		// enable texcoords
		g2_glEnableVertexAttribArray(g2_gl_program_location(draw->program, G2_GL_PROGRAM_LOCATION_TEXCOORDS));
	}

	// apply blend
	tb_byte_t 	alpha = g2_style_alpha(draw->style);
	g2_gl_draw_apply_blend(draw, draw->shader->flag & G2_GL_SHADER_FLAG_ALPHA || draw->shader->wrap == G2_SHADER_WRAP_BORDER || alpha != 0xff);

	// apply color
	g2_gl_draw_apply_color(draw, g2_color_make(alpha, 0xff, 0xff, 0xff));

	// apply wrap
	g2_gl_draw_apply_wrap(draw);

	// apply filter
	g2_gl_draw_apply_filter(draw);
}
static __tb_inline__ tb_void_t g2_gl_draw_leave_texture_state(g2_gl_draw_t* draw)
{
	// apply vertices & texcoords
	if (draw->context->version < 0x20)
	{
		// disable texcoords
		g2_glDisableClientState(G2_GL_TEXTURE_COORD_ARRAY);
	}
	else
	{
		// disable texcoords
		g2_glDisableVertexAttribArray(g2_gl_program_location(draw->program, G2_GL_PROGRAM_LOCATION_TEXCOORDS));
	}

	// disable texture
	g2_glDisable(G2_GL_TEXTURE_2D);
}
static __tb_inline__ tb_void_t g2_gl_draw_enter_vertex_matrix(g2_gl_draw_t* draw)
{
	if (draw->context->version < 0x20)
	{
		g2_glMatrixMode(G2_GL_MODELVIEW);
		g2_glPushMatrix();
	}
}
static __tb_inline__ tb_void_t g2_gl_draw_apply_vertex_matrix(g2_gl_draw_t* draw)
{
	if (draw->context->version < 0x20)
	{
		g2_glMatrixMode(G2_GL_MODELVIEW);
		g2_glLoadIdentity();
		g2_glMultMatrixf(draw->vmatrix);
	}
	else g2_glUniformMatrix4fv(g2_gl_program_location(draw->program, G2_GL_PROGRAM_LOCATION_MATRIX_MODEL), 1, G2_GL_FALSE, draw->vmatrix);
}
static __tb_inline__ tb_void_t g2_gl_draw_leave_vertex_matrix(g2_gl_draw_t* draw)
{
	if (draw->context->version < 0x20)
	{
		g2_glMatrixMode(G2_GL_MODELVIEW);
		g2_glPopMatrix();
	}
}
static __tb_inline__ tb_void_t g2_gl_draw_enter_texture_matrix(g2_gl_draw_t* draw)
{
	// apply matrix
	if (draw->context->version < 0x20)
	{
		// enter the texture matrix mode
		g2_glMatrixMode(G2_GL_TEXTURE);
		g2_glPushMatrix();
	}
}
static __tb_inline__ tb_void_t g2_gl_draw_apply_texture_matrix(g2_gl_draw_t* draw, g2_gl_rect_t const* bounds)
{
	// check
	tb_assert_and_check_return(draw->shader);

	// init
	tb_float_t bx = bounds->x1;
	tb_float_t by = bounds->y1;
	tb_float_t bw = bounds->x2 - bounds->x1;
	tb_float_t bh = bounds->y2 - bounds->y1;
	tb_float_t sw = draw->shader->width;
	tb_float_t sh = draw->shader->height;

	// apply matrix
	if (draw->context->version < 0x20)
	{
		// apply the texture matrix	
		g2_glMatrixMode(G2_GL_TEXTURE);
		g2_glLoadIdentity();
		g2_glMultMatrixf(draw->shader->matrix_gl);

		// disable auto scale in the bounds
		g2_glScalef(bw / sw, bh / sh, 1.0f);

		// move viewport to global
		g2_glTranslatef(bx / bw, by / bh, 0.0f);
	}
	else 
	{
		// init matrix
		g2_gl_matrix_copy(draw->tmatrix, draw->shader->matrix_gl);

		// disable auto scale in the bounds
		g2_gl_matrix_scale(draw->tmatrix, bw / sw, bh / sh);

		// move viewport to global
		g2_gl_matrix_translate(draw->tmatrix, bx / bw, by / bh);

		// apply the texture matrix
		g2_glUniformMatrix4fv(g2_gl_program_location(draw->program, G2_GL_PROGRAM_LOCATION_MATRIX_TEXCOORD), 1, G2_GL_FALSE, draw->tmatrix);
	}
}
static __tb_inline__ tb_void_t g2_gl_draw_leave_texture_matrix(g2_gl_draw_t* draw)
{
	if (draw->context->version < 0x20)
	{
		// leave the texture matrix mode
		g2_glMatrixMode(G2_GL_TEXTURE);
		g2_glPopMatrix();
		g2_glMatrixMode(G2_GL_MODELVIEW);
	}
}
static __tb_inline__ tb_void_t g2_gl_draw_stencil_init(g2_gl_draw_t* draw)
{
	// has stencil or has clipper? init it
	if ( 	draw->flag & G2_GL_DRAW_FLAG_STENCIL
		|| ( 	!(draw->flag & G2_GL_DRAW_FLAG_SCISSOR)
			&& 	g2_clipper_size(draw->clipper)))
	{
		// enable stencil
		g2_glDisable(G2_GL_BLEND);
		g2_glDisable(G2_GL_TEXTURE_2D);
		g2_glDisable(G2_GL_DEPTH_TEST);
		g2_glEnable(G2_GL_STENCIL_TEST);

		// init stencil
		g2_glStencilFunc(G2_GL_ALWAYS, 0, 0);
		g2_glStencilOp(G2_GL_INVERT, G2_GL_INVERT, G2_GL_INVERT);
		g2_glColorMask(G2_GL_FALSE, G2_GL_FALSE, G2_GL_FALSE, G2_GL_FALSE);

		// use stencil 
		draw->flag |= G2_GL_DRAW_FLAG_STENCIL;

		// init the pass value
		draw->pass = 0xff;
	}
}
static __tb_inline__ tb_void_t g2_gl_draw_stencil_clip_bounds(g2_gl_draw_t* draw, g2_gl_rect_t const* bounds)
{
	// init vertices
	draw->vertices[0] = bounds->x1;
	draw->vertices[1] = bounds->y1;
	draw->vertices[2] = bounds->x2;
	draw->vertices[3] = bounds->y1;
	draw->vertices[4] = bounds->x1;
	draw->vertices[5] = bounds->y2;
	draw->vertices[6] = bounds->x2;
	draw->vertices[7] = bounds->y2;
	
	// apply vertices
	g2_gl_draw_apply_vertices(draw);

	// draw 
	g2_glDrawArrays(G2_GL_TRIANGLE_STRIP, 0, 4);
}
static __tb_inline__ tb_void_t g2_gl_draw_stencil_clip_rect(g2_gl_draw_t* draw, g2_clipper_item_t const* item)
{
	// check
	tb_assert_and_check_return(item->type == G2_CLIPPER_ITEM_RECT);
	
	// init bounds
	g2_gl_rect_t bounds;
	bounds.x1 = g2_float_to_tb(item->u.rect.x);
	bounds.y1 = g2_float_to_tb(item->u.rect.y);
	bounds.x2 = g2_float_to_tb(item->u.rect.x + item->u.rect.w);
	bounds.y2 = g2_float_to_tb(item->u.rect.y + item->u.rect.h);
	tb_check_return(bounds.x1 < bounds.x2 && bounds.y1 < bounds.y2);

	// clip bounds
	g2_gl_draw_stencil_clip_bounds(draw, &bounds);
}
static __tb_inline__ tb_void_t g2_gl_draw_stencil_clip_triangle(g2_gl_draw_t* draw, g2_clipper_item_t const* item)
{
	// check
	tb_assert_and_check_return(item->type == G2_CLIPPER_ITEM_TRIANGLE);
	
	// init vertices
	draw->vertices[0] = g2_float_to_tb(item->u.triangle.p0.x);
	draw->vertices[1] = g2_float_to_tb(item->u.triangle.p0.y);
	draw->vertices[2] = g2_float_to_tb(item->u.triangle.p1.x);
	draw->vertices[3] = g2_float_to_tb(item->u.triangle.p1.y);
	draw->vertices[4] = g2_float_to_tb(item->u.triangle.p2.x);
	draw->vertices[5] = g2_float_to_tb(item->u.triangle.p2.y);
	
	// apply vertices
	g2_gl_draw_apply_vertices(draw);

	// draw 
	g2_glDrawArrays(G2_GL_TRIANGLE_STRIP, 0, 3);
}
static __tb_inline__ tb_void_t g2_gl_draw_stencil_clip_path(g2_gl_draw_t* draw, g2_clipper_item_t const* item)
{
	// check
	tb_assert_and_check_return(item->type == G2_CLIPPER_ITEM_PATH);

	// the clip path
	g2_gl_path_t* path = (g2_gl_path_t*)item->u.path;
	tb_assert_and_check_return(path);

	// null?
	tb_check_return(!g2_path_null(path));

	// like
	g2_gl_path_make_like(path);

	// like rect?
	if (path->like == G2_GL_PATH_LIKE_RECT)
	{
		// clip bounds
		g2_gl_draw_stencil_clip_bounds(draw, &path->rect);

		// ok
		return ;
	}
	// like triangle?
	else if (path->like == G2_GL_PATH_LIKE_TRIG)
	{
		// clip triangle
		g2_clipper_item_t clip = {0};
		clip.type = G2_CLIPPER_ITEM_TRIANGLE;
		clip.mode = item->mode;
		clip.u.triangle = path->trig;
		g2_gl_draw_stencil_clip_triangle(draw, &clip);

		// ok
		return ;
	}

	// make draw
	if (!g2_gl_path_make_fill(path)) return ;

	// check
	tb_assert(path->fill.data && tb_vector_size(path->fill.data));
	tb_assert(path->fill.size && tb_vector_size(path->fill.size));
	tb_check_return(path->fill.rect.x1 < path->fill.rect.x2 && path->fill.rect.y1 < path->fill.rect.y2);
	
	// init vertices
	if (draw->context->version < 0x20)
		g2_glVertexPointer(2, G2_GL_FLOAT, 0, tb_vector_data(path->fill.data));
	else g2_glVertexAttribPointer(g2_gl_program_location(draw->program, G2_GL_PROGRAM_LOCATION_VERTICES), 2, G2_GL_FLOAT, G2_GL_FALSE, 0, tb_vector_data(path->fill.data));

	// clip path
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
}
static __tb_inline__ tb_void_t g2_gl_draw_stencil_clip_circle(g2_gl_draw_t* draw, g2_clipper_item_t const* item)
{
	// check
	tb_assert_and_check_return(item->type == G2_CLIPPER_ITEM_CIRCLE);

	// init shape
	g2_shape_t shape = {0};
	shape.type = G2_SHAPE_TYPE_CIRCLE;
	shape.u.circle = item->u.circle;

	// get path from pcache first
	tb_handle_t path = g2_pcache_get(draw->painter->pcache, &shape);
	if (!path)
	{
		// init path from cache
		path = g2_pcache_add(draw->painter->pcache, &shape);
		tb_assert_and_check_return(path);

		// add circle to path
		g2_path_add_circle(path, &item->u.circle);
	}
	
	// clip path
	g2_clipper_item_t clip = {0};
	clip.type = G2_CLIPPER_ITEM_PATH;
	clip.mode = item->mode;
	clip.u.path = path;
	g2_gl_draw_stencil_clip_path(draw, &clip);
}
static __tb_inline__ tb_void_t g2_gl_draw_stencil_clip_ellipse(g2_gl_draw_t* draw, g2_clipper_item_t const* item)
{
	// check
	tb_assert_and_check_return(item->type == G2_CLIPPER_ITEM_ELLIPSE);
	
	// init shape
	g2_shape_t shape = {0};
	shape.type = G2_SHAPE_TYPE_ELLIPSE;
	shape.u.ellipse = item->u.ellipse;

	// get path from pcache first
	tb_handle_t path = g2_pcache_get(draw->painter->pcache, &shape);
	if (!path)
	{
		// init path from cache
		path = g2_pcache_add(draw->painter->pcache, &shape);
		tb_assert_and_check_return(path);

		// add ellipse to path
		g2_path_add_ellipse(path, &item->u.ellipse);
	}
	
	// clip path
	g2_clipper_item_t clip = {0};
	clip.type = G2_CLIPPER_ITEM_PATH;
	clip.mode = item->mode;
	clip.u.path = path;
	g2_gl_draw_stencil_clip_path(draw, &clip);
}
static __tb_inline__ tb_void_t g2_gl_draw_stencil_clip_item(g2_gl_draw_t* draw, g2_clipper_item_t const* item)
{
	// the clipper impl
	static tb_void_t (*clip[])(g2_gl_draw_t* , g2_clipper_item_t const* ) = 
	{
		g2_gl_draw_stencil_clip_rect
	,	g2_gl_draw_stencil_clip_path
	,	g2_gl_draw_stencil_clip_circle
	,	g2_gl_draw_stencil_clip_ellipse
	,	g2_gl_draw_stencil_clip_triangle
	};
	tb_assert_and_check_return(item->type < tb_arrayn(clip));

	// apply stencil for draw path
	g2_glStencilFunc(G2_GL_ALWAYS, 0, 0);
	g2_glStencilOp(G2_GL_INVERT, G2_GL_INVERT, G2_GL_INVERT);

	// clip it
	clip[item->type](draw, item);
}
static __tb_inline__ tb_void_t g2_gl_draw_stencil_clip(g2_gl_draw_t* draw, g2_gl_rect_t const* bounds)
{
	// check
	tb_check_return(draw->flag & G2_GL_DRAW_FLAG_STENCIL);

	// no scissor
	tb_check_return(!(draw->flag & G2_GL_DRAW_FLAG_SCISSOR));

	// the clipper size
	tb_size_t size = g2_clipper_size(draw->clipper);
	tb_check_return(size);

	// force to done mask
	tb_bool_t fmask = (draw->shader && draw->shader->type == G2_GL_SHADER_TYPE_RADIAL)? tb_true : tb_false;

	/* clip stencil
	 *
	 * invisible: 	0x01 or 0xfe
	 * visible: 	0
	 * invalidate: 	no
	 */
	tb_size_t i = 0;
	for (i = 0; i < size; i++)
	{
		// the clip item
		g2_clipper_item_t const* item = g2_clipper_item(draw->clipper, i);
		if (item)
		{
			// prepare the stencil mask for union mode
			if (item->mode == G2_CLIPPER_MODE_UNION)
			{
				// 0x01 => 0xfe
				g2_glStencilFunc(G2_GL_EQUAL, 0x01, 0xff);
				g2_glStencilOp(G2_GL_KEEP, G2_GL_INVERT, G2_GL_INVERT);
				g2_gl_draw_stencil_clip_bounds(draw, bounds);
			}

			// save vetex matrix
			tb_float_t matrix0[16];
			g2_gl_matrix_copy(matrix0, draw->vmatrix);

			// clip matrix => vertex matrix
			g2_gl_matrix_from(draw->vmatrix, &item->matrix);

			// apply vetex matrix
			g2_gl_draw_apply_vertex_matrix(draw);

			// clip item
			g2_gl_draw_stencil_clip_item(draw, item);

			// restore vetex matrix
			g2_gl_matrix_copy(draw->vmatrix, matrix0);

			// apply vetex matrix
			g2_gl_draw_apply_vertex_matrix(draw);
			
			// filter the stencil mask
			switch (item->mode)
			{
			case G2_CLIPPER_MODE_REPLACE:
				{
					// done mask
					if (i + 1 < size || fmask)
					{
						// 0x00 => 0x01, 0xff => 0x00
						g2_glStencilFunc(G2_GL_EQUAL, 0xff, 0xff);
						g2_glStencilOp(G2_GL_INCR, G2_GL_ZERO, G2_GL_ZERO);
						g2_gl_draw_stencil_clip_bounds(draw, bounds);

						// pass: 0x00
						draw->pass = 0x00;
					}
					// last? using the pass value directly
					else draw->pass = 0xff;
				}
				break;
			case G2_CLIPPER_MODE_INTERSECT:
				{
					// done mask
					if (i + 1 < size || fmask)
					{
						// 0x00 => 0x01
						g2_glStencilFunc(G2_GL_EQUAL, 0x00, 0xff);
						g2_glStencilOp(G2_GL_KEEP, G2_GL_INCR, G2_GL_INCR);
						g2_gl_draw_stencil_clip_bounds(draw, bounds);

						// 0xff => 0x00
						g2_glStencilFunc(G2_GL_EQUAL, 0xff, 0xff);
						g2_glStencilOp(G2_GL_KEEP, G2_GL_ZERO, G2_GL_ZERO);
						g2_gl_draw_stencil_clip_bounds(draw, bounds);

						// pass: 0x00
						draw->pass = 0x00;
					}
					// last? using the pass value directly
					else draw->pass = 0xff;
				}
				break;
			case G2_CLIPPER_MODE_UNION:
				{
					// 0x01 => 0x00, 0xff => 0x00
					g2_glStencilFunc(G2_GL_NOTEQUAL, 0xfe, 0xff);
					g2_glStencilOp(G2_GL_KEEP, G2_GL_ZERO, G2_GL_ZERO);
					g2_gl_draw_stencil_clip_bounds(draw, bounds);

					// pass: 0x00
					draw->pass = 0x00;
				}
				break;
			case G2_CLIPPER_MODE_SUBTRACT:
				{
					// done mask
					if (i + 1 < size)
					{
						// 0xff => 0xfe
						g2_glStencilFunc(G2_GL_EQUAL, 0xff, 0xff);
						g2_glStencilOp(G2_GL_KEEP, G2_GL_DECR, G2_GL_DECR);
						g2_gl_draw_stencil_clip_bounds(draw, bounds);

						// pass: 0x00
						draw->pass = 0x00;
					}
					// last? using the pass value directly
					else draw->pass = 0x00;
				}
				break;
			default:
				tb_trace_impl("unknown clip mode: %lu", item->mode);
				break;
			}
		}
	}

	// apply stencil for draw path
	g2_glStencilFunc(G2_GL_ALWAYS, 0, 0);
	g2_glStencilOp(G2_GL_INVERT, G2_GL_INVERT, G2_GL_INVERT);

	// invert pass 
	draw->pass = ~draw->pass;
}
static __tb_inline__ tb_void_t g2_gl_draw_stencil_draw(g2_gl_draw_t* draw)
{
	// check
	tb_check_return(draw->flag & G2_GL_DRAW_FLAG_STENCIL);

	// draw stencil
	g2_glStencilFunc(G2_GL_EQUAL, (g2_GLint_t)draw->pass, 0xff);
	g2_glStencilOp(G2_GL_ZERO, G2_GL_ZERO, G2_GL_ZERO);
	g2_glColorMask(G2_GL_TRUE, G2_GL_TRUE, G2_GL_TRUE, G2_GL_TRUE);
}
static __tb_inline__ tb_void_t g2_gl_draw_stencil_exit(g2_gl_draw_t* draw)
{
	// check
	tb_check_return(draw->flag & G2_GL_DRAW_FLAG_STENCIL);

	// exit
	g2_glColorMask(G2_GL_TRUE, G2_GL_TRUE, G2_GL_TRUE, G2_GL_TRUE);
	g2_glDisable(G2_GL_STENCIL_TEST);
}
static __tb_inline__ tb_void_t g2_gl_draw_scissor_init(g2_gl_draw_t* draw)
{
	// only one rect and no rotate?
	if (g2_clipper_size(draw->clipper) == 1)
	{
		g2_clipper_item_t const* item = (g2_clipper_item_t const*)g2_clipper_item(draw->clipper, 0);
		if (item && item->type == G2_CLIPPER_ITEM_RECT && g2_ez(item->matrix.kx) && g2_ez(item->matrix.ky)) 
		{
			// the height
			tb_size_t height = g2_bitmap_height(draw->context->surface);
			tb_assert_and_check_return(height);

			// enable scissor
			draw->flag |= G2_GL_DRAW_FLAG_SCISSOR;
			g2_glEnable(G2_GL_SCISSOR_TEST);
			
			// transform rect
			g2_float_t ox1 = item->u.rect.x;
			g2_float_t oy1 = item->u.rect.y;
			g2_float_t ox2 = item->u.rect.x + item->u.rect.w;
			g2_float_t oy2 = item->u.rect.y + item->u.rect.h;
			g2_float_t nx1 = g2_matrix_apply_x(&item->matrix, ox1, oy1);
			g2_float_t ny1 = g2_matrix_apply_y(&item->matrix, ox1, oy1);
			g2_float_t nx2 = g2_matrix_apply_x(&item->matrix, ox2, oy2);
			g2_float_t ny2 = g2_matrix_apply_y(&item->matrix, ox2, oy2);

			// scissor, @note y-position for gl
			g2_glScissor(g2_float_to_tb(nx1), (tb_float_t)height - g2_float_to_tb(ny2), g2_float_to_tb(nx2 - nx1), g2_float_to_tb(ny2 - ny1));
		}
	}
}
static __tb_inline__ tb_void_t g2_gl_draw_scissor_exit(g2_gl_draw_t* draw)
{
	if (draw->flag & G2_GL_DRAW_FLAG_SCISSOR) g2_glDisable(G2_GL_SCISSOR_TEST);
}
static __tb_inline__ tb_bool_t g2_gl_draw_context_init(g2_gl_draw_t* draw)
{
	// apply program first
	if (!g2_gl_draw_apply_program(draw)) return tb_false;

	// enter vertex state
	g2_gl_draw_enter_vertex_state(draw);

	// apply solid if no shader
	if (!draw->shader) g2_gl_draw_apply_solid(draw);
	
	// ok
	return tb_true;
}
static __tb_inline__ tb_void_t g2_gl_draw_context_exit(g2_gl_draw_t* draw)
{
	// leave vertex state
	g2_gl_draw_leave_vertex_state(draw);

	// leave texture state
	g2_gl_draw_leave_texture_state(draw);

	// disable blend
	g2_glDisable(G2_GL_BLEND);
}
static __tb_inline__ tb_void_t g2_gl_draw_style_fill_color(g2_gl_draw_t* draw, g2_gl_rect_t const* bounds)
{
	// apply solid
	g2_gl_draw_apply_solid(draw);

	// init vertices
	draw->vertices[0] = bounds->x1;
	draw->vertices[1] = bounds->y1;
	draw->vertices[2] = bounds->x2;
	draw->vertices[3] = bounds->y1;
	draw->vertices[4] = bounds->x1;
	draw->vertices[5] = bounds->y2;
	draw->vertices[6] = bounds->x2;
	draw->vertices[7] = bounds->y2;
	
	// apply vertices
	g2_gl_draw_apply_vertices(draw);

	// draw
	g2_glDrawArrays(G2_GL_TRIANGLE_STRIP, 0, 4);
}
static __tb_inline__ tb_void_t g2_gl_draw_style_fill_shader_bitmap(g2_gl_draw_t* draw, g2_gl_rect_t const* bounds)
{
	// enter texture state
	g2_gl_draw_enter_texture_state(draw);

	// enter texture matrix
	g2_gl_draw_enter_texture_matrix(draw);

	// init texcoords
	draw->texcoords[0] = 0.0f;
	draw->texcoords[1] = 0.0f;
	draw->texcoords[2] = 1.0f;
	draw->texcoords[3] = 0.0f;
	draw->texcoords[4] = 0.0f;
	draw->texcoords[5] = 1.0f;
	draw->texcoords[6] = 1.0f;
	draw->texcoords[7] = 1.0f;

	// apply texcoords
	g2_gl_draw_apply_texcoords(draw);

	// init vertices
	draw->vertices[0] = bounds->x1;
	draw->vertices[1] = bounds->y1;
	draw->vertices[2] = bounds->x2;
	draw->vertices[3] = bounds->y1;
	draw->vertices[4] = bounds->x1;
	draw->vertices[5] = bounds->y2;
	draw->vertices[6] = bounds->x2;
	draw->vertices[7] = bounds->y2;
	
	// apply vertices
	g2_gl_draw_apply_vertices(draw);

	// apply texture matrix
	g2_gl_draw_apply_texture_matrix(draw, bounds);

	// draw
	g2_glDrawArrays(G2_GL_TRIANGLE_STRIP, 0, 4);

	// leave texture matrix
	g2_gl_draw_leave_texture_matrix(draw);

	// leave texture state
	g2_gl_draw_leave_texture_state(draw);
}
static __tb_inline__ tb_void_t g2_gl_draw_style_fill_shader_linear(g2_gl_draw_t* draw, g2_gl_rect_t const* bounds)
{
	// enter texture state
	g2_gl_draw_enter_texture_state(draw);

	// enter texture matrix
	g2_gl_draw_enter_texture_matrix(draw);

	// init texcoords
	draw->texcoords[0] = 0.0f;
	draw->texcoords[1] = 0.0f;
	draw->texcoords[2] = 1.0f;
	draw->texcoords[3] = 0.0f;
	draw->texcoords[4] = 0.0f;
	draw->texcoords[5] = 1.0f;
	draw->texcoords[6] = 1.0f;
	draw->texcoords[7] = 1.0f;

	// apply texcoords
	g2_gl_draw_apply_texcoords(draw);

	// init vertices
	draw->vertices[0] = bounds->x1;
	draw->vertices[1] = bounds->y1;
	draw->vertices[2] = bounds->x2;
	draw->vertices[3] = bounds->y1;
	draw->vertices[4] = bounds->x1;
	draw->vertices[5] = bounds->y2;
	draw->vertices[6] = bounds->x2;
	draw->vertices[7] = bounds->y2;
	
	// apply vertices
	g2_gl_draw_apply_vertices(draw);

	// apply texture matrix
	g2_gl_draw_apply_texture_matrix(draw, bounds);

	// draw
	g2_glDrawArrays(G2_GL_TRIANGLE_STRIP, 0, 4);

	// leave texture matrix
	g2_gl_draw_leave_texture_matrix(draw);

	// leave texture state
	g2_gl_draw_leave_texture_state(draw);
}
static __tb_inline__ tb_void_t g2_gl_draw_style_fill_shader_radial(g2_gl_draw_t* draw, g2_gl_rect_t const* bounds)
{
	// enter texture state
	g2_gl_draw_enter_texture_state(draw);

	// enter texture matrix
	g2_gl_draw_enter_texture_matrix(draw);

	// init texcoords
	draw->texcoords[0] = 0.0f;
	draw->texcoords[1] = 0.0f;
	draw->texcoords[2] = 1.0f;
	draw->texcoords[3] = 0.0f;
	draw->texcoords[4] = 0.0f;
	draw->texcoords[5] = 1.0f;
	draw->texcoords[6] = 1.0f;
	draw->texcoords[7] = 1.0f;

	// apply texcoords
	g2_gl_draw_apply_texcoords(draw);

	// init radial variables
	tb_float_t smatrix[16];
	g2_gl_matrix_from(smatrix, &draw->shader->matrix);
	tb_float_t cx = g2_float_to_tb(draw->shader->u.radial.cp.c.x);
	tb_float_t cy = g2_float_to_tb(draw->shader->u.radial.cp.c.y);
	tb_float_t x0 = g2_gl_matrix_apply_x(smatrix, cx, cy);
	tb_float_t y0 = g2_gl_matrix_apply_y(smatrix, cx, cy);

	// init scale factor
	tb_float_t sx = tb_fabs(smatrix[0]);
	tb_float_t sy = tb_fabs(smatrix[5]);
	tb_float_t fs = tb_min(sx, sy);
	if (fs < 1e-9) fs = 1e-9;

	// init maximum radius 
	tb_float_t n1 = (x0 - bounds->x1) * (x0 - bounds->x1) + (y0 - bounds->y1) * (y0 - bounds->y1);
	tb_float_t n2 = (x0 - bounds->x2) * (x0 - bounds->x2) + (y0 - bounds->y1) * (y0 - bounds->y1);
	tb_float_t n3 = (x0 - bounds->x1) * (x0 - bounds->x1) + (y0 - bounds->y2) * (y0 - bounds->y2);
	tb_float_t n4 = (x0 - bounds->x2) * (x0 - bounds->x2) + (y0 - bounds->y2) * (y0 - bounds->y2);
	if (n2 > n1) n1 = n2;
	if (n3 > n1) n1 = n3; 
	if (n4 > n1) n1 = n4; 
	tb_float_t rm = (tb_float_t)(tb_isqrti(tb_ceil(n1)) + 1) / fs;

	// the radial factor
	static g2_gl_draw_radial_factor_t factors[] =
	{
		{0.105396307f, 	12.0f, 	30} // rm * sin(6.05)
	,	{0.070626986f, 	8.0f, 	45} // rm * sin(4.05)
	,	{0.035771616f, 	4.0f, 	90} // rm * sin(2.05)
	};
	tb_assert(g2_quality() < tb_arrayn(factors));
	g2_gl_draw_radial_factor_t const* factor = &factors[g2_quality()];

	/* init fragment vertices
	 *        
	 *        fn
	 * *****|*****
	 *  *   |   *
	 *   *rm|  *
	 *    * | *
	 *     *|*
	 *      *
	 */
	tb_float_t fn = rm * factor->factor; // rm * sin(x.05)
	draw->vertices[0] = cx - fn;
	draw->vertices[1] = cy - rm;
	draw->vertices[2] = cx + fn;
	draw->vertices[3] = cy - rm;
	draw->vertices[4] = cx;
	draw->vertices[5] = cy;

	// init fragment bounds
	g2_gl_rect_t fbounds;
	g2_gl_rect_init(&fbounds, draw->vertices[0], draw->vertices[1]);
	g2_gl_rect_done(&fbounds, draw->vertices[2], draw->vertices[3]);
	g2_gl_rect_done(&fbounds, draw->vertices[4], draw->vertices[5]);
	
	// apply vertices
	g2_gl_draw_apply_vertices(draw);

	// apply texture matrix
	g2_gl_draw_apply_texture_matrix(draw, &fbounds);

	// save vetex matrix
	tb_float_t matrix0[16];
	g2_gl_matrix_copy(matrix0, draw->vmatrix);

	// apply shader matrix
	g2_gl_matrix_multiply(draw->vmatrix, smatrix);

	// init rotate matrix: rotate one degress
	tb_float_t matrix1[16];
	g2_gl_matrix_init_rotatep(matrix1, factor->rotation, cx, cy);

	// rotate for drawing all fragments
	tb_size_t n = factor->count;
	while (n--)
	{
		// rotate one degress
		g2_gl_matrix_multiply(draw->vmatrix, matrix1);

		// apply vetex matrix
		g2_gl_draw_apply_vertex_matrix(draw);

		// draw fragment
		g2_glDrawArrays(G2_GL_TRIANGLE_STRIP, 0, 3);

	}

	// restore vetex matrix
	g2_gl_matrix_copy(draw->vmatrix, matrix0);

	// apply vetex matrix
	g2_gl_draw_apply_vertex_matrix(draw);

	// leave texture matrix
	g2_gl_draw_leave_texture_matrix(draw);

	// leave texture state
	g2_gl_draw_leave_texture_state(draw);
}
static __tb_inline__ tb_void_t g2_gl_draw_style_fill_shader(g2_gl_draw_t* draw, g2_gl_rect_t const* bounds)
{
	// draw shader
	switch (draw->shader->type)
	{
	case G2_GL_SHADER_TYPE_BITMAP:
		g2_gl_draw_style_fill_shader_bitmap(draw, bounds);
		break;
	case G2_GL_SHADER_TYPE_LINEAR:
		g2_gl_draw_style_fill_shader_linear(draw, bounds);
		break;
	case G2_GL_SHADER_TYPE_RADIAL:
		g2_gl_draw_style_fill_shader_radial(draw, bounds);
		break;
		break;
	default:
		break;
	}
}
static __tb_inline__ tb_void_t g2_gl_draw_style_fill(g2_gl_draw_t* draw, g2_gl_rect_t const* bounds)
{
	// rect or stencil?
	tb_check_return(draw->flag & (G2_GL_DRAW_FLAG_RECT | G2_GL_DRAW_FLAG_STENCIL));

	// draw
	if (draw->shader) g2_gl_draw_style_fill_shader(draw, bounds);
	else g2_gl_draw_style_fill_color(draw, bounds);
}
static __tb_inline__ tb_void_t g2_gl_draw_style_stok(g2_gl_draw_t* draw, g2_gl_rect_t const* bounds)
{
	// draw
	if (draw->shader) g2_gl_draw_style_fill_shader(draw, bounds);
}
static __tb_inline__ tb_bool_t g2_gl_draw_init(g2_gl_draw_t* draw, g2_gl_painter_t* painter, tb_size_t mode, tb_size_t flag)
{
	// init draw
	draw->painter 	= painter;
	draw->context 	= painter->context;
	draw->style 	= g2_style(painter);
	draw->shader 	= g2_style_shader(draw->style);
	draw->clipper 	= g2_clipper(painter);
	draw->flag 		= flag;
	draw->mode 		= mode;
	g2_gl_matrix_from(draw->vmatrix, &draw->painter->matrix);
	tb_assert_and_check_return_val(draw->painter && draw->context && draw->context->surface && draw->style && draw->clipper, tb_false);

	// use stencil?
	if (!(flag & G2_GL_DRAW_FLAG_CONVEX)) draw->flag |= G2_GL_DRAW_FLAG_STENCIL;
	else if (flag & G2_GL_DRAW_FLAG_RECT)
	{ 
		if (draw->shader && draw->shader->type == G2_GL_SHADER_TYPE_RADIAL) draw->flag |= G2_GL_DRAW_FLAG_STENCIL;
	}
	else if (draw->shader) draw->flag |= G2_GL_DRAW_FLAG_STENCIL;

	// init context
	if (!g2_gl_draw_context_init(draw)) return tb_false;

	// enter vetex matrix
	g2_gl_draw_enter_vertex_matrix(draw);

	// apply vetex matrix
	g2_gl_draw_apply_vertex_matrix(draw);

	// init scissor
	g2_gl_draw_scissor_init(draw);

	// init stencil
	g2_gl_draw_stencil_init(draw);

	// ok
	return tb_true;
}
static __tb_inline__ tb_void_t g2_gl_draw_clip(g2_gl_draw_t* draw, g2_gl_rect_t* bounds)
{
	// clip stencil
	g2_gl_draw_stencil_clip(draw, bounds);
}
static __tb_inline__ tb_void_t g2_gl_draw_fill(g2_gl_draw_t* draw, g2_gl_rect_t* bounds)
{
	// draw stencil
	g2_gl_draw_stencil_draw(draw);

	// draw style
	g2_gl_draw_style_fill(draw, bounds);
}
static __tb_inline__ tb_void_t g2_gl_draw_stok(g2_gl_draw_t* draw, g2_gl_rect_t* bounds)
{
	// draw stencil
	g2_gl_draw_stencil_draw(draw);

	// draw style
	g2_gl_draw_style_stok(draw, bounds);
}
static __tb_inline__ tb_void_t g2_gl_draw_exit(g2_gl_draw_t* draw)
{
	// exit scissor
	g2_gl_draw_scissor_exit(draw);

	// leave vetex matrix
	g2_gl_draw_leave_vertex_matrix(draw);

	// exit stencil
	g2_gl_draw_stencil_exit(draw);

	// exit context
	g2_gl_draw_context_exit(draw);
}
static tb_void_t g2_gl_draw_bounds(g2_gl_painter_t* painter, tb_size_t mode, g2_gl_rect_t const* bounds)
{
	// init draw
	g2_gl_draw_t draw = {0};
	if (!g2_gl_draw_init(&draw, painter, mode, G2_GL_DRAW_FLAG_RECT | G2_GL_DRAW_FLAG_CONVEX)) return ;

	// clip draw
	g2_gl_draw_clip(&draw, bounds);

	// draw stok
	if (draw.mode == G2_STYLE_MODE_STOK) g2_gl_draw_stok(&draw, bounds);

	// fill or stok
	if ((draw.flag & G2_GL_DRAW_FLAG_STENCIL) || (draw.mode == G2_STYLE_MODE_STOK))
	{
		// init vertices
		draw.vertices[0] = bounds->x1;
		draw.vertices[1] = bounds->y1;
		draw.vertices[2] = bounds->x2;
		draw.vertices[3] = bounds->y1;
		draw.vertices[4] = bounds->x2;
		draw.vertices[5] = bounds->y2;
		draw.vertices[6] = bounds->x1;
		draw.vertices[7] = bounds->y2;
		
		// draw vertices
		g2_gl_draw_apply_vertices(&draw);
		g2_glDrawArrays(draw.mode == G2_STYLE_MODE_FILL? G2_GL_TRIANGLE_STRIP : G2_GL_LINE_LOOP, 0, 4);
	}

	// draw fill
	if (draw.mode == G2_STYLE_MODE_FILL) g2_gl_draw_fill(&draw, bounds);

	// exit draw
	g2_gl_draw_exit(&draw);
}
/* ///////////////////////////////////////////////////////////////////////
 * interfaces
 */
tb_void_t g2_gl_draw_rect(g2_gl_painter_t* painter, tb_size_t mode, g2_rect_t const* rect)
{
	// check
	tb_assert_and_check_return(painter && rect);
	tb_assert_and_check_return((mode == G2_STYLE_MODE_FILL) || (mode == G2_STYLE_MODE_STOK));

	// init bounds
	g2_gl_rect_t bounds;
	bounds.x1 = g2_float_to_tb(rect->x);
	bounds.y1 = g2_float_to_tb(rect->y);
	bounds.x2 = g2_float_to_tb(rect->x + rect->w);
	bounds.y2 = g2_float_to_tb(rect->y + rect->h);
	tb_check_return(bounds.x1 < bounds.x2 && bounds.y1 < bounds.y2);

	// draw bounds
	g2_gl_draw_bounds(painter, mode, &bounds);
}
tb_void_t g2_gl_draw_path(g2_gl_painter_t* painter, tb_size_t mode, g2_gl_path_t const* path)
{
	// check
	tb_assert_and_check_return(painter && path);
	tb_assert_and_check_return((mode == G2_STYLE_MODE_FILL) || (mode == G2_STYLE_MODE_STOK));

	// null?
	tb_check_return(!g2_path_null(path));

	// make like
	g2_gl_path_make_like((g2_gl_path_t*)path);

	// make draw
	if (!g2_gl_path_make_fill((g2_gl_path_t*)path)) return ;
	
	// check
	tb_assert(path->fill.data && tb_vector_size(path->fill.data));
	tb_assert(path->fill.size && tb_vector_size(path->fill.size));
	tb_check_return(path->fill.rect.x1 < path->fill.rect.x2 && path->fill.rect.y1 < path->fill.rect.y2);
	
	// like rect?
	if (path->like == G2_GL_PATH_LIKE_RECT)
	{
		// draw bounds
		g2_gl_draw_bounds(painter, mode, &path->rect);

		// ok
		return ;
	}
	// like triangle?
	else if (path->like == G2_GL_PATH_LIKE_TRIG)
	{
		// draw triangle
		g2_gl_draw_triangle(painter, mode, &path->trig);

		// ok
		return ;
	}

	// init draw
	g2_gl_draw_t draw = {0};
	if (!g2_gl_draw_init(&draw, painter, mode, path->like == G2_GL_PATH_LIKE_CONX? G2_GL_DRAW_FLAG_CONVEX : G2_GL_DRAW_FLAG_NONE)) return ;

	// clip draw
	g2_gl_draw_clip(&draw, &path->fill.rect);

	// draw stok
	if (draw.mode == G2_STYLE_MODE_STOK) g2_gl_draw_stok(&draw, &path->fill.rect);

	// init vertices
	if (draw.context->version < 0x20)
		g2_glVertexPointer(2, G2_GL_FLOAT, 0, tb_vector_data(path->fill.data));
	else g2_glVertexAttribPointer(g2_gl_program_location(draw.program, G2_GL_PROGRAM_LOCATION_VERTICES), 2, G2_GL_FLOAT, G2_GL_FALSE, 0, tb_vector_data(path->fill.data));

	// draw vertices
	tb_size_t 	head = 0;
	tb_size_t 	size = 0;
	tb_size_t 	itor = tb_iterator_head(path->fill.size);
	tb_size_t 	tail = tb_iterator_tail(path->fill.size);
	g2_GLenum_t gmode = (draw.mode == G2_STYLE_MODE_FILL)? G2_GL_TRIANGLE_FAN : G2_GL_LINE_STRIP;
	for (; itor != tail; itor++)
	{
		size = tb_iterator_item(path->fill.size, itor);
		g2_glDrawArrays(gmode, (g2_GLint_t)head, (g2_GLint_t)size);
		head += size;
	}

	// draw fill
	if (draw.mode == G2_STYLE_MODE_FILL) g2_gl_draw_fill(&draw, &path->fill.rect);

	// exit draw
	g2_gl_draw_exit(&draw);
}
tb_void_t g2_gl_draw_arc(g2_gl_painter_t* painter, tb_size_t mode, g2_arc_t const* arc)
{
	// check
	tb_assert_and_check_return(painter && painter->pcache && arc);
	tb_assert_and_check_return(mode == G2_STYLE_MODE_STOK);

	// init shape
	g2_shape_t shape = {0};
	shape.type = G2_SHAPE_TYPE_ARC;
	shape.u.arc = *arc;

	// get path from pcache first
	tb_handle_t path = g2_pcache_get(painter->pcache, &shape);
	if (!path)
	{
		// init path from cache
		path = g2_pcache_add(painter->pcache, &shape);
		tb_assert_and_check_return(path);

		// add arc to path
		g2_path_add_arc(path, arc);
	}
	
	// draw path
	g2_gl_draw_path(painter, mode, (g2_gl_path_t const*)path);
}
tb_void_t g2_gl_draw_circle(g2_gl_painter_t* painter, tb_size_t mode, g2_circle_t const* circle)
{
	// check
	tb_assert_and_check_return(painter && painter->pcache && circle);
	tb_assert_and_check_return((mode == G2_STYLE_MODE_FILL) || (mode == G2_STYLE_MODE_STOK));

	// init shape
	g2_shape_t shape = {0};
	shape.type = G2_SHAPE_TYPE_CIRCLE;
	shape.u.circle = *circle;

	// get path from pcache first
	tb_handle_t path = g2_pcache_get(painter->pcache, &shape);
	if (!path)
	{
		// init path from cache
		path = g2_pcache_add(painter->pcache, &shape);
		tb_assert_and_check_return(path);

		// add circle to path
		g2_path_add_circle(path, circle);
	}
	
	// draw path
	g2_gl_draw_path(painter, mode, (g2_gl_path_t const*)path);
}
tb_void_t g2_gl_draw_ellipse(g2_gl_painter_t* painter, tb_size_t mode, g2_ellipse_t const* ellipse)
{
	// check
	tb_assert_and_check_return(painter && painter->pcache && ellipse);
	tb_assert_and_check_return((mode == G2_STYLE_MODE_FILL) || (mode == G2_STYLE_MODE_STOK));

	// init shape
	g2_shape_t shape = {0};
	shape.type = G2_SHAPE_TYPE_ELLIPSE;
	shape.u.ellipse = *ellipse;

	// get path from pcache first
	tb_handle_t path = g2_pcache_get(painter->pcache, &shape);
	if (!path)
	{
		// init path from cache
		path = g2_pcache_add(painter->pcache, &shape);
		tb_assert_and_check_return(path);

		// add ellipse to path
		g2_path_add_ellipse(path, ellipse);
	}
	
	// draw path
	g2_gl_draw_path(painter, mode, (g2_gl_path_t const*)path);
}
tb_void_t g2_gl_draw_triangle(g2_gl_painter_t* painter, tb_size_t mode, g2_triangle_t const* triangle)
{
	// check
	tb_assert_and_check_return(painter && triangle);
	tb_assert_and_check_return((mode == G2_STYLE_MODE_FILL) || (mode == G2_STYLE_MODE_STOK));

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

	// init draw
	g2_gl_draw_t draw = {0};
	if (!g2_gl_draw_init(&draw, painter, mode, G2_GL_DRAW_FLAG_CONVEX)) return ;

	// clip draw
	g2_gl_draw_clip(&draw, &bounds);

	// draw stok
	if (draw.mode == G2_STYLE_MODE_STOK) g2_gl_draw_stok(&draw, &bounds);

	// draw vertices
	if (draw.context->version < 0x20) g2_glVertexPointer(2, G2_GL_FLOAT, 0, vertices);
	else g2_glVertexAttribPointer(g2_gl_program_location(draw.program, G2_GL_PROGRAM_LOCATION_VERTICES), 2, G2_GL_FLOAT, G2_GL_FALSE, 0, vertices);
	g2_glDrawArrays((draw.mode == G2_STYLE_MODE_FILL)? G2_GL_TRIANGLE_STRIP : G2_GL_LINE_STRIP, 0, 3);

	// draw fill
	if (draw.mode == G2_STYLE_MODE_FILL) g2_gl_draw_fill(&draw, &bounds);

	// exit draw
	g2_gl_draw_exit(&draw);
}
tb_void_t g2_gl_draw_line(g2_gl_painter_t* painter, tb_size_t mode, g2_line_t const* line)
{	
	// check
	tb_assert_and_check_return(painter && line);
	tb_assert_and_check_return(mode == G2_STYLE_MODE_STOK);

	// init vertices
	tb_float_t vertices[4];
	vertices[0] = g2_float_to_tb(line->p0.x);
	vertices[1] = g2_float_to_tb(line->p0.y);
	vertices[2] = g2_float_to_tb(line->p1.x);
	vertices[3] = g2_float_to_tb(line->p1.y);

	// init bounds
	g2_gl_rect_t bounds;
	g2_gl_rect_init(&bounds, vertices[0], vertices[1]);
	g2_gl_rect_done(&bounds, vertices[2], vertices[3]);
	tb_check_return(bounds.x1 < bounds.x2 && bounds.y1 < bounds.y2);

	// init draw
	g2_gl_draw_t draw = {0};
	if (!g2_gl_draw_init(&draw, painter, mode, G2_GL_DRAW_FLAG_CONVEX)) return ;

	// FIXME opti clip
	// clip draw
	g2_gl_draw_clip(&draw, &bounds);

	// draw stok
	g2_gl_draw_stok(&draw, &bounds);

	// draw vertices
	if (draw.context->version < 0x20) g2_glVertexPointer(2, G2_GL_FLOAT, 0, vertices);
	else g2_glVertexAttribPointer(g2_gl_program_location(draw.program, G2_GL_PROGRAM_LOCATION_VERTICES), 2, G2_GL_FLOAT, G2_GL_FALSE, 0, vertices);
	g2_glDrawArrays(G2_GL_LINE_STRIP, 0, 2);

	// exit draw
	g2_gl_draw_exit(&draw);
}
tb_void_t g2_gl_draw_point(g2_gl_painter_t* painter, tb_size_t mode, g2_point_t const* point)
{
	// check
	tb_assert_and_check_return(painter && point);
	tb_assert_and_check_return(mode == G2_STYLE_MODE_STOK);

	// init vertices
	tb_float_t vertices[4];
	vertices[0] = g2_float_to_tb(point->x);
	vertices[1] = g2_float_to_tb(point->y);

	// init bounds
	g2_gl_rect_t bounds;
	g2_gl_rect_init(&bounds, vertices[0], vertices[1]);
	tb_check_return(bounds.x1 < bounds.x2 && bounds.y1 < bounds.y2);

	// init draw
	g2_gl_draw_t draw = {0};
	if (!g2_gl_draw_init(&draw, painter, mode, G2_GL_DRAW_FLAG_CONVEX)) return ;

	// FIXME opti clip
	// clip draw
	g2_gl_draw_clip(&draw, &bounds);

	// draw stok
	g2_gl_draw_stok(&draw, &bounds);

	// draw vertices
	if (draw.context->version < 0x20) g2_glVertexPointer(2, G2_GL_FLOAT, 0, vertices);
	else g2_glVertexAttribPointer(g2_gl_program_location(draw.program, G2_GL_PROGRAM_LOCATION_VERTICES), 2, G2_GL_FLOAT, G2_GL_FALSE, 0, vertices);
	g2_glDrawArrays(G2_GL_POINTS, 0, 1);

	// exit draw
	g2_gl_draw_exit(&draw);
}
