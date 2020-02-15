//
// Created by Laila Shellie on 2020-01-22.
//

#include "rtv1.h"

double	diff_light_cone(t_rtv1 *rt, t_figure *f, t_vect3d *ray,
					   t_roots *t, t_light *light)
{
	double	m;
	t_vect3d	x;
	t_vect3d	n;
	t_vect3d	p;
	t_vect3d	v;
	t_vect3d	l;
	double		k = 1;

	x = sub_vect3d(&f->center, &rt->cam->center);
	v = scale_vect3d(t->closest_t, &f->direction);

	m = dot_vect3d(ray, &f->direction) * t->closest_t + dot_vect3d(&x, &f->direction);
	p = scale_vect3d(t->closest_t, ray);
	p = add_vect3d(&rt->cam->center, &p);
	v = scale_vect3d(k * k * m, &f->direction);
	n = sub_vect3d(&f->center, &p);
	n = sub_vect3d(&v, &n);
	norm_vect3d(&n);
	l = sub_vect3d(&p, &light->center);
    norm_vect3d(&l);

	double dot = dot_vect3d(&l, &n);

	if (dot > 0)
        return (light->i * dot / rt->total_light);
	return (0);
}

double	diff_light_cylinder(t_rtv1 *rt, t_figure *f, t_vect3d *ray,
					   t_roots *t, t_light *light)
{
	double	m;
	t_vect3d	x;
	t_vect3d	n;
	t_vect3d	p;
	t_vect3d	v;
	t_vect3d	l;

	x = sub_vect3d(&f->center, &rt->cam->center);
	v = scale_vect3d(t->closest_t, &f->direction);

	m = dot_vect3d(ray, &f->direction) * t->closest_t + dot_vect3d(&x, &f->direction);
	p = scale_vect3d(t->closest_t, ray);
	p = add_vect3d(&rt->cam->center, &p);
	v = scale_vect3d(m, &f->direction);
	n = sub_vect3d(&f->center, &p);
	n = sub_vect3d(&v, &n);
	norm_vect3d(&n);

	l = sub_vect3d(&p, &light->center);
    norm_vect3d(&l);

	double dot = dot_vect3d(&l, &n);

	if (dot > 0)
        return (light->i * dot / rt->total_light);
	return (0);
}

double	diff_light_plane(t_rtv1 *rt, t_figure *f, t_vect3d *ray,
					 t_roots *t, t_light *light)
{
	t_vect3d	p;
	t_vect3d	n;
	t_vect3d	l;

	p = scale_vect3d(t->closest_t, ray);
	p = add_vect3d(&rt->cam->center, &p);
	n = get_normal_of_figure(rt, f, ray, t, &light->center);
	l = sub_vect3d(&p, &light->center);
    norm_vect3d(&l);

	double dot = dot_vect3d(&l, &n);

	if (dot > 0)
		return (light->i * dot / rt->total_light);
	return (0);
}

double	diff_light_sphere(t_rtv1 *rt, t_figure *f, t_vect3d *ray,
		t_roots *t, t_light *light)
{
	t_vect3d	p;
	t_vect3d	n;
	t_vect3d	l;

	p = scale_vect3d(t->closest_t, ray);
	p = add_vect3d(&rt->cam->center, &p);
	n = get_normal_of_figure(rt, f, ray, t, &light->center);
	l = sub_vect3d(&p, &light->center);
	norm_vect3d(&l);

	double dot = dot_vect3d(&l, &n);

	if (dot > 0)
        return (light->i * dot / rt->total_light);
	return (0);
}

double		get_diffusive(t_rtv1 *rt, t_figure *f, t_vect3d *ray, t_roots *t, t_light *light)
{
	if (f->type == SPHERE)
		return (diff_light_sphere(rt, f, ray, t, light));
	else if (f->type == PLANE)
		return (diff_light_plane(rt, f, ray, t, light));
	else if (f->type == CYLINDER)
		return (diff_light_cylinder(rt, f, ray, t, light));
	else if (f->type == CONE)
		return (diff_light_cone(rt, f, ray, t, light));
	return (0);
}
