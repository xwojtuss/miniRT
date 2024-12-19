/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   find_t.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wkornato <wkornato@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/19 17:27:09 by wkornato          #+#    #+#             */
/*   Updated: 2024/12/19 17:27:10 by wkornato         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini_rt.h"

void	retrieve_t(double a, double b, double disc, double *ts[2])
{
	double	temp;
	double	sqrt_disc;

	if (disc < 0)
	{
		*ts[0] = DBL_MAX;
		*ts[1] = DBL_MAX;
		return ;
	}
	sqrt_disc = sqrt(disc);
	*ts[0] = (-b - sqrt_disc) / (2.0 * a);
	*ts[1] = (-b + sqrt_disc) / (2.0 * a);
	if (*ts[0] > *ts[1])
	{
		temp = *ts[0];
		*ts[0] = *ts[1];
		*ts[1] = temp;
	}
}
