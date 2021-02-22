/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ckurt <ckurt@student.42lyon.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/08 13:36:26 by ckurt             #+#    #+#             */
/*   Updated: 2021/02/22 15:57:45 by ckurt            ###   ########lyon.fr   */
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

t_hit	*closest_inter(t_engine *engine, t_ray *ray)
{
	t_hit	*hit;

	hit = malloc(sizeof(t_hit));
	if (!hit)
		close_minirt("During malloc");
	hit->dist = INFINITY;
	hit->color = create_rgb(0, 0, 0);
	raytrace_cylinders(engine, hit, ray);
	raytrace_spheres(engine, hit, ray);
	raytrace_planes(engine, hit, ray);
	raytrace_disk(engine, hit, ray);
	raytrace_triangles(engine, hit, ray);
	return (hit);
}

void	render(t_engine *engine)
{
	if (engine->need_render)
	{
		mlx_clear_window(engine->mlx, engine->win);
		do_raytracing(engine);
		mlx_put_image_to_window(engine->mlx, engine->win, engine->frame->img, 0, 0);
		mlx_do_sync(engine->mlx);
	}
	engine->need_render = false;
}

int	call_render(t_engine *engine)
{
	render(engine);
	return (1);
}
