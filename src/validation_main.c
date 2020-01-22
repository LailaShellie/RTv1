//
// Created by Laila Shellie on 2020-01-18.
//

#include "validation.h"


int		validation_main(t_rtv1 *rt, int ac, char **av)
{
	if (ERR == read_file(rt, ac, av))
		return (ERR);
	if (ERR == parse_file(rt))
	{
		ft_putendl("Error");
		return (ERR);
	}
	return (1);
}
