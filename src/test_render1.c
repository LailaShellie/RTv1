#include "rtv1.h"
#include "validation.h"
#include "test_render.h"

t_vect3d canvas_to_viewport(int x, int y)
{
	t_vect3d	res;
	int			Cx, Cy;

	Cx = x - W / 2;
	Cy = H / 2 - y;

	res.x = (double)Cx * 1.0 / W;
	res.y = (double)Cy * 1.0 / H;
	res.z = 1;
	return (res);
}

void	intersect_ray_sphere(t_vect3d O, t_vect3d D, t_figure *figure, t_calc *calc_params)
{
	double discrim;
	double k1;
	double k2;
	double k3;
	t_vect3d	oc;

	oc = sub_vect3d(&figure->center, &O);
	k1 = dot_vect3d(&D, &D);
	k2 = 2 * dot_vect3d(&oc, &D);
	k3 = dot_vect3d(&oc, &oc) - figure->radius * figure->radius;

	discrim = k2 * k2 - 4 * k1 * k3;
	if (discrim < 0)
	{
		calc_params->t.t1 = INF;
		calc_params->t.t2 = INF;
	}
	else
	{
		calc_params->t.t1 = (-k2 + sqrt(discrim)) / (2 * k1);
    	calc_params->t.t2 = (-k2 - sqrt(discrim)) / (2 * k1);
	}
}

t_vect3d	reflect_ray(t_vect3d *ray, t_vect3d *normal)
{
	t_vect3d	res;

	res = scale_vect3d(2 * dot_vect3d(normal, ray), normal);
	res = sub_vect3d(ray, &res);
	return (res);
}


void	closest_intersection(t_rtv1 *rt, t_vect3d O, t_vect3d D, double t_min, double t_max,
							t_figure **figure_closest, t_calc *calc_params)
{
	t_figure	*figure_curr = NULL;

	calc_params->t.closest_t = INF;
	figure_curr = rt->figures;
	while (figure_curr)
	{
		intersect_ray_sphere(O, D, figure_curr, calc_params);
		if (t_min <= calc_params->t.t1 && calc_params->t.t1 < calc_params->t.closest_t)
		{
			calc_params->t.closest_t = calc_params->t.t1;
			*figure_closest = figure_curr;
		}
		if (t_min <= calc_params->t.t2 && calc_params->t.t2 < calc_params->t.closest_t)
		{
			calc_params->t.closest_t = calc_params->t.t2;
			*figure_closest = figure_curr;
		}
		figure_curr = figure_curr->next;
	}
}

double	compute_light(t_rtv1 *rt, t_vect3d point, t_vect3d normal, t_vect3d V, double specularity)
{
	double		intensity = 0.0;
	t_light		*light;
	t_vect3d	L;
	double		n_dot_l;
	double		r_dot_v;
	double		t_max;

	t_vect3d	ray;

	light = rt->lights;
	while (light)
	{
		if (light->type == AMBIENT)
		{
			intensity += light->i;
			light = light->next;
			continue ;
		}
		else if (light->type == POINT)
		{
			L = sub_vect3d(&point, &light->center);
			t_max = 1;
		}
		else
		{
			L = light->direction;
			t_max = INF;
		}

		t_roots		shadow_roots;
		t_calc		shadow_calcs;

		shadow_calcs.closest_f = NULL;

		closest_intersection(rt, point, L, 0.001, t_max, &(shadow_calcs.closest_f), &shadow_calcs);
		if (shadow_calcs.closest_f)
		{
			light = light->next;
			continue ;
		}

		n_dot_l = dot_vect3d(&normal, &L);
		if (n_dot_l > 0)
			intensity += light->i * n_dot_l / (length_vect3d(&normal) * length_vect3d(&L));

		if (specularity > 0)
		{
			ray = reflect_ray(&L ,&normal);
			// ray = scale_vect3d(2 * n_dot_l, &normal);
			// ray = sub_vect3d(&L, &ray);
			r_dot_v = dot_vect3d(&ray, &V);
			if (r_dot_v > 0)
				intensity += light->i * pow(r_dot_v / (length_vect3d(&ray) * length_vect3d(&V)), specularity);
		}

		light = light->next;
	}
	return (intensity);
}

int		test_trace_ray(t_rtv1 *rt, t_trace_ray_params trace_params)
{
	// t_figure	*figure_closest = NULL;
	t_figure	*figure_curr = NULL;
	t_calc		calc_params;
	t_vect3d	P;
	t_vect3d	N;
	t_vect3d	V;
	t_vect3d	reflected_ray;
	int			local_color;
	double		reflect;
	int			reflected_color;

	calc_params.closest_f = NULL;
	closest_intersection(rt, trace_params.o, trace_params.d,
								trace_params.t_min, trace_params.t_max, &(calc_params.closest_f), &calc_params);

	if (calc_params.closest_f == NULL)
		return (rt->background_color);
	else
	{
		P = scale_vect3d(calc_params.t.closest_t, &trace_params.d);
		P = add_vect3d(&trace_params.o, &P);
		N = sub_vect3d(&calc_params.closest_f->center, &P);
		norm_vect3d(&N);
		V = scale_vect3d(-1.0, &trace_params.d);
		local_color = calculate_color(calc_params.closest_f->color, compute_light(rt, P, N, V, calc_params.closest_f->s));

		reflect = calc_params.closest_f->reflect;
		if (trace_params.reflection_depth <= 0 || reflect <= 0.001)
			return (local_color);
		else
		{
			reflected_ray = reflect_ray(&V, &N);

			t_trace_ray_params		trace_params_reflect;

			trace_params_reflect.o = P;
			trace_params_reflect.d = reflected_ray;
			trace_params_reflect.t_min = 0.001;
			trace_params_reflect.t_max = INF;
			trace_params_reflect.reflection_depth = trace_params.reflection_depth - 1;
			reflected_color = test_trace_ray(rt, trace_params_reflect);
			local_color = calculate_color(local_color, 1 - reflect);
			reflected_color = calculate_color(reflected_color, reflect);
			return (sum_color(local_color, reflected_color));
		}
	}
}

void test_render(t_rtv1 *rt)
{
	int		x;
	int		y;
	t_trace_ray_params	trace_params;
	int			color;
	t_rot	rot_matrixes;

	trace_params.o = rt->cam->center;
	y = -1;
	calc_rotate_all(&rot_matrixes, &rt->cam->rotation);
	while (++y < H)
	{
		x = -1;
		while (++x < W)
		{

			trace_params.d = canvas_to_viewport(x, y);
			trace_params.d = mult_vect3d_rmatrix(&trace_params.d, rot_matrixes.r_all);
			trace_params.t_min = 1;
			trace_params.t_max = INF;
			trace_params.reflection_depth = rt->reflection_depth;
			color = test_trace_ray(rt, trace_params);
			((int *)rt->img->data)[x + y * rt->img->size_line / 4] = color;
		}
	}
	mlx_put_image_to_window(rt->mlx_ptr, rt->win_ptr, rt->img->img_ptr, 0, 0);
	printf("started render1\n");
}
