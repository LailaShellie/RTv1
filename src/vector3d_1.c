/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vector3d_1.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lshellie <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/22 14:57:42 by lshellie          #+#    #+#             */
/*   Updated: 2020/02/22 14:57:42 by lshellie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"

t_vect3d	scale_vect3d(double scale, t_vect3d *a)
{
	t_vect3d res;

	res.x = a->x * scale;
	res.y = a->y * scale;
	res.z = a->z * scale;
	return (res);
}

void		norm_vect3d(t_vect3d *vect)
{
	double		len;

	len = length_vect3d(vect);
	vect->x /= len;
	vect->y /= len;
	vect->z /= len;
}

t_vect3d	init_vect3d(double x, double y, double z)
{
	t_vect3d vect;

	vect.x = x;
	vect.y = y;
	vect.z = z;
	return (vect);
}

double		length_vect3d(t_vect3d *a)
{
	double		len;

	len = a->x * a->x;
	len += a->y * a->y;
	len += a->z * a->z;
	return (sqrt(len));
}

void		print_vect3d(t_vect3d *a)
{
	printf("%lf %lf %lf\n", a->x, a->y, a->z);
}
