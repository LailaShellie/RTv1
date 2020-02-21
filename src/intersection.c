//
// Created by Ivan on 20/01/2020.
//

#include "rtv1.h"

t_roots		manage(double a, double b, double c)
{
	t_roots		t;
	double		d;

	t.t1 = INF;
	t.t2 = INF;
	t.closest_t = INF;
	d = b * b - 4.0 * a * c;
	if (d < 0)
		return (t);
	t.t1 = (-b + sqrt(d)) / (2.0 * a);
	t.t2 = (-b - sqrt(d)) / (2.0 * a);
	t.closest_t = t.t1 < t.t2 ? t.t1 : t.t2;
	return (t);
}

t_roots		intersect_cylinder(t_vect3d *ray, t_vect3d *o, t_figure *f)
{
	double		a;
	double 		b;
	double 		c;
	t_vect3d	oc;

	oc = sub_vect3d(&f->center, o);
	a = dot_vect3d(&f->v1, ray) * dot_vect3d(&f->v1, ray)
			+ dot_vect3d(&f->v2, ray) * dot_vect3d(&f->v2, ray);
	b = 2.0 * (dot_vect3d(&f->v1, &oc) * dot_vect3d(&f->v1, ray)
			+ dot_vect3d(&f->v2, &oc) * dot_vect3d(&f->v2, ray));
	c = dot_vect3d(&f->v1, &oc) * dot_vect3d(&f->v1, &oc)
			+ dot_vect3d(&f->v2, &oc)* dot_vect3d(&f->v2, &oc)
			- f->radius * f->radius;
	return (manage(a, b, c));
}

t_roots		intersect_cone(t_vect3d *ray, t_vect3d *o, t_figure *f)
{
	double		a;
	double 		b;
	double 		c;
	t_vect3d	oc;

	oc = sub_vect3d(&f->center, o);
	double v1_dot_ray = dot_vect3d(&f->v1, ray);
	double v2_dot_ray = dot_vect3d(&f->v2, ray);
	double v3_dot_ray = dot_vect3d(&f->v3, ray);

	a = pow(v1_dot_ray, 2) + pow(v2_dot_ray, 2) - pow(v3_dot_ray, 2);
	b = 2.0 * (v1_dot_ray * dot_vect3d(&f->v1, &oc)
			   + v2_dot_ray * dot_vect3d(&f->v2, &oc)
			   - v3_dot_ray * dot_vect3d(&f->v3, &oc));
	c = pow(dot_vect3d(&f->v1, &oc), 2)
			+ pow(dot_vect3d(&f->v2, &oc), 2)
			- pow(dot_vect3d(&f->v3, &oc), 2);
	return (manage(a, b, c));
}

t_roots		intersect_plane(t_vect3d *ray, t_vect3d *o, t_figure *f)
{
	double	a;
	double	b;
	t_roots t;
	t_vect3d	oc;

	oc = sub_vect3d(&f->center, o);
	t.t1 = INF;
	t.t2 = INF;
	t.closest_t = INF;
	a = dot_vect3d(&oc, &f->direction);
	b = dot_vect3d(ray, &f->direction);
	if (b == 0)
		return (t);
    t.t1 = -a / b;
    t.t2 = -a / b;
	t.closest_t = t.t1;
	return (t);
}

t_roots		intersect_sphere(t_vect3d *ray, t_vect3d *o, t_figure *f)
{
	double		a;
	double 		b;
	double 		c;
	t_vect3d	oc;

	oc = sub_vect3d(&f->center, o);
	a = dot_vect3d(ray, ray);
	b = 2.0 * dot_vect3d(&oc, ray);
	c = dot_vect3d(&oc, &oc) - (f->radius * f->radius);
	return (manage(a, b, c));
}

t_roots				intersection(t_vect3d *ray, t_vect3d *o, t_figure *figure)
{
	t_roots t;

	t.t1 = INF;
	t.t2 = INF;
	t.closest_t = INF;
	if (figure->type == SPHERE)
		return (intersect_sphere(ray, o, figure));
	if (figure->type == PLANE)
		return (intersect_plane(ray, o, figure));
	if (figure->type == CONE)
		return (intersect_cone(ray, o, figure));
	if (figure->type == CYLINDER)
		return (intersect_cylinder(ray, o, figure));
	return (t);
}
