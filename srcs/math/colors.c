/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   colors.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wkornato <wkornato@student.42warsaw.pl>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/19 16:43:49 by wkornato          #+#    #+#             */
/*   Updated: 2024/12/31 22:00:53 by wkornato         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini_rt.h"

// t_vector	color_to_vector(t_objects *object)
// {
// 	t_color	color;

// 	if (object->type == PLANE)
// 		color = ((t_plane *)object)->color;
// 	else if (object->type == SPHERE)
// 		color = ((t_sphere *)object)->color;
// 	if (object->type == CYLINDER)
// 		color = ((t_cylinder *)object)->color;
// 	else if (object->type == CONE)
// 		color = ((t_cone *)object)->color;
// 	return ((t_vector){color.r, color.g, color.b});
// }

int	vector_to_int(t_vector vector)
{
	return (((int)vector.x << 16) + ((int)vector.y << 8) + ((int)vector.z));
}

t_vector	color_to_vector(t_color color)
{
	return ((t_vector){color.r, color.g, color.b});
}

t_vector	int_color_to_vector(int color)
{
	t_color	c;

	c.r = (color & 0xFF0000) >> 16;
	c.g = (color & 0xFF00) >> 8;
	c.b = color & 0xFF;
	return ((t_vector){c.r, c.g, c.b});
}
void	copy_color(t_color *dest, t_color src)
{
	dest->r = src.r;
	dest->g = src.g;
	dest->b = src.b;
}