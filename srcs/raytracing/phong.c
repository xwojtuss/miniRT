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

int	is_visible(t_raytrace_info *info, t_vector light_dir)
{
	t_objects	*curr;
	float		temp;

	temp = FLT_MAX;
	
	if (info->object->type == SPHERE)
	{
		if (is_intersect_sphere((t_ray){info->scene.light->position, multiply_v(light_dir, -1)}, info->object->object, &temp) == 1)
			printf("This is so weird for sphere\n");
	}
	else if (info->object->type == PLANE)
	{
		if (is_intersect_plane((t_ray){info->scene.light->position, multiply_v(light_dir, -1)}, info->object->object, &temp) == 1)
			printf("This is so weird for plane\n");
	}
	else if (info->object->type == CYLINDER)
	{
		if (is_intersect_ray_cylinder((t_ray){info->scene.light->position, multiply_v(light_dir, -1)}, info->object->object, &temp) == 1)
			printf("This is so weird for cylinder\n");
	}
	curr = info->scene.objects;
	while (curr)
	{
		if (curr->type == SPHERE)
		{
			if (is_intersect_sphere((t_ray){add_v(info->intersection_point, divide_v(info->normal_vector, 1000)), light_dir}, curr->object, &temp) == 1)
				return (0);
		}
		else if (curr->type == PLANE && info->object != curr)
		{
			if (is_intersect_plane((t_ray){add_v(info->intersection_point, divide_v(info->normal_vector, 1000)), light_dir}, curr->object, &temp) == 1)
				return (0);
		}
		else if (curr->type == CYLINDER)
		{
			if (is_intersect_ray_cylinder((t_ray){add_v(info->intersection_point, divide_v(info->normal_vector, 1000)), light_dir}, curr->object, &temp) == 1)
				return (0);
		}
		curr = curr->next;
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

	total_color = (t_vector){0, 0, 0};
	i = 0;
	while (i < 1)
	{
		light_dir = get_direction_vector(info.scene.light[i].position,
					info.intersection_point);
		dot_diffuse = fmax(0, dot_product(light_dir, info.normal_vector));
		diffuse = multiply_v(multiply_v(info.color, DIFFUSE_CONST * dot_diffuse
				* info.scene.light[i].brightness), is_visible(&info, light_dir));
		reflected_ray = reflect_ray(light_dir, info.normal_vector);
		view_vector = normalize_vector(subtract_v(info.scene.camera->position,
					info.intersection_point));
		dot_specular = fmax(0, dot_product(reflected_ray, view_vector));
		specular = multiply_v((t_vector){SPECULAR_CONST * pow(dot_specular,
				SHININESS_CONST) * info.scene.light[i].brightness,
			SPECULAR_CONST * pow(dot_specular, SHININESS_CONST)
			* info.scene.light[i].brightness, SPECULAR_CONST * pow(dot_specular,
				SHININESS_CONST) * info.scene.light[i].brightness}, is_visible(&info, reflected_ray));
		total_color = add_v(total_color, add_v(diffuse, specular));
		i++;
	}
	total_color = clamp_vector(add_v(total_color, multiply_v(info.color, AMBIENT_CONST)), 0, 255);
	return (vector_to_int(total_color));
}
