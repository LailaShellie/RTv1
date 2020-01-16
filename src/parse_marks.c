
#include "../rtv1.h"

int get_lights(t_rtv1 *rt)
{
	if (ft_strcmp(rt->split[LIGHTS_POS], "light:") != 0)
		return (ERR);
	if (ERR == get_position(rt, rt->split[LIGHTS + ARG1]))
		return (ERR);
}

int get_cam(t_rtv1 *rt)
{
	if (ft_strcmp(rt->split[CAM], "camera:") != 0)
		return (ERR);
	if (ERR == get_position(rt, rt->split[CAM + ARG1]))
		return (ERR);
	printf("%lf %lf %lf\n", rt->cam[X], rt->cam[Y], rt->cam[Z]);
	return (1);
}
