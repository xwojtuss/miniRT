/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_intlen_d.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wkornato <wkornato@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/20 11:35:24 by wkornato          #+#    #+#             */
/*   Updated: 2024/08/20 11:35:54 by wkornato         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

// Function that returns the number of digits in an int, not counting the minus
int	ft_intlen_d(int n)
{
	int	len;

	len = 1;
	if (n < 0)
		n *= -1;
	while (n > 9)
	{
		len++;
		n /= 10;
	}
	return (len);
}
