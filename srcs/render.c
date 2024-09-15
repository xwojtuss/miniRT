/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wkornato <wkornato@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/20 15:57:43 by wkornato          #+#    #+#             */
/*   Updated: 2024/08/23 11:18:06 by wkornato         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini_rt.h"

void	render_scene(t_scene *scene)
{
	t_vector	one;
	t_vector	two;

	(void)scene;
	assign_vector(&one, 5, 0, 0);
	assign_vector(&two, 0, 5, 0);
	print_vector(one);
	print_vector(two);
	printf("theta: %f, theta in deg: %f, length one: %f, length two: %f, dot: %f\n",
		get_angle_between(one, two), rad_to_deg(get_angle_between(one, two)), vector_length(one), vector_length(two),
		dot_product(one, two));
	//get the rays from the camera
	//find a way to differenciate between the directions of the ray
	//check if the rays intersects with any objects
	//find the up of the plane of colision
	//find the bouces of the ray
}
