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
tb_handle_t 	g2_demo_init();
tb_void_t 		g2_demo_exit(tb_handle_t hdemo);

// draw
tb_void_t 		g2_demo_draw(tb_handle_t hdemo);

// size
tb_void_t 		g2_demo_size(tb_handle_t hdemo, tb_size_t width, tb_size_t height);

// move
tb_void_t 		g2_demo_move(tb_handle_t hdemo, tb_long_t x, tb_long_t y);

// c plus plus
#ifdef __cplusplus
}
#endif

#endif


