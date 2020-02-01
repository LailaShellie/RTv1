//
// Created by Laila Shellie on 2020-01-20.
//

#include "rtv1.h"

int	sum_color(int color1, int color2)
{
	union u_color clr1;
	union u_color clr2;

	clr1.color = color1;
	clr2.color = color2;
	if (clr1.s_parts.r + clr2.s_parts.r > 255)
		clr1.s_parts.r = 255;
	else
		clr1.s_parts.r += clr2.s_parts.r;
	if (clr1.s_parts.g + clr2.s_parts.g > 255)
		clr1.s_parts.g = 255;
	else
		clr1.s_parts.g += clr2.s_parts.g;
	if (clr1.s_parts.b + clr2.s_parts.b > 255)
		clr1.s_parts.b = 255;
	else
		clr1.s_parts.b += clr2.s_parts.b;
	return (clr1.color);
}

int calculate_color(int color, double intensity)
{
	union u_color clr;

	clr.color = color;
	if (clr.s_parts.r * intensity > clr.s_parts.r)
		clr.s_parts.r = clr.s_parts.r;
	else
		clr.s_parts.r *= intensity;
	if (clr.s_parts.g * intensity > clr.s_parts.g)
		clr.s_parts.g = clr.s_parts.g;
	else
		clr.s_parts.g *= intensity;
	if (clr.s_parts.b * intensity > clr.s_parts.b)
		clr.s_parts.b = clr.s_parts.b;
	else
		clr.s_parts.b *= intensity;
	return (clr.color);

}

int		trace_ray(t_rtv1 *rt, t_vect3d *ray, t_roots *t)
{
	t_figure	*cur;
	t_figure	*closest_f;

	closest_f = 0;
	t->closest_t = INF;
	cur = rt->figures;
	while (cur)
	{
		if (intersection(&rt->cam->center, ray, cur, t))
		{
			if (t->t1 > VZ && t->t1 < t->closest_t)
			{
				t->closest_t = t->t1;
				closest_f = cur;
			}
			if (t->t2 > VZ && t->t2 < t->closest_t)
			{
				t->closest_t = t->t2;
				closest_f = cur;
			}
		}
		cur = cur->next;
	}
	if (closest_f == 0)
		return (BACKGROUND);
	return (calc_light(rt, t, closest_f, ray));
}

void		render(t_rtv1 *rt)
{
	int 		x;
	int 		y;
	t_vect3d	ray;
	t_roots		t;

	y = -1;
	while (++y < H)
	{
		x = -1;
		while (++x < W)
		{
			ray = init_vect3d((double)(x - (double)W / 2) * ((double)VW / W),
					-(double)(y - (double)H / 2) * ((double)VH / H), VZ);
			ray = sub_vect3d(&rt->cam->center, &ray);
			((int *)rt->img->data)[x + y * rt->img->size_line / 4]
			= trace_ray(rt, &ray, &t);
		}
	}
	mlx_put_image_to_window(rt->mlx_ptr, rt->win_ptr, rt->img->img_ptr, 0, 0);
}
