
#include "../rtv1.h"

int		get_intensity(t_rtv1 *rt, char *str)
{
	char	**split;
	int 	len;

	if (!(split = ft_strsplit(str, ' '))
		return (ERR);
	if ((len = count_split(split)) != POSITION)
	{
		ft_free_mas(split, len);
		return (ERR);
	}
	if (ft_strcmp(split[0], "intensity") != 0)
	{
		ft_free_mas(split, len);
		return (ERR);
	}

}

double	*get_coords(char *str)
{
	double	*ret;
	char	**split;
	int 	len;

	if (!(split = ft_strsplit(str, ','))
		|| !(ret = ft_memalloc(sizeof(double) * 3)))
		return (ERR);
	if ((len = count_split(split)) != COORDS_NUM)
	{
		ft_free_mas(split, len);
		return (ERR);
	}
	if (!ft_isdouble(split[0]) ||
		!ft_isdouble(split[1]) || !ft_isdouble(split[2]))
	{
		ft_free_mas(split, len);
		return (ERR);
	}
	ret[X] = ft_atod(split[X]);
	ret[Y] = ft_atod(split[Y]);
	ret[Z] = ft_atod(split[Z]);
	return (ret);
}

int	get_position(t_rtv1 *rt, char *str)
{
	char	**split;
	int 	len;

	if (!(split = ft_strsplit(str, ' ')))
		return (ERR);
	if ((len = count_split(split)) != POSITION)
	{
		ft_free_mas(split, len);
		return (ERR);
	}
	if (ft_strcmp(split[0], "position") != 0)
	{
		ft_free_mas(split, len);
		return (ERR);
	}
	rt->cam = get_coords(split[1]);
	ft_free_mas(split, len);
	return (rt->cam ? 1 : 0);
}
