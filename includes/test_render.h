#ifndef TEST_RENDER_H
# define TEST_RENDER_H

#include "rtv1.h"
typedef struct		s_rot
{
	double			r_x[16];
	double			r_y[16];
	double			r_z[16];
	double			r_persp[16];
	double			r_all[16];
}					t_rot;


void test_render(t_rtv1 *rt);

/*
** rotation functions
** file rotation.c
*/

void				set_rotate_matrix_zero(double *m);
void				set_rotate_matrix_one(double *m);
void				calc_rotate_x(t_rot *mr, int x_angle);
void				calc_rotate_y(t_rot *mr, int y_angle);
void				calc_rotate_z(t_rot *mr, int z_angle);
void				mult_rmatrix(double *res, double *a, double *b);
void				calc_r_x_y_z(t_rot *mr, t_vect3d *angles);
void				calc_rotate_all(t_rot *mr, t_vect3d *angles);
t_vect3d			mult_vect3d_rmatrix(t_vect3d *ray, double *rmatrix);



t_roots		intersect_cylinder(t_vect3d *ray, t_vect3d *o, t_figure *f);

#endif
