/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ukireyeu < ukireyeu@student.42warsaw.pl    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/22 19:54:06 by wkornato          #+#    #+#             */
/*   Updated: 2024/10/01 20:41:40 by ukireyeu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini_rt.h"

void	read_scene(t_scene *scene, char *file)
{
	int	fd;

	fd = open(file, O_RDONLY);
	if (fd < 0)
		err_free("Could not open file", scene);
	while (true)
	{
		if (!parse_line(scene, fd))
			break ;
	}
	close(fd);
}

int	main(int argc, char **argv)
{
	t_scene	scene;

	if (argc != 2)
		err("Invalid number of arguments");
	init_scene(&scene);
	read_scene(&scene, argv[1]);
	check_scene(&scene);
	initialize_mlx(&scene);
	initialize_viewport(&scene);

	// show_depth(scene);

	render_scene(&scene);
	mlx_loop(scene.mlx);
	free_scene(&scene);
	return (0);
}
