/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   plane.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wkornato <wkornato@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/22 19:53:58 by wkornato          #+#    #+#             */
/*   Updated: 2024/08/22 20:05:45 by wkornato         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini_rt.h"

void	check_plane_values(t_plane *plane, t_scene *scene, char **line)
{
	if (plane->orientation.x < -1 || plane->orientation.x > 1
		|| plane->orientation.y < -1 || plane->orientation.y > 1
		|| plane->orientation.z < -1 || plane->orientation.z > 1)
		err_free_array("Invalid orientation for plane", scene, line);
	if (plane->color.r < 0 || plane->color.g < 0 || plane->color.b < 0)
		err_free_array("Color of plane is not correct", scene, line);
}

void	assign_plane_values(void *object, char **temp, t_object_param type)
{
	if (type == POSITION)
		assign_vector(&((t_plane *)object)->position, ft_atof(temp[0]),
			ft_atof(temp[1]), ft_atof(temp[2]));
	else if (type == ORIENTATION)
		assign_vector(&((t_plane *)object)->orientation, ft_atof(temp[0]),
			ft_atof(temp[1]), ft_atof(temp[2]));
	else if (type == COLOR)
		assign_color(&((t_plane *)object)->color, ft_atoi(temp[0]),
			ft_atoi(temp[1]), ft_atoi(temp[2]));
}

t_plane	*new_plane(t_scene *scene, t_objects *new, char **line, size_t argc)
{
	t_plane	*plane;

	if (argc != 4)
		err_free_array("Invalid number of arguments for plane", scene, line);
	plane = (t_plane *)ft_calloc(1, sizeof(t_plane));
	if (!plane)
		err_free_array("Could not allocate memory for plane", scene, line);
	new->object = plane;
	return (plane);
}