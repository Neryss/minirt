/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raytrace_disk.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ckurt <ckurt@student.42lyon.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/10 16:03:01 by ckurt             #+#    #+#             */
/*   Updated: 2021/02/10 16:18:20 by ckurt            ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minirt.h"

bool	inter_disk(const t_ray ray, const t_disk disk, t_hit *hit)
{
	double	denom;
	double	t;

	denom = scalar(disk.normal, ray.direction);
	if (fabs(denom) > EPSILON)
	{
		t = scalar(vectorminus(disk.origin, ray.origin), disk.normal) / denom;
		if (t < EPSILON || t > hit->dist)
			return (false);
		if (distance(vectoradd(ray.origin, vectormultiply(ray.direction, t)), disk.origin) > disk.diameter)
			return (false);
		hit->normal = disk.normal;
		hit->pos = vectoradd(ray.origin, vectormultiply(ray.direction, t));
		hit->dist = distance(ray.origin, hit->pos);
		return (true);
	}
	return (false);
}

void	raytrace_disk(t_engine *engine, t_hit *hit, t_ray *ray)
{
	t_list	*new;
	t_disk	*disk;

	new = engine->scene->disk;
	while (new)
	{
		disk = new->content;
		if (inter_disk(*ray, *disk, hit))
			hit->color = disk->rgb;
		new = new->next;
	}
}