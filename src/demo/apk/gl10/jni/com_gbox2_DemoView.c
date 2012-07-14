/* ///////////////////////////////////////////////////////////////////////
 * includes
 */
#include <jni.h>
#include <android/log.h>
#include "gbox2.h"

/* ///////////////////////////////////////////////////////////////////////
 * macros
 */

// trace
#define demo_trace(...) __android_log_print(ANDROID_LOG_DEBUG, "gbox2", __VA_ARGS__)

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
	return 0;
}

/*
 * Class:     com_gbox2_DemoView
 * Method:    demo_exit
 * Signature: (I)V
 */
JNIEXPORT void JNICALL Java_com_gbox2_DemoView_demo_1exit
  (JNIEnv * env, jclass this, jint painter)
{
}

/*
 * Class:     com_gbox2_DemoView
 * Method:    demo_draw
 * Signature: (I)V
 */
JNIEXPORT void JNICALL Java_com_gbox2_DemoView_demo_1draw
  (JNIEnv * env, jclass this, jint painter)
{
}

/*
 * Class:     com_gbox2_DemoView
 * Method:    demo_size
 * Signature: (III)V
 */
JNIEXPORT void JNICALL Java_com_gbox2_DemoView_demo_1size
  (JNIEnv * env, jclass this, jint painter, jint width, jint height)
{
}

/*
 * Class:     com_gbox2_DemoView
 * Method:    demo_move
 * Signature: (IFF)V
 */
JNIEXPORT void JNICALL Java_com_gbox2_DemoView_demo_1move
  (JNIEnv * env, jclass this, jint painter, jfloat x, jfloat y)
{
}

