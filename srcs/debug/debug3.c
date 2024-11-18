/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   debug3.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wkornato <wkornato@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/24 19:17:24 by ukireyeu          #+#    #+#             */
/*   Updated: 2024/11/18 15:00:30 by wkornato         ###   ########.fr       */
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

void	show_depth(t_scene scene)
{
	int		delay;
	float	amount;
	int		x;

	delay = 10000;
	x = 1;
	amount = 0.02;
	while (true)
	{
		if (x == 1 || x == 4 || x == 5 || x == 8)
			scene.camera->position.z -= amount * 2;
		else
			scene.camera->position.z += amount * 2;
		if (x == 3 || x == 4 || x == 7 || x == 8)
			scene.camera->position.y -= amount;
		else
			scene.camera->position.y += amount;
		if (x == 3 || x == 4 || x == 5 || x == 6)
			scene.camera->position.x -= amount;
		else
			scene.camera->position.x += amount;
		initialize_viewport(&scene);
		render_scene(&scene);
		usleep(delay);
		x++;
		if (x == 9)
			x = 1;
	}
}
