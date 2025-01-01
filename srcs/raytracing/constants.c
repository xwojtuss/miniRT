/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   constants.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wkornato <wkornato@student.42warsaw.pl>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/21 14:54:06 by wkornato          #+#    #+#             */
/*   Updated: 2025/01/01 18:51:46 by wkornato         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini_rt.h"
#include "phong_reflection.h"

void	assign_default_phong(t_objects *object)
{
	object->constants.ambient = AMBIENT_CONST;
	object->constants.diffuse = DIFFUSE_CONST;
	object->constants.specular = SPECULAR_CONST;
	object->constants.shininess = SHININESS_CONST;
}
