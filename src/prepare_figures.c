//
// Created by Ivan on 26/01/2020.
//

#include "rtv1.h"

void        calculate_cam_consts(t_rtv1 *rt)
{
    t_vect3d tmp;

    tmp = init_vect3d(0.0, 1.0, 0.0);
    rt->cam->v3 = sub_vect3d(&rt->cam->center, &rt->cam->direction);

    norm_vect3d(&rt->cam->v3);

    rt->cam->v1 = cross_vect3d(&rt->cam->v3, &tmp);
    norm_vect3d(&rt->cam->v1);

    rt->cam->v2 = cross_vect3d(&rt->cam->v1, &rt->cam->v3);
    norm_vect3d(&rt->cam->v2);
}

void		calculate_consts(t_rtv1 *rt, t_figure *f)
{
	norm_vect3d(&f->direction);
	f->v3 = init_vect3d(f->direction.x, f->direction.y, f->direction.z);
	f->v1 = init_vect3d(-f->v3.y, f->v3.x, 0);

	f->v2 = init_vect3d(f->v3.x * f->v3.z,
				f->v3.y * f->v3.z,
				-f->v3.y * f->v3.y
				-f->v3.x * f->v3.x);
}

double      get_max_light(t_rtv1 *rt)
{
    t_light	*cur;
    double  res;

    res = 0;
    cur = rt->lights;
    while (cur)
    {
        res += cur->i;
        cur = cur->next;
    }
    return (res);
}

void		prepare_figures(t_rtv1 *rt)
{
	t_figure	*cur;

	rt->total_light = get_max_light(rt);
	rt->total_light = (rt->total_light < 1 ? 1 : rt->total_light);
	calculate_cam_consts(rt);
	cur = rt->figures;
	while (cur)
	{
		calculate_consts(rt, cur);
		cur = cur->next;
	}
}