/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cylinder.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wkornato <wkornato@student.42warsaw.pl>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/22 19:53:56 by wkornato          #+#    #+#             */
/*   Updated: 2024/12/31 11:34:17 by wkornato         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini_rt.h"
#include "phong_reflection.h"

void	check_cylinder_values(t_cylinder *cylinder, t_scene *scene, char **line)
{
	if (cylinder->orientation.x < -1 || cylinder->orientation.x > 1
		|| cylinder->orientation.y < -1 || cylinder->orientation.y > 1
		|| cylinder->orientation.z < -1 || cylinder->orientation.z > 1)
		err_free_array("Invalid orientation for plane", scene, line);
	if (cylinder->diam <= 0)
		err_free_array("Invalid diameter for cylinder", scene, line);
	if (cylinder->height <= 0)
		err_free_array("Invalid height for cylinder", scene, line);
	if (cylinder->color.r < 0 || cylinder->color.g < 0 || cylinder->color.b < 0)
		err_free_array("Color of cylinder is not correct", scene, line);
	if (cylinder->ambient < 0 || cylinder->diffuse < 0 || cylinder->specular < 0
		|| cylinder->shininess < 0 || cylinder->ambient > 1
		|| cylinder->diffuse > 1 || cylinder->specular > 1)
		err_free_array("Phong values for cylinder are not correct", scene,
			line);
}

void	assign_cylinder_values(void *object, char **temp, t_object_param type)
{
	if (type == POSITION)
		assign_vector(&((t_cylinder *)object)->position, ft_atof(temp[0]),
			ft_atof(temp[1]), ft_atof(temp[2]));
	else if (type == ORIENTATION)
		assign_vector(&((t_cylinder *)object)->orientation, ft_atof(temp[0]),
			ft_atof(temp[1]), ft_atof(temp[2]));
	else if (type == COLOR)
		assign_color(&((t_cylinder *)object)->color, ft_atoi(temp[0]),
			ft_atoi(temp[1]), ft_atoi(temp[2]));
}

t_texture	*copy_texture(t_texture *reference)
{
	t_texture	*new;

	if (!reference)
		return (NULL);
	new = (t_texture *)ft_calloc(1, sizeof(t_texture));
	if (!new)
		return (NULL);
	if (reference->name)
		new->name = ft_strdup(reference->name);
	else
		new->name = NULL;
	new->img = reference->img;
	new->width = reference->width;
	new->height = reference->height;
	return (new);
}

void	copy_vector(t_vector *dest, t_vector src)
{
	dest->x = src.x;
	dest->y = src.y;
	dest->z = src.z;
}

void	copy_color(t_color *dest, t_color src)
{
	dest->r = src.r;
	dest->g = src.g;
	dest->b = src.b;
}

void	add_cap(t_scene *scene, t_cylinder *cylinder, bool is_top)
{
	t_objects	*new;
	t_objects	*last;

	new = (t_objects *)ft_calloc(1, sizeof(t_objects));
	if (!new)
		err_free("Could not allocate memory", scene);
	new->type = PLANE;
	new->object = new_plane(scene, new, (char *[]){"", "0,0,0", "0,0,0",
			"0,0,0"}, 4);
	copy_vector(&((t_plane *)new->object)->position, cylinder->position);
	copy_vector(&((t_plane *)new->object)->orientation, cylinder->orientation);
	copy_color(&((t_plane *)new->object)->color, cylinder->color);
	((t_plane *)new->object)->ambient = cylinder->ambient;
	((t_plane *)new->object)->diffuse = cylinder->diffuse;
	((t_plane *)new->object)->specular = cylinder->specular;
	((t_plane *)new->object)->shininess = cylinder->shininess;
	((t_plane *)new->object)->diam = cylinder->diam;
	((t_plane *)new->object)->texture = copy_texture(cylinder->texture);
	((t_plane *)new->object)->bump = copy_texture(cylinder->bump);
	if (is_top)
		((t_plane *)new->object)->position = add_v(((t_plane *)new->object)->position,
			multiply_v(cylinder->orientation, cylinder->height));
	last = get_last_object(scene->objects);
	if (!last)
		scene->objects = new;
	else
		last->next = new;
}

t_cylinder	*new_cylinder(t_scene *scene, t_objects *new, char **line,
		size_t argc)
{
	t_cylinder	*cylinder;

	if (argc < 6 || argc > 12)
		err_free_array("Invalid number of arguments for cylinder", scene, line);
	cylinder = (t_cylinder *)ft_calloc(1, sizeof(t_cylinder));
	if (!cylinder)
		err_free_array("Could not allocate memory for cylinder", scene, line);
	new->object = cylinder;
	cylinder->diam = ft_atof(line[3]);
	cylinder->height = ft_atof(line[4]);
	cylinder->texture = NULL;
	if (argc > 6 && ft_strcmp(line[6], "-"))
		cylinder->texture = new_texture(line[6]);
	cylinder->bump = NULL;
	if (argc > 7 && ft_strcmp(line[7], "-"))
		cylinder->bump = new_texture(line[7]);
	if (argc == 12)
		assign_phong(new, line, 8);
	else
		assign_default_phong(new);
	return (cylinder);
}
