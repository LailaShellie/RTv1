
#include "../rtv1.h"

double	*get_coords(char *coords)
{
	double	*ret;
	char	**split;

	if (!(split = ft_strsplit(coords, ',')))
		return (ERR);
	if (count_split(split) != 3)
		return (ERR);
	if (!(ret = ft_memalloc(sizeof(double) * 3)))
		return (ERR);
	return (ret);
}

int	get_position(t_rtv1 *rt, char *pos)
{
	char	**split;
	int 	len;

	if (!(split = ft_strsplit(pos, ' ')))
		return (ERR);
	if ((len = count_split(split)) != 2)
	{
		ft_free_mas(split, len);
		return (ERR);
	}
	if (ft_strcmp(split[0], "position") != 0)
	{
		ft_free_mas(split, len)
		return (ERR);
	}
	rt->cam = get_coords(split[1]);
	ft_free_mas(split, len);
	return (rt->cam ? 1 : 0);
}

int get_cam(t_rtv1 *rt)
{
	if (ft_strcmp(rt->split[0], "camera:") != 0)
		return (ERR);
	if (ERR == get_position(rt, rt->split[1]))
		return (ERR);
	return (1);
}
