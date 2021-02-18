/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raytrace_cylinder.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ckurt <ckurt@student.42lyon.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/16 14:07:42 by ckurt             #+#    #+#             */
/*   Updated: 2021/02/18 14:54:55 by ckurt            ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minirt.h"

// bool	inter_base(const t_ray ray, const t_cylinder cy, t_hit *hit)
// {
// 	t_3dvector	normal;
// 	double		a;
// 	double		b;
// 	double		c;
// 	double		d;

// 	normal = cy_normal(hit, cy);
// 	a = normal.x;
// 	b = normal.y;
// 	c = normal.z;
// 	d = - (a * (cy.pos.x))
// }

// produit vectoriel rotation,

t_3dvector	cy_normal(t_hit *hit, const t_cylinder cy)
{
	t_3dvector	c0;
	t_3dvector	v;

	if (hit->pos.x < cy.pos.x + cy.radius && hit->pos.x > cy.pos.x - cy.radius
		&& hit->pos.z < cy.pos.z + cy.radius && hit->pos.z > cy.pos.z - cy.radius)
	{
		if (hit->pos.y < cy.pos.y + cy.height + EPSILON
			&& hit->pos.y > cy.pos.y + cy.height - EPSILON)
			return (get_vector(0, 1, 0));
		if (hit->pos.y < cy.pos.y + EPSILON && hit->pos.y > cy.pos.y - EPSILON)
			return (get_vector(0, -1, 0));
	}
	c0 = get_vector(cy.pos.x, hit->pos.y, cy.pos.z);
	v = vectorminus(hit->pos, c0);
	normalize(&v);
	return (v);
}

t_3dvector	process_normal(t_ray ray, t_3dvector normal)
{
	float		res;
	t_3dvector	tmp;

	res = scalar(ray.direction, normal);
	if (res < 0)
		return (normal);
	tmp = vectormultiply(normal, -1);
	return (tmp);
}

bool	test_inter(const t_cylinder cy, const t_ray ray, t_hit *hit)
{
	t_3dvector	pdp;
	t_3dvector	eyepdp;
	t_3dvector	rdxpdp;
	double		a;
	double		b;
	double		c;
	double		delta;
	double		t;
	double		t1;

	pdp = vectorminus(cy.rot, cy.pos);
	eyepdp = vectorcross(vectorminus(ray.origin, cy.pos), pdp);
	rdxpdp = vectorcross(ray.direction, pdp);
	a = scalar(rdxpdp, rdxpdp);
	b = 2 * scalar(rdxpdp, eyepdp);
	c = scalar(eyepdp, eyepdp) - (cy.radius * cy.radius * scalar(pdp, pdp));
	delta = sqrt((b * b) - (4 * a * c));
	if (delta < 0)
		return (false);
	t = (-b - (delta)) / (2.0 * a);
	t1 = (-b + (delta)) / (2.0 * a);
	if (t <= EPSILON|| t > hit->dist)
		return (false);
	hit->dist = ft_dmin(t, t1);
	hit->pos = vectoradd(ray.origin, vectormultiply(ray.direction, t));
	hit->normal = cy_normal(hit, cy);
	return (true);
}

bool	inter_cylinders(const t_ray ray, const t_cylinder cy, t_hit *hit)
{
	t_3dvector	p0;
	double		a;
	double		b;
	double		c;
	double		delta;
	double		t;

	p0 = get_vector(ray.origin.x - cy.pos.x,
			ray.origin.y - cy.pos.y, ray.origin.z - cy.pos.z);
	a = ray.direction.x * ray.direction.x + ray.direction.z * ray.direction.z;
	b = ray.direction.x * p0.x + ray.direction.z * p0.z;
	c = p0.x * p0.x + p0.z * p0.z - cy.radius * cy.radius;
	delta = b * b - a * c;
	if (delta < EPSILON)
		return (false);
	t = (-b - sqrt(delta)) / a;
	if (t <= EPSILON || t > hit->dist)
		return (false);
	hit->pos = vectoradd(ray.origin, vectormultiply(ray.direction, t));
	hit->dist = t;
	hit->normal = cy_normal(hit, cy);
	return (true);
}

float	calc_c(t_ray ra, t_cylinder *cy, t_3dvector g_b, t_3dvector g_t)
{
	return (scalar(vectorcross(vectorminus(ra.origin, g_b), vectorminus(g_t, g_b)), \
		vectorcross(vectorminus(ra.origin, g_b), vectorminus(g_t, g_b))) - \
		((cy->radius) * (cy->radius) * scalar(vectorminus(g_t, g_b), \
		vectorminus(g_t, g_b))));
}

float	intersect_caps(t_ray ra, t_cylinder *cy, t_3dvector pos)
{
	t_3dvector	tmp;
	float		a;
	float		b;
	float		t0;

	t0 = 0;
	tmp = vectorminus(ra.origin, pos);
	a = scalar(tmp, cy->rot);
	b = scalar(ra.direction, cy->rot);
	if (!(b == 0 || (a < 0 && b < 0) || (a > 0 && b > 0)))
		t0 = -a / b;
	return (t0);
}

float	magnitude(t_3dvector a)
{
	return (sqrt(pow(a.x, 2) + pow(a.y, 2) + pow(a.z, 2)));
}

t_3dvector	calculate_rot(t_3dvector *c2, t_3dvector *c3, t_3dvector rot, t_3dvector to)
{
	t_3dvector	c1;
	t_3dvector	v;
	float	c;
	float	s;
	float	r;

	v = vectorcross(to, rot);
	c = scalar(rot, to);
	s = pow(magnitude(v), 2);
	r = ((1 - c) / s);
	c1 = get_vector(-r * (pow(v.y, 2) + pow(v.z, 2)) + 1, r * v.x * \
				v.y - v.z, r * v.x * v.z + v.y);
	(*c2) = get_vector(r * v.x * v.y + v.z, -r * (pow(v.x, 2) + \
					pow(v.z, 2)) + 1, r * v.y * v.x - v.x);
	(*c3) = get_vector(r * v.x * v.z - v.y, r * v.y * v.z - v.x, -r * \
					(pow(v.x, 2) + pow(v.y, 2)) + 1);
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

void	infinite_cy(t_ray ra, t_cylinder *cy, t_3dvector *g_t, t_3dvector *g_b, double g_t_min)
{
	float		t0;
	t_3dvector	p;
	t_3dvector	normal;
	float		a;
	float		b;
	float		c;

	a = scalar(vectorcross(ra.direction, vectorminus(*g_t, *g_b)), vectorcross(ra.direction, vectorminus(*g_t, *g_b)));
	b = 2 * scalar(vectorcross(ra.direction, vectorminus(*g_t, *g_b)), vectorcross(vectorminus(ra.origin, *g_b), \
				vectorminus(*g_t, *g_b)));
	c = calc_c(ra, cy, *g_b, *g_t);
	if (pow(b, 2) - 4 * a * c > 0)
	{
		t0 = (-b - sqrt(pow(b, 2) - 4 * a * c)) / (2 * a);
		if (t0 < 0)
			t0 = (-b + sqrt(pow(b, 2) - 4 * a * c)) / (2 * a);
		p = vectoradd(ra.origin, vectormultiply(ra.direction, t0));
		p = apply_rot(p, cy->rot, get_vector(0, 1, 0));
		*g_b = apply_rot(*g_b, cy->rot, get_vector(0, 1, 0));
		*g_t = apply_rot(*g_t, cy->rot, get_vector(0, 1, 0));
		if (t0 < g_t_min && p.y >= g_b->y && p.y <= g_t->y && (g_t_min = t0))
		{
			p = apply_rot(p, get_vector(0, 1, 0), cy->rot);
			normal = get_normalized(vectorminus(p, cy->pos));
		}
	}
}

	// float	t0;
	// t_vec3	p;

	// t0 = 0;
	// g_t_min = INFINITY;
	// g_b = sub_vecs(cy->position, mult_vec_n(normalize(cy->orientation), \
	// 													cy->height / 2));
	// g_t = add_vecs(cy->position, mult_vec_n(normalize(cy->orientation), \
	// 													cy->height / 2));
	// t0 = intersect_caps(ra, cy, g_t);
	// p = add_vecs(ra.o, mult_vec_n(ra.d, t0));
	// if (t0 > 0 && dist(p, g_t) <= cy->diameter / 2 && (g_t_min = t0))
	// 	g_normal = process_normal(ra, cy->orientation);
	// t0 = intersect_caps(ra, cy, g_b);
	// p = add_vecs(ra.o, mult_vec_n(ra.d, t0));
	// if (t0 > 0 && dist(p, g_b) <= cy->diameter / 2 && (g_t_min = t0))
	// 	g_normal = process_normal(ra, cy->orientation);
	// infinite_cy(ra, cy);
	// if (!(g_t_min > 0 && g_t_min != INFINITY))
	// 	return ;
	// (*hit).t = g_t_min;
	// (*hit).cylinder = cy;
	// (*hit).normal = g_normal;

bool	test2(const t_ray ray, t_cylinder cy, t_hit *hit)
{
	double		t;
	double		tmin;
	t_3dvector	b;
	t_3dvector	v;
	t_3dvector	pos;
	t_3dvector	normal;

	t = 0;
	tmin = INFINITY;
	b = vectorminus(cy.pos, vectormultiply(get_normalized(cy.rot), cy.height / 2));
	v = vectoradd(cy.pos, vectormultiply(get_normalized(cy.rot), cy.height / 2));
	t = intersect_caps(ray, &cy, v);
	pos = vectoradd(ray.origin, vectormultiply(ray.direction, t));
	if (t > 0 && distance(pos, v) <= cy.radius && (tmin = t))
		normal = process_normal(ray, cy.rot);
	t = intersect_caps(ray, &cy, b);
	pos = vectoradd(ray.origin, vectormultiply(ray.direction, t));
	if (t > 0 && distance(pos, b) <= cy.radius && (tmin = t))
		normal = process_normal(ray, cy.rot);
	infinite_cy(ray, &cy, &v, &b, tmin);
	if (!(tmin > 0 && tmin != INFINITY))
		return (false);
	hit->dist = tmin;
	hit->pos = pos;
	hit->normal = normal;
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
		if (test2(*ray, *cy, hit))
			hit->color = cy->color;
		new = new->next;
	}
}
