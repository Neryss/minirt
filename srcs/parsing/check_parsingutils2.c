/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_parsingutils2.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ckurt <ckurt@student.42lyon.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/09 13:59:38 by ckurt             #+#    #+#             */
/*   Updated: 2021/03/09 14:08:23 by ckurt            ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minirt.h"

int	need_3dvector(char **line)
{
	int		i;
	char	*str;
	int		tmp;

	str = *line;
	i = 0;
	tmp = need_double(&str);
	if (!tmp)
		return (0);
	if (*str++ != ',')
		return (0);
	i += tmp + 1;
	tmp = need_double(&str);
	if (!tmp)
		return (0);
	if (*str++ != ',')
		return (0);
	i += tmp + 1;
	tmp = need_double(&str);
	if (!tmp)
		return (0);
	i += tmp;
	*line += i;
	return (i);
}

int	is_id(char *str, char *id)
{
	size_t	tmp;

	tmp = ft_strlen(id);
	return (!ft_strncmp(str, id, tmp) && (!str[tmp] || ft_isspace(str[tmp])));
}

bool	ft_isspace(char c)
{
	return ((c >= 9 && c <= 13) || c == ' ');
}
