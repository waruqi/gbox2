#ifndef G2_APK_GL10_DEMO_H
#define G2_APK_GL10_DEMO_H

// c plus plus
#ifdef __cplusplus
extern "C" {
#endif

/* ///////////////////////////////////////////////////////////////////////
 * includes
 */
#include "prefix.h"

/* ///////////////////////////////////////////////////////////////////////
 * interfaces
 */

// init & exit
tb_bool_t 		g2_demo_gl_init();
tb_void_t 		g2_demo_gl_exit();

// draw
tb_void_t 		g2_demo_gl_draw();

// move
tb_void_t 		g2_demo_gl_move(tb_long_t x, tb_long_t y);

// size
tb_void_t 		g2_demo_gl_size(tb_size_t width, tb_size_t height);

// fps
tb_size_t 		g2_demo_gl_tfps();

// rpt
tb_size_t 		g2_demo_gl_trpt();


// c plus plus
#ifdef __cplusplus
}
#endif

#endif


