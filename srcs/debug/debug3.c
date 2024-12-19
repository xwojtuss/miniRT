/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   debug3.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wkornato <wkornato@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/24 19:17:24 by ukireyeu          #+#    #+#             */
/*   Updated: 2024/12/19 20:45:11 by wkornato         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <mini_rt.h>

void	print_ambient_parameters(t_ambient *ambient)
{
	printf("Ambient:\n");
	printf("color:\t\tR%i, G%i, B%i\n", ambient->color.r, ambient->color.g,
		ambient->color.b);
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
