/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   scene.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ckurt <ckurt@student.42lyon.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/15 10:46:46 by ckurt             #+#    #+#             */
/*   Updated: 2021/02/22 14:30:22 by ckurt            ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minirt.h"

void	add_light(t_list **lst, char *file)
{
	t_light	*light;
	t_list	*new;

	light = malloc(sizeof(t_light));
	if (!light)
		close_minirt("Error while parsing the scene(light)\n");
	light->pos = parse_vector(&file);
	light->intensity = ft_atof(file);
	printf("i : %f\n", light->intensity);
	if (!check_intensity(light->intensity))
		close_minirt("Error : light intensity out of bounds [0, 1]");
	file += ft_atof_len(file);
	light->color = ft_get_rgb(&file);
	new = ft_lstnew(light);
	if (!new)
		close_minirt("Error while parsing the scene(light)\n");
	ft_lstadd_back(lst, new);
}

void	add_camera(t_list **lst, char *line)
{
	t_camera	*camera;
	t_list		*new;
	static int	id;

	camera = malloc(sizeof(t_camera));
	if (!camera)
		close_minirt("Error while parsing the scene(camera)\n");
	camera->pos = parse_vector(&line);
	camera->rot = parse_vector(&line);
	if (!check_normal(camera->rot))
		close_minirt("Error : camera normal out of bounds [-1, 1]");
	camera->fov = ft_atof(line);
	if (!check_fov(camera->fov))
		close_minirt("Error : camera fov out of bounds [0, 180]");
	camera->id = id++;
	new = ft_lstnew(camera);
	if (!new)
		close_minirt("Error while parsing the scene(camera)\n");
	ft_lstadd_back(lst, new);
}

void	add_disk(t_list **lst, char *line)
{
	t_disk	*disk;
	t_list	*new;

	disk = malloc(sizeof(t_disk));
	if (!disk)
		close_minirt("Error while parsing the scene(disk)\n");
	disk->origin = parse_vector(&line);
	disk->normal = parse_vector(&line);
	if (!check_normal(disk->normal))
		close_minirt("Error : disk normal out of bounds [-1, 1]");
	disk->normal.x = to_rad(90 * disk->normal.x);
	disk->normal.y = to_rad(90 * disk->normal.y);
	disk->normal.z = to_rad(90 * disk->normal.z);
	normalize(&disk->normal);
	disk->diameter = ft_atof(line);
	line += ft_atof_len(line);
	disk->rgb = ft_get_rgb(&line);
	new = ft_lstnew(disk);
	if (!new)
		close_minirt("Error while parsing the scene(disk)\n");
	ft_lstadd_back(lst, new);
}

static void	add_alight(t_engine *engine, char *line)
{
	engine->scene->alight.intensity = ft_atof(line);
	if (!check_intensity(engine->scene->alight.intensity))
		close_minirt("Error : ambiant light intensity out of bounds [0, 1]");
	line += ft_atof_len(line);
	engine->scene->alight.color = ft_get_rgb(&line);
}

void	get_scene(t_engine *engine)
{
	int		i;

	i = 0;
	while (engine->file[i])
	{
		if (ft_startwith(engine->file[i], "sp"))
			add_sphere(&engine->scene->spheres, engine->file[i] + 2);
		if (ft_startwith(engine->file[i], "pl"))
			add_plane(&engine->scene->planes, engine->file[i] + 2);
		if (engine->file[i][0] == 'l')
			add_light(&engine->scene->lights, engine->file[i] + 1);
		if (engine->file[i][0] == 'c')
			add_camera(&engine->scene->cams, engine->file[i] + 1);
		if (engine->file[i][0] == 'A')
			add_alight(engine, engine->file[i] + 1);
		if (ft_startwith(engine->file[i], "ds"))
			add_disk(&engine->scene->disk, engine->file[i] + 2);
		if (ft_startwith(engine->file[i], "tr"))
			add_triangle(&engine->scene->triangles, engine->file[i] + 2);
		if (ft_startwith(engine->file[i], "cy"))
			add_cylinder(&engine->scene->cylinders, engine->file[i] + 2);
		i++;
	}
}
