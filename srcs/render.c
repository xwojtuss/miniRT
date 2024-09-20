/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wkornato <wkornato@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/20 15:57:43 by wkornato          #+#    #+#             */
/*   Updated: 2024/09/20 20:05:20 by wkornato         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini_rt.h"

int	is_intersect_ray_sphere(t_ray ray, t_sphere *sphere)
{
	t_vector	origin_to_center;
	float		a;
	float		b;
	float		c;
	origin_to_center = add_v(multiply_v(ray.origin, -1), sphere->position);
	a = dot_product(ray.direction, ray.direction);
	b = -2 * dot_product(origin_to_center, ray.direction);
	c = dot_product(origin_to_center, origin_to_center) - pow(sphere->diam / 2, 2);
	float discriminant = b * b - 4 * a * c;
	if (discriminant < 0)
		return (NOT_SET);
	return (color_to_int(sphere->color));
}

int	is_intersect(t_ray ray, t_objects *object)
{
	if (object->type == SPHERE)
		return (is_intersect_ray_sphere(ray, object->object));
	/* else if (object->type == PLANE)
		return (is_intersect_ray_plane(ray, object));
	else if (object->type == CYLINDER)
		return (is_intersect_ray_cylinder(ray, object)); */
	return (NOT_SET);
}

int	trace_ray(t_ray ray, t_scene *scene)
{
	(void)scene;
	t_objects	*curr;
	int			color;
	float		test;

	curr = scene->objects;
	while (curr)
	{
		color = is_intersect(ray, curr);
		if (color != NOT_SET)
			return (color);
		curr = curr->next;
	}
	test = 0.5 * (ray.direction.y - 1);
	t_vector color_vector = add_v(multiply_v((t_vector){1.0, 1.0, 1.0}, test), multiply_v((t_vector){0.5, 0.7, 1.0}, 1.0 - test));
	return (rgb_to_int(color_vector.x * 255, color_vector.y * 255, color_vector.z * 255));
}

void	render_scene(t_scene *scene)
{
	double		viewport_width;
	double		viewport_height;
	double	aspect_ratio;
	aspect_ratio = (double)(scene->win_width) / (double)(scene->win_height);
	int		image_width = scene->win_width;
	int		image_height = (int)(image_width / aspect_ratio);
	if (image_height < 1)
		image_height = 1;
	
	viewport_height = 2.0 * tan(deg_to_rad(scene->camera->fov) / 2.0);
	viewport_width = viewport_height * (double)(image_width) / image_height;
	
	t_vector viewport_xv = (t_vector){viewport_width, 0, 0};
	t_vector viewport_yv = (t_vector){0, -viewport_height, 0};
	t_vector viewport_xdv = divide_v(viewport_xv, (double)(image_width));
	t_vector viewport_ydv = divide_v(viewport_yv, (double)(image_height));
	t_vector pixel_start;
	t_vector pixel_00_location;

	pixel_start = subtract_v(subtract_v(subtract_v(scene->camera->position, (t_vector){0, 0, 1}), divide_v(viewport_xv, 2.0)), divide_v(viewport_yv, 2.0));
	pixel_00_location = add_v(pixel_start, divide_v(add_v(viewport_xdv, viewport_ydv), 2.0));
	
	int x;
	int y;
	y = 0;
	while (y < scene->win_height)
	{
		x = 0;
		while (x < scene->win_width)
		{
			t_vector	pixel_center;
			pixel_center = add_v(pixel_start, add_v(multiply_v(viewport_xdv, x), multiply_v(viewport_ydv, y)));
			t_vector	ray_direction;
			ray_direction = subtract_v(pixel_center, scene->camera->position);
			
			t_ray		ray;

			ray = (t_ray){scene->camera->position, ray_direction};
			my_mlx_pixel_put(&scene->img, x, y, trace_ray(ray, scene));
			x++;
		}
		y++;
	}
	mlx_put_image_to_window(scene->mlx, scene->win, scene->img.img, 0, 0);
}
