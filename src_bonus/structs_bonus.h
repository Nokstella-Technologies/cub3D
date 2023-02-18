/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   structs_bonus.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vantonie <vantonie@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/09 20:22:01 by llima-ce          #+#    #+#             */
/*   Updated: 2023/02/17 19:51:04 by vantonie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef STRUCTS_BONUS_H
# define STRUCTS_BONUS_H

typedef struct s_img
{
	int			bpp;
	int			size_l;
	int			endian;
	int			width;
	int			height;
	int			color;
	void		*img_ptr;
	char		*dump;
}				t_img;

typedef struct s_hero {
	int			x;
	int			y;
	float		px;
	float		py;
	float		pdx;
	float		pdy;
	float		pa;
}			t_hero;

typedef struct s_map {
	char	*no;
	char	*so;
	char	*we;
	char	*ea;
	int		floor_c[3];
	int		celling_c[3];
	char	**map;
	int		map_x;
	int		map_y;
	t_hero	*hero;
}			t_map;

typedef struct s_sprite {
	t_img	*ea;
	t_img	*no;
	t_img	*so;
	t_img	*we;
}			t_sprite;

typedef struct s_move {
	t_bool	w;
	t_bool	a;
	t_bool	s;
	t_bool	d;
	t_bool	rot_r;
	t_bool	rot_l;
}			t_move;

typedef struct s_game {
	t_img		*img;
	void		*mlx;
	void		*win;
	t_sprite	*sprite;
	t_map		*cmap;
	t_hero		*hero;
	t_move		*move;
	int			err;
}			t_game;

typedef struct s_ray {
	int		r;
	int		mx;
	int		my;
	int		mp;
	int		dof;
	float	rx;
	float	ry;
	float	ra;
	float	xo;
	float	yo;
	float	vx;
	float	vy;
	float	dis_v;
	float	dis_h;
	float	tan;
	char	eye_v;
	char	eye_h;
}				t_ray;

typedef struct s_ray_print{
	int		ca;
	int		line_h;
	int		line_off;
	int		color;
	double	ty;
	double	tx;
	double	ty_step;
	float	ty_off;
	float	shade;
}			t_ray_print;
#endif