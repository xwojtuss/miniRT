/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vectors.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wkornato <wkornato@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/22 19:53:52 by wkornato          #+#    #+#             */
/*   Updated: 2024/09/24 15:40:24 by wkornato         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini_rt.h"

t_vector	multiply_v(t_vector vector, float multiplier)
{
	t_vector	result;

	result.x = vector.x * multiplier;
	result.y = vector.y * multiplier;
	result.z = vector.z * multiplier;
	return (result);
}

t_vector	divide_v(t_vector vector, float divider)
{
	t_vector	result;

	result.x = vector.x / divider;
	result.y = vector.y / divider;
	result.z = vector.z / divider;
	return (result);
}

t_vector	subtract_v(t_vector one, t_vector two)
{
	t_vector	result;

	result.x = one.x - two.x;
	result.y = one.y - two.y;
	result.z = one.z - two.z;
	return (result);
}

t_vector	add_v(t_vector one, t_vector two)
{
	t_vector	result;

	result.x = one.x + two.x;
	result.y = one.y + two.y;
	result.z = one.z + two.z;
	return (result);
}

float	dot_product(t_vector one, t_vector two)
{
	return (one.x * two.x + one.y * two.y + one.z * two.z);
}

float	vector_length(t_vector vector)
{
	return (sqrt(vector.x * vector.x + vector.y * vector.y + vector.z
			* vector.z));
}

void	normalize_vector(t_vector *vector)
{
	float	length;

	length = vector_length(*vector);
	vector->x /= length;
	vector->y /= length;
	vector->z /= length;
}

//the angle is in radians
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
