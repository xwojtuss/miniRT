/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   camera.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wkornato <wkornato@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/22 19:53:55 by wkornato          #+#    #+#             */
/*   Updated: 2024/08/22 20:09:09 by wkornato         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini_rt.h"

void	check_camera_values(t_camera *camera, t_scene *scene, char **line)
{
	if (camera->fov < 0 || camera->fov > 180)
		err_free_array("Invalid field of view for camera", scene, line);
	if (camera->orientation.x < -1 || camera->orientation.x > 1
		|| camera->orientation.y < -1 || camera->orientation.y > 1
		|| camera->orientation.z < -1 || camera->orientation.z > 1)
		err_free_array("Invalid orientation for camera", scene, line);
}

void	split_and_assign_vector_camera(t_camera *camera, char *line,
		t_object_param type, t_scene *scene)
{
	char	**temp;

	temp = ft_split(line, ',');
	if (!temp || ft_arrlen(temp) != 3)
		err_free_array("Incorrect amount of parameters to a value", scene,
			temp);
	if (type == POSITION)
		assign_vector(&camera->position, ft_atof(temp[0]), ft_atof(temp[1]),
			ft_atof(temp[2]));
	else if (type == ORIENTATION)
		assign_vector(&camera->orientation, ft_atof(temp[0]), ft_atof(temp[1]),
			ft_atof(temp[2]));
	free_array(temp);
}

void	parse_camera(t_scene *scene, char **line, size_t argc)
{
	t_camera	*camera;

	if (argc != 4)
		err_free_array("Invalid number of arguments for camera", scene, line);
	camera = (t_camera *)ft_calloc(1, sizeof(t_camera));
	if (!camera)
		err_free_array("Could not allocate memory for camera", scene, line);
	scene->camera = camera;
	split_and_assign_vector_camera(camera, line[1], POSITION, scene);
	split_and_assign_vector_camera(camera, line[2], ORIENTATION, scene);
	camera->fov = ft_atoi(line[3]);
	check_camera_values(camera, scene, line);
}
