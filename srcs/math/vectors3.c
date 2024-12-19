/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vectors3.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wkornato <wkornato@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/19 15:12:33 by wkornato          #+#    #+#             */
/*   Updated: 2024/12/19 17:29:18 by wkornato         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini_rt.h"

t_vector	cross_product(t_vector one, t_vector two)
{
	t_vector	result;

	result.x = one.y * two.z - one.z * two.y;
	result.y = one.z * two.x - one.x * two.z;
	result.z = one.x * two.y - one.y * two.x;
	return (result);
}

t_vector	multiply_v_color(t_vector v1, t_vector v2)
{
	t_vector	result;

	result.x = fmin(255.0f, v1.x * v2.x / 255.0f);
	result.y = fmin(255.0f, v1.y * v2.y / 255.0f);
	result.z = fmin(255.0f, v1.z * v2.z / 255.0f);
	return (result);
}
