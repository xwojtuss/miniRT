/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   normal_vectors.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wkornato <wkornato@student.42warsaw.pl>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/19 17:27:16 by wkornato          #+#    #+#             */
/*   Updated: 2024/12/21 15:18:17 by wkornato         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini_rt.h"

t_vector	get_nv_sphere(t_vector inter, t_vector camera_pos,
		t_sphere *sphere)
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

t_vector	get_nv_cylinder(t_vector intersect,
		t_cylinder *cylinder)
{
	t_vector	pos_to_inter;
	t_vector	parallel;
	t_vector	normal;

	if (cylinder->inter_where == TOP)
		return (multiply_v(cylinder->orientation, -1));
	else if (cylinder->inter_where == BOTTOM)
		return (cylinder->orientation);
	else if (cylinder->inter_where == SIDE)
	{
		pos_to_inter = subtract_v(intersect, cylinder->position);
		parallel = multiply_v(cylinder->orientation,
				dot_product(pos_to_inter, cylinder->orientation));
		normal = subtract_v(pos_to_inter, parallel);
		return (normalize_vector(multiply_v(normal, -1)));
	}
	return ((t_vector){0, 1, 0});
}
