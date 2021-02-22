/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   operations2.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ckurt <ckurt@student.42lyon.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/10 12:43:18 by ckurt             #+#    #+#             */
/*   Updated: 2021/02/22 13:01:23 by ckurt            ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minirt.h"

double	distance(t_3dvector p1, t_3dvector p2)
{
	return (sqrt(pow(p2.x - p1.x, 2) + pow(p2.y - p1.y, 2)
			+ pow(p2.z - p1.z, 2)));
}

void	get_triangle_normal(t_triangle *triangle)
{
	t_3dvector	a;
	t_3dvector	b;

	a = vectorminus(triangle->v2, triangle->v1);
	b = vectorminus(triangle->v3, triangle->v1);
	triangle->normal = vectorcross(a, b);
	normalize(&triangle->normal);
}

float	magnitude(t_3dvector a)
{
	return (sqrt(pow(a.x, 2) + pow(a.y, 2) + pow(a.z, 2)));
}

t_3dvector	calculate_rot(t_3dvector *c2, t_3dvector *c3
, t_3dvector rot, t_3dvector to)
{
	t_3dvector	c1;
	t_3dvector	v;
	float		c;
	float		s;
	float		r;

	v = vectorcross(to, rot);
	c = scalar(rot, to);
	s = pow(magnitude(v), 2);
	r = ((1 - c) / s);
	c1 = get_vector(-r * (pow(v.y, 2) + pow(v.z, 2)) + 1, r * v.x
			* v.y - v.z, r * v.x * v.z + v.y);
	(*c2) = get_vector(r * v.x * v.y + v.z, -r * (pow(v.x, 2)
				+ pow(v.z, 2)) + 1, r * v.y * v.x - v.x);
	(*c3) = get_vector(r * v.x * v.z - v.y, r * v.y * v.z - v.x, -r
			* (pow(v.x, 2) + pow(v.y, 2)) + 1);
	return (c1);
}

t_3dvector	apply_rot(t_3dvector pos, t_3dvector dir, t_3dvector rot)
{
	t_3dvector	c1;
	t_3dvector	c2;
	t_3dvector	c3;
	t_3dvector	prev;

	if (dir.x == 0 && dir.y < 0 && dir.z == 0)
		pos = get_vector(pos.x, pos.y, -pos.z);
	else if (!(dir.x == 0 && dir.y != 0 && dir.z == 0))
	{
		prev = pos;
		c1 = calculate_rot(&c2, &c3, rot, dir);
		pos = get_vector(scalar(c1, prev), scalar(c2, prev), scalar(c3, prev));
	}
	return (pos);
}
