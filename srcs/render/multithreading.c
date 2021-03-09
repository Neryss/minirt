/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   multithreading.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ckurt <ckurt@student.42lyon.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/03 13:12:47 by ckurt             #+#    #+#             */
/*   Updated: 2021/03/09 15:20:32 by ckurt            ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#ifdef BONUS
# include "../../includes/minirt.h"
# include <pthread.h>

void	*multi_raytracing(t_thread_data *thread_data)
{
	int	x;
	int	y;

	y = thread_data->from - 1;
	while (++y <= thread_data->to)
	{
		x = -1;
		while (++x < thread_data->engine->size_x)
		{
			put_pxl(thread_data->engine, x, y, ft_rgbtohex(0, 0, 0));
			do_raytracing(thread_data->engine, x, y);
		}
	}
	pthread_exit(NULL);
}

void	*wait_thread(pthread_t *tid, long nproc, t_thread_data *thread)
{
	int	i;

	i = 0;
	while (i < nproc)
	{
		pthread_join(tid[i++], NULL);
		if (DEBUG)
			printf("thread %d joined\n", i);		
	}
	free(tid);
	free(thread);
	return (NULL);
}

void	*render_scene_multi(t_engine *engine)
{
	t_thread_data	*thread;
	pthread_t		*id;
	int				i;
	int				to;

	i = -1;
	to = -1;
	thread = malloc(sizeof(t_thread_data) * MAX_THREAD);
	id = malloc(sizeof(pthread_t) * MAX_THREAD);
	if (!id || !thread)
		close_minirt("During thread init");
	while (++i < MAX_THREAD)
	{
		thread[i].from = to + 1;
		to = imin(engine->size_y - 1, thread[i].from
				+ (engine->size_y / MAX_THREAD));
		thread[i].id = i;
		thread[i].engine = engine;
		thread[i].to = to;
		if (pthread_create(&id[i], NULL, (void *)multi_raytracing, &thread[i]))
			close_minirt("Thread creation failed :/");
		if (DEBUG)
			printf("Thread %d created\n", i);
	}
	return (wait_thread(id, MAX_THREAD, thread));
}

void	render(t_engine *engine)
{
	mlx_clear_window(engine->mlx, engine->win);
	render_scene_multi(engine);
	mlx_put_image_to_window(engine->mlx, engine->win, engine->frame->img, 0, 0);
	mlx_do_sync(engine->mlx);
	engine->need_render = false;
}

#endif
