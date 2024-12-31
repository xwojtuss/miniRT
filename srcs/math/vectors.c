/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vectors.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wkornato <wkornato@student.42warsaw.pl>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/22 19:53:52 by wkornato          #+#    #+#             */
/*   Updated: 2024/12/31 21:02:13 by wkornato         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini_rt.h"

t_vector	scale_v(t_vector vector, float multiplier)
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

float	dot_v(t_vector one, t_vector two)
{
	return (one.x * two.x + one.y * two.y + one.z * two.z);
}
