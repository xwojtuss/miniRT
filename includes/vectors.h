/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vectors.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wkornato <wkornato@student.42warsaw.pl>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/31 22:07:06 by wkornato          #+#    #+#             */
/*   Updated: 2024/12/31 22:31:06 by wkornato         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef VECTORS_H
# define VECTORS_H

typedef struct s_color
{
	int		r;
	int		g;
	int		b;
}			t_color;

typedef struct s_vector
{
	float	x;
	float	y;
	float	z;
}			t_vector;

//	SRCS
//		MATH
//			ANGLES.C

float		deg_to_rad(float deg);

//			VECTORS.C

t_vector	scale_v(t_vector vector, float multiplier);
t_vector	divide_v(t_vector vector, float divider);
t_vector	subtract_v(t_vector one, t_vector two);
t_vector	add_v(t_vector one, t_vector two);
float		dot_v(t_vector one, t_vector two);

//			VECTORS2.C

double		get_length_v(t_vector vector);
t_vector	normalize_v(t_vector vector);
void		assign_vector(t_vector *vector, float x, float y, float z);
void		assign_color(t_color *color, int r, int g, int b);

//			VECTORS3.C

t_vector	cross_product(t_vector one, t_vector two);
t_vector	scale_v_color(t_vector v1, t_vector v2);
t_vector	clamp_vector(t_vector vector, int min, int max);
t_vector	get_direction_v(t_vector from, t_vector to);
void		copy_vector(t_vector *dest, t_vector src);

//			COLORS.C

int			vector_to_int(t_vector vector);
t_vector	color_to_vector(t_color color);
t_vector	int_color_to_vector(int color);
void		copy_color(t_color *dest, t_color src);

#endif