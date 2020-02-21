//
// Created by Laila Shellie on 2020-01-22.
//

#include "rtv1.h"

void   get_intersection_point(t_rtv1 *rt)
{
    rt->calc.p = scale_vect3d(rt->calc.t.closest_t, &rt->calc.ray);
    rt->calc.p = add_vect3d(&rt->cam->center, &rt->calc.p);
}

int in_shadow(t_rtv1 *rt, t_light *light)
{
	t_vect3d	l;
	t_figure	*cur;

	cur = rt->figures;
	l = sub_vect3d(&rt->calc.p, &light->center);
	l = sub_vect3d(&rt->calc.n, &l);
	while (cur)
	{

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
