/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   misc.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wkornato <wkornato@student.42warsaw.pl>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/22 19:54:07 by wkornato          #+#    #+#             */
/*   Updated: 2024/12/31 16:31:25 by wkornato         ###   ########.fr       */
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
	return (rgb_to_int((int)vector.x, (int)vector.y, (int)vector.z));
}

t_vector	color_to_vector(t_color color)
{
	return ((t_vector){color.r, color.g, color.b});
}
