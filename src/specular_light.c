/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   specular_light.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lshellie <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/22 13:50:58 by lshellie          #+#    #+#             */
/*   Updated: 2020/02/22 13:51:00 by lshellie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"

double		get_specular(t_rtv1 *rt, t_light *light)
{
	t_vect3d	l;
	t_vect3d	r;
	double		r_dot_v;
	t_vect3d	v;
	double		dot;

	l = sub_vect3d(&rt->calc.p, &light->center);
	dot = dot_vect3d(&l, &rt->calc.n);
	if (dot < 0)
		return (0);
	v = sub_vect3d(&rt->calc.p, &rt->cam->center);
	r = init_vect3d(2 * rt->calc.n.x * dot - l.x,
			2 * rt->calc.n.y * dot - l.y,
			2 * rt->calc.n.z * dot - l.z);
	r_dot_v = dot_vect3d(&r, &v);
	dot = length_vect3d(&r) * length_vect3d(&v);
	if (r_dot_v > 0)
		return (light->i * pow(r_dot_v / dot, 100) / rt->total_light);
	return (0);
}
