/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test_rotation_matrix1.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: odrinkwa <odrinkwa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/29 15:15:39 by odrinkwa          #+#    #+#             */
/*   Updated: 2020/02/29 15:15:46 by odrinkwa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "test_render.h"
#include "math.h"

void			mult_rmatrix(double *res, double *a, double *b)
{
	int		i;
	int		j;
	int		k;
	double	tmp[16];

	i = -1;
	while (++i < 4)
	{
		j = -1;
		while (++j < 4)
		{
			tmp[i * 4 + j] = 0;
			k = -1;
			while (++k < 4)
				tmp[i * 4 + j] += a[i * 4 + k] * b[k * 4 + j];
		}
	}
	i = -1;
	while (++i < 4)
	{
		j = -1;
		while (++j < 4)
			res[i * 4 + j] = tmp[i * 4 + j];
	}
}

void			calc_r_x_y_z(t_rot *mr, t_vect3d *angles)
{
	calc_rotate_x(mr, angles->x);
	calc_rotate_y(mr, angles->y);
	calc_rotate_z(mr, angles->z);
}

void			calc_rotate_all(t_rot *mr, t_vect3d *angles)
{
	calc_r_x_y_z(mr, angles);
	set_rotate_matrix_one(mr->r_all);
	mult_rmatrix(mr->r_all, mr->r_all, mr->r_z);
	mult_rmatrix(mr->r_all, mr->r_all, mr->r_y);
	mult_rmatrix(mr->r_all, mr->r_all, mr->r_x);
}

t_vect3d		mult_vect3d_rmatrix(t_vect3d *ray, double *rmatrix)
{
	t_vect3d	res;
	double		tmp;

	res.x = ray->x * rmatrix[0] + ray->y * rmatrix[4] +
			ray->z * rmatrix[8] + 1 * rmatrix[12];
	res.y = ray->x * rmatrix[1] + ray->y * rmatrix[5] +
			ray->z * rmatrix[9] + 1 * rmatrix[13];
	res.z = ray->x * rmatrix[2] + ray->y * rmatrix[6] +
			ray->z * rmatrix[10] + 1 * rmatrix[14];
	return (res);
}
