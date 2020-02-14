#include "rtv1.h"
#include "validation.h"

void test(union u_color col)
{
	printf("%#x %#x %#x %#x %#x\n", col.color, col.s_parts.b, col.s_parts.g, col.s_parts.r, col.s_parts.o);

}

int main(int ac, char** av)
{
    t_rtv1      *rt;

	if (!(rt = ft_memalloc(sizeof(t_rtv1))))
		return (0);

	// checking reading file
	int		fd;
	char	*file;

	if (ac != 2)
		return (ERR);
	if ((fd = open(av[1], O_RDONLY)) == -1)
		return (ERR);
	file = ft_filetrim_stop(fd, " \t\n", "//");
	printf("%s\n", file);

	read_json(rt, &file);
	//ft_memdel((void**)&file);
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
