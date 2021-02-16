/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raytrace_cylinder.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ckurt <ckurt@student.42lyon.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/16 14:07:42 by ckurt             #+#    #+#             */
/*   Updated: 2021/02/16 15:19:24 by ckurt            ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minirt.h"

// bool	inter_cylinders(const t_ray ray, const t_cylinder cy, t_hit *hit)
// {
	
// }

// void	raytrace_cylinders(t_engine *engine, t_hit *hit, t_ray *ray)
// {
// 	t_list		*new;
// 	t_cylinder	*cy;

// 	new = engine->scene->cylinders;
// 	while (new)
// 	{
// 		cy = new->content;
// 		if (inter_cylinders(*ray, *cy, hit))
// 			hit->color = cy->color;
// 		new = new->next;
// 	}
// }