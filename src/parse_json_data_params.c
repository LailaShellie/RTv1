#include "rtv1.h"
#include "validation.h"
#include "errno.h"

int		parse_params_camera(t_rtv1 *rt, char *param_name, char *value, t_cam *camera)
{
	int		res;

	if (ft_strequ(param_name, "center"))
		res = get_xyz(value, &rt->cam->center);
	else if (ft_strequ(param_name, "direction"))
		res = get_xyz(value, &rt->cam->direction);
	else
		res = ERR;
	return (res);
}

int		parse_params_light(t_rtv1 *rt, char *param_name, char *value, t_light *light)
{
	if (ft_strequ(param_name, "center"))
		get_xyz(value, &light->center);
	else if (ft_strequ(param_name, "intensity"))
		light->i = get_light_intensity(value);
	else
		return (ERR);
	return (1);
}

int		parse_params_figure(t_rtv1 *rt, char *param_name, char *value, t_figure *figure)
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
	else
		return (ERR);
	return (1);
}
