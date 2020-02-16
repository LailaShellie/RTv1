#include "rtv1.h"
#include "validation.h"
#include "errno.h"

void		print_figure(t_figure *figure)
{
	printf("\t\t\tfigure data:\n");
	printf("\t\t\t\ttype: %d\n", figure->type);
	printf("\t\t\t\tcenter: "); print_vect3d(&figure->center);
	printf("\t\t\t\tdirection: "); print_vect3d(&figure->direction);
	printf("\t\t\t\tcolor: 0x%06x\n", figure->color);
	printf("\t\t\t\tradius: %lf\n", figure->radius);
	printf("\t\t\t\tspecularity: %lf\n", figure->s);
}

void		print_light(t_light *light)
{
	printf("\t\t\tlight data:\n");
	printf("\t\t\t\tcenter: "); print_vect3d(&light->center);
	printf("\t\t\t\tintensity: %lf\n", light->i);
}

void		print_camera(t_cam *cam)
{
	printf("\t\t\tcamera data:\n");
	printf("\t\t\t\tcenter: "); print_vect3d(&cam->center);
	printf("\t\t\t\tdirection: "); print_vect3d(&cam->direction);
}
