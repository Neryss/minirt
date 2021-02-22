/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ckurt <ckurt@student.42lyon.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/08 12:53:06 by ckurt             #+#    #+#             */
/*   Updated: 2021/02/22 15:58:50 by ckurt            ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minirt.h"

static char	**read_map(char *path_to_map)
{
	int		fd;
	char	**array;

	fd = open(path_to_map, O_RDONLY);
	array = ft_read_file(fd);
	close(fd);
	return (array);
}

static void	get_resolution(char *line, t_engine *engine)
{
	int		i;

	i = 1;
	engine->size_x = ft_atoi(line + 1);
	while (line[i] == ' ' || line[i] == '\t')
		i++;
	while (ft_isdigit(line[i]) || line[i] == '-')
		i++;
	while (line[i] == ' ' || line[i] == '\t')
		i++;
	engine->size_y = ft_atoi(line + i);
}

char	**get_map_info(char *path_to_map, t_engine *engine)
{
	int		i;
	char	**map_array;

	map_array = read_map(path_to_map);
	i = 0;
	if (!map_array)
		close_minirt("Empty file");
	while (map_array[i])
	{
		if (map_array[i][0] == 'R')
			get_resolution(map_array[i], engine);
		i++;
	}
	return (map_array);
}
