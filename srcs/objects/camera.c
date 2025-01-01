/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   camera.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wkornato <wkornato@student.42warsaw.pl>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/22 19:53:55 by wkornato          #+#    #+#             */
/*   Updated: 2025/01/01 22:26:48 by wkornato         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini_rt.h"

static void	check_camera_values(t_camera *camera, t_scene *scene, char **line)
{
	if (camera->fov < 0 || camera->fov > 180)
		err_free_array("Invalid field of view for camera", scene, line);
	if (camera->orientation.x < -1 || camera->orientation.x > 1
		|| camera->orientation.y < -1 || camera->orientation.y > 1
		|| camera->orientation.z < -1 || camera->orientation.z > 1)
		err_free_array("Invalid orientation for camera", scene, line);
}

static void	split_and_assign_vector_camera(char **line, int index,
		t_object_param type, t_scene *scene)
{
	char	**temp;
	double	orientation_multitude;

	temp = ft_split(line[index], ',');
	if (!temp || ft_arrlen(temp) != 3)
		err_free_arrays("Incorrect amount of parameters to a value", scene,
			temp, line);
	orientation_multitude = get_length_v((t_vector){ft_atof(temp[0]),
			ft_atof(temp[1]), ft_atof(temp[2])});
	if (type == ORIENTATION && (round(orientation_multitude) != 1 || 1
			- orientation_multitude > 0.001 || 1 - orientation_multitude
			< -0.001))
		err_free_arrays("Orientation vector has to have a length of 1", scene,
			temp, line);
	if (type == POSITION)
		assign_vector(&scene->camera->position, ft_atof(temp[0]),
			ft_atof(temp[1]), ft_atof(temp[2]));
	else if (type == ORIENTATION)
		assign_vector(&scene->camera->orientation, ft_atof(temp[0]),
			ft_atof(temp[1]), ft_atof(temp[2]));
	free_array(temp);
}

void	parse_camera(t_scene *scene, char **line, size_t argc)
{
	t_camera	*camera;

	if (argc != 4)
		err_free_array("Invalid number of arguments for camera", scene, line);
	if (scene->camera)
		err_free_array("Too many cameras", scene, line);
	camera = (t_camera *)ft_calloc(1, sizeof(t_camera));
	if (!camera)
		err_free_array("Could not allocate memory for camera", scene, line);
	scene->camera = camera;
	camera->right = (t_vector){-1, 0, 0};
	camera->up = (t_vector){0, 1, 0};
	split_and_assign_vector_camera(line, 1, POSITION, scene);
	split_and_assign_vector_camera(line, 2, ORIENTATION, scene);
	camera->fov = ft_atoi(line[3]);
	check_camera_values(camera, scene, line);
}
