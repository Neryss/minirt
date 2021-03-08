/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   getters.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ckurt <ckurt@student.42lyon.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/09 10:24:09 by ckurt             #+#    #+#             */
/*   Updated: 2021/03/08 13:11:38 by ckurt            ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minirt.h"

t_3dvector	parse_vector(char **line)
{
	t_3dvector	vec;
	int			i;

	i = 0;
	vec.x = ft_atof(*line);
	i += ft_atof_len(*line);
	*line += i;
	if (**line != ',')
		close_minirt("Vector is invalid\n");
	*line += 1;
	vec.y = ft_atof(*line);
	i = 0;
	i += ft_atof_len(*line);
	*line += i;
	if (**line != ',')
		close_minirt("Vector is invalid\n");
	*line += 1;
	vec.z = ft_atof(*line);
	i = 0;
	i += ft_atof_len(*line);
	*line += i;
	return (vec);
}

t_rgb	ft_get_rgb(char **line)
{
	t_rgb		rgb;
	int			i;

	i = 0;
	rgb.r = ft_atof(*line);
	i += ft_atof_len(*line);
	*line += i;
	if (**line != ',')
		close_minirt("Rgb is invalid\n");
	*line += 1;
	rgb.g = ft_atof(*line);
	i = 0;
	i += ft_atof_len(*line);
	*line += i;
	if (**line != ',')
		close_minirt("Rgb is invalid\n");
	*line += 1;
	rgb.b = ft_atof(*line);
	i = 0;
	i += ft_atof_len(*line);
	*line += i;
	if (!check_rgb(rgb))
		close_minirt("Rgb out of bounds [0, 255]");
	return (rgb);
}
