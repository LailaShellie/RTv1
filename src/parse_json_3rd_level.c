/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_json_3rd_level.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: odrinkwa <odrinkwa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/29 14:58:49 by odrinkwa          #+#    #+#             */
/*   Updated: 2020/02/29 15:19:28 by odrinkwa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"
#include "validation.h"
#include "errno.h"

int		read_light_3rd_level(t_rtv1 *rt, char *parameters)
{
	t_light	*light;
	int		res;

	if (!(light = new_light()))
		return (ERR);
	res = parse_param_name_value(parameters, parse_params_light, light);
	if (!res)
	{
		free(light);
		return (ERR);
	}
	add_light(&rt->lights, light);
	return (1);
}

int		read_figure_3rd_level(t_rtv1 *rt, char *parameters)
{
	t_figure	*figure;
	int			res;

	if (!(figure = new_figure()))
		return (ERR);
	res = parse_param_name_value(parameters, parse_params_figure, figure);
	if (!res)
	{
		free(figure);
		return (ERR);
	}
	add_figure(&rt->figures, figure);
	return (1);
}
