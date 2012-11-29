/*!The Graphic 2D Box Library
 * 
 * GBox2 is free software; you can redistribute it and/or modify
 * it under the terms of the GNU Lesser General Public License as published by
 * the Free Software Foundation; either version 2.1 of the License, or
 * (at your option) any later version.
 * 
 * GBox2 is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU Lesser General Public License for more details.
 * 
 * You should have received a copy of the GNU Lesser General Public License
 * along with GBox2; 
 * If not, see <a href="http://www.gnu.org/licenses/"> http://www.gnu.org/licenses/</a>
 * 
 * Copyright (C) 2009 - 2012, ruki All rights reserved.
 *
 * @author		ruki
 * @file		path.cpp
 *
 */

/* ///////////////////////////////////////////////////////////////////////
 * includes
 */
#include "path.h"

/* ///////////////////////////////////////////////////////////////////////
 * implementation
 */
static __tb_inline__ tb_handle_t g2_skia_path_init()
{
	// alloc
	G2SkiaPath* spath = new G2SkiaPath();
	tb_assert_and_check_return_val(spath, TB_NULL);

	// ok
	return spath;
}
static __tb_inline__ tb_void_t g2_skia_path_exit(tb_handle_t path)
{
	G2SkiaPath* spath = static_cast<G2SkiaPath*>(path);
	tb_assert_and_check_return(spath);
 
	// free it
 	delete spath;
}
static __tb_inline__ tb_void_t g2_skia_path_clear(tb_handle_t path)
{
	G2SkiaPath* spath = static_cast<G2SkiaPath*>(path);
	tb_assert_and_check_return(spath);

	spath->reset();
}
static __tb_inline__ tb_void_t g2_skia_path_close(tb_handle_t path)
{
	G2SkiaPath* spath = static_cast<G2SkiaPath*>(path);
	tb_assert_and_check_return(spath);

	spath->close();
}
static __tb_inline__ tb_bool_t g2_skia_path_null(tb_handle_t path)
{	
	G2SkiaPath const* spath = static_cast<G2SkiaPath const*>(path);
	tb_assert_and_check_return_val(spath, TB_TRUE);

	return spath->isEmpty()? TB_TRUE : TB_FALSE;
}
static __tb_inline__ tb_bool_t g2_skia_path_itor_init(tb_handle_t path)
{
	G2SkiaPath* spath = static_cast<G2SkiaPath*>(path);
	tb_assert_and_check_return_val(spath, TB_FALSE);

	// init
	spath->iterator().setPath(*spath, false);
	
	// ok
	return TB_TRUE;
}
static __tb_inline__ tb_size_t g2_skia_path_itor_next(tb_handle_t path, g2_point_t pt[3])
{
	G2SkiaPath* spath = static_cast<G2SkiaPath*>(path);
	tb_assert_and_check_return_val(spath, G2_PATH_CODE_NONE);

	// next, @note hack: g2_point_t => SkPoint
	g2_point_t points[4];
	SkPath::Verb verb = spath->iterator().next((SkPoint*)(points));
	switch (verb)
	{
	case SkPath::kMove_Verb:
		pt[0] = points[0];
		break;
	case SkPath::kLine_Verb:
		pt[0] = points[1];
		break;
	case SkPath::kQuad_Verb:
		pt[0] = points[1];
		pt[1] = points[2];
		break;
	case SkPath::kCubic_Verb:
		pt[0] = points[1];
		pt[1] = points[2];
		pt[2] = points[3];
		break;
	default:
		break;
	}

	// ok?
	return verb != SkPath::kDone_Verb? (static_cast<tb_size_t>(verb) + 1) : G2_PATH_CODE_NONE;
}
static __tb_inline__ tb_void_t g2_skia_path_itor_exit(tb_handle_t path)
{
}
static __tb_inline__ tb_bool_t g2_skia_path_last_pt(tb_handle_t path, g2_point_t* pt)
{	
	G2SkiaPath const* spath = static_cast<G2SkiaPath const*>(path);
	tb_assert_and_check_return_val(spath && pt, TB_TRUE);

	return spath->getLastPt((SkPoint*)pt)? TB_TRUE : TB_FALSE;
}
static __tb_inline__ tb_void_t g2_skia_path_move_to(tb_handle_t path, g2_point_t const* pt)
{
	G2SkiaPath* spath = static_cast<G2SkiaPath*>(path);
	tb_assert_and_check_return(spath && pt);

	spath->moveTo(pt->x, pt->y);
}
static __tb_inline__ tb_void_t g2_skia_path_line_to(tb_handle_t path, g2_point_t const* pt)
{
	G2SkiaPath* spath = static_cast<G2SkiaPath*>(path);
	tb_assert_and_check_return(spath && pt);

	spath->lineTo(pt->x, pt->y);
}
static __tb_inline__ tb_void_t g2_skia_path_quad_to(tb_handle_t path, g2_point_t const* cp, g2_point_t const* pt)
{
	G2SkiaPath* spath = static_cast<G2SkiaPath*>(path);
	tb_assert_and_check_return(spath && pt && cp);

	spath->quadTo(cp->x, cp->y, pt->x, pt->y);
}
static __tb_inline__ tb_void_t g2_skia_path_cube_to(tb_handle_t path, g2_point_t const* c0, g2_point_t const* c1, g2_point_t const* pt)
{
	G2SkiaPath* spath = static_cast<G2SkiaPath*>(path);
	tb_assert_and_check_return(spath && pt && c0 && c1);

	spath->cubicTo(c0->x, c0->y, c1->x, c1->y, pt->x, pt->y);
}
static __tb_inline__ tb_void_t g2_skia_path_arc_to(tb_handle_t path, g2_arc_t const* arc)
{
	G2SkiaPath* spath = static_cast<G2SkiaPath*>(path);
	tb_assert_and_check_return(spath && arc);

	spath->arcTo(SkRect::MakeXYWH(arc->c0.x - arc->rx, arc->c0.y - arc->ry, arc->rx + arc->rx, arc->ry + arc->ry), arc->ab, arc->an, false);
}
static __tb_inline__ tb_void_t g2_skia_path_add_path(tb_handle_t path, tb_handle_t path2)
{
	G2SkiaPath* spath = static_cast<G2SkiaPath*>(path);
	tb_assert_and_check_return(spath && path2);

	spath->addPath(*static_cast<G2SkiaPath const*>(path2));
}
static __tb_inline__ tb_void_t g2_skia_path_add_line(tb_handle_t path, g2_line_t const* line)
{
	G2SkiaPath* spath = static_cast<G2SkiaPath*>(path);
	tb_assert_and_check_return(spath && line);

	spath->incReserve(2);
	spath->moveTo(line->p0.x, line->p0.y);
	spath->lineTo(line->p1.x, line->p1.y);
}
static __tb_inline__ tb_void_t g2_skia_path_add_arc(tb_handle_t path, g2_arc_t const* arc)
{
	G2SkiaPath* spath = static_cast<G2SkiaPath*>(path);
	tb_assert_and_check_return(spath && arc);

	spath->addArc(SkRect::MakeXYWH(arc->c0.x - arc->rx, arc->c0.y - arc->ry, arc->rx + arc->rx, arc->ry + arc->ry), arc->ab, arc->an);
}
static __tb_inline__ tb_void_t g2_skia_path_add_triangle(tb_handle_t path, g2_triangle_t const* triangle)
{
	G2SkiaPath* spath = static_cast<G2SkiaPath*>(path);
	tb_assert_and_check_return(spath && triangle);

	spath->incReserve(3);
	spath->moveTo(triangle->p0.x, triangle->p0.y);
	spath->lineTo(triangle->p1.x, triangle->p1.y);
	spath->lineTo(triangle->p2.x, triangle->p2.y);
	spath->close();
}
static __tb_inline__ tb_void_t g2_skia_path_add_rect(tb_handle_t path, g2_rect_t const* rect)
{
	G2SkiaPath* spath = static_cast<G2SkiaPath*>(path);
	tb_assert_and_check_return(spath && rect);

	spath->addRect(SkRect::MakeXYWH(rect->x, rect->y, rect->w, rect->h));
}
static __tb_inline__ tb_void_t g2_skia_path_add_circle(tb_handle_t path, g2_circle_t const* circle)
{
	G2SkiaPath* spath = static_cast<G2SkiaPath*>(path);
	tb_assert_and_check_return(spath && circle);

	spath->addCircle(circle->c.x, circle->c.y, circle->r);
}
static __tb_inline__ tb_void_t g2_skia_path_add_ellipse(tb_handle_t path, g2_ellipse_t const* ellipse)
{
	G2SkiaPath* spath = static_cast<G2SkiaPath*>(path);
	tb_assert_and_check_return(spath && ellipse);

	spath->addOval(SkRect::MakeXYWH(ellipse->c0.x - ellipse->rx, ellipse->c0.y - ellipse->ry, ellipse->rx + ellipse->rx, ellipse->ry + ellipse->ry));
}

