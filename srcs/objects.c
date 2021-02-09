/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   objects.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ckurt <ckurt@student.42lyon.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/09 10:06:20 by ckurt             #+#    #+#             */
/*   Updated: 2021/02/09 10:49:45 by ckurt            ###   ########lyon.fr   */
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

void	get_scene(t_engine *engine)
{
	t_list	*list;
	int		i;

	list = NULL;
	i = 0;
	while (engine->file[i])
	{
		if (ft_startwith(engine->file[i], "sp"))
			add_sphere(&engine->scene->spheres, engine->file[i]);
	}
}