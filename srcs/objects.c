/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   objects.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ckurt <ckurt@student.42lyon.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/09 10:06:20 by ckurt             #+#    #+#             */
/*   Updated: 2021/02/09 16:11:06 by ckurt            ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minirt.h"

void	add_sphere(t_list **lst, char *file)
{
	t_sphere	*sphere;
	t_list		*new;

	sphere = malloc(sizeof(t_sphere));
	if (!sphere)
		close_minirt("Error while parsing the scene\n");
	sphere->pos = parse_vector(&file);
	sphere->r = ft_atof(file);
	file += ft_atof_len(file);
	sphere->rgb = ft_get_rgb(&file);
	new = ft_lstnew(sphere);
	if (!new)
		close_minirt("Error while parsing the scene\n");
	ft_lstadd_back(lst, new);
}

void	add_plane(t_list **lst, char *file)
{
	t_plane	*plane;
	t_list	*new;

	plane = malloc(sizeof(t_plane));
	if (!plane)
		close_minirt("Error while parsing the scene\n");
	plane->origin = parse_vector(&file);
	plane->normal = parse_vector(&file);
	plane->normal = vectormultiply(plane->normal, 90 * M_PI);
	plane->normal = vectordivide(plane->normal, 180);
	plane->rgb = ft_get_rgb(&file);
	new = ft_lstnew(plane);
	if (!new)
		close_minirt("Error while parsing the scene\n");
	ft_lstadd_back(lst, new);
}

void	add_light(t_list **lst, char *file)
{
	t_light	*light;
	t_list	*new;

	light = malloc(sizeof(t_light));
	if (!light)
		close_minirt("Error while parsing the scene\n");
	light->pos = parse_vector(&file);
	light->intensity = ft_atof(file);
	file += ft_atof_len(file);
	light->color = ft_get_rgb(&file);
	new = ft_lstnew(light);
	if (!new)
		close_minirt("Error while parsing the scene\n");
	ft_lstadd_back(lst, new);
}

void	add_camera(t_list **lst, char *line)
{
	t_camera	*camera;
	t_list		*new;
	static int	id;

	camera = malloc(sizeof(t_camera));
	if (!camera)
		close_minirt("Error while parsing the scene\n");
	camera->pos = parse_vector(&line);
	// line += ft_atof_len(line);
	camera->rot = parse_vector(&line);
	camera->fov = ft_atof(line) * M_PI / 180;
	camera->id = id++;
	new = ft_lstnew(camera);
	if (!new)
		close_minirt("Error while parsing the scene\n");
	ft_lstadd_back(lst, new);
}

void	get_scene(t_engine *engine)
{
	t_list	*list;
	int		i;

	list = NULL;
	i = 0;
	while (engine->file[i])
	{
		printf("yo\n");
		if (ft_startwith(engine->file[i], "sp"))
			add_sphere(&engine->scene->spheres, engine->file[i]);
		if (ft_startwith(engine->file[i], "pl"))
			add_plane(&engine->scene->planes, engine->file[i]);
		if (engine->file[i][0] == 'l')
			add_light(&engine->scene->lights, engine->file[i]);
		if (engine->file[i][0] == 'c')
			add_camera(&engine->scene->cams, engine->file[i]);
		i++;
	}
}

t_light	*create_light(t_3dvector pos, double intensity, t_rgb color)
{
	t_light	*light;

	if (!(light = malloc(sizeof(t_light))))
		return (NULL);
	light->pos = pos;
	light->intensity = intensity;
	light->color = color;
	return (light);
}

t_ray			*create_ray(t_3dvector pos, t_3dvector dir)
{
	t_ray		*ray;

	if (!(ray = malloc(sizeof(t_ray))))
		return (NULL);
	ray->origin = pos;
	ray->direction = dir;
	return (ray);
}
