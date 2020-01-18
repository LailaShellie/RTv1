
#include "validation.h"

char	**check_param(char *str)
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
	return (split);
}

int		count_split(char **split)
{
	int 	len;

	len = 0;
	while (split[len])
		++len;
	return (len);
}

int		is_param(char *str)
{
	if (ft_strncmp(str, "type", 4) == 0)
		return (1);
	else if (ft_strncmp(str, "radius", 6) == 0)
		return (1);
	else if (ft_strncmp(str, "intensity", 9) == 0)
		return (1);
	else if (ft_strncmp(str, "specularity", 11) == 0)
		return (1);
	else if (ft_strncmp(str, "color", 5) == 0)
		return (1);
	else if (ft_strncmp(str, "vector", 6) == 0)
		return (1);
	else if (ft_strncmp(str, "point", 5) == 0)
		return (1);
	return (ERR);
}

int		is_figure(char *str)
{
	if (ft_strncmp(str, "sphere", 6) == 0)
		return (1);
	else if (ft_strncmp(str, "cone", 4) == 0)
		return (1);
	else if (ft_strncmp(str, "plane", 5) == 0)
		return (1);
	else if (ft_strncmp(str, "cylinder", 8) == 0)
		return (1);
	return (ERR);
}

int		is_mark(char *str)
{
	if (ft_strcmp(str, "camera:") == 0)
		return (1);
	else if (ft_strcmp(str, "light:") == 0)
		return (1);
	else if (ft_strcmp(str, "figure:") == 0)
		return (1);
	return (ERR);
}
