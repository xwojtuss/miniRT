/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mlx_hooks.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wkornato <wkornato@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/24 15:40:25 by wkornato          #+#    #+#             */
/*   Updated: 2024/11/19 15:20:33 by wkornato         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini_rt.h"

void	rotate_camera(t_camera *camera, t_vector rotation, t_vector axis,
		float angle)
{
	rotation = normalize_vector(rotation);
	camera->orientation = add_v(multiply_v(camera->orientation, cos(angle)),
			multiply_v(cross_product(axis, camera->orientation), sin(angle)));
	camera->orientation = normalize_vector(camera->orientation);
	camera->right = normalize_vector(cross_product((t_vector){0, 1, 0},
				camera->orientation));
	camera->up = normalize_vector(cross_product(camera->orientation,
				camera->right));
}

int	mouse_hook(int x, int y, t_scene *scene)
{
	int	x_from_center;
	int	y_from_center;

	x_from_center = x - scene->win_width / 2;
	y_from_center = y - scene->win_height / 2;
	if (x_from_center == 0 && y_from_center == 0)
		return (EXIT_SUCCESS);
	if (y_from_center < 0 && scene->camera->orientation.y < FLOAT_PITCH_LIMIT)
		rotate_camera(scene->camera, (t_vector){1, 0, 0},
			multiply_v(scene->camera->right, -1.0),
			deg_to_rad(MOUSE_SENSITIVITY));
	else if (y_from_center > 0 && scene->camera->orientation.y >
		-FLOAT_PITCH_LIMIT)
		rotate_camera(scene->camera, (t_vector){-1, 0, 0}, scene->camera->right,
			deg_to_rad(MOUSE_SENSITIVITY));
	if (x_from_center < 0)
		rotate_camera(scene->camera, (t_vector){0, -1, 0}, scene->camera->up,
			deg_to_rad(MOUSE_SENSITIVITY));
	else if (x_from_center > 0)
		rotate_camera(scene->camera, (t_vector){0, 1, 0},
			multiply_v(scene->camera->up, -1.0), deg_to_rad(MOUSE_SENSITIVITY));
	else
		return (EXIT_SUCCESS);
	initialize_viewport(scene);
	render_scene(scene);
	mlx_mouse_move(scene->mlx, scene->win, scene->win_width / 2,
		scene->win_height / 2);
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
		scene->camera->position = subtract_v(scene->camera->position,
				multiply_v(scene->camera->orientation, MOVE_STEP));
	else if (keycode == XK_s)
		scene->camera->position = add_v(scene->camera->position,
				multiply_v(scene->camera->orientation, MOVE_STEP));
	else if (keycode == XK_a)
		scene->camera->position = subtract_v(scene->camera->position,
				multiply_v(scene->camera->right, MOVE_STEP));
	else if (keycode == XK_d)
		scene->camera->position = add_v(scene->camera->position,
				multiply_v(scene->camera->right, MOVE_STEP));
	else if (keycode == XK_space)
		scene->camera->position = subtract_v(scene->camera->position,
				multiply_v(scene->camera->up, MOVE_STEP));
	else if (keycode == XK_c)
		scene->camera->position = add_v(scene->camera->position,
				multiply_v(scene->camera->up, MOVE_STEP));
	else if (keycode == XK_equal && scene->camera->fov < 175)
		scene->camera->fov += 5;
	else if (keycode == XK_minus && scene->camera->fov > 5)
		scene->camera->fov -= 5;
	else if (keycode == XK_Up
		&& scene->camera->orientation.y < FLOAT_PITCH_LIMIT)
		rotate_camera(scene->camera, (t_vector){1, 0, 0},
			multiply_v(scene->camera->right, -1.0), deg_to_rad(ROTATE_DEGREE));
	else if (keycode == XK_Down && scene->camera->orientation.y >
		-FLOAT_PITCH_LIMIT)
		rotate_camera(scene->camera, (t_vector){-1, 0, 0}, scene->camera->right,
			deg_to_rad(ROTATE_DEGREE));
	else if (keycode == XK_Left)
		rotate_camera(scene->camera, (t_vector){0, -1, 0}, scene->camera->up,
			deg_to_rad(ROTATE_DEGREE));
	else if (keycode == XK_Right)
		rotate_camera(scene->camera, (t_vector){0, 1, 0},
			multiply_v(scene->camera->up, -1.0), deg_to_rad(ROTATE_DEGREE));
	else if (keycode == XK_p)
		print_objects_parameters(scene);
	else
		return (EXIT_SUCCESS);
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
