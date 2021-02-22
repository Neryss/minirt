/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils3.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ckurt <ckurt@student.42lyon.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/22 16:45:13 by ckurt             #+#    #+#             */
/*   Updated: 2021/02/22 16:46:22 by ckurt            ###   ########lyon.fr   */
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

bool	check_normal(t_3dvector nor)
{
	if (nor.x < -1 || nor.x > 1)
		return (false);
	if (nor.y < -1 || nor.y > 1)
		return (false);
	if (nor.z < -1 || nor.z > 1)
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
