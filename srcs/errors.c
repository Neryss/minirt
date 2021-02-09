/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   errors.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ckurt <ckurt@student.42lyon.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/08 13:17:54 by ckurt             #+#    #+#             */
/*   Updated: 2021/02/09 13:29:38 by ckurt            ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minirt.h"

void	close_minirt(char *error)
{
	if (error == 0)
		exit(EXIT_SUCCESS);
	else
	{
		if (ft_strcmp(error, ""))
			printf("%s\n", error);
		exit(EXIT_FAILURE);
	}
}
