#include "mini_rt.h"

void	print_sphere_parameters(t_sphere *sphere)
{
	printf("Sphere:\n");
	printf("color: R%i, G%i, B%i\n", sphere->color.r, sphere->color.g,
			sphere->color.b);
	printf("position: X%f, Y%f, Z%f\n", sphere->position.x, sphere->position.y,
			sphere->position.z);
	printf("diameter: %f\n", sphere->diam);
}

void	print_plane_parameters(t_plane *plane)
{
	printf("Plane:\n");
	printf("color: R%i, G%i, B%i\n", plane->color.r, plane->color.g,
			plane->color.b);
	printf("position: X%f, Y%f, Z%f\n", plane->position.x, plane->position.y,
			plane->position.z);
	printf("orientation: X%f, Y%f, Z%f\n", plane->orientation.x,
			plane->orientation.y, plane->orientation.z);
}

void	print_light_parameters(t_light *light)
{
	printf("Light:\n");
	printf("position: X%f, Y%f, Z%f\n", light->position.x, light->position.y,
			light->position.z);
	printf("brightness: %f\n", light->brightness);
}

void	print_cylinder_parameters(t_cylinder *cylinder)
{
	printf("Cylinder:\n");
	printf("color: R%i, G%i, B%i\n", cylinder->color.r, cylinder->color.g,
			cylinder->color.b);
	printf("position: X%f, Y%f, Z%f\n", cylinder->position.x,
			cylinder->position.y, cylinder->position.z);
	printf("orientation: X%f, Y%f, Z%f\n", cylinder->orientation.x,
			cylinder->orientation.y, cylinder->orientation.z);
	printf("diameter: %f\n", cylinder->diam);
	printf("height: %f\n", cylinder->height);
}

void	print_camera_parameters(t_camera *camera)
{
	printf("Camera:\n");
	printf("position: X%f, Y%f, Z%f\n", camera->position.x, camera->position.y,
			camera->position.z);
	printf("orientation: X%f, Y%f, Z%f\n", camera->orientation.x,
			camera->orientation.y, camera->orientation.z);
	printf("fov: %f\n", camera->fov);
}

void	print_ambient_parameters(t_ambient *ambient)
{
	printf("Ambient:\n");
	printf("color: R%i, G%i, B%i\n", ambient->color.r, ambient->color.g,
			ambient->color.b);
	printf("brightness: %f\n", ambient->brightness);
}

void	print_objects_parameters(t_objects *object)
{
	t_objects *current;

	current = object;
	while (current)
	{
		if (current->type == SPHERE)
			print_sphere_parameters(current->object);
		else if (current->type == PLANE)
			print_plane_parameters(current->object);
		else if (current->type == LIGHT)
			print_light_parameters(current->object);
		else if (current->type == CYLINDER)
			print_cylinder_parameters(current->object);
		else if (current->type == CAMERA)
			print_camera_parameters(current->object);
		else if (current->type == AMBIENT)
			print_ambient_parameters(current->object);
		current = current->next;
	}
}