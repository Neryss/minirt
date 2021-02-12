/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raytracing.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ckurt <ckurt@student.42lyon.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/12 14:48:13 by ckurt             #+#    #+#             */
/*   Updated: 2021/02/12 15:14:38 by ckurt            ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minirt.h"

void	handle_lights(t_engine *engine, t_hit *hit)
{
	t_handler	obj;

	obj.list = engine->scene->lights;
	obj.diffuse = create_rgb(0, 0, 0);
	while (obj.list)
	{
		obj.light = obj.list->content;
		obj.color = create_rgb(0, 0, 0);
		obj.ray = create_ray(hit->pos, vectorminus(obj.light->pos, hit->pos));
		obj.obs_hit = closest_inter(engine, obj.ray);
		if (distance(hit->pos, obj.light->pos) < obj.obs_hit->dist)
		{
			obj.normal_dot_light = ft_dmax(scalar(hit->normal,
						obj.ray->direction), 0) * (10 * obj.light->intensity)
				/ distance(hit->pos, obj.light->pos);
			obj.color = mult_rgb_double(add_rgb_rgb(mult_rgb_double(obj.light->color, obj.normal_dot_light), obj.color), ALBEDO);
			obj.diffuse = add_rgb_rgb(obj.diffuse, obj.color);
		}
		free(obj.obs_hit);
		obj.list = obj.list->next;
	}
	hit->color = mult_rgb_rgb(add_rgb_rgb(mult_rgb_double(engine->scene->alight.color,
					engine->scene->alight.intensity), obj.diffuse), hit->color);
	set_hit_color(hit);
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
			if (hit->dist < INFINITY)
			{
				if (scalar(hit->normal, ray->direction) >= 0)
					hit->normal = vectormultiply(hit->normal, -1);
				handle_lights(engine, hit);
			}
			// printf("[%f]\n", hit->dist);
			put_pxl(engine, x, y, 0x000000);
			put_pxl(engine, x, y, ft_rgbtohex(hit->color.r, hit->color.g, hit->color.b));
			free(ray);
			free(hit);
			x++;
		}
		y++;
	}
}