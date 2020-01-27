//
// Created by Laila Shellie on 2020-01-22.
//

#include "../rtv1.h"

double		calc_light(t_rtv1 *rt, t_roots *t, t_figure *f,
		t_vect3d *ray)
{
	double i;
	t_light	*cur;

//	if s != -1 {
//		R = 2*N*dot(N, L) - L
//		r_dot_v = dot(R, V)
//		if r_dot_v > 0
//		i += light.intensity*pow(r_dot_v/(length(R)*length(V)), s)


	i = 0.2;
	cur = rt->lights;
	while (cur)
	{
		i += get_normal(rt, f, ray, t, cur);
	//	if (f->s != -1)
		//	i += get_blare();
		cur = cur->next;
	}
	return (i);
}

int 		check_light(t_rtv1 *rt, t_vect3d *p, t_light *light)
{
	t_vect3d	l;
	t_roots		t;
	t_figure	*cur;

	cur = rt->figures;
	sub_vect3d(&l, &light->center, p);
	norm_vect(&l);
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