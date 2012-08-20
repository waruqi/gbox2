/* ///////////////////////////////////////////////////////////////////////
 * includes
 */
#include "demo.h"
#include <GLES/gl.h>
#include <GLES/glext.h>

/* ////////////////////////////////////////////////////////////////////////
 * macros
 */

// pixfmt
//#define G2_DEMO_PIXFMT 			(G2_PIXFMT_XRGB8888 | G2_PIXFMT_NENDIAN)
//#define G2_DEMO_PIXFMT 			(G2_PIXFMT_ARGB8888 | G2_PIXFMT_NENDIAN)
#define G2_DEMO_PIXFMT 				(G2_PIXFMT_RGB565 | G2_PIXFMT_NENDIAN)

/* ////////////////////////////////////////////////////////////////////////
 * globals
 */

// context
static tb_handle_t 	g_context 		= TB_NULL;

// surface
static tb_handle_t 	g_surface 		= TB_NULL;

// painter
static tb_handle_t 	g_painter 		= TB_NULL;

// style
static tb_handle_t 	g_style 		= TB_NULL;

// clock
static tb_hong_t 	g_bt 			= 0;
static tb_hong_t 	g_fp 			= 0;
static tb_hong_t 	g_rt 			= 0;
static tb_hong_t 	g_fps 			= 0;

// position
static tb_long_t 	g_x0 			= 0;
static tb_long_t 	g_y0 			= 0;
static tb_long_t 	g_dx 			= 0;
static tb_long_t 	g_dy 			= 0;
static tb_long_t 	g_x 			= 0;
static tb_long_t 	g_y 			= 0;
static tb_float_t 	g_an 			= 0.;
static tb_bool_t 	g_bm 			= TB_FALSE;
static g2_matrix_t 	g_mx;

// style
static tb_size_t 	g_mode 			= G2_STYLE_MODE_NONE;
static tb_size_t 	g_penw 			= 1;
static tb_size_t 	g_capi 			= 0;
static tb_size_t 	g_joini 		= 0;
static tb_size_t 	g_shaderi 		= 0;
static tb_handle_t 	g_bitmap 		= TB_NULL;
static tb_size_t 	g_cap[] 		= {G2_STYLE_CAP_BUTT, G2_STYLE_CAP_SQUARE, G2_STYLE_CAP_ROUND};
static tb_size_t 	g_join[] 		= {G2_STYLE_JOIN_MITER, G2_STYLE_JOIN_BEVEL, G2_STYLE_JOIN_ROUND};
static tb_handle_t 	g_shader[7] 	= {TB_NULL};
static tb_handle_t 	g_mhader[7] 	= {TB_NULL};

// gl10
static GLuint 		g_gsurface 		= 0;
static GLfloat 		g_gvertices[8] 	= {-1, -1, 1, -1, -1, 1, 1, 1};
static GLfloat 		g_gtexcoords[8] = {0, 0, 1, 0, 0, 1, 1, 1};

/* ////////////////////////////////////////////////////////////////////////
 * demo 
 */
#include "rect.c"
//#include "path.c"
//#include "clip.c"
//#include "line.c"
//#include "arc.c"
//#include "point.c"
//#include "triangle.c"
//#include "ellipse.c"
//#include "circle.c"

/* ///////////////////////////////////////////////////////////////////////
 * implementation
 */

