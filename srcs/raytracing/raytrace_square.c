/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raytrace_square.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ckurt <ckurt@student.42lyon.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/24 20:03:19 by ckurt             #+#    #+#             */
/*   Updated: 2021/03/03 13:06:16 by ckurt            ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minirt.h"

double	get_proj(t_3dvector origin, t_3dvector dir, t_3dvector pos)
{
	t_3dvector	relative_pos;

	relative_pos = vectorminus(pos, origin);
	return (fabs(scalar(dir, relative_pos)));
}

bool	check_edges(t_square sq, t_hit hit)
{
	t_3dvector	up;
	t_3dvector	right;

	if (sq.normal.x == 1 && sq.normal.y == 0 && sq.normal.z == 0)
		up = get_vector(0, 1, 0);
	else
		up = get_normalized(vectorcross(get_vector(1, 0, 0), sq.normal));
	if (get_proj(sq.pos, up, hit.pos) > sq.size)
		return (false);
	right = get_normalized(vectorcross(up, sq.normal));
	if (get_proj(sq.pos, right, hit.pos) > sq.size)
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
