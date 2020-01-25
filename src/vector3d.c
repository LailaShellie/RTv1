//
// Created by Ivan on 19/01/2020.
//

#include "../rtv1.h"

void	norm_vect(t_vect3d *vect)
{
	double		len;

	len = length_vect3d(vect);
	vect->x /= len;
	vect->y /= len;
	vect->z /= len;
}

void	init_vect3d(t_vect3d *vect, double x, double y, double z)
{
	vect->x = x;
	vect->y = y;
	vect->z = z;
}

double		length_vect3d(t_vect3d *a)
{
	double		len;

	len = a->x * a->x;
	len += a->y * a->y;
	len += a->z * a->z;
	return (sqrt(len));
}

void		sub_vect3d(t_vect3d *res, t_vect3d *start, t_vect3d *end)
{
	res->x = end->x - start->x;
	res->y = end->y - start->y;
	res->z = end->z - start->z;
}

void		add_vect3d(t_vect3d *res, t_vect3d *start, t_vect3d *end)
{
	res->x = end->x + start->x;
	res->y = end->y + start->y;
	res->z = end->z + start->z;
}

double		dot_vect3d(t_vect3d *a, t_vect3d *b)
{
	return (a->x * b->x + a->y
	* b->y + a->z * b->z);
}

void		print_vect3d(t_vect3d *a)
{
	printf("%lf %lf %lf\n", a->x, a->y, a->z);
}