
#include "validation.h"

static int get_figure(t_rtv1 *rt, char **str)
{
	t_figure	*new;

	if (!(new = new_figure())
	|| count_split(str) < 7)
		return (ERR);
	if (!(new->type = get_type(str[ARG1])))
		return (ERR);
	if (!(new->c->coords = get_point(str[ARG2])))
		return (ERR);
	if (!(new->v->coords = get_vector(str[ARG3])))
		return (ERR);
	if (!(new->color = get_color(str[ARG4])))
		return (ERR);
	if (!(new->r = get_radius(str[ARG5])))
		return (ERR);
	if (!(new->s = get_specularity(str[ARG6])))
		return (ERR);
	add_figure(&rt->figures, new);
	printf("%#x\n", new->color);
	return (1);
}

static int get_light(t_rtv1 *rt, char **str)
{
	t_light		*new;

	if (!(new = new_light()))
		return (ERR);
	if (!(new->c->coords = get_point(str[ARG1])))
		return (ERR);
	if (!(new->i = get_intensity(str[ARG2])))
		return (ERR);
	add_light(&rt->lights, new);
	printf("light:\n");
	printf("%lf %lf %lf\n", new->c->coords[X], new->c->coords[Y], new->c->coords[Z]);
	printf("%lf\n", new->i);
	return (1);
}

static int get_cam(t_rtv1 *rt, char **str)
{
	if (rt->cam)
		return (ERR);
	if (!(rt->cam = new_cam()))
		return (ERR);
	if (!(rt->cam->c->coords = get_point(str[ARG1])))
		return (ERR);
	if (!(rt->cam->v->coords = get_vector(str[ARG2])))
		return (ERR);
	printf("camera:\n");
	printf("%lf %lf %lf\n", rt->cam->c->coords[X], rt->cam->c->coords[Y], rt->cam->c->coords[Z]);
	printf("%lf %lf %lf\n", rt->cam->v->coords[X], rt->cam->v->coords[Y], rt->cam->v->coords[Z]);
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
