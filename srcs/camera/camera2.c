/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   camera2.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ckurt <ckurt@student.42lyon.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/11 13:45:38 by ckurt             #+#    #+#             */
/*   Updated: 2021/03/11 14:02:50 by ckurt            ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minirt.h"

t_3dvector	vec3_rotatex(t_3dvector vec3, double alpha)
{
	double	y;
	double	z;

	y = vec3.y * cos(M_PI * alpha) - vec3.z * sin(M_PI * alpha);
	z = vec3.y * sin(M_PI * alpha) + vec3.z * cos(M_PI * alpha);
	return (get_vector(vec3.x, y, z));
}

t_3dvector	vec3_rotatey(t_3dvector vec3, double beta)
{
	double	x;
	double	z;

	x = vec3.x * cos(M_PI * beta) + vec3.z * sin(M_PI * beta);
	z = vec3.x * -sin(M_PI * beta) + vec3.z * cos(M_PI * beta);
	return (get_vector(x, vec3.y, z));
}

t_3dvector	vec3_rotatez(t_3dvector vec3, double gamma)
{
	double	x;
	double	y;

	x = vec3.x * cos(M_PI * gamma) - vec3.y * sin(M_PI * gamma);
	y = vec3.x * sin(M_PI * gamma) + vec3.y * cos(M_PI * gamma);
	return (get_vector(x, y, vec3.z));
}

t_3dvector	vec3_rotatexyz(t_3dvector vec3, t_3dvector ovec3)
{
	t_3dvector	rvec3;
	t_3dvector	tmp_x;
	t_3dvector	tmp_y;

	tmp_x = vec3_rotatex(vec3, ovec3.x);
	tmp_y = vec3_rotatey(tmp_x, ovec3.y);
	rvec3 = vec3_rotatez(tmp_y, ovec3.z);
	return (rvec3);
}
