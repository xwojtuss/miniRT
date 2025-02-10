/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mlx_hooks.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wkornato <wkornato@student.42warsaw.pl>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/24 15:40:25 by wkornato          #+#    #+#             */
/*   Updated: 2024/12/31 21:00:31 by wkornato         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini_rt.h"

void	move_object(int keycode, t_scene *scene)
{
	if (scene->selected == NULL)
		return ;
	if (keycode == XK_i)
	{
		if (scene->selected->type == LINE)
			((t_line *)scene->selected->object)->position.x += 1;
		else if (scene->selected->type == SPHERE)
			((t_sphere *)scene->selected->object)->position.x += 1;
		else if (scene->selected->type == CYLINDER)
			((t_cylinder *)scene->selected->object)->position.x += 1;
		else if (scene->selected->type == PLANE)
			((t_plane *)scene->selected->object)->position.x += 1;
		else if (scene->selected->type == CONE)
			((t_cone *)scene->selected->object)->position.x += 1;
	}
	else if (keycode == XK_j)
	{
		if (scene->selected->type == LINE)
			((t_line *)scene->selected->object)->position.z += 1;
		else if (scene->selected->type == SPHERE)
			((t_sphere *)scene->selected->object)->position.z += 1;
		else if (scene->selected->type == CYLINDER)
			((t_cylinder *)scene->selected->object)->position.z += 1;
		else if (scene->selected->type == PLANE)
			((t_plane *)scene->selected->object)->position.z += 1;
		else if (scene->selected->type == CONE)
			((t_cone *)scene->selected->object)->position.z += 1;
	}
	else if (keycode == XK_k)
	{
		if (scene->selected->type == LINE)
			((t_line *)scene->selected->object)->position.x -= 1;
		else if (scene->selected->type == SPHERE)
			((t_sphere *)scene->selected->object)->position.x -= 1;
		else if (scene->selected->type == CYLINDER)
			((t_cylinder *)scene->selected->object)->position.x -= 1;
		else if (scene->selected->type == PLANE)
			((t_plane *)scene->selected->object)->position.x -= 1;
		else if (scene->selected->type == CONE)
			((t_cone *)scene->selected->object)->position.x -= 1;
	}
	else if (keycode == XK_l)
	{
		if (scene->selected->type == LINE)
			((t_line *)scene->selected->object)->position.z -= 1;
		else if (scene->selected->type == SPHERE)
			((t_sphere *)scene->selected->object)->position.z -= 1;
		else if (scene->selected->type == CYLINDER)
			((t_cylinder *)scene->selected->object)->position.z -= 1;
		else if (scene->selected->type == PLANE)
			((t_plane *)scene->selected->object)->position.z -= 1;
		else if (scene->selected->type == CONE)
			((t_cone *)scene->selected->object)->position.z -= 1;
	}
	else if (keycode == XK_u)
	{
		if (scene->selected->type == LINE)
			((t_line *)scene->selected->object)->position.y += 1;
		else if (scene->selected->type == SPHERE)
			((t_sphere *)scene->selected->object)->position.y += 1;
		else if (scene->selected->type == CYLINDER)
			((t_cylinder *)scene->selected->object)->position.y += 1;
		else if (scene->selected->type == PLANE)
			((t_plane *)scene->selected->object)->position.y += 1;
		else if (scene->selected->type == CONE)
			((t_cone *)scene->selected->object)->position.y += 1;
	}
	else if (keycode == XK_h)
	{
		if (scene->selected->type == LINE)
			((t_line *)scene->selected->object)->position.y -= 1;
		else if (scene->selected->type == SPHERE)
			((t_sphere *)scene->selected->object)->position.y -= 1;
		else if (scene->selected->type == CYLINDER)
			((t_cylinder *)scene->selected->object)->position.y -= 1;
		else if (scene->selected->type == PLANE)
			((t_plane *)scene->selected->object)->position.y -= 1;
		else if (scene->selected->type == CONE)
			((t_cone *)scene->selected->object)->position.y -= 1;
	}
}

int	key_hook(int keycode, t_scene *scene)
{
	if (keycode == KEY_ESC)
	{
		free_scene(scene);
		exit(EXIT_SUCCESS);
	}
	else if (DEBUG_TOOLS && (keycode == XK_i || keycode == XK_j || keycode == XK_k || keycode == XK_l || keycode == XK_u || keycode == XK_h))
		move_object(keycode, scene);
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
			add_v(scale_v(scene->viewport_grid_vector_x, x),
				scale_v(scene->viewport_grid_vector_y, y)));
	ray_direction = subtract_v(pixel_center, scene->camera->position);
	ray = (t_ray){scene->camera->position, ray_direction};
	object = get_closest_object(*scene, ray, &temp);
	if (object)
	{
		scene->selected = object;
		print_object_parameters(object);
	}
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
