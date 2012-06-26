/* ////////////////////////////////////////////////////////////////////////
 * includes
 */
#include "demo.h"

/* ////////////////////////////////////////////////////////////////////////
 * globals
 */

// points
static g2_ipoint_t pts0[] = 
{
	{-100, -100}
, 	{-50, -100}
, 	{0, -150}
, 	{50, -100}
, 	{100, -100}
, 	{100, -50}
, 	{20, 0}
, 	{100, 50}
, 	{100, 100}
, 	{50, 100}
, 	{0, 150}
, 	{-50, 100}
, 	{-100, 100}
, 	{-100, 50}
, 	{-200, 0}
, 	{-100, -50}
, 	{-100, -100}
};
static g2_ipoint_t pts1[] = 
{
	{0, 0}
, 	{-50, -100}
, 	{0, -200}
, 	{50, -100}
, 	{0, 0}
, 	{0, 0}
, 	{100, -50}
, 	{200, 0}
, 	{100, 50}
, 	{0, 0}
, 	{0, 0}
, 	{50, 100}
, 	{0, 200}
, 	{-50, 100}
, 	{0, 0}
, 	{0, 0}
, 	{-100, 50}
, 	{-200, 0}
, 	{-100, -50}
, 	{0, 0}
};
static g2_ipoint_t pts2[] = 
{
 	{-200, -200}
, 	{-200, 200}
, 	{200, 200}
, 	{200, -200}
, 	{-200, -200}
, 	{-100, 100}
, 	{-100, -100}
, 	{100, -100}
, 	{100, 100}
, 	{-100, 100}
};
static g2_ipoint_t pts3[] = 
{
	{-100, -100}
, 	{0, -150}
, 	{100, -100}
, 	{20, 0}
, 	{100, 100}
, 	{0, 150}
, 	{-100, 100}
, 	{-200, 0}
, 	{-100, -100}
};
static g2_ipoint_t cpts3[] = 
{
 	{-50, -100}
, 	{50, -100}
, 	{100, -50}
, 	{100, 50}
, 	{50, 100}
, 	{-50, 100}
, 	{-100, 50}
, 	{-100, -50}
};
static g2_ipoint_t pts4[] = 
{
	{0, 0}
, 	{0, -200}
, 	{0, 0}
, 	{0, 0}
, 	{200, 0}
, 	{0, 0}
, 	{0, 0}
, 	{0, 200}
, 	{0, 0}
, 	{0, 0}
, 	{-200, 0}
, 	{0, 0}
};
static g2_ipoint_t cpts4[] = 
{
 	{-50, -100}
, 	{50, -100}
, 	{0, 0}
, 	{100, -50}
, 	{100, 50}
, 	{0, 0}
, 	{50, 100}
, 	{-50, 100}
, 	{0, 0}
, 	{-100, 50}
, 	{-100, -50}
};

static tb_size_t 		g_pti = 0;
static g2_ipoint_t* 	g_pts[] = 	{ 	pts0, pts1, pts2, pts3, pts4 	};
static tb_size_t 		g_ptn[] = 	{ 	sizeof(pts0) / sizeof(g2_ipoint_t)
									, 	sizeof(pts1) / sizeof(g2_ipoint_t)
									, 	sizeof(pts2) / sizeof(g2_ipoint_t)
									, 	sizeof(pts3) / sizeof(g2_ipoint_t)
									, 	sizeof(pts4) / sizeof(g2_ipoint_t)
									};
static g2_ipoint_t* 	g_cpts[] = 	{ 	TB_NULL, TB_NULL, TB_NULL, cpts3, cpts4 };
static tb_size_t 		g_cptn[] = 	{ 	0
									, 	0
									, 	0
									, 	sizeof(cpts3) / sizeof(g2_point_t)
									, 	sizeof(cpts4) / sizeof(g2_point_t)
									};
static tb_size_t const 	g_ptm = 5;
static tb_handle_t 		g_path[5] = {0};

/* ////////////////////////////////////////////////////////////////////////
 * events
 */
