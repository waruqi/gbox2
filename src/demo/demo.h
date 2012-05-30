#ifndef GB2_DEMO_H
#define GB2_DEMO_H

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
#define GB2_DEMO_WIDTH 		(640)
#define GB2_DEMO_HEIGHT 	(480)

/* ////////////////////////////////////////////////////////////////////////
 * callbacks
 */
static tb_bool_t gb2_demo_init(tb_int_t argc, tb_char_t** argv);
static tb_void_t gb2_demo_exit();
static tb_void_t gb2_demo_render();
static tb_void_t gb2_demo_move(tb_int_t x, tb_int_t y);
static tb_void_t gb2_demo_drag(tb_int_t x, tb_int_t y);
static tb_void_t gb2_demo_wheeldown(tb_int_t x, tb_int_t y);
static tb_void_t gb2_demo_wheelup(tb_int_t x, tb_int_t y);
static tb_void_t gb2_demo_lclickdown(tb_int_t x, tb_int_t y);
static tb_void_t gb2_demo_lclickup(tb_int_t x, tb_int_t y);
static tb_void_t gb2_demo_rclickdown(tb_int_t x, tb_int_t y);
static tb_void_t gb2_demo_rclickup(tb_int_t x, tb_int_t y);
static tb_void_t gb2_demo_key(tb_int_t key);

/* ////////////////////////////////////////////////////////////////////////
 * gl
 */
static tb_void_t gb2_demo_gl_keyboard(tb_byte_t key, tb_int_t x, tb_int_t y)
{
	gb2_demo_key(key);
}
static tb_void_t gb2_demo_gl_special(tb_int_t key, tb_int_t x, tb_int_t y)
{
	gb2_demo_key(key);
}
static tb_void_t gb2_demo_gl_display()
{
	// clear
	//glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	// render 
	gb2_demo_render();

	// flush
	glutSwapBuffers();
}
#if 0
static tb_void_t gb2_demo_gl_draw(gb2_vframe_t const* vframe)
{
	if (vframe && vframe->data[0])
	{
		glPixelZoom(1.0, -1.0);
		glRasterPos2i(0, g_vdevice.height - 1);
		switch (g_vdevice.pixfmt)
		{
		case MD_PIXFMT_RGB565:
			glDrawPixels(vframe->width, vframe->height, GL_RGB, GL_UNSIGNED_SHORT_5_6_5, vframe->data[0]);
			break;
		case MD_PIXFMT_XRGB8888:
			glDrawPixels(vframe->width, vframe->height, GL_BGRA, GL_UNSIGNED_BYTE, vframe->data[0]);
			break;
		default:
			break;
		}
	}
}
#endif
static tb_void_t gb2_demo_gl_reshape(tb_int_t w, tb_int_t h)
{
	glViewport(0, 0, w, h);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluOrtho2D(0.0, (GLfloat)w, 0.0, (GLfloat)h);
	glMatrixMode(GL_MODELVIEW);
}
static tb_void_t gb2_demo_gl_click(tb_int_t button, tb_int_t state, tb_int_t x, tb_int_t y)
{
	if (button == 0) // left
	{
		if (state == 0)
		{
			gb2_demo_lclickdown(x, y);
		}
		else if (state == 1)
		{
			gb2_demo_lclickup(x, y);
		}
	}
	else if (button == 2) // right
	{	
		if (state == 0)
		{
			gb2_demo_rclickdown(x, y);
		}
		else if (state == 1)
		{
			gb2_demo_rclickup(x, y);
		}
	}
	else if (button == 3) // wheelup
	{	
		if (state == 0) // down
		{
			gb2_demo_wheelup(x, y);
		}
	}
	else if (button == 4) // wheeldown
	{	
		if (state == 0) // down
		{
			gb2_demo_wheeldown(x, y);
		}
	}
}

static tb_bool_t gb2_demo_gl_init(tb_int_t argc, tb_char_t** argv)
{
	// init gl
	glutInit (&argc, argv);
	glutInitDisplayMode (GLUT_RGBA | GLUT_DOUBLE | GLUT_ALPHA | GLUT_STENCIL | GLUT_MULTISAMPLE);
	//glutInitDisplayMode (GLUT_RGBA | GLUT_DOUBLE | GLUT_STENCIL);
	glutInitWindowPosition (0, 0);
	glutInitWindowSize (GB2_DEMO_WIDTH, GB2_DEMO_HEIGHT);
	glutCreateWindow ("gbox2");
	glutDisplayFunc(gb2_demo_gl_display);
	glutIdleFunc(gb2_demo_gl_display);
	glutReshapeFunc(gb2_demo_gl_reshape);
	glutMouseFunc(gb2_demo_gl_click);
	glutPassiveMotionFunc(gb2_demo_move);
	glutMotionFunc(gb2_demo_drag);
	glutKeyboardFunc(gb2_demo_gl_keyboard);
	glutSpecialFunc(gb2_demo_gl_special);

	// ok
	return TB_TRUE;
}

/* ////////////////////////////////////////////////////////////////////////
 * main
 */
tb_int_t main(tb_int_t argc, tb_char_t** argv)
{
	// init tbox
	if (!tb_init(malloc(50 * 1024 * 1024), 50 * 1024 * 1024)) return TB_FALSE;

	// init exit
	atexit(gb2_demo_exit);

	// init gl
	if (!gb2_demo_gl_init(argc, argv)) return TB_FALSE;

	// init demo 
	if (!gb2_demo_init(argc, argv)) return TB_FALSE;

	// loop 
	glutMainLoop();

end:
	// exit demo
	gb2_demo_exit();

	// exit tbox
	tb_exit();
	return 0;
}










#endif

