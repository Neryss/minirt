/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vector.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ckurt <ckurt@student.42lyon.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/08 12:50:29 by ckurt             #+#    #+#             */
/*   Updated: 2021/02/08 15:39:12 by ckurt            ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minirt.h"

t_3dvector	vectoradd(t_3dvector v1, t_3dvector v2)
{
	t_3dvector	res;

	res.x = v1.x + v2.x;
	res.y = v1.y + v2.y;
	res.z = v1.z + v2.z;
	return (res);
}

t_3dvector	vectormultiply(t_3dvector v1, double value)
{
	t_3dvector	res;

	res.x = v1.x * value;
	res.y = v1.y * value;
	res.z = v1.z * value;
	return (res);
}

t_3dvector	getvector(double x, double y, double z)
{
	t_3dvector	v1;

	v1.x = x;
	v1.y = y;
	v1.z = z;
	return (v1);
}

t_3dvector	vectorminus(t_3dvector v1, t_3dvector v2)
{
	t_3dvector	res;

	res.x = v1.x - v2.x;
	res.y = v1.y - v2.y;
	res.z = v1.z - v2.z;
	return (res);
}
