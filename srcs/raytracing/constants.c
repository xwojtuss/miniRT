/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   constants.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wkornato <wkornato@student.42warsaw.pl>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/21 14:54:06 by wkornato          #+#    #+#             */
/*   Updated: 2024/12/21 15:19:32 by wkornato         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini_rt.h"
#include "phong_reflection.h"

float	get_diffuse(t_objects *object)
{
	if (object->type == PLANE)
		return (((t_plane *)object->object)->diffuse);
	else if (object->type == SPHERE)
		return (((t_sphere *)object->object)->diffuse);
	else if (object->type == CYLINDER)
		return (((t_cylinder *)object->object)->diffuse);
	return (0);
}

float	get_ambient(t_objects *object)
{
	if (object->type == PLANE)
		return (((t_plane *)object->object)->ambient);
	else if (object->type == SPHERE)
		return (((t_sphere *)object->object)->ambient);
	else if (object->type == CYLINDER)
		return (((t_cylinder *)object->object)->ambient);
	return (0);
}

float	get_specular(t_objects *object)
{
	if (object->type == PLANE)
		return (((t_plane *)object->object)->specular);
	else if (object->type == SPHERE)
		return (((t_sphere *)object->object)->specular);
	else if (object->type == CYLINDER)
		return (((t_cylinder *)object->object)->specular);
	return (0);
}

float	get_shininess(t_objects *object)
{
	if (object->type == PLANE)
		return (((t_plane *)object->object)->shininess);
	else if (object->type == SPHERE)
		return (((t_sphere *)object->object)->shininess);
	else if (object->type == CYLINDER)
		return (((t_cylinder *)object->object)->shininess);
	return (0);
}

void	assign_default_phong(t_objects *object)
{
	if (object->type == PLANE)
	{
		((t_plane *)object->object)->ambient = AMBIENT_CONST;
		((t_plane *)object->object)->diffuse = DIFFUSE_CONST;
		((t_plane *)object->object)->specular = SPECULAR_CONST;
		((t_plane *)object->object)->shininess = SHININESS_CONST;
	}
	else if (object->type == SPHERE)
	{
		((t_sphere *)object->object)->ambient = AMBIENT_CONST;
		((t_sphere *)object->object)->diffuse = DIFFUSE_CONST;
		((t_sphere *)object->object)->specular = SPECULAR_CONST;
		((t_sphere *)object->object)->shininess = SHININESS_CONST;
	}
	else if (object->type == CYLINDER)
	{
		((t_cylinder *)object->object)->ambient = AMBIENT_CONST;
		((t_cylinder *)object->object)->diffuse = DIFFUSE_CONST;
		((t_cylinder *)object->object)->specular = SPECULAR_CONST;
		((t_cylinder *)object->object)->shininess = SHININESS_CONST;
	}
}
