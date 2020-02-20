#include "rtv1.h"
#include "validation.h"
#include "errno.h"

int		parse_params_scene(char *param_name, char *value, t_rtv1 *rt)
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
	else if (ft_strequ(param_name, "background_color"))
		rt->background_color = get_rgb(value);
	else if (ft_strequ(param_name, "reflection_depth"))
		rt->reflection_depth = (int)get_double(value);
	else
		res = ERR;
	return (res);
}

int		parse_params_camera(char *param_name, char *value, t_cam *camera)
{
	int		res;

	if (ft_strequ(param_name, "center"))
		res = get_xyz(value, &camera->center);
	else if (ft_strequ(param_name, "direction"))
		res = get_xyz(value, &camera->direction);
	else if (ft_strequ(param_name, "rotation"))
		res = get_xyz(value, &camera->rotation);
	else
		res = ERR;
	return (res);
}

int		parse_params_light(char *param_name, char *value, t_light *light)
{
	if (ft_strequ(param_name, "center"))
		get_xyz(value, &light->center);
	else if (ft_strequ(param_name, "direction"))
		get_xyz(value, &light->direction);
	else if (ft_strequ(param_name, "intensity"))
		light->i = get_light_intensity(value);
	else if (ft_strequ(param_name, "type"))
		light->type = get_light_type(value);
	else
		return (ERR);
	return (1);
}

int		parse_params_figure(char *param_name, char *value, t_figure *figure)
{
	if (ft_strequ(param_name, "type"))
		figure->type = choose_type(value);
	else if (ft_strequ(param_name, "center"))
		get_xyz(value, &figure->center);
	else if (ft_strequ(param_name, "direction"))
		get_xyz(value, &figure->direction);
	else if (ft_strequ(param_name, "color"))
		figure->color = get_rgb(value);
	else if (ft_strequ(param_name, "radius"))
		figure->radius = get_double(value);
	else if (ft_strequ(param_name, "specularity"))
		figure->s = get_double(value);
	else if (ft_strequ(param_name, "reflective"))
		figure->reflect = get_double(value);
	else
		return (ERR);
	return (1);
}
