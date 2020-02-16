//
// Created by Laila Shellie on 2020-01-31.
//

#include "rtv1.h"

#define SPEC 100

double		get_specular(t_rtv1 *rt, t_light *light)
{
    t_vect3d	l;
    t_vect3d    r;
    double      r_dot_v;
    t_vect3d    v;
    double      dot;

    l = sub_vect3d(&rt->calc.p, &light->center);
    dot = dot_vect3d(&l, &rt->calc.n);
    if (dot < 0)
        return (0);
    v = sub_vect3d(&rt->calc.p, &rt->cam->center);
    r = init_vect3d(2 * rt->calc.n.x * dot - l.x,
            2 * rt->calc.n.y * dot - l.y,
            2 * rt->calc.n.z * dot - l.z);
    r_dot_v = dot_vect3d(&r, &v);
    if (r_dot_v > 0)
        return (light->i * pow(r_dot_v / (length_vect3d(&r) * length_vect3d(&v)), SPEC) / rt->total_light);
	return (0);
}