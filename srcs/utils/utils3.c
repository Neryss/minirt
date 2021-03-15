/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils3.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ckurt <ckurt@student.42lyon.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/22 16:45:13 by ckurt             #+#    #+#             */
/*   Updated: 2021/03/15 10:02:52 by ckurt            ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minirt.h"

bool	check_rgb(t_rgb c)
{
	if (c.r < 0 || c.r > 255)
		return (false);
	if (c.g < 0 || c.g > 255)
		return (false);
	if (c.b < 0 || c.b > 255)
		return (false);
	return (true);
}

bool	check_fov(int fov)
{
	if (fov < 0 || fov > 180)
		return (false);
	return (true);
}

bool	check_intensity(double i)
{
	if (i < 0 || i > 1)
		return (false);
	return (true);
}

bool	check_vector(t_3dvector v, double a, double b)
{
	if ((v.x < a || v.x > b) || (v.y < a || v.y > b) || (v.z < a || v.z > b))
		return (false);
	return (true);
}
