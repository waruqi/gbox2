#ifndef G2_DEMO_H
#define G2_DEMO_H

/* ////////////////////////////////////////////////////////////////////////
 * includes
 */
#include "gbox2.h"
#include <stdlib.h>
#if defined(TB_CONFIG_OS_MAC)
# 	include <OpenGL/gl.h>
# 	include <OpenGL/glu.h>
# 	include <GLUT/glut.h>
#elif defined(TB_CONFIG_OS_ANDROID)
# 	include <GLES/gl.h>
# 	include <GLES/glext.h>
#else
# 	define GL_GLEXT_PROTOTYPES
# 	include <GL/glut.h>
# 	include <GL/glext.h>
#endif


/* ////////////////////////////////////////////////////////////////////////
 * macros
 */

// width & height
#define G2_DEMO_WIDTH 			(640)
#define G2_DEMO_HEIGHT 			(480)

// pixfmt
#if defined(G2_CONFIG_CORE_SKIA)
//# 	define G2_DEMO_PIXFMT 			(G2_PIXFMT_RGB565 | G2_PIXFMT_NENDIAN)
# 	define G2_DEMO_PIXFMT 			(G2_PIXFMT_ARGB8888 | G2_PIXFMT_NENDIAN)
#elif defined(G2_CONFIG_CORE_GL) || defined(G2_CONFIG_CORE_GLES)
# 	define G2_DEMO_PIXFMT 			(G2_PIXFMT_RGB565 | G2_PIXFMT_LENDIAN)
//# 	define G2_DEMO_PIXFMT 			(G2_PIXFMT_RGB888 | G2_PIXFMT_BENDIAN)
//# 	define G2_DEMO_PIXFMT 			(G2_PIXFMT_RGBA5551 | G2_PIXFMT_LENDIAN)
//# 	define G2_DEMO_PIXFMT 			(G2_PIXFMT_RGBA4444 | G2_PIXFMT_LENDIAN)
//# 	define G2_DEMO_PIXFMT 			(G2_PIXFMT_RGBA8888 | G2_PIXFMT_BENDIAN)
#else
//# 	define G2_DEMO_PIXFMT 			(G2_PIXFMT_RGB565 | G2_PIXFMT_NENDIAN)
//# 	define G2_DEMO_PIXFMT 			(G2_PIXFMT_ARGB1555 | G2_PIXFMT_NENDIAN)
//# 	define G2_DEMO_PIXFMT 			(G2_PIXFMT_ARGB4444 | G2_PIXFMT_NENDIAN)
# 	define G2_DEMO_PIXFMT 			(G2_PIXFMT_ARGB8888 | G2_PIXFMT_NENDIAN)
//# 	define G2_DEMO_PIXFMT 			(G2_PIXFMT_RGB565 | G2_PIXFMT_NENDIAN)
//# 	define G2_DEMO_PIXFMT 			(G2_PIXFMT_RGBA5551 | G2_PIXFMT_NENDIAN)
//# 	define G2_DEMO_PIXFMT 			(G2_PIXFMT_RGBA4444 | G2_PIXFMT_NENDIAN)
//# 	define G2_DEMO_PIXFMT 			(G2_PIXFMT_RGBA8888 | G2_PIXFMT_NENDIAN)
#endif

/* ////////////////////////////////////////////////////////////////////////
 * globals
 */

// context
static tb_handle_t 	g_context 	= TB_NULL;

// surface
static tb_handle_t 	g_surface 	= TB_NULL;

// painter
static tb_handle_t 	g_painter 	= TB_NULL;

// clock
static tb_hong_t 	g_bt 		= 0;
static tb_hong_t 	g_fp 		= 0;
static tb_hong_t 	g_rt 		= 0;
static tb_hong_t 	g_fps 		= 0;
static tb_bool_t 	g_pt 		= TB_FALSE;

// position
static tb_long_t 	g_x0 		= G2_DEMO_WIDTH >> 1;
static tb_long_t 	g_y0 		= G2_DEMO_HEIGHT >> 1;
static tb_long_t 	g_dx 		= 0;
static tb_long_t 	g_dy 		= 0;
static tb_long_t 	g_x 		= 0;
static tb_long_t 	g_y 		= 0;
static tb_float_t 	g_an 		= 0.;
static tb_bool_t 	g_bm 		= TB_FALSE;
static g2_matrix_t 	g_mx;

/* ////////////////////////////////////////////////////////////////////////
 * callbacks
 */
