#ifndef G2_APK_GL10_PREFIX_H
#define G2_APK_GL10_PREFIX_H

// c plus plus
#ifdef __cplusplus
extern "C" {
#endif

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

// c plus plus
#ifdef __cplusplus
}
#endif

#endif


