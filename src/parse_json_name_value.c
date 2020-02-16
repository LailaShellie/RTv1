#include "rtv1.h"
#include "validation.h"
#include "errno.h"

int		parse_param_name_value(char *parameters, int func(), void *param)
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
		res = func(param_name, value, param);
		if (errno)
			res = ERR;
		free(param_name);
		free(value);
		if (!(res))
			return (ERR);
	}
	return (1);
}
