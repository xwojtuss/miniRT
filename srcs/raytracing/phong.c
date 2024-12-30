/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   phong.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wkornato <wkornato@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/07 16:56:12 by wkornato          #+#    #+#             */
/*   Updated: 2024/12/30 04:37:35 by wkornato         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini_rt.h"
#include "phong_reflection.h"

t_vector	reflect_ray(t_vector incident, t_vector normal)
{
	return (subtract_v(incident, multiply_v(normal, 2 * dot_product(incident,
					normal))));
}

t_vector	clamp_vector(t_vector vector, int min, int max)
{
	vector.x = fmin(max, fmax(min, vector.x));
	vector.y = fmin(max, fmax(min, vector.y));
	vector.z = fmin(max, fmax(min, vector.z));
	return (vector);
}

int	is_visible(t_scene *scene, t_vector inter, t_vector normal,
		t_vector light_position)
{
	t_ray		shadow_ray;
	t_vector	shadow_intersection;
	float		light_distance;
	float		intersection_distance;
	double		t;

	shadow_ray.origin = add_v(inter, multiply_v(normal, DBL_EPSILON));
	shadow_ray.direction = normalize_vector(subtract_v(light_position,
				shadow_ray.origin));
	light_distance = vector_length(subtract_v(light_position,
				shadow_ray.origin));
	if (get_closest_object(*scene, shadow_ray, &t))
	{
		shadow_intersection = get_inter(shadow_ray, t);
		shadow_intersection = add_v(shadow_intersection, multiply_v(normal,
					DBL_EPSILON));
		intersection_distance = vector_length(subtract_v(shadow_intersection,
					shadow_ray.origin));
		if (intersection_distance < (light_distance - FLT_EPSILON))
			return (0);
	}
	return (1);
}

void	calculate_color(t_vector *total_color, t_lights *curr,
		t_raytrace_info info, t_vector light_dir)
{
	t_vector	diffuse;
	t_vector	reflected_ray;
	t_vector	view_vector;
	t_vector	specular;

	diffuse = multiply_v_color(info.color,
			multiply_v(color_to_vector(curr->color), get_diffuse(info.object)
				* fmax(0, dot_product(light_dir, info.normal_vector))
				* curr->brightness));
	reflected_ray = reflect_ray(light_dir, info.normal_vector);
	view_vector = normalize_vector(subtract_v(info.scene->camera->position,
				info.inter));
	specular = multiply_v(color_to_vector(curr->color),
			get_specular(info.object) * pow(fmax(0,
					dot_product(info.normal_vector,
						normalize_vector(add_v(light_dir, view_vector)))),
				get_shininess(info.object)) * curr->brightness);
	*total_color = add_v(*total_color, add_v(diffuse, specular));
}

int	phong_reflection(t_raytrace_info info)
{
	t_vector	total_color;
	t_vector	light_dir;
	t_lights	*curr;

	total_color = (t_vector){0, 0, 0};
	info.inter = subtract_v(info.inter, multiply_v(info.normal_vector,
				OFFSET_NORMAL));
	curr = info.scene->light;
	while (curr)
	{
		if (is_visible(info.scene, info.inter, info.normal_vector,
				curr->position))
		{
			light_dir = get_direction_vector(curr->position, info.inter);
			calculate_color(&total_color, curr, info, light_dir);
		}
		curr = curr->next;
	}
	total_color = add_v(multiply_v_color(info.color,
				multiply_v(color_to_vector(info.scene->ambient->color),
					info.scene->ambient->brightness
					* get_ambient(info.object))), total_color);
	total_color = clamp_vector(total_color, 0, 255);
	return (vector_to_int(total_color));
}
