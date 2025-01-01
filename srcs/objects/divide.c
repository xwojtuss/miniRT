/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   divide.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wkornato <wkornato@student.42warsaw.pl>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/31 19:52:35 by wkornato          #+#    #+#             */
/*   Updated: 2025/01/01 16:16:11 by wkornato         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini_rt.h"

static void	copy_cone_to_plane(t_objects *src, t_objects *dest)
{
	copy_vector(&((t_plane *)dest->object)->position,
		((t_cone *)src->object)->position);
	copy_vector(&((t_plane *)dest->object)->orientation,
		((t_cone *)src->object)->orientation);
	copy_color(&((t_plane *)dest->object)->color,
		((t_cone *)src->object)->color);
	dest->constants.ambient = src->constants.ambient;
	dest->constants.diffuse = src->constants.diffuse;
	dest->constants.specular = src->constants.specular;
	dest->constants.shininess = src->constants.shininess;
	dest->texture = copy_texture(src->texture);
	dest->bump = copy_texture(src->bump);
	((t_plane *)dest->object)->diam = ((t_cone *)src->object)->diam
		- OFFSET_NORMAL;
}

void	add_base(t_scene *scene, t_objects *reference)
{
	t_objects	*new;
	t_objects	*last;

	new = (t_objects *)ft_calloc(1, sizeof(t_objects));
	if (!new)
		err_free("Could not allocate memory", scene);
	new->type = PLANE;
	new->object = new_plane(scene, new, (char *[]){"", "0,0,0", "0,0,0",
			"0,0,0"}, 4);
	copy_cone_to_plane(reference, new);
	last = get_last_object(scene->objects);
	if (!last)
		scene->objects = new;
	else
		last->next = new;
}

static void	copy_cyl_to_plane(t_objects *src, t_objects *dest)
{
	copy_vector(&((t_plane *)dest->object)->position,
		((t_cylinder *)src->object)->position);
	copy_vector(&((t_plane *)dest->object)->orientation,
		((t_cylinder *)src->object)->orientation);
	copy_color(&((t_plane *)dest->object)->color,
		((t_cylinder *)src->object)->color);
	dest->constants.ambient = src->constants.ambient;
	dest->constants.diffuse = src->constants.diffuse;
	dest->constants.specular = src->constants.specular;
	dest->constants.shininess = src->constants.shininess;
	dest->texture = copy_texture(src->texture);
	dest->bump = copy_texture(src->bump);
	((t_plane *)dest->object)->diam = ((t_cylinder *)src->object)->diam
		- OFFSET_NORMAL;
}

void	add_cap(t_scene *scene, t_objects *reference, bool is_top)
{
	t_objects	*new;
	t_objects	*last;
	t_plane		*new_pl;

	new = (t_objects *)ft_calloc(1, sizeof(t_objects));
	if (!new)
		err_free("Could not allocate memory", scene);
	new->type = PLANE;
	new->object = new_plane(scene, new, (char *[]){"", "0,0,0", "0,0,0",
			"0,0,0"}, 4);
	new_pl = new->object;
	copy_cyl_to_plane(reference, new);
	if (is_top)
		new_pl->position = add_v(new_pl->position,
				scale_v(((t_cylinder *)reference->object)->orientation,
					((t_cylinder *)reference->object)->height));
	last = get_last_object(scene->objects);
	if (!last)
		scene->objects = new;
	else
		last->next = new;
}

void	add_caps(t_scene *scene, char *type)
{
	t_objects	*last;

	last = get_last_object(scene->objects);
	if (!last)
		return ;
	if (!ft_strcmp(type, "cy"))
	{
		add_cap(scene, last, true);
		add_cap(scene, last, false);
	}
	else if (!ft_strcmp(type, "co"))
		add_base(scene, last);
}
