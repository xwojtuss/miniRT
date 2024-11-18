/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vectors2.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wkornato <wkornato@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/24 19:21:22 by ukireyeu          #+#    #+#             */
/*   Updated: 2024/11/18 15:00:11 by wkornato         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini_rt.h"

double	vector_length(t_vector vector)
{
	return (sqrt(vector.x * vector.x + vector.y * vector.y + vector.z
			* vector.z));
}

t_vector	normalize_vector(t_vector vector)
{
	t_vector	normalized;
	float		length;

	length = vector_length(vector);
	normalized.x = vector.x / length;
	normalized.y = vector.y / length;
	normalized.z = vector.z / length;
	return (normalized);
}

// the angle is in radians
float	get_angle_between(t_vector one, t_vector two)
{
	float	len_one;
	float	len_two;

	len_one = vector_length(one);
	len_two = vector_length(two);
	return (acos(dot_product(one, two) / (len_one * len_two)));
}

void	assign_vector(t_vector *vector, float x, float y, float z)
{
	vector->x = x;
	vector->y = y;
	vector->z = z;
}

void	assign_color(t_color *color, int r, int g, int b)
{
	color->r = r;
	color->g = g;
	color->b = b;
}
