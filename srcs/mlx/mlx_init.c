
#include "mini_rt.h"

void	initialize_mlx(t_scene *scene)
{
	scene->mlx = mlx_init();
	if (!scene->mlx)
		err_free("Could not initialize mlx", scene);
	scene->win = mlx_new_window(scene->mlx, scene->win_width, scene->win_height,
			"miniRT");
	if (!scene->win)
		err_free("Could not create window", scene);
	scene->img.img = mlx_new_image(scene->mlx, scene->win_width, scene->win_height);
	if (!scene->img.img)
		err_free("Could not create image", scene);
	scene->img.addr = mlx_get_data_addr(scene->img.img, &scene->img.bits_per_pixel,
			&scene->img.line_length, &scene->img.endian);
	if (!scene->img.addr)
		err_free("Could not get image address", scene);
	mlx_hook(scene->win, DestroyNotify, NoEventMask, close_win_handler, scene);
	mlx_hook(scene->win, KeyPress, KeyPressMask, key_hook, scene);
}
