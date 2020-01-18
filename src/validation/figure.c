//
// Created by Laila Shellie on 2020-01-17.
//

#include "validation.h"

t_figure		*new_figure()
{
	t_figure		*new;

	if (!(new = ft_memalloc(sizeof(t_figure))))
		return (ERR);
	if (!(new->c = new_vect3d()))
		return (ERR);
	if (!(new->v = new_vect3d()))
		return (ERR);
	return (new);
}

void		add_figure(t_figure **figures, t_figure *new)
{
	t_figure		*first;

 	if (!*figures)
	{
		*figures = new;
		return ;
	}
	first = *figures;
	new->next = first;
	*figures = new;
}