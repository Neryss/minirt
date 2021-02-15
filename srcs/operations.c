/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   operations.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ckurt <ckurt@student.42lyon.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/09 15:04:53 by ckurt             #+#    #+#             */
/*   Updated: 2021/02/15 11:11:03 by ckurt            ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minirt.h"

double	scalar(t_3dvector v1, t_3dvector v2)
{
	return ((v1.x * v2.x) + (v1.y * v2.y) + (v1.z * v2.z));
}

double	getnorm2(t_3dvector v1)
{
	return ((v1.x * v1.x) + (v1.y * v1.y) + (v1.z * v1.z));
}

t_3dvector	get_normalized(t_3dvector vector)
{
	t_3dvector	res;

	res.x = vector.x;
	res.y = vector.y;
	res.z = vector.z;
	normalize(&res);
	return (res);
}

t_3dvector	get_vector(double x, double y, double z)
{
	t_3dvector	res;

	res.x = x;
	res.y = y;
	res.z = z;
	return (res);
}

void	normalize(t_3dvector *v1)
{
	double	norm;

	norm = sqrt(getnorm2(v1[0]));
	v1->x /= norm;
	v1->y /= norm;
	v1->z /= norm;
}
