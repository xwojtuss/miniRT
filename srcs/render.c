/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ukireyeu < ukireyeu@student.42warsaw.pl    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/20 15:57:43 by wkornato          #+#    #+#             */
/*   Updated: 2024/09/25 22:06:41 by ukireyeu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini_rt.h"

float	retrieve_t_sphere(float a, float b, float disc)
{
	float	t;

	if (disc < 0)
		return (0);
	t = (-b + disc) / (2 * a);
	return (t);
}

// TODO: return the x of the closest intersection
int	is_intersect_ray_sphere(t_ray ray, t_sphere *sphere)
{
	t_vector	origin_to_center;
	float		a;
	float		b;
	float		c;
	float		discriminant;
	float		t;

	origin_to_center = add_v(multiply_v(ray.origin, -1), sphere->position);
	a = dot_product(ray.direction, ray.direction);
	b = -2 * dot_product(origin_to_center, ray.direction);
	c = dot_product(origin_to_center, origin_to_center) - pow(sphere->diam / 2,
			2);
	discriminant = b * b - 4 * a * c;
	if (discriminant < 0)
		return (NOT_SET);
	t = retrieve_t_sphere(a, b, discriminant);
	printf("The value of t: %f\n", t);
	return (color_to_int(sphere->color));
}

int	is_intersect(t_ray ray, t_objects *object)
{
	if (object->type == SPHERE)
		return (is_intersect_ray_sphere(ray, object->object));
	return (NOT_SET);
}

int	trace_ray(t_ray ray, t_scene *scene)
{
	t_objects	*curr;
	int			color;
	t_vector	color_vector;

	(void)scene;
	curr = scene->objects;
	while (curr)
	{
		color = is_intersect(ray, curr);
		if (color != NOT_SET)
			return (color);
		curr = curr->next;
	}
	if (color == NOT_SET)
		return (0x000000);
	return (rgb_to_int(color_vector.x * 255, color_vector.y * 255,
			color_vector.z * 255));
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
