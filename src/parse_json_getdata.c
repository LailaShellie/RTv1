#include "rtv1.h"
#include "validation.h"
#include "errno.h"

int	set_colors(unsigned char o, unsigned char r, \
			unsigned char g, unsigned char b)
{
	return ((int)o << 24 | (int)r << 16 | (int)g << 8 | (int)b);
}

int				get_rgb(char *str)
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

int			choose_type(char *line)
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

double		get_double(char *str)
{
	if (ft_isdouble(str))
		return (ft_atod(str));
	else
	{
		errno = 127;
		return(ERR_1);
	}
}

double		get_light_intensity(char *str)
{
	double 	i;

	i = get_double(str);
	if (i > 1.0)
		i = 1.0;
	if (i < 0.0)
		i = 0.0;
	return (i);
}
