/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   phong_reflection.h                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wkornato <wkornato@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/07 16:54:56 by wkornato          #+#    #+#             */
/*   Updated: 2024/12/19 20:03:37 by wkornato         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHONG_REFLECTION_H
# define PHONG_REFLECTION_H

typedef struct s_raytrace_info
{
	t_vector	inter;
	t_vector	normal_vector;
	t_ray		*ray;
	t_scene		*scene;
	t_vector	color;
	t_objects	*object;
	double		t;
}				t_raytrace_info;

int				phong_reflection(t_raytrace_info info);
t_objects		*get_closest_object(t_scene scene, t_ray ray, double *new_t);
t_vector		get_normal_vector_plane(t_ray ray, t_plane plane);
t_vector		get_normal_vector_sphere(t_vector inter, t_vector center);
t_vector		get_normal_sphere_new(t_vector inter, t_vector camera_pos,
					t_sphere *sphere);

int				is_intersect_sphere(t_ray ray, t_sphere *sphere,
					double *prev_t);
int				is_intersect_plane(t_ray ray, t_plane *plane, double *prev_t);
int				is_intersect_ray_cylinder(t_ray ray, t_cylinder *cylinder,
					double *prev_t);
t_vector		get_normal_vector_cylinder_new(t_vector intersect,
					t_cylinder *cylinder);

# define SPECULAR_CONST 0.5
# define DIFFUSE_CONST 0.7
# define AMBIENT_CONST 0.3
# define SHININESS_CONST 2

#endif