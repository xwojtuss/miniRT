#include "mini_rt.h"

void	init_scene(t_scene *scene)
{
	scene->win_height = WIN_HEIGHT_DEFAULT;
	scene->win_width = WIN_WIDTH_DEFAULT;
	scene->mlx = NULL;
	scene->win = NULL;
	scene->objects = NULL;
	scene->light = NULL;
	scene->ambient = NULL;
	scene->camera = NULL;
}
