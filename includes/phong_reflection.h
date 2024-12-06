#ifndef PHONG_REFLECTION_H
# define PHONG_REFLECTION_H

typedef struct s_raytrace_info
{
	t_vector	intersection_point;
	t_vector	normal_vector;
	t_vector	ray_direction;
	t_scene		scene;
	t_vector	color;
	t_objects	*object;
}				t_raytrace_info;

int				phong_reflection(t_raytrace_info info);

t_vector		get_normal_vector_cylinder(t_ray ray, t_cylinder *cylinder,
					float t);
t_vector		get_normal_vector_plane(t_ray ray, t_plane plane);
t_vector		get_normal_vector_sphere(t_vector intersection_point,
					t_vector center);

int				is_intersect_sphere(t_ray ray, t_sphere *sphere, float *prev_t);
int				is_intersect_plane(t_ray ray, t_plane *plane, float *prev_t);
int				is_intersect_ray_cylinder(t_ray ray, t_cylinder *cylinder,
					float *prev_t);

# define SPECULAR_CONST 1
# define DIFFUSE_CONST 0.6
# define AMBIENT_CONST 0.1
# define SHININESS_CONST 32

# define OFFSET 1e-6

#endif