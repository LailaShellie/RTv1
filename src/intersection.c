//
// Created by Ivan on 20/01/2020.
//

#include "../rtv1.h"

int			intersect_cylinder(t_vect3d *cam_pos, t_vect3d *ray,
							   t_figure *cylinder, t_roots *t)
{
	double		a;
	double 		b;
	double 		c;
	double		d;

	t_vect3d	*v1;
	t_vect3d	*v2;


	v1 = new_vect3d();
	v2 = new_vect3d();


	init_vect3d(v1, -cylinder->direction->xyz[Y], cylinder->direction->xyz[X], 0);
	init_vect3d(v2, cylinder->direction->xyz[X] * cylinder->direction->xyz[Z],
			cylinder->direction->xyz[Y] * cylinder->direction->xyz[Z],
			-cylinder->direction->xyz[Y] * cylinder->direction->xyz[Y]
			- cylinder->direction->xyz[X] * cylinder->direction->xyz[X]);
	norm_vect(v1);
	norm_vect(v2);
	sub_vect3d(cylinder->oc, cylinder->center, cam_pos);
	a = dot_vect3d(v1, ray) * dot_vect3d(v1, ray)
			+ dot_vect3d(v2, ray) * dot_vect3d(v2, ray);
	b = 2.0 * (dot_vect3d(v1, cylinder->oc) * dot_vect3d(v1, ray)
			+ dot_vect3d(v2, cylinder->oc) * dot_vect3d(v2, ray));
	c = dot_vect3d(v1, cylinder->oc) * dot_vect3d(v1, cylinder->oc)
			+ dot_vect3d(v2, cylinder->oc)* dot_vect3d(v2, cylinder->oc)
			- cylinder->radius * cylinder->radius;
	d = b * b - 4.0 * a * c;
	if (d < 0)
		return (0);
	t->t1 = (-b + sqrt(d)) / (2.0 * a);
	t->t2 = (-b - sqrt(d)) / (2.0 * a);
	return (1);
}

int			intersect_cone(t_vect3d *cam_pos, t_vect3d *ray,
							   t_figure *cone, t_roots *t)
{
	double		a;
	double 		b;
	double 		c;
	double		d;

	t_vect3d	*v1;
	t_vect3d	*v2;
	t_vect3d	*v3;


	v1 = new_vect3d();
	v2 = new_vect3d();
	v3 = new_vect3d();


	init_vect3d(v3, cone->direction->xyz[X], cone->direction->xyz[Y], cone->direction->xyz[Z]);
	norm_vect(v3);

	init_vect3d(v1, -v3->xyz[Y], v3->xyz[X], 0);
	norm_vect(v1);

	init_vect3d(v2, v3->xyz[X] * v3->xyz[Z],
				v3->xyz[Y] * v3->xyz[Z],
				-v3->xyz[Y] * v3->xyz[Y]
				-v3->xyz[X] * v3->xyz[X]);
	norm_vect(v2);

	sub_vect3d(cone->oc, cone->center, cam_pos);
	a = dot_vect3d(v1, ray) * dot_vect3d(v1, ray) * (1 / tan(cone->radius))
		+ dot_vect3d(v2, ray) * dot_vect3d(v2, ray) * (1 / tan(cone->radius))
		- dot_vect3d(v3, ray) * dot_vect3d(v3, ray);
	b = 2.0 * (dot_vect3d(v1, cone->oc) * dot_vect3d(v1, ray) * (1 / tan(cone->radius))
			   + dot_vect3d(v2, cone->oc) * dot_vect3d(v2, ray) * (1 / tan(cone->radius))
			   - dot_vect3d(v3, ray) * dot_vect3d(v3, cone->oc));
	c = dot_vect3d(v1, cone->oc) * dot_vect3d(v1, cone->oc) * (1 / tan(cone->radius))
		+ dot_vect3d(v2, cone->oc) * dot_vect3d(v2, cone->oc) * (1 / tan(cone->radius))
		- dot_vect3d(v3, cone->oc) * dot_vect3d(v3, cone->oc);
	d = b * b - 4.0 * a * c;
	if (d < 0)
		return (0);
	t->t1 = (-b + sqrt(d)) / (2.0 * a);
	t->t2 = (-b - sqrt(d)) / (2.0 * a);
	return (1);
}

int			intersect_plane(t_vect3d *cam_pos, t_vect3d *ray,
								t_figure *plane, t_roots *t)
{
	double	a;
	double	b;

	sub_vect3d(plane->oc, plane->center, cam_pos);
	a = dot_vect3d(plane->oc, plane->direction);
	b = dot_vect3d(ray, plane->direction);
	if (b == 0)
		return (0);
	t->t1 = -a / b;
	t->t2 = -a / b;
	return (1);
}

int			intersect_sphere(t_vect3d *cam_pos, t_vect3d *ray,
								t_figure *sphere, t_roots *t)
{
	double		a;
	double 		b;
	double 		c;
	double		d;

	sub_vect3d(sphere->oc, sphere->center, cam_pos);
	a = dot_vect3d(ray, ray);
	b = 2.0 * dot_vect3d(sphere->oc, ray);
	c = dot_vect3d(sphere->oc, sphere->oc) - (sphere->radius * sphere->radius);
	d = b * b - 4.0 * a * c;
	if (d < 0)
		return (0);
	t->t1 = (-b + sqrt(d)) / (2.0 * a);
	t->t2 = (-b - sqrt(d)) / (2.0 * a);
	return (1);
}

int		intersection(t_vect3d *cam_pos, t_vect3d *ray, t_figure *figure, t_roots *t)
{
	if (figure->type == SPHERE)
		return (intersect_sphere(cam_pos, ray, figure, t));
	if (figure->type == PLANE)
		return (intersect_plane(cam_pos, ray, figure, t));
	if (figure->type == CONE)
		return (intersect_cone(cam_pos, ray, figure, t));
	if (figure->type == CYLINDER)
		return (intersect_cylinder(cam_pos, ray, figure, t));
	return (0);
}