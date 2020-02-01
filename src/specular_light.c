//
// Created by Laila Shellie on 2020-01-31.
//

#include "rtv1.h"

#define SPEC 100

double	spec_light_cone(t_rtv1 *rt, t_figure *f, t_vect3d *ray,
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

	double dot = dot_vect3d(&l, &n);
	double i = 0;

	t_vect3d    r;
	double      r_dot_v1;
	t_vect3d    v1;

	v1 = sub_vect3d(&p, &rt->cam->center);
	r = init_vect3d(2 * n.x * dot - l.x, 2 * n.y * dot - l.y, 2 * n.z * dot - l.z);
	r_dot_v1 = dot_vect3d(&r, &v1);
	if (r_dot_v1 > 0)
		i += light->i * pow(r_dot_v1 / (length_vect3d(&r) * length_vect3d(&v1)), SPEC);
	return (i);
}

double	spec_light_cylinder(t_rtv1 *rt, t_figure *f, t_vect3d *ray,
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

	double dot = dot_vect3d(&l, &n);
	double i = 0;

	t_vect3d    r;
	double      r_dot_v1;
	t_vect3d    v1;

	v1 = sub_vect3d(&p, &rt->cam->center);
	r = init_vect3d(2 * n.x * dot - l.x, 2 * n.y * dot - l.y, 2 * n.z * dot - l.z);
	r_dot_v1 = dot_vect3d(&r, &v1);
	if (r_dot_v1 > 0)
		i += light->i * pow(r_dot_v1 / (length_vect3d(&r) * length_vect3d(&v1)), SPEC);
	return (i);
}

double	spec_light_plane(t_rtv1 *rt, t_figure *f, t_vect3d *ray,
						   t_roots *t, t_light *light)
{
	t_vect3d	p;
	t_vect3d	n;
	t_vect3d	l;

	p = scale_vect3d(t->closest_t, ray);
	p = add_vect3d(&rt->cam->center, &p);
	n = get_normal_of_figure(rt, f, ray, t, &light->center);
	l = sub_vect3d(&p, &light->center);

	double dot = dot_vect3d(&l, &n);

	double		i = 0;
	t_vect3d    r;
	double      r_dot_v;
	t_vect3d    v;

	v = sub_vect3d(&p, &rt->cam->center);
	r = init_vect3d(2 * n.x * dot - l.x, 2 * n.y * dot - l.y, 2 * n.z * dot - l.z);
	r_dot_v = dot_vect3d(&r, &v);
	if (r_dot_v > 0)
		i = light->i * pow(r_dot_v / (length_vect3d(&r) * length_vect3d(&v)), SPEC);
	return (i);
}

double	spec_light_sphere(t_rtv1 *rt, t_figure *f, t_vect3d *ray,
							t_roots *t, t_light *light)
{
	t_vect3d	p;
	t_vect3d	n;
	t_vect3d	l;
	double      i = 0;

	p = scale_vect3d(t->closest_t, ray);
	p = add_vect3d(&rt->cam->center, &p);
	n = get_normal_of_figure(rt, f, ray, t, &light->center);
	l = sub_vect3d(&p, &light->center);

	double dot = dot_vect3d(&l, &n);

	t_vect3d    r;
	double      r_dot_v;
	t_vect3d    v;

	v = sub_vect3d(&p, &rt->cam->center);
	r = init_vect3d(2 * n.x * dot - l.x, 2 * n.y * dot - l.y, 2 * n.z * dot - l.z);
	r_dot_v = dot_vect3d(&r, &v);
	if (r_dot_v > 0)
	{
		i += light->i * pow(r_dot_v / (length_vect3d(&r) * length_vect3d(&v)), SPEC);
		if (calculate_color(0xffffff, i) <= 0xfffff)
			i = 0;
	}
	return (i);
}

double		get_specular(t_rtv1 *rt, t_figure *f, t_vect3d *ray, t_roots *t, t_light *light)
{
	if (f->type == SPHERE)
		return (spec_light_sphere(rt, f, ray, t, light));
	else if (f->type == PLANE)
		return (spec_light_plane(rt, f, ray, t, light));
	else if (f->type == CYLINDER)
		return (spec_light_cylinder(rt, f, ray, t, light));
	else if (f->type == CONE)
		return (spec_light_cone(rt, f, ray, t, light));
	return (0);
}