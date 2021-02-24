/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raytrace_square.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ckurt <ckurt@student.42lyon.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/24 20:03:19 by ckurt             #+#    #+#             */
/*   Updated: 2021/02/24 20:23:49 by ckurt            ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minirt.h"

double	get_proj(t_3dvector origin, t_3dvector v1, t_3dvector v2)
{
	t_3dvector	proj;
	t_3dvector	a;
	t_3dvector	b;

	a = vectorminus(v1, origin);
	b = vectorminus(v2, origin);
	proj = vectormultiply(a, scalar(b, a) / pow(magnitude(a), 2));
	return (fabs(distance(get_vector(0, 0, 0), proj)));
}

bool	check_edges(t_square sq, t_hit hit)
{
	t_3dvector	r0;
	t_3dvector	p;

	r0 = sq.normal;
	r0 = vectorcross(r0, get_vector(1, 0, 0));
	p = vectoradd(sq.pos, vectormultiply(r0, sq.size));
	if (get_proj(sq.pos, p, hit.pos) > sq.size)
		return (false);
	r0 = vectorcross(get_vector(0, 1, 0), r0);
	p = vectoradd(sq.pos, vectormultiply(r0, sq.size));
	if (get_proj(sq.pos, p, hit.pos) > sq.size)
		return (false);
	return (true);
}

bool	intersect_square(t_ray ray, t_square sq, t_hit *hit)
{
	double		denom;
	double		t;
	t_3dvector	p;
	t_hit		tmp_hit;

	denom = scalar(sq.normal, ray.direction);
	if (fabs(denom) <= EPSILON)
		return (false);
	t = scalar(vectorminus(sq.pos, ray.origin), sq.normal) / denom;
	p = vectoradd(ray.origin, vectormultiply(ray.direction, t));
	if (t < EPSILON || t > hit->dist)
		return (false);
	tmp_hit.pos = vectoradd(ray.origin, vectormultiply(ray.direction, t));
	if (!check_edges(sq, tmp_hit))
		return (false);
	hit->normal = sq.normal;
	hit->dist = t;
	hit->pos = vectoradd(ray.origin, vectormultiply(ray.direction, t));
	return (true);
}

void	raytrace_square(t_engine *engine, t_hit *hit, t_ray *ray)
{
	t_list		*new;
	t_square	*sq;

	new = engine->scene->squares;
	while (new)
	{
		sq = new->content;
		if (intersect_square(*ray, *sq, hit))
			hit->color = sq->color;
		new = new->next;
	}
}