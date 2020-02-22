/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   calculate_light.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lshellie <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/22 13:23:57 by lshellie          #+#    #+#             */
/*   Updated: 2020/02/22 13:23:58 by lshellie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"

void		get_intersection_point(t_rtv1 *rt)
{
	rt->calc.p = scale_vect3d(rt->calc.t.closest_t, &rt->calc.ray);
	rt->calc.p = add_vect3d(&rt->cam->center, &rt->calc.p);
}

int			in_shadow(t_rtv1 *rt, t_light *light)
{
	t_vect3d	l;
	t_figure	*cur;
	t_roots		t;
	double		max;

	l = sub_vect3d(&rt->calc.p, &light->center);
	max = length_vect3d(&l);
	norm_vect3d(&l);
	max /= length_vect3d(&l);
	cur = rt->figures;
	while (cur)
	{
		t = intersection(&l, &rt->calc.p, cur);
		if (t.closest_t > 0.0001 && t.closest_t <= max + 0.0001)
			return (1);
		cur = cur->next;
	}
	return (0);
}

int			calc_light(t_rtv1 *rt)
{
	double	i_diff;
	double	i_spec;
	int		color;
	t_light	*cur;

	get_intersection_point(rt);
	get_normal_of_figure(rt);
	color = 0;
	cur = rt->lights;
	while (cur)
	{
		if (!in_shadow(rt, cur))
		{
			i_diff = get_diffusive(rt, cur);
			i_spec = get_specular(rt, cur);
			color = sum_color(color,
					calculate_color(rt->calc.closest_f->color, i_diff));
			color = sum_color(color,
					calculate_color(0xffffff, i_spec));
		}
		cur = cur->next;
	}
	return (color);
}
