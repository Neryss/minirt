/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cylinder_utils2.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ckurt <ckurt@student.42lyon.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/22 12:57:22 by ckurt             #+#    #+#             */
/*   Updated: 2021/02/22 13:12:39 by ckurt            ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minirt.h"

t_3dvector	process_normal(t_ray ray, t_3dvector normal)
{
	if (scalar(ray.direction, normal) < EPSILON)
		return (normal);
	return (vectormultiply(normal, -1));
}

void	set_res(t_resolve *res, double t, t_ray ray, t_cylinder cy)
{
	res->tmin = t;
	res->normal = process_normal(ray, cy.rot);
}
