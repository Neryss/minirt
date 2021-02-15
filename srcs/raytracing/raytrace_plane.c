/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raytrace_plane.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ckurt <ckurt@student.42lyon.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/10 14:34:51 by ckurt             #+#    #+#             */
/*   Updated: 2021/02/15 12:19:24 by ckurt            ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minirt.h"

bool	inter_plane(const t_ray ray, const t_plane plane, t_hit *hit)
{
	double	denom;
	double	t;

	denom = scalar(plane.normal, ray.direction);
	if (fabs(denom) > EPSILON)
	{
		t = scalar(vectorminus(plane.origin, ray.origin), plane.normal) / denom;
		if (t < EPSILON || t > hit->dist)
			return (false);
		hit->normal = plane.normal;
		hit->pos = vectoradd(ray.origin, vectormultiply(ray.direction, t));
		hit->dist = distance(ray.origin, hit->pos);
		return (true);
	}
	return (false);
}

void	raytrace_planes(t_engine *engine, t_hit *hit, t_ray *ray)
{
	t_list	*new;
	t_plane	*plane;

	new = engine->scene->planes;
	while (new)
	{
		plane = new->content;
		if (inter_plane(*ray, *plane, hit))
			hit->color = plane->rgb;
		new = new->next;
	}
}
