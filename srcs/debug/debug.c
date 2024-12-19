/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   debug.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wkornato <wkornato@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/22 19:54:01 by wkornato          #+#    #+#             */
/*   Updated: 2024/12/19 21:18:48 by wkornato         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini_rt.h"

void	print_vector(t_vector vector)
{
	printf("vector: %f, %f, %f\n", vector.x, vector.y, vector.z);
}

void	print_array(char **array)
{
	int	i;

	i = 0;
	if (!array)
		return ;
	while (array[i])
	{
		printf("%s\n", array[i]);
		i++;
	}
}

static void	rotate_camera(t_camera *camera, t_vector rotation, t_vector axis,
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

static bool	check_camera_debug_tools(int keycode, t_scene *scene)
{
	if (keycode == XK_equal && scene->camera->fov < 175)
		scene->camera->fov += 5;
	else if (keycode == XK_minus && scene->camera->fov > 5)
		scene->camera->fov -= 5;
	else if (keycode == XK_Up
		&& scene->camera->orientation.y < FLOAT_PITCH_LIMIT)
		rotate_camera(scene->camera, (t_vector){1, 0, 0},
			multiply_v(scene->camera->right, -1.0), deg_to_rad(ROTATE_DEGREE));
	else if (keycode == XK_Down
		&& scene->camera->orientation.y > -FLOAT_PITCH_LIMIT)
		rotate_camera(scene->camera, (t_vector){-1, 0, 0}, scene->camera->right,
			deg_to_rad(ROTATE_DEGREE));
	else if (keycode == XK_Left)
		rotate_camera(scene->camera, (t_vector){0, -1, 0}, scene->camera->up,
			deg_to_rad(ROTATE_DEGREE));
	else if (keycode == XK_Right)
		rotate_camera(scene->camera, (t_vector){0, 1, 0},
			multiply_v(scene->camera->up, -1.0), deg_to_rad(ROTATE_DEGREE));
	else
		return (false);
	return (true);
}

bool	check_debug_tools(int keycode, t_scene *scene)
{
	if (keycode == XK_w)
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
	else if (keycode == XK_p)
		print_objects_parameters(scene);
	else if (!check_camera_debug_tools(keycode, scene))
		return (false);
	return (true);
}
