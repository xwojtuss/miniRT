/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cylinder.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wkornato <wkornato@student.42warsaw.pl>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/22 19:53:56 by wkornato          #+#    #+#             */
/*   Updated: 2024/12/21 14:50:24 by wkornato         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini_rt.h"
#include "phong_reflection.h"

void	check_cylinder_values(t_cylinder *cylinder, t_scene *scene, char **line)
{
	if (cylinder->orientation.x < -1 || cylinder->orientation.x > 1
		|| cylinder->orientation.y < -1 || cylinder->orientation.y > 1
		|| cylinder->orientation.z < -1 || cylinder->orientation.z > 1)
		err_free_array("Invalid orientation for plane", scene, line);
	if (cylinder->diam <= 0)
		err_free_array("Invalid diameter for cylinder", scene, line);
	if (cylinder->height <= 0)
		err_free_array("Invalid height for cylinder", scene, line);
	if (cylinder->color.r < 0 || cylinder->color.g < 0 || cylinder->color.b < 0)
		err_free_array("Color of cylinder is not correct", scene, line);
	if (cylinder->ambient < 0 || cylinder->diffuse < 0 || cylinder->specular < 0
		|| cylinder->shininess < 0 || cylinder->ambient > 1
		|| cylinder->diffuse > 1 || cylinder->specular > 1)
		err_free_array("Phong values for cylinder are not correct", scene,
			line);
}

void	assign_cylinder_values(void *object, char **temp, t_object_param type)
{
	if (type == POSITION)
		assign_vector(&((t_cylinder *)object)->position, ft_atof(temp[0]),
			ft_atof(temp[1]), ft_atof(temp[2]));
	else if (type == ORIENTATION)
		assign_vector(&((t_cylinder *)object)->orientation, ft_atof(temp[0]),
			ft_atof(temp[1]), ft_atof(temp[2]));
	else if (type == COLOR)
		assign_color(&((t_cylinder *)object)->color, ft_atoi(temp[0]),
			ft_atoi(temp[1]), ft_atoi(temp[2]));
}

t_cylinder	*new_cylinder(t_scene *scene, t_objects *new, char **line,
		size_t argc)
{
	t_cylinder	*cylinder;

	if (argc < 6 || argc > 12)
		err_free_array("Invalid number of arguments for cylinder", scene, line);
	cylinder = (t_cylinder *)ft_calloc(1, sizeof(t_cylinder));
	if (!cylinder)
		err_free_array("Could not allocate memory for cylinder", scene, line);
	new->object = cylinder;
	cylinder->diam = ft_atof(line[3]);
	cylinder->height = ft_atof(line[4]);
	cylinder->texture = NULL;
	if (argc > 6 && ft_strcmp(line[6], "-"))
		cylinder->texture = new_texture(line[6]);
	cylinder->bump = NULL;
	if (argc > 7 && ft_strcmp(line[7], "-"))
		cylinder->bump = new_texture(line[7]);
	if (argc == 12)
		assign_phong(new, line, 8);
	else
		assign_default_phong(new);
	return (cylinder);
}
