/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raytrace_cylinder.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ckurt <ckurt@student.42lyon.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/16 14:07:42 by ckurt             #+#    #+#             */
/*   Updated: 2021/02/17 14:15:42 by ckurt            ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minirt.h"

bool	inter_cylinders(const t_ray ray, const t_cylinder cy, t_hit *hit)
{
	t_3dvector	p0;
	double		a;
	double		b;
	double		c;
	double		delta;
	double		t;

	p0 = get_vector(ray.origin.x - cy.pos.x, ray.origin.y - cy.pos.y, ray.origin.z - cy.pos.z);

	a = ray.direction.x * ray.direction.x + ray.direction.z * ray.direction.z;
	b = ray.direction.x * p0.x + ray.direction.z * p0.z;
	c = p0.x * p0.x + p0.z * p0.z - cy.radius * cy.radius;

	delta = b * b - a * c;
	if (delta < EPSILON)
		return (false);
	t = (-b - sqrt(delta)) / a;
	if (t <= EPSILON)
		return (false);
	hit->pos = p0;
	hit->dist = t;
	// printf("sk\n");
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
		if (inter_cylinders(*ray, *cy, hit))
			hit->color = cy->color;
		new = new->next;
	}
}