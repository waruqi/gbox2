#ifndef G2_DEMO_H
#define G2_DEMO_H

/* ////////////////////////////////////////////////////////////////////////
 * includes
 */
#include "gbox2.h"
#ifdef TB_CONFIG_OS_MAC
# 	include <OpenGL/gl.h>
# 	include <OpenGL/glu.h>
# 	include <GLUT/glut.h>
#else
# 	include <GL/glut.h>
#endif

/* ////////////////////////////////////////////////////////////////////////
 * macros
 */
#define G2_DEMO_WIDTH 			(640)
#define G2_DEMO_HEIGHT 			(480)

/* ////////////////////////////////////////////////////////////////////////
 * globals
 */

// surface
static tb_handle_t 	g_surface 	= TB_NULL;

// painter
static tb_handle_t 	g_painter 	= TB_NULL;

// style
static tb_handle_t 	g_style 	= TB_NULL;

// width & height
static tb_size_t 	g_width 	= G2_DEMO_WIDTH;
static tb_size_t 	g_height 	= G2_DEMO_HEIGHT;

// pixfmt
static tb_size_t 	g_pixfmt 	= G2_PIXFMT_XRGB8888;

// clock
static tb_hong_t 	g_bt 		= 0;
static tb_hong_t 	g_fp 		= 0;
static tb_hong_t 	g_rt 		= 0;
static tb_hong_t 	g_fps 		= 0;

// position
static tb_long_t 	g_x0 		= G2_DEMO_WIDTH >> 1;
static tb_long_t 	g_y0 		= G2_DEMO_HEIGHT >> 1;
static tb_long_t 	g_dx 		= 0;
static tb_long_t 	g_dy 		= 0;
static tb_long_t 	g_x 		= 0;
static tb_long_t 	g_y 		= 0;
static tb_float_t 	g_an 		= 0.;
static tb_bool_t 	g_bm 		= TB_FALSE;

// style
static tb_size_t 	g_mode 		= G2_STYLE_MODE_NONE;
static tb_size_t 	g_penw 		= 1;
static tb_size_t 	g_capi 		= 0;
static tb_size_t 	g_joini 	= 0;
static tb_size_t 	g_cap[] 	= {G2_STYLE_CAP_BUTT, G2_STYLE_CAP_SQUARE, G2_STYLE_CAP_ROUND};
static tb_size_t 	g_join[] 	= {G2_STYLE_JOIN_MITER, G2_STYLE_JOIN_BEVEL, G2_STYLE_JOIN_ROUND};

/* ////////////////////////////////////////////////////////////////////////
 * callbacks
 */
static tb_bool_t g2_demo_init(tb_int_t argc, tb_char_t** argv);
static tb_void_t g2_demo_exit();
static tb_void_t g2_demo_size(tb_int_t w, tb_int_t h);
static tb_void_t g2_demo_render();
static tb_void_t g2_demo_move(tb_int_t x, tb_int_t y);
static tb_void_t g2_demo_drag(tb_int_t x, tb_int_t y);
static tb_void_t g2_demo_wheeldown(tb_int_t x, tb_int_t y);
static tb_void_t g2_demo_wheelup(tb_int_t x, tb_int_t y);
static tb_void_t g2_demo_lclickdown(tb_int_t x, tb_int_t y);
static tb_void_t g2_demo_lclickup(tb_int_t x, tb_int_t y);
static tb_void_t g2_demo_rclickdown(tb_int_t x, tb_int_t y);
static tb_void_t g2_demo_rclickup(tb_int_t x, tb_int_t y);
static tb_void_t g2_demo_key(tb_int_t key);

/* ////////////////////////////////////////////////////////////////////////
 * gl
 */
