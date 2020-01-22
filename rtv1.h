
#ifndef RTV1_RTV1_H
# define RTV1_RTV1_H

# include <unistd.h>
# include <fcntl.h>
# include <stdio.h>
# include <math.h>

# include "mlx/mlx.h"
# include "libft/libft.h"

# define W 800
# define H 800

# define VW 1
# define VH 1
# define VZ 1

# define ERR 0
# define ERR_1 0.0 / 0.0
# define INF 1.0 / 0.0

# define X 0
# define Y 1
# define Z 2

# define SPHERE 1
# define CONE 2
# define PLANE 3
# define CYLINDER 4

# define CAM 0
# define LIGHTS 2

# define BACKGROUND 0x000000

typedef	struct		s_roots
{
	double			t1;
	double			t2;
	double			closest_t;
}					t_roots;

typedef struct		s_vect3d
{
	double			*xyz;
}					t_vect3d;

typedef struct		s_cam
{
	t_vect3d		*center;
	t_vect3d		*direction;
}					t_cam;

typedef struct		s_light
{
	t_vect3d		*ccenter;
	double			i;
	struct s_light	*next;
}					t_light;

typedef struct		s_figure
{
	int				type;
    t_vect3d		*center;
	t_vect3d		*direction;
	t_vect3d		*oc;
	int				color;
    double			radius;
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
int					validation_main(t_rtv1 *rt, int ac, char **av);
int					set_colors(unsigned char o, unsigned char r, \
			unsigned char g, unsigned char b);
t_vect3d			*new_vect3d();
void	init_vect3d(t_vect3d *vect, double x, double y, double z);
void		sub_vect3d(t_vect3d *res, t_vect3d *start, t_vect3d *end);
void		add_vect3d(t_vect3d *res, t_vect3d *start, t_vect3d *end);
double		dot_vect3d(t_vect3d *a, t_vect3d *b);
void	free_vect3d(t_vect3d *vect);
void	norm_vect(t_vect3d *vect);
double		length_vect3d(t_vect3d *a);
void		print_vect3d(t_vect3d *a);

void		render(t_rtv1 *rt);
void		hooks(t_rtv1 *rt);

int		intersection(t_vect3d *cam_pos, t_vect3d *ray, t_figure *figure, t_roots *t);

double		calc_light(t_rtv1 *rt, t_roots *t,
						  t_figure *f, t_vect3d *ray, t_vect3d *cam_pos);
double		get_normal(t_figure *f, t_vect3d *ray,
						 t_vect3d *cam_pos, t_roots *t, t_light *light);

#endif
