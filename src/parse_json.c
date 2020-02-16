#include "rtv1.h"
#include "validation.h"
#include "errno.h"


int		parse_param_name_value(t_rtv1 *rt, char *parameters, int func(), void *param)
{
	char		*param_name;
	char		*value;
	int			res;

	res = 1;
	while ((param_name = read_parameter_to_str(&parameters)))
	{
		if (!(value = read_parameter_to_str(&parameters)))
		{
			free(param_name);
			return (ERR);
		}
		printf("\t\t\t%s %s\n", param_name, value);
		errno = 0;
		res = func(rt, param_name, value, param);
		if (errno)
			res = ERR;
		free(param_name);
		free(value);
		if (!(res))
			return (ERR);
	}
	return (1);
}

int		read_title_2nd_level(t_rtv1 *rt, char *param_title)
{
	if (!(rt->title = param_title))
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
	res = parse_param_name_value(rt, parameters, parse_params_camera, rt->cam);
	if (!res)
	{
		ft_memdel((void**)&rt->cam);
		return (ERR);
	}
	print_camera(rt->cam);
	return (1);
}

int		read_light_3rd_level(t_rtv1 *rt, char *parameters)
{
	t_light	*light;
	int		res;

	if (!(light = new_light()))
		return (ERR);
	res = parse_param_name_value(rt, parameters, parse_params_light, light);
	if (!res)
	{
		free(light);
		return (ERR);
	}
	print_light(light);
	add_light(&rt->lights, light);
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

int		read_figure_3rd_level(t_rtv1 *rt, char *parameters)
{
	t_figure	*figure;
	int			res;

	if (!(figure = new_figure()))
		return (ERR);

	res = parse_param_name_value(rt, parameters, parse_params_figure, figure);
	if (!res)
	{
		free(figure);
		return (ERR);
	}
	print_figure(figure);
	add_figure(&rt->figures, figure);
	return (1);
}

int		read_figures_2nd_level(t_rtv1 *rt, char *parameters)
{
	char	*value;
	int		res;
	t_light	*new;

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

int		parse_params_scene(t_rtv1 *rt, char *param_name, char *value, void *param)
{
	int		res;

	if (ft_strequ(param_name, "title"))
		res = read_title_2nd_level(rt, value);
	else if (ft_strequ(param_name, "camera"))
		res = read_camera_2nd_level(rt, value);
	else if (ft_strequ(param_name, "lights"))
		res = read_lights_2nd_level(rt, value);
	else if (ft_strequ(param_name, "figures"))
		res = read_figures_2nd_level(rt, value);
	else
		res = ERR;
	return (res);
}

int		read_json_1st_level(t_rtv1 *rt, char *file)
{
	int		res;

	res = parse_param_name_value(rt, file, parse_params_scene, NULL);
	if (!res)
		return (ERR);
	return (1);
}

int		read_json(t_rtv1 *rt, int fd)
{
	char	*file;
	char	*file_start;
	char	*str;
	int		res;

	res = 0;
	str = NULL;
	file = ft_filetrim_stop(fd, " \t\n", "//");
	file_start = file;
	printf("%s\n", file);

	if (!(str = read_parameter_to_str(&file)))
		return (res);

	printf("param_start=%s\n", str);
	fflush(stdout);

	res = read_json_1st_level(rt, str);
	free(file_start);
	free(str);
	return (res);
}
