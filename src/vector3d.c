//
// Created by Ivan on 19/01/2020.
//

#include "../rtv1.h"

void	init_vect3d(t_vect3d *vect, double x, double y, double z)
{
	vect->coords[X] = x;
	vect->coords[Y] = y;
	vect->coords[Z] = z;
}

void	free_vect3d(t_vect3d *vect)
{
	free(vect->coords);
	free(vect);
}

t_vect3d	*new_vect3d()
{
	t_vect3d	*new;

	if (!(new = ft_memalloc(sizeof(t_vect3d))))
		return (ERR);
	if (!(new->coords = ft_memalloc(sizeof(double) * 3)))
		return (ERR);
	return (new);
}

void		sub_vect3d(t_vect3d *res, t_vect3d *start, t_vect3d *end)
{
	res->coords[X] = end->coords[X] - start->coords[X];
	res->coords[Y] = end->coords[Y] - start->coords[Y];
	res->coords[Z] = end->coords[Z] - start->coords[Z];
}

double		dot_vect3d(t_vect3d *a, t_vect3d *b)
{
	return (a->coords[X] * b->coords[X] + a->coords[Y]
	* b->coords[Y] + a->coords[Z] * b->coords[Z]);
}