static tb_void_t g2_demo_move(tb_int_t x, tb_int_t y)
{
	g_dx = x > g_x0? x - g_x0 : g_x0 - x;
	g_dy = y > g_y0? y - g_y0 : g_y0 - y;

	g2_float_t dx = g2_long_to_float(g_dx);
	g2_float_t dy = g2_long_to_float(g_dy);

	g2_float_t an = 0;
	if (y == g_y0) an = 0;
	else if (x == g_x0) an = g2_long_to_float(90);
	else an = g2_div(g2_imul(g2_atan(g2_div(dy, dx)), 180), G2_PI);
	if (y < g_y0 && x < g_x0) an = g2_long_to_float(180) - an;
	if (y > g_y0 && x < g_x0) an += g2_long_to_float(180);
	if (y > g_y0 && x > g_x0) an = g2_long_to_float(360) - an;
	g_an = an;
}
static tb_void_t g2_demo_drag(tb_int_t x, tb_int_t y)
{
}
static tb_void_t g2_demo_wheeldown(tb_int_t x, tb_int_t y)
{	
	if (g_penw > 1) g_penw--;
	else g_penw = 1;
	g2_style_width_set(g_style, g2_long_to_float(g_penw));
}
static tb_void_t g2_demo_wheelup(tb_int_t x, tb_int_t y)
{
	if (g_penw > 1000) g_penw = 1000;
	else g_penw++;
	g2_style_width_set(g_style, g2_long_to_float(g_penw));
}
static tb_void_t g2_demo_lclickdown(tb_int_t x, tb_int_t y)
{
	g_pti = (g_pti + 1) % g_ptm;	
}
static tb_void_t g2_demo_lclickup(tb_int_t x, tb_int_t y)
{
}
static tb_void_t g2_demo_rclickdown(tb_int_t x, tb_int_t y)
{
	g_capi = (g_capi + 1) % 3;
	g_joini = (g_joini + 1) % 3;
	g2_style_cap_set(g_style, g_cap[g_capi]);
	g2_style_join_set(g_style, g_join[g_joini]);
}
static tb_void_t g2_demo_rclickup(tb_int_t x, tb_int_t y)
{
}
static tb_void_t g2_demo_key(tb_int_t key)
{
	if (key == 'a')
	{
		tb_size_t flag = g2_style_flag(g_style);
		g2_style_flag_set(g_style, flag & G2_STYLE_FLAG_ANTI_ALIAS? flag & ~G2_STYLE_FLAG_ANTI_ALIAS : flag | G2_STYLE_FLAG_ANTI_ALIAS);
	}
}

/* ////////////////////////////////////////////////////////////////////////
 * implemention
 */
static tb_bool_t g2_demo_init(tb_int_t argc, tb_char_t** argv)
{
	// init path
	tb_size_t 	i = 0;
	tb_size_t 	j = 0;
	for (i = 0; i < g_ptm; i++)
	{
		g_path[i] = g2_path_init();
		if (g_cpts[i])
		{
			g2_path_movei_to(g_path[i], &g_pts[i][0]);
			for (j = 1; j < g_ptn[i]; j++)
				g2_path_quadi_to(g_path[i], &g_pts[i][j], &g_cpts[i][j - 1]);
			g2_path_close(g_path[i]);
		}
		else
		{
			g2_path_movei_to(g_path[i], &g_pts[i][0]);
			for (j = 1; j < g_ptn[i]; j++)
				g2_path_linei_to(g_path[i], &g_pts[i][j]);
			g2_path_close(g_path[i]);
		}
	}

	// ok
	return TB_TRUE;
}
static tb_void_t g2_demo_exit()
{
	tb_size_t i;
	for (i = 0; i < g_ptm; i++) g2_path_exit(g_path[i]);
}
static tb_void_t g2_demo_size(tb_int_t w, tb_int_t h)
{
	// init style
	g2_style_width_set(g_style, g2_long_to_float(g_penw));
	g2_style_cap_set(g_style, g_cap[g_capi]);
	g2_style_join_set(g_style, g_join[g_joini]);
}
static tb_void_t g2_demo_render()
{
	g2_float_t x0 = g2_long_to_float(g_x0);
	g2_float_t y0 = g2_long_to_float(g_y0);
	g2_float_t dx = g2_long_to_float(g_dx);
	g2_float_t dy = g2_long_to_float(g_dy);
	g2_float_t dw = g2_long_to_float(g_width);
	g2_float_t dh = g2_long_to_float(g_height);

	dx = g2_lsh(dx, 2);
	dy = g2_lsh(dy, 2);

	// save
	g2_save(g_painter, G2_SAVE_MODE_MATRIX);

#if 0
	g2_translate(g_painter, x0, y0);
	g2_scale(g_painter, g2_div(dx, dw), g2_div(-dy, dh));
	g2_rotate(g_painter, g_an);
#else
	g2_matrix_t mx;
	g2_matrix_init_translate(&mx, x0, y0);
	g2_matrix_scale(&mx, g2_div(dx, dw), g2_div(-dy, dh));
	g2_matrix_rotate(&mx, g_an);
	g2_matrix_set(g_painter, &mx);
#endif

	// clip
	g2_clip_path(g_painter, G2_CLIP_MODE_REPLACE | (g2_style_flag(g_style) & G2_STYLE_FLAG_ANTI_ALIAS? G2_CLIP_MODE_ANTI_ALIAS : 0), g_path[g_pti]);

	// load
	g2_load(g_painter);

	// clip
	g2_clip2i_rect(g_painter, G2_CLIP_MODE_INTERSECT, 10, 10, g_width - 20, g_height - 20);

	// draw
	g2_style_mode_set(g_style, G2_STYLE_MODE_FILL);
	g2_style_color_set(g_style, G2_COLOR_RED);
	g2_draw2i_rect(g_painter, 0, 0, g_width, g_height);
}
