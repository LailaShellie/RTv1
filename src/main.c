
#include "../rtv1.h"

int main(int ac, char** av)
{
    t_rtv1      *rt;

	if (!(rt = ft_memalloc(sizeof(t_rtv1))))
		exit(0);
	if (ERR == read_file(rt, ac, av))
		exit(0);
	if (ERR == parse_file(rt))
	{
		ft_putendl("Error");
		return (0);
	}
//	if (ERR == init_mlx(rt))
//		exit(0);
    return (0);
}
