/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_normal.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lshellie <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/22 13:27:15 by lshellie          #+#    #+#             */
/*   Updated: 2020/02/22 13:27:15 by lshellie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"

void	normal_plane(t_rtv1 *rt)
{
	t_vect3d	cam_p;

	cam_p = sub_vect3d(&rt->calc.p, &rt->cam->center);
	norm_vect3d(&cam_p);
	if (dot_vect3d(&rt->calc.closest_f->direction, &cam_p) > 0)
		rt->calc.n = scale_vect3d(1, &rt->calc.closest_f->direction);
	else
		rt->calc.n = scale_vect3d(-1, &rt->calc.closest_f->direction);
}

void	normal_sphere(t_rtv1 *rt)
{
	t_vect3d	cam_p;

	cam_p = sub_vect3d(&rt->calc.p, &rt->cam->center);
	norm_vect3d(&cam_p);
	rt->calc.n = sub_vect3d(&rt->calc.closest_f->center, &rt->calc.p);
	norm_vect3d(&rt->calc.n);
	if (dot_vect3d(&rt->calc.n, &cam_p) < 0)
		rt->calc.n = scale_vect3d(-1, &rt->calc.n);
}

void	normal_cone(t_rtv1 *rt)
{
	double		m;
	t_vect3d	pc;
	t_vect3d	v;
	t_vect3d	x;
	t_vect3d	cam_p;

	cam_p = sub_vect3d(&rt->calc.p, &rt->cam->center);
	norm_vect3d(&cam_p);
	x = sub_vect3d(&rt->calc.closest_f->center, &rt->cam->center);
	pc = sub_vect3d(&rt->calc.closest_f->center, &rt->calc.p);
	m = dot_vect3d(&rt->calc.ray, &rt->calc.closest_f->direction)
		* rt->calc.t.closest_t
		+ dot_vect3d(&x, &rt->calc.closest_f->direction);
	v = scale_vect3d(m * (1 + rt->calc.closest_f->radius
			* rt->calc.closest_f->radius),
			&rt->calc.closest_f->direction);
	rt->calc.n = sub_vect3d(&v, &pc);
	norm_vect3d(&rt->calc.n);
	if (dot_vect3d(&rt->calc.n, &cam_p) < 0)
		rt->calc.n = scale_vect3d(-1, &rt->calc.n);
}

void	normal_cylinder(t_rtv1 *rt)
{
	double		m;
	t_vect3d	x;
	t_vect3d	v;
	t_vect3d	cam_p;

	cam_p = sub_vect3d(&rt->calc.p, &rt->cam->center);
	norm_vect3d(&cam_p);
	x = sub_vect3d(&rt->calc.closest_f->center, &rt->cam->center);
	v = scale_vect3d(rt->calc.t.closest_t, &rt->calc.closest_f->direction);
	m = dot_vect3d(&rt->calc.ray, &rt->calc.closest_f->direction)
			* rt->calc.t.closest_t
			+ dot_vect3d(&x, &rt->calc.closest_f->direction);
	v = scale_vect3d(m, &rt->calc.closest_f->direction);
	rt->calc.n = sub_vect3d(&rt->calc.closest_f->center, &rt->calc.p);
	rt->calc.n = sub_vect3d(&v, &rt->calc.n);
	norm_vect3d(&rt->calc.n);
	if (dot_vect3d(&rt->calc.n, &cam_p) < 0)
		rt->calc.n = scale_vect3d(-1, &rt->calc.n);
}

void	get_normal_of_figure(t_rtv1 *rt)
{
	if (rt->calc.closest_f->type == SPHERE)
		normal_sphere(rt);
	else if (rt->calc.closest_f->type == PLANE)
		normal_plane(rt);
	else if (rt->calc.closest_f->type == CYLINDER)
		normal_cylinder(rt);
	else if (rt->calc.closest_f->type == CONE)
		normal_cone(rt);
}
