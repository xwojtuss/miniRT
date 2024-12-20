/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   colors.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wkornato <wkornato@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/19 16:43:49 by wkornato          #+#    #+#             */
/*   Updated: 2024/12/20 16:42:29 by wkornato         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini_rt.h"

t_vector	color_to_vector_plane(void *object)
{
	t_color	color;

	color = ((t_plane *)object)->color;
	return ((t_vector){color.r, color.g, color.b});
}

t_vector	color_to_vector_cylinder(void *object)
{
	t_color	color;

	color = ((t_cylinder *)object)->color;
	return ((t_vector){color.r, color.g, color.b});
}

t_vector	color_to_vector_sphere(void *object)
{
	t_color	color;

	color = ((t_sphere *)object)->color;
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
