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
 * Signature: (III)Z
 */
JNIEXPORT jboolean JNICALL Java_com_gbox2_DemoView_demo_1init
  (JNIEnv * env, jclass this, jint width, jint height, jint version)
{
	// init tbox
	static tb_bool_t init = TB_FALSE;
	if (!init)
	{
		if (!tb_init(TB_NULL, 0)) return JNI_FALSE;
		init = TB_TRUE;
	}

	return g2_demo_gl_init(width, height, version)? JNI_TRUE : JNI_FALSE;
}

/*
 * Class:     com_gbox2_DemoView
 * Method:    demo_exit
 * Signature: ()V
 */
JNIEXPORT void JNICALL Java_com_gbox2_DemoView_demo_1exit
  (JNIEnv * env, jclass this)
{
	g2_demo_gl_exit();
}

/*
 * Class:     com_gbox2_DemoView
 * Method:    demo_draw
 * Signature: ()V
 */
JNIEXPORT void JNICALL Java_com_gbox2_DemoView_demo_1draw
  (JNIEnv * env, jclass this)
{
	g2_demo_gl_draw();
}

/*
 * Class:     com_gbox2_DemoView
 * Method:    demo_size
 * Signature: (II)V
 */
JNIEXPORT void JNICALL Java_com_gbox2_DemoView_demo_1size
  (JNIEnv * env, jclass this, jint width, jint height)
{
	g2_demo_gl_size(width, height);
}

/*
 * Class:     com_gbox2_DemoView
 * Method:    demo_move
 * Signature: (FF)V
 */
JNIEXPORT void JNICALL Java_com_gbox2_DemoView_demo_1move
  (JNIEnv * env, jclass this, jfloat x, jfloat y)
{
	g2_demo_gl_move((tb_long_t)x, (tb_long_t)y);
}

/*
 * Class:     com_gbox2_DemoView
 * Method:    demo_tfps
 * Signature: ()I
 */
JNIEXPORT jint JNICALL Java_com_gbox2_DemoView_demo_1tfps
  (JNIEnv * env, jclass this)
{
	return g2_demo_gl_tfps();
}

/*
 * Class:     com_gbox2_DemoView
 * Method:    demo_trpt
 * Signature: ()I
 */
JNIEXPORT jint JNICALL Java_com_gbox2_DemoView_demo_1trpt
  (JNIEnv * env, jclass this)
{
	return g2_demo_gl_trpt();
}
/*
 * Class:     com_gbox2_DemoView
 * Method:    demo_tkey
 * Signature: (I)V
 */
JNIEXPORT void JNICALL Java_com_gbox2_DemoView_demo_1tkey
  (JNIEnv * env, jclass this, jint key)
{
	g2_demo_gl_tkey(key);
}

