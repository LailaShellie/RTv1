//
// Created by Ivan on 20/02/2020.
//

#include "libft.h"

int		count_split(char **split)
{
	int 	len;

	len = 0;
	while (split[len])
		++len;
	return (len);
}