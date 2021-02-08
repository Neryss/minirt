/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   events.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ckurt <ckurt@student.42lyon.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/08 13:28:47 by ckurt             #+#    #+#             */
/*   Updated: 2021/02/08 14:59:35 by ckurt            ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minirt.h"

int	exit_hook(t_engine *engine)
{
	(void)engine;
	printf("closing program");
	exit(0);
}

int	key_press(int key, t_engine *engine)
{
	if (key == 53)
	{
		clean_close(engine);
		exit(0);
	}
	return (1);
}
