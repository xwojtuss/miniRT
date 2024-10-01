/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wkornato <wkornato@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/20 15:57:43 by wkornato          #+#    #+#             */
<<<<<<< HEAD
/*   Updated: 2024/09/30 17:14:55 by wkornato         ###   ########.fr       */
=======
/*   Updated: 2024/09/26 17:53:43 by ukireyeu         ###   ########.fr       */
>>>>>>> 7b3b2ab (fix elements)
/*                                                                            */
/* ************************************************************************** */

#include "mini_rt.h"

<<<<<<< HEAD
float	retrieve_t_sphere(float a, float b, float disc)
{
	float	t;

	if (disc < 0)
		return (0);
	t = (-b + sqrt(disc)) / (2 * a);
	return (t);
}

int	is_intersect_ray_cylinder(t_ray ray, t_cylinder *cylinder)
{
	t_vector	new_start;

	new_start = subtract_v(ray.origin, cylinder->position);
	t_vector	perpendicular_comp_start;
	t_vector	perpendicular_comp_dist;

	perpendicular_comp_start = subtract_v(new_start, multiply_v(cylinder->orientation, dot_product(new_start, cylinder->orientation)));
	perpendicular_comp_dist = subtract_v(ray.direction, multiply_v(cylinder->orientation, dot_product(ray.direction, cylinder->orientation)));
	
	(void)perpendicular_comp_start;
	float discriminant;

	discriminant = dot_product(perpendicular_comp_dist, perpendicular_comp_dist) * 4 * pow(cylinder->diam / 2, 2);
	float t = -2 * dot_product(perpendicular_comp_dist, perpendicular_comp_start) + sqrt(discriminant) / 2 * dot_product(ray.direction, ray.direction);
	(void)t;
	if (discriminant < 0)
		return (NOT_SET);
	t_vector p_of_axis = add_v(subtract_v(perpendicular_comp_start, cylinder->position), multiply_v(subtract_v(perpendicular_comp_dist, cylinder->orientation), t));
	if (vector_length(p_of_axis) >= cylinder->height  || vector_length(p_of_axis) <= 0)
		return (NOT_SET);
	return (color_to_int(cylinder->color));
}

=======
>>>>>>> 7b3b2ab (fix elements)
// TODO: return the x of the closest intersection
int	render_sphere(t_ray ray, t_sphere *sphere, float *prev_t)
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
<<<<<<< HEAD
	discriminant = b * b - 4 * a * c;
	if (discriminant < 0)
		return (NOT_SET);
	t = retrieve_t_sphere(a, b, discriminant);
	(void)t;
	// printf("The value of t: %f\n", t);
	return (color_to_int(sphere->color));
=======
	disc = b * b - 4 * a * c;
	if (disc < 0)
		return (0);
	t = (-b + sqrt(disc)) / (2 * a);
	if (*prev_t > t)
		return (*prev_t = t, 1);
	return (0);
>>>>>>> 7b3b2ab (fix elements)
}

void	render_object(t_ray ray, t_objects *object, float *t, int *color)
{
	if (object->type == SPHERE)
<<<<<<< HEAD
		return (is_intersect_ray_sphere(ray, object->object));
	else if (object->type == CYLINDER)
		return (is_intersect_ray_cylinder(ray, object->object));
	return (NOT_SET);
=======
		if (render_sphere(ray, object->object, t))
		{
			*color = color_to_int(((t_sphere *)object->object)->color);
		}
>>>>>>> 7b3b2ab (fix elements)
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
