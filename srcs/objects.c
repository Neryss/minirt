/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   objects.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ckurt <ckurt@student.42lyon.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/09 10:06:20 by ckurt             #+#    #+#             */
/*   Updated: 2021/02/15 12:57:57 by ckurt            ###   ########lyon.fr   */
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
	sphere->diameter = ft_atof(file) / 2;
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
	plane->normal.x = to_rad(90 * plane->normal.x);
	plane->normal.y = to_rad(90 * plane->normal.y);
	plane->normal.z = to_rad(90 * plane->normal.z);
	normalize(&plane->normal);
	plane->rgb = ft_get_rgb(&file);
	new = ft_lstnew(plane);
	if (!new)
		close_minirt("Error while parsing the scene\n");
	ft_lstadd_back(lst, new);
}

void	add_triangle(t_list **lst, char *file)
{
	t_triangle	*triangle;
	t_list		*new;

	triangle = malloc(sizeof(t_triangle));
	if (!triangle)
		close_minirt("Error while parsing the scene (triangle)\n");
	triangle->v1 = parse_vector(&file);
	triangle->v2 = parse_vector(&file);
	triangle->v3 = parse_vector(&file);
	triangle->color = ft_get_rgb(&file);
	get_triangle_normal(triangle);
	new = ft_lstnew(triangle);
	if (!new)
		close_minirt("Error while parsing the scene (triangle)\n");
	ft_lstadd_back(lst, new);
}

t_light	*create_light(t_3dvector pos, double intensity, t_rgb color)
{
	t_light	*light;

	light = malloc(sizeof(t_light));
	if (!light)
		close_minirt("Error during light malloc\n");
	light->pos = pos;
	light->intensity = intensity;
	light->color = color;
	return (light);
}

t_ray	*create_ray(t_3dvector pos, t_3dvector dir)
{
	t_ray	*ray;

	ray = malloc(sizeof(t_ray));
	if (!ray)
		close_minirt("Error during ray malloc\n");
	ray->origin = pos;
	ray->direction = get_normalized(dir);
	return (ray);
}
