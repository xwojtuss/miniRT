/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mlx_init.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wkornato <wkornato@student.42warsaw.pl>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/24 15:40:26 by wkornato          #+#    #+#             */
/*   Updated: 2024/12/31 12:27:37 by wkornato         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini_rt.h"

void	open_texture_helper(t_texture *texture, t_scene *scene)
{
	if (texture)
	{
		texture->img.img = mlx_xpm_file_to_image(scene->mlx, texture->name,
				&texture->width, &texture->height);
		if (!texture->img.img)
			err_free("Could not open texture", scene);
		texture->img.addr = mlx_get_data_addr(texture->img.img,
				&texture->img.bits_per_pixel, &texture->img.line_length,
				&texture->img.endian);
		if (!texture->img.addr)
			err_free("Could not get texture address", scene);
		if (texture->width <= 0 || texture->height <= 0)
			err_free("Texture is not correct", scene);
	}
}

void	open_textures(t_scene *scene)
{
	t_objects	*curr;

	curr = scene->objects;
	while (curr)
	{
		if (curr->type == PLANE)
		{
			open_texture_helper(((t_plane *)curr->object)->texture, scene);
			open_texture_helper(((t_plane *)curr->object)->bump, scene);
		}
		else if (curr->type == SPHERE)
		{
			open_texture_helper(((t_sphere *)curr->object)->texture, scene);
			open_texture_helper(((t_sphere *)curr->object)->bump, scene);
		}
		else if (curr->type == CYLINDER)
		{
			open_texture_helper(((t_cylinder *)curr->object)->texture, scene);
			open_texture_helper(((t_cylinder *)curr->object)->bump, scene);
		}
		else if (curr->type == CONE)
		{
			open_texture_helper(((t_cone *)curr->object)->texture, scene);
			open_texture_helper(((t_cone *)curr->object)->bump, scene);
		}
		curr = curr->next;
	}
}

void	initialize_mlx(t_scene *scene)
{
	scene->mlx = mlx_init();
	if (!scene->mlx)
		err_free("Could not initialize mlx", scene);
	scene->win = mlx_new_window(scene->mlx, scene->win_width, scene->win_height,
			"miniRT");
	if (!scene->win)
		err_free("Could not create window", scene);
	scene->img.img = mlx_new_image(scene->mlx, scene->win_width,
			scene->win_height);
	if (!scene->img.img)
		err_free("Could not create image", scene);
	scene->img.addr = mlx_get_data_addr(scene->img.img,
			&scene->img.bits_per_pixel, &scene->img.line_length,
			&scene->img.endian);
	if (!scene->img.addr)
		err_free("Could not get image address", scene);
	open_textures(scene);
	mlx_hook(scene->win, DestroyNotify, NoEventMask, close_win_handler, scene);
	mlx_hook(scene->win, KeyPress, KeyPressMask, key_hook, scene);
	if (DEBUG_TOOLS)
		mlx_mouse_hook(scene->win, mouse_click_handler, scene);
}
