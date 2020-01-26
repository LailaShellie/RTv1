
#include "../rtv1.h"

void test(union u_color col)
{
	printf("%#x %#x %#x %#x %#x\n", col.color, col.s_parts.b, col.s_parts.g, col.s_parts.r, col.s_parts.o);

}

int main(int ac, char** av)
{
    t_rtv1      *rt;

	if (!(rt = ft_memalloc(sizeof(t_rtv1))))
		return (0);
	if (!(validation_main(rt, ac, av)))
		return (ERR);
	if (ERR == init_mlx(rt))
		return (0);
	prepare_figures(rt);
	render(rt);
	hooks(rt);
    return (0);
}
