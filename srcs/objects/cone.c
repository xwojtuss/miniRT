/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cone.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wkornato <wkornato@student.42warsaw.pl>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/22 19:53:56 by wkornato          #+#    #+#             */
/*   Updated: 2025/01/01 18:56:37 by wkornato         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini_rt.h"
#include "phong_reflection.h"

void	check_cone_values(t_cone *cone, t_scene *scene, char **line)
{
	if (cone->orientation.x < -1 || cone->orientation.x > 1
		|| cone->orientation.y < -1 || cone->orientation.y > 1
		|| cone->orientation.z < -1 || cone->orientation.z > 1)
		err_free_array("Invalid orientation for cone", scene, line);
	if (cone->diam <= 0)
		err_free_array("Invalid diameter for cone", scene, line);
	if (cone->height <= 0)
		err_free_array("Invalid height for cone", scene, line);
	if (cone->color.r < 0 || cone->color.g < 0 || cone->color.b < 0)
		err_free_array("Color of cone is not correct", scene, line);
}

void	assign_cone_values(void *object, char **temp, t_object_param type)
{
	if (type == POSITION)
		assign_vector(&((t_cone *)object)->position, ft_atof(temp[0]),
			ft_atof(temp[1]), ft_atof(temp[2]));
	else if (type == ORIENTATION)
	{
		assign_vector(&((t_cone *)object)->orientation, ft_atof(temp[0]),
			ft_atof(temp[1]), ft_atof(temp[2]));
		((t_cone *)object)->orientation = normalize_v(((t_cone *)object)->orientation);
	}
	else if (type == COLOR)
		assign_color(&((t_cone *)object)->color, ft_atoi(temp[0]),
			ft_atoi(temp[1]), ft_atoi(temp[2]));
}

t_cone	*new_cone(t_scene *scene, t_objects *new, char **line,
		size_t argc)
{
	t_cone	*cone;

	if (argc < 6 || argc > 11)
		err_free_array("Invalid number of arguments for cone", scene, line);
	cone = (t_cone *)ft_calloc(1, sizeof(t_cone));
	if (!cone)
		err_free_array("Could not allocate memory for cone", scene, line);
	new->object = cone;
	cone->diam = ft_atof(line[3]);
	cone->height = ft_atof(line[4]);
	new->texture = NULL;
	if (argc > 6 && ft_strcmp(line[6], "-"))
		new->texture = new_texture(line[6]);
	new->bump = NULL;
	if (argc > 7 && ft_strcmp(line[7], "-"))
		new->bump = new_texture(line[7]);
	if (argc == 11)
		assign_phong(new, line, 8);
	else
		assign_default_phong(new);
	return (cone);
}
