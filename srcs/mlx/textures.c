/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   textures.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wkornato <wkornato@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/20 13:29:04 by wkornato          #+#    #+#             */
/*   Updated: 2024/12/20 14:37:44 by wkornato         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini_rt.h"

unsigned int get_pixel_color(t_image image, int x, int y)
{
	int offset;
	
	offset = (y * image.line_length) + (x * (image.bits_per_pixel / 8));
	return *(unsigned int *)(image.addr + offset);
}

void	assign_phong(t_objects *new, char **line, size_t start)
{
	if (new->type == PLANE)
	{
		((t_plane *)new->object)->ambient = ft_atof(line[start]);
		((t_plane *)new->object)->diffuse = ft_atof(line[start + 1]);
		((t_plane *)new->object)->specular = ft_atof(line[start + 2]);
		((t_plane *)new->object)->shininess = ft_atof(line[start + 3]);
	}
	else if (new->type == SPHERE)
	{
		((t_sphere *)new->object)->ambient = ft_atof(line[start]);
		((t_sphere *)new->object)->diffuse = ft_atof(line[start + 1]);
		((t_sphere *)new->object)->specular = ft_atof(line[start + 2]);
		((t_sphere *)new->object)->shininess = ft_atof(line[start + 3]);
	}
	else if (new->type == CYLINDER)
	{
		((t_cylinder *)new->object)->ambient = ft_atof(line[start]);
		((t_cylinder *)new->object)->diffuse = ft_atof(line[start + 1]);
		((t_cylinder *)new->object)->specular = ft_atof(line[start + 2]);
		((t_cylinder *)new->object)->shininess = ft_atof(line[start + 3]);
	}
}

t_texture	*new_texture(char *name)
{
	t_texture	*texture;

	texture = (t_texture *)ft_calloc(1, sizeof(t_texture));
	if (!texture)
		return (NULL);
	texture->height = 0;
	texture->width = 0;
	texture->name = ft_strdup(name);
	return (texture);
}
