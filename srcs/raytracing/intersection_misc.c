/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   intersection_misc.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wkornato <wkornato@student.42warsaw.pl>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/19 17:19:27 by wkornato          #+#    #+#             */
/*   Updated: 2024/12/31 22:21:51 by wkornato         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini_rt.h"

t_vector	get_inter(t_ray ray, double t)
{
	return (add_v(ray.origin, scale_v(ray.direction, t)));
}

bool	check_side_cylinder(t_ray ray, t_cylinder *cylinder, double *t1,
		double *prev_t)
{
	double	height_pos;

	height_pos = dot_v(subtract_v(get_inter(ray, *t1),
				cylinder->position), cylinder->orientation);
	if (height_pos >= 0 && height_pos <= cylinder->height)
		return (*prev_t = *t1, true);
	return (false);
}

bool	check_side_cone(t_ray ray, t_cone *cone, double *t1, double *prev_t)
{
	double	height_pos;

	height_pos = dot_v(subtract_v(get_inter(ray, *t1), cone->position),
			cone->orientation);
	if (height_pos >= -cone->height / 2 && height_pos <= cone->height / 2)
		return (*prev_t = *t1, true);
	return (false);
}

bool	is_inside_cylinder(t_vector ray_origin, t_cylinder cylinder)
{
	t_vector	to_origin;
	double		projected_height;
	double		perpendicular_distance;

	to_origin = subtract_v(ray_origin, cylinder.position);
	projected_height = dot_v(to_origin, cylinder.orientation);
	if (projected_height < 0 || projected_height > cylinder.height)
		return (false);
	perpendicular_distance = get_length_v(subtract_v(to_origin,
				scale_v(cylinder.orientation, projected_height)));
	return (perpendicular_distance < (cylinder.diam / 2));
}
