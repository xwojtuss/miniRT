#include "mini_rt.h"

t_vector	get_normal_vector_sphere(t_ray ray, t_vector center)
{
	return (normalize_vector(subtract_v(ray.origin, center)));
}