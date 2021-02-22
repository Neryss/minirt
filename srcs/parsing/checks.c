/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   checks.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ckurt <ckurt@student.42lyon.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/08 13:19:09 by ckurt             #+#    #+#             */
/*   Updated: 2021/02/22 14:20:44 by ckurt            ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minirt.h"

bool	check_rgb(t_rgb c)
{
	if (c.r <  0 || c.r > 255)
		return (false);
	if (c.g < 0 || c.g > 255)
		return (false);
	if (c.b < 0 || c.b > 255)
		return (false);
	return (true);
}

bool	check_normal(t_3dvector nor)
{
	if (nor.x < -1 || nor.x > 1)
		return (false);
	if (nor.y < -1 || nor.y > 1)
		return (false);
	if (nor.z < -1 || nor.z > 1)
		return (false);
	return (true);
}

bool	check_fov(int fov)
{
	if (fov < 0 || fov > 180)
		return (false);
	return (true);
}

bool	check_intensity(double i)
{
	if (i < 0 || i > 1)
		return (false);
	return (true);
}

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
