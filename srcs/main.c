/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wkornato <wkornato@student.42warsaw.pl>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/22 19:54:06 by wkornato          #+#    #+#             */
/*   Updated: 2025/01/01 19:33:49 by wkornato         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini_rt.h"

static void	read_scene(t_scene *scene, char *file)
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
	if (ft_strncmp(argv[1] + ft_strlen(argv[1]) - 3, ".rt", 3))
		err("Invalid file extension");
	init_scene(&scene);
	scene.file = argv[1];
	read_scene(&scene, argv[1]);
	check_scene(&scene);
	initialize_mlx(&scene);
	initialize_viewport(&scene);
	render_scene(&scene);
	mlx_loop(scene.mlx);
	free_scene(&scene);
	return (0);
}
