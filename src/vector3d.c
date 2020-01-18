//
// Created by Ivan on 19/01/2020.
//

#include "../rtv1.h"

t_vect3d	*new_vect3d()
{
	t_vect3d	*new;

	if (!(new = ft_memalloc(sizeof(t_vect3d))))
		return (ERR);
	return (new);
}