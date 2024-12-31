/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   intersection_misc.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wkornato <wkornato@student.42warsaw.pl>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/19 17:19:27 by wkornato          #+#    #+#             */
/*   Updated: 2024/12/31 20:09:56 by wkornato         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini_rt.h"

t_vector	get_inter(t_ray ray, double t)
{
	return (add_v(ray.origin, multiply_v(ray.direction, t)));
}
bool	check_side_cylinder(t_ray ray, t_cylinder *cylinder, double *t1,
		double *prev_t)
{
	double	height_pos;

	height_pos = dot_product(subtract_v(get_inter(ray, *t1),
				cylinder->position), cylinder->orientation);
	if (height_pos >= 0 && height_pos <= cylinder->height)
		return (*prev_t = *t1, true);
	return (false);
}

bool	check_side_cone(t_ray ray, t_cone *cone, double *t1, double *prev_t)
{
	double	height_pos;

	height_pos = dot_product(subtract_v(get_inter(ray, *t1), cone->position),
			cone->orientation);
	if (height_pos >= -cone->height / 2 && height_pos <= cone->height / 2)
		return (*prev_t = *t1, true);
	return (false);
}
