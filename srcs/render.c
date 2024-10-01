/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ukireyeu < ukireyeu@student.42warsaw.pl    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/20 15:57:43 by wkornato          #+#    #+#             */
/*   Updated: 2024/10/01 20:49:41 by ukireyeu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini_rt.h"

int	is_intersect_ray_cylinder(t_ray ray, t_cylinder *cylinder)
{
	t_vector	new_start;
	t_vector	perpendicular_comp_start;
	t_vector	perpendicular_comp_dist;
	t_vector p_of_axis;
	float discriminant;
	float t;

	new_start = subtract_v(ray.origin, cylinder->position);
	perpendicular_comp_start = subtract_v(new_start, multiply_v(cylinder->orientation, dot_product(new_start, cylinder->orientation)));
	perpendicular_comp_dist = subtract_v(ray.direction, multiply_v(cylinder->orientation, dot_product(ray.direction, cylinder->orientation)));

	(void)perpendicular_comp_start;

	discriminant = dot_product(perpendicular_comp_dist, perpendicular_comp_dist) * 4 * pow(cylinder->diam / 2, 2);
	t = -2 * dot_product(perpendicular_comp_dist, perpendicular_comp_start) + sqrt(discriminant) / 2 * dot_product(ray.direction, ray.direction);
	(void)t;
	if (discriminant < 0)
		return (NOT_SET);
	p_of_axis = add_v(subtract_v(perpendicular_comp_start, cylinder->position), multiply_v(subtract_v(perpendicular_comp_dist, cylinder->orientation), t));
	if (vector_length(p_of_axis) >= cylinder->height  || vector_length(p_of_axis) <= 0)
		return (NOT_SET);
	return (color_to_int(cylinder->color));
}

t_vector	get_intersection_point(t_ray ray, float t)
{
	return (add_v(ray.origin, multiply_v(ray.direction, t)));
}

t_vector	get_normal_vector_sphere(t_ray ray, t_vector center)
{
	return (normalize_vector(subtract_v(ray.origin, center)));
}

static int	intersect_sphere(t_ray ray, t_sphere *sphere, float *prev_t)
{
	t_vector	origin_to_center;
	float		a;
	float		b;
	float		c;
	float		disc;
	float		t;

	origin_to_center = add_v(multiply_v(ray.origin, -1), sphere->position);
	a = dot_product(ray.direction, ray.direction);
	b = -2 * dot_product(origin_to_center, ray.direction);
	c = dot_product(origin_to_center, origin_to_center) - pow(sphere->diam / 2,
			2);
	disc = b * b - 4 * a * c;
	if (disc < 0)
		return (0);
	t = retrieve_t_sphere(a, b, disc);
	if (*prev_t > t && t > 0)
		return (*prev_t = t, 1);
	return (0);
}

static int	intersect_plane(t_ray ray, t_plane *plane, float *prev_t)
{
	float	ND;
	float	t;

	ND = dot_product(plane->orientation, ray.direction);
	if (ND <= 0)
		return (0);
	t = dot_product(multiply_v(plane->orientation, -1), subtract_v(ray.origin,
				plane->position)) / ND;
	if (t > 0 && *prev_t > t)
		return (*prev_t = t, 1);
	return (0);
}

static int	intersect_plane(t_ray ray, t_plane *plane, float *prev_t)
{
	float	ND;
	float	t;

	ND = dot_product(plane->orientation, ray.direction);
	if (ND <= 0)
		return (0);
	t = dot_product(multiply_v(plane->orientation, -1), subtract_v(ray.origin,
				plane->position)) / ND;
	if (t > 0 && *prev_t > t)
		return (*prev_t = t, 1);
	return (0);
}

void	render_object(t_ray ray, t_objects *object, float *t, int *color)
{
	if (object->type == SPHERE)
		if (intersect_sphere(ray, object->object, t))
			*color = color_to_int(((t_sphere *)object->object)->color);
	if (object->type == PLANE)
		if (intersect_plane(ray, object->object, t))
			*color = color_to_int(((t_plane *)object->object)->color);
}

int	trace_ray(t_ray ray, t_scene *scene)
{
	t_objects	*curr;
	int			color;
	float		t;

	(void)scene;
	curr = scene->objects;
	t = FLT_MAX;
	color = 0x000000;
	while (curr)
	{
		render_object(ray, curr, &t, &color);
		curr = curr->next;
	}
	return (color);
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
