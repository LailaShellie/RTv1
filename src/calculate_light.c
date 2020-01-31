//
// Created by Laila Shellie on 2020-01-22.
//

#include "rtv1.h"

int			calc_light(t_rtv1 *rt, t_roots *t, t_figure *f,
		t_vect3d *ray)
{
	double	i_diff;
	double	i_spec;
	int		color;

	t_light	*cur;
	color = f->color;
	i_diff = 0.0;
	i_spec = 0.0;
	cur = rt->lights;
	while (cur)
	{
		i_diff += get_diffusive(rt, f, ray, t, cur);
		i_spec += get_specular(rt, f, ray, t, cur);
		cur = cur->next;
	}
	return (sum_color(calculate_color(f->color, i_diff), calculate_color(0x10101, i_spec)));
}

int 		check_light(t_rtv1 *rt, t_vect3d *p, t_light *light)
{
	t_vect3d	l;
	t_roots		t;
	t_figure	*cur;

	cur = rt->figures;
	l = sub_vect3d(&light->center, p);
	norm_vect3d(&l);
	while (cur)
	{
		if (intersection(p, &l, cur, &t))
		{
			if (t.t2 > 0 || t.t1 > 0)
				return (1);
		}
		cur = cur->next;
	}
	return (0);
}