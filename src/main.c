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
#include "test_render.h"

t_roots		manage(double a, double b, double c)
{
	t_roots		t;
	double		d;

	t.t1 = INF;
	t.t2 = INF;
	t.closest_t = INF;
	d = b * b - 4.0 * a * c;
	if (d < 0)
		return (t);
	t.t1 = (-b + sqrt(d)) / (2.0 * a);
	t.t2 = (-b - sqrt(d)) / (2.0 * a);
	return (t);
}

int			main(int ac, char **av)
{
	t_rtv1		*rt;
	int			fd;

	if (!(rt = ft_memalloc(sizeof(t_rtv1))))
		return (0);
	if ((fd = open(av[1], O_RDONLY)) == -1)
		return (ft_close(rt));
	if (!(read_json(rt, fd)))
		return (ft_close(rt));
	if (ERR == init_mlx(rt))
		return (ft_close(rt));
	prepare_figures(rt);
	render(rt);
	hooks(rt);
	return (0);
}
