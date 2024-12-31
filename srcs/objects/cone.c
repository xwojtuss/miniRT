/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cone.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wkornato <wkornato@student.42warsaw.pl>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/22 19:53:56 by wkornato          #+#    #+#             */
/*   Updated: 2024/12/31 16:51:04 by wkornato         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini_rt.h"
#include "phong_reflection.h"

void	check_cone_values(t_cone *cone, t_scene *scene, char **line)
{
	if (cone->orientation.x < -1 || cone->orientation.x > 1
		|| cone->orientation.y < -1 || cone->orientation.y > 1
		|| cone->orientation.z < -1 || cone->orientation.z > 1)
		err_free_array("Invalid orientation for cone", scene, line);
	if (cone->diam <= 0)
		err_free_array("Invalid diameter for cone", scene, line);
	if (cone->height <= 0)
		err_free_array("Invalid height for cone", scene, line);
	if (cone->color.r < 0 || cone->color.g < 0 || cone->color.b < 0)
		err_free_array("Color of cone is not correct", scene, line);
	if (cone->ambient < 0 || cone->diffuse < 0 || cone->specular < 0
		|| cone->shininess < 0 || cone->ambient > 1
		|| cone->diffuse > 1 || cone->specular > 1)
		err_free_array("Phong values for cone are not correct", scene,
			line);
}

void	assign_cone_values(void *object, char **temp, t_object_param type)
{
	if (type == POSITION)
		assign_vector(&((t_cone *)object)->position, ft_atof(temp[0]),
			ft_atof(temp[1]), ft_atof(temp[2]));
	else if (type == ORIENTATION)
		assign_vector(&((t_cone *)object)->orientation, ft_atof(temp[0]),
			ft_atof(temp[1]), ft_atof(temp[2]));
	else if (type == COLOR)
		assign_color(&((t_cone *)object)->color, ft_atoi(temp[0]),
			ft_atoi(temp[1]), ft_atoi(temp[2]));
}

void	add_base(t_scene *scene, t_cone *cone)
{
	t_objects	*new;
	t_objects	*last;

	new = (t_objects *)ft_calloc(1, sizeof(t_objects));
	if (!new)
		err_free("Could not allocate memory", scene);
	new->type = PLANE;
	new->object = new_plane(scene, new, (char *[]){"", "0,0,0", "0,0,0",
			"0,0,0"}, 4);
	copy_vector(&((t_plane *)new->object)->position, cone->position);
	copy_vector(&((t_plane *)new->object)->orientation, cone->orientation);
	copy_color(&((t_plane *)new->object)->color, cone->color);
	((t_plane *)new->object)->ambient = cone->ambient;
	((t_plane *)new->object)->diffuse = cone->diffuse;
	((t_plane *)new->object)->specular = cone->specular;
	((t_plane *)new->object)->shininess = cone->shininess;
	((t_plane *)new->object)->diam = cone->diam - OFFSET_NORMAL;
	((t_plane *)new->object)->texture = copy_texture(cone->texture);
	((t_plane *)new->object)->bump = copy_texture(cone->bump);
	last = get_last_object(scene->objects);
	if (!last)
		scene->objects = new;
	else
		last->next = new;
}

t_cone	*new_cone(t_scene *scene, t_objects *new, char **line,
		size_t argc)
{
	t_cone	*cone;

	if (argc < 6 || argc > 12)
		err_free_array("Invalid number of arguments for cone", scene, line);
	cone = (t_cone *)ft_calloc(1, sizeof(t_cone));
	if (!cone)
		err_free_array("Could not allocate memory for cone", scene, line);
	new->object = cone;
	cone->diam = ft_atof(line[3]);
	cone->height = ft_atof(line[4]);
	cone->texture = NULL;
	if (argc > 6 && ft_strcmp(line[6], "-"))
		cone->texture = new_texture(line[6]);
	cone->bump = NULL;
	if (argc > 7 && ft_strcmp(line[7], "-"))
		cone->bump = new_texture(line[7]);
	if (argc == 12)
		assign_phong(new, line, 8);
	else
		assign_default_phong(new, scene->ambient->brightness);
	return (cone);
}
