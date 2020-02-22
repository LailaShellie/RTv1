/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   objects.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lshellie <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/22 13:38:24 by lshellie          #+#    #+#             */
/*   Updated: 2020/02/22 13:38:25 by lshellie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "validation.h"

t_figure	*new_figure(void)
{
	t_figure		*new;

	if (!(new = ft_memalloc(sizeof(t_figure))))
		return (ERR);
	return (new);
}

void		add_figure(t_figure **figures, t_figure *new)
{
	t_figure		*first;

	if (!*figures)
	{
		*figures = new;
		new->next = 0;
		return ;
	}
	first = *figures;
	new->next = first;
	*figures = new;
}

t_light		*new_light(void)
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
		new->next = 0;
		return ;
	}
	first = *lights;
	new->next = first;
	*lights = new;
}

t_cam		*new_cam(void)
{
	t_cam		*new;

	if (!(new = ft_memalloc(sizeof(t_cam))))
		return (ERR);
	return (new);
}
