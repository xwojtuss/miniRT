#include "mini_rt.h"
#include "phong_reflection.h"

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
	t_vector	ambient;

	total_color = (t_vector){0, 0, 0};
	i = 0;
	while (i < 1)
	{
		light_dir = normalize_vector(get_direction_vector(info.scene.light[i].position,
					info.intersection_point));
		dot_diffuse = fmax(0, dot_product(light_dir, info.normal_vector));
		diffuse = multiply_v(info.color, DIFFUSE_CONST * dot_diffuse
				* info.scene.light[i].brightness);
		reflected_ray = reflect_ray(light_dir, info.normal_vector);
		view_vector = normalize_vector(subtract_v(info.scene.camera->position,
					info.intersection_point));
		dot_specular = fmax(0, dot_product(reflected_ray, view_vector));
		specular = (t_vector){SPECULAR_CONST * pow(dot_specular,
				SHININESS_CONST) * info.scene.light[i].brightness,
			SPECULAR_CONST * pow(dot_specular, SHININESS_CONST)
			* info.scene.light[i].brightness, SPECULAR_CONST * pow(dot_specular,
				SHININESS_CONST) * info.scene.light[i].brightness};
		total_color = add_v(total_color, add_v(diffuse, specular));
		i++;
	}
	ambient = multiply_v(info.color, AMBIENT_CONST);
	total_color = add_v(total_color, ambient);
	total_color = clamp_vector(total_color, 0, 255);
	return (vector_to_int(total_color));
}
