/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   objects2.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ckurt <ckurt@student.42lyon.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/16 14:12:58 by ckurt             #+#    #+#             */
/*   Updated: 2021/02/22 15:59:30 by ckurt            ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minirt.h"

void	add_cylinder(t_list **lst, char *file)
{
	t_cylinder	*cy;
	t_list		*new;

	cy = malloc(sizeof(t_cylinder));
	if (!cy)
		close_minirt("Wile parsing the scene (cylinder)\n");
	cy->pos = parse_vector(&file);
	cy->rot = parse_vector(&file);
	cy->radius = ft_atof(file) / 2;
	file += ft_atof_len(file) + 1;
	cy->height = ft_atof(file);
	file += ft_atof_len(file) + 1;
	cy->color = ft_get_rgb(&file);
	new = ft_lstnew(cy);
	if (!new)
		close_minirt("Wile parsing the scene(cylinder)\n");
	ft_lstadd_back(lst, new);
}
