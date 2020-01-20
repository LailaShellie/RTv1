//
// Created by Ivan on 19/01/2020.
//

#include "../rtv1.h"

void	init_vect3d(t_vect3d *vect, double x, double y, double z)
{
	vect->xyz[X] = x;
	vect->xyz[Y] = y;
	vect->xyz[Z] = z;
}

void	free_vect3d(t_vect3d *vect)
{
	free(vect->xyz);
	free(vect);
}

t_vect3d	*new_vect3d()
{
	t_vect3d	*new;

	if (!(new = ft_memalloc(sizeof(t_vect3d))))
		return (ERR);
	if (!(new->xyz = ft_memalloc(sizeof(double) * 3)))
		return (ERR);
	return (new);
}

void		sub_vect3d(t_vect3d *res, t_vect3d *start, t_vect3d *end)
{
	res->xyz[X] = end->xyz[X] - start->xyz[X];
	res->xyz[Y] = end->xyz[Y] - start->xyz[Y];
	res->xyz[Z] = end->xyz[Z] - start->xyz[Z];
}

double		dot_vect3d(t_vect3d *a, t_vect3d *b)
{
	return (a->xyz[X] * b->xyz[X] + a->xyz[Y]
	* b->xyz[Y] + a->xyz[Z] * b->xyz[Z]);
}