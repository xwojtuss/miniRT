/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   debug3.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wkornato <wkornato@student.42warsaw.pl>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/24 19:17:24 by ukireyeu          #+#    #+#             */
/*   Updated: 2025/01/01 19:42:19 by wkornato         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini_rt.h"

void	print_color(t_color color)
{
	printf("color:\t\t\x1b[38;2;%i;%i;%imR%i, G%i, B%i\x1b[0m\n", color.r,
		color.g, color.b, color.r, color.g, color.b);
}

void	print_light_parameters(t_lights *light)
{
	t_lights	*curr;

	curr = light;
	while (curr)
	{
		printf("Light:\n");
		printf("position:\tX%f, Y%f, Z%f\n", curr->position.x, curr->position.y,
			curr->position.z);
		print_color(curr->color);
		printf("brightness:\t%f\n", curr->brightness);
		curr = curr->next;
	}
}

void	print_ambient_parameters(t_ambient *ambient)
{
	printf("Ambient:\n");
	print_color(ambient->color);
	printf("brightness:\t%f\n", ambient->brightness);
}

void	print_object_parameters(t_objects *object)
{
	if (object->type == SPHERE)
		print_sphere_parameters(object->object);
	else if (object->type == PLANE)
		print_plane_parameters(object->object);
	else if (object->type == CYLINDER)
		print_cylinder_parameters(object->object);
	else if (object->type == CONE)
		print_cone_parameters(object->object);
	else if (object->type == LINE)
		print_line_parameters(object->object);
}

void	print_objects_parameters(t_scene *scene)
{
	t_objects	*current;

	current = scene->objects;
	print_camera_parameters(scene->camera);
	print_ambient_parameters(scene->ambient);
	print_light_parameters(scene->light);
	while (current)
	{
		print_object_parameters(current);
		current = current->next;
	}
}
