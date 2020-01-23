//
// Created by Laila Shellie on 2020-01-22.
//

#include "../rtv1.h"

double		calc_light(t_rtv1 *rt, t_roots *t, t_figure *f,
		t_vect3d *ray, t_vect3d *cam_pos)
{
	double i;
	t_light	*cur;

	i = 0.2;
	cur = rt->lights;
	while (cur)
	{
		i += get_normal(f, ray, cam_pos, t, cur);
		cur = cur->next;
	//	printf("%lf\n", i);
	}
	return (i);
}