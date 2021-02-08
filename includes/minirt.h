/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minirt.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ckurt <ckurt@student.42lyon.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/08 10:32:43 by ckurt             #+#    #+#             */
/*   Updated: 2021/02/08 15:01:58 by ckurt            ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINIRT_H
# define MINIRT_H

# include <mlx.h>
# include <stdio.h>
# include <unistd.h>
# include <stdlib.h>
# include <fcntl.h>
# include "../libft/libft.h"

typedef struct s_image
{
	void		*img;
	char		*addr;
	int			bpp;
	int			line_len;
	int			endian;
}				t_frame;

typedef struct s_engine
{
	void		*mlx;
	void		*win;
	t_frame		*frame;
	char		**file;
	int			size_x;
	int			size_y;
}				t_engine;

typedef struct s_3dvector
{
	double		x;
	double		y;
	double		z;
}				t_3dvector;

typedef struct s_sphere
{
	t_3dvector	pos;
	double		r;
	int			rgb;
}				t_sphere;

typedef struct s_plane
{
	t_3dvector	pos;
	t_3dvector	rot;
	int			rgb;
}				t_plane;

typedef struct	s_square
{
	t_3dvector	*pos;
	t_3dvector	*rot;
	double		size;
	int			rgb;
}				t_square;

typedef struct	s_cylinder
{
	t_3dvector	*pos;
	t_3dvector	*rot;
	double		diameter;
	double		height;
	int			rgb;
}				t_cylinder;

typedef struct	s_triangle
{
	t_3dvector	*pos1;
	t_3dvector	*pos2;
	t_3dvector	*pos3;
	int			rbg;
}				t_triangle;

int			start_init(char *map_path, t_engine *engine, int save);
int			init_frame(t_engine *engine);
int			check_resolution(t_engine *engine, int save);
int			check_caps_args(t_engine *engine);
int			exit_hook(t_engine *engine);
void		check_args(int argc, char **argv);
void		close_minirt(int error);
void		clean_close(t_engine *engine);
char		**get_map_info(char *path_to_map, t_engine *engine);
void		put_pxl(t_engine *engine, int x, int y, int color);
void		fill_screen(t_engine *engine);
int			key_press(int key, t_engine *engine);
int			exit_hook(t_engine *engine);

t_3dvector		vectoradd(t_3dvector v1, t_3dvector v2);
t_3dvector		vectormultiply(t_3dvector v1, double value);
t_3dvector		getvector(double x, double y, double z);
t_3dvector		vectorminus(t_3dvector v1, t_3dvector v2);

#endif