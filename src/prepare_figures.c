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
    printf("!!!\n");

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
	f->oc = sub_vect3d(&f->center, &rt->cam->center);
}

void		prepare_figures(t_rtv1 *rt)
{
	t_figure	*cur;

	calculate_cam_consts(rt);
	cur = rt->figures;
	while (cur)
	{
		calculate_consts(rt, cur);
		cur = cur->next;
	}
}