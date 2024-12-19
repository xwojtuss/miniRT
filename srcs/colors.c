/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   colors.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wkornato <wkornato@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/19 16:43:49 by wkornato          #+#    #+#             */
/*   Updated: 2024/12/19 16:43:50 by wkornato         ###   ########.fr       */
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
