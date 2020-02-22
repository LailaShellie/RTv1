/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lshellie <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/22 13:36:26 by lshellie          #+#    #+#             */
/*   Updated: 2020/02/22 13:36:29 by lshellie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"
#include "validation.h"

int		main(int ac, char **av)
{
	t_rtv1		*rt;
	int			fd;

	if (!(rt = ft_memalloc(sizeof(t_rtv1))))
		return (0);
	if (ac != 2)
		return (ERR);
	if ((fd = open(av[1], O_RDONLY)) == -1)
		return (ERR);
	if (!(read_json(rt, fd)))
		return (ERR);
	if (ERR == init_mlx(rt))
		return (0);
	prepare_figures(rt);
	render(rt);
	hooks(rt);
	return (0);
}
