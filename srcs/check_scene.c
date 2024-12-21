/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_scene.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wkornato <wkornato@student.42warsaw.pl>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/22 19:54:00 by wkornato          #+#    #+#             */
/*   Updated: 2024/12/21 14:14:23 by wkornato         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini_rt.h"

void	check_scene(t_scene *scene)
{
	if (!scene->ambient)
		err_free("No ambient light", scene);
	if (!scene->camera)
		err_free("No camera", scene);
	if (!scene->light)
		err_free("No diffuse light", scene);
}

void	check_line(char **instructions, t_scene *scene, int fd)
{
	size_t	argc;

	argc = ft_arrlen(instructions);
	if (argc == 0)
		return (free_array(instructions));
	if (!ft_strcmp(instructions[0], "A"))
		parse_ambient_light(scene, instructions, argc);
	else if (!ft_strcmp(instructions[0], "C"))
		parse_camera(scene, instructions, argc);
	else if (!ft_strcmp(instructions[0], "L"))
		parse_light(scene, instructions, argc);
	else if (!ft_strcmp(instructions[0], "sp"))
		parse_new_object(scene, instructions, argc, SPHERE);
	else if (!ft_strcmp(instructions[0], "pl"))
		parse_new_object(scene, instructions, argc, PLANE);
	else if (!ft_strcmp(instructions[0], "cy"))
		parse_new_object(scene, instructions, argc, CYLINDER);
	else
	{
		free_array(instructions);
		close(fd);
		err_free("Invalid identifier", scene);
	}
	free_array(instructions);
}
