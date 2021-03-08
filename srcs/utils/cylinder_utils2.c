/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cylinder_utils2.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ckurt <ckurt@student.42lyon.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/22 12:57:22 by ckurt             #+#    #+#             */
/*   Updated: 2021/03/08 12:24:03 by ckurt            ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minirt.h"

void	set_res(t_cyresolve *res, double t, t_ray ray, t_cylinder cy)
{
	res->tmin = t;
	res->normal = process_normal_cy(ray, cy.rot);
}

void	calc_things(double *a, double *b, t_ray ray, t_cyresolve *res)
{
	*a = scalar(vectorcross(ray.direction, vectorminus(res->t, res->b)),
			vectorcross(ray.direction, vectorminus(res->t, res->b)));
	*b = 2 * scalar(vectorcross(ray.direction, vectorminus(res->t, res->b)),
			vectorcross(vectorminus(ray.origin, res->b),
				vectorminus(res->t, res->b)));
}

double	calc_c(t_ray ray, t_cylinder cy, t_3dvector t, t_3dvector b)
{
	return (scalar(vectorcross(vectorminus(ray.origin, b), vectorminus(t, b)),
			vectorcross(vectorminus(ray.origin, b), vectorminus(t, b)))
		- (cy.radius * cy.radius * scalar(vectorminus(t, b),
				vectorminus(t, b))));
}

t_3dvector	calclanormalparceqttroplongue(t_cylinder cy, t_3dvector p)
{
	return (vectorminus(vectoradd(cy.pos, vectormultiply(get_normalized(cy.rot),
					scalar(vectorminus(p, cy.pos),
						get_normalized(cy.rot)))), p));
}
