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
	t_vect3d p;

    p = scale_vect3d(t->closest_t, ray);
    p = add_vect3d(&rt->cam->center, &p);
	color = 0;
	i_diff = 0.0;
	i_spec = 0.0;
	cur = rt->lights;
	while (cur)
	{
	    i_diff = get_diffusive(rt, f, ray, t, cur);
	    i_spec = get_specular(rt, f, ray, t, cur);

	    color = sum_color(color, calculate_color(f->color, i_diff));
	    color = sum_color(color, calculate_color(0xffffff, i_spec));
		cur = cur->next;
	}
	return (color);
}
