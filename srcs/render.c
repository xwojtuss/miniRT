/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wkornato <wkornato@student.42warsaw.pl>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/20 15:57:43 by wkornato          #+#    #+#             */
/*   Updated: 2024/11/12 22:09:46 by wkornato         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini_rt.h"

t_vector	get_intersection_point(t_ray ray, float t)
{
	return (add_v(ray.origin, multiply_v(ray.direction, t)));
}

t_vector	get_normal_vector_sphere(t_ray ray, t_vector center)
{
	return (normalize_vector(subtract_v(ray.origin, center)));
}

void	retrieve_t(float a, float b, float disc, float *t1, float *t2)
{
	if (disc < 0)
	{
		*t1 = 0;
		*t2 = 0;
		return ;
	}
	*t1 = (-b + sqrt(disc)) / (2 * a);
	*t2 = (-b - sqrt(disc)) / (2 * a);
}

float	is_intersect_cylinder_caps(t_ray ray, t_vector caps_info[2], t_cylinder *cylinder, float *prev_t)
{
	float t_cap_top, t_cap_bottom;
	t_vector	p;

	t_cap_bottom = dot_product(subtract_v(caps_info[0], ray.origin),
			cylinder->orientation) / dot_product(ray.direction,
			cylinder->orientation);
	if (t_cap_bottom > FLT_EPSILON)
	{
		p = get_intersection_point(ray, t_cap_bottom);
		if (vector_length(subtract_v(p, caps_info[0])) <= cylinder->diam / 2
			&& t_cap_bottom < *prev_t)
			return (*prev_t = t_cap_bottom, 1);
	}
	t_cap_top = dot_product(subtract_v(caps_info[1], ray.origin),
			cylinder->orientation) / dot_product(ray.direction,
			cylinder->orientation);
	if (t_cap_top > FLT_EPSILON)
	{
		p = get_intersection_point(ray, t_cap_top);
		if (vector_length(subtract_v(p, caps_info[1])) <= cylinder->diam / 2
			&& t_cap_top < *prev_t)
			return (*prev_t = t_cap_top, 1);
	}
	return (0);
}

void	get_t_cylinder(t_cylinder *cylinder, t_ray ray, float *t1, float *t2)
{
	t_vector	oc;
	t_vector	d;
	float	a;
	float	b;
	float	discriminant;

	oc = subtract_v(ray.origin, cylinder->position);
	d = subtract_v(ray.direction, multiply_v(cylinder->orientation,
				dot_product(ray.direction, cylinder->orientation)));
	oc = subtract_v(oc, multiply_v(cylinder->orientation, dot_product(oc,
					cylinder->orientation)));
	a = dot_product(d, d);
	b = 2 * dot_product(d, oc);
	discriminant = b * b - 4 * a * (dot_product(oc, oc) - pow(cylinder->diam / 2, 2));
	*t1 = FLT_MIN;
	*t2 = FLT_MIN;
	if (discriminant < 0)
		return ;
	retrieve_t(a, b, discriminant, t1, t2);
}

int	is_intersect_ray_cylinder(t_ray ray, t_cylinder *cylinder, float *prev_t)
{
	float	t;
	float	height_pos;
	float	t1, t2;
	t_vector cap_top, cap_bottom, p;

	cap_bottom = cylinder->position;
	cap_top = add_v(cylinder->position, multiply_v(cylinder->orientation,
				cylinder->height));
	get_t_cylinder(cylinder, ray, &t1, &t2);
	if (t1 == FLT_MIN && t2 == FLT_MIN)
		return (0);
	for (int i = 0; i < 2; ++i)
	{
		t = (i == 0) ? t1 : t2;
		if (t > FLT_EPSILON)
		{
			p = get_intersection_point(ray, t);
			height_pos = dot_product(subtract_v(p, cylinder->position),
					cylinder->orientation);
			if (height_pos >= 0 && height_pos <= cylinder->height
				&& t < *prev_t)
			{
				*prev_t = t;
				return (1);
			}
		}
	}
	return (is_intersect_cylinder_caps(ray, (t_vector[2]){cap_bottom, cap_top}, cylinder, prev_t));
}

static int	is_intersect_plane(t_ray ray, t_plane *plane, float *prev_t)
{
	float	ND;
	float	t;

	ND = dot_product(plane->orientation, ray.direction);
	if (ND == 0)
		return (0);
	t = dot_product(multiply_v(plane->orientation, -1), subtract_v(ray.origin,
				plane->position)) / ND;
	if (t > 0 && *prev_t > t)
		return (*prev_t = t, 1);
	return (0);
}

float	is_intersect_sphere(t_ray ray, t_sphere *sphere, float *prev_t)
{
	t_vector	origin_to_center;
	float		a;
	float		b;
	float		c;
	float		disc;
	float		t1;
	float		t2;
	float		temp;

	t1 = 0;
	t2 = 0;
	origin_to_center = subtract_v(sphere->position, ray.origin);
	a = dot_product(ray.direction, ray.direction);
	b = -2 * dot_product(origin_to_center, ray.direction);
	c = dot_product(origin_to_center, origin_to_center) - pow(sphere->diam / 2,
			2);
	disc = b * b - 4 * a * c;
	retrieve_t(a, b, disc, &t1, &t2);
	if (t1 > t2)
	{
		temp = t1;
		t1 = t2;
		t2 = temp;
	}
	if (vector_length(origin_to_center) <= sphere->diam / 2)
	{
		if (t2 > 0 && *prev_t > t2)
			return (*prev_t = t2, 1);
	}
	else
	{
		if (t1 > 0 && *prev_t > t1)
			return (*prev_t = t1, 1);
	}
	return (0);
}

void	render_object(t_ray ray, t_objects *object, float *t, int *color)
{
	if (object->type == SPHERE)
	{
		if (is_intersect_sphere(ray, object->object, t) == 0)
			return ;
		*color = color_to_int(((t_sphere *)object->object)->color);
		// t_vector colorvec = multiply_v(add_v(subtract_v(get_intersection_point(ray,
					// 		*t), ((t_sphere *)object->object)->position),
					// (t_vector){1, 1, 1}), 128);
		// *color = (int)colorvec.x << 16 | (int)colorvec.y << 8 | (int)colorvec.z;
	}
	else if (object->type == PLANE)
	{
		if (is_intersect_plane(ray, object->object, t) == 0)
			return ;
		*color = color_to_int(((t_plane *)object->object)->color);
		// t_vector colorvec = multiply_v(add_v(((t_plane *)object->object)->orientation,
					// (t_vector){1, 1, 1}), 128);
		// *color = (int)colorvec.x << 16 | (int)colorvec.y << 8 | (int)colorvec.z;
	}
	else if (object->type == CYLINDER)
	{
		if (is_intersect_ray_cylinder(ray, object->object, t) == 0)
			return ;
		*color = color_to_int(((t_cylinder *)object->object)->color);
		/* t_vector colorvec = multiply_v(add_v(((t_cylinder *)object->object)->orientation,
					(t_vector){1, 1, 1}), 128);
		*color = (int)colorvec.x << 16 | (int)colorvec.y << 8 | (int)colorvec.z; */
	}
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
									add_v(multiply_v(scene->viewport_grid_vector_x,
												x),
										multiply_v(scene->viewport_grid_vector_y,
												y)));
			ray_direction = subtract_v(pixel_center, scene->camera->position);
			ray = (t_ray){scene->camera->position, ray_direction};
			my_mlx_pixel_put(&scene->img, x, y, trace_ray(ray, scene));
			x++;
		}
		y++;
	}
	mlx_put_image_to_window(scene->mlx, scene->win, scene->img.img, 0, 0);
}
