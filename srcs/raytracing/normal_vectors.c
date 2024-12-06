#include "mini_rt.h"

t_vector	get_intersection_point(t_ray ray, double t);

t_vector	get_normal_sphere_new(t_vector intersection_point, t_vector camera_pos, t_sphere *sphere)
{
	t_vector result;
	
	result = normalize_vector(subtract_v(intersection_point, sphere->position));
	if (vector_length(subtract_v(camera_pos, sphere->position)) > sphere->diam / 2)
		result = multiply_v(result, -1);
	return (result);
}

t_vector	get_normal_vector_sphere(t_vector intersection_point, t_vector center)
{
	return (get_direction_vector(intersection_point, center));
}

t_vector	get_normal_vector_plane(t_ray ray, t_plane plane)
{
	if (dot_product(subtract_v(ray.origin, plane.position), plane.orientation) > 0)
		return (multiply_v(plane.orientation, -1));
	return (plane.orientation);
}

t_vector	get_normal_vector_cylinder(t_ray ray, t_cylinder *cylinder, double t)
{
	t_vector	p;
	t_vector	normal;
	float		m;

	p = get_intersection_point(ray, t);
	m = dot_product(p, cylinder->orientation);
	normal = subtract_v(subtract_v(p, cylinder->position),
			multiply_v(cylinder->orientation, m));
	return (normalize_vector(normal));
}