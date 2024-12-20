#include "mini_rt.h"
#include "phong_reflection.h"

void	assign_default_phong(t_objects *object)
{
	if (object->type == PLANE)
	{
		((t_plane *)object->object)->ambient = AMBIENT_CONST;
		((t_plane *)object->object)->diffuse = DIFFUSE_CONST;
		((t_plane *)object->object)->specular = SPECULAR_CONST;
		((t_plane *)object->object)->shininess = SHININESS_CONST;
	}
	else if (object->type == SPHERE)
	{
		((t_sphere *)object->object)->ambient = AMBIENT_CONST;
		((t_sphere *)object->object)->diffuse = DIFFUSE_CONST;
		((t_sphere *)object->object)->specular = SPECULAR_CONST;
		((t_sphere *)object->object)->shininess = SHININESS_CONST;
	}
	else if (object->type == CYLINDER)
	{
		((t_cylinder *)object->object)->ambient = AMBIENT_CONST;
		((t_cylinder *)object->object)->diffuse = DIFFUSE_CONST;
		((t_cylinder *)object->object)->specular = SPECULAR_CONST;
		((t_cylinder *)object->object)->shininess = SHININESS_CONST;
	}
}
