/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raytracing.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ckurt <ckurt@student.42lyon.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/12 14:48:13 by ckurt             #+#    #+#             */
/*   Updated: 2021/02/22 15:06:20 by ckurt            ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minirt.h"

static void	init_obj(t_handler *handler, t_hit *hit, t_engine *engine)
{
	handler->light = handler->list->content;
	handler->color = create_rgb(0, 0, 0);
	handler->ray = create_ray(hit->pos, vectorminus(handler->light->pos, hit->pos));
	handler->obs_hit = closest_inter(engine, handler->ray);
}

void	handle_lights(t_engine *engine, t_hit *hit)
{
	t_handler	obj;

	obj.list = engine->scene->lights;
	obj.diffuse = create_rgb(0, 0, 0);
	while (obj.list)
	{
		init_obj(&obj, hit, engine);
		if (distance(hit->pos, obj.light->pos) < obj.obs_hit->dist)
		{
			obj.normal_dot_light = ft_dmax(scalar(hit->normal,
						obj.ray->direction), 0) * (10 * obj.light->intensity)
				/ distance(hit->pos, obj.light->pos);
			obj.color = mult_rgb_double(add_rgb_rgb(
						mult_rgb_double(obj.light->color, obj.normal_dot_light),
						obj.color), ALBEDO);
			obj.diffuse = add_rgb_rgb(obj.diffuse, obj.color);
		}
		obj.list = obj.list->next;
		free(obj.obs_hit);
		free(obj.ray);
	}
	hit->color = mult_rgb_rgb(add_rgb_rgb(mult_rgb_double(engine->scene->alight.color,
					engine->scene->alight.intensity), obj.diffuse), hit->color);
	set_hit_color(hit);
}

static void	draw_pixel(t_engine *engine, int x, int y, t_hit *hit)
{
	put_pxl(engine, x, y, 0x000000);
	put_pxl(engine, x, y, ft_rgbtohex(hit->color.r,
		hit->color.g, hit->color.b));
	free(hit);
}

t_ray	*create_spe_ray(t_engine *engine, int x, int y)
{
	t_ray	*ray;

	ray = create_ray(engine->camera->pos,
			getvector(x - engine->size_x
				/ 2, engine->size_y / 2 - y,
				(engine->size_y / 2) / tan((
						engine->camera->fov * M_PI / 180) / 2)));
	return (ray);
}

void	do_raytracing(t_engine *engine)
{
	int		x;
	int		y;
	t_ray	*ray;
	t_hit	*hit;

	y = -1;
	while (++y < engine->size_y)
	{
		x = -1;
		while (++x < engine->size_x)
		{
			ray = create_spe_ray(engine, x, y);
			hit = closest_inter(engine, ray);
			if (hit->dist < INFINITY)
			{
				if (scalar(hit->normal, ray->direction) >= 0)
					hit->normal = vectormultiply(hit->normal, -1);
				handle_lights(engine, hit);
			}
			draw_pixel(engine, x, y, hit);
			free(ray);
		}
	}
}
