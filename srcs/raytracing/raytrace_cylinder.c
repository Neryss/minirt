/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raytrace_cylinder.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ckurt <ckurt@student.42lyon.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/16 14:07:42 by ckurt             #+#    #+#             */
/*   Updated: 2021/03/11 13:15:34 by ckurt            ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minirt.h"

typedef struct s_inf
{
	double		t;
	double		a;
	double		b;
	double		c;
	t_3dvector	p;
}				t_inf;

void	inf_cylinder_part2(t_inf inf, t_ray ray, t_cyresolve *res,
		t_cylinder cy)
{
	inf.t = (-inf.b + sqrt(pow(inf.b, 2) - 4 * inf.a * inf.c))
		/ (2 * inf.a);
	inf.p = vectoradd(ray.origin, vectormultiply(ray.direction, inf.t));
	inf.p = apply_rot(inf.p, cy.rot, get_vector(0, 1, 0));
	if (inf.t < res->tmin && inf.p.y >= res->b.y && inf.p.y <= res->t.y)
	{
		res->tmin = inf.t;
		inf.p = vectoradd(ray.origin, vectormultiply(ray.direction, inf.t));
		res->normal = calclanormalparceqttroplongue(cy, inf.p);
	}
}

void	infinite_cylinder(t_ray ray, t_cylinder cy, t_cyresolve *res)
{
	t_inf	inf;

	calc_things(&inf.a, &inf.b, ray, res);
	inf.c = calc_c(ray, cy, res->t, res->b);
	if (pow(inf.b, 2) - 4 * inf.a * inf.c > EPSILON)
	{
		inf.t = (-inf.b - sqrt(pow(inf.b, 2) - 4 * inf.a * inf.c))
			/ (2 * inf.a);
		if (inf.t < EPSILON)
			inf.t = (-inf.b + sqrt(pow(inf.b, 2) - 4 * inf.a * inf.c))
				/ (2 * inf.a);
		inf.p = vectoradd(ray.origin, vectormultiply(ray.direction, inf.t));
		inf.p = apply_rot(inf.p, cy.rot, get_vector(0, 1, 0));
		res->b = apply_rot(res->b, cy.rot, get_vector(0, 1, 0));
		res->t = apply_rot(res->t, cy.rot, get_vector(0, 1, 0));
		if (inf.t < res->tmin && inf.p.y >= res->b.y && inf.p.y <= res->t.y)
		{
			res->tmin = inf.t;
			inf.p = vectoradd(ray.origin, vectormultiply(ray.direction, inf.t));
			res->normal = calclanormalparceqttroplongue(cy, inf.p);
		}
		if (!CY_CAPS)
			inf_cylinder_part2(inf, ray, res, cy);
	}
}

void	check_caps(t_ray ray, t_cyresolve *res, t_cylinder cy)
{
	double		t;
	t_3dvector	pos;

	t = intersect_caps(ray, cy, res->t);
	pos = vectoradd(ray.origin, vectormultiply(ray.direction, t));
	if (t > EPSILON && distance(pos, res->t) < cy.radius)
	{
		res->tmin = t;
		res->normal = process_normal_cy(ray, cy.rot);
	}
	t = intersect_caps(ray, cy, res->b);
	pos = vectoradd(ray.origin, vectormultiply(ray.direction, t));
	if (t > EPSILON && t < res->tmin && distance(pos, res->b) < cy.radius)
	{
		res->tmin = t;
		res->normal = process_normal_cy(ray, cy.rot);
	}
}

bool	intersect_cylinder(t_ray ray, t_cylinder cy, t_hit *hit)
{
	t_cyresolve	res;

	if (cy.height < EPSILON || cy.radius < EPSILON)
		return (false);
	res.tmin = INFINITY;
	res.b = vectorminus(cy.pos, vectormultiply(cy.rot, cy.height / 2));
	res.t = vectoradd(cy.pos, vectormultiply(cy.rot, cy.height / 2));
	if (CY_CAPS)
		check_caps(ray, &res, cy);
	infinite_cylinder(ray, cy, &res);
	if (res.tmin < EPSILON || res.tmin == INFINITY || res.tmin > hit->dist)
		return (false);
	hit->dist = res.tmin;
	hit->pos = vectoradd(ray.origin, vectormultiply(ray.direction, res.tmin));
	hit->normal = get_normalized(res.normal);
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
