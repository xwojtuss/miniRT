/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   debug2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wkornato <wkornato@student.42warsaw.pl>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/24 15:40:10 by wkornato          #+#    #+#             */
/*   Updated: 2024/12/07 16:53:04 by wkornato         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini_rt.h"

void	print_sphere_parameters(t_sphere *sphere)
{
	printf("Sphere:\n");
	printf("color:\t\tR%i, G%i, B%i\n", sphere->color.r, sphere->color.g,
		sphere->color.b);
	printf("position:\tX%f, Y%f, Z%f\n", sphere->position.x, sphere->position.y,
		sphere->position.z);
	printf("diameter:\t%f\n", sphere->diam);
}

void	print_plane_parameters(t_plane *plane)
{
	printf("Plane:\n");
	printf("color:\t\tR%i, G%i, B%i\n", plane->color.r, plane->color.g,
		plane->color.b);
	printf("position:\tX%f, Y%f, Z%f\n", plane->position.x, plane->position.y,
		plane->position.z);
	printf("orientation:\tX%f, Y%f, Z%f\n", plane->orientation.x,
		plane->orientation.y, plane->orientation.z);
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
		printf("brightness:\t%f\n", curr->brightness);
		curr = curr->next;
	}
}

void	print_cylinder_parameters(t_cylinder *cylinder)
{
	printf("Cylinder:\n");
	printf("color:\t\tR%i, G%i, B%i\n", cylinder->color.r, cylinder->color.g,
		cylinder->color.b);
	printf("position:\tX%f, Y%f, Z%f\n", cylinder->position.x,
		cylinder->position.y, cylinder->position.z);
	printf("orientation:\tX%f, Y%f, Z%f\n", cylinder->orientation.x,
		cylinder->orientation.y, cylinder->orientation.z);
	printf("diameter:\t%f\n", cylinder->diam);
	printf("height:\t\t%f\n", cylinder->height);
}

void	print_camera_parameters(t_camera *camera)
{
	printf("Camera:\n");
	printf("position:\tX%f, Y%f, Z%f\n", camera->position.x, camera->position.y,
		camera->position.z);
	printf("orientation:\tX%f, Y%f, Z%f\n", camera->orientation.x,
		camera->orientation.y, camera->orientation.z);
	printf("fov:\t\t%f\n", camera->fov);
}
