/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_intersections.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wkornato <wkornato@student.42warsaw.pl>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/19 17:16:27 by wkornato          #+#    #+#             */
/*   Updated: 2024/12/31 16:25:35 by wkornato         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini_rt.h"

bool	check_side_cylinder(t_ray ray, t_cylinder *cylinder, double *t1, double *prev_t)
{
	double	height_pos;

	height_pos = dot_product(subtract_v(get_inter(ray, *t1),
				cylinder->position), cylinder->orientation);
	if (height_pos >= 0 && height_pos <= cylinder->height)
		return (*prev_t = *t1, 1);
	return (0);
}

bool	check_side_cone(t_ray ray, t_cone *cone, double *t1, double *prev_t)
{
	double	height_pos;

	height_pos = dot_product(subtract_v(get_inter(ray, *t1), cone->position), cone->orientation);

	if (height_pos >= -cone->height/2 && height_pos <= cone->height/2)
		return (*prev_t = *t1, 1);
	return (0);
}

int	is_intersect_ray_cylinder(t_ray ray, t_cylinder *cylinder, double *prev_t)
{
	double	t1;
	double	t2;

	get_t_cylinder(cylinder, ray, &t1, &t2);
	if (t1 == DBL_MAX && t2 == DBL_MAX)
		return (0);
	if (t1 > DBL_EPSILON && t1 < *prev_t && check_side_cylinder(ray, cylinder,
			&t1, prev_t))
		return (1);
	if (t2 > DBL_EPSILON && t2 < *prev_t && check_side_cylinder(ray, cylinder,
			&t2, prev_t))
		return (1);
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
	if (t > 0 && *prev_t > t && vector_length(subtract_v(get_inter(ray, t),
				plane->position)) < plane->diam / 2 + OFFSET_NORMAL)
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

bool	is_intersect_cone(t_ray ray, t_cone *cone, double *t)
{
	t_vector	origin_to_center;
	double		tan_theta_squared;
	double		a, b, c;
	double		discriminant;
	double		t1, t2;
	t_vector	intersect_point;
	double		height_proj;

	tan_theta_squared = pow((cone->diam / 2.0) / cone->height, 2);
	origin_to_center = subtract_v(ray.origin, add_v(cone->position, multiply_v(cone->orientation, cone->height)));

	a = dot_product(ray.direction, ray.direction) - 
        (1 + tan_theta_squared) * pow(dot_product(ray.direction, cone->orientation), 2);
    
    b = 2 * (dot_product(ray.direction, origin_to_center) - 
        (1 + tan_theta_squared) * dot_product(ray.direction, cone->orientation) * 
        dot_product(origin_to_center, cone->orientation));
    
    c = dot_product(origin_to_center, origin_to_center) - 
        (1 + tan_theta_squared) * pow(dot_product(origin_to_center, cone->orientation), 2);
	discriminant = b * b - 4 * a * c;
	if (discriminant < 0)
		return (false);
	retrieve_t(a, b, discriminant, (double *[2]){&t1, &t2});

	if (t1 > t2)
	{
		double temp = t1;
		t1 = t2;
		t2 = temp;
	}

	if (t1 > 0 && t1 < *t)
	{
		intersect_point = get_inter(ray, t1);
		height_proj = dot_product(subtract_v(intersect_point, cone->position), cone->orientation);
		if (height_proj >= 0 && height_proj <= cone->height)
			return (*t = t1, 1);
	}

	if (t2 > 0 && t2 < *t)
	{
		intersect_point = get_inter(ray, t2);
		height_proj = dot_product(subtract_v(intersect_point, cone->position), cone->orientation);
		if (height_proj >= 0 && height_proj <= cone->height)
			return (*t = t2, 1);
	}

	return (false);
}
