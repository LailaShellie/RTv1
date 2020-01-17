//
// Created by Laila Shellie on 2020-01-17.
//

#include "../rtv1.h"

int	set_colors(unsigned char o, unsigned char r, \
			unsigned char g, unsigned char b)
{
	int i;
	int tmp;
	int res;
	int j;

	i = 0;
	res = 0;
	tmp = 0;
	j = 0;
	while (i <= 31)
	{
		tmp = (i >= 0 && i <= 7) ? b : tmp;
		tmp = (i >= 8 && i <= 15) ? g : tmp;
		tmp = (i >= 16 && i <= 23) ? r : tmp;
		tmp = (i >= 24 && i <= 31) ? o : tmp;
		j = 0;
		while (j <= 7)
		{
			if (tmp & (1 << j))
				res |= 1 << i;
			++i;
			++j;
		}
	}
	return (res);
}

static int		*get_rgb(char *str)
{
	char	**split;
	int 	len;
	int 	*ret;

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
	if (!(ret = ft_memalloc(sizeof(int *) * 4)))
		return (ERR);
	ret[R] = ft_abs(ft_atod(split[R])) % 256;
	ret[G] = ft_abs(ft_atod(split[G])) % 256;
	ret[B] = ft_abs(ft_atod(split[B])) % 256;
	return (ret);
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

int		*get_color(char *str)
{
	char	**split;
	int 	*ret;

	if (!(split = check_color(str)))
		return (ERR);
	ret = get_rgb(split[1]);
	ft_free_mas(split, count_split(split));
	return (ret);
}