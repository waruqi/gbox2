#ifndef G2_APK_GL1x_JNI_H
#define G2_APK_GL1x_JNI_H

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
 * Signature: (I)Z
 */
JNIEXPORT jboolean JNICALL Java_com_gbox2_DemoView_demo_1init
  (JNIEnv *, jclass, jint);

/*
 * Class:     com_gbox2_DemoView
 * Method:    demo_exit
 * Signature: ()V
 */
JNIEXPORT void JNICALL Java_com_gbox2_DemoView_demo_1exit
  (JNIEnv *, jclass);

/*
 * Class:     com_gbox2_DemoView
 * Method:    demo_draw
 * Signature: ()V
 */
JNIEXPORT void JNICALL Java_com_gbox2_DemoView_demo_1draw
  (JNIEnv *, jclass);

/*
 * Class:     com_gbox2_DemoView
 * Method:    demo_size
 * Signature: (II)V
 */
JNIEXPORT void JNICALL Java_com_gbox2_DemoView_demo_1size
  (JNIEnv *, jclass, jint, jint);

/*
 * Class:     com_gbox2_DemoView
 * Method:    demo_move
 * Signature: (FF)V
 */
JNIEXPORT void JNICALL Java_com_gbox2_DemoView_demo_1move
  (JNIEnv *, jclass, jfloat, jfloat);

/*
 * Class:     com_gbox2_DemoView
 * Method:    demo_tfps
 * Signature: ()I
 */
JNIEXPORT jint JNICALL Java_com_gbox2_DemoView_demo_1tfps
  (JNIEnv *, jclass);

/*
 * Class:     com_gbox2_DemoView
 * Method:    demo_trpt
 * Signature: ()I
 */
JNIEXPORT jint JNICALL Java_com_gbox2_DemoView_demo_1trpt
  (JNIEnv *, jclass);

/*
 * Class:     com_gbox2_DemoView
 * Method:    demo_tkey
 * Signature: (I)V
 */
JNIEXPORT void JNICALL Java_com_gbox2_DemoView_demo_1tkey
  (JNIEnv *, jclass, jint );

// c plus plus
#ifdef __cplusplus
}
#endif

#endif


