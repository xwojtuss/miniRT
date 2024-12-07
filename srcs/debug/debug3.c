/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   debug3.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wkornato <wkornato@student.42warsaw.pl>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/24 19:17:24 by ukireyeu          #+#    #+#             */
/*   Updated: 2024/12/07 16:53:16 by wkornato         ###   ########.fr       */
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

void	print_objects_parameters(t_scene *scene)
{
	t_objects	*current;

	current = scene->objects;
	print_camera_parameters(scene->camera);
	print_ambient_parameters(scene->ambient);
	print_light_parameters(scene->light);
	while (current)
	{
		if (current->type == SPHERE)
			print_sphere_parameters(current->object);
		else if (current->type == PLANE)
			print_plane_parameters(current->object);
		else if (current->type == CYLINDER)
			print_cylinder_parameters(current->object);
		current = current->next;
	}
}
