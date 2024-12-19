/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   intersection_misc.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wkornato <wkornato@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/19 17:19:27 by wkornato          #+#    #+#             */
/*   Updated: 2024/12/19 17:26:37 by wkornato         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini_rt.h"

t_vector	get_inter(t_ray ray, double t)
{
	return (add_v(ray.origin, multiply_v(ray.direction, t)));
}

double	get_t_cap_bottom(t_ray ray, t_cylinder *cylinder)
{
	return (dot_product(subtract_v(cylinder->position, ray.origin),
			cylinder->orientation) / dot_product(ray.direction,
			cylinder->orientation));
}

double	get_t_cap_top(t_ray ray, t_cylinder *cylinder)
{
	return (dot_product(subtract_v(add_v(cylinder->position,
					multiply_v(cylinder->orientation, cylinder->height)),
				ray.origin), cylinder->orientation) / dot_product(ray.direction,
			cylinder->orientation));
}

double	is_intersect_cylinder_caps(t_ray ray, t_cylinder *cylinder,
		double *prev_t)
{
	double	t_cap_top;
	double	t_cap_bottom;

	t_cap_bottom = get_t_cap_bottom(ray, cylinder);
	t_cap_top = get_t_cap_top(ray, cylinder);
	if (t_cap_bottom > DBL_EPSILON && t_cap_bottom < *prev_t
		&& (t_cap_bottom < t_cap_top || t_cap_top < 0))
	{
		if (vector_length(subtract_v(get_inter(ray, t_cap_bottom),
					cylinder->position)) <= cylinder->diam / 2)
			return (cylinder->is_caps = BOTTOM, t_cap_bottom);
	}
	if (t_cap_top > DBL_EPSILON && t_cap_top < *prev_t)
	{
		if (vector_length(subtract_v(get_inter(ray, t_cap_top),
					add_v(cylinder->position, multiply_v(cylinder->orientation,
							cylinder->height)))) <= cylinder->diam / 2)
			return (cylinder->is_caps = TOP, t_cap_top);
	}
	return (0);
}

void	get_t_cylinder(t_cylinder *cylinder, t_ray ray, double *t1, double *t2)
{
	t_vector	oc;
	t_vector	d;
	double		a;
	double		b;
	double		discriminant;

	oc = subtract_v(ray.origin, cylinder->position);
	d = subtract_v(ray.direction, multiply_v(cylinder->orientation,
				dot_product(ray.direction, cylinder->orientation)));
	oc = subtract_v(oc, multiply_v(cylinder->orientation, dot_product(oc,
					cylinder->orientation)));
	a = dot_product(d, d);
	b = 2.0 * dot_product(d, oc);
	discriminant = b * b - 4.0 * a * (dot_product(oc, oc) - pow(cylinder->diam
				/ 2.0, 2));
	*t1 = DBL_MAX;
	*t2 = DBL_MAX;
	if (discriminant >= 0)
		retrieve_t(a, b, discriminant, (double *[2]){t1, t2});
}
