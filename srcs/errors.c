/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   errors.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ckurt <ckurt@student.42lyon.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/08 13:17:54 by ckurt             #+#    #+#             */
/*   Updated: 2021/02/08 13:22:29 by ckurt            ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minirt.h"

static void	error_handler(int error)
{
	if (error == -6)
		printf("Error\nInitialized unique object twice or more\n");
	if (error == -5)
		printf("Error\nNo camera\n");
	if (error == -4)
		printf("Error\nDesired file doesn't exist\n");
	if (error == -3)
		printf("Error\nTrying to open a directory\n");
	if (error == -2)
		printf("Error\nWrong scene format\n");
	if (error == -1)
		printf("Error\nWrong number of arguments\n");
	if (error == 1)
		printf("Error\nInit failed!\n");
	if (error == 2)
		printf("Error\nResolution fail\n");
	if (error == 3)
		printf("Error\nParsing error\n");
	if (error == 4)
		printf("Error\nMalloc error\n");
	if (error == 5)
		printf("Error\nObject list not initialized correctly\n");
}

void	close_minirt(int error)
{
	if (error == 0)
		exit(EXIT_SUCCESS);
	else
	{
		error_handler(error);
		exit(EXIT_FAILURE);
	}
}
