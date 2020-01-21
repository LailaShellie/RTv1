//
// Created by Ivan on 20/01/2020.
//

#include "../rtv1.h"

int			intersect_cylinder(t_vect3d *cam_pos, t_vect3d *ray,
							   t_figure *cylinder, t_roots *t)
{
	return (0);
}

int			intersect_cone(t_vect3d *cam_pos, t_vect3d *ray,
							   t_figure *cone, t_roots *t)
{
	return (0);
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
	//printf("%lf %lf\n", t->t1, t->t2);
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