//
// Created by Ivan on 26/01/2020.
//

#include "rtv1.h"

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

	cur = rt->figures;
	while (cur)
	{
		calculate_consts(rt, cur);
		cur = cur->next;
	}
}