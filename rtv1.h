
#ifndef RTV1_RTV1_H
# define RTV1_RTV1_H

# include <unistd.h>
# include <fcntl.h>
# include <stdio.h>

# include "mlx/mlx.h"
# include "libft/libft.h"

# define W 800
# define H 800
# define ERR 0

# define X 0
# define Y 1
# define Z 2

typedef struct       s_figure
{
    double       c[3];
    int            type;
    double       r;
}                              t_fgr;

typedef struct		s_img
{
    void			*img_ptr;
    int				bpp;
    int				size_line;
    int				endian;
    char			*data;
}					t_img;

typedef struct  s_rtv1
{
    void              *mlx_ptr;
    void              *win_ptr;
    t_img         *img;
    double       *cam;
    char              *file;
}                     t_rtv1;

int     init_mlx(t_rtv1 *rt);
int     read_file(t_rtv1 *rt, int ac, char **av);
int     parse_file(t_rtv1 *rt);
char       *get_line(char *line);
int 	is_mark(char *line)

#endif
