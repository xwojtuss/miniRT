/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   textures.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wkornato <wkornato@student.42warsaw.pl>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/20 13:29:04 by wkornato          #+#    #+#             */
/*   Updated: 2024/12/31 20:44:41 by wkornato         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini_rt.h"

unsigned int	get_pixel_color(t_image image, int x, int y)
{
	int	offset;

	offset = (y * image.line_length) + (x * (image.bits_per_pixel / 8));
	return (*(unsigned int *)(image.addr + offset));
}

void	assign_phong(t_objects *new, char **line, size_t start)
{
	new->constants.ambient = ft_atof(line[start]);
	new->constants.diffuse = ft_atof(line[start + 1]);
	new->constants.specular = ft_atof(line[start + 2]);
	new->constants.shininess = ft_atof(line[start + 3]);
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
