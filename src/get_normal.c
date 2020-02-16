//
// Created by Ivan on 26/01/2020.
//

#include "rtv1.h"

void		normal_plane(t_rtv1 *rt, t_light *light)
{
    if (dot_vect3d(&rt->calc.closest_f->direction, &light->center) > 0)
        rt->calc.n = scale_vect3d(1, &rt->calc.closest_f->direction);
    else
        rt->calc.n = scale_vect3d(-1, &rt->calc.closest_f->direction);
}

void		normal_sphere(t_rtv1 *rt)
{
	rt->calc.n = sub_vect3d(&rt->calc.closest_f->center, &rt->calc.p);
	norm_vect3d(&rt->calc.n);
}

void       normal_cylinder_cone(t_rtv1 *rt)
{
    double      m;
    t_vect3d	x;
    t_vect3d	v;

    x = sub_vect3d(&rt->calc.closest_f->center, &rt->cam->center);
    v = scale_vect3d(rt->calc.t.closest_t, &rt->calc.closest_f->direction);
    m = dot_vect3d(&rt->calc.ray, &rt->calc.closest_f->direction)
            * rt->calc.t.closest_t + dot_vect3d(&x, &rt->calc.closest_f->direction);
    v = scale_vect3d(m, &rt->calc.closest_f->direction);
    rt->calc.n = sub_vect3d(&rt->calc.closest_f->center, &rt->calc.p);
    rt->calc.n = sub_vect3d(&v, &rt->calc.n);
    norm_vect3d(&rt->calc.n);
}

void		get_normal_of_figure(t_rtv1 *rt, t_light *light)
{

	if (rt->calc.closest_f->type == SPHERE)
		normal_sphere(rt);
	else if (rt->calc.closest_f->type == PLANE)
		normal_plane(rt, light);
	else if (rt->calc.closest_f->type == CYLINDER)
		normal_cylinder_cone(rt);
    else if (rt->calc.closest_f->type == CONE)
        normal_cylinder_cone(rt);
}

