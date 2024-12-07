/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   light.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wkornato <wkornato@student.42warsaw.pl>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/22 19:53:57 by wkornato          #+#    #+#             */
/*   Updated: 2024/12/07 16:59:09 by wkornato         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini_rt.h"

void	check_light_values(t_lights *light, t_scene *scene, char **line)
{
	if (light->brightness < 0 || light->brightness > 1)
		err_free_array("Invalid brightness for light", scene, line);
}

void	assign_color_to_light(bool is_default, char *values, t_scene *scene,
		t_color *color)
{
	char	**temp;

	temp = NULL;
	if (is_default)
		assign_color(color, 255, 255, 255);
	else
	{
		temp = ft_split(values, ',');
		if (!temp || ft_arrlen(temp) != 3)
			err_free_array("Incorrect amount of parameters to a value", scene,
				temp);
		assign_color(color, ft_atof(temp[0]), ft_atof(temp[1]),
			ft_atof(temp[2]));
		free_array(temp);
	}
}

void	parse_light(t_scene *scene, char **instructions, size_t argc)
{
	char		**temp;
	t_lights	*light;

	if (argc != 3 && argc != 4)
		err_free_array("Invalid number of arguments for light", scene,
			instructions);
	light = (t_lights *)ft_calloc(1, sizeof(t_lights));
	if (!light)
		err_free_array("Could not allocate memory for light", scene,
			instructions);
	light->next = scene->light;
	scene->light = light;
	temp = ft_split(instructions[1], ',');
	if (!temp || ft_arrlen(temp) != 3)
		err_free_array("Incorrect amount of parameters to a value", scene,
			temp);
	assign_vector(&light->position, ft_atof(temp[0]), ft_atof(temp[1]),
		ft_atof(temp[2]));
	free_array(temp);
	light->brightness = ft_atof(instructions[2]);
	assign_color_to_light((argc == 3), instructions[3], scene, &light->color);
	check_light_values(light, scene, instructions);
}
