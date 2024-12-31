/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sphere.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wkornato <wkornato@student.42warsaw.pl>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/22 19:53:59 by wkornato          #+#    #+#             */
/*   Updated: 2024/12/31 16:51:18 by wkornato         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini_rt.h"

void	check_sphere_values(t_sphere *sphere, t_scene *scene, char **line)
{
	if (sphere->diam <= 0)
		err_free_array("Invalid diameter for sphere", scene, line);
	if (sphere->color.r < 0 || sphere->color.g < 0 || sphere->color.b < 0)
		err_free_array("Color of sphere is not correct", scene, line);
	if (sphere->ambient < 0 || sphere->diffuse < 0 || sphere->specular < 0
		|| sphere->shininess < 0 || sphere->ambient > 1
		|| sphere->diffuse > 1 || sphere->specular > 1)
		err_free_array("Phong values for sphere are not correct", scene,
			line);
}

void	assign_sphere_values(void *object, char **temp, t_object_param type)
{
	if (type == POSITION)
		assign_vector(&((t_sphere *)object)->position, ft_atof(temp[0]),
			ft_atof(temp[1]), ft_atof(temp[2]));
	else if (type == COLOR)
		assign_color(&((t_sphere *)object)->color, ft_atoi(temp[0]),
			ft_atoi(temp[1]), ft_atoi(temp[2]));
}

t_sphere	*new_sphere(t_scene *scene, t_objects *new, char **line,
		size_t argc)
{
	t_sphere	*sphere;

	if (argc < 4 || argc > 10)
		err_free_array("Invalid number of arguments for sphere", scene, line);
	sphere = (t_sphere *)ft_calloc(1, sizeof(t_sphere));
	if (!sphere)
		err_free_array("Could not allocate memory for sphere", scene, line);
	new->object = sphere;
	sphere->diam = ft_atof(line[2]);
	sphere->texture = NULL;
	if (argc > 4 && ft_strcmp(line[4], "-"))
		sphere->texture = new_texture(line[4]);
	sphere->bump = NULL;
	if (argc > 5 && ft_strcmp(line[5], "-"))
		sphere->bump = new_texture(line[5]);
	if (argc == 10)
		assign_phong(new, line, 6);
	else
		assign_default_phong(new, scene->ambient->brightness);
	return (sphere);
}
