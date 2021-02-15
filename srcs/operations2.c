/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   operations2.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ckurt <ckurt@student.42lyon.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/10 12:43:18 by ckurt             #+#    #+#             */
/*   Updated: 2021/02/15 15:19:36 by ckurt            ###   ########lyon.fr   */
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
