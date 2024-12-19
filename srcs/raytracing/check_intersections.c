#include "mini_rt.h"

int	is_intersect_ray_cylinder(t_ray ray, t_cylinder *cylinder, double *prev_t)
{
	double	height_pos;
	double	caps_t;
	double	temp;

	double t1, t2;
	cylinder->is_caps = NOWHERE;
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
	if (t1 > DBL_EPSILON && t1 < *prev_t)
	{
		height_pos = dot_product(subtract_v(get_inter(ray, t1),
					cylinder->position), cylinder->orientation);
		if (height_pos >= 0 && height_pos <= cylinder->height && (caps_t == 0
				|| t1 < caps_t))
			return (*prev_t = t1, cylinder->is_caps = SIDE, 1);
	}
	if (t2 > DBL_EPSILON && t2 < *prev_t)
	{
		height_pos = dot_product(subtract_v(get_inter(ray, t2),
					cylinder->position), cylinder->orientation);
		if (height_pos >= 0 && height_pos <= cylinder->height && (caps_t == 0
				|| t2 < caps_t))
			return (*prev_t = t2, cylinder->is_caps = SIDE, 1);
	}
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

int	is_intersect_sphere(t_ray ray, t_sphere *sphere, double *prev_t)
{
	t_vector	origin_to_center;
	float		a;
	float		b;
	float		c;
	float		disc;
	double		t1;
	double		t2;
	float		temp;

	t1 = 0;
	t2 = 0;
	origin_to_center = subtract_v(sphere->position, ray.origin);
	a = dot_product(ray.direction, ray.direction);
	b = -2 * dot_product(origin_to_center, ray.direction);
	c = dot_product(origin_to_center, origin_to_center) - pow(sphere->diam / 2,
			2);
	disc = b * b - 4 * a * c;
	retrieve_t(a, b, disc, &t1, &t2);
	if (t1 > t2)
	{
		temp = t1;
		t1 = t2;
		t2 = temp;
	}
	if (vector_length(origin_to_center) <= sphere->diam / 2)
	{
		if (t2 > 0 && *prev_t > t2)
			return (*prev_t = t2, 1);
	}
	else
	{
		if (t1 > 0 && *prev_t > t1)
			return (*prev_t = t1, 1);
	}
	return (0);
}