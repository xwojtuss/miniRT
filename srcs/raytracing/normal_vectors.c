#include "mini_rt.h"

t_vector	get_intersection_point(t_ray ray, double t);

t_vector	get_normal_sphere_new(t_vector intersection_point,
		t_vector camera_pos, t_sphere *sphere)
{
	t_vector	result;

	result = normalize_vector(subtract_v(intersection_point, sphere->position));
	if (vector_length(subtract_v(camera_pos, sphere->position)) > sphere->diam
		/ 2 + OFFSET_NORMAL)
		result = multiply_v(result, -1);
	return (result);
}

t_vector	get_normal_vector_sphere(t_vector intersection_point,
		t_vector center)
{
	return (get_direction_vector(intersection_point, center));
}

t_vector	get_normal_vector_plane(t_ray ray, t_plane plane)
{
	if (dot_product(subtract_v(ray.origin, plane.position),
			plane.orientation) > 0)
		return (multiply_v(plane.orientation, -1));
	return (plane.orientation);
}

t_vector	get_normal_vector_cylinder(t_vector intersection_point,
		t_cylinder *cylinder)
{
	t_vector center_to_intersection = subtract_v(intersection_point,
			cylinder->position);
	t_vector projection = multiply_v(cylinder->orientation,
			dot_product(center_to_intersection, cylinder->orientation));
	t_vector projection_to_intersection = subtract_v(center_to_intersection,
			projection);

	if (dot_product(center_to_intersection,
			cylinder->orientation) > cylinder->height - OFFSET_NORMAL
		&& dot_product(center_to_intersection,
			cylinder->orientation) < cylinder->height + OFFSET_NORMAL)
		return (multiply_v(cylinder->orientation, -1.0));
	else if (dot_product(center_to_intersection,
			cylinder->orientation) < OFFSET_NORMAL)
		return (cylinder->orientation);

	if (vector_length(projection_to_intersection) > cylinder->diam / 2 + OFFSET_NORMAL
		&& vector_length(projection_to_intersection) < cylinder->diam / 2 - OFFSET_NORMAL)
		return (normalize_vector(projection_to_intersection));
	else
		return (multiply_v(normalize_vector(projection_to_intersection), -1.0));
}