/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minirt.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ckurt <ckurt@student.42lyon.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/08 12:12:58 by ckurt             #+#    #+#             */
/*   Updated: 2021/02/09 11:04:06 by ckurt            ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minirt.h"

int	main(int argc, char **argv)
{
	t_engine	engine;
	int			save;

	save = 0;
	if (argc == 3 && !ft_strcmp(argv[2], "--save"))
		save = 1;
	init_engine(&engine);
	check_args(argc, argv);
	start_init(argv[1], &engine, save);
	if (!init_frame(&engine))
		close_minirt("Error during scene init\n");
	if (save)
	{
		get_save(&engine, "save.bmp");
		close_minirt("");
	}
	mlx_key_hook(engine.win, key_press, &engine);
	mlx_hook(engine.win, 17, 0, exit_hook, &engine);
	mlx_loop_hook(engine.mlx, call_render, &engine);
	mlx_loop(engine.mlx);
	return (0);
}
