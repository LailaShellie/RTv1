//
// Created by Laila Shellie on 2020-01-17.
//

#include "validation.h"

int	set_colors(unsigned char o, unsigned char r, \
			unsigned char g, unsigned char b)
{
	return ((int)o << 24 | (int)r << 16 | (int)g << 8 | (int)b);
}

static int		get_rgb(char *str)
{
	char	**split;
	int 	len;

	if (!(split = ft_strsplit(str, ',')))
		return (ERR);
	if ((len = count_split(split)) != COORDS_NUM)
	{
		ft_free_mas(split, len);
		return (ERR);
	}
	if (!ft_isnumber(split[R]) ||
		!ft_isnumber(split[G]) ||
		!ft_isnumber(split[B]))
	{
		ft_free_mas(split, len);
		return (ERR);
	}
	return (set_colors(0, ft_atoi(split[R]),
			ft_atoi(split[G]), ft_atoi(split[B])));
}

static char	**check_color(char *str)
{
	char	**split;
	int 	len;

	if (!(split = ft_strsplit(str, ' ')))
		return (ERR);
	if ((len = count_split(split)) != 2)
	{
		ft_free_mas(split, len);
		return (ERR);
	}
	if (ft_strcmp(split[0], "color") != 0)
	{
		ft_free_mas(split, count_split(split));
		return (ERR);
	}
	return (split);
}

int		get_color(char *str)
{
	char	**split;
	int 	ret;

	if (!(split = check_color(str)))
		return (ERR);
	ret = get_rgb(split[1]);
	ft_free_mas(split, count_split(split));
	return (ret);
}