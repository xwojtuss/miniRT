/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   intersection_misc.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wkornato <wkornato@student.42warsaw.pl>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/19 17:19:27 by wkornato          #+#    #+#             */
/*   Updated: 2024/12/31 11:41:23 by wkornato         ###   ########.fr       */
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
