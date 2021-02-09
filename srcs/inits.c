/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   inits.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ckurt <ckurt@student.42lyon.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/09 10:09:10 by ckurt             #+#    #+#             */
/*   Updated: 2021/02/09 16:14:04 by ckurt            ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minirt.h"

int	start_init(char *map_path, t_engine *engine, int save)
{
	engine->file = get_map_info(map_path, engine);
	if (!check_resolution(engine, save))
		return (-1);
	if (!check_caps_args(engine))
		close_minirt("Error too many unique objects");
	engine->mlx = mlx_init();
	printf("{%d}\n", engine->size_x);
	engine->win = mlx_new_window(
			engine->mlx, engine->size_x, engine->size_y, map_path);
	get_scene(engine);
	if (!engine->mlx || !engine->win)
		close_minirt("Error during mlx init\n");
	return (1);
}

int	init_frame(t_engine *engine)
{
	engine->frame = malloc(sizeof(t_frame));
	if (!engine->frame)
		close_minirt("Error no frame\n");
	engine->frame->img = mlx_new_image(
			engine->mlx, engine->size_x, engine->size_y);
	engine->frame->addr = mlx_get_data_addr(engine->frame->img,
			&engine->frame->bpp, &engine->frame->line_len, &engine->frame->endian);
	if (!engine->frame->img || !engine->frame->addr)
		close_minirt("Error during img setup\n");
	return (1);
}

void	init_engine(t_engine *engine)
{
	engine->file = NULL;
	engine->frame = NULL;
	engine->mlx = NULL;
	engine->scene = NULL;
	engine->size_x = 0;
	engine->size_y = 0;
	engine->win = NULL;
}