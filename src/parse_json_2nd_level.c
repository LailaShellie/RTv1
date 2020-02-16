#include "rtv1.h"
#include "validation.h"
#include "errno.h"

int		read_title_2nd_level(t_rtv1 *rt, char *param_title)
{
	if (!(rt->title = ft_strdup(param_title)))
		return (0);
	printf("\ttitle = %s\n", rt->title);
	return (1);
}

int		read_camera_2nd_level(t_rtv1 *rt, char *parameters)
{
	int		res;

	if (rt->cam)
		return (ERR);
	rt->cam = new_cam();
	printf("\tcamera:\n");
	res = parse_param_name_value(parameters, parse_params_camera, rt->cam);
	if (!res)
	{
		ft_memdel((void**)&rt->cam);
		return (ERR);
	}
	print_camera(rt->cam);
	return (1);
}

int		read_lights_2nd_level(t_rtv1 *rt, char *parameters)
{
	char	*value;
	int		res;
	t_light	*new;

	printf("\tlights: %s\n", parameters);
	res = 1;
	while ((value = read_parameter_to_str(&parameters)))
	{
		printf("\t\tlight: %s\n", value);
		res = read_light_3rd_level(rt, value);
		free(value);
		if (!(res))
			return (ERR);
	}
	return (1);
}

int		read_figures_2nd_level(t_rtv1 *rt, char *parameters)
{
	char	*value;
	int		res;

	printf("\tfigures: %s\n", parameters);
	res = 1;
	while ((value = read_parameter_to_str(&parameters)))
	{
		printf("\t\tfigure: %s\n", value);
		res = read_figure_3rd_level(rt, value);
		free(value);
		if (!(res))
			return (ERR);
	}
	return (1);
}
