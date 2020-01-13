
#include "../rtv1.h"

int		parse_file(t_rtv1 *rt)
{
	if (ERR == get_cam(rt))
		return (ERR);

	return (1);
}
