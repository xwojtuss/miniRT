/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mlx_hooks.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wkornato <wkornato@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/24 15:40:25 by wkornato          #+#    #+#             */
/*   Updated: 2024/10/01 15:17:35 by wkornato         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini_rt.h"

int	mouse_hook(int x, int y, t_scene *scene)
{
	(void)x;
	(void)y;
	(void)scene;
	// change cam orientation here
	mlx_mouse_move(scene->mlx, scene->win, scene->win_width / 2, scene->win_height / 2);
	return (EXIT_SUCCESS);
}

int	key_hook(int keycode, t_scene *scene)
{
	(void)scene;
	if (keycode == KEY_ESC)
	{
		free_scene(scene);
		exit(EXIT_SUCCESS);
	}
	else if (keycode == XK_w)
		scene->camera->position.z -= 0.5;
	else if (keycode == XK_s)
		scene->camera->position.z += 0.5;
	else if (keycode == XK_a)
		scene->camera->position.x -= 0.5;
	else if (keycode == XK_d)
		scene->camera->position.x += 0.5;
	else if (keycode == XK_space)
		scene->camera->position.y += 0.5;
	else if (keycode == XK_c)
		scene->camera->position.y -= 0.5;
	else if (keycode == XK_equal && scene->camera->fov < 175)
		scene->camera->fov += 5;
	else if (keycode == XK_minus && scene->camera->fov > 5)
		scene->camera->fov -= 5;
	else
		return (EXIT_SUCCESS);
	print_camera_parameters(scene->camera);
	initialize_viewport(scene);
	render_scene(scene);
	return (EXIT_SUCCESS);
}

int	close_win_handler(void *context)
{
	t_scene	*scene;

	scene = (t_scene *)context;
	free_scene(scene);
	exit(EXIT_SUCCESS);
	return (0);
}
