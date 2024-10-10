/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mlx_hooks.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wkornato <wkornato@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/24 15:40:25 by wkornato          #+#    #+#             */
/*   Updated: 2024/10/10 19:05:42 by wkornato         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini_rt.h"

int	mouse_hook(int x, int y, t_scene *scene)
{
	(void)x;
	(void)y;
	(void)scene;
	// this is where we will rotate the camera using mouse
	mlx_mouse_move(scene->mlx, scene->win, scene->win_width / 2,
		scene->win_height / 2);
	return (EXIT_SUCCESS);
}

void	rotate_camera(t_camera *camera, t_vector rotation)
{
	t_vector	cross;
	float	dot;

	cross = cross_product(camera->orientation, rotation);
	dot = dot_product(camera->orientation, rotation);
	camera->orientation = add_v(multiply_v(camera->orientation, cos(deg_to_rad(ROTATE_DEGREE))), add_v(multiply_v(cross, sin(deg_to_rad(ROTATE_DEGREE))), multiply_v(rotation, dot * (1 - cos(deg_to_rad(ROTATE_DEGREE))))));
	camera->orientation = normalize_vector(camera->orientation);
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
		scene->camera->position.z -= MOVE_STEP;
	else if (keycode == XK_s)
		scene->camera->position.z += MOVE_STEP;
	else if (keycode == XK_a)
		scene->camera->position.x -= MOVE_STEP;
	else if (keycode == XK_d)
		scene->camera->position.x += MOVE_STEP;
	else if (keycode == XK_space)
		scene->camera->position.y += MOVE_STEP;
	else if (keycode == XK_c)
		scene->camera->position.y -= MOVE_STEP;
	else if (keycode == XK_equal && scene->camera->fov < 175)
		scene->camera->fov += 5;
	else if (keycode == XK_minus && scene->camera->fov > 5)
		scene->camera->fov -= 5;
	else if (keycode == XK_Up)
		rotate_camera(scene->camera, (t_vector){1, 0, 0});
	else if (keycode == XK_Down)
		rotate_camera(scene->camera, (t_vector){-1, 0, 0});
	else if (keycode == XK_Left)
		rotate_camera(scene->camera, (t_vector){0, -1, 0});
	else if (keycode == XK_Right)
		rotate_camera(scene->camera, (t_vector){0, 1, 0});
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
