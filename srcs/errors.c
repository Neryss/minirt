/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   errors.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ckurt <ckurt@student.42lyon.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/08 13:17:54 by ckurt             #+#    #+#             */
/*   Updated: 2021/03/08 16:27:38 by ckurt            ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minirt.h"

void	close_minirt(char *error)
{
	if (!ft_strcmp(error, ""))
		exit(EXIT_SUCCESS);
	else
	{
		printf("Error\n%s\n", error);
		exit(EXIT_FAILURE);
	}
}
