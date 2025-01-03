/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   phong_reflection.h                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wkornato <wkornato@student.42warsaw.pl>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/07 16:54:56 by wkornato          #+#    #+#             */
/*   Updated: 2024/12/31 22:20:22 by wkornato         ###   ########.fr       */
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

//	SRCS
//		RAYTRACING
//			PHONG.C

int						phong_reflection(t_raytrace_info info);

//			UV_TRANSLATE.C

t_vector				get_color_plane(t_plane *plane,
							t_raytrace_info *raytrace);

t_vector				get_color_sphere(t_sphere *sphere,
							t_raytrace_info *raytrace);
t_vector				get_color_cylinder(t_cylinder *cylinder,
							t_raytrace_info *raytrace);
t_vector				get_color_cone(t_cone *cone, t_raytrace_info *raytrace);
void					recalculate_normal_vector(t_raytrace_info *raytrace);

# define SPECULAR_CONST 0.5
# define DIFFUSE_CONST 0.7
# define AMBIENT_CONST 0.3
# define SHININESS_CONST 2

#endif