tb_bool_t g2_demo_gl_init()
{
#ifndef G2_CONFIG_CORE_GL10
	
	// disable
	glDisable(GL_DEPTH_TEST);
	glDisable(GL_BLEND);
	glDisable(GL_DITHER);
	
	// enable texture
	glEnable(GL_TEXTURE_2D);
	
	// Indicate that pixel rows are tightly packed (defaults to stride of 4 which is kind of only good for RGBA or FLOAT data types)
	glPixelStorei(GL_UNPACK_ALIGNMENT, 1);

	// init surface
	glActiveTexture(GL_TEXTURE0);
	glGenTextures(1, &g_gsurface);        
	tb_assert_and_check_return_val(g_gsurface, TB_FALSE);
	glBindTexture(GL_TEXTURE_2D, g_gsurface);
	
	// fill
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);    
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	//glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	//glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);	
	
	// scale
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
	
	// init vertices && texcoords
	glEnableClientState(GL_VERTEX_ARRAY); 
	glEnableClientState(GL_NORMAL_ARRAY); 
	glEnableClientState(GL_TEXTURE_COORD_ARRAY);
	
	glVertexPointer(2, GL_FLOAT, 0, g_gvertices);
	glTexCoordPointer(2, GL_FLOAT, 0, g_gtexcoords);

#endif
	return TB_TRUE;
}
tb_void_t g2_demo_gl_exit()
{
	// exit demo
	g2_demo_exit();

	// exit painter
	if (g_painter) g2_exit(g_painter);
	g_painter = TB_NULL;

	// exit context
	if (g_context) g2_context_exit(g_context);
	g_context = TB_NULL;

	// exit surface
#ifndef G2_CONFIG_CORE_GL10
	if (g_gsurface) glDeleteTextures(1, &g_gsurface);
	g_gsurface = 0;
#endif

}
tb_void_t g2_demo_gl_draw()
{	
	// check
	tb_check_return(g_painter);

	// clear
	g2_clear(g_painter, G2_COLOR_BLACK);

	// matrix
	if (g_bm)
	{
		g2_save(g_painter, G2_SAVE_MODE_MATRIX);
		g2_matrix_set(g_painter, &g_mx);
	}

	// start clock
	g_rt = tb_uclock();

	// render 
	if (g_mode & G2_STYLE_MODE_FILL)
	{
		g2_style_clear(g_style);
		g2_style_mode_set(g_style, G2_STYLE_MODE_FILL);
		g2_style_color_set(g_style, G2_COLOR_RED);
		g2_style_shader_set(g_style, g_bm? g_mhader[g_shaderi] : g_shader[g_shaderi]);
		if (g_shaderi == 6) 
		{
			g2_matrix_t mx;
			tb_size_t bw 	= g2_bitmap_width(g_bitmap);
			tb_size_t bh 	= g2_bitmap_height(g_bitmap);
			tb_size_t cw 	= g2_bitmap_width(g_surface);
			tb_size_t ch 	= g2_bitmap_height(g_surface);
			if (g_bm)
			{
				g2_matrix_init_translate(&mx, -g2_long_to_float(100), -g2_long_to_float(100));
				g2_matrix_scale(&mx, g2_long_to_float(200) / bw, g2_long_to_float(200) / bh);
				g2_shader_matrix_set(g_mhader[g_shaderi], &mx);
			}
			else
			{
				g2_matrix_init_translate(&mx, 0, 0);
				g2_matrix_scale(&mx, g2_long_to_float(cw) / bw, g2_long_to_float(ch) / bh);
				g2_shader_matrix_set(g_shader[g_shaderi], &mx);
			}
		}

		g2_demo_draw();
	}

	if (g_mode & G2_STYLE_MODE_STOK)
	{
		g2_style_clear(g_style);
		g2_style_mode_set(g_style, G2_STYLE_MODE_STOK);
		g2_style_color_set(g_style, G2_COLOR_BLUE);

		g2_style_width_set(g_style, g2_long_to_float(g_penw));
		g2_style_cap_set(g_style, g_cap[g_capi]);
		g2_style_join_set(g_style, g_join[g_joini]);

		g2_demo_draw();
	}

	// stop clock
	g_rt = tb_uclock() - g_rt;

	// load 
	if (g_bm) g2_load(g_painter);

	// draw
#ifndef G2_CONFIG_CORE_GL10
	if (g_surface)
	{
		tb_size_t width 	= g2_bitmap_width(g_surface);
		tb_size_t height 	= g2_bitmap_height(g_surface);
		tb_size_t pixfmt 	= g2_bitmap_pixfmt(g_surface);

		switch (pixfmt)
		{
		case G2_PIXFMT_RGB565:
			glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_SHORT_5_6_5, g2_bitmap_data(g_surface));
			break;
		case G2_PIXFMT_XRGB8888:
			glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, g2_bitmap_data(g_surface));
			break;
		case G2_PIXFMT_ARGB8888:
			glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, g2_bitmap_data(g_surface));
			break;
		default:
			break;
		}

		// draw rectangle
		glDrawArrays(GL_TRIANGLE_STRIP, 0, 4);
	}
