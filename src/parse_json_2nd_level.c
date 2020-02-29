/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_json_2nd_level.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: odrinkwa <odrinkwa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/29 15:14:38 by odrinkwa          #+#    #+#             */
/*   Updated: 2020/02/29 15:19:45 by odrinkwa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"
#include "validation.h"
#include "errno.h"

int		read_title_2nd_level(t_rtv1 *rt, char *param_title)
{
	if (!(rt->title = ft_strdup(param_title)))
		return (0);
	return (1);
}

int		read_camera_2nd_level(t_rtv1 *rt, char *parameters)
{
	int		res;

	if (rt->cam)
		return (ERR);
	rt->cam = new_cam();
	res = parse_param_name_value(parameters, parse_params_camera, rt->cam);
	if (!res)
	{
		ft_memdel((void**)&rt->cam);
		return (ERR);
	}
	return (1);
}

int		read_lights_2nd_level(t_rtv1 *rt, char *parameters)
{
	char	*value;
	int		res;
	t_light	*new;

	res = 1;
	while ((value = read_parameter_to_str(&parameters)))
	{
		res = read_light_3rd_level(rt, value);
		free(value);
		if (!(res))
			return (ERR);
	}
	return (1);
}

int		read_figures_2nd_level(t_rtv1 *rt, char *parameters)
{
	char	*value;
	int		res;

	res = 1;
	while ((value = read_parameter_to_str(&parameters)))
	{
		res = read_figure_3rd_level(rt, value);
		free(value);
		if (!(res))
			return (ERR);
	}
	return (1);
}
