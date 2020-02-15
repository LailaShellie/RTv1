//
// Created by Laila Shellie on 2020-01-17.
//

#include "validation.h"

int		get_xyz(char *str, t_vect3d *vect)
{
	char	**split;
	int 	len;

	if (!(split = ft_strsplit(str, ',')))
		return (ERR);
	if ((len = count_split(split)) != 3)
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
	vect->x = ft_atod(split[X]);
	vect->y = ft_atod(split[Y]);
	vect->z= ft_atod(split[Z]);
	ft_free_mas(split, len);
	return (1);
}

int		get_vector(char *str, t_vect3d *vect)
{
	char	**split;

	if (!(split = check_param(str)))
		return (ERR);
	if (ft_strcmp(split[0], "vector") != 0)
	{
		ft_free_mas(split, count_split(split));
		return (ERR);
	}
	get_xyz(split[1], vect);
	ft_free_mas(split, count_split(split));
	return (1);
}