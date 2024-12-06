/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wkornato <wkornato@student.42warsaw.pl>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/20 15:57:43 by wkornato          #+#    #+#             */
/*   Updated: 2024/12/06 20:46:22 by wkornato         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini_rt.h"
#include "phong_reflection.h"

t_vector get_intersection_point(t_ray ray, double t)
{
	return (add_v(ray.origin, multiply_v(ray.direction, t)));
}

void retrieve_t(double a, double b, double disc, double *t1, double *t2)
{
	double temp;
	double sqrt_disc;

    if (disc < 0)
    {
        *t1 = DBL_MAX;
        *t2 = DBL_MAX;
        return;
    }
    sqrt_disc = sqrt(disc);
    *t1 = (-b - sqrt_disc) / (2.0 * a);
    *t2 = (-b + sqrt_disc) / (2.0 * a); 
    if (*t1 > *t2)
    {
        temp = *t1;
        *t1 = *t2;
        *t2 = temp;
    }
}

double	is_intersect_cylinder_caps(t_ray ray,
		t_cylinder *cylinder, double *prev_t)
{
	t_vector cap_top, cap_bottom, p;
	double t_cap_top, t_cap_bottom;
	
	cap_bottom = cylinder->position;
	cap_top = add_v(cylinder->position, multiply_v(cylinder->orientation,
				cylinder->height));
	t_cap_bottom = dot_product(subtract_v(cap_bottom, ray.origin),
			cylinder->orientation) / dot_product(ray.direction,
			cylinder->orientation);
	t_cap_top = dot_product(subtract_v(cap_top, ray.origin),
			cylinder->orientation) / dot_product(ray.direction,
			cylinder->orientation);
	if (t_cap_bottom > DBL_EPSILON && t_cap_bottom < *prev_t && (t_cap_bottom < t_cap_top || t_cap_top < 0))
	{
		p = get_intersection_point(ray, t_cap_bottom);
		if (vector_length(subtract_v(p, cap_bottom)) <= cylinder->diam / 2)
			return (t_cap_bottom);
	}
	if (t_cap_top > DBL_EPSILON && t_cap_top < *prev_t)
	{
		p = get_intersection_point(ray, t_cap_top);
		if (vector_length(subtract_v(p, cap_top)) <= cylinder->diam / 2)
			return (t_cap_top);
	}
	return (0);
}

void get_t_cylinder(t_cylinder *cylinder, t_ray ray, double *t1, double *t2)
{
    t_vector oc;
    t_vector d;
    double a, b, discriminant;

    oc = subtract_v(ray.origin, cylinder->position);
    d = subtract_v(ray.direction, multiply_v(cylinder->orientation,
                dot_product(ray.direction, cylinder->orientation)));
    oc = subtract_v(oc, multiply_v(cylinder->orientation, dot_product(oc,
                    cylinder->orientation)));
    a = dot_product(d, d);
    b = 2.0 * dot_product(d, oc);
    discriminant = b * b - 4.0 * a * (dot_product(oc, oc) - pow(cylinder->diam / 2.0, 2));
    *t1 = DBL_MAX;
    *t2 = DBL_MAX;
    if (discriminant >= 0)
        retrieve_t(a, b, discriminant, t1, t2);
}

int is_intersect_ray_cylinder(t_ray ray, t_cylinder *cylinder, double *prev_t)
{
    double	t1, t2;
	double	height_pos;
	double	caps_t;
    get_t_cylinder(cylinder, ray, &t1, &t2);
    
    if (t1 == DBL_MAX && t2 == DBL_MAX)
        return (0);
    if (t1 > t2)
	{
        double temp = t1;
        t1 = t2;
        t2 = temp;
    }
	caps_t = is_intersect_cylinder_caps(ray, cylinder, prev_t);
    if (t1 > DBL_EPSILON && t1 < *prev_t)
    {
        height_pos = dot_product(subtract_v(get_intersection_point(ray, t1), cylinder->position), cylinder->orientation);
        if (height_pos >= 0 && height_pos <= cylinder->height && (caps_t == 0 || t1 < caps_t))
            return (*prev_t = t1, 1);
    }
    if (t2 > DBL_EPSILON && t2 < *prev_t)
    {
        height_pos = dot_product(subtract_v(get_intersection_point(ray, t2), cylinder->position), cylinder->orientation);
        if (height_pos >= 0 && height_pos <= cylinder->height && (caps_t == 0 || t2 < caps_t))
            return (*prev_t = t2, 1);
    }
	if (caps_t > DBL_EPSILON && caps_t < *prev_t)
		return (*prev_t = caps_t, 1);
    return (0);
}

int	is_intersect_plane(t_ray ray, t_plane *plane, double *prev_t)
{
	double	ND;
	double	t;

	ND = dot_product(plane->orientation, ray.direction);
	if (ND == 0)
		return (0);
	t = dot_product(multiply_v(plane->orientation, -1), subtract_v(ray.origin,
				plane->position)) / ND;
	if (t > 0 && *prev_t > t)
		return (*prev_t = t, 1);
	return (0);
}

int	is_intersect_sphere(t_ray ray, t_sphere *sphere, double *prev_t)
{
	t_vector	origin_to_center;
	float		a;
	float		b;
	float		c;
	float		disc;
	double		t1;
	double		t2;
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

int	render_object(t_ray ray, t_objects *object, t_scene scene, double *t)
{
	(void)scene;
	if (object->type == SPHERE)
	{
		if (is_intersect_sphere(ray, object->object, t) == 0)
			return (0x000000);
		return (phong_reflection((t_raytrace_info){get_intersection_point(ray, *t), get_normal_sphere_new(get_intersection_point(ray, *t), ray.origin, (t_sphere *)object->object), ray.direction,
				scene, color_to_vector(((t_sphere *)object->object)->color), object}));
	}
	else if (object->type == PLANE)
	{
		if (is_intersect_plane(ray, object->object, t) == 0)
			return (0x000000);
		return (phong_reflection((t_raytrace_info){get_intersection_point(ray,
					*t), get_normal_vector_plane(ray,
					*(t_plane *)object->object), ray.direction, scene,
				color_to_vector(((t_plane *)object->object)->color), object}));
	}
	else if (object->type == CYLINDER)
	{
		if (is_intersect_ray_cylinder(ray, object->object, t) == 0)
			return (0x000000);
		return (phong_reflection((t_raytrace_info){get_intersection_point(ray,
					*t), get_normal_vector_cylinder(get_intersection_point(ray, *t), (t_cylinder *)object->object),
				ray.direction, scene,
				color_to_vector(((t_cylinder *)object->object)->color), object}));
		// return (color_to_int(((t_cylinder *)object->object)->color));
	}
	return (0x000000);
}

int	trace_ray(t_ray ray, t_scene *scene)
{
	t_objects	*curr;
	int			color;
	int			result;
	double		t;

	t = DBL_MAX;
	curr = scene->objects;
	color = 0x000000;
	result = 0x000000;
	while (curr)
	{
		color = render_object(ray, curr, *scene, &t);
		if (color != 0x000000)
			result = color;
		curr = curr->next;
	}
	return (result);
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
