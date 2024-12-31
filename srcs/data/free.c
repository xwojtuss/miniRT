/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wkornato <wkornato@student.42warsaw.pl>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/20 15:15:54 by wkornato          #+#    #+#             */
/*   Updated: 2024/12/31 20:29:05 by wkornato         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini_rt.h"

static void	destroy_images(t_objects *objects, t_scene *scene)
{
	if (objects->texture)
	{
		if (objects->texture->img.img)
			mlx_destroy_image(scene->mlx, objects->texture->img.img);
		free(objects->texture->name);
		free(objects->texture);
		objects->texture = NULL;
	}
	if (objects->bump)
	{
		if (objects->bump->img.img)
			mlx_destroy_image(scene->mlx, objects->bump->img.img);
		free(objects->bump->name);
		free(objects->bump);
		objects->bump = NULL;
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
