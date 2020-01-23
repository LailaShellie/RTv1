//
// Created by Laila Shellie on 2020-01-22.
//

#include "../rtv1.h"

double	cos_cylinder(t_figure *f, t_vect3d *ray,
					t_vect3d *cam_pos, t_roots *t, t_light *light)
{
	double	m;
	t_vect3d	x;

	sub_vect3d(&x, f->center, cam_pos);
	m = dot_vect3d(ray, f->direction) * t->closest_t + dot_vect3d(&x, f->direction);

}

double	cos_plane(t_figure *f, t_vect3d *ray,
					 t_vect3d *cam_pos, t_roots *t, t_light *light)
{
	t_vect3d	*p;
	t_vect3d	*n1;
	t_vect3d	*l;
	t_vect3d	*p1;

	p = new_vect3d();
	p1 = new_vect3d();
	init_vect3d(p, t->closest_t * ray->xyz[X],
					t->closest_t * ray->xyz[Y],
					t->closest_t * ray->xyz[Z]);
	add_vect3d(p, cam_pos, p);
	n1 = new_vect3d();
	init_vect3d(n1, f->direction->xyz[X],
					f->direction->xyz[Y],
					f->direction->xyz[Z]);
	norm_vect(n1);
	l = new_vect3d();
	init_vect3d(l, light->ccenter->xyz[X],
					light->ccenter->xyz[Y],
					light->ccenter->xyz[Z]);
	sub_vect3d(l, p, l);
	init_vect3d(p1, -p->xyz[X], -p->xyz[Y], -p->xyz[Z]);


	double dot = dot_vect3d(p1, n1);

	if (dot < 0)
		init_vect3d(n1, -n1->xyz[X], -n1->xyz[Y], -n1->xyz[Z]);
	dot = dot_vect3d(l, n1);
	if (dot > 0)
		return (light->i * dot) / (length_vect3d(l) * length_vect3d(n1));
	return (0);
}

double	cos_sphere(t_figure *f, t_vect3d *ray,
		t_vect3d *cam_pos, t_roots *t, t_light *light)
{
	t_vect3d	*p;
	t_vect3d	*n;
	t_vect3d	*l;

	p = new_vect3d();
	init_vect3d(p, t->closest_t * ray->xyz[X],
			t->closest_t * ray->xyz[Y],
			t->closest_t * ray->xyz[Z]);
	add_vect3d(p, cam_pos, p);
	n = new_vect3d();
	sub_vect3d(n, f->center, p);
	norm_vect(n);
	l = new_vect3d();
	init_vect3d(l, light->ccenter->xyz[X],
				light->ccenter->xyz[Y],
				light->ccenter->xyz[Z]);
	sub_vect3d(l, p, l);

	double dot = dot_vect3d(l, n);

	if (dot > 0)
		return (light->i * dot) / (length_vect3d(l) * length_vect3d(n));
	return (0);
}

double		get_normal(t_figure *f, t_vect3d *ray,
		t_vect3d *cam_pos, t_roots *t, t_light *light)
{
	if (f->type == SPHERE)
		return (cos_sphere(f, ray, cam_pos, t, light));
	else if (f->type == PLANE)
		return (cos_plane(f, ray, cam_pos, t, light));
	return (0);
}