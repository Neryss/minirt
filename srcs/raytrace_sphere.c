/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raytrace_sphere.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ckurt <ckurt@student.42lyon.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/09 14:03:27 by ckurt             #+#    #+#             */
/*   Updated: 2021/02/09 15:32:38 by ckurt            ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minirt.h"

static bool	inter_sphere(t_sphere *sp, t_hit *hit, t_ray *ray)
{
	t_3dvector	tmp;
	double		adj;
	double		d2;
	double		r2;
	double		thc;
	double		t;
	double		t1;

	tmp = vectorminus(sp->pos, ray->origin);
	adj = scalar(tmp, ray->origin);
	d2 = scalar(tmp, tmp) - (adj * adj);
	r2 = sp->r * sp->r;
	if (d2 > r2)
		return (false);
	thc = sqrt(r2 - d2);
	t = adj - thc;
	t1 = adj + thc;
	if (t < 0.0 && t1 < 0.0)
		return (false);
	if (t < t1)
		adj = t;
	else
		adj = t1;
	if (adj > hit->dist)
		return (false);
	hit->dist = adj;
	return (true);
}

void	raytrace_spheres(t_engine *engine, t_hit *hit, t_ray *ray)
{
	t_list	*new;

	new = engine->scene->spheres;
	while (new)
	{
		if (inter_sphere(new->content, hit, ray))
			hit->color = ((t_sphere *)new->content)->rgb;
		new = new->next;
	}
}