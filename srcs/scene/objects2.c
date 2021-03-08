/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   objects2.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ckurt <ckurt@student.42lyon.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/16 14:12:58 by ckurt             #+#    #+#             */
/*   Updated: 2021/03/08 13:21:20 by ckurt            ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minirt.h"

bool	check_rot(t_3dvector rot)
{
	if (rot.x < -1 || rot.x > 1)
		return (false);
	if (rot.y < -1 || rot.x > 1)
		return (false);
	if (rot.z < -1 || rot.x > 1)
		return (false);
	return (true);
}

void	add_cylinder(t_list **lst, char *file)
{
	t_cylinder	*cy;
	t_list		*new;

	cy = malloc(sizeof(t_cylinder));
	if (!cy)
		close_minirt("Wile parsing the scene (cylinder)");
	cy->pos = parse_vector(&file);
	cy->rot = parse_vector(&file);
	if (!check_rot(cy->rot))
		close_minirt("Invalid rotation");
	cy->radius = ft_atof(file) / 2;
	file += ft_atof_len(file) + 1;
	cy->height = ft_atof(file);
	file += ft_atof_len(file) + 1;
	cy->color = ft_get_rgb(&file);
	new = ft_lstnew(cy);
	if (!new)
		close_minirt("Wile parsing the scene(cylinder)");
	ft_lstadd_back(lst, new);
}

void	add_square(t_list **lst, char *file)
{
	t_square	*sq;
	t_list		*new;

	sq = malloc(sizeof(t_square));
	if (!sq)
		close_minirt("While parsing the scene (square)");
	sq->pos = parse_vector(&file);
	sq->normal = parse_vector(&file);
	if (!check_normal(sq->normal))
		close_minirt("Normal out of bounds [-1, 1]");
	sq->normal.x = to_rad(90 * sq->normal.x);
	sq->normal.y = to_rad(90 * sq->normal.y);
	sq->normal.z = to_rad(90 * sq->normal.z);
	normalize(&sq->normal);
	sq->size = ft_atof(file) / 2;
	file += ft_atof_len(file);
	sq->color = ft_get_rgb(&file);
	new = ft_lstnew(sq);
	if (!new)
		close_minirt("While parsing the scene (square)");
	ft_lstadd_back(lst, new);
}
