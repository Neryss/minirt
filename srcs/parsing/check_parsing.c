/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_parsing.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ckurt <ckurt@student.42lyon.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/09 13:58:34 by ckurt             #+#    #+#             */
/*   Updated: 2021/03/09 13:58:39 by ckurt            ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minirt.h"

bool	check_resolution(char *str)
{
	if (!need_space(&str))
		return (false);
	if (!need_int(&str))
		return (false);
	if (!need_space(&str))
		return (false);
	if (!need_int(&str))
		return (false);
	if (!need_eol(&str))
		return (false);
	return (true);
}

bool	check_alight(char *str)
{
	if (!need_space(&str))
		return (false);
	if (!need_double(&str))
		return (false);
	if (!need_space(&str))
		return (false);
	if (!need_rgb(&str))
		return (false);
	if (!need_eol(&str))
		return (false);
	return (true);
}

bool	check_camera(char *str)
{
	if (!need_space(&str))
		return (false);
	if (!need_3dvector(&str))
		return (false);
	if (!need_space(&str))
		return (false);
	if (!need_3dvector(&str))
		return (false);
	if (!need_space(&str))
		return (false);
	if (!need_int(&str))
		return (false);
	if (!need_eol(&str))
		return (false);
	return (true);
}

bool	check_light(char *str)
{
	if (!need_space(&str))
		return (false);
	if (!need_3dvector(&str))
		return (false);
	if (!need_space(&str))
		return (false);
	if (!need_double(&str))
		return (false);
	if (!need_space(&str))
		return (false);
	if (!need_rgb(&str))
		return (false);
	if (!need_eol(&str))
		return (false);
	return (true);
}

void	check_line(char *line)
{
	if (is_id(line, "R") && !check_resolution(line + 1))
		close_minirt(ft_strjoin("misconfiguration in : ", line));
	else if (is_id(line, "A") && !check_alight(line + 1))
		close_minirt(ft_strjoin("misconfiguration in : ", line));
	else if (is_id(line, "c") && !check_camera(line + 1))
		close_minirt(ft_strjoin("misconfiguration in : ", line));
	else if (is_id(line, "l") && !check_light(line + 1))
		close_minirt(ft_strjoin("misconfiguration in : ", line));
	else if (is_id(line, "sp") && !check_sphere(line + 2))
		close_minirt(ft_strjoin("misconfiguration in : ", line));
	else if (is_id(line, "pl") && !check_plane(line + 2))
		close_minirt(ft_strjoin("misconfiguration in : ", line));
	else if (is_id(line, "sq") && !check_square(line + 2))
		close_minirt(ft_strjoin("misconfiguration in : ", line));
	else if (is_id(line, "cy") && !check_cylinder(line + 2))
		close_minirt(ft_strjoin("misconfiguration in : ", line));
	else if (is_id(line, "tr") && !check_triangle(line + 2))
		close_minirt(ft_strjoin("misconfiguration in : ", line));
}
