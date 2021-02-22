/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minirt.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ckurt <ckurt@student.42lyon.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/08 10:32:43 by ckurt             #+#    #+#             */
/*   Updated: 2021/02/22 14:20:54 by ckurt            ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINIRT_H
# define MINIRT_H

# include <mlx.h>
# include <stdio.h>
# include <unistd.h>
# include <stdlib.h>
# include <fcntl.h>
# include <math.h>
# include <stdbool.h>
# include "../libft/libft.h"

# define ALBEDO 0.4
# define EPSILON 0.001

# define EXIT_KEY 53
# define CAM_KEY 8

typedef struct s_3dvector
{
	double		x;
	double		y;
	double		z;
}				t_3dvector;

typedef struct s_image
{
	void		*img;
	char		*addr;
	int			bpp;
	int			line_len;
	int			endian;
}				t_frame;

typedef struct s_alight
{
	double		intensity;
	t_rgb		color;
}				t_alight;

typedef struct s_scene
{
	t_list		*cams;
	t_list		*lights;
	t_list		*spheres;
	t_list		*planes;
	t_list		*disk;
	t_list		*triangles;
	t_list		*cylinders;
	t_alight	alight;
}				t_scene;

typedef struct s_camera
{
	t_3dvector	pos;
	t_3dvector	rot;
	int			fov;
	int			id;
}				t_camera;

typedef struct s_engine
{
	void		*mlx;
	void		*win;
	t_frame		*frame;
	t_scene		*scene;
	t_camera	*camera;
	char		**file;
	int			size_x;
	int			size_y;
	bool		need_render;
}				t_engine;

typedef struct s_hit
{
	t_3dvector	pos;
	t_3dvector	normal;
	double		dist;
	t_rgb		color;
}				t_hit;

typedef struct s_cylinder
{
	t_3dvector	pos;
	t_3dvector	rot;
	double		radius;
	double		height;
	t_rgb		color;
}				t_cylinder;

typedef struct s_triangle
{
	t_3dvector	v1;
	t_3dvector	v2;
	t_3dvector	v3;
	t_3dvector	normal;
	t_rgb		color;
}				t_triangle;

typedef struct s_ray
{
	t_3dvector	origin;
	t_3dvector	direction;
}				t_ray;

typedef struct s_sphere
{
	t_3dvector	pos;
	double		diameter;
	t_rgb		rgb;
}				t_sphere;

typedef struct s_plane
{
	t_3dvector	origin;
	t_3dvector	normal;
	t_rgb		rgb;
}				t_plane;

typedef struct s_disk
{
	t_3dvector	origin;
	t_3dvector	normal;
	double		diameter;
	t_rgb		rgb;
}				t_disk;

typedef struct s_light
{
	t_3dvector	pos;
	double		intensity;
	t_rgb		color;
}				t_light;

typedef struct s_handler
{
	t_ray		*ray;
	t_hit		*obs_hit;
	t_list		*list;
	t_light		*light;
	t_rgb		color;
	t_rgb		diffuse;
	double		normal_dot_light;
}				t_handler;

typedef struct s_resolve
{
	double		tmin;
	t_3dvector	t;
	t_3dvector	b;
	t_3dvector	normal;
}				t_resolve;

void		init_engine(t_engine *engine);
void		add_sphere(t_list **lst, char *file);
void		add_light(t_list **lst, char *file);
void		add_plane(t_list **lst, char *file);
void		add_camera(t_list **lst, char *line);
void		add_triangle(t_list **lst, char *file);
void		add_cylinder(t_list **lst, char *file);
void		get_scene(t_engine *engine);
void		init_headers(unsigned int *headers
, t_engine *engine, int extrabytes);
void		write_headers(int outfile, unsigned int *headers);
void		get_save(t_engine *engine, char *filename);
void		write_custom(int fd, unsigned int val);
void		check_args(int argc, char **argv);
void		close_minirt(char *error);
void		clean_close(t_engine *engine);
void		put_pxl(t_engine *engine, int x, int y, int color);
void		imgcpy(int fd, t_engine *engine);
void		render(t_engine *engine);
void		fill_screen(t_engine *engine);
void		raytrace_spheres(t_engine *engine, t_hit *hit, t_ray *ray);
void		raytrace_planes(t_engine *engine, t_hit *hit, t_ray *ray);
void		raytrace_disk(t_engine *engine, t_hit *hit, t_ray *ray);
void		raytrace_triangles(t_engine *engine, t_hit *hit, t_ray *ray);
void		raytrace_cylinders(t_engine *engine, t_hit *hit, t_ray *ray);
void		normalize(t_3dvector *v1);
void		change_cam(t_engine *engine);
void		do_raytracing(t_engine *engine);
void		get_triangle_normal(t_triangle *triangle);
void		set_hit_color(t_hit *hit);
void		set_res(t_resolve *res, double t, t_ray ray, t_cylinder cy);
void		init_res(t_resolve *res, t_cylinder cy);
void		set_hit(t_hit *hit, t_ray ray, t_resolve res);
char		**get_map_info(char *path_to_map, t_engine *engine);
double		getnorm2(t_3dvector v1);
double		scalar(t_3dvector v1, t_3dvector v2);
double		ft_dmin(double a, double b);
double		distance(t_3dvector p1, t_3dvector p2);
double		ft_dmax(double a, double b);
double		to_rad(double value);
double		calc_a(t_ray ray, t_resolve *res);
double		calc_b(t_ray ray, t_resolve *res);
float		magnitude(t_3dvector a);
int			start_init(char *map_path, t_engine *engine, int save);
int			init_frame(t_engine *engine);
int			check_resolution(t_engine *engine, int save);
int			check_caps_args(t_engine *engine);
int			exit_hook(t_engine *engine);
int			key_press(int key, t_engine *engine);
int			exit_hook(t_engine *engine);
int			get_pixel_color(t_engine *engine, int x, int y);
int			call_render(t_engine *engine);
int			imax(int a, int b);
int			imin(int a, int b);
bool		check_rgb(t_rgb c);
bool		check_normal(t_3dvector nor);
bool		check_fov(int fov);
bool		check_intensity(double i);
t_ray		*create_ray(t_3dvector pos, t_3dvector dir);
t_hit		*closest_inter(t_engine *engine, t_ray *ray);
t_rgb		create_rgb(int r, int g, int b);
t_rgb		mult_rgb_double(t_rgb rgb, double value);
t_rgb		add_rgb_rgb(t_rgb c1, t_rgb c2);
t_rgb		mult_rgb_rgb(t_rgb r1, t_rgb r2);
t_rgb		ft_get_rgb(char **line);

t_3dvector	process_normal(t_ray ray, t_3dvector normal);
t_3dvector	return_normal(t_3dvector point, t_cylinder cy);
t_3dvector	apply_rot(t_3dvector pos, t_3dvector dir, t_3dvector rot);
t_3dvector	get_normalized(t_3dvector vector);
t_3dvector	parse_vector(char **line);
t_3dvector	vectoradd(t_3dvector v1, t_3dvector v2);
t_3dvector	vectormultiply(t_3dvector v1, double value);
t_3dvector	getvector(double x, double y, double z);
t_3dvector	vectorminus(t_3dvector v1, t_3dvector v2);
t_3dvector	vectordivide(t_3dvector v1, double value);
t_3dvector	vectorcross(t_3dvector v1, t_3dvector v2);
t_3dvector	get_vector(double x, double y, double z);

#endif