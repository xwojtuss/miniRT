/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mlx_hooks.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wkornato <wkornato@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/24 15:40:25 by wkornato          #+#    #+#             */
/*   Updated: 2024/09/24 15:40:26 by wkornato         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini_rt.h"

int	key_hook(int keycode, t_scene *scene)
{
	(void)scene;
	if (keycode == KEY_ESC)
	{
		free_scene(scene);
		exit(EXIT_SUCCESS);
	}
	return (0);
}

int	close_win_handler(void *context)
{
	t_scene	*scene;

	scene = (t_scene *)context;
	free_scene(scene);
	exit(EXIT_SUCCESS);
	return (0);
}
