/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_json_read_param.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: odrinkwa <odrinkwa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/29 15:09:38 by odrinkwa          #+#    #+#             */
/*   Updated: 2020/02/29 15:17:48 by odrinkwa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"
#include "validation.h"

static	char	find_openchar(char **file)
{
	char	openchar;

	while (**file)
	{
		if (('0' <= **file && **file <= '9') || **file == '.')
			return (**file);
		else if ((**file == '"') || (**file == '[') || (**file == '{'))
		{
			openchar = **file;
			(*file)++;
			return (openchar);
		}
		(*file)++;
	}
	return (0);
}

char			*read_parameter_to_str(char **file)
{
	char	*res;
	int		len_param;
	char	*start_param;
	char	openchar;

	openchar = find_openchar(file);
	if (**file == '\0')
		return (NULL);
	start_param = *file;
	len_param = ft_goto_endparam(file, openchar);
	if (len_param)
	{
		res = (char*)malloc(sizeof(char) * (len_param + 1));
		ft_memcpy(res, start_param, len_param);
		res[len_param] = '\0';
		return (res);
	}
	else
		return (NULL);
}
