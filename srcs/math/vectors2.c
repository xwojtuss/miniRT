/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vectors2.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wkornato <wkornato@student.42warsaw.pl>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/24 19:21:22 by ukireyeu          #+#    #+#             */
/*   Updated: 2024/12/31 22:31:06 by wkornato         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini_rt.h"

double	get_length_v(t_vector vector)
{
	return (sqrt(vector.x * vector.x + vector.y * vector.y + vector.z
			* vector.z));
}

t_vector	normalize_v(t_vector vector)
{
	t_vector	normalized;
	float		length;

	length = get_length_v(vector);
	normalized.x = vector.x / length;
	normalized.y = vector.y / length;
	normalized.z = vector.z / length;
	return (normalized);
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
