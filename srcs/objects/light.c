/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   light.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wkornato <wkornato@student.42warsaw.pl>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/22 19:53:57 by wkornato          #+#    #+#             */
/*   Updated: 2024/12/06 21:22:14 by wkornato         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini_rt.h"

void	check_light_values(t_lights *light, t_scene *scene, char **line)
{
	if (light->brightness < 0 || light->brightness > 1)
		err_free_array("Invalid brightness for light", scene, line);
}

void	parse_light(t_scene *scene, char **instructions, size_t argc)
{
	char	**temp;

	if (argc != 3 && argc != 4)
		err_free_array("Invalid number of arguments for light", scene,
			instructions);
	scene->light = (t_lights *)ft_calloc(1, sizeof(t_lights));
	if (!scene->light)
		err_free_array("Could not allocate memory for light", scene,
			instructions);
	temp = ft_split(instructions[1], ',');
	if (!temp || ft_arrlen(temp) != 3)
		err_free_array("Incorrect amount of parameters to a value", scene,
			temp);
	assign_vector(&scene->light->position, ft_atof(temp[0]), ft_atof(temp[1]),
		ft_atof(temp[2]));
	free_array(temp);
	scene->light->brightness = ft_atof(instructions[2]);
	if (argc == 4)
	{
		temp = ft_split(instructions[3], ',');
		if (!temp || ft_arrlen(temp) != 3)
			err_free_array("Incorrect amount of parameters to a value", scene,
				temp);
		assign_color(&scene->light->color, ft_atof(temp[0]), ft_atof(temp[1]),
			ft_atof(temp[2]));
		free_array(temp);
	}
	check_light_values(scene->light, scene, instructions);
}
