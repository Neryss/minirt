/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   save.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ckurt <ckurt@student.42lyon.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/09 10:53:42 by ckurt             #+#    #+#             */
/*   Updated: 2021/02/18 12:48:20 by ckurt            ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minirt.h"

void	init_headers(unsigned int *headers
, t_engine *engine, int extrabytes)
{
	int	paddedsize;

	paddedsize = engine->size_y * ((engine->size_x * 3) + extrabytes);
	headers[0] = paddedsize + 54;
	headers[1] = 0;
	headers[2] = 54;
	headers[3] = 40;
	headers[4] = engine->size_x;
	headers[5] = engine->size_y;
	headers[7] = 0;
	headers[8] = paddedsize;
	headers[9] = 0;
	headers[10] = 0;
	headers[11] = 0;
	headers[12] = 0;
}

void	write_headers(int outfile, unsigned int *headers)
{
	int	i;

	i = 0;
	while (i <= 5)
	{
		write_custom(outfile, headers[i] & 0x000000FF);
		write_custom(outfile, (headers[i] & 0x0000FF00) >> 8);
		write_custom(outfile, (headers[i] & 0x00FF0000) >> 16);
		write_custom(outfile, (headers[i] & (unsigned int) 0xFF000000) >> 24);
		i++;
	}
	write_custom(outfile, 1);
	write_custom(outfile, 0);
	write_custom(outfile, 32);
	write_custom(outfile, 0);
	i = 7;
	while (i <= 12)
	{
		write_custom(outfile, headers[i] & 0x000000FF);
		write_custom(outfile, (headers[i] & 0x0000FF00) >> 8);
		write_custom(outfile, (headers[i] & 0x00FF0000) >> 16);
		write_custom(outfile, (headers[i] & (unsigned int) 0xFF000000) >> 24);
		i++;
	}
}

void	get_save(t_engine *engine, char *filename)
{
	unsigned int	headers[13];
	int				outfile;
	int				extrabytes;

	extrabytes = 4 - ((engine->size_x * 3) % 4);
	if (extrabytes == 4)
		extrabytes = 0;
	init_headers(headers, engine, extrabytes);
	render(engine);
	outfile = open(filename, O_WRONLY | O_APPEND | O_CREAT | O_TRUNC, 0775);
	write(outfile, "BM", 2);
	write_headers(outfile, headers);
	imgcpy(outfile, engine);
	close(outfile);
}

int	get_pixel_color(t_engine *engine, int x, int y)
{
	char	*src;

	src = engine->frame->addr + (y
			* (engine->frame->line_len) + x * (engine->frame->bpp / 8));
	return (*(int *)src);
}

void	imgcpy(int fd, t_engine *engine)
{
	int	x;
	int	y;
	int	i;
	int	tmp;
	int	*buffer;

	y = engine->size_y;
	while (--y >= 0)
	{
		buffer = malloc(engine->size_x * sizeof(int));
		if (!buffer)
			close_minirt("Malloc error\n");
		x = 0;
		i = 0;
		while (x < engine->size_x)
		{
			tmp = get_pixel_color(engine, x, y);
			buffer[i++] = tmp;
			x++;
		}
		write(fd, buffer, engine->size_x * 4);
		free(buffer);
	}
}
