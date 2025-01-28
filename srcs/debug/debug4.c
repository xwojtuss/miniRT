/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   debug4.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wkornato <wkornato@student.42warsaw.pl>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/28 10:36:08 by wkornato          #+#    #+#             */
/*   Updated: 2025/01/28 12:28:39 by wkornato         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini_rt.h"

t_objects	*debug_intersect(void)
{
	t_objects	*new;

	new = (t_objects *)ft_calloc(1, sizeof(t_objects));
	if (!new)
		return (NULL);
	new->bump = NULL;
	new->texture = NULL;
	new->next = NULL;
	new->type = INTER;
	new->object = NULL;
	return (new);
}
