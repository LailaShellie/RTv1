#include "rtv1.h"
#include "validation.h"
#include "errno.h"

int		read_title_2nd_level(t_rtv1 *rt, char **file)
{
	if (!(rt->title = read_parameter_to_str(file)))
		return (0);
	printf("\ttitle = %s\n", rt->title);
	return (1);
}

int		read_camera_2nd_level(t_rtv1 *rt, char **file)
{
	char	*param_name;
	char	*param_name_to_free;
	char	*value;
	char	*param_camera;
	char	*param_cam_to_free;
	int		res;

	if (rt->cam)
		return (ERR);
	rt->cam = new_cam();
	if (!(param_camera = read_parameter_to_str(file)))
		return (0);
	param_cam_to_free = param_camera;
	printf("\tcamera:\n");
	while ((param_name = read_parameter_to_str(&param_camera)))
	{
		param_name_to_free = param_name;
		value = read_parameter_to_str(&param_camera);
		printf("\t\t%s = %s\n", param_name, value);
		if (ft_strequ(param_name, "center"))
			res = get_xyz(value, &rt->cam->center);
		if (ft_strequ(param_name, "direction"))
			res = get_xyz(value, &rt->cam->direction);
		ft_memdel((void**)&value);
		ft_memdel((void**)&param_name_to_free);
		if (!(res))
		{
			ft_memdel((void**)&param_cam_to_free);
			return (ERR);
		}
	}
	printf("\t\t\tcamera data:\n");
	printf("\t\t\t\tcenter: "); print_vect3d(&rt->cam->center);
	printf("\t\t\t\tdirection: "); print_vect3d(&rt->cam->direction);

	ft_memdel((void**)&param_cam_to_free);
	return (1);
}

double		get_double(char *str)
{
	if (ft_isdouble(str))
		return (ft_atod(str));
	else
		return(ERR_1);
}

double		get_light_intensity(char *str)
{
	double 	i;

	i = get_double(str);
	if (i > 1.0)
		i = 1.0;
	if (i < 0.0)
		i = 0.0;
	return (i);
}

void		print_figure(t_figure *figure)
{
	printf("\t\t\tfigure data:\n");
	printf("\t\t\t\ttype: %d\n", figure->type);
	printf("\t\t\t\tcenter: "); print_vect3d(&figure->center);
	printf("\t\t\t\tdirection: "); print_vect3d(&figure->direction);
	printf("\t\t\t\tcolor: 0x%06x\n", figure->color);
	printf("\t\t\t\tradius: %lf\n", figure->radius);
	printf("\t\t\t\tspecularity: %lf\n", figure->s);
}

void		print_light(t_light *light)
{
	printf("\t\t\tlight data:\n");
	printf("\t\t\t\tcenter: "); print_vect3d(&light->center);
	printf("\t\t\t\tintensity: %lf\n", light->i);
}



int		read_light_params_4th_level(t_light *light, char **file)
{
	char	*param_name;
	char	*value;
	int		res;

	res = 1;
	while ((param_name = read_parameter_to_str(file)))
	{
		if (!(value = read_parameter_to_str(file)))
		{
			ft_memdel((void**)&param_name);
			return (ERR);
		}
		errno = 0;
		if (ft_strequ(param_name, "center"))
			get_xyz(value, &light->center);
		else if (ft_strequ(param_name, "intensity"))
			light->i = get_light_intensity(value);
		else
			res = ERR;
		if (errno)
			res = ERR;
		printf("\t\t\t%s %s\n", param_name, value);
		ft_memdel((void**)&value);
		ft_memdel((void**)&param_name);
	}
	print_light(light);
	return (res);
}

int		read_light_3rd_level(t_rtv1 *rt, char **file)
{
	t_light	*new;
	int		res;
	
	if (!(new = new_light()))
		return (ERR);
	res = read_light_params_4th_level(new, file);
	if (!res)
	{
		ft_memdel((void**)&new);
		return (ERR);
	}
	add_light(&rt->lights, new);	
	return (1);
}

int		read_lights_2nd_level(t_rtv1 *rt, char **file)
{
	char	*param_lights;
	char	*param_lights_to_free;
	char	*param_light;
	char	*param_light_to_free;
	int		res;
	t_light	*new;

	if (!(param_lights = read_parameter_to_str(file)))
		return (ERR);
	param_lights_to_free = param_lights;
	printf("\tlights: %s\n", param_lights);
	while ((param_light = read_parameter_to_str(&param_lights)))
		{
			param_light_to_free = param_light;
			printf("\t\tlight: %s\n", param_light);			
			res = read_light_3rd_level(rt, &param_light);
			ft_memdel((void**)&param_light_to_free);
			if (!res)
			{
				ft_memdel((void**)&param_lights_to_free);
				return (ERR);
			}
		}
	ft_memdel((void**)&param_lights_to_free);
	return (1);
}

int		read_figure_params_4th_level(t_figure *figure, char **file)
{
	char	*param_name;
	char	*value;
	int		res;

	res = 1;
	while ((param_name = read_parameter_to_str(file)))
	{
		if (!(value = read_parameter_to_str(file)))
		{
			ft_memdel((void**)&param_name);
			return (ERR);
		}
		errno = 0;
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
			res = ERR;
		if (errno)
			res = ERR;
		printf("\t\t\t%s %s\n", param_name, value);
		ft_memdel((void**)&value);
		ft_memdel((void**)&param_name);
	}
	print_figure(figure);
	return (res);
}

int		read_figures_2nd_level(t_rtv1 *rt, char **file)
{
	char		*param_figures;
	char		*param_figure;
	t_figure	*new;

	param_figures = read_parameter_to_str(file);
	printf("\tfigures: %s\n", param_figures);
	while ((param_figure = read_parameter_to_str(&param_figures)))
		{
			if (!(new = new_figure()))
				return (ERR);
			printf("\t\tfigure: %s\n", param_figure);
			read_figure_params_4th_level(new, &param_figure);
			add_figure(&rt->figures, new);
		}
	return (1);
}

int		read_json_1st_level(t_rtv1 *rt, char **file)
{
	char	*param_name;
	int		res;

	while (**file)
	{
		if (!(param_name = read_parameter_to_str(file)))
			return (0);
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
				{
					ft_memdel((void**)&param_name);
					return (0);
				}
				//TODO check res (corrections error)
			}
		ft_memdel((void**)&param_name);
		if (!res)
			return (0);
	}
	return (1);
}

int		read_json(t_rtv1 *rt, char **file)
{
	char	*str;
	char	*str_to_free;
	char	*file_to_free;
	int		res;

	res = 0;
	str = NULL;
	file_to_free = *file;
	if (!(str = read_parameter_to_str(file)))
	{
		ft_memdel((void**)&file_to_free);
		return (res);
	}
	str_to_free = str;

	printf("param_start=%s\n", str);
	fflush(stdout);

	res = read_json_1st_level(rt, &str);

	ft_memdel((void**)&file_to_free);
	ft_memdel((void**)&str_to_free);
	return (res);

}
