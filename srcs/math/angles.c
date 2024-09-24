/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   angles.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wkornato <wkornato@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/24 15:40:21 by wkornato          #+#    #+#             */
/*   Updated: 2024/09/24 15:40:22 by wkornato         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini_rt.h"

float	rad_to_deg(float rad)
{
	return (rad * 180 / PI);
}

float	deg_to_rad(float deg)
{
	return (deg * PI / 180);
}
