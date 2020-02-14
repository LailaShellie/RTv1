#include "rtv1.h"
#include "validation.h"

char	*read_parameter_to_str(char **file)
{
	char	*res;
	int		len_param;
	char	*start_param;
	char	openchar;

	while (**file)
	{
		if (('0' <= **file && **file <= '9') || **file == '.')
		{
			openchar = **file;
			break ;
		}
		else if ( (**file == '"') || (**file == '[') || (**file == '{'))
		{
			openchar = **file;
			(*file)++;
			break ;
		}
		(*file)++;
		continue ;
	}
	if (**file == '\0')
		return (NULL);
	start_param = *file;
	len_param = ft_goto_endparam(file, openchar);

	if (len_param)
	{
		res = (char*)malloc(sizeof(char) * (len_param + 1));
		ft_memcpy(res, start_param, len_param);
		res[len_param] = '\0';
		return (res);
	}
	else
		return (NULL);
}
