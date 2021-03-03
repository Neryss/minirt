/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   scene.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ckurt <ckurt@student.42lyon.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/15 10:46:46 by ckurt             #+#    #+#             */
/*   Updated: 2021/03/03 13:04:53 by ckurt            ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minirt.h"

void	add_light(t_list **lst, char *file)
{
	t_light	*light;
	t_list	*new;

	light = malloc(sizeof(t_light));
	if (!light)
		close_minirt("While parsing the scene(light)\n");
	light->pos = parse_vector(&file);
	light->intensity = ft_atof(file);
	printf("i : %f\n", light->intensity);
	if (!check_intensity(light->intensity))
		close_minirt("Light intensity out of bounds [0, 1]");
	file += ft_atof_len(file);
	light->color = ft_get_rgb(&file);
	new = ft_lstnew(light);
	if (!new)
		close_minirt("While parsing the scene(light)\n");
	ft_lstadd_back(lst, new);
}

void	add_camera(t_list **lst, char *line)
{
	t_camera	*camera;
	t_list		*new;
	static int	id;

	camera = malloc(sizeof(t_camera));
	if (!camera)
		close_minirt("While parsing the scene(camera)\n");
	camera->pos = parse_vector(&line);
	camera->rot = parse_vector(&line);
	if (!check_normal(camera->rot))
		close_minirt("Camera normal out of bounds [-1, 1]");
	camera->fov = ft_atof(line);
	if (!check_fov(camera->fov))
		close_minirt("Camera fov out of bounds [0, 180]");
	camera->id = id++;
	new = ft_lstnew(camera);
	if (!new)
		close_minirt("While parsing the scene(camera)\n");
	ft_lstadd_back(lst, new);
}

void	add_alight(t_engine *engine, char *line)
{
	engine->scene->alight.intensity = ft_atof(line);
	if (!check_intensity(engine->scene->alight.intensity))
		close_minirt("Ambiant light intensity out of bounds [0, 1]");
	line += ft_atof_len(line);
	engine->scene->alight.color = ft_get_rgb(&line);
}

void	get_scene(t_engine *engine)
{
	int		i;

	i = 0;
	while (engine->file[i])
	{
		if (check_lines(engine, i) || check_uniq(engine->file[i]))
			;
		else
			close_minirt(ft_strjoin("Bad file formating at : \n"
				, engine->file[i]));
		i++;
	}
}
