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

void	print_light_parameters(t_light *light)
{
	printf("Light:\n");
	printf("position:\tX%f, Y%f, Z%f\n", light->position.x, light->position.y,
			light->position.z);
	printf("brightness:\t%f\n", light->brightness);
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

void	print_ambient_parameters(t_ambient *ambient)
{
	printf("Ambient:\n");
	printf("color:\t\tR%i, G%i, B%i\n", ambient->color.r, ambient->color.g,
			ambient->color.b);
	printf("brightness:\t%f\n", ambient->brightness);
}

void	print_objects_parameters(t_scene *scene)
{
	t_objects *current;

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