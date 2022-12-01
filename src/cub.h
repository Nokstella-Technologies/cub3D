/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llima-ce <llima-ce@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/03 17:22:02 by llima-ce          #+#    #+#             */
/*   Updated: 2022/12/01 18:38:22 by llima-ce         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB_H
# define CUB_H

# include <stdio.h>
# include <stdlib.h>

# include <math.h>
# include <fcntl.h>
# include <unistd.h>
# include "libft.h"
# include "mlx.h"
# include "defines.h"

typedef struct	s_data {
	void	*img;
	char	*addr;
	int		bits_per_pixel;
	int		line_length;
	int		endian;
}				t_data;

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

typedef struct	s_sprite {
	void	*ea;
	void	*no;
	void	*so;
	void	*we;
}			t_sprite;

typedef struct s_move {
	t_bool	w;
	t_bool	a;
	t_bool	s;
	t_bool	d;
	t_bool	rot_r;
	t_bool	rot_l;
}			t_move;

typedef struct	s_game {
	t_data		*img;
	void		*mlx;
	void		*win;
	t_sprite	*sprite;
	t_map		*cmap;
	t_hero		*hero;
	t_move		*move;
	int			err;
}			t_game;

// char map[5][5] = {"11111","10001","10N01", "10001", "11111"};

t_game	*read_map(char **argv);
int		custom_error(char *error, int err);
void	free_ptr(void **ptr);
void	clean_all(t_game *game);
int		verify_sprite_color(char *line, t_map *map);
void	validation_map_line(t_map *cmap, t_game *game);
void	start_game(t_game *game);
int		print_mini_map(t_game *game);
float	fix_ang(float a);
int		draw_line(t_game *game, int begin[2], int end[2], int color);
void	square(t_game *game, int x, int y, int color);
int		close_all(t_game *game);
int		create_trgb(int t, int r, int g, int b);
float	deg_to_rad(float a);
#endif