
#include "../rtv1.h"

int		parse_file(t_rtv1 *rt)
{
	if (!(rt->split = ft_strsplit(rt->file, '\n')))
		return (ERR);
	if (ERR == get_cam(rt))
		return (ERR);
	if (ERR == get_lights(rt))
		return (ERR);
	return (1);
}