static tb_void_t g2_demo_gl_keyboard(tb_byte_t key, tb_int_t x, tb_int_t y)
{
	switch (key)
	{
	case 'a':
		{
			tb_size_t flag = g2_style_flag(g_style);
			g2_style_flag_set(g_style, flag & G2_STYLE_FLAG_ANTI_ALIAS? flag & ~G2_STYLE_FLAG_ANTI_ALIAS : flag | G2_STYLE_FLAG_ANTI_ALIAS);
		}
		break;
	case 'w':
		{
			if (g_penw > 1000) g_penw = 1000;
			else g_penw++;
			g2_style_width_set(g_style, g2_long_to_float(g_penw));
		}
		break;
	case 'm':
		{
			g_bm = g_bm? TB_FALSE : TB_TRUE;
		}
		break;
	default:
		break;
	}

	g2_demo_key(key);
}
static tb_void_t g2_demo_gl_special(tb_int_t key, tb_int_t x, tb_int_t y)
{
	g2_demo_gl_keyboard(key, x, y);
}
static tb_void_t g2_demo_gl_printf(tb_char_t const* fmt, ...)
{
	// format text
	tb_char_t text[4096] = {0};
	tb_size_t size = 0;
	tb_va_format(text, 4096, fmt, &size);

	// the text color
	GLfloat c[4] = {1., 1., 0., 1.};
	glColor4fv(c);

	// init position
	glMatrixMode(GL_MODELVIEW);
	glPushMatrix();
	glLoadIdentity();
	glTranslatef(20., g_height - 20., 0);
	glScalef(0.12, 0.12, 0.12);

	// render it
	tb_int_t i = 0;
	for (i = 0; i < size; ++i) 
		glutStrokeCharacter(GLUT_STROKE_ROMAN, text[i]);

	glPopMatrix();
}
static tb_void_t g2_demo_gl_display()
{
	// check
	tb_check_return(g_painter);

	// clear
	g2_clear(g_painter, G2_COLOR_BLACK);

	// matrix
	if (g_bm)
	{
		g2_float_t x0 = g2_long_to_float(g_x0);
		g2_float_t y0 = g2_long_to_float(g_y0);
		g2_float_t dx = g2_long_to_float(g_dx);
		g2_float_t dy = g2_long_to_float(g_dy);
		g2_float_t dw = g2_long_to_float(g_width);
		g2_float_t dh = g2_long_to_float(g_height);

		dx = g2_lsh(dx, 2);
		dy = g2_lsh(dy, 2);

		// save
		g2_save(g_painter, G2_SAVE_MODE_MATRIX);

#if 0
		g2_translate(g_painter, x0, y0);
		g2_scale(g_painter, g2_div(dx, dw), g2_div(dy, dh));
		g2_rotate(g_painter, g_an);
#else
		g2_matrix_t mx;
		g2_matrix_init_translate(&mx, x0, y0);
		g2_matrix_scale(&mx, g2_div(dx, dw), g2_div(dy, dh));
		g2_matrix_rotate(&mx, g_an);
		g2_matrix_set(g_painter, &mx);
#endif
	}

	// start clock
	g_rt = tb_uclock();

	// render 
	if (g_mode & G2_STYLE_MODE_FILL)
	{
		g2_style_mode_set(g_style, G2_STYLE_MODE_FILL);
		g2_style_color_set(g_style, G2_COLOR_RED);

		g2_demo_render();
	}

	if (g_mode & G2_STYLE_MODE_STROKE)
	{
		g2_style_mode_set(g_style, G2_STYLE_MODE_STROKE);
		g2_style_color_set(g_style, G2_COLOR_BLUE);

		g2_demo_render();
	}

	// stop clock
	g_rt = tb_uclock() - g_rt;

	// load 
	if (g_bm) g2_load(g_painter);

	// draw
	if (g_surface)
	{
		glPixelZoom(1.0, -1.0);
		glRasterPos2i(0, g_height);
		switch (g_pixfmt)
		{
		case G2_PIXFMT_RGB565:
			glDrawPixels(g_width, g_height, GL_RGB, GL_UNSIGNED_SHORT_5_6_5, g2_bitmap_data(g_surface));
			break;
		case G2_PIXFMT_XRGB8888:
			glDrawPixels(g_width, g_height, GL_BGRA, GL_UNSIGNED_BYTE, g2_bitmap_data(g_surface));
			break;
		default:
			break;
		}
	}

	// render fps & rpt
	if (!g_bt) g_bt = tb_uclock();
	if (!(g_fp++ & 0x15)) g_fps = (1000000 * g_fp) / ((tb_uclock() - g_bt) + 1);
	g2_demo_gl_printf("fps: %lld, rpt: %lld us", g_fps, g_rt);

	// flush
	glutSwapBuffers();
}
static tb_void_t g2_demo_gl_reshape(tb_int_t w, tb_int_t h)
{
	// init width & height
	g_width = w;
	g_height = h;

	// init position
	g_x0 	= g_width >> 1;
	g_y0 	= g_height >> 1;
	g_dx 	= g_width >> 2;
	g_dy 	= g_height >> 2;
	g_x 	= g_dx;
	g_y 	= g_dy;

	// init surface
#ifndef G2_CONFIG_CORE_GL
	if (g_surface) g2_bitmap_exit(g_surface);
	g_surface = g2_bitmap_init(g_pixfmt, g_width, g_height);
	tb_assert_and_check_return_val(g_surface, 0);
	g2_bitmap_make(g_surface);
#endif

	// init painter
	if (g_painter) g2_exit(g_painter);
	g_painter = g2_init(g_surface);
	tb_assert_and_check_return_val(g_painter, 0);

	// init style
	g_style = g2_style(g_painter);
	tb_assert_and_check_return_val(g_style, 0);

	g2_style_width_set(g_style, g2_long_to_float(g_penw));
	g2_style_cap_set(g_style, g_cap[g_capi]);
	g2_style_join_set(g_style, g_join[g_joini]);

	// init viewport
	glViewport(0, 0, w, h);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluOrtho2D(0.0, (GLfloat)w, 0.0, (GLfloat)h);
	glMatrixMode(GL_MODELVIEW);

	// resize
	g2_demo_size(w, h);
}
static tb_void_t g2_demo_gl_click(tb_int_t button, tb_int_t state, tb_int_t x, tb_int_t y)
{
	if (button == 0) // left
	{
		if (state == 0)
		{
			g2_demo_lclickdown(x, y);
		}
		else if (state == 1)
		{
			g2_demo_lclickup(x, y);
		}
	}
	else if (button == 2) // right
	{	
		if (state == 0)
		{
			g2_demo_rclickdown(x, y);
		}
		else if (state == 1)
		{
			g_capi = (g_capi + 1) % 3;
			g_joini = (g_joini + 1) % 3;
			g2_style_cap_set(g_style, g_cap[g_capi]);
			g2_style_join_set(g_style, g_join[g_joini]);

			g2_demo_rclickup(x, y);
		}
	}
	else if (button == 3) // wheelup
	{	
		if (state == 0) // down
		{
			g2_demo_wheelup(x, y);
		}
	}
	else if (button == 4) // wheeldown
	{	
		if (state == 0) // down
		{
			g2_demo_wheeldown(x, y);
		}
	}
}

