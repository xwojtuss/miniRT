/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wkornato <wkornato@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/22 19:54:06 by wkornato          #+#    #+#             */
/*   Updated: 2024/08/23 11:02:38 by wkornato         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini_rt.h"

void	read_scene(t_scene *scene, char *file)
{
	int	fd;

	fd = open(file, O_RDONLY);
	if (fd < 0)
		err_free("Could not open file", scene);
	while (true)
	{
		if (!parse_line(scene, fd))
			break ;
	}
	close(fd);
}

int	key_hook(int keycode, t_scene *scene)
{
	(void)scene;
	if (keycode == KEY_ESC)
	{
		free_scene(scene);
		exit(EXIT_SUCCESS);
	}
	return (0);
}

int	main(int argc, char **argv)
{
	t_scene	scene;

	if (argc != 2)
		err("Invalid number of arguments");
	init_scene(&scene);
	read_scene(&scene, argv[1]);
	check_scene(&scene);
	scene.mlx = mlx_init();
	if (!scene.mlx)
		err_free("Could not initialize mlx", &scene);
	scene.win = mlx_new_window(scene.mlx, scene.win_width, scene.win_height,
			"miniRT");
	if (!scene.win)
		err_free("Could not create window", &scene);
	mlx_hook(scene.win, ClientMessage, NoEventMask, close_win_handler, &scene);
	mlx_hook(scene.win, KeyPress, KeyPressMask, key_hook, &scene);
	render_scene(&scene);
	mlx_loop(scene.mlx);
	free_scene(&scene);
	return (0);
}