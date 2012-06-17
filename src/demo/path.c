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
	g_dx = (x - g_x0) << 1;
	g_dy = (y - g_y0) << 1;
	if (g_dx < 0) g_dx = -g_dx;
	if (g_dy < 0) g_dy = -g_dy;
}
static tb_void_t g2_demo_drag(tb_int_t x, tb_int_t y)
{
	g_x0 = x;
	g_y0 = y;
}
static tb_void_t g2_demo_wheeldown(tb_int_t x, tb_int_t y)
{	
	if (g_penw > 1) g_penw--;
	else g_penw = 1;
	g2_style_width_set(g_style, g2_int_to_scalar(g_penw));
}
static tb_void_t g2_demo_wheelup(tb_int_t x, tb_int_t y)
{
	if (g_penw > 1000) g_penw = 1000;
	else g_penw++;
	g2_style_width_set(g_style, g2_int_to_scalar(g_penw));
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
}

/* ////////////////////////////////////////////////////////////////////////
 * implemention
 */
static tb_bool_t g2_demo_init(tb_int_t argc, tb_char_t** argv)
{
	// init style
	g2_style_width_set(g_style, g2_int_to_scalar(g_penw));
	g2_style_cap_set(g_style, g_cap[g_capi]);
	g2_style_join_set(g_style, g_join[g_joini]);

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
		}
		else
		{
			g2_path_movei_to(g_path[i], &g_pts[i][0]);
			for (j = 1; j < g_ptn[i]; j++)
				g2_path_linei_to(g_path[i], &g_pts[i][j]);
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
static tb_void_t g2_demo_render()
{
	g2_style_mode_set(g_style, G2_STYLE_MODE_FILL);
	g2_style_color_set(g_style, G2_COLOR_RED);
	g2_draw_path(g_painter, g_path[g_pti]);

	g2_style_mode_set(g_style, G2_STYLE_MODE_STROKE);
	g2_style_color_set(g_style, G2_COLOR_BLUE);
	g2_draw_path(g_painter, g_path[g_pti]);
}
