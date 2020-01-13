
#include "../rtv1.h"

double	*get_coords(char *coords)
{
	double	*ret;
	char	**split;

	if (!(split = ft_strsplit(coords, ',')))
		return (ERR);
	if (split[1] == 0)
		return (ERR);
	if (!(ret = ft_memalloc(sizeof(double) * 3)))
		return (ERR);
}

int	get_position(t_rtv1 *rt, char *pos)
{
	char	*split;

	if (!(split = ft_strsplit(pos, ' ')))
		return (ERR);
	if (split[1] == 0)
		return (ERR);
	if (ft_strcmp(split[0], "position") != 0 || split[2] != 0)
		return (ERR);
}

int get_cam(t_rtv1 *rt)
{
	char	*cam;
	char	*pos;
	char	*pos_end;

	if (!(cam = ft_strstr(rt->file, "camera:")))
		return (ERR);
	if (!(pos = get_line(cam)))
		return (ERR);
	pos_end = ft_strchr(pos, '\n');
	*pos_end = 0;
	if (ERR = get_position())
		return (ERR);
	*pos_end = '\n';
	return (1);
}
