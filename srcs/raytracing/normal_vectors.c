#include "mini_rt.h"

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