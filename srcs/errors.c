/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   errors.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ckurt <ckurt@student.42lyon.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/08 13:17:54 by ckurt             #+#    #+#             */
/*   Updated: 2021/02/15 14:54:46 by ckurt            ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minirt.h"

void	close_minirt(char *error)
{
	if (!ft_strcmp(error, ""))
		exit(EXIT_SUCCESS);
	else
	{
		printf("%s\n", error);
		exit(EXIT_FAILURE);
	}
}
