/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   initialize.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wkornato <wkornato@student.42warsaw.pl>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/24 15:40:37 by wkornato          #+#    #+#             */
/*   Updated: 2024/12/31 17:22:06 by wkornato         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini_rt.h"

static void	setup_screen(t_scene *scene)
{
	t_vector	width_vector;
	t_vector	height_vector;
	t_vector	*vtl;

	vtl = &scene->viewport_top_left;
	width_vector = multiply_v(scene->camera->right, scene->viewport_width);
	height_vector = multiply_v(scene->camera->up, scene->viewport_height);
	scene->viewport_grid_vector_x = divide_v(width_vector,
			(double)(scene->image_width));
	scene->viewport_grid_vector_y = divide_v(height_vector,
			(double)(scene->image_height));
	*vtl = subtract_v(subtract_v(subtract_v(scene->camera->position,
					scene->camera->orientation),
				divide_v(scene->viewport_grid_vector_x, 2.0)),
			divide_v(scene->viewport_grid_vector_y, 2.0));
	scene->viewport_top_left = subtract_v(scene->viewport_top_left,
			divide_v(height_vector, 2.0));
	scene->viewport_top_left = subtract_v(scene->viewport_top_left,
			divide_v(width_vector, 2.0));
}

void	initialize_viewport(t_scene *scene)
{
	double		aspect_ratio;
	t_camera	*camera;

	camera = scene->camera;
	aspect_ratio = (double)(scene->win_width) / (double)(scene->win_height);
	scene->image_width = scene->win_width;
	scene->image_height = (int)(scene->image_width / aspect_ratio);
	if (scene->image_height < 1)
		scene->image_height = 1;
	scene->viewport_height = 2.0 * tan(deg_to_rad(camera->fov) / 2.0);
	scene->viewport_width = scene->viewport_height * aspect_ratio;
	if (fabs(camera->orientation.y) == 1)
		camera->right = normalize_vector(cross_product((t_vector){1, 0, 0},
					camera->orientation));
	else
		camera->right = normalize_vector(cross_product((t_vector){0, -1, 0},
					camera->orientation));
	camera->up = normalize_vector(cross_product(camera->orientation,
				camera->right));
	setup_screen(scene);
}

void	init_scene(t_scene *scene)
{
	scene->win_height = WIN_HEIGHT_DEFAULT;
	scene->win_width = WIN_WIDTH_DEFAULT;
	scene->img.img = NULL;
	scene->mlx = NULL;
	scene->win = NULL;
	scene->objects = NULL;
	scene->light = NULL;
	scene->ambient = NULL;
	scene->camera = NULL;
}
