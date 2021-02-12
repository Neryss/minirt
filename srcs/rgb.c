/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rgb.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ckurt <ckurt@student.42lyon.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/10 13:17:01 by ckurt             #+#    #+#             */
/*   Updated: 2021/02/12 14:49:13 by ckurt            ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minirt.h"

t_rgb	mult_rgb_double(t_rgb rgb, double value)
{
	t_rgb color;

	color = create_rgb(rgb.r * value, rgb.g * value, rgb.b * value);
	return (color);
}

t_rgb	mult_rgb_rgb(t_rgb r1, t_rgb r2)
{
	t_rgb	res;

	res = create_rgb(r1.r * (r2.r / 255.), r1.g * (r2.g / 255.), r1.b * (r2.b / 255.));
	return (res);
}

t_rgb	add_rgb_rgb(t_rgb c1, t_rgb c2)
{
	t_rgb	res;

	res = create_rgb(c1.r + c2.r, c1.g + c2.g, c1.b + c2.b);
	return (res);
}

t_rgb	create_rgb(int r, int g, int b)
{
	t_rgb	rgb;

	rgb.r = r;
	rgb.g = g;
	rgb.b = b;
	return (rgb);
}
