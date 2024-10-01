/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ukireyeu < ukireyeu@student.42warsaw.pl    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/22 19:54:06 by wkornato          #+#    #+#             */
<<<<<<< HEAD
/*   Updated: 2024/10/01 15:40:28 by wkornato         ###   ########.fr       */
=======
/*   Updated: 2024/09/26 17:43:03 by ukireyeu         ###   ########.fr       */
>>>>>>> 7b3b2ab (fix elements)
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
<<<<<<< HEAD
	
	show_depth(scene);

	// render_scene(&scene);
=======
	// print_objects_parameters(&scene);
	render_scene(&scene);
>>>>>>> 7b3b2ab (fix elements)
	mlx_loop(scene.mlx);
	free_scene(&scene);
	return (0);
}
