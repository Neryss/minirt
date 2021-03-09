/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_parsingutils.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ckurt <ckurt@student.42lyon.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/09 13:59:27 by ckurt             #+#    #+#             */
/*   Updated: 2021/03/09 13:59:29 by ckurt            ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minirt.h"

int	need_space(char **line)
{
	int		i;
	char	*str;

	str = *line;
	i = 0;
	while (ft_isspace(str[i]))
		i++;
	*line += i;
	return (i);
}

int	need_int(char **line)
{
	int		i;
	char	*str;

	str = *line;
	i = 0;
	if (*str == '-')
		i++;
	while (ft_isdigit(str[i]))
		i++;
	*line += i;
	return (i);
}

int	need_eol(char **line)
{
	int		i;
	char	*str;

	str = *line;
	i = 0;
	while (str[i] && ft_isspace(str[i]))
		i++;
	if (str[i])
		return (0);
	else
		i++;
	*line += i;
	return (i);
}

int	need_double(char **line)
{
	int		i;
	char	*str;
	int		tmp;

	str = *line;
	i = 0;
	tmp = need_int(&str);
	i += tmp;
	if (*str != '.')
	{
		*line += i;
		return (i);
	}
	i++;
	str++;
	if (*str == '-')
		return (0);
	tmp = need_int(&str);
	if (!tmp)
		return (0);
	i += tmp;
	*line += i;
	return (i);
}

int	need_rgb(char **line)
{
	int		i;
	char	*str;
	int		tmp;

	str = *line;
	i = 0;
	tmp = need_int(&str);
	if (!tmp)
		return (0);
	if (*str++ != ',')
		return (0);
	i += tmp + 1;
	tmp = need_int(&str);
	if (!tmp)
		return (0);
	if (*str++ != ',')
		return (0);
	i += tmp + 1;
	tmp = need_int(&str);
	if (!tmp)
		return (0);
	i += tmp;
	*line += i;
	return (i);
}
