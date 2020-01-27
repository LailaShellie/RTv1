//
// Created by Laila Shellie on 2020-01-22.
//

#include "../rtv1.h"

double	cos_cone(t_rtv1 *rt, t_figure *f, t_vect3d *ray,
					   t_roots *t, t_light *light)
{
	double	m;
	t_vect3d	x;
	t_vect3d	n;
	t_vect3d	p;
	t_vect3d	v;
	t_vect3d	l;
	double		k = 1 / tan(f->radius);

	sub_vect3d(&x, &f->center, &rt->cam->center);
	norm_vect(&f->direction);
	init_vect3d(&v,
				t->closest_t * f->direction.x,
				t->closest_t * f->direction.y,
				t->closest_t * f->direction.z);
	m = dot_vect3d(ray, &f->direction) * t->closest_t + dot_vect3d(&x, &f->direction);
	init_vect3d(&p, t->closest_t * ray->x,
				t->closest_t * ray->y,
				t->closest_t * ray->z);
	init_vect3d(&v, (k) * m * f->direction.x,
			(k) * m * f->direction.y,
			(k) * m * f->direction.z);
	sub_vect3d(&n, &f->center, &p);
	sub_vect3d(&n, &v, &n);
	norm_vect(&n);
	init_vect3d(&l, light->center.x, light->center.y, light->center.z);
	sub_vect3d(&l, &p, &l);

	double dot = dot_vect3d(&l, &n);

	if (dot > 0)
		return (light->i * dot / 1.4) / (length_vect3d(&l) * length_vect3d(&n));
	return (0);
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

	sub_vect3d(&x, &f->center, &rt->cam->center);
	norm_vect(&f->direction);
	init_vect3d(&v,
			t->closest_t * f->direction.x,
			t->closest_t * f->direction.y,
			t->closest_t * f->direction.z);
	m = dot_vect3d(ray, &f->direction) * t->closest_t + dot_vect3d(&x, &f->direction);
	init_vect3d(&p, t->closest_t * ray->x,
				t->closest_t * ray->y,
				t->closest_t * ray->z);
	init_vect3d(&v, m * f->direction.x, m * f->direction.y, m * f->direction.z);
	sub_vect3d(&n, &f->center, &p);
	sub_vect3d(&n, &v, &n);
	norm_vect(&n);
	init_vect3d(&l, light->center.x, light->center.y, light->center.z);
	sub_vect3d(&l, &p, &l);

	double dot = dot_vect3d(&l, &n);

	if (dot > 0)
		return (light->i * dot / 1.4) / (length_vect3d(&l) * length_vect3d(&n));
	return (0);
}

double	cos_plane(t_rtv1 *rt, t_figure *f, t_vect3d *ray,
					 t_roots *t, t_light *light)
{
	t_vect3d	p;
	t_vect3d	n1;
	t_vect3d	l;
	t_vect3d	p1;

	init_vect3d(&p, t->closest_t * ray->x,
					t->closest_t * ray->y,
					t->closest_t * ray->z);
	add_vect3d(&p, &rt->cam->center, &p);
	init_vect3d(&n1, f->direction.x,
					f->direction.y,
					f->direction.z);
	norm_vect(&n1);
	init_vect3d(&l, light->center.x,
					light->center.y,
					light->center.z);
	sub_vect3d(&l, &p, &l);
	init_vect3d(&p1, -p.x, -p.y, -p.z);


	double dot = dot_vect3d(&p1, &n1);

	if (dot < 0)
		init_vect3d(&n1, -n1.x, -n1.y, -n1.z);
	dot = dot_vect3d(&l, &n1);
	if (dot > 0)
		return (light->i * dot / 1.4) / (length_vect3d(&l) * length_vect3d(&n1));
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

	norm_vect(ray);
	init_vect3d(&p, t->closest_t * ray->x,
			t->closest_t * ray->y,
			t->closest_t * ray->z);
	add_vect3d(&p, &rt->cam->center, &p);
	sub_vect3d(&n, &f->center, &p);
	norm_vect(&n);
	init_vect3d(&l, light->center.x,
				light->center.y,
				light->center.z);
	sub_vect3d(&l, &p, &l);

	double dot = dot_vect3d(&l, &n);

	if (dot > 0)
		i = light->i * (dot / 1.4) / (length_vect3d(&l) * length_vect3d(&n));
    else
        return (0);
	t_vect3d    r;
	double      r_dot_v;
	t_vect3d    v;

	sub_vect3d(&v, &p, &rt->cam->center);
	init_vect3d(&r, 2 * n.x * dot - l.x, 2 * n.y * dot - l.y, 2 * n.z * dot - l.z);
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
