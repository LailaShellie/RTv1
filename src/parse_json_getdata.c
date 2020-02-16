#include "rtv1.h"
#include "validation.h"
#include "errno.h"

double		get_double(char *str)
{
	if (ft_isdouble(str))
		return (ft_atod(str));
	else
	{
		errno = 127;
		return(ERR_1);
	}
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