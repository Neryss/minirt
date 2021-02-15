/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raytrace_triangle.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ckurt <ckurt@student.42lyon.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/15 12:21:54 by ckurt             #+#    #+#             */
/*   Updated: 2021/02/15 14:37:37 by ckurt            ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minirt.h"

bool	inter_triangles(const t_ray ray, const t_triangle tr, t_hit *hit)
{
	t_3dvector	edge;
	t_3dvector	vt;
	t_3dvector	vp;
	double		denom;
	double		t;

	denom = scalar(tr.normal, ray.direction);
	if (fabs(denom) > EPSILON)
	{
		denom = scalar(tr.normal, tr.v1);
		t = ((scalar(tr.normal, ray.origin) + denom)
			/ scalar(tr.normal, ray.direction));
		if (t < 0)
			return (false);
		hit->normal = tr.normal;
		hit->pos = vectoradd(ray.origin, vectormultiply(ray.direction, t));
		hit->dist = distance(ray.origin, hit->pos);
		edge = vectorminus(tr.v2, tr.v1);
		vp = vectorminus(hit->pos, tr.v1);
		vt = vectorcross(edge, vp);
		if (scalar(tr.normal, vt) < 0)
			return (false);
		edge = vectorminus(tr.v3, tr.v2);
		vp = vectorminus(hit->pos, tr.v2);
		vt = vectorcross(edge, vp);
		if (scalar(tr.normal, vt) < 0)
			return (false);
		edge = vectorminus(tr.v1, tr.v3);
		vp = vectorminus(hit->pos, tr.v3);
		vt = vectorcross(edge, vp);
		if (scalar(tr.normal, vt) < 0)
			return (false);
		return (true);
	}
	return (false);
}

void	raytrace_triangles(t_engine *engine, t_hit *hit, t_ray *ray)
{
	t_list		*new;
	t_triangle	*tr;

	new = engine->scene->triangles;
	while (new)
	{
		tr = new->content;
		if (inter_triangles(*ray, *tr, hit))
			hit->color = tr->color;
		new = new->next;
	}
}
