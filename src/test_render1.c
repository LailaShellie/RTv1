#include "rtv1.h"
#include "validation.h"
#include "test_render.h"

t_vect3d canvas_to_viewport(int x, int y)
{
	t_vect3d	res;
	int			Cx, Cy;

	Cx = x - W / 2;
	Cy = y - H / 2;

	res.x = (double)Cx * 1.0 * W;
	res.y = (double)Cy * 1.0 * H;
	res.z = 1;
	return (res);
}

void	intersect_ray_sphere(t_vect3d O, t_vect3d D, t_figure *figure, t_roots *roots)
{

}

int		test_trace_ray(t_rtv1 *rt, t_vect3d O, t_vect3d D, double t_min, double t_max)
{
	t_figure	*figure_closest = NULL;
	t_figure	*figure_curr = NULL;
	t_roots		roots;

	roots.closest_t = INF;
	figure_curr = rt->figures;
	while (figure_curr)
	{
		intersect_ray_sphere(O, D, figure_curr, &roots);
		if (t_min <= roots.t1 && roots.t1 < roots.closest_t)
		{
			roots.closest_t = roots.t1;
			figure_closest = figure_curr;
		}
		if (t_min <= roots.t2 && roots.t2 < roots.closest_t)
		{
			roots.closest_t = roots.t2;
			figure_closest = figure_curr;
		}
		figure_curr = figure_curr->next;
	}
	if (figure_closest == NULL)
		return (BACKGROUND);
	else
		return (figure_closest->color);
}

void test_render(t_rtv1 *rt)
{
	int		x;
	int		y;
	t_vect3d	D;
	t_vect3d	O;
	int			color;

	int		Cx, Cy;

	O = init_vect3d(0.0, 0.0, 0.0);
	y = -1;
	while (++y < H)
	{
		x = -1;
		while (++x < W)
		{
			D = canvas_to_viewport(x, y);
			color = test_trace_ray(rt, O, D, 1, INF);
			((int *)rt->img->data)[x + y * rt->img->size_line / 4] = color;


		}
	}
	mlx_put_image_to_window(rt->mlx_ptr, rt->win_ptr, rt->img->img_ptr, 0, 0);
	printf("started render1\n");
}
