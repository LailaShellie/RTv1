//
// Created by Laila Shellie on 2020-01-18.
//

#ifndef RTV1_VALIDATION_H
#define RTV1_VALIDATION_H

#include "../../rtv1.h"

# define ARG1 1
# define ARG2 2
# define ARG3 3
# define ARG4 4
# define ARG5 5
# define ARG6 6

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
