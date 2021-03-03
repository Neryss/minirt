/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raytracing_utils.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ckurt <ckurt@student.42lyon.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/03 11:06:08 by ckurt             #+#    #+#             */
/*   Updated: 2021/03/03 11:12:32 by ckurt            ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minirt.h"

t_3dvector	set_ray_direction(t_engine *engine, t_camera cam, int x, int y)
{
	t_3dvector	pixel;
	t_3dvector	axis;
	double		size_x;
	double		size_y;
	double		fov;

	axis = get_vector(0, 1, 0);
	size_x = engine->size_x;
	size_y = engine->size_y;
	fov = cam.fov;
	pixel.x = ((2 * ((x + .5) / size_x)) - 1) * (size_x / size_y)
		* tan((fov / 2) * (M_PI / 180));
	pixel.y = (1 - (2 * ((y + .5) / size_y))) * tan((fov / 2) * (M_PI / 180));
	pixel.z = 1;
	if (!(cam.rot.x == 0 && cam.rot.y > 0 && cam.rot.z == 0))
		pixel = apply_rot(pixel, cam.rot, axis);
	return (pixel);
}

t_ray	*create_spe_ray(t_engine *engine, int x, int y)
{
	t_ray	*ray;

	ray = create_ray(engine->camera->pos,
			set_ray_direction(engine, *engine->camera, x, y));
	return (ray);
}
