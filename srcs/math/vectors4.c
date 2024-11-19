/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vectors4.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wkornato <wkornato@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/19 15:13:12 by wkornato          #+#    #+#             */
/*   Updated: 2024/11/19 15:13:16 by wkornato         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini_rt.h"

float	get_max_float(float *t, int size)
{
	float	max_t;
	int		i;

	i = 0;
	max_t = t[0];
	while (++i < size)
	{
		if (t[i] > max_t)
			max_t = t[i];
	}
	return (max_t);
}

float	get_min_float(float *t, int size)
{
	float	min_t;
	int		i;

	i = 0;
	min_t = t[0];
	while (++i < size)
	{
		if (t[i] < min_t && t[i] > 0)
			min_t = t[i];
	}
	return (min_t);
}

t_vector	get_direction_vector(t_vector from, t_vector to)
{
	return (normalize_vector(subtract_v(to, from)));
}
