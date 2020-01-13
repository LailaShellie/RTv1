#include "../rtv1.h"


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
