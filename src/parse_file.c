
#include "../rtv1.h"

static char	***get_marks(char **split, int num)
{
	int 	i;
	int 	j;
	char 	***marks;

	j = -1;
	i = -1;
	if (!(marks = ft_memalloc(sizeof(char **) * (num + 1))))
		return (ERR);
	while (split[++i])
	{
		if (is_mark(split[i]))
			marks[++j] = &split[i];
	}
	return (marks);
}

static int		pre_check(char **split)
{
	int 	i;
	int 	num;

	i = -1;
	num = 0;
	while (split[++i])
	{
		if (!is_mark(split[i]) &&
		!is_param(split[i]) &&
		!is_figure(split[i]))
			return (ERR);
		if (is_mark(split[i]))
			++num;
	}
	return (num);
}

int		parse_file(t_rtv1 *rt)
{
	int		num;
	char 	***marks;

	if (!(rt->split = ft_strsplit(rt->file, '\n')))
		return (ERR);
	if (!(num = pre_check(rt->split)))
		return (ERR);
	if (!(marks = get_marks(rt->split, num)))
		return (ERR);
	if (ERR == parse_marks(rt, marks))
		return (ERR);
	return (1);
}
