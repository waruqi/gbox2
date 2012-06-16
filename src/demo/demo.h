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
 * globals
 */

// surface
static tb_handle_t 	g_surface 	= TB_NULL;

// painter
static tb_handle_t 	g_painter 	= TB_NULL;

// style
static tb_handle_t 	g_style 	= TB_NULL;

// width & height
static tb_size_t 	g_width 	= 640;
static tb_size_t 	g_height 	= 480;

// pixfmt
static tb_size_t 	g_pixfmt 	= G2_PIXFMT_XRGB8888;

// clock
static tb_hong_t 	g_bt 		= 0; 
static tb_hong_t 	g_tb 		= 0;
static tb_hong_t 	g_te 		= 0;
static tb_hong_t 	g_rt 		= 0;
static tb_hong_t 	g_ft 		= 0;
static tb_hong_t 	g_fp 		= 0;

// position
static tb_long_t 	g_x0 		= 0;
static tb_long_t 	g_y0 		= 0;
static tb_long_t 	g_dx 		= 0;
static tb_long_t 	g_dy 		= 0;
static tb_long_t 	g_x 		= 0;
static tb_long_t 	g_y 		= 0;
static tb_float_t 	g_an 		= 0.;

// style
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
	g2_demo_key(key);
}
static tb_void_t g2_demo_gl_special(tb_int_t key, tb_int_t x, tb_int_t y)
{
	g2_demo_key(key);
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
	// clear
//	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	g2_clear(g_painter, G2_COLOR_BLACK);
	
	// start clock
	g_tb = tb_uclock();

	// render 
	g2_demo_render();

	// stop clock
	g_te = tb_uclock();

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

	// render fps & rps
	g_fp++;
	g_rt += g_te - g_tb;
	g_ft = g_te - g_bt;
	if (!g_bt) g_bt = g_tb;
	tb_long_t fps = (tb_long_t)((1000000 * g_fp) / (g_ft + 1));
	tb_long_t rps = (tb_long_t)((1000000 * g_fp) / (g_rt + 1));
	g2_demo_gl_printf("fps: %ld, rps: %ld, rpt: %ld us", fps, rps, (tb_long_t)(g_te - g_tb));

	// flush
	glutSwapBuffers();
}
static tb_void_t g2_demo_gl_reshape(tb_int_t w, tb_int_t h)
{
	g_width = w;
	g_height = h;
	glViewport(0, 0, w, h);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluOrtho2D(0.0, (GLfloat)w, 0.0, (GLfloat)h);
	glMatrixMode(GL_MODELVIEW);
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
	glutPassiveMotionFunc(g2_demo_move);
	glutMotionFunc(g2_demo_drag);
	glutKeyboardFunc(g2_demo_gl_keyboard);
	glutSpecialFunc(g2_demo_gl_special);

	// init surface
#ifndef G2_CONFIG_CORE_GL
	g_surface = g2_bitmap_init(g_pixfmt, g_width, g_height);
	tb_assert_and_check_return_val(g_surface, 0);
	g2_bitmap_make(g_surface);
#endif

	// init painter
	g_painter = g2_init(g_surface);
	tb_assert_and_check_return_val(g_painter, 0);

	// init style
	g_style = g2_style(g_painter);
	tb_assert_and_check_return_val(g_style, 0);

	// init position
	g_x0 	= g_width >> 1;
	g_y0 	= g_height >> 1;
	g_dx 	= g_width >> 2;
	g_dy 	= g_height >> 2;
	g_x 	= g_width >> 1;
	g_y 	= g_height >> 1;

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

