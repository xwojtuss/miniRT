/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ambient.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wkornato <wkornato@student.42warsaw.pl>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/22 19:53:44 by wkornato          #+#    #+#             */
/*   Updated: 2025/01/01 18:31:37 by wkornato         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini_rt.h"

static void	check_ambient_values(t_ambient *obj, t_scene *scene, char **line)
{
	if (obj->brightness < 0 || obj->brightness > 1)
		err_free_array("Invalid brightness for ambient light", scene, line);
	if (obj->color.r < 0 || obj->color.g < 0 || obj->color.b < 0)
		err_free_array("Color of ambient light is not correct", scene, line);
}

void	parse_ambient_light(t_scene *scene, char **instructions, size_t argc)
{
	char	**temp;

	if (argc != 3)
		err_free_array("Invalid number of arguments for ambient light", scene,
			instructions);
	if (scene->ambient)
		err_free_array("Too many ambient lights", scene,
			instructions);
	scene->ambient = (t_ambient *)ft_calloc(1, sizeof(t_ambient));
	if (!scene->ambient)
		err_free_array("Could not allocate memory for ambient light", scene,
			instructions);
	scene->ambient->brightness = ft_atof(instructions[1]);
	temp = ft_split(instructions[2], ',');
	if (!temp || ft_arrlen(temp) != 3)
		err_free_arrays("Incorrect amount of parameters to a value", scene,
			temp, instructions);
	assign_color(&scene->ambient->color, ft_atoi(temp[0]), ft_atoi(temp[1]),
		ft_atoi(temp[2]));
	free_array(temp);
	check_ambient_values(scene->ambient, scene, instructions);
}
