//
// Created by Laila Shellie on 2020-01-22.
//

#include "rtv1.h"

//if (figure_closest == NULL)
//return (rt->background_color);
//else
//{
//P = scale_vect3d(roots.closest_t, &D);
//P = add_vect3d(&O, &P);
//N = sub_vect3d(&figure_closest->center, &P);
//norm_vect3d(&N);
//V = scale_vect3d(-1.0, &D);
//local_color = calculate_color(figure_closest->color, compute_light(rt, P, N, V, figure_closest->s));
//
//reflect = figure_closest->reflect;
//if (depth <= 0 || reflect <= 0.001)
//return (local_color);
//else
//{
//ray = reflect_ray(&V, &N);
//reflected_color = test_trace_ray(rt, P, ray, 0.001, INF, depth - 1);
//local_color = calculate_color(local_color, 1 - reflect);
//reflected_color = calculate_color(reflected_color, reflect);
//return (sum_color(local_color, reflected_color));
//}
//}

void   get_intersection_point(t_rtv1 *rt)
{
    rt->calc.p = scale_vect3d(rt->calc.t.closest_t, &rt->calc.ray);
    rt->calc.p = add_vect3d(&rt->cam->center, &rt->calc.p);
}

int in_shadow(t_rtv1 *rt, t_light *light)
{
	t_vect3d	l;
	t_figure	*cur;
	t_roots		t;

	l = sub_vect3d(&rt->calc.p, &light->center);
	norm_vect3d(&l);
	cur = rt->figures;
	while (cur)
	{
		t = intersection(&l, &rt->calc.p, cur);
		if (t.closest_t > 0.0001 && t.closest_t < INF)
			return (1);
		cur = cur->next;
	}
	return (0);
}

int			calc_light(t_rtv1 *rt)
{
	double	i_diff;
	double	i_spec;
	int		color;
	t_light	*cur;

    get_intersection_point(rt);
    get_normal_of_figure(rt);
	color = 0;
	cur = rt->lights;
	while (cur)
	{
	    if (!in_shadow(rt, cur))
		{
			i_diff = get_diffusive(rt, cur);
			i_spec = get_specular(rt, cur);

			color = sum_color(color, calculate_color(rt->calc.closest_f->color, i_diff));
			color = sum_color(color, calculate_color(0xffffff, i_spec));
		}
            cur = cur->next;
	}
	return (color);
}