static tb_void_t g2_demo_gl_move(tb_int_t x, tb_int_t y)
{
	g_x = x;
	g_y = y;

	g_dx = x > g_x0? (x - g_x0) << 1 : (g_x0 - x) << 1;
	g_dy = y > g_y0? (y - g_y0) << 1 : (g_y0 - y) << 1;

	g2_float_t dx = g2_long_to_float(g_dx);
	g2_float_t dy = g2_long_to_float(g_dy);

	g2_float_t an = 0;
	if (y == g_y0) an = 0;
	else if (x == g_x0) an = g2_long_to_float(90);
	else an = g2_div(g2_imul(g2_atan(g2_div(dy, dx)), 180), G2_PI);
	if (y < g_y0 && x < g_x0) an = g2_long_to_float(180) - an;
	if (y > g_y0 && x < g_x0) an += g2_long_to_float(180);
	if (y > g_y0 && x > g_x0) an = g2_long_to_float(360) - an;
	g_an = -an;

	g2_demo_move(x, y);
}

/* ////////////////////////////////////////////////////////////////////////
 * main
 */
tb_int_t main(tb_int_t argc, tb_char_t** argv)
{
	// init tbox
	if (!tb_init(malloc(50 * 1024 * 1024), 50 * 1024 * 1024)) return 0;

	// init exit
	atexit(g2_demo_exit);

	// init gl
	glutInit (&argc, argv);
	glutInitDisplayMode (GLUT_RGBA | GLUT_DOUBLE | GLUT_ALPHA | GLUT_STENCIL | GLUT_MULTISAMPLE);
	//glutInitDisplayMode (GLUT_RGBA | GLUT_DOUBLE | GLUT_STENCIL);
	glutInitWindowPosition (0, 0);
	glutInitWindowSize (g_width, g_height);
	glutCreateWindow ("gbox2");
	glutDisplayFunc(g2_demo_gl_display);
	glutIdleFunc(g2_demo_gl_display);
	glutReshapeFunc(g2_demo_gl_reshape);
	glutMouseFunc(g2_demo_gl_click);
	glutPassiveMotionFunc(g2_demo_gl_move);
	glutMotionFunc(g2_demo_drag);
	glutKeyboardFunc(g2_demo_gl_keyboard);
	glutSpecialFunc(g2_demo_gl_special);

	// init demo 
	if (!g2_demo_init(argc, argv)) return 0;

	// loop 
	glutMainLoop();

	// exit demo
	g2_demo_exit();

	// free painter
	if (g_painter) g2_exit(g_painter);

	// free surface
	if (g_surface) g2_bitmap_exit(g_surface);

	// exit tbox
	tb_exit();
	return 0;
}










#endif

