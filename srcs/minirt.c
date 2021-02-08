/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minirt.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ckurt <ckurt@student.42lyon.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/08 12:12:58 by ckurt             #+#    #+#             */
/*   Updated: 2021/02/08 14:56:11 by ckurt            ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minirt.h"

int	init_frame(t_engine *engine)
{
	engine->frame = malloc(sizeof(t_frame));
	if (!engine->frame)
		return (0);
	engine->frame->img = mlx_new_image(
			engine->mlx, engine->size_x, engine->size_y);
	engine->frame->addr = mlx_get_data_addr(engine->frame->img,
			&engine->frame->bpp, &engine->frame->line_len, &engine->frame->endian);
	if (!engine->frame->img || !engine->frame->addr)
		return (0);
	return (1);
}

int	start_init(char *map_path, t_engine *engine, int save)
{
	engine->file = get_map_info(map_path, engine);
	if (!check_resolution(engine, save))
		return (-1);
	if (!check_caps_args(engine))
		close_minirt(-6);
	engine->mlx = mlx_init();
	engine->win = mlx_new_window(
			engine->mlx, engine->size_x, engine->size_y, map_path);
	if (!engine->mlx || !engine->win)
		close_minirt(0);
	return (1);
}

int	main(int argc, char **argv)
{
	t_engine	engine;
	int			save;

	save = 0;
	if (argc == 3 && !ft_strcmp(argv[2], "--save"))
		save = 1;
	check_args(argc, argv);
	start_init(argv[1], &engine, save);
	if (!init_frame(&engine))
		close_minirt(1);
	mlx_key_hook(engine.win, key_press, &engine);
	mlx_hook(engine.win, 17, 0, exit_hook, &engine);
	mlx_loop(engine.mlx);
	return (0);
}