/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cylinder_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ckurt <ckurt@student.42lyon.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/22 12:44:00 by ckurt             #+#    #+#             */
/*   Updated: 2021/02/22 13:12:35 by ckurt            ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minirt.h"

t_3dvector	return_normal(t_3dvector point, t_cylinder cy)
{
	return (vectorminus(vectoradd(cy.pos,
				vectormultiply(get_normalized(cy.rot),
					 scalar(vectorminus(point, cy.pos),
							get_normalized(cy.rot)))), point));
}

double	calc_b(t_ray ray, t_resolve *res)
{
	return (2 * scalar(vectorcross(ray.direction, vectorminus(res->t, res->b)),
			vectorcross(vectorminus(ray.origin, res->b),
					vectorminus(res->t, res->b))));
}

double	calc_a(t_ray ray, t_resolve *res)
{
	return (scalar(vectorcross(ray.direction, vectorminus(res->t, res->b)),
			vectorcross(ray.direction, vectorminus(res->t, res->b))));
}

void	set_hit(t_hit *hit, t_ray ray, t_resolve res)
{
	hit->dist = res.tmin;
	hit->pos = vectoradd(ray.origin, vectormultiply(ray.direction, res.tmin));
	hit->normal = get_normalized(res.normal);
}

void	init_res(t_resolve *res, t_cylinder cy)
{
	res->tmin = INFINITY;
	res->b = vectorminus(cy.pos,
			vectormultiply(get_normalized(cy.rot), cy.height / 2));
	res->t = vectoradd(cy.pos,
			vectormultiply(get_normalized(cy.rot), cy.height / 2));
}
