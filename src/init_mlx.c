/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_mlx.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lshellie <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/22 13:28:43 by lshellie          #+#    #+#             */
/*   Updated: 2020/02/22 13:29:08 by lshellie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"
#include "fdf.h"

int			ft_close(t_rtv1 *rt)
{
	free(rt);
	exit(0);
}

int			rt_keyhooks_angle(int keycode, t_rtv1 *rt)
{
	if (keycode == FDF_KEY_U)
		rt->cam->rotation.x -= FDF_ANGLE_ROTATE_PRECISION;
	else if (keycode == FDF_KEY_J)
		rt->cam->rotation.x += FDF_ANGLE_ROTATE_PRECISION;
	else if (keycode == FDF_KEY_H)
		rt->cam->rotation.y += FDF_ANGLE_ROTATE_PRECISION;
	else if (keycode == FDF_KEY_K)
		rt->cam->rotation.y -= FDF_ANGLE_ROTATE_PRECISION;
	else if (keycode == FDF_KEY_Y)
		rt->cam->rotation.z += FDF_ANGLE_ROTATE_PRECISION;
	else if (keycode == FDF_KEY_I)
		rt->cam->rotation.z -= FDF_ANGLE_ROTATE_PRECISION;
	return (1);
}

int			rt_keyhooks(int keycode, t_rtv1 *rt)
{
	if (keycode == FDF_KEY_ESC || keycode == FDF_KEY_Q)
		ft_close(rt);
	else if (keycode == FDF_KEY_S)
		rt->cam->center.y += FDF_STEP_SIZE;
	else if (keycode == FDF_KEY_X)
		rt->cam->center.y -= FDF_STEP_SIZE;
	else if (keycode == FDF_KEY_Z)
		rt->cam->center.x -= FDF_STEP_SIZE;
	else if (keycode == FDF_KEY_C)
		rt->cam->center.x += FDF_STEP_SIZE;
	else if (keycode == FDF_KEY_D)
		rt->cam->center.z += FDF_STEP_SIZE;
	else if (keycode == FDF_KEY_A)
		rt->cam->center.z -= FDF_STEP_SIZE;
	else if (keycode == FDF_KEY_U || keycode == FDF_KEY_J
	|| keycode == FDF_KEY_H || keycode == FDF_KEY_K
	|| keycode == FDF_KEY_Y || keycode == FDF_KEY_I)
		rt_keyhooks_angle(keycode, rt);
	else
		return (0);
	prepare_figures(rt);
	render(rt);
	return (1);
}

void		hooks(t_rtv1 *rt)
{
	mlx_hook(rt->win_ptr, 17, 0, ft_close, rt);
	mlx_key_hook(rt->win_ptr, rt_keyhooks, rt);
	mlx_loop(rt->mlx_ptr);
}

int			init_mlx(t_rtv1 *rt)
{
	if (!(rt->mlx_ptr = mlx_init()))
		return (ERR);
	if (!(rt->win_ptr = mlx_new_window(rt->mlx_ptr, W, H, "RTv1")))
		return (ERR);
	if (!(rt->img = ft_memalloc(sizeof(t_img))))
		return (ERR);
	if (!(rt->img->img_ptr = mlx_new_image(rt->mlx_ptr, W, H)))
		return (ERR);
	if (!(rt->img->data = mlx_get_data_addr(rt->img->img_ptr,
			&rt->img->bpp, &rt->img->size_line, &rt->img->endian)))
		return (ERR);
	return (1);
}
