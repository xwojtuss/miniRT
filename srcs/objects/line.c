/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   line.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wkornato <wkornato@student.42warsaw.pl>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/28 11:03:31 by wkornato          #+#    #+#             */
/*   Updated: 2025/01/28 11:54:13 by wkornato         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini_rt.h"

void	check_line_values(t_line *o_line, t_scene *scene, char **line)
{
	if (o_line->orientation.x < -1 || o_line->orientation.x > 1
		|| o_line->orientation.y < -1 || o_line->orientation.y > 1
		|| o_line->orientation.z < -1 || o_line->orientation.z > 1)
		err_free_array("Invalid orientation for line", scene, line);
	if (o_line->color.r < 0 || o_line->color.g < 0 || o_line->color.b < 0)
		err_free_array("Color of line is not correct", scene, line);
	if (o_line->length < FLT_EPSILON && o_line->length != INFINITY)
		err_free_array("Length of line is not correct", scene, line);
}

void	assign_line_values(void *object, char **temp, t_object_param type)
{
	if (type == POSITION)
		assign_vector(&((t_line *)object)->position, ft_atof(temp[0]),
			ft_atof(temp[1]), ft_atof(temp[2]));
	else if (type == ORIENTATION)
	{
		assign_vector(&((t_line *)object)->orientation, ft_atof(temp[0]),
			ft_atof(temp[1]), ft_atof(temp[2]));
		((t_line *)object)->orientation = normalize_v(((t_line *)object)->orientation);
	}
	else if (type == COLOR)
		assign_color(&((t_line *)object)->color, ft_atoi(temp[0]),
			ft_atoi(temp[1]), ft_atoi(temp[2]));
}

t_line	*new_line(t_scene *scene, t_objects *new, char **line, size_t argc)
{
	t_line	*o_line;

	if (argc < 4 || argc > 5)
		err_free_array("Invalid number of arguments for line", scene, line);
	o_line = (t_line *)ft_calloc(1, sizeof(t_line));
	if (!o_line)
		err_free_array("Could not allocate memory for line", scene, line);
	new->object = o_line;
	new->texture = NULL;
	new->bump = NULL;
	((t_line *)new->object)->length = INFINITY;
	if (argc == 5 && ft_strcmp(line[4], "inf"))
		((t_line *)new->object)->length = ft_atof(line[4]);
	assign_default_phong(new);
	return (o_line);
}
