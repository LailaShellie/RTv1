//
// Created by Ivan on 19/01/2020.
//

#include "validation.h"

t_cam		*new_cam()
{
	t_cam		*new;

	if (!(new = ft_memalloc(sizeof(t_cam))))
		return (ERR);
	return (new);
}