/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ckurt <ckurt@student.42lyon.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/15 10:45:41 by ckurt             #+#    #+#             */
/*   Updated: 2021/02/22 16:42:55 by ckurt            ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minirt.h"

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

bool	check_uniq(char *str)
{
	if (str[0] == 'R' && ft_iswhitespace(*(str + 1)))
		return (true);
	if (str[0] == 'A' && ft_iswhitespace(*(str + 1)))
		return (true);
	return (false);
}

static bool	iw(char c)
{
	if (ft_iswhitespace(c))
		return (true);
	return (false);
}

bool	check_lines(t_engine *engine, int i)
{
	if (ft_startwith(engine->file[i], "sp") && iw(*(engine->file[i] + 2)))
		add_sphere(&engine->scene->spheres, engine->file[i] + 2);
	else if (ft_startwith(engine->file[i], "pl") && iw(*(engine->file[i] + 2)))
		add_plane(&engine->scene->planes, engine->file[i] + 2);
	else if (engine->file[i][0] == 'l' && iw(*(engine->file[i] + 1)))
		add_light(&engine->scene->lights, engine->file[i] + 1);
	else if (engine->file[i][0] == 'c' && iw(*(engine->file[i] + 1)))
		add_camera(&engine->scene->cams, engine->file[i] + 1);
	else if (engine->file[i][0] == 'A' && iw(*(engine->file[i] + 1)))
		add_alight(engine, engine->file[i] + 1);
	else if (ft_startwith(engine->file[i], "ds") && iw(*(engine->file[i] + 2)))
		add_disk(&engine->scene->disk, engine->file[i] + 2);
	else if (ft_startwith(engine->file[i], "tr") && iw(*(engine->file[i] + 2)))
		add_triangle(&engine->scene->triangles, engine->file[i] + 2);
	else if (ft_startwith(engine->file[i], "cy") && iw(*(engine->file[i] + 2)))
		add_cylinder(&engine->scene->cylinders, engine->file[i] + 2);
	else
		return (false);
	return (true);
}
