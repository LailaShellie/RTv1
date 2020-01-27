//
// Created by Ivan on 26/01/2020.
//

#include "../rtv1.h"

t_vect3d		normal_plane(t_figure *plane, t_vect3d *p)
{
	t_vect3d	n;

	sub_vect3d(&n, &sphere->center, p);
	norm_vect(&n);
	return (n);
}

t_vect3d		normal_sphere(t_figure *sphere, t_vect3d *p)
{
	t_vect3d	n;

	sub_vect3d(&n, &sphere->center, p);
	norm_vect(&n);
	return (n);
}

t_vect3d		get_normal_of_figure(t_rtv1 *rt, t_figure *f, t_vect3d *ray, t_roots *t)
{
	t_vect3d	p;

	init_vect3d(&p, t->closest_t * ray->x, t->closest_t * ray->y, t->closest_t * ray->z);
	if (f->type == SPHERE)
		return (normal_sphere(f, &p));
	else if (f->type == PLANE)
		return (normal_plane(f, &p));
//	else if (f->type == CYLINDER)
//		return (cos_cylinder(rt, f, ray, &p));
//	else if (f->type == CONE)
//		return (cos_cone(rt, f, ray, &p));
}

