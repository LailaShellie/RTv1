#include "rtv1.h"

int			testing(int key, t_rtv1 *rt)
{
	printf("%d\n", key);
	if (key >= 123 && key <= 126)
	{
		if (key == 123)
			rt->cam->center.x -= 0.1;
		if (key == 124)
			rt->cam->center.x += 0.1;
		if (key == 126)
			rt->cam->center.z += 0.1;
		if (key == 125)
			rt->cam->center.z -= 0.1;
		prepare_figures(rt);
		render(rt);
	}
	if (key == 24)
	{
		rt->cam->center.y += 0.1;
		prepare_figures(rt);
		render(rt);
	}
	else if (key == 27)
	{
		rt->cam->center.y -= 0.1;
		prepare_figures(rt);
		render(rt);
	}

	return (1);
}

int			ft_close(t_rtv1 *rt)
{
	exit(0);
}

void		hooks(t_rtv1 *rt)
{
	mlx_hook(rt->win_ptr, 2, 0, testing, rt);
	mlx_hook(rt->win_ptr, 17, 0, ft_close, rt);
	mlx_loop(rt->mlx_ptr);
}

int  init_mlx(t_rtv1 *rt)
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
