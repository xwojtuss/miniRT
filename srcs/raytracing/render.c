/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wkornato <wkornato@student.42warsaw.pl>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/20 15:57:43 by wkornato          #+#    #+#             */
/*   Updated: 2024/12/31 22:27:30 by wkornato         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini_rt.h"
#include "phong_reflection.h"

t_objects	*get_closest_object(t_scene scene, t_ray ray, double *new_t)
{
	t_objects	*curr;
	t_objects	*result;
	double		t;

	*new_t = INFINITY;
	t = INFINITY;
	curr = scene.objects;
	result = scene.objects;
	while (curr)
	{
		if ((curr->type == SPHERE && is_intersect_sphere(ray, curr->object, &t)
				&& t < *new_t) || (curr->type == PLANE
				&& is_intersect_plane(ray, curr->object, &t) && t < *new_t)
			|| (curr->type == CYLINDER && is_intersect_ray_cylinder(ray,
					curr->object, &t) && t < *new_t) || (curr->type == CONE
				&& is_intersect_cone(ray, curr->object, &t) && t < *new_t))
		{
			*new_t = t;
			result = curr;
		}
		curr = curr->next;
	}
	if (*new_t >= DBL_MAX)
		return (NULL);
	return (result);
}

static t_raytrace_info	init_raytrace_info(t_ray ray, t_scene *scene)
{
	t_raytrace_info	raytrace;

	raytrace.scene = scene;
	raytrace.t = INFINITY;
	raytrace.object = get_closest_object(*scene, ray, &raytrace.t);
	raytrace.ray = &ray;
	raytrace.color = (t_vector){0, 0, 0};
	raytrace.inter = (t_vector){0, 0, 0};
	raytrace.normal_vector = (t_vector){0, 0, 0};
	return (raytrace);
}

static void	get_normal_vectors(t_scene *scene, t_raytrace_info *raytrace,
		t_ray ray)
{
	if (raytrace->object->type == PLANE)
		raytrace->normal_vector = get_nv_plane(ray, raytrace->object->object);
	else if (raytrace->object->type == SPHERE)
		raytrace->normal_vector = get_nv_sphere(raytrace->inter,
				scene->camera->position, raytrace->object->object);
	else if (raytrace->object->type == CYLINDER)
		raytrace->normal_vector = get_nv_cylinder(raytrace->inter,
				raytrace->object->object, ray);
	else if (raytrace->object->type == CONE)
		raytrace->normal_vector = get_nv_cone(raytrace->inter,
				raytrace->object->object, ray);
}

static int	trace_ray(t_ray ray, t_scene *scene)
{
	t_raytrace_info	raytrace;

	raytrace = init_raytrace_info(ray, scene);
	if (raytrace.object == NULL || raytrace.t == INFINITY)
		return (vector_to_int(scale_v(color_to_vector(scene->ambient->color),
					scene->ambient->brightness)));
	raytrace.inter = get_inter(ray, raytrace.t);
	get_normal_vectors(scene, &raytrace, ray);
	if (raytrace.object->type == SPHERE)
		raytrace.color = get_color_sphere(raytrace.object->object, &raytrace);
	else if (raytrace.object->type == CYLINDER)
		raytrace.color = get_color_cylinder(raytrace.object->object, &raytrace);
	else if (raytrace.object->type == PLANE)
		raytrace.color = get_color_plane(raytrace.object->object, &raytrace);
	else if (raytrace.object->type == CONE)
		raytrace.color = get_color_cone(raytrace.object->object, &raytrace);
	recalculate_normal_vector(&raytrace);
	return (phong_reflection(raytrace));
}

void	render_scene(t_scene *scene)
{
	int			x;
	int			y;
	t_vector	pixel_center;
	t_vector	ray_direction;
	t_ray		ray;

	y = 0;
	while (y < scene->win_height)
	{
		x = 0;
		while (x < scene->win_width)
		{
			pixel_center = add_v(scene->viewport_top_left,
					add_v(scale_v(scene->viewport_grid_vector_x, x),
						scale_v(scene->viewport_grid_vector_y, y)));
			ray_direction = subtract_v(pixel_center, scene->camera->position);
			ray = (t_ray){scene->camera->position, ray_direction};
			my_mlx_pixel_put(&scene->img, x, y, trace_ray(ray, scene));
			x++;
		}
		y++;
	}
	mlx_put_image_to_window(scene->mlx, scene->win, scene->img.img, 0, 0);
}
