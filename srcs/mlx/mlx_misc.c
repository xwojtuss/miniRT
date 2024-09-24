/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mlx_misc.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ukireyeu < ukireyeu@student.42warsaw.pl    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/24 15:40:28 by wkornato          #+#    #+#             */
/*   Updated: 2024/09/24 19:20:20 by ukireyeu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini_rt.h"

void	my_mlx_pixel_put(t_image *data, int x, int y, int color)
{
	char	*dst;

	dst = data->addr + (y * data->line_length + x * (data->bits_per_pixel / 8));
	*(unsigned int *)dst = color;
}

int	close_win(void *context, int exit_code)
{
	t_scene	*scene;

	scene = (t_scene *)context;
	if (scene->img.img && scene->mlx)
		mlx_destroy_image(scene->mlx, scene->img.img);
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
