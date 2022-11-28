/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llima-ce <llima-ce@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/03 17:22:02 by llima-ce          #+#    #+#             */
/*   Updated: 2022/11/28 19:08:57 by llima-ce         ###   ########.fr       */
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

typedef struct	s_vars {
	void	*mlx;
	void	*win;
}				t_vars;

typedef struct	s_pixel {
	void	*img;
	char	*addr;
	int		bits_per_pixel;
	int		line_length;
	int		endian;
}				t_pixel;

typedef struct s_map {
	char	*no;
	char	*so;
	char	*we;
	char	*ea;
	int		floor_c[3];
	int		celing_c[3];
	char	**map;
	int		map_x;
	int		map_y;
}			t_map;

typedef struct	s_game {
	t_vars	*vars;
	t_map	*cmap;
	int		err;
}			t_game;


// char map[5][5] = {"11111","10001","10N01", "10001", "11111"};
#define MAP_WIDTH 64
#define SPRINT_MINIMAP "./textures/minimap.xpm"

# define X_EVENT_KEY_PRESS 2
# define X_EVENT_DESTROY_NOTIFY 17
# define X_EVENT_FOCUS_IN 9

# define KEY_ESC 65307
# define KEY_Q 113

# define KEY_W 119
# define KEY_A 97
# define KEY_S 115
# define KEY_D 100

# define KEY_UP 65362
# define KEY_LEFT 65361
# define KEY_DOWN 65364
# define KEY_RIGHT 65363
# define PI 3.1415926535


# define UNKNOWN_ERR 500
# define MALLOC_ERR 501
# define FD_ERR 502

# define INV_ATR 511
# define REPEAT_ATR 510
# define INV_COLOR 512

// # define FD_ERR "File not found"
// # define ML_ERR "Malloc error"



t_game	*read_map(char **argv);
int		custom_error(char *error, int err);
void	free_ptr(void **ptr);
void	*clean_map(t_map *map, int a);
int		verify_sprite_color(char *line, t_map *map);

#endif