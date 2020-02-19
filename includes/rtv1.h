
#ifndef RTV1_RTV1_H
# define RTV1_RTV1_H

# include <unistd.h>
# include <fcntl.h>
# include <stdio.h>
# include <math.h>

# include "mlx.h"
# include "libft.h"

# define W 800
# define H 800

# define VW 1
# define VH 1
# define VZ 2

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

# define POINT 0
# define AMBIENT 1
# define DIRECTIONAL 2

# define FDF_KEY_ESC 53
# define FDF_KEY_Q 12

# define BACKGROUND 0x000000

union				u_color
{
	int					color;
	struct
	{
		unsigned char	b : 8;
		unsigned char	g : 8;
		unsigned char	r : 8;
		unsigned char	o : 8;
	}					s_parts;
};

typedef	struct		s_roots
{
	double			t1;
	double			t2;
	double			closest_t;
}					t_roots;

typedef struct		s_vect3d
{
	double			x;
	double			y;
	double			z;
}					t_vect3d;

typedef struct		s_cam
{
	t_vect3d		center;
	t_vect3d		direction;
	t_vect3d		rotation;
    t_vect3d		v1;
    t_vect3d		v2;
    t_vect3d		v3;
}					t_cam;

typedef struct		s_light
{
	int				type;
	t_vect3d		center;
	t_vect3d		direction;
	double			i;
	struct s_light	*next;
}					t_light;

typedef struct		s_figure
{
	int				type;
    t_vect3d		center;
	t_vect3d		direction;
	t_vect3d		v1;
	t_vect3d		v2;
	t_vect3d		v3;
	t_vect3d		oc;
	int				color;
    double			radius;
    double			s;
	double			reflect;
	struct s_figure	*next;
}					t_figure;

typedef struct		s_img
{
    void			*img_ptr;
	char			*data;
    int				bpp;
    int				size_line;
    int				endian;
}					t_img;

typedef struct      s_calc
{
    t_vect3d        ray;
    t_vect3d        p;
    t_vect3d        n;
    t_roots         t;
    t_figure        *closest_f;
}                   t_calc;

typedef struct		s_rtv1
{
    void			*mlx_ptr;
    void			*win_ptr;
    t_img			*img;
    char			*file;
    char			**split;
	char			*title;
    int             total_light;
	int				background_color;
    t_cam			*cam;
    t_light			*lights;
    t_figure		*figures;
    t_calc          calc;
}                     t_rtv1;

int					init_mlx(t_rtv1 *rt);
int					validation_main(t_rtv1 *rt, int ac, char **av);
void				prepare_figures(t_rtv1 *rt);

t_vect3d			scale_vect3d(double scale, t_vect3d *a);
void				norm_vect3d(t_vect3d *vect);
t_vect3d			init_vect3d(double x, double y, double z);
double				length_vect3d(t_vect3d *a);
t_vect3d			sub_vect3d(t_vect3d *start, t_vect3d *end);
t_vect3d			add_vect3d(t_vect3d *start, t_vect3d *end);
double				dot_vect3d(t_vect3d *a, t_vect3d *b);
t_vect3d            cross_vect3d(t_vect3d *a, t_vect3d *b);
void				print_vect3d(t_vect3d *a);

void				render(t_rtv1 *rt);
int					trace_ray(t_rtv1 *rt);
void				hooks(t_rtv1 *rt);

int					intersection(t_rtv1 *rt, t_figure *figure);

int					calc_light(t_rtv1 *rt);
double				get_diffusive(t_rtv1 *rt, t_light *light);
double				get_specular(t_rtv1 *rt, t_light *light);

int 				check_light(t_rtv1 *rt, t_vect3d *p, t_light *light);

void			get_normal_of_figure(t_rtv1 *rt);

int					calculate_color(int color, double intensity);
int	sum_color(int color1, int color2);

#endif
