//
// Created by Laila Shellie on 2020-01-17.
//

#include "validation.h"

static double	get_param(char **split)
{
	double	ret;

	if (ft_isdouble(split[1]))
		ret = ft_atod(split[1]);
	else
		ret = ERR_1;
	ft_free_mas(split, count_split(split));
	return (ret);
}

double		get_radius(char *str)
{
	char **split;

	if (!(split = check_param(str)))
		return (ERR_1);
	if (ft_strcmp(split[0], "radius") == 0)
		return (get_param(split));
	ft_free_mas(split, count_split(split));
	return (ERR_1);
}

double		get_intensity(char *str)
{
	char	**split;

	if (!(split = check_param(str)))
		return (ERR_1);
	if (ft_strcmp(split[0], "intensity") == 0)
		return (get_param(split));
	ft_free_mas(split, count_split(split));
	return (ERR_1);
}

double		get_specularity(char *str)
{
	char	**split;

	if (!(split = check_param(str)))
		return (ERR_1);
	if (ft_strcmp(split[0], "specularity") == 0)
		return (get_param(split));
	ft_free_mas(split, count_split(split));
	return (ERR_1);
}
