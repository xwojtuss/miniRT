/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_intersections.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wkornato <wkornato@student.42warsaw.pl>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/19 17:16:27 by wkornato          #+#    #+#             */
/*   Updated: 2024/12/21 15:17:48 by wkornato         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini_rt.h"

bool	check_side(t_ray ray, t_cylinder *cylinder, double *ts[3])
{
	double	height_pos;

	height_pos = dot_product(subtract_v(get_inter(ray, *ts[0]),
				cylinder->position), cylinder->orientation);
	if (height_pos >= 0 && height_pos <= cylinder->height && (*ts[2] == 0
			|| *ts[0] < *ts[2]))
		return (*ts[1] = *ts[0], cylinder->inter_where = SIDE, 1);
	return (0);
}

int	is_intersect_ray_cylinder(t_ray ray, t_cylinder *cylinder, double *prev_t)
{
	double	caps_t;
	double	temp;
	double	t1;
	double	t2;

	cylinder->inter_where = NOWHERE;
	get_t_cylinder(cylinder, ray, &t1, &t2);
	if (t1 == DBL_MAX && t2 == DBL_MAX)
		return (0);
	if (t1 > t2)
	{
		temp = t1;
		t1 = t2;
		t2 = temp;
	}
	caps_t = is_intersect_cylinder_caps(ray, cylinder, prev_t);
	if (t1 > DBL_EPSILON && t1 < *prev_t && check_side(ray, cylinder,
			(double *[3]){&t1, prev_t, &caps_t}))
		return (1);
	if (t2 > DBL_EPSILON && t2 < *prev_t && check_side(ray, cylinder,
			(double *[3]){&t2, prev_t, &caps_t}))
		return (1);
	if (caps_t > DBL_EPSILON && caps_t - OFFSET_NORMAL < *prev_t)
		return (*prev_t = caps_t, 1);
	return (0);
}

int	is_intersect_plane(t_ray ray, t_plane *plane, double *prev_t)
{
	double	t;

	if (dot_product(plane->orientation, ray.direction) == 0)
		return (0);
	t = dot_product(multiply_v(plane->orientation, -1), subtract_v(ray.origin,
				plane->position)) / dot_product(plane->orientation,
			ray.direction);
	if (t > 0 && *prev_t > t)
		return (*prev_t = t, 1);
	return (0);
}

void	get_t_sphere(t_sphere *sphere, t_ray ray, double *t1, double *t2)
{
	t_vector	origin_to_center;
	double		a;
	double		b;
	double		c;
	double		disc;

	origin_to_center = subtract_v(ray.origin, sphere->position);
	a = dot_product(ray.direction, ray.direction);
	b = 2 * dot_product(ray.direction, origin_to_center);
	c = dot_product(origin_to_center, origin_to_center) - pow(sphere->diam / 2,
			2);
	disc = pow(b, 2) - 4 * a * c;
	if (disc < 0)
	{
		*t1 = DBL_MAX;
		*t2 = DBL_MAX;
	}
	else
		retrieve_t(a, b, disc, (double *[2]){t1, t2});
}

int	is_intersect_sphere(t_ray ray, t_sphere *sphere, double *prev_t)
{
	double	t1;
	double	t2;
	float	temp;

	t1 = 0;
	t2 = 0;
	get_t_sphere(sphere, ray, &t1, &t2);
	if (t1 == DBL_MAX && t2 == DBL_MAX)
		return (0);
	if (t1 > t2)
	{
		temp = t1;
		t1 = t2;
		t2 = temp;
	}
	if (vector_length(subtract_v(ray.origin, sphere->position)) <= sphere->diam
		/ 2 && t2 > 0 && *prev_t > t2)
		return (*prev_t = t2, 1);
	else if (t1 > 0 && *prev_t > t1)
		return (*prev_t = t1, 1);
	return (0);
}
