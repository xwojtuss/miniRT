/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_intersections.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wkornato <wkornato@student.42warsaw.pl>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/19 17:16:27 by wkornato          #+#    #+#             */
/*   Updated: 2024/12/31 20:10:30 by wkornato         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini_rt.h"

bool	is_intersect_ray_cylinder(t_ray ray, t_cylinder *cylinder,
		double *prev_t)
{
	double	t1;
	double	t2;

	t1 = DBL_MAX;
	t2 = DBL_MAX;
	get_t_cylinder(cylinder, ray, &t1, &t2);
	if (t1 == DBL_MAX && t2 == DBL_MAX)
		return (false);
	if (t1 > DBL_EPSILON && t1 < *prev_t && check_side_cylinder(ray, cylinder,
			&t1, prev_t))
		return (true);
	if (t2 > DBL_EPSILON && t2 < *prev_t && check_side_cylinder(ray, cylinder,
			&t2, prev_t))
		return (true);
	return (false);
}

bool	is_intersect_plane(t_ray ray, t_plane *plane, double *prev_t)
{
	double	t;

	if (dot_product(plane->orientation, ray.direction) == 0)
		return (false);
	t = dot_product(multiply_v(plane->orientation, -1), subtract_v(ray.origin,
				plane->position)) / dot_product(plane->orientation,
			ray.direction);
	if (t > 0 && *prev_t > t && vector_length(subtract_v(get_inter(ray, t),
				plane->position)) < plane->diam / 2 + OFFSET_NORMAL)
		return (*prev_t = t, true);
	return (false);
}

bool	is_intersect_sphere(t_ray ray, t_sphere *sphere, double *prev_t)
{
	double	t1;
	double	t2;
	float	temp;

	t1 = 0;
	t2 = 0;
	get_t_sphere(sphere, ray, &t1, &t2);
	if (t1 == DBL_MAX && t2 == DBL_MAX)
		return (false);
	if (t1 > t2)
	{
		temp = t1;
		t1 = t2;
		t2 = temp;
	}
	if (vector_length(subtract_v(ray.origin, sphere->position)) <= sphere->diam
		/ 2 && t2 > 0 && *prev_t > t2)
		return (*prev_t = t2, true);
	else if (t1 > 0 && *prev_t > t1)
		return (*prev_t = t1, true);
	return (false);
}

bool	is_intersect_cone(t_ray ray, t_cone *cone, double *prev_t)
{
	double	height_proj;
	double	t1;
	double	t2;

	t1 = DBL_MAX;
	t2 = DBL_MAX;
	get_t_cone(cone, ray, &t1, &t2);
	if (t1 == DBL_MAX && t2 == DBL_MAX)
		return (false);
	if (t1 > DBL_EPSILON && t1 < *prev_t)
	{
		height_proj = dot_product(subtract_v(get_inter(ray, t1),
					cone->position), cone->orientation);
		if (height_proj >= 0 && height_proj <= cone->height)
			return (*prev_t = t1, true);
	}
	if (t2 > DBL_EPSILON && t2 < *prev_t)
	{
		height_proj = dot_product(subtract_v(get_inter(ray, t2),
					cone->position), cone->orientation);
		if (height_proj >= 0 && height_proj <= cone->height)
			return (*prev_t = t2, true);
	}
	return (false);
}
