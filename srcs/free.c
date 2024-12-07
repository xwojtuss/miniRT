/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wkornato <wkornato@student.42warsaw.pl>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/20 15:15:54 by wkornato          #+#    #+#             */
/*   Updated: 2024/12/07 16:37:07 by wkornato         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini_rt.h"

void	free_scene(t_scene *scene)
{
	t_objects	*objects;
	t_objects	*next;
	t_lights	*light;
	t_lights	*next_light;

	if (!scene)
		return ;
	objects = scene->objects;
	while (objects)
	{
		next = objects->next;
		if (objects->object)
			free(objects->object);
		if (objects)
			free(objects);
		objects = next;
	}
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
