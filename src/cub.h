/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llima-ce <llima-ce@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/03 17:22:02 by llima-ce          #+#    #+#             */
/*   Updated: 2023/01/10 11:39:33 by llima-ce         ###   ########.fr       */
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
# include "structs.h"
# include "defines.h"

t_game	*read_map(char **argv);
int		custom_error(char *error, int err);
void	free_ptr(void **ptr);
void	clean_all(t_game *game, int err);
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
void	my_mlx_pixel_put(t_img *data, int x, int y, int color);
int		get_sprite_color(int pixel, char *sprite, int shade);
void	draw_mini_map(t_game *game, int a, int b, int y);
void	horizontal_ray_check(t_game *game, t_ray *ray);
void	vertical_ray_check(t_game *game, t_ray *ray);
void	horizontal_ray_dist(t_game *game, t_ray *ray);
void	vertical_ray_dist(t_game *game, t_ray *ray);
void	calculate_ray_wall_height(t_game *game, t_ray *ray, t_ray_print *draws);
void	cam_rotation(t_game *game);
void	move_player(t_game *game);
int		get_color_t(int trgb, char type);
#endif