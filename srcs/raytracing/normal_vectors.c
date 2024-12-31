/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   normal_vectors.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wkornato <wkornato@student.42warsaw.pl>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/19 17:27:16 by wkornato          #+#    #+#             */
/*   Updated: 2024/12/31 22:31:06 by wkornato         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini_rt.h"

t_vector	get_nv_sphere(t_vector inter, t_vector camera_pos, t_sphere *sphere)
{
	t_vector	result;

	result = normalize_v(subtract_v(inter, sphere->position));
	if (get_length_v(subtract_v(camera_pos, sphere->position)) > sphere->diam
		/ 2 + OFFSET_NORMAL)
		result = scale_v(result, -1);
	return (result);
}

t_vector	get_normal_vector_sphere(t_vector inter, t_vector center)
{
	return (get_direction_v(inter, center));
}

t_vector	get_nv_plane(t_ray ray, t_plane *plane)
{
	if (dot_v(subtract_v(ray.origin, plane->position), plane->orientation) > 0)
		return (scale_v(plane->orientation, -1));
	return (plane->orientation);
}

t_vector	get_nv_cylinder(t_vector intersect, t_cylinder *cylinder, t_ray ray)
{
	t_vector	pos_to_inter;
	t_vector	parallel;
	t_vector	normal;

	pos_to_inter = subtract_v(intersect, cylinder->position);
	parallel = scale_v(cylinder->orientation, dot_v(pos_to_inter,
				cylinder->orientation));
	normal = subtract_v(pos_to_inter, parallel);
	if (is_inside_cylinder(ray.origin, *cylinder))
		normal = scale_v(normal, -1);
	return (normalize_v(scale_v(normal, -1)));
}

t_vector	get_nv_cone(t_vector intersect, t_cone *cone, t_ray ray)
{
	t_vector	axis_point;
	t_vector	radial;
	double		cos_angle;

	axis_point = add_v(cone->position, scale_v(cone->orientation,
				dot_v(subtract_v(intersect, cone->position),
					cone->orientation)));
	radial = normalize_v(subtract_v(intersect, axis_point));
	cos_angle = cone->height / sqrt(pow(cone->height, 2) + pow(cone->diam / 2,
				2));
	(void)ray;
	radial = add_v(radial, scale_v(cone->orientation, -cos_angle));
	return (scale_v(normalize_v(radial), -1));
}
