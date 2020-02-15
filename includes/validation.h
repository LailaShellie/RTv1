//
// Created by Laila Shellie on 2020-01-18.
//

#ifndef RTV1_VALIDATION_H
#define RTV1_VALIDATION_H

#include "rtv1.h"

# define R 0
# define G 1
# define B 2

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

int					get_vector(char *str, t_vect3d *vect);
int                 get_xyz(char *str, t_vect3d *vect);

double				get_radius(char *str);
double				get_intensity(char *str);
double				get_specularity(char *str);

int					get_type(char *str);
int			        choose_type(char *line);

int					get_color(char *str);
int				    get_rgb(char *str);

t_figure			*new_figure();
void				add_figure(t_figure **figures, t_figure *new);
t_light				*new_light();
void				add_light(t_light **lights, t_light *new);

t_cam				*new_cam();

void		ft_trim(char **line);

/*
** parsing json
*/
int		ft_gotochar(char **str, char ch);
int		ft_goto_endnumber(char **str);
int		ft_goto_endparam(char **str, char openchar);

char	*read_parameter_to_str(char **file);
int		read_json(t_rtv1 *rt, char **file);


#endif
