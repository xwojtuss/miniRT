/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_pow.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wkornato <wkornato@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/20 10:46:26 by wkornato          #+#    #+#             */
/*   Updated: 2024/08/20 11:26:47 by wkornato         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

long double	ft_pow(double x, int y)
{
	long double	res;

	res = 1;
	while (y > 0)
	{
		res *= x;
		y--;
	}
	while (y < 0)
	{
		res /= x;
		y++;
	}
	return (res);
}
