/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   find_t.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wkornato <wkornato@student.42warsaw.pl>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/19 17:27:09 by wkornato          #+#    #+#             */
/*   Updated: 2025/01/01 16:23:11 by wkornato         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini_rt.h"

void	retrieve_t(double a, double b, double disc, double *ts[2])
{
	double	temp;
	double	sqrt_disc;

	if (disc < 0)
	{
		*ts[0] = DBL_MAX;
		*ts[1] = DBL_MAX;
		return ;
	}
	sqrt_disc = sqrt(disc);
	*ts[0] = (-b - sqrt_disc) / (2.0 * a);
	*ts[1] = (-b + sqrt_disc) / (2.0 * a);
	if (*ts[0] > *ts[1])
	{
		temp = *ts[0];
		*ts[0] = *ts[1];
		*ts[1] = temp;
	}
}

void	get_t_sphere(t_sphere *sphere, t_ray ray, double *t1, double *t2)
{
	t_vector	origin_to_center;
	double		a;
	double		b;
	double		c;
	double		disc;

	origin_to_center = subtract_v(ray.origin, sphere->position);
	a = dot_v(ray.direction, ray.direction);
	b = 2 * dot_v(ray.direction, origin_to_center);
	c = dot_v(origin_to_center, origin_to_center) - pow(sphere->diam / 2, 2);
	disc = pow(b, 2) - 4 * a * c;
	if (disc < 0)
	{
		*t1 = DBL_MAX;
		*t2 = DBL_MAX;
	}
	else
		retrieve_t(a, b, disc, (double *[2]){t1, t2});
}

void	get_t_cylinder(t_cylinder *cylinder, t_ray ray, double *t1, double *t2)
{
	t_vector	oc;
	t_vector	d;
	double		a;
	double		b;
	double		discriminant;

	oc = subtract_v(ray.origin, cylinder->position);
	d = subtract_v(ray.direction, scale_v(cylinder->orientation,
				dot_v(ray.direction, cylinder->orientation)));
	oc = subtract_v(oc, scale_v(cylinder->orientation, dot_v(oc,
					cylinder->orientation)));
	a = dot_v(d, d);
	b = 2.0 * dot_v(d, oc);
	discriminant = b * b - 4.0 * a * (dot_v(oc, oc) - pow(cylinder->diam / 2.0,
				2));
	if (discriminant >= 0)
		retrieve_t(a, b, discriminant, (double *[2]){t1, t2});
}

void	get_t_cone(t_cone *cone, t_ray ray, double *t1, double *t2)
{
	t_vector	origin_to_center;
	double		tan_theta_squared;
	double		discriminant;
	double		a;
	double		b;

	tan_theta_squared = pow((cone->diam / 2.0) / cone->height, 2);
	origin_to_center = subtract_v(ray.origin, add_v(cone->position,
				scale_v(cone->orientation, cone->height)));
	a = dot_v(ray.direction, ray.direction) - (1 + tan_theta_squared)
		* pow(dot_v(ray.direction, cone->orientation), 2);
	b = 2 * (dot_v(ray.direction, origin_to_center) - (1 + tan_theta_squared)
			* dot_v(ray.direction, cone->orientation) * dot_v(origin_to_center,
				cone->orientation));
	discriminant = b * b - 4 * a * (dot_v(origin_to_center, origin_to_center)
		- (1 + tan_theta_squared) * pow(dot_v(origin_to_center,
				cone->orientation), 2));
	if (discriminant < 0)
		return ;
	retrieve_t(a, b, discriminant, (double *[2]){t1, t2});
}
