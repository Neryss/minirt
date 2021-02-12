/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raytracing.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ckurt <ckurt@student.42lyon.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/12 14:48:13 by ckurt             #+#    #+#             */
/*   Updated: 2021/02/12 14:49:52 by ckurt            ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minirt.h"

void	handle_lights(t_engine *engine, t_hit *hit)
{
	t_ray	*ray;
	t_hit	*obs_hit;
	t_list	*list;
	t_light	*light;
	t_rgb	color;
	t_rgb	diffuse;
	double	normal_dot_light;

	list = engine->scene->lights;
	diffuse = create_rgb(0, 0, 0);
	while (list)
	{
		light = list->content;
		color = create_rgb(0, 0, 0);
		ray = create_ray(hit->pos, vectorminus(light->pos, hit->pos));
		obs_hit = closest_inter(engine, ray);
		if (distance(hit->pos, light->pos) < obs_hit->dist)
		{
			normal_dot_light = ft_dmax(scalar(hit->normal,
						ray->direction), 0) * (10 * light->intensity)
				/ distance(hit->pos, light->pos);
			color = mult_rgb_double(add_rgb_rgb(mult_rgb_double(
							light->color,
							normal_dot_light), color), ALBEDO);
			diffuse = add_rgb_rgb(diffuse, color);
		}
		free(obs_hit);
		list = list->next;
	}
	hit->color = mult_rgb_rgb(add_rgb_rgb(mult_rgb_double(engine->scene->alight.color,
					engine->scene->alight.intensity), diffuse), hit->color);
	hit->color.r = imin(hit->color.r, 255);
	hit->color.g = imin(hit->color.g, 255);
	hit->color.b = imin(hit->color.b, 255);
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