
#include "validation.h"

void		ft_trim(char **line)
{
	char 	*tmp;

	if ((*line)[0] == '\t' || (*line)[0] == ' ')
	{
		tmp = (*line);
		*line = ft_strtrim(*line);
		free(tmp);
	}
}

static void	ft_join(t_rtv1 *rt, char *line)
{
	char 	*tmp;

	if (line[0] == 0)
		return ;
	if (rt->file)
	{
		tmp = rt->file;
		rt->file = ft_strjoin(rt->file, "\n");
		free(tmp);
		tmp = rt->file;
		rt->file = ft_strjoin(rt->file, line);
		free(tmp);
	}
	else
		rt->file = ft_strdup(line);
}

int     read_file(t_rtv1 *rt, int ac, char **av)
{
	int		fd;
	char	*line;

	line = 0;
	if (ac != 2)
		return (ERR);
	if ((fd = open(av[1], O_RDONLY)) == -1)
		return (ERR);
	while (get_next_line(fd, &line) > 0)
	{
		ft_trim(&line);
		ft_join(rt, line);
		free(line);
		line = 0;
	}
	close(fd);
	return (1);
}
