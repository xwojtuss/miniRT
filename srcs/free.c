/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wkornato <wkornato@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/20 15:15:54 by wkornato          #+#    #+#             */
/*   Updated: 2024/12/19 16:15:25 by wkornato         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini_rt.h"

static void	free_objects(t_objects *objects)
{
	t_objects	*next;

	while (objects)
	{
		next = objects->next;
		if (objects->object)
			free(objects->object);
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
	free_objects(scene->objects);
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
