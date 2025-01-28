/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_intersections.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wkornato <wkornato@student.42warsaw.pl>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/19 17:16:27 by wkornato          #+#    #+#             */
/*   Updated: 2025/01/28 11:59:28 by wkornato         ###   ########.fr       */
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

	if (dot_v(plane->orientation, ray.direction) == 0)
		return (false);
	t = dot_v(scale_v(plane->orientation, -1), subtract_v(ray.origin,
				plane->position)) / dot_v(plane->orientation, ray.direction);
	if (t > 0 && *prev_t > t && get_length_v(subtract_v(get_inter(ray, t),
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
	if (get_length_v(subtract_v(ray.origin, sphere->position)) <= sphere->diam
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
		height_proj = dot_v(subtract_v(get_inter(ray, t1), cone->position),
				cone->orientation);
		if (height_proj >= 0 && height_proj <= cone->height)
			return (*prev_t = t1, true);
	}
	if (t2 > DBL_EPSILON && t2 < *prev_t)
	{
		height_proj = dot_v(subtract_v(get_inter(ray, t2), cone->position),
				cone->orientation);
		if (height_proj >= 0 && height_proj <= cone->height)
			return (*prev_t = t2, true);
	}
	return (false);
}

bool	is_intersect_line(t_ray ray, t_line *line, double *prev_t)
{
	t_vector	cross_k1_k2;
	double		t1;
	double		t2;
	t_vector	point1;
	t_vector	point2;

	cross_k1_k2 = cross_product(ray.direction, line->orientation);
	t1 = dot_v(cross_product(subtract_v(line->position, ray.origin),
				line->orientation), cross_k1_k2) / dot_v(cross_k1_k2,
			cross_k1_k2);
	t2 = dot_v(cross_product(subtract_v(line->position, ray.origin),
				ray.direction), cross_k1_k2) / dot_v(cross_k1_k2, cross_k1_k2);
	point1 = (t_vector){ray.origin.x + t1 * ray.direction.x, ray.origin.y + t1
		* ray.direction.y, ray.origin.z + t1 * ray.direction.z};
	point2 = (t_vector){line->position.x + t2 * line->orientation.x,
		line->position.y + t2 * line->orientation.y, line->position.z + t2
		* line->orientation.z};
	if (t1 > 0 && fabs(point1.x - point2.x) < 1e-1 && fabs(point1.y
			- point2.y) < 1e-1 && fabs(point1.z
			- point2.z) < 1e-1 && ((t2 >= 0 && t2 <= line->length) || line->length == INFINITY))
	{
		*prev_t = t1;
		return (true);
	}
	return (false);
}
