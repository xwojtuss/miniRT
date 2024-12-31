/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   misc.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wkornato <wkornato@student.42warsaw.pl>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/22 19:54:07 by wkornato          #+#    #+#             */
/*   Updated: 2024/12/31 21:53:04 by wkornato         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini_rt.h"

t_objects	*get_last_object(t_objects *objects)
{
	t_objects	*last;

	last = objects;
	if (!last)
		return (NULL);
	while (last->next)
		last = last->next;
	return (last);
}
