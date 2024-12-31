/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wkornato <wkornato@student.42warsaw.pl>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/22 19:54:08 by wkornato          #+#    #+#             */
/*   Updated: 2024/12/31 21:33:33 by wkornato         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini_rt.h"

static t_objects	*add_object(t_scene *scene, t_object_type type, char **line)
{
	t_objects	*last;
	t_objects	*new;

	last = get_last_object(scene->objects);
	new = (t_objects *)ft_calloc(1, sizeof(t_objects));
	if (!new)
	{
		free_array(line);
		err_free("Could not allocate memory", scene);
	}
	new->type = type;
	if (!last)
		scene->objects = new;
	else
		last->next = new;
	return (new);
}

static void	split_and_assign_vector(t_objects *object, char *line,
		t_object_param type, t_scene *scene)
{
	char	**temp;
	float	orientation_multitude;

	temp = ft_split(line, ',');
	if (!temp || ft_arrlen(temp) != 3)
		err_free_array("Incorrect amount of parameters to a value", scene,
			temp);
	orientation_multitude = get_length_v((t_vector){ft_atof(temp[0]),
			ft_atof(temp[1]), ft_atof(temp[2])});
	if (type == ORIENTATION && (round(orientation_multitude) != 1
			|| 1 - orientation_multitude > 0.001
			|| 1 - orientation_multitude < -0.001))
		err_free_array("Orientation vector has to have a length of 1", scene,
			temp);
	if (object->type == SPHERE)
		assign_sphere_values(object->object, temp, type);
	else if (object->type == PLANE)
		assign_plane_values(object->object, temp, type);
	else if (object->type == CYLINDER)
		assign_cylinder_values(object->object, temp, type);
	else if (object->type == CONE)
		assign_cone_values(object->object, temp, type);
	free_array(temp);
}

static void	check_values(t_objects *object, t_object_type type, t_scene *scene,
		char **line)
{
	if (type == SPHERE)
		check_sphere_values((t_sphere *)object->object, scene, line);
	else if (type == PLANE)
		check_plane_values((t_plane *)object->object, scene, line);
	else if (type == CYLINDER)
		check_cylinder_values((t_cylinder *)object->object, scene, line);
	else if (type == CONE)
		check_cone_values((t_cone *)object->object, scene, line);
	if (object->constants.ambient < 0 || object->constants.diffuse < 0 || object->constants.specular < 0
		|| object->constants.shininess < 0 || object->constants.ambient > 1
		|| object->constants.diffuse > 1 || object->constants.specular > 1)
		err_free_array("Phong constants are not correct", scene,
			line);
}

void	parse_new_object(t_scene *scene, char **line, size_t argc,
		t_object_type type)
{
	t_objects	*new;

	new = add_object(scene, type, line);
	if (new->type == SPHERE)
		new->object = new_sphere(scene, new, line, argc);
	else if (new->type == PLANE)
		new->object = new_plane(scene, new, line, argc);
	else if (new->type == CYLINDER)
		new->object = new_cylinder(scene, new, line, argc);
	else if (new->type == CONE)
		new->object = new_cone(scene, new, line, argc);
	split_and_assign_vector(new, line[1], POSITION, scene);
	if (new->type == CYLINDER || new->type == CONE)
		split_and_assign_vector(new, line[5], COLOR, scene);
	else
		split_and_assign_vector(new, line[3], COLOR, scene);
	if (new->type == PLANE || new->type == CYLINDER || new->type == CONE)
		split_and_assign_vector(new, line[2], ORIENTATION, scene);
	check_values(new, new->type, scene, line);
}

int	parse_line(t_scene *scene, int fd)
{
	char	*line;
	char	**instructions;

	line = get_next_line(fd);
	if (!line || !*line)
		return (0);
	if (line[ft_strlen(line) - 1] == '\n')
		line[ft_strlen(line) - 1] = '\0';
	instructions = ft_split(line, ' ');
	free(line);
	if (!instructions)
	{
		close(fd);
		err_free("Could not split line", scene);
	}
	check_line(instructions, scene, fd);
	if (instructions && instructions[0])
		add_caps(scene, instructions[0]);
	free_array(instructions);
	return (1);
}
