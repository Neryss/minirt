/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cylinder_utils3.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ckurt <ckurt@student.42lyon.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/08 11:19:03 by ckurt             #+#    #+#             */
/*   Updated: 2021/03/08 11:21:38 by ckurt            ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minirt.h"

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

t_3dvector	process_normal_cy(t_ray ray, t_3dvector normal)
{
	if (scalar(ray.direction, normal) < EPSILON)
		return (normal);
	return (vectormultiply(normal, -1));
}
