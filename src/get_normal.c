//
// Created by Ivan on 26/01/2020.
//

#include "rtv1.h"

t_vect3d		normal_plane(t_figure *plane, t_vect3d *light)
{
	if (dot_vect3d(&plane->direction, light) > 0)
		return (scale_vect3d(1, &plane->direction));
	return (scale_vect3d(-1, &plane->direction));
}

t_vect3d		normal_sphere(t_figure *sphere, t_vect3d *p)
{
	t_vect3d	n;

	n = sub_vect3d(&sphere->center, p);
	norm_vect3d(&n);
	return (n);
}

t_vect3d		get_normal_of_figure(t_rtv1 *rt, t_figure *f, t_vect3d *ray, t_roots *t, t_vect3d *light)
{
	t_vect3d	p;

	p = scale_vect3d(t->closest_t, ray);
	p = add_vect3d(&rt->cam->center, &p);
	if (f->type == SPHERE)
		return (normal_sphere(f, &p));
	else if (f->type == PLANE)
		return (normal_plane(f, light));
//	else if (f->type == CYLINDER)
//		return (cos_cylinder(rt, f, ray, &p));
//	else if (f->type == CONE)
//		return (cos_cone(rt, f, ray, &p));
}

