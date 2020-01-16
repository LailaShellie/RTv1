
#include "../rtv1.h"



int		count_split(char **split)
{
	int 	len;

	len = 0;
	while (split[len])
		++len;
	return (len);
}

int		is_mark(char *line)
{
	if (ft_strcmp(line, "camera") == 0)
		return (1);
	else if (ft_strcmp(line, "light") == 0)
		return (1);
	else if (ft_strcmp(line, "figure") == 0)
		return (1);
	return (0);
}

char *get_line(char *line)
{
	char	*next;

	if (!line || *line == 0)
		return (0);
	next = ft_strchr(line, '\n');
	if (next)
		++next;
	return (next);
}