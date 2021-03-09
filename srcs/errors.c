/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   errors.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ckurt <ckurt@student.42lyon.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/08 13:17:54 by ckurt             #+#    #+#             */
/*   Updated: 2021/03/09 13:43:56 by ckurt            ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minirt.h"

void	close_minirt(char *error)
{
	if (!ft_strcmp(error, ""))
		exit(EXIT_SUCCESS);
	else
	{
		ft_putendl_fd("Error", 2);
		ft_putendl_fd(error, 2);
		exit(EXIT_FAILURE);
	}
}
