/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ckurt <ckurt@student.42lyon.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/08 13:36:26 by ckurt             #+#    #+#             */
/*   Updated: 2021/02/08 15:38:32 by ckurt            ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minirt.h"

void	put_pxl(t_engine *engine, int x, int y, int color)
{
	char	*dst;

	dst = engine->frame->addr
		+ (y * engine->frame->line_len + x
			* (engine->frame->bpp / 8));
	*(unsigned int*)dst = color;
}

void	fill_screen(t_engine *engine)
{
	int	x;
	int	y;

	x = 0;
	y = 0;
	while (y < engine->size_y)
	{
		while (x < engine->size_x)
		{
			put_pxl(engine, x, y, ft_rgbtohex(0, 0, 0));
			x++;
		}
		x = 0;
		y++;
	}
}

void	render(t_engine *engine)
{
	mlx_clear_window(engine->mlx, engine->win);
	fill_screen(engine);
	mlx_do_sync(engine->mlx);
}
