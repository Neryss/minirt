/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   window.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ckurt <ckurt@student.42lyon.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/08 14:56:58 by ckurt             #+#    #+#             */
/*   Updated: 2021/02/08 14:58:02 by ckurt            ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minirt.h"

void	clean_close(t_engine *engine)
{
	mlx_clear_window(engine->mlx, engine->win);
	mlx_destroy_window(engine->mlx, engine->win);
}
