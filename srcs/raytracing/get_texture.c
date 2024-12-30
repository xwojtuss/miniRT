/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_texture.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wkornato <wkornato@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/21 14:59:40 by wkornato          #+#    #+#             */
/*   Updated: 2024/12/30 04:54:06 by wkornato         ###   ########.fr       */
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
	if (!plane->texture)
		return (color_to_vector(plane->color));
	x = (int)(raytrace->u_val * plane->texture->width) % plane->texture->width;
	y = (int)(raytrace->v_val * plane->texture->height)
		% plane->texture->height;
	return (int_color_to_vector(get_pixel_color(plane->texture->img, x, y)));
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

	p_local = subtract_v(raytrace->inter, cylinder->position);
	raytrace->v_val = dot_product(p_local, cylinder->orientation)
		/ cylinder->height;
	if (cylinder->orientation.x == 0 && cylinder->orientation.y == 0)
		raytrace->tangent = (t_vector){1, 0, 0};
	else
		raytrace->tangent = (t_vector){0, 0, 1};
	raytrace->tangent = normalize_vector(cross_product(cylinder->orientation,
				raytrace->tangent));
	raytrace->bitangent = cross_product(cylinder->orientation,
			raytrace->tangent);
	raytrace->u_val = 1.0 - atan2(dot_product(p_local, raytrace->bitangent),
			dot_product(p_local, raytrace->tangent)) / (PI * 2);
	if (raytrace->u_val < 0)
		raytrace->u_val += 1;
	if (cylinder->texture == NULL)
		return (color_to_vector(cylinder->color));
	return (int_color_to_vector(get_pixel_color(cylinder->texture->img,
				(int)(raytrace->u_val * cylinder->texture->width)
			% cylinder->texture->width, (int)(raytrace->v_val
			* cylinder->texture->height) % cylinder->texture->height)));
}

void	recalculate_normal_vector(t_raytrace_info *raytrace)
{
	int			x;
	int			y;
	t_texture	*bump;
	t_vector	p;

	bump = NULL;
	if (raytrace->object->type == PLANE)
		bump = ((t_plane *)raytrace->object->object)->bump;
	else if (raytrace->object->type == SPHERE)
		bump = ((t_sphere *)raytrace->object->object)->bump;
	else if (raytrace->object->type == CYLINDER)
		bump = ((t_cylinder *)raytrace->object->object)->bump;
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
