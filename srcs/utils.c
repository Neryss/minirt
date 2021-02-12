/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ckurt <ckurt@student.42lyon.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/09 10:59:49 by ckurt             #+#    #+#             */
/*   Updated: 2021/02/12 14:49:38 by ckurt            ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minirt.h"

void	write_custom(int fd, unsigned int val)
{
	char	tmp;

	tmp = val;
	write(fd, &tmp, 1);
}

int	imax(int a, int b)
{
	if (a > b)
		return (a);
	return (b);
}

int	imin(int a, int b)
{
	if (a < b)
		return (a);
	return (b);
}

double	ft_dmax(double a, double b)
{
	if (a > b)
		return (a);
	else
		return (b);
}

double	ft_dmin(double a, double b)
{
	if (a < b)
		return (a);
	else
		return (b);
}

void	set_hit_color(t_hit *hit)
{
	hit->color.r = imin(hit->color.r, 255);
	hit->color.g = imin(hit->color.g, 255);
	hit->color.b = imin(hit->color.b, 255);
}
