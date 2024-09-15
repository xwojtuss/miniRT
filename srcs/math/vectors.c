/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vectors.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wkornato <wkornato@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/22 19:53:52 by wkornato          #+#    #+#             */
/*   Updated: 2024/08/23 11:14:44 by wkornato         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini_rt.h"

void	add_v(t_vector one, t_vector two, t_vector *dest)
{
	float temp_one;
	float temp_two;

	temp_one = one.x;
	temp_two = two.x;
	dest->x = temp_one + temp_two;
	temp_one = one.y;
	temp_two = two.y;
	dest->y = temp_one + temp_two;
	temp_one = one.z;
	temp_two = two.z;
	dest->z = temp_one + temp_two;
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
