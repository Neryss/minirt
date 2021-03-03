/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ckurt <ckurt@student.42lyon.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/08 13:36:26 by ckurt             #+#    #+#             */
/*   Updated: 2021/03/03 15:59:39 by ckurt            ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#ifndef BONUS
# include "../includes/minirt.h"

void	render(t_engine *engine)
{
	if (engine->need_render)
	{
		mlx_clear_window(engine->mlx, engine->win);
		do_raytracing(engine);
		mlx_put_image_to_window(engine->mlx, engine->win, engine->frame->img, 0, 0);
		mlx_do_sync(engine->mlx);
	}
	engine->need_render = false;
}

#endif