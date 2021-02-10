/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ckurt <ckurt@student.42lyon.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/08 13:36:26 by ckurt             #+#    #+#             */
/*   Updated: 2021/02/10 11:26:00 by ckurt            ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minirt.h"

void	put_pxl(t_engine *engine, int x, int y, int color)
{
	char	*dst;

	dst = engine->frame->addr
		+ (y * engine->frame->line_len + x
			* (engine->frame->bpp / 8));
	*(unsigned int*)dst = color;
}

void	fill_screen(t_engine *engine)
{
	int	x;
	int	y;

	x = 0;
	y = 0;
	while (y < engine->size_y)
	{
		while (x < engine->size_x)
		{
			put_pxl(engine, x, y, ft_rgbtohex(0, 0, 0));
			x++;
		}
		x = 0;
		y++;
	}
}

void	do_raytracing(t_engine *engine)
{
	int	x;
	int	y;
	t_ray	*ray;
	t_hit	*hit;

	y = 0;
	while (y < engine->size_y)
	{
		x = 0;
		while (x < engine->size_x)
		{
			ray = create_ray(engine->camera->pos,
			getvector(x - engine->size_x
			/ 2, engine->size_y / 2 - y,
			(engine->size_y / 2) / tan((engine->camera->fov * M_PI / 180) / 2)));
			hit = closest_inter(engine, ray);
			printf("[%f]\n", hit->dist);
			put_pxl(engine, x, y, ft_rgbtohex(hit->color.r, hit->color.g, hit->color.b));
			// put_pxl(engine, x, y, ft_rgbtohex(255, 0, 0));
			x++;
			free(ray);
		}
		y++;
	}
}

t_rgb	create_rgb(int r, int g, int b)
{
	t_rgb	rgb;

	rgb.r = r;
	rgb.g = g;
	rgb.b = b;

	return (rgb);
}

t_hit	*closest_inter(t_engine *engine, t_ray *ray)
{
	t_hit	*hit;

	hit = malloc(sizeof(t_hit));
	if (!hit)
		close_minirt("Error during malloc");
	hit->dist = INFINITY;
	hit->color = create_rgb(0, 0, 0);
	raytrace_spheres(engine, hit, ray);
	return (hit);
}

void	render(t_engine *engine)
{
	mlx_clear_window(engine->mlx, engine->win);
	fill_screen(engine);
	do_raytracing(engine);
	mlx_put_image_to_window(engine->mlx, engine->win, engine->frame->img, 0, 0);
	mlx_do_sync(engine->mlx);
}

int	call_render(t_engine *engine)
{
	render(engine);
	return (1);
}
