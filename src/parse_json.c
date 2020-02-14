#include "rtv1.h"
#include "validation.h"

int		read_title_2nd_level(t_rtv1 *rt, char **file)
{
	rt->title = read_parameter_to_str(file);
	printf("title = %s\n", rt->title);
	return (1);
}

int		read_camera_2nd_level(t_rtv1 *rt, char **file)
{
	char	*param_name;
	char	*param;
	char	*param_camera;

	if (rt->cam)
		return (ERR);
	rt->cam = new_cam();
	param_camera = read_parameter_to_str(file);
	printf("camera:\n");
	while ((param_name = read_parameter_to_str(&param_camera)))
	{
		param = read_parameter_to_str(&param_camera);
		printf("%s = %s\n", param_name, param);
	}
	return (1);
}

int		read_light_params_4th_level(t_rtv1 *rt, char **file)
{
	char	*param_name;
	char	*value;

	while ((param_name = read_parameter_to_str(file)))
		{
			if (ft_strequ(param_name, "center"))
				value = read_parameter_to_str(file);
			else if (ft_strequ(param_name, "intensity"))
				value = read_parameter_to_str(file);
			printf("%s %s\n", param_name, value);
		}
}

int		read_lights_2nd_level(t_rtv1 *rt, char **file)
{
	char	*param_lights;
	char	*param_light;

	param_lights = read_parameter_to_str(file);
	printf("lights: %s\n", param_lights);
	while ((param_light = read_parameter_to_str(&param_lights)))
		{
			printf("light: %s\n", param_light);
			read_light_params_4th_level(rt, &param_light);
		}
	return (1);
}

int		read_figures_2nd_level(t_rtv1 *rt, char **file)
{
	return (1);
}

int		read_json_1st_level(t_rtv1 *rt, char **file)
{
	char	*param_name;
	int		res;

	while (**file)
	{
		param_name = read_parameter_to_str(file);
		if (param_name != NULL)
			{
				if (ft_strequ(param_name, "title"))
					res = read_title_2nd_level(rt, file);
				else if (ft_strequ(param_name, "camera"))
					res = read_camera_2nd_level(rt, file);
				else if (ft_strequ(param_name, "lights"))
					res = read_lights_2nd_level(rt, file);
				else if (ft_strequ(param_name, "figures"))
					res = read_figures_2nd_level(rt, file);
				else
					; //TODO error: bad parameter
				//TODO check res (corrections error)
			}
	}
	// printf("\n\n%s %s\n", param_name, rt->title);
	return (1);
}

int		read_json(t_rtv1 *rt, char **file)
{
	char	*str;

	str = read_parameter_to_str(file);

	printf("param=%s\n", str);
	fflush(stdout);

	read_json_1st_level(rt, &str);
	return (0);

}
