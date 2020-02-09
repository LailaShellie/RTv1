//
// Created by Ivan on 19/01/2020.
//

#include "rtv1.h"

t_vect3d	scale_vect3d(double scale, t_vect3d *a)
{
	t_vect3d res;

	res.x = a->x * scale;
	res.y = a->y * scale;
	res.z = a->z * scale;
	return (res);
}

void	norm_vect3d(t_vect3d *vect)
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

t_vect3d            cross_vect3d(t_vect3d *a, t_vect3d *b)
{
    t_vect3d v;

    v.x = a->y * b->z - a->z * b->y;
    v.y = a->z * b->x - a->x * b->z;
    v.z = a->x * b->y - a->y * b->x;
    return (v);
}

void		print_vect3d(t_vect3d *a)
{
	printf("%lf %lf %lf\n", a->x, a->y, a->z);
}