#endif

	// render fps & rpt
	if (!g_bt) g_bt = tb_uclock();
	if (!(++g_fp & 0x15))
	{
		g_fps = (1000000 * g_fp) / ((tb_uclock() - g_bt) + 1);
		g_fp = 0;
		g_bt = 0;
	}
	tb_print("fps: %lld, rpt: %lld us", g_fps, g_rt);
}
tb_void_t g2_demo_gl_size(tb_size_t width, tb_size_t height)
{
#ifndef G2_CONFIG_CORE_GL10
	// init viewport
	glViewport(0, 0, width, height);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glOrthof(-1.0f, 1.0f, -1.0f, 1.0f, -1.0f, 1.0f);
	glMatrixMode(GL_MODELVIEW);
	glScalef(1.0f, -1.0f, 1.0f);
#endif

	if (!g_painter)
	{
		// init position
		g_x0 		= width >> 1;
		g_y0 		= height >> 1;
		g_dx 		= width >> 2;
		g_dy 		= height >> 2;
		g_x 		= g_dx;
		g_y 		= g_dy;

		// init matrix
		g2_matrix_init_translate(&g_mx, g2_long_to_float(g_x0), g2_long_to_float(g_y0));	

		// init gradient
		g2_color_t 		color[3] = {G2_COLOR_RED, G2_COLOR_GREEN, G2_COLOR_BLUE};
		g2_gradient_t 	grad = {color, TB_NULL, 3};

		// init bitmap
		g_bitmap = g2_bitmap_init_url(G2_DEMO_PIXFMT, "/mnt/sdcard/logo.bmp");

		// init shader
		g_shader[1]	= g2_shader_init2i_linear(g_x0 - 100, 0, g_x0 + 100, 0, &grad, G2_SHADER_MODE_CLAMP);
		g_mhader[1]	= g2_shader_init2i_linear(-50, 0, 50, 0, &grad, G2_SHADER_MODE_CLAMP);

		g_shader[2]	= g2_shader_init2i_radial(g_x0, g_y0, 100, &grad, G2_SHADER_MODE_CLAMP);
		g_mhader[2]	= g2_shader_init2i_radial(0, 0, 50, &grad, G2_SHADER_MODE_CLAMP);

		g_shader[3]	= g2_shader_init2i_radial2(g_x0, g_y0, 100, g_x0, g_y0, 200, &grad, G2_SHADER_MODE_CLAMP);
		g_mhader[3]	= g2_shader_init2i_radial2(0, 0, 50, 0, 0, 100, &grad, G2_SHADER_MODE_CLAMP);

		g_shader[4]	= g2_shader_init2i_conical(0, 0, 100, width, height, 200, &grad, G2_SHADER_MODE_CLAMP);
		g_mhader[4]	= g2_shader_init2i_conical(-50, -50, 50, 50, 50, 100, &grad, G2_SHADER_MODE_CLAMP);

		g_shader[5]	= g2_shader_init2i_sweep(g_x0, g_y0, &grad);
		g_mhader[5]	= g2_shader_init2i_sweep(0, 0, &grad);

		if (g_bitmap)
		{
			g_shader[6]	= g2_shader_init_bitmap(g_bitmap, G2_SHADER_MODE_CLAMP, G2_SHADER_MODE_CLAMP);
			g_mhader[6]	= g2_shader_init_bitmap(g_bitmap, G2_SHADER_MODE_CLAMP, G2_SHADER_MODE_CLAMP);
		}

		// init context
#ifdef G2_CONFIG_CORE_GL10
		g_context = g2_context_init_gl10(G2_DEMO_PIXFMT, width, height);
		tb_assert_and_check_return(g_context);
#else
		g_context = g2_context_init_skia(G2_DEMO_PIXFMT, TB_NULL, width, height, 0);
		tb_assert_and_check_return(g_context);
#endif

		// init surface
		g_surface = g2_context_surface(g_context);
		tb_assert_and_check_return(g_surface);

		// init painter
		g_painter = g2_init(g_context);
		tb_assert_and_check_return(g_painter);

		// init style
		g_style = g2_style(g_painter);
		tb_assert_and_check_return(g_style);

		// init demo 
		if (!g2_demo_init()) return ;
	}
	else
	{
		// update position
		g_x0 		= width >> 1;
		g_y0 		= height >> 1;
		g_dx 		= width >> 2;
		g_dy 		= height >> 2;
		g_x 		= g_dx;
		g_y 		= g_dy;

		// update matrix
		g2_matrix_init_translate(&g_mx, g2_long_to_float(g_x0), g2_long_to_float(g_y0));	

		// resize context
		g2_context_set(g_painter, g2_context_resize(g_context, width, height));

		// resize
		g2_demo_size(width, height);
	}
}
tb_void_t g2_demo_gl_move(tb_long_t x, tb_long_t y)
{
	g_x = x;
	g_y = y;

	g_dx = x > g_x0? (x - g_x0) << 1 : (g_x0 - x) << 1;
	g_dy = y > g_y0? (y - g_y0) << 1 : (g_y0 - y) << 1;

	g2_float_t x0 = g2_long_to_float(g_x0);
	g2_float_t y0 = g2_long_to_float(g_y0);
	g2_float_t dx = g2_long_to_float(g_dx);
	g2_float_t dy = g2_long_to_float(g_dy);
	g2_float_t dw = g2_long_to_float(g2_bitmap_width(g_surface));
	g2_float_t dh = g2_long_to_float(g2_bitmap_height(g_surface));

	g2_float_t an = 0;
	if (y == g_y0) an = 0;
	else if (x == g_x0) an = g2_long_to_float(90);
	else an = g2_div(g2_atan(g2_div(dy, dx)) * 180, G2_PI);
	if (y < g_y0 && x < g_x0) an = g2_long_to_float(180) - an;
	if (y > g_y0 && x < g_x0) an += g2_long_to_float(180);
	if (y > g_y0 && x > g_x0) an = g2_long_to_float(360) - an;
	g_an = -an;

	dx = g2_lsh(dx, 2);
	dy = g2_lsh(dy, 2);

	g2_matrix_init_translate(&g_mx, x0, y0);
	g2_matrix_scale(&g_mx, g2_div(dx, dw), g2_div(dy, dh));
	g2_matrix_rotate(&g_mx, g_an);

	g2_demo_move(x, y);
}
tb_size_t g2_demo_gl_tfps()
{
	return (tb_size_t)g_fps;
}
tb_size_t g2_demo_gl_trpt()
{
	return (tb_size_t)g_rt;
}
tb_void_t g2_demo_gl_tkey(tb_size_t key)
{
	switch (key)
	{
	case 'q':
		{
			g2_quality_set((g2_quality() + 1) % 3);
		}
		break;
	case 'w':
		{
			if (g_penw > 1000) g_penw = 1000;
			else g_penw++;
		}
		break;
	case 'm':
		{
			g_bm = g_bm? TB_FALSE : TB_TRUE;
		}
		break;
	case 'f':
		{
			g_shaderi = (g_shaderi + 1) % (g_bitmap? 7 : 6);
		}
		break;	
	case 's':
		{
			g_capi = (g_capi + 1) % 3;
			g_joini = (g_joini + 1) % 3;
		}
		break;
	default:
		break;
	}

	g2_demo_tkey(key);
}

