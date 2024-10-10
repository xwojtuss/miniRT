/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   initialize.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wkornato <wkornato@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/24 15:40:37 by wkornato          #+#    #+#             */
/*   Updated: 2024/10/10 19:33:17 by wkornato         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini_rt.h"

void	initialize_viewport(t_scene *scene)
{
	double	aspect_ratio;

	// the camera orientation is not working here, the initialization does not
	// take into account the camera orientation i think
	aspect_ratio = (double)(scene->win_width) / (double)(scene->win_height);
	scene->image_width = scene->win_width;
	scene->image_height = (int)(scene->image_width / aspect_ratio);
	if (scene->image_height < 1)
		scene->image_height = 1;
	scene->viewport_height = 2.0 * tan(deg_to_rad(scene->camera->fov) / 2.0);
	scene->viewport_width = scene->viewport_height * aspect_ratio;
	scene->viewport_grid_vector_x = divide_v((t_vector){scene->viewport_width,
			0, 0}, (double)(scene->image_width));
	scene->viewport_grid_vector_y = divide_v((t_vector){0,
			-(scene->viewport_height), 0}, (double)(scene->image_height));
	scene->viewport_top_left
		= subtract_v(subtract_v(subtract_v(scene->camera->position,
					scene->camera->orientation),
				divide_v((t_vector){scene->viewport_width, 0, 0}, 2.0)),
			divide_v((t_vector){0, -(scene->viewport_height), 0}, 2.0));
}

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
