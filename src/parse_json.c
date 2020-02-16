#include "rtv1.h"
#include "validation.h"
#include "errno.h"

int		read_json_1st_level(t_rtv1 *rt, char *file)
{
	int		res;

	res = parse_param_name_value(file, parse_params_scene, rt);
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
