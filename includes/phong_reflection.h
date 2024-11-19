#ifndef PHONG_REFLECTION_H
# define PHONG_REFLECTION_H

typedef struct s_raytrace_info
{
	t_vector	intersection_point;
	t_vector	normal_vector;
	t_vector	ray_direction;
	t_scene		scene;
	t_vector	color;
}				t_raytrace_info;

int				phong_reflection(t_raytrace_info info);

t_vector		get_normal_vector_cylinder(t_ray ray, t_cylinder *cylinder,
					float t);
t_vector		get_normal_vector_plane(t_ray ray, t_plane plane);
t_vector		get_normal_vector_sphere(t_vector intersection_point, t_vector center);

# define SPECULAR_CONST 1
# define DIFFUSE_CONST 0.6
# define AMBIENT_CONST 0.1
# define SHININESS_CONST 32

#endif