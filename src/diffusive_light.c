//
// Created by Laila Shellie on 2020-01-22.
//

#include "rtv1.h"

double		get_diffusive(t_rtv1 *rt, t_light *light)
{
    t_vect3d	l;

    l = sub_vect3d(&rt->calc.p, &light->center);
    norm_vect3d(&l);

    double dot = dot_vect3d(&l, &rt->calc.n);

    if (dot > 0)
        return (light->i * dot / rt->total_light);
    return (0);
}
