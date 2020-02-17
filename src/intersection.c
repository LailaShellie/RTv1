//
// Created by Ivan on 20/01/2020.
//

#include "rtv1.h"

int			intersect_cylinder(t_rtv1 *rt, t_figure *f)
{
	double		a;
	double 		b;
	double 		c;
	double		d;

	a = dot_vect3d(&f->v1, &rt->calc.ray) * dot_vect3d(&f->v1, &rt->calc.ray)
			+ dot_vect3d(&f->v2, &rt->calc.ray) * dot_vect3d(&f->v2, &rt->calc.ray);
	b = 2.0 * (dot_vect3d(&f->v1, &rt->calc.oc) * dot_vect3d(&f->v1, &rt->calc.ray)
			+ dot_vect3d(&f->v2, &rt->calc.oc) * dot_vect3d(&f->v2, &rt->calc.ray));
	c = dot_vect3d(&f->v1, &rt->calc.oc) * dot_vect3d(&f->v1, &rt->calc.oc)
			+ dot_vect3d(&f->v2, &rt->calc.oc)* dot_vect3d(&f->v2, &rt->calc.oc)
			- f->radius * f->radius;
	d = b * b - 4.0 * a * c;
	if (d < 0)
		return (0);
    rt->calc.t.t1 = (-b + sqrt(d)) / (2.0 * a);
    rt->calc.t.t2 = (-b - sqrt(d)) / (2.0 * a);
	return (1);
}

int			intersect_cone(t_rtv1 *rt, t_figure *f)
{
	double		a;
	double 		b;
	double 		c;
	double		d;

	double 		k = (1 + f->radius * f->radius);

	double v1_dot_ray = dot_vect3d(&f->v1, &rt->calc.ray);
	double v2_dot_ray = dot_vect3d(&f->v2, &rt->calc.ray);
	double v3_dot_ray = dot_vect3d(&f->v3, &rt->calc.ray);

	a = pow(v1_dot_ray, 2) * k + pow(v2_dot_ray, 2) * k - pow(v3_dot_ray, 2);
	b = 2.0 * (v1_dot_ray * dot_vect3d(&f->v1, &rt->calc.oc) * k
			   + v2_dot_ray * dot_vect3d(&f->v2, &rt->calc.oc) * k
			   - v3_dot_ray * dot_vect3d(&f->v3, &rt->calc.oc));
	c = pow(dot_vect3d(&f->v1, &rt->calc.oc), 2) * k
			+ pow(dot_vect3d(&f->v2, &rt->calc.oc), 2) * k
			- pow(dot_vect3d(&f->v3, &rt->calc.oc), 2);
	d = b * b - 4.0 * a * c;
	if (d < 0)
		return (0);
    rt->calc.t.t1 = (-b + sqrt(d)) / (2.0 * a);
    rt->calc.t.t2 = (-b - sqrt(d)) / (2.0 * a);
	return (1);
}

int			intersect_plane(t_rtv1 *rt, t_figure *f)
{
	double	a;
	double	b;

	a = dot_vect3d(&rt->calc.oc, &f->direction);
	b = dot_vect3d(&rt->calc.ray, &f->direction);
	if (b == 0)
		return (0);
    rt->calc.t.t1 = -a / b;
    rt->calc.t.t2 = -a / b;
	return (1);
}

int			intersect_sphere(t_rtv1 *rt, t_figure *f)
{
	double		a;
	double 		b;
	double 		c;
	double		d;

	a = dot_vect3d(&rt->calc.ray, &rt->calc.ray);
	b = 2.0 * dot_vect3d(&rt->calc.oc, &rt->calc.ray);
	c = dot_vect3d(&rt->calc.oc, &rt->calc.oc) - (f->radius * f->radius);
	d = b * b - 4.0 * a * c;
	if (d < 0)
		return (0);
	rt->calc.t.t1 = (-b + sqrt(d)) / (2.0 * a);
    rt->calc.t.t2 = (-b - sqrt(d)) / (2.0 * a);
	return (1);
}

int					intersection(t_rtv1 *rt, t_figure *figure)
{
	if (figure->type == SPHERE)
		return (intersect_sphere(rt, figure));
	if (figure->type == PLANE)
		return (intersect_plane(rt, figure));
	if (figure->type == CONE)
		return (intersect_cone(rt, figure));
	if (figure->type == CYLINDER)
		return (intersect_cylinder(rt, figure));
	return (0);
}
