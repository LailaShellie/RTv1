/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rtv1.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lshellie <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/29 13:41:37 by lshellie          #+#    #+#             */
/*   Updated: 2020/02/29 13:41:39 by lshellie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

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
# define ERR_1 NAN
# define INF INFINITY

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

union					u_color
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

typedef struct			s_rot
{
	double				r_x[16];
	double				r_y[16];
	double				r_z[16];
	double				r_persp[16];
	double				r_all[16];
}						t_rot;

typedef	struct			s_roots
{
	double				t1;
	double				t2;
	double				closest_t;
}						t_roots;

typedef struct			s_vect3d
{
	double				x;
	double				y;
	double				z;
}						t_vect3d;

typedef struct			s_cam
{
	t_vect3d			center;
	t_vect3d			direction;
	t_vect3d			rotation;
	t_vect3d			v1;
	t_vect3d			v2;
	t_vect3d			v3;
}						t_cam;

typedef struct			s_light
{
	int					type;
	t_vect3d			center;
	t_vect3d			direction;
	double				i;
	struct s_light		*next;
}						t_light;

typedef struct			s_figure
{
	int					type;
	t_vect3d			center;
	t_vect3d			direction;
	t_vect3d			v1;
	t_vect3d			v2;
	t_vect3d			v3;
	int					color;
	double				radius;
	double				s;
	double				reflect;
	struct s_figure		*next;
}						t_figure;

typedef struct			s_img
{
	void				*img_ptr;
	char				*data;
	int					bpp;
	int					size_line;
	int					endian;
}						t_img;

typedef struct			s_calc
{
	t_vect3d			ray;
	t_vect3d			p;
	t_vect3d			n;
	t_vect3d			v;
	t_roots				t;
	t_figure			*closest_f;
}						t_calc;

typedef struct			s_trace_ray_params
{
	t_vect3d			o;
	t_vect3d			d;
	double				t_min;
	double				t_max;
	int					reflection_depth;
}						t_trace_ray_params;
typedef struct			s_rtv1
{
	void				*mlx_ptr;
	void				*win_ptr;
	t_img				*img;
	char				*title;
	int					total_light;
	int					background_color;
	int					reflection_depth;
	t_rot				rotation_matrixes;
	t_cam				*cam;
	t_light				*lights;
	t_figure			*figures;
	t_calc				calc;
}						t_rtv1;

int						init_mlx(t_rtv1 *rt);
void					prepare_figures(t_rtv1 *rt);

t_vect3d				scale_vect3d(double scale, t_vect3d *a);
void					norm_vect3d(t_vect3d *vect);
t_vect3d				init_vect3d(double x, double y, double z);
double					length_vect3d(t_vect3d *a);
t_vect3d				sub_vect3d(t_vect3d *start, t_vect3d *end);
t_vect3d				add_vect3d(t_vect3d *start, t_vect3d *end);
double					dot_vect3d(t_vect3d *a, t_vect3d *b);
t_vect3d				cross_vect3d(t_vect3d *a, t_vect3d *b);
void					print_vect3d(t_vect3d *a);

void					render(t_rtv1 *rt);
int						trace_ray(t_rtv1 *rt, t_vect3d *ray, t_vect3d *point);
void					hooks(t_rtv1 *rt);

t_roots					intersection(t_vect3d *ray,
		t_vect3d *p, t_figure *figure);

int						calc_light(t_rtv1 *rt);
double					get_diffusive(t_rtv1 *rt, t_light *light);
double					get_specular(t_rtv1 *rt, t_light *light);

void					get_normal_of_figure(t_rtv1 *rt);

int						calculate_color(int color, double intensity);
int						sum_color(int color1, int color2);
void					free_rtv1(t_rtv1 *rt);
t_roots					manage(double a, double b, double c);
int						ft_close(t_rtv1 *rt);

#endif
