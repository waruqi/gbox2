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
 * implemention
 */
static tb_bool_t g2_demo_init()
{
	// init path
	tb_size_t 	i = 0;
	tb_size_t 	j = 0;
	for (i = 0; i < g_ptm; i++)
	{
		tb_size_t h = 0;
		tb_size_t c = 0;
		g_path[i] = g2_path_init();
		if (g_cpts[i])
		{
			g2_path_movei_to(g_path[i], &g_pts[i][0]);
			for (j = 1; j < g_ptn[i]; j++)
			{
				if (c)
				{
					g2_path_close(g_path[i]);
					g2_path_movei_to(g_path[i], &g_pts[i][j]);
					h = j;
					c = 0;
				}
				else 
				{
					g2_path_quadi_to(g_path[i], &g_cpts[i][j - 1], &g_pts[i][j]);
					if (g_pts[i][j].x == g_pts[i][h].x && g_pts[i][j].y == g_pts[i][h].y) c = 1;
				}
			}
			g2_path_close(g_path[i]);
		}
		else
		{
			g2_path_movei_to(g_path[i], &g_pts[i][0]);
			for (j = 1; j < g_ptn[i]; j++)
			{
				if (c)
				{
					g2_path_close(g_path[i]);
					g2_path_movei_to(g_path[i], &g_pts[i][j]);
					h = j;
					c = 0;
				}
				else 
				{
					g2_path_linei_to(g_path[i], &g_pts[i][j]);
					if (g_pts[i][j].x == g_pts[i][h].x && g_pts[i][j].y == g_pts[i][h].y) c = 1;
				}
			}
			g2_path_close(g_path[i]);
		}
	}

	// init mode
	g_mode = G2_STYLE_MODE_FILL_STOK;

	// init matrix
	g_bm = TB_TRUE;

	// ok
	return TB_TRUE;
}
static tb_void_t g2_demo_exit()
{
	tb_size_t i;
	for (i = 0; i < g_ptm; i++) g2_path_exit(g_path[i]);
}
static tb_void_t g2_demo_draw()
{
	g2_draw_path(g_painter, g_path[g_pti]);
}
static tb_void_t g2_demo_move(tb_long_t x, tb_long_t y)
{
}
static tb_void_t g2_demo_size(tb_size_t width, tb_size_t height)
{
}
static tb_void_t g2_demo_tkey(tb_size_t key)
{
	if (key == 'p') g_pti = (g_pti + 1) % g_ptm;
}
