/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_rtv1.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lshellie <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/28 18:06:27 by lshellie          #+#    #+#             */
/*   Updated: 2020/02/28 18:06:29 by lshellie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"

void		free_figures(t_figure *figures)
{
	t_figure *cur;
	t_figure *tmp;

	cur = figures;
	while (cur)
	{
		tmp = cur;
		cur = cur->next;
		free(tmp);
	}
}

void		free_lights(t_light *lights)
{
	t_light *cur;
	t_light *tmp;

	cur = lights;
	while (cur)
	{
		tmp = cur;
		cur = cur->next;
		free(tmp);
	}
}

void		free_rtv1(t_rtv1 *rt)
{
	free_figures(rt->figures);
	free_lights(rt->lights);
	free(rt->cam);
}