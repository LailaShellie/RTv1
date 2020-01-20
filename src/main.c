
#include "../rtv1.h"

int main(int ac, char** av)
{
    t_rtv1      *rt;

	if (!(rt = ft_memalloc(sizeof(t_rtv1))))
		exit(0);
	if (!(validation_main(rt, ac, av)))
		return (ERR);
	if (ERR == init_mlx(rt))
		exit(0);
	render(rt);
	mlx_put_image_to_window(rt->mlx_ptr, rt->win_ptr, rt->img->img_ptr, 0, 0);
	hooks(rt);
    return (0);
}
