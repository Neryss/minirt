/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   checks.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ckurt <ckurt@student.42lyon.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/08 13:19:09 by ckurt             #+#    #+#             */
/*   Updated: 2021/02/09 10:47:53 by ckurt            ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minirt.h"

int	check_caps_args(t_engine *engine)
{
	int	resolution;
	int	alight;
	int	i;

	i = 0;
	alight = 0;
	resolution = 0;
	while (engine->file[i])
	{
		if (engine->file[i][0] == 'R')
			resolution++;
		if (engine->file[i][0] == 'A')
			alight++;
		i++;
	}
	if (resolution >= 2 || alight >= 2)
		return (0);
	return (1);
}

void	check_args(int argc, char **argv)
{
	if (argc != 2 && argc != 3)
		close_minirt("Error wrong numbers of arguments\n");
	if (!ft_endwith(argv[1], ".rt"))
		close_minirt("Error bad file format\n");
	if (open(argv[1], O_DIRECTORY) != -1)
		close_minirt("Error invalid file descriptor");
	if (open(argv[1], O_RDONLY) == -1)
		close_minirt("Error during file opening");
}

int	check_resolution(t_engine *engine, int save)
{
	int	max_x;
	int	max_y;

	mlx_get_screen_size(engine->mlx, &max_x, &max_y);
	printf("x: %d\n", engine->size_x);
	printf("y: %d\n", engine->size_y);
	if (!save)
	{
		if (engine->size_x <= 0 || engine->size_y <= 0)
			close_minirt("Error invalid resolution\n");
		if (engine->size_x > max_x)
			engine->size_x = max_x;
		if (engine->size_y > max_y)
			engine->size_y = max_y;
	}
	return (1);
}