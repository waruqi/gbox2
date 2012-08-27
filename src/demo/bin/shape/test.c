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
#define G2_DEMO_PIXFMT 			(G2_PIXFMT_ARGB8888 | G2_PIXFMT_NENDIAN)
//#define G2_DEMO_PIXFMT 			(G2_PIXFMT_RGB565 | G2_PIXFMT_NENDIAN)

/* ////////////////////////////////////////////////////////////////////////
 * globals
 */
static tb_uint_t 				g_texture = 0;

/* ////////////////////////////////////////////////////////////////////////
 * gl
 */

static tb_void_t g2_demo_gl_display()
{
	// clear
	glClear(GL_COLOR_BUFFER_BIT);

	// init texture
	glEnable(GL_TEXTURE_2D);
//	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, g_texture);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
	glTexEnvi(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT); 
	
	glEnableClientState(GL_VERTEX_ARRAY); 
//	glEnableClientState(GL_NORMAL_ARRAY); 
//	glEnableClientState(GL_TEXTURE_COORD_ARRAY);

	// texcoords
	tb_float_t texcoords[] = 
	{
		0.0f, 0.0f
	, 	1.0f, 0.0f
	, 	0.0f, 1.0f
	, 	1.0f, 1.0f
	};
	glTexCoordPointer(2, GL_FLOAT, 0, texcoords);

	static tb_byte_t* data = TB_NULL;
	if (!data)
	{
		data = tb_malloc(300 * 300 * 4);
		tb_memset(data, 0x55, 300 * 300 * 4);
	}
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, 300, 300, 0, GL_BGRA, GL_UNSIGNED_BYTE, data);

	// init rect
	tb_float_t vertices[8];
	vertices[0] = 0;
	vertices[1] = 0;
	vertices[2] = 400;
	vertices[3] = 0;
	vertices[4] = 0;
	vertices[5] = 400;
	vertices[6] = 400;
	vertices[7] = 400;

	// draw rect
	glVertexPointer(2, GL_FLOAT, 0, vertices);
	glDrawArrays(GL_TRIANGLE_STRIP, 0, 4);

	// exit texture
//	glActiveTexture(GL_TEXTURE0);
	glDisable(GL_TEXTURE_2D);

	// flush
	glutSwapBuffers();
}
static tb_void_t g2_demo_gl_reshape(tb_int_t w, tb_int_t h)
{
	glViewport(0, 0, w, h);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glOrtho(0.0, (GLfloat)w, 0.0, (GLfloat)h, -1.0f, 1.0f);
	glMatrixMode(GL_MODELVIEW);
}

/* ////////////////////////////////////////////////////////////////////////
 * main
 */
tb_int_t main(tb_int_t argc, tb_char_t** argv)
{
	// init tbox
	if (!tb_init(malloc(50 * 1024 * 1024), 50 * 1024 * 1024)) return 0;

	// init gl
	glutInit (&argc, argv);
	glutInitDisplayMode (GLUT_RGBA | GLUT_DOUBLE | GLUT_STENCIL | GLUT_MULTISAMPLE);
	glutInitWindowPosition (0, 0);
	glutInitWindowSize (G2_DEMO_WIDTH, G2_DEMO_HEIGHT);
	glutCreateWindow ("gbox2");
	glutDisplayFunc(g2_demo_gl_display);
	glutIdleFunc(g2_demo_gl_display);
	glutReshapeFunc(g2_demo_gl_reshape);

 	glGenTextures(1, &g_texture);
	glBindTexture(GL_TEXTURE_2D, g_texture);

	// loop 
	glutMainLoop();

	// exit tbox
	tb_exit();
	return 0;
}



