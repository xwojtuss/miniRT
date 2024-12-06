#include "mini_rt.h"
#include "phong_reflection.h"

t_vector	get_intersection_point(t_ray ray, float t);

t_vector	reflect_ray(t_vector light_dir, t_vector normal)
{
	return (subtract_v(multiply_v(normal, 2 * dot_product(light_dir, normal)),
			light_dir));
}

t_vector	clamp_vector(t_vector vector, int min, int max)
{
	vector.x = fmin(max, fmax(min, vector.x));
	vector.y = fmin(max, fmax(min, vector.y));
	vector.z = fmin(max, fmax(min, vector.z));
	return (vector);
}

bool	find_closest_intersection(t_scene scene, t_ray ray, t_vector *intersection_point)
{
	t_objects	*curr;
	float		t;
	float		min_t;

	min_t = FLT_MAX;
	t = FLT_MAX;
	curr = scene.objects;
	while (curr)
	{
		if (curr->type == SPHERE)
		{
			if (is_intersect_sphere(ray, curr->object, &t))
			{
				if (t < min_t)
				{
					min_t = t;
					*intersection_point = get_intersection_point(ray, t);
				}
			}
		}
		else if (curr->type == PLANE)
		{
			if (is_intersect_plane(ray, curr->object, &t))
			{
				if (t < min_t)
				{
					min_t = t;
					*intersection_point = get_intersection_point(ray, t);
				}
			}
		}
		else if (curr->type == CYLINDER)
		{
			if (is_intersect_ray_cylinder(ray, curr->object, &t))
			{
				if (t < min_t)
				{
					min_t = t;
					*intersection_point = get_intersection_point(ray, t);
				}
			}
		}
		curr = curr->next;
	}
	return (min_t < FLT_MAX);
}

int	is_visible(t_scene *scene, t_vector intersection_point, t_vector normal, t_vector light_position)
{
	t_ray shadow_ray;
	t_vector shadow_intersection;
	// float light_distance;

	shadow_ray.origin = add_v(intersection_point, multiply_v(normal, FLT_EPSILON));
	shadow_ray.direction = normalize_vector(subtract_v(light_position, shadow_ray.origin));
	// light_distance = vector_length(subtract_v(light_position, shadow_ray.origin));
	if (find_closest_intersection(*scene, shadow_ray, &shadow_intersection))
	{
		shadow_intersection = add_v(shadow_intersection, multiply_v(normal, FLT_EPSILON));
		// float intersection_distance = vector_length(subtract_v(shadow_intersection, shadow_ray.origin));

		// if (intersection_distance < (light_distance - FLT_EPSILON))
		return (0);
	}
	return (1);
}


int	phong_reflection(t_raytrace_info info)
{
	t_vector	total_color;
	int			i;
	t_vector	light_dir;
	float		dot_diffuse;
	t_vector	diffuse;
	t_vector	reflected_ray;
	t_vector	view_vector;
	float		dot_specular;
	t_vector	specular;

	// if (info.inside)
	// 	info.intersection_point = subtract_v(info.intersection_point,
	// 			multiply_v(info.normal_vector, FLT_EPSILON));
	// else
	// 	info.intersection_point = add_v(info.intersection_point,
	// 			multiply_v(info.normal_vector, FLT_EPSILON));
	total_color = (t_vector){0, 0, 0};
	i = 0; 
	while (i < 1)
	{
		light_dir = get_direction_vector(info.scene.light[i].position,
					info.intersection_point);
		dot_diffuse = fmax(0, dot_product(light_dir, info.normal_vector));
		diffuse = multiply_v(multiply_v(info.color, DIFFUSE_CONST * dot_diffuse
				* info.scene.light[i].brightness), is_visible(&info.scene, info.intersection_point, info.normal_vector, info.scene.light[i].position));
		reflected_ray = reflect_ray(light_dir, info.normal_vector);
		view_vector = normalize_vector(subtract_v(info.scene.camera->position,
					info.intersection_point));
		dot_specular = fmax(0, dot_product(reflected_ray, view_vector));
		specular = multiply_v((t_vector){SPECULAR_CONST * pow(dot_specular,
				SHININESS_CONST) * info.scene.light[i].brightness,
			SPECULAR_CONST * pow(dot_specular, SHININESS_CONST)
			* info.scene.light[i].brightness, SPECULAR_CONST * pow(dot_specular,
				SHININESS_CONST) * info.scene.light[i].brightness}, is_visible(&info.scene, info.intersection_point, info.normal_vector, info.scene.light[i].position));
		total_color = add_v(total_color, add_v(diffuse, specular));
		i++;
	}
	total_color = clamp_vector(add_v(total_color, multiply_v(info.color, AMBIENT_CONST)), 0, 255);
	return (vector_to_int(total_color));
}
