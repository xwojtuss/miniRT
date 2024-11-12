/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wkornato <wkornato@student.42warsaw.pl>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/20 15:15:54 by wkornato          #+#    #+#             */
/*   Updated: 2024/11/12 21:37:58 by wkornato         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini_rt.h"

void	free_scene(t_scene *scene)
{
	t_objects	*objects;
	t_objects	*next;

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
	if (scene->light)
		free(scene->light);
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
