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

void	intersect_ray_sphere(t_vect3d O, t_vect3d D, t_figure *figure, t_roots *roots)
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
		roots->t1 = INF;
		roots->t2 = INF;
	}
	else
	{
		roots->t1 = (-k2 + sqrt(discrim)) / (2 * k1);
    	roots->t2 = (-k2 - sqrt(discrim)) / (2 * k1);
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
							t_figure **figure_closest, t_roots *roots)
{
	t_figure	*figure_curr = NULL;

	roots->closest_t = INF;
	figure_curr = rt->figures;
	while (figure_curr)
	{
		intersect_ray_sphere(O, D, figure_curr, roots);
		if (t_min <= roots->t1 && roots->t1 < roots->closest_t)
		{
			roots->closest_t = roots->t1;
			*figure_closest = figure_curr;
		}
		if (t_min <= roots->t2 && roots->t2 < roots->closest_t)
		{
			roots->closest_t = roots->t2;
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

		t_figure	*shadow_figure = NULL;
		t_roots		shadow_roots;

		closest_intersection(rt, point, L, 0.001, t_max, &shadow_figure, &shadow_roots);
		if (shadow_figure)
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

int		test_trace_ray(t_rtv1 *rt, t_vect3d O, t_vect3d D, double t_min, double t_max, int depth)
{
	t_figure	*figure_closest = NULL;
	t_figure	*figure_curr = NULL;
	t_roots		roots;
	t_vect3d	P;
	t_vect3d	N;
	t_vect3d	V;
	t_vect3d	ray;
	int			local_color;
	double		reflect;
	int			reflected_color;

	closest_intersection(rt, O, D, t_min, t_max, &figure_closest, &roots);

	if (figure_closest == NULL)
		return (rt->background_color);
	else
	{
		P = scale_vect3d(roots.closest_t, &D);
		P = add_vect3d(&O, &P);
		N = sub_vect3d(&figure_closest->center, &P);
		norm_vect3d(&N);
		V = scale_vect3d(-1.0, &D);
		local_color = calculate_color(figure_closest->color, compute_light(rt, P, N, V, figure_closest->s));

		reflect = figure_closest->reflect;
		if (depth <= 0 || reflect <= 0.001)
			return (local_color);
		else
		{
			ray = reflect_ray(&V, &N);
			reflected_color = test_trace_ray(rt, P, ray, 0.001, INF, depth - 1);
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
	t_vect3d	D;
	t_vect3d	O;
	int			color;

	int		Cx, Cy;

	O = init_vect3d(0.0, 0.0, 0.0);
	y = -1;
	while (++y < H)
	{
		x = -1;
		while (++x < W)
		{
			D = canvas_to_viewport(x, y);
			color = test_trace_ray(rt, O, D, 1, INF, 3);
			((int *)rt->img->data)[x + y * rt->img->size_line / 4] = color;
		}
	}
	mlx_put_image_to_window(rt->mlx_ptr, rt->win_ptr, rt->img->img_ptr, 0, 0);
	printf("started render1\n");
}
