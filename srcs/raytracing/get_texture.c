/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_texture.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wkornato <wkornato@student.42warsaw.pl>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/21 14:59:40 by wkornato          #+#    #+#             */
/*   Updated: 2024/12/31 20:48:21 by wkornato         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini_rt.h"
#include "phong_reflection.h"

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
	if (!raytrace->object->texture)
		return (color_to_vector(plane->color));
	x = (int)(raytrace->u_val * raytrace->object->texture->width)
		% raytrace->object->texture->width;
	y = (int)(raytrace->v_val * raytrace->object->texture->height)
		% raytrace->object->texture->height;
	return (int_color_to_vector(get_pixel_color(raytrace->object->texture->img,
				x, y)));
}

t_vector	get_color_sphere(t_sphere *sphere, t_raytrace_info *raytrace)
{
	int	x;
	int	y;

	raytrace->u_val = 1.0 - (atan2(raytrace->normal_vector.z,
				raytrace->normal_vector.x) + PI) / PI;
	raytrace->v_val = acos(raytrace->normal_vector.y) / PI;
	if (raytrace->normal_vector.x == 1)
		raytrace->tangent = (t_vector){0, 1, 0};
	else
		raytrace->tangent = normalize_vector(cross_product((t_vector){1, 0, 0},
					raytrace->normal_vector));
	raytrace->bitangent = cross_product(raytrace->tangent,
			raytrace->normal_vector);
	if (!raytrace->object->texture)
		return (color_to_vector(sphere->color));
	x = (int)(raytrace->u_val * raytrace->object->texture->width)
		% raytrace->object->texture->width;
	y = (int)(raytrace->v_val * raytrace->object->texture->height)
		% raytrace->object->texture->height;
	if (x < 0)
		x += raytrace->object->texture->width;
	if (y < 0)
		y += raytrace->object->texture->height;
	return (int_color_to_vector(get_pixel_color(raytrace->object->texture->img,
				x, y)));
}

t_vector	get_color_cylinder(t_cylinder *cylinder, t_raytrace_info *raytrace)
{
	t_vector	p_local;

	p_local = subtract_v(raytrace->inter, cylinder->position);
	raytrace->v_val = 8 * dot_product(p_local, cylinder->orientation)
		/ cylinder->height;
	if (cylinder->orientation.x == 0 && cylinder->orientation.y == 0)
		raytrace->tangent = (t_vector){1, 0, 0};
	else
		raytrace->tangent = (t_vector){0, 0, 1};
	raytrace->tangent = normalize_vector(cross_product(cylinder->orientation,
				raytrace->tangent));
	raytrace->bitangent = cross_product(cylinder->orientation,
			raytrace->tangent);
	raytrace->u_val = 8 * (1.0 - atan2(dot_product(p_local,
					raytrace->bitangent), dot_product(p_local,
					raytrace->tangent)) / (PI * 2));
	if (raytrace->u_val < 0)
		raytrace->u_val += 1;
	if (raytrace->object->texture == NULL)
		return (color_to_vector(cylinder->color));
	return (int_color_to_vector(get_pixel_color(raytrace->object->texture->img,
				(int)(raytrace->u_val * raytrace->object->texture->height)
				% raytrace->object->texture->width, (int)(raytrace->v_val
					* raytrace->object->texture->width)
				% raytrace->object->texture->height)));
}

t_vector	get_color_cone(t_cone *cone, t_raytrace_info *raytrace)
{
	double	angle;
	double	height_proj;

	raytrace->tangent = normalize_vector(cross_product(cone->orientation,
				raytrace->normal_vector));
	raytrace->bitangent = normalize_vector(cross_product(raytrace->normal_vector,
				raytrace->tangent));
	height_proj = dot_product(subtract_v(raytrace->inter, cone->position),
			cone->orientation);
	angle = atan2(dot_product(raytrace->inter, raytrace->bitangent),
			dot_product(raytrace->inter, raytrace->tangent));
	raytrace->u_val = 8 * (1.0 - (angle + PI) / (2.0 * PI));
	raytrace->v_val = 8 * height_proj / cone->height;
	if (height_proj < 0 || height_proj > cone->height)
	{
		raytrace->u_val = 0;
		raytrace->v_val = 0;
	}
	if (raytrace->object->texture == NULL)
		return (color_to_vector(cone->color));
	return (int_color_to_vector(get_pixel_color(raytrace->object->texture->img,
				(int)(raytrace->u_val * raytrace->object->texture->width)
				% raytrace->object->texture->width, (int)(raytrace->v_val
					* raytrace->object->texture->height) % raytrace->object->texture->height)));
}

void	recalculate_normal_vector(t_raytrace_info *raytrace)
{
	int			x;
	int			y;
	t_texture	*bump;
	t_vector	p;

	bump = raytrace->object->bump;
	if (!bump)
		return ;
	x = (int)(raytrace->u_val * bump->width) % bump->width;
	y = (int)(raytrace->v_val * bump->height) % bump->height;
	p = int_color_to_vector(get_pixel_color(bump->img, x, y));
	p = subtract_v(multiply_v(divide_v(p, 255.0), 2.0), (t_vector){1.0, 1.0,
			1.0});
	raytrace->normal_vector = normalize_vector((t_vector){p.x
			* raytrace->tangent.x + p.y * raytrace->bitangent.x + p.z
			* raytrace->normal_vector.x, p.x * raytrace->tangent.y + p.y
			* raytrace->bitangent.y + p.z * raytrace->normal_vector.y, p.x
			* raytrace->tangent.z + p.y * raytrace->bitangent.z + p.z
			* raytrace->normal_vector.z});
}
