#include "libft.h"

char	*ft_strtrim_stop(char **str, const char *pattern, const char *stop)
{
	size_t	len_trim_str;
	char	*i_str;
	char	*j_str;
	char	*stop_str;
	char	*str_new;

	if (str == NULL || *str == NULL)
		return (NULL);
	if (pattern == NULL || *pattern == '\0')
		return (*str);
	stop_str = (stop == NULL || stop[0] == '\0')?
				NULL : ft_strstr(*str, stop);
	len_trim_str = 0;
	i_str = *str;
	while (*i_str && (i_str != stop_str))
		if (!ft_strchr(pattern, *(i_str++)))
			len_trim_str++;
	str_new = (char*)malloc(sizeof(char) * (len_trim_str + 1));
	i_str = *str;
	j_str = str_new;
	while(*i_str && len_trim_str)
	{
		if (!ft_strchr(pattern, *i_str))
		{
			*(j_str++) = *i_str;
			len_trim_str--;
		}
		i_str++;
	}
	*j_str = '\0';
	ft_memdel((void**)str);
	*str = str_new;
	return (*str);
}

char	*ft_filetrim_stop(int fd, const char *pattern, const char *stop)
{
	char	*line;
	char	*file;
	char	*tmp;

	file = (char*)ft_memalloc(sizeof(char));
	line = NULL;
	while (get_next_line(fd, &line) > 0)
	{
		ft_strtrim_stop(&line, pattern, stop);
 		tmp = file;
 		file = ft_strjoin(file, line);
 		ft_memdel((void**)&tmp);
 		ft_memdel((void**)&line);
	}
	ft_memdel((void**)&line);
	return (file);
}
