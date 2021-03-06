/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_json_name_value.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: odrinkwa <odrinkwa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/29 15:09:27 by odrinkwa          #+#    #+#             */
/*   Updated: 2020/02/29 15:20:16 by odrinkwa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"
#include "validation.h"
#include "errno.h"

int		parse_param_name_value(char *parameters, int func(), void *param)
{
	char		*param_name;
	char		*value;
	int			res;

	res = 1;
	while ((param_name = read_parameter_to_str(&parameters)))
	{
		if (!(value = read_parameter_to_str(&parameters)))
		{
			free(param_name);
			return (ERR);
		}
		errno = 0;
		res = func(param_name, value, param);
		if (errno)
			res = ERR;
		free(param_name);
		free(value);
		if (!(res))
			return (ERR);
	}
	return (1);
}
