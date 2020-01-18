//
// Created by Laila Shellie on 2020-01-17.

#include "validation.h"

static int	choose_type(char *line)
{
	if (ft_strcmp(line, "sphere") == 0)
		return (SPHERE);
	else if (ft_strcmp(line, "cone") == 0)
		return (CONE);
	else if (ft_strcmp(line, "plane") == 0)
		return (PLANE);
	else if (ft_strcmp(line, "cylinder") == 0)
		return (CYLINDER);
	return (ERR);
}

int			get_type(char *str)
{
	char	**split;
	int 	len;
	int		ret;

	if (!(split = ft_strsplit(str, ' ')))
		return (ERR);
	if ((len = count_split(split)) != 2)
	{
		ft_free_mas(split, len);
		return (ERR);
	}
	if (ft_strcmp(split[0], "type") != 0)
	{
		ft_free_mas(split, len);
		return (ERR);
	}
	ret = choose_type(split[1]);
	ft_free_mas(split, len);
	return (ret);
}