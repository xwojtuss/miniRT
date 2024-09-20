/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   misc.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wkornato <wkornato@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/22 19:54:07 by wkornato          #+#    #+#             */
/*   Updated: 2024/09/20 17:26:47 by wkornato         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini_rt.h"

t_objects	*get_last_object(t_objects *objects)
{
	t_objects	*last;

	last = objects;
	if (!last)
		return (NULL);
	while (last->next)
		last = last->next;
	return (last);
}

int	color_to_int(t_color color)
{
	return ((color.r << 16) + (color.g << 8) + color.b);
}

int	rgb_to_int(int r, int g, int b)
{
	return ((r << 16) + (g << 8) + b);
}

int	vector_to_int(t_vector vector)
{
	return (rgb_to_int(vector.x, vector.y, vector.z));
}
