/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ckurt <ckurt@student.42lyon.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/08 13:36:26 by ckurt             #+#    #+#             */
/*   Updated: 2021/03/08 10:47:27 by ckurt            ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#ifndef BONUS
# include "../includes/minirt.h"

void	*render_thread(t_thread_data *thread)
{
	int	x;
	int	y;

	y = thread->from - 1;
	while (++y < thread->to)
	{
		x = -1;
		while (++x < thread->engine->size_x)
		{
			put_pxl(thread->engine, x, y, ft_rgbtohex(0, 0, 0));
			do_raytracing(thread->engine, x, y);
		}
	}
	return (NULL);
}

void	render(t_engine *engine)
{
	t_thread_data	thread;

	thread.engine = engine;
	thread.from = 0;
	thread.to = engine->size_y - 1;
	thread.id = 0;
	mlx_clear_window(engine->mlx, engine->win);
	render_thread(&thread);
	mlx_put_image_to_window(engine->mlx, engine->win, engine->frame->img, 0, 0);
	mlx_do_sync(engine->mlx);
	engine->need_render = false;
}

#endif