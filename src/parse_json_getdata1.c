/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_json_getdata1.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: odrinkwa <odrinkwa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/29 14:56:33 by odrinkwa          #+#    #+#             */
/*   Updated: 2020/02/29 14:57:08 by odrinkwa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"
#include "validation.h"
#include "errno.h"

double		get_light_intensity(char *str)
{
	double	i;

	i = get_double(str);
	if (i > 1.0)
		i = 1.0;
	if (i < 0.0)
		i = 0.0;
	return (i);
}

double		get_light_type(char *str)
{
	if (ft_strequ(str, "ambient"))
		return (AMBIENT);
	else if (ft_strequ(str, "point"))
		return (POINT);
	else if (ft_strequ(str, "directional"))
		return (DIRECTIONAL);
	else
		return (0);
}
