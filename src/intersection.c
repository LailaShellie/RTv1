/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   intersection.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lshellie <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/22 13:33:11 by lshellie          #+#    #+#             */
/*   Updated: 2020/02/22 13:33:12 by lshellie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

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
	return (t);
}

t_roots		intersect_cylinder(t_vect3d *ray, t_vect3d *o, t_figure *f)
{
	double		a;
	double		b;
	double		c;
	t_vect3d	oc;

	oc = sub_vect3d(&f->center, o);
	a = dot_vect3d(&f->v1, ray) * dot_vect3d(&f->v1, ray)
			+ dot_vect3d(&f->v2, ray) * dot_vect3d(&f->v2, ray);
	b = 2.0 * (dot_vect3d(&f->v1, &oc) * dot_vect3d(&f->v1, ray)
			+ dot_vect3d(&f->v2, &oc) * dot_vect3d(&f->v2, ray));
	c = dot_vect3d(&f->v1, &oc) * dot_vect3d(&f->v1, &oc)
			+ dot_vect3d(&f->v2, &oc) * dot_vect3d(&f->v2, &oc)
			- f->radius * f->radius;
	return (manage(a, b, c));
}

t_roots		intersect_cone(t_vect3d *ray, t_vect3d *o, t_figure *f)
{
	double		a;
	double		b;
	double		c;
	t_vect3d	oc;

	oc = sub_vect3d(&f->center, o);
	a = dot_vect3d(ray, ray)
			- (1 + f->radius * f->radius) * dot_vect3d(ray, &f->direction)
			* dot_vect3d(ray, &f->direction);
	b = 2.0 * (dot_vect3d(ray, &oc) - (1 + f->radius * f->radius) * dot_vect3d(ray, &f->direction) *
			dot_vect3d(&oc, &f->direction));
	c = dot_vect3d(&oc, &oc) - (1 + f->radius * f->radius) * dot_vect3d(&oc, &f->direction) *
			dot_vect3d(&oc, &f->direction);
	return (manage(a, b, c));
}

t_roots		intersect_plane(t_vect3d *ray, t_vect3d *o, t_figure *f)
{
	double		a;
	double		b;
	t_roots		t;
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
	double		b;
	double		c;
	t_vect3d	oc;

	oc = sub_vect3d(&f->center, o);
	a = dot_vect3d(ray, ray);
	b = 2.0 * dot_vect3d(&oc, ray);
	c = dot_vect3d(&oc, &oc) - (f->radius * f->radius);
	return (manage(a, b, c));
}

t_roots		intersection(t_vect3d *ray, t_vect3d *o, t_figure *figure)
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
