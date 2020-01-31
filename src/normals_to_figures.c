//
// Created by Laila Shellie on 2020-01-22.
//

#include "rtv1.h"

double	cos_cone(t_rtv1 *rt, t_figure *f, t_vect3d *ray,
					   t_roots *t, t_light *light)
{
	double	m;
	t_vect3d	x;
	t_vect3d	n;
	t_vect3d	p;
	t_vect3d	v;
	t_vect3d	l;
	double		k = 1;//(1 + f->radius * f->radius);

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
	double i;

	if (dot > 0)
		i = (light->i * dot) / (length_vect3d(&l) * length_vect3d(&n));
	else
		return (0);
	t_vect3d    r;
	double      r_dot_v1;
	t_vect3d    v1;

	v1 = sub_vect3d(&p, &rt->cam->center);
	r = init_vect3d(2 * n.x * dot - l.x, 2 * n.y * dot - l.y, 2 * n.z * dot - l.z);
	if (f->s > 10)
	{
		r_dot_v1 = dot_vect3d(&r, &v1);
		if (r_dot_v1 > 0)
			i += light->i * pow(r_dot_v1 / (length_vect3d(&r) * length_vect3d(&v1)), f->s);
	}
	return (i);
}

double	cos_cylinder(t_rtv1 *rt, t_figure *f, t_vect3d *ray,
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
	double i;

	if (dot > 0)
		i = (light->i * dot) / (length_vect3d(&l) * length_vect3d(&n));
	else
		return (0);
	t_vect3d    r;
	double      r_dot_v1;
	t_vect3d    v1;

	v1 = sub_vect3d(&p, &rt->cam->center);
	r = init_vect3d(2 * n.x * dot - l.x, 2 * n.y * dot - l.y, 2 * n.z * dot - l.z);
	if (f->s > 10)
	{
		r_dot_v1 = dot_vect3d(&r, &v1);
		if (r_dot_v1 > 0)
			i += light->i * pow(r_dot_v1 / (length_vect3d(&r) * length_vect3d(&v1)), f->s);
	}
	return (i);
}

double	cos_plane(t_rtv1 *rt, t_figure *f, t_vect3d *ray,
					 t_roots *t, t_light *light)
{
	t_vect3d	p;
	t_vect3d	n;
	t_vect3d	l;

	p = scale_vect3d(t->closest_t, ray);
	p = add_vect3d(&rt->cam->center, &p);
	n = get_normal_of_figure(rt, f, ray, t, light);
	l = sub_vect3d(&p, &light->center);

	double dot = dot_vect3d(&l, &n);

	if (dot > 0)
		return (light->i * dot) / (length_vect3d(&l) * length_vect3d(&n));
	return (0);
}

//if s != -1 {
//  R = 2*N*dot(N, L) - L
//  r_dot_v = dot(R, V)
//  if r_dot_v > 0
//      i += light.intensity*pow(r_dot_v/(length(R)*length(V)), s)

double	cos_sphere(t_rtv1 *rt, t_figure *f, t_vect3d *ray,
		t_roots *t, t_light *light)
{
	t_vect3d	p;
	t_vect3d	n;
	t_vect3d	l;
	double      i;

	p = scale_vect3d(t->closest_t, ray);
	p = add_vect3d(&rt->cam->center, &p);
	n = get_normal_of_figure(rt, f, ray, t, light);
	l = sub_vect3d(&p, &light->center);

	double dot = dot_vect3d(&l, &n);

	if (dot > 0)
		i = light->i * (dot) / (length_vect3d(&l) * length_vect3d(&n));
    else
        return (0);
	t_vect3d    r;
	double      r_dot_v;
	t_vect3d    v;

	v = sub_vect3d(&p, &rt->cam->center);
	r = init_vect3d(2 * n.x * dot - l.x, 2 * n.y * dot - l.y, 2 * n.z * dot - l.z);
	if (f->s > 10)
    {
	    r_dot_v = dot_vect3d(&r, &v);
	    if (r_dot_v > 0)
            i += light->i * pow(r_dot_v / (length_vect3d(&r) * length_vect3d(&v)), f->s);
    }
	return (i);
}

double		get_normal(t_rtv1 *rt, t_figure *f, t_vect3d *ray, t_roots *t, t_light *light)
{
	if (f->type == SPHERE)
		return (cos_sphere(rt, f, ray, t, light));
	else if (f->type == PLANE)
		return (cos_plane(rt, f, ray, t, light));
	else if (f->type == CYLINDER)
		return (cos_cylinder(rt, f, ray, t, light));
	else if (f->type == CONE)
		return (cos_cone(rt, f, ray, t, light));
	return (0);
}
