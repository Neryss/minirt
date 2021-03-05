/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ckurt <ckurt@student.42lyon.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/03 15:57:44 by ckurt             #+#    #+#             */
/*   Updated: 2021/03/05 18:24:29 by ckurt            ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minirt.h"

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
	raytrace_triangles(engine, hit, ray);
	raytrace_square(engine, hit, ray);
	return (hit);
}

int	call_render(t_engine *engine)
{
	if (engine->need_render)
		render(engine);
	return (1);
}

void	put_pxl(t_engine *engine, int x, int y, int color)
{
	char	*dst;

	dst = engine->frame->addr
		+ (y * engine->frame->line_len + x
			* (engine->frame->bpp / 8));
	*(unsigned int*)dst = color;
}
