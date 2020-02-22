/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   diffusive_light.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lshellie <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/22 13:26:15 by lshellie          #+#    #+#             */
/*   Updated: 2020/02/22 13:26:16 by lshellie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"

double		get_diffusive(t_rtv1 *rt, t_light *light)
{
	t_vect3d	l;
	double		dot;

	l = sub_vect3d(&rt->calc.p, &light->center);
	norm_vect3d(&l);
	dot = dot_vect3d(&l, &rt->calc.n);
	if (dot > 0)
		return (light->i * dot / rt->total_light);
	return (0);
}
