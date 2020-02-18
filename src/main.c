#include "rtv1.h"
#include "validation.h"
#include "test_render.h"

void test(union u_color col)
{
	printf("%#x %#x %#x %#x %#x\n", col.color, col.s_parts.b, col.s_parts.g, col.s_parts.r, col.s_parts.o);

}

int main(int ac, char** av)
{
	t_rtv1		*rt;
	int			fd;
	int			is_test_render = 0;

	if (!(rt = ft_memalloc(sizeof(t_rtv1))))
		return (0);
	if (ac != 2)
	{
		if (ac == 3 && ft_strequ(av[2], "--test-render"))
			is_test_render = 1;
		else
			return (ERR);
	}
	if ((fd = open(av[1], O_RDONLY)) == -1)
		return (ERR);
	if (!(read_json(rt, fd)))
		return (ERR);
	if (ERR == init_mlx(rt))
		return (0);
	if (!is_test_render)
	{
		prepare_figures(rt);
		render(rt);
		hooks(rt);
	}
	else
	{
		test_render(rt);
		hooks(rt);
	}
    return (0);
}
