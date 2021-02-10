/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   getters.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ckurt <ckurt@student.42lyon.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/09 10:24:09 by ckurt             #+#    #+#             */
/*   Updated: 2021/02/10 15:31:13 by ckurt            ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minirt.h"

t_3dvector		parse_vector(char **line)
{
	t_3dvector	vec;
	int			i;

	i = 0;
	vec.x = ft_atof(*line);
	i += ft_skipuntilc(*line, ',');
	*line += i;
	if (**line != ',')
		close_minirt("Error vector is invalid\n");
	*line += 1;
	vec.y = ft_atof(*line);
	i = 0;
	i += ft_atof_len(*line);
	*line += i;
	if (**line != ',')
		close_minirt("Error vector is invalid\n");
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
	i += ft_skipuntilc(*line, ',');
	*line += i;
	if (**line != ',')
		close_minirt("Error vector is invalid\n");
	*line += 1;
	rgb.g = ft_atof(*line);
	i = 0;
	i += ft_atof_len(*line);
	*line += i;
	if (**line != ',')
		close_minirt("Error vector is invalid\n");
	*line += 1;
	rgb.b = ft_atof(*line);
	i = 0;
	i += ft_atof_len(*line);
	*line += i;
	return (rgb);
}
