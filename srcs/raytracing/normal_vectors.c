#include "mini_rt.h"

t_vector	get_normal_sphere_new(t_vector inter,
		t_vector camera_pos, t_sphere *sphere)
{
	t_vector	result;

	result = normalize_vector(subtract_v(inter, sphere->position));
	if (vector_length(subtract_v(camera_pos, sphere->position)) > sphere->diam
		/ 2 + OFFSET_NORMAL)
		result = multiply_v(result, -1);
	return (result);
}

t_vector	get_normal_vector_sphere(t_vector inter,
		t_vector center)
{
	return (get_direction_vector(inter, center));
}

t_vector	get_normal_vector_plane(t_ray ray, t_plane plane)
{
	if (dot_product(subtract_v(ray.origin, plane.position),
			plane.orientation) > 0)
		return (multiply_v(plane.orientation, -1));
	return (plane.orientation);
}

t_vector get_normal_vector_cylinder_new(t_vector intersect, t_cylinder *cylinder)
{
	if (cylinder->is_caps == TOP)
		return (multiply_v(cylinder->orientation, -1));
	else if (cylinder->is_caps == BOTTOM)
		return (cylinder->orientation);
	else if (cylinder->is_caps == SIDE)
	{
		t_vector	pos_to_inter = subtract_v(intersect, cylinder->position);
		t_vector	parallel = multiply_v(cylinder->orientation,
				dot_product(pos_to_inter, cylinder->orientation));
		t_vector	normal = subtract_v(pos_to_inter, parallel);
		(void)normal;
		return (normalize_vector(multiply_v(normal, -1)));
	}
	return (printf("idk"), (t_vector){0, 1, 0});
}