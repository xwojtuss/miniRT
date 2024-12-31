/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   normal_vectors.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wkornato <wkornato@student.42warsaw.pl>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/19 17:27:16 by wkornato          #+#    #+#             */
/*   Updated: 2024/12/31 17:40:05 by wkornato         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini_rt.h"

t_vector	get_nv_sphere(t_vector inter, t_vector camera_pos, t_sphere *sphere)
{
	t_vector	result;

	result = normalize_vector(subtract_v(inter, sphere->position));
	if (vector_length(subtract_v(camera_pos, sphere->position)) > sphere->diam
		/ 2 + OFFSET_NORMAL)
		result = multiply_v(result, -1);
	return (result);
}

t_vector	get_normal_vector_sphere(t_vector inter, t_vector center)
{
	return (get_direction_vector(inter, center));
}

t_vector	get_nv_plane(t_ray ray, t_plane *plane)
{
	if (dot_product(subtract_v(ray.origin, plane->position),
			plane->orientation) > 0)
		return (multiply_v(plane->orientation, -1));
	return (plane->orientation);
}

bool	is_inside_cylinder(t_vector ray_origin, t_cylinder cylinder)
{
	t_vector	to_origin;
	double		projected_height;
	double		perpendicular_distance;

	to_origin = subtract_v(ray_origin, cylinder.position);
	projected_height = dot_product(to_origin, cylinder.orientation);
	if (projected_height < 0 || projected_height > cylinder.height)
		return (false);
	perpendicular_distance = vector_length(subtract_v(to_origin,
				multiply_v(cylinder.orientation, projected_height)));
	return (perpendicular_distance < (cylinder.diam / 2));
}

t_vector	get_nv_cylinder(t_vector intersect, t_cylinder *cylinder, t_ray ray)
{
	t_vector	pos_to_inter;
	t_vector	parallel;
	t_vector	normal;

	pos_to_inter = subtract_v(intersect, cylinder->position);
	parallel = multiply_v(cylinder->orientation, dot_product(pos_to_inter,
				cylinder->orientation));
	normal = subtract_v(pos_to_inter, parallel);
	if (is_inside_cylinder(ray.origin, *cylinder))
		normal = multiply_v(normal, -1);
	return (normalize_vector(multiply_v(normal, -1)));
}

t_vector	get_nv_cone(t_vector intersect, t_cone *cone, t_ray ray)
{
	t_vector axis_point;
	t_vector radial;
	double cos_angle;
	
	axis_point = add_v(cone->position, multiply_v(cone->orientation,
				dot_product(subtract_v(intersect, cone->position),
					cone->orientation)));
	radial = normalize_vector(subtract_v(intersect, axis_point));
	cos_angle = cone->height / sqrt(pow(cone->height, 2) + pow(cone->diam / 2,
				2));
	(void)ray;
	radial = add_v(radial, multiply_v(cone->orientation, -cos_angle));
	return (multiply_v(normalize_vector(radial), -1));
}