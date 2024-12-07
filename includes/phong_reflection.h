/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   phong_reflection.h                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wkornato <wkornato@student.42warsaw.pl>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/07 16:54:56 by wkornato          #+#    #+#             */
/*   Updated: 2024/12/07 16:55:06 by wkornato         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

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

t_vector		get_normal_vector_cylinder(t_vector intersection_point,
					t_cylinder *cylinder);
t_vector		get_normal_vector_plane(t_ray ray, t_plane plane);
t_vector		get_normal_vector_sphere(t_vector intersection_point,
					t_vector center);
t_vector		get_normal_sphere_new(t_vector intersection_point,
					t_vector camera_pos, t_sphere *sphere);

int				is_intersect_sphere(t_ray ray, t_sphere *sphere,
					double *prev_t);
int				is_intersect_plane(t_ray ray, t_plane *plane, double *prev_t);
int				is_intersect_ray_cylinder(t_ray ray, t_cylinder *cylinder,
					double *prev_t);

# define SPECULAR_CONST 0.5
# define DIFFUSE_CONST 0.6
# define AMBIENT_CONST 1
# define SHININESS_CONST 10

# define OFFSET 1e-6

#endif