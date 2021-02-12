/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raytrace_sphere.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ckurt <ckurt@student.42lyon.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/09 14:03:27 by ckurt             #+#    #+#             */
/*   Updated: 2021/02/12 14:38:59 by ckurt            ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minirt.h"

bool	secdegsolve(t_3dvector point, double *t1, double *t2)
{
	double	discr;
	double	root;

	discr = point.y * point.y - 4 * point.x * point.z;
	if (discr < 0)
		return (false);
	else if (discr == 0)
	{
		*t1 = -0.5 * point.y / point.x;
		*t2 = -0.5 * point.y / point.x;
	}
	else
	{
		if (point.y > 0)
			root = -0.5 * (point.y + sqrt(discr));
		else
			root = -0.5 * (point.y - sqrt(discr));
		*t1 = root / point.x;
		*t2 = point.z / root;
	}
	if (*t1 > *t2)
		ft_swap(t1, t2);
	return (true);
}

bool	inter_sphere(const t_ray ray, const t_sphere sphere, t_hit *hit)
{
	double		t1;
	double		t2;
	t_3dvector	vect;

	vect = vectorminus(ray.origin, sphere.pos);
	if (!secdegsolve(get_vector(scalar(ray.direction, ray.direction)
				, 2 * scalar(ray.direction, vect),
				scalar(vect, vect) - pow(sphere.diameter, 2)), &t1, &t2))
		return (false);
	if ((t1 < 0 && t2 < 0) || (t1 > hit->dist && t2 > hit->dist))
		return (false);
	else if (t1 <= 0)
		t1 = t2;
	else if (t2 <= 0)
		t2 = t1;
	hit->dist = ft_dmin(t1, t2);
	hit->pos = vectoradd(ray.origin, vectormultiply(ray.direction, t2));
	hit->normal = get_normalized(vectorminus(hit->pos, sphere.pos));
	hit->pos = vectoradd(hit->pos, vectormultiply(hit->normal, 0.001));
	return (true);
}

void	raytrace_spheres(t_engine *engine, t_hit *hit, t_ray *ray)
{
	t_list		*new;
	t_sphere	*sphere;

	new = engine->scene->spheres;
	while (new)
	{
		sphere = new->content;
		if (inter_sphere(*ray, *sphere, hit))
			hit->color = sphere->rgb;
		new = new->next;
	}
}
