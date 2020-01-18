//
// Created by Laila Shellie on 2020-01-17.
//

#include "validation.h"

t_light		*new_light()
{
	t_light		*new;

	if (!(new = ft_memalloc(sizeof(t_light))))
		return (ERR);
	return (new);
}

void		add_light(t_light **lights, t_light *new)
{
	t_light		*first;

	if (!*lights)
	{
		*lights = new;
		return ;
	}
	first = *lights;
	new->next = first;
	*lights = new;
}