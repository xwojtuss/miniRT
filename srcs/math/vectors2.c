/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vectors2.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ukireyeu < ukireyeu@student.42warsaw.pl    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/24 19:21:22 by ukireyeu          #+#    #+#             */
/*   Updated: 2024/09/24 19:22:36 by ukireyeu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini_rt.h"

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
