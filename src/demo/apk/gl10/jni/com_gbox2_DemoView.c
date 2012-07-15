/* ///////////////////////////////////////////////////////////////////////
 * includes
 */
#include "prefix.h"

/* ///////////////////////////////////////////////////////////////////////
 * implementation
 */

/*
 * Class:     com_gbox2_DemoView
 * Method:    demo_init
 * Signature: ()I
 */
JNIEXPORT jint JNICALL Java_com_gbox2_DemoView_demo_1init
  (JNIEnv * env, jclass this)
{
	// init tbox
	static tb_bool_t init = TB_FALSE;
	if (!init)
	{
		if (!tb_init(TB_NULL, 0)) return 0;
		init = TB_TRUE;
	}

	// init 
	return (jint)g2_demo_init();
}

/*
 * Class:     com_gbox2_DemoView
 * Method:    demo_exit
 * Signature: (I)V
 */
JNIEXPORT void JNICALL Java_com_gbox2_DemoView_demo_1exit
  (JNIEnv * env, jclass this, jint demo)
{
	g2_demo_exit((tb_handle_t)demo);
}

/*
 * Class:     com_gbox2_DemoView
 * Method:    demo_draw
 * Signature: (I)V
 */
JNIEXPORT void JNICALL Java_com_gbox2_DemoView_demo_1draw
  (JNIEnv * env, jclass this, jint demo)
{
	g2_demo_draw((tb_handle_t)demo);
}

/*
 * Class:     com_gbox2_DemoView
 * Method:    demo_size
 * Signature: (III)V
 */
JNIEXPORT void JNICALL Java_com_gbox2_DemoView_demo_1size
  (JNIEnv * env, jclass this, jint demo, jint width, jint height)
{
	g2_demo_size((tb_handle_t)demo, width, height);
}

/*
 * Class:     com_gbox2_DemoView
 * Method:    demo_move
 * Signature: (IFF)V
 */
JNIEXPORT void JNICALL Java_com_gbox2_DemoView_demo_1move
  (JNIEnv * env, jclass this, jint demo, jfloat x, jfloat y)
{
	g2_demo_move((tb_handle_t)demo, (tb_long_t)x, (tb_long_t)y);
}

