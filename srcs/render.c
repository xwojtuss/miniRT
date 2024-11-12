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

void retrieve_t(float a, float b, float disc, float *t1, float *t2)
{
	if (disc < 0)
	{
		*t1 = 0;
		*t2 = 0;
		return;
	}
	*t1 = (-b + sqrt(disc)) / (2 * a);
	*t2 = (-b - sqrt(disc)) / (2 * a);
}

int is_intersect_cylinder_caps(t_ray ray, t_cylinder cylinder, float *t_cap)
{
	float t1, t2;
	t_vector ctop, cbottom, p1, p2;
	float radius = cylinder.diam / 2;

	ctop = add_v(cylinder.position, multiply_v(cylinder.orientation, cylinder.height));
	cbottom = cylinder.position;
	t1 = dot_product(subtract_v(cbottom, ray.origin), cylinder.orientation) / dot_product(ray.direction, cylinder.orientation);
	t2 = dot_product(subtract_v(ctop, ray.origin), cylinder.orientation) / dot_product(ray.direction, cylinder.orientation);
	if (t1 > FLT_EPSILON)
	{
		p1 = get_intersection_point(ray, t1);
		if (vector_length(subtract_v(p1, cbottom)) <= radius)
		{
			*t_cap = t1;
			return (1);
		}
	}
	if (t2 > FLT_EPSILON)
	{
		p2 = get_intersection_point(ray, t2);
		if (vector_length(subtract_v(p2, ctop)) <= radius)
		{
			*t_cap = t2;
			return (1);
		}
	}

	return (0);
}


int is_intersect_ray_cylinder(t_ray ray, t_cylinder *cylinder, float *prev_t)
{
	t_vector new_start;
	t_vector perpendicular_comp_start;
	t_vector perpendicular_comp_dist;
	float discriminant;
	float t1;
	float t2;
	float a;
	float b;
	float c;
	float t_cap;
	float height_pos;
	t_vector intersection_point;

	t1 = 0;
	t2 = 0;
	t_cap = FLT_MAX;
	if (!is_intersect_cylinder_caps(ray, *cylinder, &t_cap))
		t_cap = FLT_MAX;
	new_start = subtract_v(ray.origin, cylinder->position);
	perpendicular_comp_start = subtract_v(new_start, multiply_v(cylinder->orientation, dot_product(new_start, cylinder->orientation)));
	perpendicular_comp_dist = subtract_v(ray.direction, multiply_v(cylinder->orientation, dot_product(ray.direction, cylinder->orientation)));
	a = dot_product(perpendicular_comp_dist, perpendicular_comp_dist);
	b = 2 * dot_product(perpendicular_comp_dist, perpendicular_comp_start);
	c = dot_product(perpendicular_comp_start, perpendicular_comp_start) - pow(cylinder->diam / 2, 2);
	discriminant = b * b - 4 * a * c;
	if (discriminant < 0)
		return (0);
	retrieve_t(a, b, discriminant, &t1, &t2);
	if (t1 > t2)
	{
		float temp = t1;
		t1 = t2;
		t2 = temp;
	}
	float t = t1 > FLT_EPSILON ? t1 : t2;
	if (t <= FLT_EPSILON || t >= *prev_t)
		return (0);
	intersection_point = get_intersection_point(ray, t);
	height_pos = dot_product(cylinder->orientation, subtract_v(intersection_point, cylinder->position));
	if (height_pos < 0 || height_pos > cylinder->height)
	{
		if (t_cap < *prev_t)
		{
			*prev_t = t_cap;
			return (1);
		}
		return (0);
	}
	*prev_t = t;
	return (1);
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
        float temp = t1;
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
		// t_vector colorvec = multiply_v(add_v(subtract_v(get_intersection_point(ray, *t), ((t_sphere *)object->object)->position), (t_vector){1, 1, 1}), 128);
		// *color = (int)colorvec.x << 16 | (int)colorvec.y << 8 | (int)colorvec.z;
	}
	else if (object->type == PLANE)
	{
		if (is_intersect_plane(ray, object->object, t) == 0)
			return ;
		*color = color_to_int(((t_plane *)object->object)->color);
		// t_vector colorvec = multiply_v(add_v(((t_plane *)object->object)->orientation, (t_vector){1, 1, 1}), 128);
		// *color = (int)colorvec.x << 16 | (int)colorvec.y << 8 | (int)colorvec.z;
	}
	else if (object->type == CYLINDER)
	{
		if (is_intersect_ray_cylinder(ray, object->object, t) == 0)
			return ;
		*color = color_to_int(((t_cylinder *)object->object)->color);
		/* t_vector colorvec = multiply_v(add_v(((t_cylinder *)object->object)->orientation, (t_vector){1, 1, 1}), 128);
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
