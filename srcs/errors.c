/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   errors.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wkornato <wkornato@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/22 19:54:02 by wkornato          #+#    #+#             */
/*   Updated: 2024/08/22 19:54:03 by wkornato         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini_rt.h"

void	err(char *message)
{
	ft_putstr_fd("Error\n", STDERR_FILENO);
	ft_putstr_fd(message, STDERR_FILENO);
	ft_putstr_fd("\n", STDERR_FILENO);
	exit(EXIT_FAILURE);
}

void	err_free(char *message, t_scene *scene)
{
	ft_putstr_fd("Error\n", STDERR_FILENO);
	ft_putstr_fd(message, STDERR_FILENO);
	ft_putstr_fd("\n", STDERR_FILENO);
	free_scene(scene);
	exit(EXIT_FAILURE);
}

void	err_free_fd(char *message, t_scene *scene, int fd)
{
	ft_putstr_fd("Error\n", STDERR_FILENO);
	ft_putstr_fd(message, STDERR_FILENO);
	ft_putstr_fd("\n", STDERR_FILENO);
	free_scene(scene);
	close(fd);
	exit(EXIT_FAILURE);
}

void	err_free_array(char *message, t_scene *scene, char **array)
{
	ft_putstr_fd("Error\n", STDERR_FILENO);
	ft_putstr_fd(message, STDERR_FILENO);
	ft_putstr_fd("\n", STDERR_FILENO);
	free_array(array);
	free_scene(scene);
	exit(EXIT_FAILURE);
}