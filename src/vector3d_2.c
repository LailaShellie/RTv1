/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vector3d_2.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lshellie <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/22 14:52:27 by lshellie          #+#    #+#             */
/*   Updated: 2020/02/22 14:52:28 by lshellie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"

t_vect3d	sub_vect3d(t_vect3d *start, t_vect3d *end)
{
	t_vect3d res;

	res.x = end->x - start->x;
	res.y = end->y - start->y;
	res.z = end->z - start->z;
	return (res);
}

t_vect3d	add_vect3d(t_vect3d *start, t_vect3d *end)
{
	t_vect3d res;

	res.x = end->x + start->x;
	res.y = end->y + start->y;
	res.z = end->z + start->z;
	return (res);
}

double		dot_vect3d(t_vect3d *a, t_vect3d *b)
{
	return (a->x * b->x + a->y
			* b->y + a->z * b->z);
}

t_vect3d	cross_vect3d(t_vect3d *a, t_vect3d *b)
{
	t_vect3d v;

	v.x = a->y * b->z - a->z * b->y;
	v.y = a->z * b->x - a->x * b->z;
	v.z = a->x * b->y - a->y * b->x;
	return (v);
}
