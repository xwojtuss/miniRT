/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wkornato <wkornato@student.42warsaw.pl>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/20 15:15:54 by wkornato          #+#    #+#             */
/*   Updated: 2024/12/31 12:28:13 by wkornato         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini_rt.h"

void	destroy_texture(t_scene *scene, t_texture *texture)
{
	if (texture)
	{
		if (texture->img.img)
			mlx_destroy_image(scene->mlx, texture->img.img);
		free(texture->name);
		free(texture);
		texture = NULL;
	}
}

void	destroy_images(t_objects *objects, t_scene *scene)
{
	if (objects->type == PLANE)
	{
		destroy_texture(scene, ((t_plane *)objects->object)->texture);
		destroy_texture(scene, ((t_plane *)objects->object)->bump);
	}
	else if (objects->type == SPHERE)
	{
		destroy_texture(scene, ((t_sphere *)objects->object)->texture);
		destroy_texture(scene, ((t_sphere *)objects->object)->bump);
	}
	else if (objects->type == CYLINDER)
	{
		destroy_texture(scene, ((t_cylinder *)objects->object)->texture);
		destroy_texture(scene, ((t_cylinder *)objects->object)->bump);
	}
	else if (objects->type == CONE)
	{
		destroy_texture(scene, ((t_cone *)objects->object)->texture);
		destroy_texture(scene, ((t_cone *)objects->object)->bump);
	}
}

static void	free_objects(t_objects *objects, t_scene *scene)
{
	t_objects	*next;

	while (objects)
	{
		next = objects->next;
		if (objects->object)
		{
			destroy_images(objects, scene);
			free(objects->object);
		}
		if (objects)
			free(objects);
		objects = next;
	}
}

void	free_scene(t_scene *scene)
{
	t_lights	*light;
	t_lights	*next_light;

	if (!scene)
		return ;
	free_objects(scene->objects, scene);
	light = scene->light;
	while (light)
	{
		next_light = light->next;
		free(light);
		light = next_light;
	}
	if (scene->ambient)
		free(scene->ambient);
	if (scene->camera)
		free(scene->camera);
	close_win(scene, NOT_SET);
}

void	free_array(char **array)
{
	size_t	i;

	i = 0;
	if (!array)
		return ;
	while (array[i])
	{
		if (array[i])
			free(array[i]);
		i++;
	}
	free(array);
}
