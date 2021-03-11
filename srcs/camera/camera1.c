/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   camera1.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ckurt <ckurt@student.42lyon.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/11 13:44:27 by ckurt             #+#    #+#             */
/*   Updated: 2021/03/11 13:52:34 by ckurt            ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minirt.h"

t_ray	new_ray(t_3dvector origin, t_3dvector dir)
{
	t_ray	ray;

	ray.origin = origin;
	ray.direction = get_normalized(dir);
	return (ray);
}

t_ray	init_ray(t_engine *engine, t_camera cam, int x, int y)
{
	t_3dvector	res;
	double		size_x;
	double		size_y;

	size_x = engine->size_x;
	size_y = engine->size_y;
	res.x = ((2 * ((x + .5) / size_x)) - 1) * (size_x / size_y)
		*tan((cam.fov / 2) *(M_PI / 180));
	res.y = (1 - (2 * ((y + .5) / size_y))) * tan((cam.fov / 2) *(M_PI / 180));
	res.z = 1;
	return (new_ray(cam.pos, vec3_rotatexyz(res, cam.rot)));
}
