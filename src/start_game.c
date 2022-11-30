/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   start_game.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llima-ce <llima-ce@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/29 14:05:55 by llima-ce          #+#    #+#             */
/*   Updated: 2022/11/30 16:33:34 by llima-ce         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "cub.h"

void	move(t_game *game, int keycode)
{
	if (keycode == KEY_A || keycode == KEY_LEFT || keycode == KEY_D
		|| keycode == KEY_RIGHT)
	{
		if (keycode == KEY_D || keycode == KEY_RIGHT)
			game->hero->pa -= 5;
		else if (keycode == KEY_A || keycode == KEY_LEFT)
			game->hero->pa += 5;
		game->hero->pa = fix_ang(game->hero->pa);
		game->hero->pdx = cos(DEGTORAD(game->hero->pa));
		game->hero->pdy = -sin(DEGTORAD(game->hero->pa));
	}
}

void	move_forward(t_game *game, int keycode)
{
	if ((keycode == KEY_W || keycode == KEY_UP) && game->cmap->map[(int)(game->cmap->hero->py + game->cmap->hero->pdy * 5) / 64][(int)(game->cmap->hero->px + game->cmap->hero->pdx * 5) / 64] != '1')
	{
		game->cmap->hero->px += game->cmap->hero->pdx * 5;
		game->cmap->hero->py += game->cmap->hero->pdy * 5;
	}
	else if ((keycode == KEY_S || keycode == KEY_DOWN )&& game->cmap->map[(int)(game->cmap->hero->py - game->cmap->hero->pdy * 5) / 64][(int)(game->cmap->hero->px - game->cmap->hero->pdx * 5) / 64] != '1')
	{
		game->cmap->hero->px-= game->cmap->hero->pdx * 5;
		game->cmap->hero->py-= game->cmap->hero->pdy * 5;
	}
}

int	key_hook(int keycode, t_game *game)
{
	if (keycode == 113 || keycode == KEY_ESC)
		clean_all(game);
	else if (keycode == KEY_D || keycode == KEY_RIGHT || keycode == KEY_A
		|| keycode == KEY_LEFT)
		move(game, keycode);
	else if (keycode == KEY_S || keycode == KEY_DOWN || keycode == KEY_W
		|| keycode == KEY_UP)
		move_forward(game, keycode);
	print_mini_map(game);
	return (0);
}

static int	resume_game(t_game *game)
{
	print_mini_map(game);
	return (0);
}

void	start_game(t_game *game)
{
	t_data	img;

	game->mlx = mlx_init();
	game->win = mlx_new_window(game->mlx, MAP_X, MAP_Y, "Hello world!");
	img.img = mlx_new_image(game->mlx, MAP_X, MAP_Y);
	img.addr = mlx_get_data_addr(img.img, &img.bits_per_pixel, &img.line_length,
								&img.endian);
	game->img = &img;
	game->hero = game->cmap->hero;
	print_mini_map(game);
	mlx_key_hook(game->win, &key_hook, game);
	mlx_hook(game->win, 17, 0, &close_all, game);
	mlx_hook(game->win, 9, 1L << 21, &resume_game, game);
	mlx_loop(game->mlx);
}