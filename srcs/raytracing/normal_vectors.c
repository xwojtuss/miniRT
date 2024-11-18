#include "mini_rt.h"

t_vector	get_intersection_point(t_ray ray, float t);

t_vector	get_normal_vector_sphere(t_ray ray, t_vector center)
{
	return (normalize_vector(subtract_v(ray.origin, center)));
}

t_vector	get_normal_vector_plane(t_ray ray, t_plane plane)
{
	if (dot_product(subtract_v(ray.origin, plane.position), plane.orientation) > 0)
		return (multiply_v(plane.orientation, -1));
	return (plane.orientation);
}

t_vector	get_normal_vector_cylinder(t_ray ray, t_cylinder *cylinder, float t)
{
	t_vector	oc;
	t_vector	p;
	t_vector	normal;
	float		m;

	oc = subtract_v(ray.origin, cylinder->position);
	p = get_intersection_point(ray, t);
	m = dot_product(p, cylinder->orientation);
	normal = subtract_v(subtract_v(p, cylinder->position),
			multiply_v(cylinder->orientation, m));
	return (normalize_vector(normal));
}