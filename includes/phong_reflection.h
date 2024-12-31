/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   phong_reflection.h                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wkornato <wkornato@student.42warsaw.pl>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/07 16:54:56 by wkornato          #+#    #+#             */
/*   Updated: 2024/12/31 20:42:42 by wkornato         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHONG_REFLECTION_H
# define PHONG_REFLECTION_H

# include "mini_rt.h"

typedef struct s_raytrace_info
{
	t_vector	inter;
	t_vector	normal_vector;
	t_ray		*ray;
	t_scene		*scene;
	t_vector	color;
	t_objects	*object;
	t_vector	tangent;
	t_vector	bitangent;
	double		u_val;
	double		v_val;
	double		t;
	double		ambient;
	double		diffuse;
	double		specular;
	double		shininess;
}				t_raytrace_info;

float			get_ambient(t_objects *object);
float			get_diffuse(t_objects *object);
float			get_specular(t_objects *object);
float			get_shininess(t_objects *object);

t_vector		get_color_plane(t_plane *plane, t_raytrace_info *raytrace);
t_vector		get_color_sphere(t_sphere *sphere, t_raytrace_info *raytrace);
t_vector		get_color_cylinder(t_cylinder *cylinder,
					t_raytrace_info *raytrace);
t_vector		get_color_cone(t_cone *cone, t_raytrace_info *raytrace);
void			recalculate_normal_vector(t_raytrace_info *raytrace);

int				phong_reflection(t_raytrace_info info);
t_objects		*get_closest_object(t_scene scene, t_ray ray, double *new_t);
t_vector		get_nv_plane(t_ray ray, t_plane *plane);
t_vector		get_normal_vector_sphere(t_vector inter, t_vector center);
t_vector		get_nv_sphere(t_vector inter, t_vector camera_pos,
					t_sphere *sphere);
t_vector		get_nv_cone(t_vector intersect, t_cone *cone, t_ray ray);

int				is_intersect_sphere(t_ray ray, t_sphere *sphere,
					double *prev_t);
int				is_intersect_plane(t_ray ray, t_plane *plane, double *prev_t);
int				is_intersect_ray_cylinder(t_ray ray, t_cylinder *cylinder,
					double *prev_t);
bool			is_intersect_cone(t_ray ray, t_cone *cone, double *t);
t_vector		get_nv_cylinder(t_vector intersect, t_cylinder *cylinder,
					t_ray ray);

# define SPECULAR_CONST 0.5
# define DIFFUSE_CONST 0.7
# define AMBIENT_CONST 0.3
# define SHININESS_CONST 2

#endif