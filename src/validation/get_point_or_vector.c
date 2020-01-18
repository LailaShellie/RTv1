//
// Created by Laila Shellie on 2020-01-17.
//

#include "validation.h"

static double	*get_coords(char *str)
{
	double	*ret;
	char	**split;
	int 	len;

	if (!(split = ft_strsplit(str, ',')))
		return (ERR);
	if ((len = count_split(split)) != COORDS_NUM)
	{
		ft_free_mas(split, len);
		return (ERR);
	}
	if (!ft_isdouble(split[X]) ||
		!ft_isdouble(split[Y]) || !ft_isdouble(split[Z]))
	{
		ft_free_mas(split, len);
		return (ERR);
	}
	if (!(ret = ft_memalloc(sizeof(double) * 3)))
		return (ERR);
	ret[X] = ft_atod(split[X]);
	ret[Y] = ft_atod(split[Y]);
	ret[Z] = ft_atod(split[Z]);
	return (ret);
}

double	*get_point(char *str)
{
	char	**split;
	double	*ret;

	if (!(split = check_param(str)))
		return (ERR);
	if (ft_strcmp(split[0], "point") != 0)
	{
		ft_free_mas(split, count_split(split));
		return (ERR);
	}
	ret = get_coords(split[1]);
	ft_free_mas(split, count_split(split));
	return (ret);
}

double	*get_vector(char *str)
{
	char	**split;
	double	*ret;

	if (!(split = check_param(str)))
		return (ERR);
	if (ft_strcmp(split[0], "vector") != 0)
	{
		ft_free_mas(split, count_split(split));
		return (ERR);
	}
	ret = get_coords(split[1]);
	ft_free_mas(split, count_split(split));
	return (ret);
}