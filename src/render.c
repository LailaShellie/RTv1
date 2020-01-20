//
// Created by Laila Shellie on 2020-01-20.
//

#include "../rtv1.h"

int			intersect_sphere(t_vect3d *cam_pos, t_vect3d *ray,
		t_figure *sphere, t_roots *t)
{
	double		a;
	double 		b;
	double 		c;
	double		d;

	sub_vect3d(sphere->oc, sphere->center, cam_pos);
	a = dot_vect3d(ray, ray);
	b = 2.0 * dot_vect3d(sphere->oc, ray);
	c = dot_vect3d(sphere->oc, sphere->oc) - (sphere->radius * sphere->radius);
	d = b * b - 4.0 * a * c;
	if (d < 0)
		return (0);
	t->t1 = (-b + sqrt(d)) / (2.0 * a);
	t->t2 = (-b - sqrt(d)) / (2.0 * a);
	return (1);
}

int		trace_ray(t_rtv1 *rt, t_vect3d *cam_pos, t_vect3d *ray)
{
	t_figure	*cur;
	t_figure	*closest_f;
	double 		closest_t;
	t_roots		*t = ft_memalloc(sizeof(t_roots));

	closest_f = 0;
	closest_t = INF;
	cur = rt->figures;
	while (cur)
	{
		if (intersect_sphere(cam_pos, ray, cur, t))
		{
			if (t->t1 > VZ && t->t1 < closest_t)
			{
				closest_t = t->t1;
				closest_f = cur;
			}
			if (t->t2 > VZ && t->t2 < closest_t)
			{
				closest_t = t->t2;
				closest_f = cur;
			}
		}
		cur = cur->next;
	}
	if (closest_f == 0)
		return (BACKGROUND);
	return (closest_f->color);
}

void		render(t_rtv1 *rt)
{
	int 		x;
	int 		y;
	t_vect3d	*ray;

	ray = new_vect3d();
	y = -1;
	while (++y < H)
	{
		x = -1;
		while (++x < W)
		{
			init_vect3d(ray, (double)(x - W / 2) * ((double)VW / W), (double)(y - H / 2) * ((double)VH / H), VZ);
			sub_vect3d(ray, rt->cam->center, ray);
			((int *)rt->img->data)[x + y * rt->img->size_line / 4]
			= trace_ray(rt, rt->cam->center, ray);
		}
	}
}