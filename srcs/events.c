/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   events.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ckurt <ckurt@student.42lyon.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/08 13:28:47 by ckurt             #+#    #+#             */
/*   Updated: 2021/02/09 15:43:02 by ckurt            ###   ########lyon.fr   */
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

void	change_cam(t_engine *engine)
{
	t_list	*frst;

	frst = engine->scene->cams;
	while (frst)
	{
		if (frst->content)
		{
			if (!engine->camera || ((t_camera *)frst->content)->id > engine->camera->id)
			{
				engine->camera = frst->content;
				return ;
			}
		}
		frst = frst->next;
	}
	if (engine->camera)
	{
		engine->camera = NULL;
		change_cam(engine);
	}
	else
		close_minirt("Error during camera alloc\n");
}