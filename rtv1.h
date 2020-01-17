
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
# define ERR_1 0.0 / 0.0

# define X 0
# define Y 1
# define Z 2

# define R 0
# define G 1
# define B 2

# define ARG1 1
# define ARG2 2
# define ARG3 3
# define ARG4 4
# define ARG5 5
# define ARG6 6

# define SPHERE 1
# define CONE 2
# define PLANE 3
# define CYLINDER 4

# define CAM 0
# define LIGHTS 2

# define COORDS_NUM 3
# define POSITION 2

typedef struct		s_cam
{
	double			*xyz1;
	double			*xyz2;
}					t_cam;

typedef struct		s_light
{
	double			*c;
	double			i;
	struct s_light	*next;
}					t_light;

typedef struct		s_figure
{
	int				type;
    double			*c;
	double			*v;
	int				*color;
    double			r;
    double			s;
	struct s_figure	*next;
}					t_figure;

typedef struct		s_img
{
    void			*img_ptr;
    int				bpp;
    int				size_line;
    int				endian;
    char			*data;
}					t_img;

typedef struct		s_rtv1
{
    void			*mlx_ptr;
    void			*win_ptr;
    t_img			*img;
    char			*file;
    char			**split;
    t_cam			*cam;
    t_light			*lights;
    t_figure		*figures;
}                     t_rtv1;

int					init_mlx(t_rtv1 *rt);

int					read_file(t_rtv1 *rt, int ac, char **av);
int					parse_file(t_rtv1 *rt);

int					is_mark(char *str);
int					is_param(char *str);
int					is_figure(char *str);
int					count_split(char **split);
char				**check_param(char *str);
int					parse_marks(t_rtv1 *rt, char ***marks);

double				*get_point(char *str);
double				*get_vector(char *str);

double				get_radius(char *str);
double				get_intensity(char *str);
double				get_specularity(char *str);

int					get_type(char *str);

int					*get_color(char *str);

t_figure			*new_figure();
void				add_figure(t_figure **figures, t_figure *new);
t_light				*new_light();
void				add_light(t_light **lights, t_light *new);

#endif
