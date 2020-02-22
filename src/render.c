/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lshellie <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/22 13:47:32 by lshellie          #+#    #+#             */
/*   Updated: 2020/02/22 13:47:33 by lshellie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "rtv1.h"

int			sum_color(int color1, int color2)
{
	union u_color clr1;
	union u_color clr2;

	clr1.color = color1;
	clr2.color = color2;
	if ((unsigned int)clr1.s_parts.r + (unsigned int)clr2.s_parts.r > 255)
		clr1.s_parts.r = 255;
	else
		clr1.s_parts.r += clr2.s_parts.r;
	if ((unsigned int)clr1.s_parts.g + (unsigned int)clr2.s_parts.g > 255)
		clr1.s_parts.g = 255;
	else
		clr1.s_parts.g += clr2.s_parts.g;
	if ((unsigned int)clr1.s_parts.b + (unsigned int)clr2.s_parts.b > 255)
		clr1.s_parts.b = 255;
	else
		clr1.s_parts.b += clr2.s_parts.b;
	return (clr1.color);
}

int			calculate_color(int color, double intensity)
{
	union u_color clr;

	clr.color = color;
	if ((unsigned int)clr.s_parts.r * intensity > 255)
		clr.s_parts.r = 255;
	else
		clr.s_parts.r *= intensity;
	if ((unsigned int)clr.s_parts.g * intensity > 255)
		clr.s_parts.g = 255;
	else
		clr.s_parts.g *= intensity;
	if ((unsigned int)clr.s_parts.b * intensity > 255)
		clr.s_parts.b = 255;
	else
		clr.s_parts.b *= intensity;
	return (clr.color);
}

int			trace_ray(t_rtv1 *rt, t_vect3d *ray, t_vect3d *o)
{
	t_figure	*cur;
	t_roots		t;

	rt->calc.closest_f = 0;
	rt->calc.t.closest_t = INF;
	cur = rt->figures;
	while (cur)
	{
		t = intersection(ray, o, cur);
		if (t.closest_t > VZ && t.closest_t <= rt->calc.t.closest_t)
		{
			rt->calc.closest_f = cur;
			rt->calc.t = t;
		}
		cur = cur->next;
	}
	if (rt->calc.closest_f == 0)
		return (BACKGROUND);
	return (calc_light(rt));
}

t_vect3d	gen_ray(t_rtv1 *rt, int x, int y)
{
	t_vect3d	ray;
	double		u;
	double		v;

	u = ((double)W - (double)x * VZ) / H;
	v = ((double)H - (double)y * VZ) / W;
	ray = init_vect3d(u * rt->cam->v1.x + v
			* rt->cam->v2.x + VZ * rt->cam->v3.x,
			u * rt->cam->v1.y + v * rt->cam->v2.y + VZ * rt->cam->v3.y,
			u * rt->cam->v1.z + v * rt->cam->v2.z + VZ * rt->cam->v3.z);
	norm_vect3d(&ray);
	return (ray);
}

void		render(t_rtv1 *rt)
{
	int		x;
	int		y;

	y = -1;
	while (++y < H)
	{
		x = -1;
		while (++x < W)
		{
			rt->calc.ray = gen_ray(rt, x, y);
			((int *)rt->img->data)[x + y * rt->img->size_line / 4] =
					trace_ray(rt, &rt->calc.ray, &rt->cam->center);
		}
	}
	mlx_put_image_to_window(rt->mlx_ptr, rt->win_ptr, rt->img->img_ptr, 0, 0);
}
