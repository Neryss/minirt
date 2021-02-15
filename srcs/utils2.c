/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ckurt <ckurt@student.42lyon.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/15 10:45:41 by ckurt             #+#    #+#             */
/*   Updated: 2021/02/15 11:17:00 by ckurt            ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minirt.h"

double	to_rad(double value)
{
	return (value * M_PI * .5);
}

void	set_hit_color(t_hit *hit)
{
	hit->color.r = imin(hit->color.r, 255);
	hit->color.g = imin(hit->color.g, 255);
	hit->color.b = imin(hit->color.b, 255);
}
