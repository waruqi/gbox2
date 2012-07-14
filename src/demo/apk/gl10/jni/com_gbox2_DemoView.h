#ifndef G2_APK_GL10_DEMO_H
#define G2_APK_GL10_DEMO_H

// c plus plus
#ifdef __cplusplus
extern "C" {
#endif

/* ///////////////////////////////////////////////////////////////////////
 * includes
 */
#include <jni.h>

/* ///////////////////////////////////////////////////////////////////////
 * interfaces
 */
/*
 * Class:     com_gbox2_DemoView
 * Method:    demo_init
 * Signature: ()I
 */
JNIEXPORT jint JNICALL Java_com_gbox2_DemoView_demo_1init
  (JNIEnv *, jclass);

/*
 * Class:     com_gbox2_DemoView
 * Method:    demo_exit
 * Signature: (I)V
 */
JNIEXPORT void JNICALL Java_com_gbox2_DemoView_demo_1exit
  (JNIEnv *, jclass, jint);

/*
 * Class:     com_gbox2_DemoView
 * Method:    demo_draw
 * Signature: (I)V
 */
JNIEXPORT void JNICALL Java_com_gbox2_DemoView_demo_1draw
  (JNIEnv *, jclass, jint);

/*
 * Class:     com_gbox2_DemoView
 * Method:    demo_size
 * Signature: (III)V
 */
JNIEXPORT void JNICALL Java_com_gbox2_DemoView_demo_1size
  (JNIEnv *, jclass, jint, jint, jint);

/*
 * Class:     com_gbox2_DemoView
 * Method:    demo_move
 * Signature: (IFF)V
 */
JNIEXPORT void JNICALL Java_com_gbox2_DemoView_demo_1move
  (JNIEnv *, jclass, jint, jfloat, jfloat);

// c plus plus
#ifdef __cplusplus
}
#endif

#endif


