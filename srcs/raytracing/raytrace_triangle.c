/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raytrace_triangle.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ckurt <ckurt@student.42lyon.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/15 12:21:54 by ckurt             #+#    #+#             */
/*   Updated: 2021/02/17 13:09:21 by ckurt            ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minirt.h"

static bool	edge_inter1(const t_triangle *tr, t_hit *tmp_hit)
{
	t_3dvector	edge;
	t_3dvector	vt;
	t_3dvector	vp;

	edge = vectorminus(tr->v2, tr->v1);
	vp = vectorminus(tmp_hit->pos, tr->v1);
	vt = vectorcross(edge, vp);
	if (scalar(tr->normal, vt) < 0)
		return (false);
	return (true);
}

static bool	edge_inter2(const t_triangle *tr, t_hit *tmp_hit)
{
	t_3dvector	edge;
	t_3dvector	vt;
	t_3dvector	vp;

	edge = vectorminus(tr->v3, tr->v2);
	vp = vectorminus(tmp_hit->pos, tr->v2);
	vt = vectorcross(edge, vp);
	if (scalar(tr->normal, vt) < 0)
		return (false);
	return (true);
}

static bool	edge_inter3(const t_triangle *tr, t_hit *tmp_hit)
{
	t_3dvector	edge;
	t_3dvector	vt;
	t_3dvector	vp;

	edge = vectorminus(tr->v1, tr->v3);
	vp = vectorminus(tmp_hit->pos, tr->v3);
	vt = vectorcross(edge, vp);
	if (scalar(tr->normal, vt) < 0)
		return (false);
	return (true);
}

bool	inter_triangles(const t_ray ray, const t_triangle tr, t_hit *hit)
{
	t_hit		tmp_hit;
	double		denom;
	double		t;

	denom = scalar(tr.normal, ray.direction);
	if (fabs(denom) < EPSILON)
		return (false);
	denom = scalar(tr.normal, tr.v1);
	t = ((-scalar(tr.normal, ray.origin) + denom)
			/ scalar(tr.normal, ray.direction));
	if (t < EPSILON || t > hit->dist)
		return (false);
	tmp_hit.normal = tr.normal;
	tmp_hit.pos = vectoradd(ray.origin, vectormultiply(ray.direction, t));
	tmp_hit.dist = distance(ray.origin, tmp_hit.pos);
	if (!edge_inter1(&tr, &tmp_hit) || !edge_inter2(&tr, &tmp_hit)
		|| !edge_inter3(&tr, &tmp_hit))
		return (false);
	hit->normal = tmp_hit.normal;
	hit->pos = tmp_hit.pos;
	hit->dist = tmp_hit.dist;
	return (true);
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
