/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mlx_hooks.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wkornato <wkornato@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/24 15:40:25 by wkornato          #+#    #+#             */
/*   Updated: 2024/12/19 21:18:39 by wkornato         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini_rt.h"

int	key_hook(int keycode, t_scene *scene)
{
	if (keycode == KEY_ESC)
	{
		free_scene(scene);
		exit(EXIT_SUCCESS);
	}
	else if (!DEBUG_TOOLS || !check_debug_tools(keycode, scene))
		return (EXIT_SUCCESS);
	initialize_viewport(scene);
	render_scene(scene);
	return (EXIT_SUCCESS);
}

int	mouse_click_handler(int button, int x, int y, t_scene *scene)
{
	t_vector	pixel_center;
	t_vector	ray_direction;
	t_ray		ray;
	double		temp;
	t_objects	*object;

	if (button != 1)
		return (EXIT_SUCCESS);
	temp = 0;
	pixel_center = add_v(scene->viewport_top_left,
			add_v(multiply_v(scene->viewport_grid_vector_x, x),
				multiply_v(scene->viewport_grid_vector_y, y)));
	ray_direction = subtract_v(pixel_center, scene->camera->position);
	ray = (t_ray){scene->camera->position, ray_direction};
	object = get_closest_object(*scene, ray, &temp);
	if (object)
		print_object_parameters(object);
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
