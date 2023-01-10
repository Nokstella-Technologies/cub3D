/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   start_game.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llima-ce <llima-ce@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/29 14:05:55 by llima-ce          #+#    #+#             */
/*   Updated: 2023/01/10 17:32:42 by llima-ce         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub.h"

int	key_pressed(int keycode, t_game *game)
{
	if (keycode == KEY_W)
		game->move->w = TRUE;
	if (keycode == KEY_S)
		game->move->s = TRUE;
	if (keycode == KEY_LEFT)
		game->move->rot_l = TRUE;
	if (keycode == KEY_RIGHT)
		game->move->rot_r = TRUE;
	if (keycode == KEY_A)
		game->move->a = TRUE;
	if (keycode == KEY_D)
		game->move->d = TRUE;
	return (0);
}

int	key_release(int keycode, t_game *game)
{
	if (keycode == KEY_ESC)
		close_all(game);
	if (keycode == KEY_W)
		game->move->w = FALSE;
	if (keycode == KEY_S)
		game->move->s = FALSE;
	if (keycode == KEY_LEFT)
		game->move->rot_l = FALSE;
	if (keycode == KEY_RIGHT)
		game->move->rot_r = FALSE;
	if (keycode == KEY_A)
		game->move->a = FALSE;
	if (keycode == KEY_D)
		game->move->d = FALSE;
	return (0);
}

void	loop(t_game *game)
{
	mlx_do_sync(game->mlx);
	mlx_hook(game->win, 2, 1L << 0, &key_pressed, game);
	mlx_hook(game->win, 3, 1L << 1, &key_release, game);
	mlx_hook(game->win, 17, 0, &close_all, game);
	mlx_hook(game->win, 9, 1L << 21, &print_mini_map, game);
	mlx_loop_hook(game->mlx, &print_mini_map, game);
	mlx_loop(game->mlx);
}

void	start_game(t_game *game)
{
	t_img	img;

	game->mlx = mlx_init();
	game->win = mlx_new_window(game->mlx, MAP_X, MAP_Y, "Cub42D");
	if (!game->mlx || !game->win)
	{
		game->err = custom_error("failed to open the screen", 520);
		close_all(game);
	}
	init_sprites(game);
	img.img_ptr = mlx_new_image(game->mlx, MAP_X, MAP_Y);
	img.dump = mlx_get_data_addr(img.img_ptr, &img.bpp, &img.size_l,
			&img.endian);
	game->img = &img;
	game->hero = game->cmap->hero;
	if (game->err != 0)
		close_all(game);
	loop(game);
}