static tb_bool_t g2_demo_init(tb_int_t argc, tb_char_t const** argv);
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
	case 'q':
		{
			g2_quality_set((g2_quality() + 1) % 3);
		}
		break;
	case 'm':
		{
			g_bm = g_bm? TB_FALSE : TB_TRUE;
		}
		break;
	case 't':
		{
			g_pt = g_pt? TB_FALSE : TB_TRUE;
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
static tb_void_t g2_demo_gl_display()
{
	// check
	tb_check_return(g_painter);

	// clear
	g2_draw_clear(g_painter, G2_COLOR_BLACK);

	// matrix
	if (g_bm) g2_matrix_copy(g2_matrix_save(g_painter), &g_mx);

	// start clock
	g_rt = tb_uclock();

	// render
	g2_demo_render();

	// stop clock
	g_rt = tb_uclock() - g_rt;

	// load 
	if (g_bm) g2_matrix_load(g_painter);

	// draw
#if defined(G2_CONFIG_CORE_SKIA) || defined(G2_CONFIG_CORE_SOFT)
	if (g_surface)
	{
		tb_size_t width 	= g2_bitmap_width(g_surface);
		tb_size_t height 	= g2_bitmap_height(g_surface);
		tb_size_t pixfmt 	= g2_bitmap_pixfmt(g_surface);

		glPixelZoom(1.0, -1.0);
		glRasterPos2i(0, height - 1);
		switch (G2_PIXFMT(pixfmt))
		{
		case G2_PIXFMT_RGB565:
			glDrawPixels(width, height, GL_RGB, GL_UNSIGNED_SHORT_5_6_5, g2_bitmap_data(g_surface));
			break;
		case G2_PIXFMT_XRGB8888:
			glDrawPixels(width, height, GL_BGRA, GL_UNSIGNED_BYTE, g2_bitmap_data(g_surface));
			break;
		case G2_PIXFMT_ARGB8888:
			glDrawPixels(width, height, GL_BGRA, GL_UNSIGNED_BYTE, g2_bitmap_data(g_surface));
			break;
		default:
			break;
		}
	}
#endif

	// render fps & rpt
	g_fp++;
	if (!g_bt) g_bt = tb_uclock();
	if ((tb_uclock() - g_bt) > 1000000)
	{
		g_fps = (1000000 * g_fp) / (tb_uclock() - g_bt);
		g_fp = 0;
		g_bt = 0;

		if (g_pt) tb_print("fps: %lld, rpt: %lld us", g_fps, g_rt);
	}

	// flush
	glutSwapBuffers();
}
static tb_void_t g2_demo_gl_reshape(tb_int_t w, tb_int_t h)
{
#if defined(G2_CONFIG_CORE_SKIA) || defined(G2_CONFIG_CORE_SOFT)
	// init viewport
	glViewport(0, 0, w, h);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glOrtho(0.0, (GLfloat)w, 0.0, (GLfloat)h, -1.0f, 1.0f);
	glMatrixMode(GL_MODELVIEW);
#endif

	// update position
	g_x0 		= w >> 1;
	g_y0 		= h >> 1;
	g_dx 		= w >> 2;
	g_dy 		= h >> 2;
	g_x 		= g_dx;
	g_y 		= g_dy;

	// update matrix
	g2_matrix_init_translate(&g_mx, g2_long_to_float(g_x0), g2_long_to_float(g_y0));	

	// resize context
	g2_context_resize(g2_context(g_painter), w, h);

	// resize
	g2_demo_size(w, h);
}
static tb_void_t g2_demo_gl_click(tb_int_t button, tb_int_t state, tb_int_t x, tb_int_t y)
{
	if (button == 0) // left
	{
		if (state == 0)
			g2_demo_lclickdown(x, y);
		else if (state == 1)
			g2_demo_lclickup(x, y);
	}
	else if (button == 2) // right
	{	
		if (state == 0)
			g2_demo_rclickdown(x, y);
		else if (state == 1)
			g2_demo_rclickup(x, y);
	}
	else if (button == 3) // wheelup
	{	
		if (state == 0) // down
			g2_demo_wheelup(x, y);
	}
	else if (button == 4) // wheeldown
	{	
		if (state == 0) // down
			g2_demo_wheeldown(x, y);
	}
}

static tb_void_t g2_demo_gl_move(tb_int_t x, tb_int_t y)
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
static tb_bool_t g2_demo_gl_init(tb_int_t argc, tb_char_t** argv)
{
	// init gl
	glutInit (&argc, argv);
	glutInitDisplayMode (GLUT_RGBA | GLUT_DOUBLE | GLUT_STENCIL | GLUT_MULTISAMPLE);
	glutInitWindowPosition (0, 0);
	glutInitWindowSize (G2_DEMO_WIDTH, G2_DEMO_HEIGHT);
	glutCreateWindow ("gbox2");
	glutDisplayFunc(g2_demo_gl_display);
	glutIdleFunc(g2_demo_gl_display);
	glutReshapeFunc(g2_demo_gl_reshape);
	glutMouseFunc(g2_demo_gl_click);
	glutPassiveMotionFunc(g2_demo_gl_move);
	glutMotionFunc(g2_demo_drag);
	glutKeyboardFunc(g2_demo_gl_keyboard);
	glutSpecialFunc(g2_demo_gl_special);

	// ok
	return TB_TRUE;
}

/* ////////////////////////////////////////////////////////////////////////
 * gbox2
 */
#if defined(G2_CONFIG_CORE_GL) || defined(G2_CONFIG_CORE_GLES)
static tb_void_t g2_demo_gbox2_init_gl()
{
	// load interfaces for common
//	G2_GL_INTERFACE_LOAD_S(glActiveTexture);
	G2_GL_INTERFACE_LOAD_S(glAlphaFunc);
	G2_GL_INTERFACE_LOAD_S(glBindTexture);
	G2_GL_INTERFACE_LOAD_S(glBlendFunc);
	G2_GL_INTERFACE_LOAD_S(glClear);
	G2_GL_INTERFACE_LOAD_S(glClearColor);
	G2_GL_INTERFACE_LOAD_S(glClearStencil);
	G2_GL_INTERFACE_LOAD_S(glColorMask);
	G2_GL_INTERFACE_LOAD_S(glDeleteTextures);
	G2_GL_INTERFACE_LOAD_S(glDisable);
	G2_GL_INTERFACE_LOAD_S(glDrawArrays);
	G2_GL_INTERFACE_LOAD_S(glEnable);
	G2_GL_INTERFACE_LOAD_S(glGenTextures);
	G2_GL_INTERFACE_LOAD_S(glGetString);
	G2_GL_INTERFACE_LOAD_S(glIsTexture);
	G2_GL_INTERFACE_LOAD_S(glPixelStorei);
	G2_GL_INTERFACE_LOAD_S(glStencilFunc);
	G2_GL_INTERFACE_LOAD_S(glStencilMask);
	G2_GL_INTERFACE_LOAD_S(glStencilOp);
	G2_GL_INTERFACE_LOAD_S(glTexImage2D);
	G2_GL_INTERFACE_LOAD_S(glTexParameterf);
	G2_GL_INTERFACE_LOAD_S(glTexParameteri);
	G2_GL_INTERFACE_LOAD_S(glViewport);

	// load interfaces for gl 1.x
	G2_GL_INTERFACE_LOAD_S(glColor4f);
	G2_GL_INTERFACE_LOAD_S(glColorPointer);
	G2_GL_INTERFACE_LOAD_S(glDisableClientState);
	G2_GL_INTERFACE_LOAD_S(glEnableClientState);
	G2_GL_INTERFACE_LOAD_S(glLoadIdentity);
	G2_GL_INTERFACE_LOAD_S(glLoadMatrixf);
	G2_GL_INTERFACE_LOAD_S(glMatrixMode);
	G2_GL_INTERFACE_LOAD_S(glMultMatrixf);
# 	ifdef G2_CONFIG_CORE_GLES
	G2_GL_INTERFACE_LOAD_S(glOrthof);
# 	else
	G2_GL_INTERFACE_LOAD_S(glOrtho);
# 	endif
	G2_GL_INTERFACE_LOAD_S(glPopMatrix);
	G2_GL_INTERFACE_LOAD_S(glPushMatrix);
	G2_GL_INTERFACE_LOAD_S(glRotatef);
	G2_GL_INTERFACE_LOAD_S(glScalef);
	G2_GL_INTERFACE_LOAD_S(glTexCoordPointer);
	G2_GL_INTERFACE_LOAD_S(glTexEnvi);
	G2_GL_INTERFACE_LOAD_S(glTranslatef);
	G2_GL_INTERFACE_LOAD_S(glVertexPointer);

	// load interfaces for gl >= 2.0
#if !G2_CONFIG_GL_VERSION || G2_CONFIG_GL_VERSION >= 0x20
	G2_GL_INTERFACE_LOAD_S(glAttachShader);
	G2_GL_INTERFACE_LOAD_S(glCompileShader);
	G2_GL_INTERFACE_LOAD_S(glCreateProgram);
	G2_GL_INTERFACE_LOAD_S(glCreateShader);
	G2_GL_INTERFACE_LOAD_S(glDeleteProgram);
	G2_GL_INTERFACE_LOAD_S(glDeleteShader);
	G2_GL_INTERFACE_LOAD_S(glDisableVertexAttribArray);
	G2_GL_INTERFACE_LOAD_S(glEnableVertexAttribArray);
	G2_GL_INTERFACE_LOAD_S(glGetAttribLocation);
	G2_GL_INTERFACE_LOAD_S(glGetProgramiv);
	G2_GL_INTERFACE_LOAD_S(glGetProgramInfoLog);
	G2_GL_INTERFACE_LOAD_S(glGetShaderiv);
	G2_GL_INTERFACE_LOAD_S(glGetShaderInfoLog);
	G2_GL_INTERFACE_LOAD_S(glGetUniformLocation);
	G2_GL_INTERFACE_LOAD_S(glLinkProgram);
	G2_GL_INTERFACE_LOAD_S(glShaderSource);
	G2_GL_INTERFACE_LOAD_S(glUniform1i);
	G2_GL_INTERFACE_LOAD_S(glUniformMatrix4fv);
	G2_GL_INTERFACE_LOAD_S(glUseProgram);
	G2_GL_INTERFACE_LOAD_S(glVertexAttrib4f);
	G2_GL_INTERFACE_LOAD_S(glVertexAttribPointer);
#endif
}
#endif
static tb_bool_t g2_demo_gbox2_init(tb_int_t argc, tb_char_t** argv)
{
	// init context
#if defined(G2_CONFIG_CORE_GL) || defined(G2_CONFIG_CORE_GLES)
	g2_demo_gbox2_init_gl();
	g_context = g2_context_init_gl(G2_DEMO_PIXFMT, G2_DEMO_WIDTH, G2_DEMO_HEIGHT, G2_CONFIG_GL_VERSION);
	tb_assert_and_check_return_val(g_context, TB_FALSE);
#elif defined(G2_CONFIG_CORE_SKIA)
	g_context = g2_context_init_skia(G2_DEMO_PIXFMT, TB_NULL, G2_DEMO_WIDTH, G2_DEMO_HEIGHT, 0);
	tb_assert_and_check_return_val(g_context, TB_FALSE);
#else
	g_context = g2_context_init_soft(G2_DEMO_PIXFMT, TB_NULL, G2_DEMO_WIDTH, G2_DEMO_HEIGHT, 0);
	tb_assert_and_check_return_val(g_context, TB_FALSE);
#endif

	// init surface
	g_surface = g2_context_surface(g_context);
	tb_assert_and_check_return_val(g_surface, TB_FALSE);

	// init painter
	g_painter = g2_init(g_context);
	tb_assert_and_check_return_val(g_painter, TB_FALSE);

	// init position
	g_x0 		= G2_DEMO_WIDTH >> 1;
	g_y0 		= G2_DEMO_HEIGHT >> 1;
	g_dx 		= G2_DEMO_WIDTH >> 2;
	g_dy 		= G2_DEMO_HEIGHT >> 2;
	g_x 		= g_dx;
	g_y 		= g_dy;

	// init matrix
	g2_matrix_init_translate(&g_mx, g2_long_to_float(g_x0), g2_long_to_float(g_y0));	

	// ok
	return TB_TRUE;
}
static tb_void_t g2_demo_gbox2_exit()
{
	// exit painter
	if (g_painter) g2_exit(g_painter);

	// exit context
	if (g_context) g2_context_exit(g_context);
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
	if (!g2_demo_gl_init(argc, argv)) return 0;

	// init gbox2
	if (!g2_demo_gbox2_init(argc, argv)) return 0;

	// init demo 
	if (!g2_demo_init(argc, argv)) return 0;

	// loop 
	glutMainLoop();

	// exit demo
	g2_demo_exit();

	// exit gbox2
	g2_demo_gbox2_exit();

	// exit tbox
	tb_exit();
	return 0;
}



#endif

