
#include "../rtv1.h"

static int get_cam(t_rtv1 *rt, char **str)
{
	if (rt->cam)
		return (ERR);
	if (!(rt->cam = ft_memalloc(sizeof(t_cam))))
		return (ERR);
	if (!(rt->cam->xyz1 = get_point(str[ARG1])))
		return (ERR);
	if (!(rt->cam->xyz2 = get_vector(str[ARG2])))
		return (ERR);
	printf("%lf %lf %lf\n", rt->cam->xyz1[X], rt->cam->xyz1[Y], rt->cam->xyz1[Z]);
	printf("%lf %lf %lf\n", rt->cam->xyz2[X], rt->cam->xyz2[Y], rt->cam->xyz2[Z]);
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
	}
	return (1);
}
