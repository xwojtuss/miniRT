/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wkornato <wkornato@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/20 15:57:43 by wkornato          #+#    #+#             */
/*   Updated: 2024/12/20 18:18:58 by wkornato         ###   ########.fr       */
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
					curr->object, &t) && t < *new_t))
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

t_vector	get_color_plane(t_plane *plane, t_raytrace_info *raytrace)
{
	t_vector	arbitrary;
	t_vector	p_local;
	int			x;
	int			y;

	if (plane->orientation.x == 0 && plane->orientation.y == 0)
		arbitrary = (t_vector){1, 0, 0};
	else
		arbitrary = (t_vector){0, 0, 1};
	raytrace->tangent = cross_product(arbitrary, raytrace->normal_vector);
	raytrace->bitangent = cross_product(raytrace->normal_vector,
			raytrace->tangent);
	p_local = subtract_v(raytrace->inter, plane->position);
	raytrace->u_val = 1.0 - dot_product(p_local, raytrace->tangent);
	raytrace->v_val = dot_product(p_local, raytrace->bitangent);
	raytrace->u_val = raytrace->u_val - floor(raytrace->u_val);
	raytrace->v_val = raytrace->v_val - floor(raytrace->v_val);
	if (!plane->texture)
		return (color_to_vector(plane->color));
	x = (int)(raytrace->u_val * plane->texture->width) % plane->texture->width;
	y = (int)(raytrace->v_val * plane->texture->height)
		% plane->texture->height;
	return (int_color_to_vector(get_pixel_color(plane->texture->img, x, y)));
}

t_vector	get_color_sphere(t_sphere *sphere, t_raytrace_info *raytrace)
{
	double	phi;
	double	theta;
	int		x;
	int		y;

	phi = acos(raytrace->normal_vector.y);
	theta = atan2(raytrace->normal_vector.z, raytrace->normal_vector.x);
	raytrace->u_val = (theta + PI) / PI;
	raytrace->v_val = phi / PI;
	if (raytrace->normal_vector.x == 1)
		raytrace->tangent = (t_vector){0, 1, 0};
	else
		raytrace->tangent = normalize_vector(cross_product((t_vector){1, 0, 0},
					raytrace->normal_vector));
	raytrace->bitangent = cross_product(raytrace->tangent,
			raytrace->normal_vector);
	if (!sphere->texture)
		return (color_to_vector(sphere->color));
	x = (int)(raytrace->u_val * sphere->texture->width)
		% sphere->texture->width;
	y = (int)(raytrace->v_val * sphere->texture->height)
		% sphere->texture->height;
	if (x < 0)
		x += sphere->texture->width;
	if (y < 0)
		y += sphere->texture->height;
	return (int_color_to_vector(get_pixel_color(sphere->texture->img, x, y)));
}

t_vector	get_color_cylinder(t_cylinder *cylinder, t_raytrace_info *raytrace)
{
	t_vector	p_local;
	int			x;
	int			y;

	p_local = subtract_v(raytrace->inter, cylinder->position);
	raytrace->v_val = dot_product(p_local, cylinder->orientation) / cylinder->height;
	if (cylinder->orientation.x == 0 && cylinder->orientation.y == 0)
		raytrace->tangent = (t_vector){1, 0, 0};
	else
		raytrace->tangent = (t_vector){0, 0, 1};
	raytrace->tangent = cross_product(cylinder->orientation, raytrace->tangent);
	raytrace->tangent = normalize_vector(raytrace->tangent);
	raytrace->bitangent = cross_product(cylinder->orientation,
			raytrace->tangent);
	raytrace->u_val = atan2(dot_product(p_local, raytrace->bitangent),
			dot_product(p_local, raytrace->tangent)) / (PI * 2);
	if (raytrace->u_val < 0)
		raytrace->u_val += 1;
	if (cylinder->texture == NULL)
		return (color_to_vector(cylinder->color));
	x = (int)(raytrace->u_val * cylinder->texture->width)
		% cylinder->texture->width;
	y = (int)(raytrace->v_val * cylinder->texture->height)
		% cylinder->texture->height;
	return (int_color_to_vector(get_pixel_color(cylinder->texture->img, x, y)));
}

void	recalculate_normal_vector(t_raytrace_info *raytrace)
{
	int			x;
	int			y;
	t_texture	*bump;
	t_vector	world_perturbation;

	if (raytrace->object->type == PLANE)
		bump = ((t_plane *)raytrace->object->object)->bump;
	else if (raytrace->object->type == SPHERE)
		bump = ((t_sphere *)raytrace->object->object)->bump;
	else if (raytrace->object->type == CYLINDER)
		bump = ((t_cylinder *)raytrace->object->object)->bump;
	else
		return ;
	if (!bump)
		return ;
	x = (int)(raytrace->u_val * bump->width) % bump->width;
	y = (int)(raytrace->v_val * bump->height) % bump->height;
	t_vector perturbation = int_color_to_vector(get_pixel_color(bump->img, x, y));
	perturbation.x = (perturbation.x / 255.0) * 2.0 - 1.0;
	perturbation.y = (perturbation.y / 255.0) * 2.0 - 1.0;
	perturbation.z = (perturbation.z / 255.0) * 2.0 - 1.0;
	world_perturbation = (t_vector){perturbation.x * raytrace->tangent.x
		+ perturbation.y * raytrace->bitangent.x + perturbation.z
		* raytrace->normal_vector.x, perturbation.x * raytrace->tangent.y
		+ perturbation.y * raytrace->bitangent.y + perturbation.z
		* raytrace->normal_vector.y, perturbation.x * raytrace->tangent.z
		+ perturbation.y * raytrace->bitangent.z + perturbation.z
		* raytrace->normal_vector.z};
	raytrace->normal_vector = normalize_vector(world_perturbation);
}

static int	trace_ray(t_ray ray, t_scene *scene)
{
	t_raytrace_info	raytrace;

	raytrace = init_raytrace_info(ray, scene);
	if (raytrace.object == NULL || raytrace.t == INFINITY)
		return (DEFAULT_BACKGROUND_COLOR);
	raytrace.inter = get_inter(ray, raytrace.t);
	if (raytrace.object->type == SPHERE)
	{
		raytrace.normal_vector = get_normal_sphere_new(raytrace.inter,
				scene->camera->position, raytrace.object->object);
		raytrace.color = get_color_sphere(raytrace.object->object, &raytrace);
	}
	else if (raytrace.object->type == CYLINDER)
	{
		raytrace.normal_vector = get_normal_vector_cylinder_new(raytrace.inter,
				raytrace.object->object);
		raytrace.color = get_color_cylinder(raytrace.object->object, &raytrace);
	}
	else if (raytrace.object->type == PLANE)
	{
		raytrace.normal_vector = get_normal_vector_plane(ray,
				*(t_plane *)raytrace.object->object);
		raytrace.color = get_color_plane(raytrace.object->object, &raytrace);
	}
	else
		return (DEFAULT_BACKGROUND_COLOR);
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
					add_v(multiply_v(scene->viewport_grid_vector_x, x),
						multiply_v(scene->viewport_grid_vector_y, y)));
			ray_direction = subtract_v(pixel_center, scene->camera->position);
			ray = (t_ray){scene->camera->position, ray_direction};
			my_mlx_pixel_put(&scene->img, x, y, trace_ray(ray, scene));
			x++;
		}
		y++;
	}
	mlx_put_image_to_window(scene->mlx, scene->win, scene->img.img, 0, 0);
}
