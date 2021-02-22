/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raytrace_cylinder.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ckurt <ckurt@student.42lyon.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/16 14:07:42 by ckurt             #+#    #+#             */
/*   Updated: 2021/02/22 12:59:19 by ckurt            ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minirt.h"

double	intersect_caps(t_ray ray, t_cylinder cy, t_3dvector pos)
{
	t_3dvector	tmp;
	double		a;
	double		b;
	double		t;

	t = 0;
	tmp = vectorminus(ray.origin, pos);
	a = scalar(tmp, cy.rot);
	b = scalar(ray.direction, cy.rot);
	if (!(b == 0 || (a < 0 && b < 0) || (a > 0 && b > 0)))
		t = -a / b;
	return (t);
}

double	calc_c(t_ray ray, t_cylinder cy, t_3dvector t, t_3dvector b)
{
	return (scalar(vectorcross(vectorminus(ray.origin, b), vectorminus(t, b)),
			vectorcross(vectorminus(ray.origin, b), vectorminus(t, b)))
		- (cy.radius * cy.radius * scalar(vectorminus(t, b),
					vectorminus(t, b))));
}

void	infinite_cylinder(t_ray ray, t_cylinder cy, t_resolve *res)
{
	double		t;
	double		a;
	double		b;
	double		c;
	t_3dvector	p;

	a = calc_a(ray, res);
	b = calc_b(ray, res);
	c = calc_c(ray, cy, res->t, res->b);
	if (pow(b, 2) - 4 * a * c > EPSILON)
	{
		t = (-b - sqrt(pow(b, 2) - 4 * a * c)) / (2 * a);
		if (t < EPSILON)
			t = (-b + sqrt(pow(b, 2) - 4 * a * c)) / (2 * a);
		p = vectoradd(ray.origin, vectormultiply(ray.direction, t));
		p = apply_rot(p, cy.rot, get_vector(0, 1, 0));
		res->b = apply_rot(res->b, cy.rot, get_vector(0, 1, 0));
		res->t = apply_rot(res->t, cy.rot, get_vector(0, 1, 0));
		if (t < res->tmin && p.y >= res->b.y && p.y <= res->t.y)
		{
			res->tmin = t;
			p = vectoradd(ray.origin, vectormultiply(ray.direction, t));
			res->normal = return_normal(p, cy);
		}
	}
}

bool	intersect_cylinder(t_ray ray, t_cylinder cy, t_hit *hit)
{
	double		t;
	t_3dvector	pos;
	t_resolve	res;

	if (cy.height < EPSILON || cy.radius < EPSILON)
		return (false);
	init_res(&res, cy);
	t = intersect_caps(ray, cy, res.t);
	pos = vectoradd(ray.origin, vectormultiply(ray.direction, t));
	if (t > EPSILON && distance(pos, res.t) < cy.radius)
		set_res(&res, t, ray, cy);
	t = intersect_caps(ray, cy, res.b);
	pos = vectoradd(ray.origin, vectormultiply(ray.direction, t));
	if (t > EPSILON && distance(pos, res.b) < cy.radius)
		set_res(&res, t, ray, cy);
	infinite_cylinder(ray, cy, &res);
	if (res.tmin < EPSILON || res.tmin == INFINITY || res.tmin > hit->dist)
		return (false);
	set_hit(hit, ray, res);
	return (true);
}

void	raytrace_cylinders(t_engine *engine, t_hit *hit, t_ray *ray)
{
	t_list		*new;
	t_cylinder	*cy;

	new = engine->scene->cylinders;
	while (new)
	{
		cy = new->content;
		if (intersect_cylinder(*ray, *cy, hit))
			hit->color = cy->color;
		new = new->next;
	}
}
