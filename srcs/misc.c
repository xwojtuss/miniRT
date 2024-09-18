/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   misc.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wkornato <wkornato@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/22 19:54:07 by wkornato          #+#    #+#             */
/*   Updated: 2024/08/22 19:54:08 by wkornato         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini_rt.h"

t_objects	*get_last_object(t_objects *objects)
{
	t_objects	*last;

	last = objects;
	if (!last)
		return (NULL);
	while (last->next)
		last = last->next;
	return (last);
}

int	close_win_handler(void *context)
{
	t_scene	*scene;

	scene = (t_scene *)context;
	free_scene(scene);
	exit(EXIT_SUCCESS);
	return (0);
}

int	close_win(void *context, int exit_code)
{
	t_scene	*scene;

	scene = (t_scene *)context;
	if (scene->win && scene->mlx)
		mlx_destroy_window(scene->mlx, scene->win);
	if (scene->mlx)
		mlx_destroy_display(scene->mlx);
	if (scene->mlx)
		free(scene->mlx);
	if (exit_code != NOT_SET)
		exit(exit_code);
	return (0);
}
