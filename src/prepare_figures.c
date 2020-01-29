//
// Created by Ivan on 26/01/2020.
//

#include "rtv1.h"

void		calculate_consts(t_rtv1 *rt, t_figure *f)
{
	norm_vect(&f->direction);
	init_vect3d(&f->v3, f->direction.x, f->direction.y, f->direction.z);

	init_vect3d(&f->v1, -f->v3.y, f->v3.x, 0);
	norm_vect(&f->v1);

	init_vect3d(&f->v2, f->v3.x * f->v3.z,
				f->v3.y * f->v3.z,
				-f->v3.y * f->v3.y
				-f->v3.x * f->v3.x);
	norm_vect(&f->v2);

	sub_vect3d(&f->oc, &f->center, &rt->cam->center);
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