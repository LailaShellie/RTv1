
#include "validation.h"

static int get_figure(t_rtv1 *rt, char **str)
{
	t_figure	*new;

	if (!(new = new_figure())
	|| count_split(str) < 7)
		return (ERR);
	if (!(new->type = get_type(str[ARG1])))
		return (ERR);
	if (!(get_vector(str[ARG2], &new->center)))
		return (ERR);
	if (!(get_vector(str[ARG3], &new->direction)))
		return (ERR);
	if (!(new->color = get_color(str[ARG4])))
		return (ERR);
	if (!(new->radius = get_radius(str[ARG5])))
		return (ERR);
	if (!(new->s = get_specularity(str[ARG6])))
		return (ERR);
	add_figure(&rt->figures, new);
	return (1);
}

static int get_light(t_rtv1 *rt, char **str)
{
	t_light		*new;

	if (!(new = new_light()))
		return (ERR);
	if (!(get_vector(str[ARG1], &new->center)))
		return (ERR);
	if (!(new->i = get_intensity(str[ARG2])))
		return (ERR);
	add_light(&rt->lights, new);
	return (1);
}

static int get_cam(t_rtv1 *rt, char **str)
{
	if (rt->cam)
		return (ERR);
	if (!(rt->cam = new_cam()))
		return (ERR);
	if (!(get_vector(str[ARG1], &rt->cam->center)))
		return (ERR);
	if (!(get_vector(str[ARG2], &rt->cam->direction)))
		return (ERR);
	return (1);
}

int		parse_marks(t_rtv1 *rt, char ***marks)
{
	int 	i;

	i = -1;
	while (marks[++i])
	{
		if (ft_strcmp(marks[i][0], "camera:") == 0)
			if (ERR == get_cam(rt, marks[i]))
				return (ERR);
		if (ft_strcmp(marks[i][0], "light:") == 0)
			if (ERR == get_light(rt, marks[i]))
				return (ERR);
		if (ft_strcmp(marks[i][0], "figure:") == 0)
			if (ERR == get_figure(rt, marks[i]))
				return (ERR);
	}
	return (1);
}
