/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mutithreading.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ckurt <ckurt@student.42lyon.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/03 13:12:47 by ckurt             #+#    #+#             */
/*   Updated: 2021/03/03 13:32:31 by ckurt            ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minirt.h"
#include <pthread.h>

void	thread_test()
{
	t_thread_data	thread;
	pthread_t		*id;
	int				i;

	i = 0;
	id = malloc(sizeof(pthread_t) * MAX_THREAD);
	if (!id)
		close_minirt("During thread init");
	while (i < MAX_THREAD)
		pthread_create(&id[i++], NULL, );
}