/* ///////////////////////////////////////////////////////////////////////
 * interfaces
 */
extern "C"
{
	tb_handle_t g2_path_init()
	{
		return g2_skia_path_init();
	}
	tb_void_t g2_path_exit(tb_handle_t path)
	{
		g2_skia_path_exit(path);
	}
	tb_void_t g2_path_clear(tb_handle_t path)
	{
		g2_skia_path_clear(path);
	}
	tb_void_t g2_path_close(tb_handle_t path)
	{
		g2_skia_path_close(path);
	}
	tb_bool_t g2_path_null(tb_handle_t path)
	{
		return g2_skia_path_null(path);		
	}
	tb_bool_t g2_path_itor_init(tb_handle_t path)
	{
		return g2_skia_path_itor_init(path);
	}
	tb_size_t g2_path_itor_next(tb_handle_t path, g2_point_t pt[3])
	{
		return g2_skia_path_itor_next(path, pt);
	}
	tb_void_t g2_path_itor_exit(tb_handle_t path)
	{
		g2_skia_path_itor_exit(path);
	}
	tb_bool_t g2_path_last_pt(tb_handle_t path, g2_point_t* pt)
	{
		return g2_skia_path_last_pt(path, pt);		
	}
	tb_void_t g2_path_move_to(tb_handle_t path, g2_point_t const* pt)
	{
		g2_skia_path_move_to(path, pt);		
	}
	tb_void_t g2_path_line_to(tb_handle_t path, g2_point_t const* pt)
	{
		g2_skia_path_line_to(path, pt);		
	}
	tb_void_t g2_path_quad_to(tb_handle_t path, g2_point_t const* cp, g2_point_t const* pt)
	{
		g2_skia_path_quad_to(path, cp, pt);		
	}
	tb_void_t g2_path_cube_to(tb_handle_t path, g2_point_t const* c0, g2_point_t const* c1, g2_point_t const* pt)
	{
		g2_skia_path_cube_to(path, c0, c1, pt);		
	}
	tb_void_t g2_path_arc_to(tb_handle_t path, g2_arc_t const* arc)
	{
		g2_skia_path_arc_to(path, arc);		
	}
	tb_void_t g2_path_add_path(tb_handle_t path, tb_handle_t path2)
	{
		g2_skia_path_add_path(path, path2);
	}
	tb_void_t g2_path_add_line(tb_handle_t path, g2_line_t const* line)
	{
		g2_skia_path_add_line(path, line);
	}
	tb_void_t g2_path_add_arc(tb_handle_t path, g2_arc_t const* arc)
	{
		g2_skia_path_add_arc(path, arc);
	}
	tb_void_t g2_path_add_triangle(tb_handle_t path, g2_triangle_t const* triangle)
	{
		g2_skia_path_add_triangle(path, triangle);
	}
	tb_void_t g2_path_add_rect(tb_handle_t path, g2_rect_t const* rect)
	{
		g2_skia_path_add_rect(path, rect);
	}
	tb_void_t g2_path_add_circle(tb_handle_t path, g2_circle_t const* circle)
	{
		g2_skia_path_add_circle(path, circle);
	}
	tb_void_t g2_path_add_ellipse(tb_handle_t path, g2_ellipse_t const* ellipse)
	{
		g2_skia_path_add_ellipse(path, ellipse);
	}
}

