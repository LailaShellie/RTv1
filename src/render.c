//
// Created by Laila Shellie on 2020-01-20.
//

#include "../rtv1.h"

int			intersect_sphere(t_vect3d *o, t_vect3d *d,
		t_figure *sphere, t_roots *t)
{
	double		k1;
	double 		k2;
	double 		k3;

	t_vect3d	*oc = new_vect3d();

	sub_vect3d(oc, sphere->center, o);

	k1 = dot_vect3d(d, d);
	k2 = 2.0 * dot_vect3d(oc, d);
	k3 = dot_vect3d(oc, oc) - (sphere->radius * sphere->radius);

//	printf("%lf %lf\n", dot_vect3d(oc, oc), sphere->r * sphere->r);

	double 		disc;

	disc = k2 * k2 - 4.0 * k1 * k3;
	free_vect3d(oc);
//	printf("%lf\n", dot_vect3d(oc, oc));
//	printf("%lf %lf %lf\n", k1, k2, k3);
	if (disc < 0)
	{
//		printf("INF\n");
		return (0);
	}
	t->t1 = (-k2 + sqrt(disc)) / (2.0 * k1);
	t->t2 = (-k2 - sqrt(disc)) / (2.0 * k1);
//	printf("%lf %lf\n", t->t1, t->t2);
	return (1);
}

int		trace_ray(t_rtv1 *rt, t_vect3d *o, t_vect3d *d)
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
		if (intersect_sphere(o, d, cur, t))
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
	int 	x;
	int 	y;

	t_vect3d	*d;

	d = new_vect3d();

	y = -1;
	while (++y < H)
	{
		x = -1;
		while (++x < W)
		{
			init_vect3d(d, (double)(x - W / 2) * ((double)VW / W), (double)(y - H / 2) * ((double)VH / H), VZ);
		//	printf("1 %lf %lf %lf\n", d->coords[X], d->coords[Y], d->coords[Z]);
			sub_vect3d(d, rt->cam->center, d);
	//		printf("%lf %lf %lf\n", d->coords[X], d->coords[Y], d->coords[Z]);
			((int *)rt->img->data)[x + y * rt->img->size_line / 4]
			= trace_ray(rt, rt->cam->center, d);
		}
	}
}