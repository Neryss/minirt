/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raytrace_cylinder.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ckurt <ckurt@student.42lyon.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/16 14:07:42 by ckurt             #+#    #+#             */
/*   Updated: 2021/02/18 11:14:16 by ckurt            ###   ########lyon.fr   */
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

void	raytrace_cylinders(t_engine *engine, t_hit *hit, t_ray *ray)
{
	t_list		*new;
	t_cylinder	*cy;

	new = engine->scene->cylinders;
	while (new)
	{
		cy = new->content;
		if (test_inter(*cy, *ray, hit))
			hit->color = cy->color;
		new = new->next;
	}
}
