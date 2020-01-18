
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
	printf("%.x\n", set_colors(0x99, 0xAA, 0xCC, 0xFF));
    return (0);
}
